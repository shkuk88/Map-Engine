#pragma once
#include "GameObject.h"

struct AABB
{
	D3DXVECTOR3 Center;
	D3DXVECTOR3 Pos[8];
	
	D3DXVECTOR3 Max;
	D3DXVECTOR3 Min;
};


class MapNode
{
public:
	bool m_isLeaf;

	DWORD m_NodeDepth;

	// �ٿ�� �ڽ�
	AABB				m_Box;
	// ��� �ڳ� ���� �ε��� �� ��ġ
	vector<DWORD>		m_CornerIndex;
	vector<D3DXVECTOR3> m_CornerList;
	vector<MapNode*>	m_ChildList;
	vector<MapNode*>	m_NeighborList;
	vector<GameObject*> m_ObjectList;
	// �߰�,, x,y
	DWORD				m_PositionIndex[2]; 

public:

	MapNode();
	virtual ~MapNode();
};

