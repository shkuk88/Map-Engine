#pragma once
#include "Component.h"
#include "Physics.h"

enum class ECollider : char {
	AABB = 0, OBB, Sphere,
};


class ColliderAABB;
class ColliderOBB;

class Collider : public Component, public Physics
{
protected:
	float m_radius;								// ������
	
	forward_list<Collider*> m_CollisionList;	// üũ�� �浹ü
	forward_list<Collider*> m_IgnoreList;		// �浹 ���� ���
public:
	void (*CollisionEvent)(Collider*, Collider*) = nullptr;
	ECollider	m_eCollider;

	D3DXVECTOR3 m_pivot = Vector3::Zero;		// �θ� ��� �ǹ�
	
	float m_mapHeight = -9999.0f;				// �� ����
private:
	bool CollisionAllCheck(const float& spf)						  noexcept;
protected:												  
	virtual bool CollisionCheck(Collider* pCollider)				  noexcept;
public:
	bool SphereToSphere(Collider* pSphereA, Collider* pSphereB)	const noexcept;
	bool SphereToAABB(Collider* pSphere, ColliderAABB* pAABB)	const noexcept;
	bool SphereToOBB(Collider* pSphere, ColliderOBB* pOBB)		const noexcept;
	bool AABBToAABB(ColliderAABB* ApAABB, ColliderAABB* BpAABB)	const noexcept;
	bool AABBToOBB(ColliderAABB* pAABB, ColliderOBB* pOBB)		const noexcept;
	bool OBBToOBB(ColliderOBB* ApOBB, ColliderOBB* BpOBB)		const noexcept;
	///
	void AddIgnoreList(Collider* pCollider)			  noexcept;
	void ClearIgnoreList()							  noexcept;
	void ClearCollisionList()						  noexcept;
	// ������
	void  SetRadius(const float& radius)			  noexcept;
	const float GetRadius()						const noexcept;
	const float GetWorldRadius()				const noexcept;
	const D3DXVECTOR3 GetCenter()				const noexcept;


	//void Update()												noexcept override;
	virtual bool Init()											noexcept override;
	virtual bool Frame(const float& spf, const float& accTime)	noexcept override;
	virtual bool Render(ID3D11DeviceContext* pDContext)			noexcept override;
	virtual bool Release()										noexcept override;
	Component* clone()											noexcept override;
protected:
	Collider();
public:
	Collider(const float& radius);
	virtual ~Collider();
};