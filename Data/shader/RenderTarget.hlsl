#include "Basis.hlsl"

Texture2D   g_txDiffuse   : register(t0);
Texture2D	g_txNormalMap : register(t1);
//Buffer<float> g_fGaussianMask : register(t2);
//TextureCube g_txCubeMap   : register(t2);

SamplerState samLinear : register (s0);

static const int g_iTexSizeX = 1024;
static const int g_iTexSizeY = 820;

float g_fGaussianMask[9] =
{
	0.013519569015984728,
	0.047662179108871855,
	0.11723004402070096,
	0.20116755999375591,
	0.240841295721373,
	0.20116755999375591,
	0.11723004402070096,
	0.047662179108871855,
	0.013519569015984728
};

struct VS_OUTPUT_MRT
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};


VS_OUTPUT_MRT VS_MRT(float4 pos : POSITION)
{
	VS_OUTPUT_MRT output;
	output.pos = pos;
	// Plane�� ���� ��ġ�� �ؽ��� ��ǥ�� ��ȯ
	output.tex.x = (pos.x + 1.0f) / 2.0f;		// -1 ~ 1�� ���� 0 ~ 1�� ��ȯ
	output.tex.y = (-pos.y + 1.0f) / 2.0f;		// 1 ~ -1�� ���� 0 ~ 1�� ��ȯ
	return output;
}

float4 GaussianBlur(float3 vTex, Texture2D tex2D)
{
	int		g_iMask = 3;

	float dx = 1.0f / g_iTexSizeX;
	float dy = 1.0f / g_iTexSizeY;
	float2 vStart = float2(vTex.x - dx * (g_iMask / 2),
						   vTex.y - dy * (g_iMask / 2));
	float4 vSum = 0;
	float fX, fY;
	//[roll]
	for (int ix = 0; ix < g_iMask; ix++)
	{
		fX = vStart.x + dx * ix;
		//[roll]
		for (int iy = 0; iy < g_iMask; iy++)
		{
			fY = vStart.y + dy * iy;
			vSum += tex2D.Sample(samLinear, float2(fX, fY)) * g_fGaussianMask[ix * g_iMask + iy];
		}
	}
	vSum.w = 1.0f;
	return vSum;
}
float4 Blur(float3 vTex, Texture2D tex2D)
{
	int		g_iMask = 3;
	// �ȼ� ����
	float dx = 1.0f / g_iTexSizeX;
	float dy = 1.0f / g_iTexSizeY;
	// �ȼ� ���� �ݰ��� ù��° ĭ���� ����
	float2 vStart = float2(vTex.x - dx * (g_iMask / 2),
						   vTex.y - dy * (g_iMask / 2));
	float4 vSum = 0;
	float fX, fY;
	// ����ġ
	float fWeight = 1.0f / (g_iMask*g_iMask);

	//[roll]
	for (int ix = 0; ix < g_iMask; ix++)
	{
		fX = vStart.x + dx * ix;
		//[roll]
		for (int iy = 0; iy < g_iMask; iy++)
		{
			fY = vStart.y + dy * iy;
			// ���� �ȼ����� �ش� ����ġ�� ���� ������ ����
			vSum += tex2D.Sample(samLinear, float2(fX, fY)) * fWeight;
		}
	}
	vSum.w = 1.0f;
	return vSum;
}
float4 Sharp(float3 vTex, Texture2D tex2D)
{
	int		g_iMask = 3;

	float dx = 1.0f / g_iTexSizeX;
	float dy = 1.0f / g_iTexSizeY;
	float2 vStart = float2(vTex.x - dx * (g_iMask / 2),
						   vTex.y - dy * (g_iMask / 2));
	float4 vSum = 0;
	float fX, fY;
	float fWeight = -1.0f;
	int   iSharp = g_iMask * g_iMask / 2;
	//[roll]
	for (int ix = 0; ix < g_iMask; ix++)
	{
		fX = vStart.x + dx * ix;
		//[roll]
		for (int iy = 0; iy < g_iMask; iy++)
		{
			fWeight = -1.0f;
			// �߽� �ȼ��̸� ����ġ�� ��ü �� ������ŭ ��, 
			if (ix* g_iMask + iy == iSharp)
			{
				fWeight = g_iMask * g_iMask;
			}
			fY = vStart.y + dy * iy;
			vSum += tex2D.Sample(samLinear, float2(fX, fY))*fWeight;
		}
	}
	vSum.w = 1.0f;
	return vSum;
}

