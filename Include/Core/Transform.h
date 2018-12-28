#pragma once
#include "header.h"


// SRT Ŭ����
class Transform
{
protected:
	D3DXVECTOR3		m_position = { 0,0,0 };			// �߽� ��ǥ
	D3DXQUATERNION	m_rotation = { 0,0,0,0 };		// ȸ��
	D3DXVECTOR3		m_scale    = { 1,1,1 };			// ũ��

	D3DXVECTOR3		m_Look = { 0.0f, 0.0f, 1.0f };	// �ٶ� ��ġ
	D3DXVECTOR3		m_Side = { 1.0f, 0.0f, 0.0f };	// ���̵� ����
	D3DXVECTOR3		m_Up   = { 0.0f, 1.0f, 0.0f };	// ���� ����
public:
	// ����
	void Transformation(const Transform& transform)					 noexcept;
	void Translate(const D3DXVECTOR3& position)						 noexcept;
	void Translate(const float& x, const float& y, const float& z)	 noexcept;
	void Translate(const float& x, const float& y)					 noexcept;
	void Rotate(const D3DXQUATERNION& rotation)						 noexcept;
	void Rotate(const D3DXVECTOR3& rotation)						 noexcept;
	void Rotate(const float& x, const float& y, const float& z)		 noexcept;
	void Rotate(const float& x, const float& y)						 noexcept;
	void Scaling(const D3DXVECTOR3& scale)							 noexcept;
	void Scaling(const float& x, const float& y, const float& z)	 noexcept;
	// Setter
	void SetFocus(const D3DXVECTOR3& target)						 noexcept;
	void SetTransform(const Transform& transform)					 noexcept;
	void SetPosition(const D3DXVECTOR3& position)					 noexcept;
	void SetPosition(const float& x, const float& y, const float& z) noexcept;
	void SetPositionX(const float& x)								 noexcept;
	void SetPositionY(const float& y)								 noexcept;
	void SetPositionZ(const float& z)								 noexcept;

	void SetRotation(const D3DXQUATERNION& rotation)				 noexcept;
	void SetRotation(const float& x, const float& y, const float& z) noexcept;
	void SetRotationX(const float& x)								 noexcept;
	void SetRotationY(const float& y)								 noexcept;
	void SetRotationZ(const float& z)								 noexcept;

	void SetScale(const D3DXVECTOR3& scale)							 noexcept;
	void SetScale(const float& x, const float& y, const float& z)	 noexcept;
	void SetScaleX(const float& x)									 noexcept;
	void SetScaleY(const float& y)									 noexcept;
	void SetScaleZ(const float& z)									 noexcept;
	// Getter
	const Transform&		GetTransform()					   const noexcept;
	const D3DXVECTOR3&		GetPosition()					   const noexcept;
	const D3DXQUATERNION&	GetRotation()					   const noexcept;
	const D3DXVECTOR3&		GetScale()						   const noexcept;
	float					GetScaleAverage()				   const noexcept;
	
	const D3DXVECTOR3&	GetForward()						   const noexcept;
	const D3DXVECTOR3	GetBackward()						   const noexcept;
	const D3DXVECTOR3&	GetRight()							   const noexcept;
	const D3DXVECTOR3	GetLeft()							   const noexcept;
	const D3DXVECTOR3&	GetUp()								   const noexcept;
	const D3DXVECTOR3	GetDown()							   const noexcept;
public:
	Transform() = default;
	Transform(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const D3DXVECTOR3& scale) noexcept;
	//Transform(Transform&)  = default;
	//Transform(Transform&&) = default;
	//Transform& operator = (const Transform&) = default;
	//Transform& operator = (Transform&&) = default;
	virtual ~Transform() = default;
};