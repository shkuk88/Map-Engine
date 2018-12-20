#pragma once
#include "header.h"

class Renderer;

class Raycast
{
private:
	static D3DXVECTOR3 m_start;
public:
	static D3DXVECTOR3 m_ray;
	static D3DXVECTOR3 HitPoint;
public:
	// start���� direction * range�� �߻�
	static bool Raycasting(const Renderer* pTarget, const D3DXVECTOR3& start, const D3DXVECTOR3& direction, const float& range, D3DXVECTOR3* pHitPoint = nullptr) noexcept;
	// ������ �������� �߻�
	static bool Raycasting(const Renderer* pTarget, D3DXVECTOR3* pHitPoint = nullptr, const D3DXMATRIX* pWorldMatrix = nullptr)	noexcept;
	// ���� ����
	static void SetRaycast(const D3DXVECTOR3& start, const D3DXVECTOR3& direction, const float& range)	noexcept;
	// ȭ�� Ŀ�� ��ġ�� ���� ����
	static void SetMousePick(const POINT& cursor, const float& range) noexcept;
	//void DrawRay();
public:
	Raycast();
	virtual ~Raycast() = default;
};

