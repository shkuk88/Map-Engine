#pragma once
#include "Renderer.h"


// n * m ���� ���� ����, ���̸� ������ �ش� �ؽ��� �ȼ������� ����
class HeightMap : public Renderer
{
protected:
	D3DXVECTOR3 m_light = { -100, 100, 0 };		// �ϴ� ����
	// ��ü ������, ���̽���, �� ����
	UINT m_vertexCount;
	UINT m_faceCount;
	float m_cellSize;
	// ��ü ���� ��, �� ����
	UINT m_vertexCols;			
	UINT m_vertexRows;
	// �� ��ü ������
	float m_mapHalfWidth;
	float m_mapHalfHeight;
	vector<UINT> m_vertexHeight;
	// ���̽����� �븻 ����
	vector<D3DXVECTOR3>	  m_faceNormal;			
	// �� ������ �����ϴ� ���̽� ����Ʈ
	vector<vector<UINT> > m_NormalLookupTable;	
protected:
	void GenFaceNormal()			 noexcept;	// 1. ��� ���̽��� ���� �븻 ����
	void GenNormalLookupTable()		 noexcept;	// 2. �� ������ �����ϴ� ��� ���̽� ����Ʈ ����
	void GenVertexNormalFastLookup() noexcept;	// 3. ���� ���
	void InitVertexNormalVector()	 noexcept;	// �� ������ �븻 ���� ��� (1+2+3)
	D3DXVECTOR3 GetNormalVector(const UINT& vectorIndex) noexcept;	// �ش� �ε����� �븻 ���� ��ȯ
	virtual HRESULT CreateIndexBuffer(const WORD& cols, const WORD& rows, const UINT& indexCount) noexcept;
public:
	// �� ����
	virtual HRESULT Create(const WORD& cols, const WORD& rows, const float& cellSize = 1, const float& offsetX = 1.0f, const float& offsetY = 1.0f) noexcept;
	// ���̸� �ҷ�����
	virtual void SetHeightMap(ID3D11DeviceContext* pContext, const wstring_view& fileName, const wstring_view& directory) noexcept;
	// ���̸� �ҷ����� + ����
	virtual void CreateHeightMap(ID3D11DeviceContext* pContext, const wstring_view& fileName, const float& cellSize = 1, const float& offsetX = 1.0f, const float& offsetY = 1.0f, const wstring_view& directory = L"../../data/texture/") noexcept;
	// �ش� ��ǥ �� ���� ���� ��ȯ
	virtual float GetMapHeight(const D3DXVECTOR3& position, Renderer* pPlane);
public:
	virtual bool Init()											noexcept override;
	virtual bool Frame(const float& spf, const float& accTime)	noexcept override;
	virtual bool Render(ID3D11DeviceContext* pDContext)			noexcept override;
	virtual bool Release()										noexcept override;
	virtual Component* clone() noexcept override;
protected:
	Component* cloneAddition() noexcept override;
protected:
	HeightMap() = default;
public:
	HeightMap(const wstring_view& myName, const EComponent& eComType, const wstring_view& srcName = L"",
			  const string_view& vertexShaderName = "VS_Final", const string_view& pixelShaderName = "PS_Final") noexcept;
	virtual ~HeightMap() = default;
};