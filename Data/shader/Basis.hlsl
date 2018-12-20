// setShaderResourceView~ �Ҷ� ù��° ���ڰ� ���������� �����̰�,
// ���������� �� ���Կ� �ش��ϴ� �ؽ��� �ȼ� ���� �޾ƿ� ������ ����� �� �ִ�.(Max 8, ���÷��� ��������)
//Texture2D g_txDiffuse  : register (t0);
//Texture2D g_txDiffuse1 : register (t1);
//SamplerState samLinear : register (s0);

static const float NEAR = 0.1f;
static const float FAR = 2000.0f;

// ��� ���� : ���� 0��
cbuffer cbMatrix: register(b0)
{
	matrix	g_matWorld		: packoffset(c0);
	matrix	g_matView		: packoffset(c4);
	matrix	g_matProj		: packoffset(c8);
	matrix	g_matNormal		: packoffset(c12);
	float4  g_MeshColor     : packoffset(c16);
};
// ȯ�� ������
cbuffer cbObjectData : register(b1)
{
	//matrix g_matNormal;
	float4 cb_LightVector;
	float4 cb_EyePos;
	float4 cb_EyeDir;
}
// ����? ������
cbuffer cbLightMaterial : register(b2)
{
	float4 cb_AmbientLightColor : packoffset(c0);
	float4 cb_DiffuseLightColor : packoffset(c1);
	float3 cb_SpecularLightColor: packoffset(c2);
	float  cb_SpecularPower		: packoffset(c2.w);
};
// ���׸���, ������ ������
cbuffer cbMaterial : register (b3)
{
	float			cb_useLight     : packoffset(c0.x);
	float			cb_useNormalMap : packoffset(c0.y);
	float			cb_useEnviMap   : packoffset(c0.z);
	float			cb_useShadow    : packoffset(c0.w);
	float4x4		g_matShadow  : packoffset(c1);
	float			g_iObjectID  : packoffset(c5.x);
	float			g_iNumKernel : packoffset(c5.y);
	//float			g_iDummy	 : packoffset(c4.zw);
}
// ť��� ���
cbuffer cbCubeViewMatrix : register(b4)
{
	matrix g_matCubeView[6] : packoffset(c0);
}


// MRT��
struct PBUFFER_OUTPUT
{
	float4 color0 : SV_TARGET0;
	float4 color1 : SV_TARGET1;
};

// PNCTT ���� �Է�
struct VS_INPUT_PNCTT
{
	float3 pos : POSITION;
	float3 nor : NORMAL;
	float4 col : COLOR0;			// 0�� �������ͷ� ���
	float2 tex : TEXCOORD0;
	float3 tan : TANGENT;
};
// ���� ���(�븻+����)
struct VS_OUTPUT_PNCT
{
	float4 pos : SV_POSITION;
	float4 nor : NORMAL;
	float4 col : COLOR0;
	float2 tex : TEXCOORD0;
};