float4 Sobel(float3 vTex, Texture2D tex2D)
{
	float4 diffuseColor = tex2D.Sample(samLinear, vTex.xy);

	float dx = 1.0f / g_iTexSizeX;
	float dy = 1.0f / g_iTexSizeY;

	float4 tl = tex2D.Sample(samLinear, float2(vTex.x - dx, vTex.y - dy));
	float4 l = tex2D.Sample(samLinear, float2(vTex.x - dx, vTex.y));
	float4 bl = tex2D.Sample(samLinear, float2(vTex.x - dx, vTex.y + dy));

	float4 t = tex2D.Sample(samLinear, float2(vTex.x, vTex.y - dy));
	float4 b = tex2D.Sample(samLinear, float2(vTex.x, vTex.y + dy));

	float4 tr = tex2D.Sample(samLinear, float2(vTex.x + dx, vTex.y - dy));
	float4 r = tex2D.Sample(samLinear, float2(vTex.x + dx, vTex.y));
	float4 br = tex2D.Sample(samLinear, float2(vTex.x + dx, vTex.y + dy));

	// -1 0 1
	// -2 0 2
	// -1 0 1
	float4 SobelX = -tl - (2.0f * l) - bl + tr + (2.0f * r) + br;

	// -1 -2 -1
	//  0  0  0
	//  1  2  1
	float4 SobelY = -tl - (2.0f * t) - tr + bl + (2.0f * b) + br;

	//float3 N = normalize(float3(-SobelX.x, -SobelY.x, 1.0f));
	//N = N *0.5f +0.5f;

	float4 SobelResult = abs(SobelX) + abs(SobelY);
	float deltaNormal = (SobelResult.x + SobelResult.y + SobelResult.z) / 3;
	float deltaDepth = SobelResult.w;

	if (deltaNormal < 0.9f && deltaDepth < 0.05f)
	{
		return float4(1, 1, 1, 0);
	}
	// �븻�� ���̰� ũ�ų�, ������ ���̰� ũ�� ��輱
	else
	{
		return float4(0, 0, 0, 1);
	}
}

// �� ���⸸�� ����ũ ����
float4 GaussianPixelShader(float3 vTex, Texture2D tex2D)
{
	int		g_iTexSizeX = 800;
	int		g_iTexSizeY = 600;

	const float Pixels[13] =
	{
		-6,    -5,   -4,   -3,   -2,   -1,    0,    1,    2,    3,    4,    5,    6,
	};

	const float BlurWeights[13] =
	{
		0.002216,   0.008764,   0.026995,   0.064759,   0.120985,   0.176033,
		0.199471,
		0.176033,   0.120985,   0.064759,   0.026995,   0.008764,   0.002216,
	};

	// Pixel width
	float dx = 1.0f / g_iTexSizeX;
	float dy = 1.0f / g_iTexSizeY;
	float4 color = { 0, 0, 0, 1 };

	float2 blur;
	blur.y = vTex.y;

	for (int i = 0; i < 13; i++)
	{
		blur.x = vTex.x + Pixels[i] * dx;
		color += tex2D.Sample(samLinear, blur.xy) * BlurWeights[i];
	}
	return color;
}



// MRT �ȼ�
float4 PS_MRT(VS_OUTPUT_MRT input) : SV_TARGET
{
	float4 vTexture = g_txDiffuse.Sample(samLinear,input.tex);
	//if (vTexture.w < 0.1f)
	//{
	//	discard;
	//}
	float4 vNormalDepth = g_txNormalMap.Sample(samLinear,input.tex);
	
	// ���� ��� �� �ܺ� ���
	float4 vEdgeColor = Sobel(float3(input.tex, 0.0f),g_txNormalMap);
	float4 vFinal = vEdgeColor * vTexture;

//#ifdef GAUSSIAN_BLUR
	//float4 vBlur = GaussianBlur(float3(input.tex, 0.0f), g_txDiffuse);
//#else
	float4 vBlur = Blur(float3(input.tex, 0.0f), g_txDiffuse);
//#endif

	float4 vSharp = Sharp(float3(input.tex, 0.0f), g_txDiffuse);
	// ������ ����, �ָ� �� ȿ��
	float4 cBlur = lerp(vSharp, vBlur, vNormalDepth.w);

	vFinal = lerp(vFinal, cBlur, 0.5f);
	vFinal.w = 1.0f;
	//vNormalDepth.w = 1.0f;
	return vFinal;
}


// ��ó�� None
float4 PS_MRT_None(VS_OUTPUT_MRT input) : SV_TARGET
{
	float4 vFinal = g_txDiffuse.Sample(samLinear,input.tex);
	vFinal.w = 1.0f;
	return vFinal;
}

// �븻�� ���
float4 PS_MRT_Normal(VS_OUTPUT_MRT input) : SV_TARGET
{
	//float4 vNormalDepth = g_txNormalMap.Sample(samLinear,input.tex);
	//vNormalDepth.w = 1.0f;	// �ؽ�ó�� �׸������� ������ ���¶� w �������ѵ� �״��
	return g_txNormalMap.Sample(samLinear,input.tex);
}