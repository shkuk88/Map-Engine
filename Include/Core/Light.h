#pragma once
#include "Camera.h"

// ȯ�� ������
struct CB_Environment
{
	//D3DXMATRIX  matNormal;
	D3DXVECTOR4 LightVector;
	D3DXVECTOR4 EyePos;
	D3DXVECTOR4 EyeDir;
};

// ���� ������
struct CB_Light
{
	D3DXVECTOR4 Ambient;
	D3DXVECTOR4 Diffuse;
	D3DXVECTOR4 Specular;
};

// ������ ������
struct CB_Material
{
	float			useLight;
	float			useNormalMap;
	float			useEnviMap;
	float			useShadow;
	D3DXMATRIX		matShadow;
	float			ObjectID;
	float			NumKernel;
	float			fZ , fW;
};

enum class ELight {
	Directional = 0, Point, SportLight, 
};


// ����Ʈ
class Light : public Camera
{
protected:
	Camera** m_ppCamera = nullptr;
	ID3D11Buffer*		m_pEnviCBuffer = nullptr;	// ȯ�� ���
	ID3D11Buffer*		m_pLightCBuffer = nullptr;	// ���� ���
	ID3D11Buffer*		m_pMaterialCBuffer = nullptr;	// ������ ���

	CB_Environment	m_cbEnviData;		// ȯ�� ������
	CB_Light		m_cbLightData;		// ���� ������

	// Color, Power, Distance...,, ī�޶� ���� Ȱ��
public:
	CB_Material		m_cbMaterial;			// ������ ������
	ELight m_lightType;
protected:
	HRESULT CreateConstBuffer(const void* data, const UINT& dataSize, ID3D11Buffer** pConstBuffer) noexcept;
	void	UpdateConstBuffer(ID3D11DeviceContext* pDContext)	noexcept;
public:
	void SetParent(GameObject* pParent)							noexcept override;

	virtual bool Init()											noexcept override;
	virtual bool Frame(const float& spf, const float& accTime)	noexcept override;
	virtual bool Render(ID3D11DeviceContext* pDContext)			noexcept override;
	virtual bool Release()										noexcept override;
protected:
	Light() = default;
public:
	Light(const wstring_view& myName, const ELight& eLightType, const bool& isPerspect = true) noexcept;
	virtual ~Light() = default;
};