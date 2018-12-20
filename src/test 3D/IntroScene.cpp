#include "IntroScene.h"



bool IntroScene::Init() noexcept
{
	// ====================================================================================================
#pragma region Basic
	// ������Ʈ ���
	ObjectManager::Get().SetProtoComponent(new RPlane(L"Plane", L"None.png"));
	ObjectManager::Get().SetProtoComponent(new RCube(L"Cube", L"None.png"));
	ObjectManager::Get().SetProtoComponent(new RSphere(20, L"Sphere", L"None.png"));
	ObjectManager::Get().SetProtoComponent(new RLine(L"Line"));

	// �⺻ ��ü ���
	auto pRend = (Renderer*)ObjectManager::Get().TakeComponent(L"Plane");				// ����� ������Ʈ �ҷ���
	GameObject* pObject = new GameObject(L"Plane", { pRend }, EObjType::Object);
	ObjectManager::Get().SetProtoObject(pObject);

	pRend = (Renderer*)ObjectManager::Get().TakeComponent(L"Cube");
	pObject = new GameObject(L"Cube", { pRend }, EObjType::Object);
	ObjectManager::Get().SetProtoObject(pObject);

	pRend = (Renderer*)ObjectManager::Get().TakeComponent(L"Sphere");
	pObject = new GameObject(L"Sphere", { pRend }, EObjType::Object);
	ObjectManager::Get().SetProtoObject(pObject);

	// ���� �߽���
	RLine*		pSelectLines[3];
	pSelectLines[0] = (RLine*)ObjectManager::Get().TakeComponent(L"Line");
	pSelectLines[1] = (RLine*)ObjectManager::Get().TakeComponent(L"Line");
	pSelectLines[2] = (RLine*)ObjectManager::Get().TakeComponent(L"Line");
	pSelectLines[0]->SetLineInfo(DxManager::Get().GetDContext(), Vector3::Left * 1000, Vector3::Right * 1000, Color::Red, true);
	pSelectLines[1]->SetLineInfo(DxManager::Get().GetDContext(), Vector3::Up * 1000, Vector3::Down * 1000, Color::Green, true);
	pSelectLines[2]->SetLineInfo(DxManager::Get().GetDContext(), Vector3::Forward * 1000, Vector3::Backward * 1000, Color::Blue, true);
	ObjectManager::Get().PushObject(new GameObject(L"Center", { pSelectLines[0], pSelectLines[1], pSelectLines[2] }));

	// ����Ʈ
	auto pTrans = new CTransformer(Vector3::Up * 150.0f, Quaternion::Up * PI * 0.35f, Vector3::One);
	pTrans->TransEvent = [](Transform* pParent, Transform* pTrans, const float& spf, const float& accTime) {
		pParent->SetTransform(*pTrans);
		pParent->Translate({ cosf(0.5f * accTime) * 200.0f, 0.0f, sinf(0.5f * accTime) * 200.0f });
		return; spf; accTime; pTrans;
	};
	ObjectManager::Get().Lights.front()->AddComponent({ pTrans });
	// ����Ʈ ������
	auto pShpere = (Renderer*)ObjectManager::GetInstance().TakeComponent(L"Sphere");
	pShpere->SetShaderLayout("VS_PNCT", "PS_PCT");
	pObject = new GameObject(L"Sun", pShpere);
	pObject->SetScale(Vector3::One * 7);
	pObject->SetParent(ObjectManager::Get().Lights.front());

	// ���� ��
	auto mapMap = new HeightMap(L"HeightMap", EComponent::Renderer, L"mounds.jpg");
	auto pHeightMap = new GameObject(L"HeightMap", mapMap, EObjType::Map);
	mapMap->CreateHeightMap(DxManager::GetDContext(), L"HeightMap/HEIGHT_MOUNDS.bmp", 10, 1.0f, 0.8f);
	mapMap->SetNormalMap(L"NormalMap/wall_NM_height.dds");
	mapMap->SetEnviromentMap(L"CubeMap/grassenvmap1024.dds", EEnviType::Fresnel);
	pHeightMap->Translate(Vector3::Down * 100);
	ObjectManager::Get().PushObject(pHeightMap);

	// ��ƼŬ
	auto pParticle = new ParticleSystem(L"ParticleSystem", new Particle(), L"UI/cat.png");
	pParticle->m_maxParticleCount = 9999;
	pParticle->m_spawnInterval = 0.013f;
	pParticle->m_minLifeCycle = 10.0f;
	pParticle->m_maxLifeCycle = 15.0f;
	pParticle->m_minInitPosition = Vector3::One * 200;
	pParticle->m_maxInitPosition = -Vector3::One * 200;
	pParticle->m_minDirection = -Vector3::One;
	pParticle->m_maxDirection = Vector3::One;
	pParticle->m_minMaxMoveSpeed = 2.0;
	pParticle->m_maxMaxMoveSpeed = 20.0;
	pParticle->m_minAccMoveSpeed = 1.0f;
	pParticle->m_maxAccMoveSpeed = 2.0f;
	pParticle->m_minCurMoveSpeed = 1.0f;
	pParticle->m_maxCurMoveSpeed = 10.0f;
	pParticle->m_minDirAngle = Quaternion::Zero;
	pParticle->m_maxDirAngle = Quaternion::Zero;
	pParticle->m_minRotateSpeed = 0.0f;
	pParticle->m_maxRotateSpeed = 0.0f;
	pParticle->m_minColor = { 0.5f, 0.5f, 0.5f, 0.5f };
	pParticle->m_maxColor = Color::White * 2;
	pParticle->m_minGravityPower = 5.0f;
	pParticle->m_maxGravityPower = 10.0f;

	auto pParticleObject = new GameObject(L"ParticleSystem", { pParticle });
	pParticleObject->Translate(Vector3::Up * 200);
	ObjectManager::Get().PushObject(pParticleObject);

	// �븻 ȯ�� ť��
	auto pRenderer = (Renderer*)ObjectManager::Get().TakeComponent(L"Cube");
	pRenderer->SetNormalMap(L"NormalMap/tileADOT3.jpg");
	pRenderer->SetEnviromentMap(L"CubeMap/grassenvmap1024.dds", EEnviType::Refraction);
	pObject = new GameObject(L"NormalEnvi1", { pRenderer, new CTransformer(Vector3::Zero, Quaternion::Right * 2.0f) }, EObjType::Object);
	pObject->Translate(Vector3::Forward * 15.0f);
	pObject->Scaling(Vector3::One * 8);
	ObjectManager::Get().PushObject(pObject);

	// ȯ�� ��ü
	pRenderer = (Renderer*)ObjectManager::Get().TakeComponent(L"Sphere");
	pRenderer->SetEnviromentMap(L"CubeMap/grassenvmap1024.dds", EEnviType::Fresnel);
	pObject = new GameObject(L"Envi3", { pRenderer }, EObjType::Object);
	pObject->Translate(Vector3::Left * 20);
	pObject->SetScale(Vector3::One * 6);
	ObjectManager::Get().PushObject(pObject);
#pragma endregion
	// ====================================================================================================



	return true;
}


