#pragma once
#ifdef _DEBUG
#pragma comment( lib, "_CoreLib D3D_d.lib")
#else
#pragma comment( lib, "_CoreLib D3D.lib")
#endif // _DEBUG

#include "CoreDX.h"
///
#include "SkySphere.h"
#include "MaxImporter.h"
#include "ParticleSystem.h"
#include "Raycast.h"
#include "Light.h"
#include "PlaneUI.h"
#include "RLine.h"
#include "RSphere.h"
#include "RCube.h"
//#include "HeightMap.h"
#include "CTransformer.h"

//map
#include "XQuadTreeIndex.h"
#include "XCamera.h"
#include "XMapImporter.h"
#include "XObjectManager.h" 

// =====================================================================
// ī�޶� ����(Shift ������)
// {
//		�̵�		: ���콺 ��Ŭ��, ��, WASD, QE
//		ȸ��		: ���콺 ��Ŭ��, ����Ű
//		����		: R
//		FOV ���� : Z, X, C
// }
// 
// F1 : ���̾� ������
// F2 : �븻�� Ȯ��
// F3 : PostEffect Off
// F4 : PostEffect On
//
// �����е� 1,2,3 : �� ��ȯ(IntroScene �� ��ġ�Ȱ� ����)
//
// =====================================================================
// Context, Device �� DirectX�� ���õȰ� ��κ� DxManager�� �ֽ��ϴ�.
// ī�޶� �ʿ��ϸ� ObjectManager::Get().Cameras[ECamera::Main]->m_mat~ ������ ������ �� �ֽ��ϴ�.
//
// GameObject�� ��� �����ð� ���� Ŭ�������� GameObject::Frame(), GameObject::Render() �� �����ø� 
// Transform�� �ִ� position, rotation, scale ���� ���� ����� ���ŵ˴ϴ�.
// SetParent, CutParent�� �θ� ���� �� ���� �մϴ�.
//
// =====================================================================
// MainClass���� Core�� ��ӹް� ��ü ���� �����մϴ�.
// �� ������ MainClass�� ��ӹ޾� �����ϱ� ������ �߽��ϴ�.
// �� �� ���� �ش� ���� �ʿ��� ��ü�� �����ϰ� ����ϴ� ������ �մϴ�.
// �� ���� MainClass���� static���� ����� ������ ������ �� �ֽ��ϴ�.(static �ƴϸ� ������)
//
// =====================================================================

enum class ESceneName : char {
	Intro = 0,
	Main,
	Ending,
};

// ��ü ���� ������ �帧�� ����
class MainClass : public Core 
{
public:
	static GameObject* m_pSkyBox;

	static map<ESceneName, MainClass*> m_SceneList;
	static MainClass* m_curScene;

	// map
	XCamera			m_Camera;
	XMap*			m_pMap;
	XQuadTreeIndex*	m_pMapTree;
	XMapImporter	m_Importer;
public:
	// �� ����
	void SetScene(const ESceneName& sceneName, const bool& useRelease = true) noexcept;

	virtual bool Init()		noexcept override;
	virtual bool Frame()	noexcept override;
	virtual bool Render()	noexcept override;
	virtual bool Release()	noexcept override;
public:
	MainClass() = default;
	~MainClass() = default;
};