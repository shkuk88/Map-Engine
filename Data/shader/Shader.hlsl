#include "Basis.hlsl"

Texture2D   g_txDiffuse   : register(t0);
Texture2D	g_txNormalMap : register(t1);
TextureCube g_txCubeMap   : register(t2);
//Texture2D g_txDiffuse1 : register (t1);

SamplerState samLinear : register (s0);

// �� �Է�
struct VS_INPUT_PC
{
	float3 pos : POSITION;
	float4 col : COLOR0;
};
// �� ���
struct VS_OUTPUT_PC
{
	float4 pos : SV_POSITION;
	float4 col : COLOR0;
};

//// �⺻ ����
//VS_OUTPUT_PNCT VS_PNCT(VS_INPUT_PNCTT input)
//{
//	VS_OUTPUT_PNCT output = (VS_OUTPUT_PNCT)0;
//	output.pos = mul(float4(input.pos, 1.0f), g_matWorld);
//	output.pos = mul(output.pos, g_matView);
//	output.pos = mul(output.pos, g_matProj);
//
//	output.col = input.col;
//	output.tex = input.tex;
//	return output;
//}
//VS_OUTPUT_PNCT VS_Light(VS_INPUT_PNCTT input)
//{
//	VS_OUTPUT_PNCT output = (VS_OUTPUT_PNCT)0;
//	output.pos = mul(float4(input.pos, 1.0f), g_matWorld);
//	
//	input.nor = normalize(mul(input.nor, (float3x3)g_matNormal));
//
//	float3 vLightDir = normalize(cb_LightVector.xyz - output.pos.xyz);// -output.pos.xyz;
//	float fDot = lerp(dot(vLightDir, input.nor), 1.0f, 0.3f) + 0.2f;
//	output.col = float4(fDot, fDot, fDot, 1.0f) * input.col;
//
//	output.pos = mul(output.pos, g_matView);
//	output.pos = mul(output.pos, g_matProj);
//
//	//output.col = input.col;
//	output.tex = input.tex;
//	return output;
//}

// �⺻ ����
VS_OUTPUT_PNCT VS_PNCT(VS_INPUT_PNCTT input)
{
	VS_OUTPUT_PNCT output = (VS_OUTPUT_PNCT)0;
	output.pos = mul(float4(input.pos, 1.0f), g_matWorld);
	output.pos = mul(output.pos, g_matView);
	output.pos = mul(output.pos, g_matProj);
	
	input.nor = normalize(mul(input.nor, (float3x3)g_matNormal));
	output.nor = float4(input.nor, (output.pos.w - NEAR) / (FAR - NEAR));

	output.col = input.col;
	output.tex = input.tex;
	return output;

}
VS_OUTPUT_PNCT VS_Light(VS_INPUT_PNCTT input)
{
	VS_OUTPUT_PNCT output = (VS_OUTPUT_PNCT)0;
	output.pos = mul(float4(input.pos, 1.0f), g_matWorld);
	output.pos = mul(output.pos, g_matView);
	output.pos = mul(output.pos, g_matProj);

	input.nor = normalize(mul(input.nor, (float3x3)g_matNormal));
	output.nor = float4(input.nor, (output.pos.w - NEAR) / (FAR - NEAR));

	float3 vLightDir = normalize(cb_LightVector.xyz - output.pos.xyz);// -output.pos.xyz;
	float fDot = lerp(dot(vLightDir, input.nor), 1.0f, 0.2f) + 0.2f;
	output.col = float4(fDot, fDot, fDot, 1.0f) * input.col;

	//output.col = input.col;
	output.tex = input.tex;
	return output;
}
// �� ���� ���̴�
VS_OUTPUT_PC VS_PC(VS_INPUT_PC input)
{
	VS_OUTPUT_PC output = (VS_OUTPUT_PC)0;
	output.pos = mul(float4(input.pos, 1.0f), g_matWorld);
	output.pos = mul(output.pos, g_matView);
	output.pos = mul(output.pos, g_matProj);
	output.col = input.col;
	return output;
}
// �⺻ �ȼ�
PBUFFER_OUTPUT PS_PCT(VS_OUTPUT_PNCT input)
{
	PBUFFER_OUTPUT output;
	output.color0 = g_txDiffuse.Sample(samLinear, input.tex) * input.col;
	//output.color1 = float4(input.nor.xyz * 0.5f + 0.5f, input.nor.w);
	//input.nor.w = 1.0f;
	output.color1 = float4(input.nor);
	return output;
}


// �� �ȼ� ���̴�
float4 PS_PC(VS_OUTPUT_PC input) : SV_TARGET
{
	return input.col;
}

// �������� �ȼ� ���̴�
float4 PS_Frustum(VS_OUTPUT_PNCT input) : SV_TARGET
{
	return float4(0.8f, 1.0f, 0.8f, 0.6f);
}



//[maxvertexcount(20)]		// �ִ� ������Ƽ�� ����
////			   PrimitiveType(point, line, triangle, lineadj, triangleadj)
//void GS_Sphere(triangle VS_OUTPUT_PNCT input[3], inout TriangleStream<VS_OUTPUT_PNCT> TriStream)
//{
//	VS_OUTPUT_PNCT output;
//	// �ﰢ�� ���� ���
//	float3 centerPos = (input[0].pos.xyz + input[1].pos.xyz + input[2].pos.xyz) / 3.0f;
//
//	// ������ ���� �߽����� ����� ���̽� �߰�
//	for (int i = 0; i < 3; ++i)
//	{
//		// �ϳ��� �ﰢ���� ������ ��������� ����
//		output.pos = input[i].pos;
//		TriStream.Append(output);
//
//		int iNext = (i + 1) % 3;
//		output.pos = input[iNext].pos;
//		TriStream.Append(output);
//		output.pos = float4(centerPos, 1.0f);
//		TriStream.Append(output);
//		// primitive Strip�� ������ �����, primitive ������ ����?
//		TriStream.RestartStrip();
//	}
//	TriStream.RestartStrip();
//}