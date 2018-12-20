#pragma once
#include "RPlane.h"


// UICamera�� ���� ������
class PlaneUI : public RPlane
{
protected:
	//virtual HRESULT Create() noexcept override;
public:
	virtual bool Init()											noexcept override;
	virtual bool Frame(const float& spf, const float& accTime)	noexcept override;
	virtual bool Render(ID3D11DeviceContext* pDContext)			noexcept override;
	virtual bool Release()										noexcept override;
	virtual Component* clone() noexcept override;
protected:
	PlaneUI() = default;
public:
	PlaneUI(const wstring_view& myName, const wstring_view& srcName = L"",
		 const string_view& vertexShaderName = "VS_PNCT", const string_view& pixelShaderName = "PS_PCT") noexcept;
	virtual ~PlaneUI() = default;
};