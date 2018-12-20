#pragma once
#include "Renderer.h"


// �ϳ��� ���� ��Ÿ���� ��ü
class RLine : public Renderer
{
private:
	vector<Vertex_PC> m_vertexList;				// ���� ����Ʈ ���
	bool m_isDebugLine;
private:
	virtual HRESULT Create() noexcept override;
	HRESULT CreateVertexBuffer();
public:
	void SetLineInfo(ID3D11DeviceContext* pDContext, const D3DXVECTOR3& start, const D3DXVECTOR3& end, const D3DXVECTOR4& color, const bool& isDebugLine = false) noexcept;

	bool isDebugLine();
	void isDebugLine(const bool& isDebugLine);

	virtual bool PrevRender(ID3D11DeviceContext* pDContext)		noexcept override;
	virtual bool PostRender(ID3D11DeviceContext* pDContext)		noexcept override;
	virtual bool Init()											noexcept override;
	virtual bool Frame(const float& spf, const float& accTime)	noexcept override;
	virtual bool Render(ID3D11DeviceContext* pDContext)			noexcept override;
	virtual bool Release()										noexcept override;
	virtual Component* clone() noexcept override;
protected:
	RLine() = default;
public:
	RLine(const wstring_view& myName, const string_view& vertexShaderName = "VS_PC", const string_view& pixelShaderName = "PS_PC") noexcept;
	virtual ~RLine() = default;
};