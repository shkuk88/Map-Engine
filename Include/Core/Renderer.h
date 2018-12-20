#pragma once
#include "Light.h"
#include "Component.h"
#include "Sprite.h"

struct Vertex_PC
{
	D3DXVECTOR3 pos;		// ��ġ ��ǥ
	D3DXVECTOR4 col;		// �÷���
};

struct Vertex_PNCT
{
	D3DXVECTOR3 pos;		// ��ġ ��ǥ
	D3DXVECTOR3 nor;		// �븻 ����
	D3DXVECTOR4 col;		// �÷���
	D3DXVECTOR2 tex;		// �ؽ��� ��ǥ
	D3DXVECTOR3 tan;		// ��������
	bool operator == (const Vertex_PNCT& vertex)
	{
		return pos == vertex.pos && nor == vertex.nor && col == vertex.col && tex == vertex.tex ? true : false;
	}
};

//struct CB_Material
//{
//	float useLight;// : packoffset(c0);
//	float a;  float s; float d;
//	//bool useNormalMap;
//	//bool useEnviMap;
//	//bool useShadow;
//};

enum class EEnviType : char {
	Basic = 0, Fresnel, Refraction,
};

enum class ERenderType : char {
	Basic = 0, Particle, HeightMap, Instance, //, Line, Cube,
};


//class Camera;

// ������ ����� �ִ� ������Ʈ
class Renderer : public Component
{
protected:
	Camera** m_ppCamera;							// �������� ī�޶�, ���ý� �ش� ī�޶� ����

	UINT m_indexCount = 0;							// �ε��� ����
	vector<WORD>		m_indexList;				// �ε��� �迭
	// ���۵�
	ID3D11Buffer*		m_pVertexBuffer = nullptr;	// ���� ����
	ID3D11Buffer*		m_pIndexBuffer  = nullptr;	// �ε��� ����
	
	// ���̾ƿ�, ���̴�
	ID3D11InputLayout*	m_pInputLayout  = nullptr;	// ���� ���̾ƿ�
	ID3D11VertexShader*	m_pVShader	    = nullptr;	// ���� ���̴�
	ID3D11PixelShader*	m_pPShader	    = nullptr;	// �ȼ� ���̴�
	ID3D11ShaderResourceView* m_pEnviMap = nullptr;	  // ȯ�� ��
	ID3D11ShaderResourceView* m_pNormalMap = nullptr; // �븻 ��

	ID3D11Buffer*		m_pMatrixCBuffer = nullptr;		// ��� ���� - ���
	ID3D11Buffer*		m_pMaterialCBuffer = nullptr;	// ������, ���׸��� ���
	CB_Material			m_cbMaterial;					// ������, ���׸��� ������
	
	wstring				m_srcName;					// �ؽ�ó �̸� (default=��ü�̸�)
	vector<Sprite>*		m_pSpriteList = nullptr;	// ��������Ʈ(��ǥ, ������) ����Ʈ
	vector<Sprite>::iterator m_curSprite;			// ���� ��������Ʈ ���ͷ�����
	float  m_frameCount = 0.0f;

	bool m_isMultiTexture = false;	// ��Ƽ �ؽ��ĸ� ����
	// ���� ���� ���ÿ�
	static UINT Stride;				// ���� ũ��
	static UINT Offset;				// ���� ������
public:
	vector<Vertex_PNCT>	m_vertexList;		// ���� �迭
	ERenderType m_eRenderType = ERenderType::Basic;
protected:
	// ������->�ʱⰪ ����
	void SetInfo(const wstring_view& myName, const EComponent& eComType, const wstring_view& srcName = L"",
			const string_view& vertexShaderName = "VS_Final", const string_view& pixelShaderName = "PS_Final") noexcept;
	virtual HRESULT Create() noexcept { return S_OK; };
	// ���� ����
	HRESULT CreateConstBuffer(const void* data, const UINT& dataSize, ID3D11Buffer** pConstBuffer);
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer(const UINT& indexCount, const bool& needInit = true);
	virtual void	UpdateConstBuffer(ID3D11DeviceContext* pDContext) noexcept;

	virtual void UpdateTextureUV();
	virtual void EndSpriteEvent();
	// ���� ���� ���ϱ�
	void CreateTangentSpaceVectors(D3DXVECTOR3 *v0, D3DXVECTOR3 *v1, D3DXVECTOR3 *v2,
								   const D3DXVECTOR2& uv0, const D3DXVECTOR2& uv1, const D3DXVECTOR2& uv2,
								   D3DXVECTOR3 *vTangent, D3DXVECTOR3 *vBiNormal, D3DXVECTOR3 *vNormal) noexcept;
	void CreateTangentSpaceVectors(D3DXVECTOR3 *v1, D3DXVECTOR3 *v2, D3DXVECTOR3 *v3,
								   const float& _u1, const float& _v1, const float& _u2, const float& _v2, const float& _u3, const float& _v3,
								   D3DXVECTOR3 *vTangent, D3DXVECTOR3 *vBiNormal, D3DXVECTOR3 *vNormal) noexcept;
	//DWORD EncodeVectorAsDWORDColor(D3DXVECTOR3* vVector) noexcept;
public:
	// �븻, ȯ�� �� ����
	void SetNormalMap(const wstring_view& normalTexName) noexcept;
	void SetEnviromentMap(const wstring_view& enviTexName, const EEnviType& eEnviType = EEnviType::Basic) noexcept;
	void SetLightRate(const float& value)	noexcept;
	void SetShadowRate(const float& value)	noexcept;
	float GetLightRate()			  const noexcept;
	float GetShadowRate()			  const noexcept;

	// ����, �ȼ� ���̴� �� ���̾ƿ� ����
	void SetShaderLayout(const string_view& vertexName, const string_view& pixelName);
	void SetPixelShader(const string_view& pixelName);
	// �����Լ�
	void SetSpriteList(const wstring_view& srcName = L"") noexcept;
	void SetSpriteList(vector<Sprite>* pSpriteList) noexcept;
	vector<Sprite>::iterator& GetCurSprite() noexcept;
	void SetCamera(Camera** pCamera);
	void SetColor(ID3D11DeviceContext* pDContext, const float& red, const float& green, const float& blue);
	void SetColor(ID3D11DeviceContext* pDContext, const D3DXVECTOR4& color);
	void SetAlpha(ID3D11DeviceContext* pDContext, const float& alpha);

	bool isMultiTexture() noexcept;
	void isMultiTexture(const bool& isMulti) noexcept;

	virtual bool PrevRender(ID3D11DeviceContext* pDContext)		noexcept;
	virtual bool PostRender(ID3D11DeviceContext* pDContext)		noexcept;
	virtual bool Init()											noexcept override;
	virtual bool Frame(const float& spf, const float& accTime)	noexcept override;
	virtual bool Render(ID3D11DeviceContext* pDContext)			noexcept override;
	virtual bool Release()										noexcept override;
	virtual Component* clone() noexcept override;
protected:
	virtual Component* cloneAddition() noexcept;		// clone ����� pointer �� �߰� ó��
protected:
	friend class CoreMFC;
	friend class Raycast;
	Renderer() = default;
	Renderer(Renderer&) = default;
	Renderer(Renderer&&) = default;
	Renderer& operator = (const Renderer&) = default;
	Renderer& operator = (Renderer&&) = default;
public:
	~Renderer() noexcept = default;
};