// ������
bool IntroScene::Frame() noexcept
{
	DxManager::Get().Frame();
	ObjectManager::Get().Frame(Timer::SPF, Timer::AccumulateTime);
	SoundManager::Get().Frame();
	return true;
}
 
// ����
bool IntroScene::Render() noexcept
{
	DxManager::Get().Render();
	ObjectManager::Get().Render(DxManager::Get().GetDContext());
	SoundManager::Get().Render();
	return true;
}

// ������
bool IntroScene::Release() noexcept
{
	ObjectManager::Get().Release();
	return true;
}


void IntroScene::LoadSound() noexcept
{
	//SoundManager::Get().Load("BGM/Mischievous Masquerade", false, FMOD_LOOP_NORMAL);
	//SoundManager::Get().Load("BGM/Sandbag Mini Game", false, FMOD_LOOP_NORMAL);
	//SoundManager::Get().Load("BGM/Brawl Breaks", false, FMOD_LOOP_NORMAL);
	//SoundManager::Get().Load("BGM/PLAY ROUGH", false, FMOD_LOOP_NORMAL);
	//SoundManager::Get().Load("BGM/Ending", false, FMOD_LOOP_NORMAL);
	//SoundManager::Get().setBGM("BGM/PLAY ROUGH");
	//
	//SoundManager::Get().Load("bash1");
}