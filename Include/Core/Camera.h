#pragma once
#include "GameObject.h"

struct CB_VSMatrix
{
	D3DXMATRIX  m_matWorld;
	D3DXMATRIX  m_matView;
	D3DXMATRIX  m_matProj;
	D3DXMATRIX  matNormal;
	D3DXVECTOR4 m_meshColor;
};

class Camera : public GameObject
{
protected:
	// �θ�� ������ ��ǥ, ����
	D3DXVECTOR3	m_curPosition;
	D3DXQUATERNION m_curRotation;

	float m_Aspect;			// ��Ⱦ��
	float m_FOV;			// �þ߰�
	float m_Near;			// �ּ� ���� �Ÿ�
	float m_Far;			// �ִ� ���� �Ÿ�
	// �ִ��, ����, �����
	float m_maxMoveSpeed;
	float m_accMoveSpeed;
	float m_curMoveSpeed;
	// ȸ����
	float m_rotateSpeed;

	bool m_isPerspect = true;		// �����̴�
public:
	static Camera* SelectCamera;	// ���õ� ī�޶�

	D3DXMATRIX  m_matWorld;			// ����
	D3DXMATRIX  m_matView;			// ��
	D3DXMATRIX  m_matProj;			// ����
	CB_VSMatrix		m_cbVS;			// ��ȯ�� ���
protected:
	// �� ���, ���� ��� ����
	void SetViewMatrix();
	void SetProjMatrix();
	void UpdateMatrix() noexcept override;					// ��� ����
public:
	virtual void SetParent(GameObject* pParent) override;
	void SetOrthoWH(const float& width, const float& height);
	void isPerspect(const bool& isPerspect);

	virtual bool Init()											noexcept override;
	virtual bool Frame(const float& spf, const float& accTime)	noexcept override;
	virtual bool Render(ID3D11DeviceContext* pDContext)			noexcept override;
	virtual bool Release()										noexcept override;
protected:
	Camera() = default;
public:
	Camera(const wstring_view& myName, const bool& isPerspect = true) noexcept;
	virtual ~Camera() = default;
};