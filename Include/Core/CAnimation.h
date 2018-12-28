#pragma once
#include "Component.h"
#include "Transform.h"

// �ִϸ��̼ǽ� �븻�� : �븻Ʈ������ - ������ ������� ��ġ�� �� ?

struct Anim : Transform
{
	D3DXMATRIX  matScaleAxis;

	friend class AseParser;
	friend class MaxImporter;
	friend class Dialog_Hierarchy;
};

class CAnimation : public Component
{
private:
	D3DXMATRIX m_matAnim;			// �ִ� ���
	vector<Anim> m_Animations;		// �ִϸ��̼� ����Ʈ

	UINT m_curAnimIndex = 0;		// �ִ� �ε���
	float m_animSpeed	= 1.0f;		// �ִ� �ӵ�
	float m_animFrame	= 0.0f;		// �ִ� ������ ����
	float m_frameCount	= 0.0f;		// �ִ� ����
public:
	void Update()										noexcept override;

	bool Init()											noexcept override;
	bool Frame(const float& spf, const float& accTime)	noexcept override;
	bool Render(ID3D11DeviceContext* pDContext)			noexcept override;
	bool Release()										noexcept override;
	Component* clone() noexcept;
public:
	friend class AseParser;
	friend class MaxImporter;
	friend class Dialog_Hierarchy;
	CAnimation();
	virtual ~CAnimation() = default;
};