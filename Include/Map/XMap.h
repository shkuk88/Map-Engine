#pragma once
#include "XShape.h"
#include "XMapImporter.h"

enum TexturePresence { Tex_Have = 0, Tex_None, Tex_Alpha };
struct ConstantBuffer_Light
{
	D3DXMATRIX	matInvWorld;		// ����� �� ����ϴ��� �ǹ�
	D3DXVECTOR4	vDiffuseMaterial;
	D3DXVECTOR4	vAmbientMaterial;	// ��ο� �κ��� �⺻������ ��� �ϵ��� �ִ� ��
	D3DXVECTOR4 vSpecularMaterial;	// �⺻ ����ŧ���� ��
	D3DXVECTOR4	vDiffuseLightColor;
	D3DXVECTOR4	vAmbientLightColor;	
	D3DXVECTOR4 vSpecularLightColor;// ����ŧ�� ����Ʈ�� ��
	D3DXVECTOR4 vLightDirection;	// �𷺼� ����Ʈ, w�� ����(�ϴ��� ������� ����)
	D3DXVECTOR4 vSightDirection;	// �ü� ����, w�� ����

};

struct XVertexLookUp
{
	set<DWORD> vListNormal;	// �����Ǵ� ������ ��ġ�� �ȵǱ� ������ set����
};

class XMap :public XShape
{
public:
	DX::XDxHelper			m_Object;
	vector<float>			m_fHeightList;
	vector<D3DXVECTOR3>		m_vFaceNormals;
	vector<long>			m_iNormalLookUpTable; //���� ������ �����ϴ� ���̽�, DWORD�� XVertexLookUp�� �ֵ��� ������ ����
	int						m_iRow;
	int						m_iCol;
	int						m_iVertexs;
	int						m_iFace;
	float					m_fDistance;
	float					m_fScaleHeight;
	ComPtr<ID3D11VertexShader>			m_pVS[3];
	ComPtr<ID3D11PixelShader>			m_pPS[3];
	map<int, ComPtr<ID3D11ShaderResourceView>>	m_AlphaSRV;
public:
	D3DXVECTOR3				m_vLook;
	ComPtr<ID3D11Buffer>	m_pLightConstantBuffer;
	ConstantBuffer_Light	m_LightData;
public:
	bool		CreateVertexList();	// Vertex,Index,Normal,Color ���� �� �󿡼� ������ �ϰ� ���Ϸ� �ҷ����°� �´�.
	bool		CreateIndexList();
	HRESULT		CreateHeightMap(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, TCHAR* HeightMap);
	float		GetHeight(float x, float z);
	float		GetHeightmap(int row, int col);
	float		Lerp(float fStart, float fEnd, float fTangent);
	bool		InitFaceNormals();				//���̽����� �븻���� ����ؼ� ����
	D3DXVECTOR3 ComputeFaceNormal(DWORD dwIndex0, DWORD dwIndex1, DWORD dwIndex2);
	bool		GetNormalLookUpTable();			//������ ���� FACE���� ���
	bool		CalcPerVertexNormalsFastLookUp();
	void		InitConstant();		// shader�� �ѱ� light vector�� ���Ƿ� ������ۿ� ����
	void		SetScaleHeight(float fScaleHeight = 1.0f);
	void		SetAlphaTexture(TCHAR* szAlphaTex0, TCHAR* szAlphaTex1, TCHAR* szAlphaTex2, TCHAR* szAlphaTex3);
	void		SetAlphaSRV(ID3D11ShaderResourceView* pSRV,int iColor);
public:
	void		SetLookVector(D3DXVECTOR3 vLook);
	void		InitLight();
	void		UpdateLight();
	bool		ImportData(ID3D11Device* pDevice, XMapImporter* pImporter);
	void		CreateBuffer(ID3D11Device* pDevice );
	void		CreateShader(ID3D11Device* pDevice, TCHAR* szMapShader, TCHAR* szOnlyColorShader, char* szVSFunctionName, char* szPSFunctionName);
public:
	virtual bool Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, float fDistance, TCHAR* szTexture, TCHAR* szHeightTexture, TCHAR* szMapShader, TCHAR* szOnlyColorShader, char* szVSFunctionName, char* szPSFunctionName);
	bool Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, float fCellCount, float fDistance, TCHAR* szTexture, TCHAR* szMapShader, TCHAR* szOnlyColorShader, char* szVSFunctionName, char* szPSFunctionName);
	bool Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, XMapImporter* pImporter, TCHAR* szMapShader, TCHAR* szOnlyColorShader, char* szVSFunctionName, char* szPSFunctionName);
	bool PreRender(ID3D11DeviceContext* pContext);
	bool PostRender(ID3D11DeviceContext* pContext);
	virtual bool Init() noexcept override;
	virtual bool Frame(const float& spf, const float& accTime) noexcept override;
	virtual bool Render(ID3D11DeviceContext* pContext) noexcept override;
	virtual bool Release() noexcept override;
public:
	XMap();
	virtual~XMap();
};