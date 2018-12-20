#pragma once
#include "header.h"
#include "PlaneUI.h"

class RenderDepthView
{
private:
	enum { MaxMaskCount = 25, };
protected:

	//ID3D11Buffer* m_pMaskBuffer;
	//ID3D11ShaderResourceView* m_pMaskArray;
	//int m_iMask = 3;

	int m_RTViewCount;

	D3D11_TEXTURE2D_DESC		m_TexDesc;
	ID3D11Texture2D*			m_pTexTextures[2];	// �߰� ������ �ؽ�ó
	ID3D11RenderTargetView*		m_pTexRTViews[2];	// �ؽ�ó ����, �븻+����
public:
	PlaneUI*					m_pScreen;

	ID3D11ShaderResourceView*	m_pTexSRViews[2];	// �߰� ��¿� ���ҽ�
	ID3D11RenderTargetView*		m_pRTView;			// ������ �ĸ� ���� �� ������ �� ����
	ID3D11DepthStencilView*		m_pDepthSView;		// ���� ���ٽ� ��
protected:
	virtual HRESULT CreateResourceRTView(ID3D11DeviceContext* pDContext, IDXGISwapChain*& pSwapChain, const DXGI_SWAP_CHAIN_DESC& swapDesc) noexcept;
	virtual HRESULT CreateDSView(const DXGI_SWAP_CHAIN_DESC& swapDesc) noexcept;
	// ����þ� ���� ���µ�
	virtual HRESULT CreateKernel() noexcept;
public:
	HRESULT Create(ID3D11DeviceContext* pDContext, IDXGISwapChain* pSwapChain, const DXGI_SWAP_CHAIN_DESC& swapDesc, const bool& isShadowMap = false) noexcept;
	void DrawView(ID3D11DeviceContext* pDContext)  noexcept;
	void ClearView(ID3D11DeviceContext* pDContext) noexcept;
	void Setting(ID3D11DeviceContext* pDContext) noexcept;
	vector<Sprite>::iterator& GetScreenSprite() const noexcept;

	RenderDepthView() = default;
	virtual ~RenderDepthView() = default;
};