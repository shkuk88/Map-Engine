#pragma once
#include "Renderer.h"
#include "Instancer.h"

#pragma pack(push, 1)
struct InstanceData 
{
	D3DXMATRIX matWorld;
	float numTexture;
	D3DXVECTOR4 color;
	//bool isEnable;
};
#pragma pack(pop)


// ���� ������ ������ ��ü���� �ν��Ͻ�
class InstanceRenderer : public Renderer
{
private:
	forward_list<Instancer*>			m_objectList; // ��ϵ� ��ü��
	forward_list<Instancer*>::iterator  m_curObject;

	ID3D11Buffer*		 m_pBuffers[2];				  // ���� + �ν��Ͻ�
	ID3D11Buffer*		 m_pInstanceBuffer = nullptr; // ������ ����� ����
	vector<InstanceData> m_dataList;				  // ���� ��� ������

	// + ��������Ʈ�� ���� ���ƾߴ� 
	//	-> ��������Ʈ(����Ʈ) ���� ���� ���� ��������Ʈ ī���� �޵���

	// ���� ���� ���ÿ�
	UINT Strides[2];				// ���� ũ��
	UINT Offsets[2];				// ���� ������
public:
	//
private:
	HRESULT Create() noexcept override;
	// ���� ����
	HRESULT CreateInstanceBuffer() noexcept;
	void	UpdateInstanceBuffer(ID3D11DeviceContext* pDContext) noexcept;
	void	UpdateConstBuffer(ID3D11DeviceContext* pDContext) noexcept override;

	Component* cloneAddition() noexcept override;
public:
	void AddInstance(Instancer* pObject)				noexcept;
	void RemoveInstance(Instancer* pObject)			noexcept;

	bool PostRender(ID3D11DeviceContext* pDContext)		noexcept override;
	bool Init()											noexcept override;
	bool Frame(const float& spf, const float& accTime)	noexcept override;
	bool Render(ID3D11DeviceContext* pDContext)			noexcept override;
	bool Release()										noexcept override;
	Component* clone() noexcept override;
protected:
	friend class AseParser;
	friend class MaxImporter;
	//InstanceRenderer() = default;
public:
	InstanceRenderer(const wstring_view& myName, const string_view& vertexShaderName = "VS_Instance", const string_view& pixelShaderName = "PS_Instance") noexcept;
	virtual ~InstanceRenderer() = default;
};