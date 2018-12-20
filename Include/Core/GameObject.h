#pragma once
//#include "header.h"
//#include "IDxBasis.h"
#include "Transform.h"
#include "Component.h"


enum class EObjType : char {
	Dummy,
	Image,
	//Collider,
	UI,
	Map,
	Object,
	Camera,
	Light,
};


// ������Ʈ�� ��� ������ �⺻ Ŭ����
class GameObject : public Transform, public IDxBasis
{
protected:
	GameObject*						 m_pParent = nullptr;	 // �θ� ������
	forward_list<GameObject*>		 m_childList;			 // �ڽ� ����Ʈ
	map<EComponent, forward_list<Component*> > m_components; // ������Ʈ ����Ʈ

	D3DXMATRIX m_matLocal;			// ���� ���(��� ���夾)
	D3DXMATRIX m_matScale;			// Scale ���
	D3DXMATRIX m_matRotation;		// Rotation ���
	
	bool  m_isEnable	= true;		// Ȱ��ȭ ����
	bool  m_isGlobal	= false;	// ObjectManager ������� ���� ����
	bool  m_isStatic	= false;	// SRT ���� ����
	bool  m_isBillBoard = false;	// ������ ��� ���� ����
	bool  m_isNotDelete = false;	// ���� ���� ����(����)
public:
	wstring	 m_myName;								// ��ü �̸�
	EObjType m_objType = EObjType::Dummy;			// ��ü Ÿ��
protected:
	virtual HRESULT Create()	noexcept { return S_OK; } ; // ����ȣȯ��
	virtual void UpdateMatrix() noexcept;	// ��� ����
public:
	// ������Ʈ �߰�, ����, �˻�
	void AddComponent(Component* pComponent) noexcept;
	void AddComponent(const initializer_list<Component*>& components) noexcept;
	void DeleteComponent(Component* pComponent) noexcept;
	forward_list<Component*>* GetComponentList(const EComponent& eCompType) noexcept;
	map<EComponent, forward_list<Component*> >& GetComponentList() noexcept;
	// �θ� ����
	virtual void SetParent(GameObject* pParent);
	GameObject*  GetParent() const;
	void		 CutParent();
	forward_list<GameObject*>* GetChildList();
	// �θ���� * �ڽķ���
	void SetWorldPosition(const D3DXVECTOR3& position)	  noexcept;
	void SetWorldRotation(const D3DXQUATERNION& rotation) noexcept;
	void SetWorldScale(const D3DXVECTOR3& scale)		  noexcept;
	D3DXVECTOR3	   GetWorldPosition()	const noexcept;
	D3DXQUATERNION GetWorldRotation()	const noexcept;
	D3DXVECTOR3	   GetWorldScale()		const noexcept;
	// ��� ����, ��ȯ
	void  SetWorldMatrix(const D3DXMATRIX& matWorld)  noexcept;
	const D3DXMATRIX& GetWorldMatrix()			const noexcept;
	const D3DXMATRIX& GetScaleMatrix()			const noexcept;
	const D3DXMATRIX& GetRotationMatrix()		const noexcept;

	bool isEnable()		noexcept;
	void isEnable(const bool& isEnable, const bool& putDisablePool = false) noexcept;
	bool isGlobal()		noexcept;
	void isGlobal(const bool& isGlobal) noexcept;
	bool isStatic()		noexcept;
	void isStatic(const bool& isStatic) noexcept;
	bool isBillBoard()	noexcept;
	void isBillBoard(const bool& isBillBoard) noexcept;
	bool isNotDelete()	noexcept;
	void isNotDelete(const bool& isNotDelete) noexcept;

	virtual bool Init()											noexcept override;
	virtual bool Frame(const float& spf, const float& accTime)	noexcept override;
	virtual bool Render(ID3D11DeviceContext* pDContext)			noexcept override;
	virtual bool Release()										noexcept override;
	virtual GameObject* clone()									noexcept;		// �ڱ� ��ü ���� ��ȯ
private:
	GameObject* cloneChild(GameObject* pObject)					noexcept;		// �ڽ� ������
protected:
	friend class AseParser;
	friend class MaxImporter;
	friend class Dialog_Hierarchy;
	friend class CAnimation;

	GameObject() = default;
public:
	GameObject(const wstring_view& myName, const EObjType& eType = EObjType::Dummy);
	GameObject(const wstring_view& myName, const std::initializer_list<Component*>& components, const EObjType& eType = EObjType::Dummy);
	GameObject(const wstring_view& myName, Component* pComponent, const EObjType& eType = EObjType::Dummy);
	virtual ~GameObject() noexcept = default;
};