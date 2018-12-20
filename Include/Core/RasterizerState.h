#pragma once
#include "header.h"

class RasterizerState
{
protected:
	// ���� ������
	D3D11_PRIMITIVE_TOPOLOGY m_PrimitiveType;
	D3D11_RASTERIZER_DESC	 m_RasterizerDesc;
	D3D11_CULL_MODE			 m_CullMode;
	D3D11_FILL_MODE			 m_FillMode;

	// ���ؽ�, �ȼ� ���̴�
	ID3D11RasterizerState*	 m_pRasterizerState;
public:

	// �����Ͷ����� ���°� ����
	HRESULT SetRasterizerState(const D3D11_CULL_MODE& cullMode, const D3D11_FILL_MODE& fillMode, const D3D11_PRIMITIVE_TOPOLOGY& = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) noexcept;
	HRESULT SetRasterizerState(const D3D11_RASTERIZER_DESC& RSDesc) noexcept;

	// ������Ƽ�� ���� ���� 
	void SetPrimitiveType(const D3D11_PRIMITIVE_TOPOLOGY& type) noexcept;

	// �����Ͷ����� ���°� ���� 
	HRESULT SetState(ID3D11DeviceContext* pDContext) noexcept;
public:
	RasterizerState() = default;
	~RasterizerState() = default;
};

