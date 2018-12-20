#pragma once
#include "RCube.h"

class RPlane;

// �������� ���� ĳ����(���� �׿�)
class Character : public RCube
{
protected:
	//RPlane* m_follower;		// ����׿� �ٴ�

	float m_maxMoveSpeed = 55.0f;
	float m_accMoveSpeed = 7.0f;
	float m_curMoveSpeed = 0.0f;

	//float m_curGravity = 0.0f;
	float m_rotateSpeed = 2.0f;
public:
	virtual HRESULT Create() noexcept override;
	virtual bool Init()											noexcept override;
	virtual bool Frame(const float& spf, const float& accTime)	noexcept override;
	virtual bool Render(ID3D11DeviceContext* pDContext)			noexcept override;
	virtual bool Release()										noexcept override;
	virtual Component* clone() noexcept override;
protected:
	Character() = default;
public:
	Character(const wstring_view& myName, const EComponent& eComType, const wstring_view& srcName = L"",
			  const string_view& vertexShaderName = "VS_PNCT", const string_view& pixelShaderName = "PS_Final") noexcept;
	virtual ~Character() = default;
};