#pragma once
#include "SamplerState.h"
#include "RasterizerState.h"
#include "RenderDepthView.h"
#include "GameObject.h"
#include "Camera.h"
#include <filesystem>

// ���� ��ü ������
enum class ERasterS : char {
	Current = 0,			// �������� ����
	Basic,					// �⺻��
	Wireframe,
	CullBack,
	CullFront,
	Line,
	DepthBias,
	size					// �׿�
};
enum class EBlendS : char {
	Current = 0,
	Basic,
	NoAlpha,
	//Red,
	//Green,
	//Blue,
	size
};
enum class EDepthS : char {
	Current = 0,
	Basic,
	D_Always_S_Off,
	D_Less_S_Always,
	D_Off_S_Less,
	D_Off_S_Off,
	D_Off_NoWrite,
	size
};
enum class ESamTextureS : char {
	Current = 0,
	Basic,
	Wrap,
	Mirror,
	Clamp,
	Border,
};
enum class ESamFilterS : char {
	Current = 0,
	Basic,
	Linear,
	Anisotropic,
	Point,
	CompLinearPoint,
};
enum class EViewPort : char {
	Main = 0,
	MiniMap,
	SubView1,
	SubView2,
	SubView3,
	SubView4,
};


class Texture;

class DxManager : public IBasis, public ISingleton<DxManager>
{
private:
	ID3D11Device*				m_pD3dDevice;		// �׷���ī�� �����(���ҽ� ����)
	ID3D11DeviceContext*		m_pD3dContext;		// ������ ó�� �� ����
	IDXGIFactory*				m_pGIFactory;		// Graphic Infrastructure ��ü
	//D3D11_VIEWPORT				m_ViewPort;			// ����Ʈ
	DXGI_SWAP_CHAIN_DESC		m_SwapChainDesc;	// SwapChain����
	// ========================================================================
	map<EViewPort, D3D11_VIEWPORT>		   m_ViewPortList;	// ����Ʈ ��
	map<wstring, Texture*>				   m_TextureList;	// �ؽ��� ��

	SamplerState						   m_SamplerState;	// ���÷� ���� ��ü
	map<ERasterS, RasterizerState*>		   m_RasterList;	// �����Ͷ����� ���� ��
	map<EBlendS, ID3D11BlendState*>		   m_BlenderList;	// ���� ���� ��
	map<EDepthS, ID3D11DepthStencilState*> m_DepthList;		// ����	���� ��
	HRESULT hr;			// ���� üŷ��
public:
	IDXGISwapChain*	m_pSwapChain;		// ���� �� �ĸ� ���� ���� �� ����
	RenderDepthView	m_RTDSView;			// ��Ÿ��, ����-���ٽ� ��
	RenderDepthView m_RTDSViewShadow;	// ������ �� ������

	map<string, ID3D11VertexShader*>	   m_VShaderList;	// ���� ���̴� ��
	map<string, ID3D11PixelShader*>		   m_PShaderList;	// �ȼ� ���̴� ��
	map<string, ID3D11GeometryShader*>	   m_GShaderList;	// ���� ���̴� ��
	map<string, ID3D11InputLayout*>		   m_LayoutList;	// ��ǲ ���̾ƿ� ��
private:
	// DX �ʱ�ȭ
	HRESULT CreateDevice();
	HRESULT CreateGIFactory();
	HRESULT CreateSwapChain();
	//HRESULT SetViewPort();
	// ���µ� ����
	HRESULT CreateRasterizerState();
	HRESULT CreateBlendState();
	HRESULT CreateDepthStencilState();
	// ���̴� �ε�
	void	InitLoadShader() noexcept;
	HRESULT LoadVertexShader(const wstring_view& loadUrl, const string_view& funcName);
	HRESULT LoadPixelShader(const wstring_view& loadUrl, const string_view& funcName);
	HRESULT LoadGeometryShader(const wstring_view& loadUrl, const string_view& funcName);
	// �ؽ���, ���� ���̾ƿ� �ε�
	Texture* LoadShaderResourceView(const filesystem::path& textureName, const bool& isFullPath);
	HRESULT  LoadInputLayout(ID3DBlob* pVertexBuf, const string_view& funcName);
public:
	static ID3D11Device*& GetDevice();
	static ID3D11DeviceContext*& GetDContext();
	// ����Ʈ ����, ����
	void CreateViewPort(const EViewPort& viewEnum, const float& x, const float& y, const float& width, const float& height);
	void SetViewPort(const EViewPort& viewEnum);
	void ClearDepthStencilView();
	// ���� ����
	void SetRasterizerState(const ERasterS& rasterEnum);
	void SetBlendState(const EBlendS& blendEnum);
	void SetDepthStencilState(const EDepthS& depthEnum, const UINT& stencilRef = 1);
	void SetSamplerState(const UINT& slotIndex, const ESamTextureS& textureEnum, const ESamFilterS& filterEnum = ESamFilterS::Current, const UINT& maxAnisotropy = 16, const D3D11_COMPARISON_FUNC& compFunc = (D3D11_COMPARISON_FUNC)0);

	Texture* GetTexture(const wstring_view& textureName, const bool& isFullPath = false);
	HRESULT	ResizeDevice(const int& width, const int& height);
		
	bool InitRTView() noexcept;
	virtual bool PrevRender() noexcept;
	virtual bool PostRender() noexcept;
	virtual bool Init() noexcept override;
	virtual bool Frame() noexcept override;
	virtual bool Render() noexcept override;
	virtual bool Release() noexcept override;
private:
	friend class ISingleton<DxManager>;
	friend class Dialog_Preset;
	DxManager() = default;
public:
	virtual ~DxManager() = default;
};