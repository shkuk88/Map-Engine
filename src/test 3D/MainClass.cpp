#include "MainClass.h"
#include "IntroScene.h"
#include "GameScene.h"
#include "EndingScene.h"


MainClass*				    MainClass::m_curScene	= nullptr;
map<ESceneName, MainClass*> MainClass::m_SceneList;
GameObject*  MainClass::m_pSkyBox		= nullptr;



bool MainClass::Init() noexcept
{
	// map
	I_Input.Set(m_hWnd,m_hInstance);
	I_Input.Init();
	m_Camera.Init();
	m_Importer.Import();
	m_pMap = new XMap;
	m_pMap->Create(DxManager::Get().GetDevice(), DxManager::Get().GetDContext(), &m_Importer,	 _T("../../Data/Map/Shader/MapShader_Specular.hlsl"), _T("../../Data/Map/Shader/MapShader_Color_Specular.hlsl"), "VS", "PS");
	m_pMapTree = new XQuadTreeIndex;
	m_pMapTree->Build(m_pMap);


	// 폰트 설정
	WriteManager::Get().SetText({ 0, 0 }, L"", D2D1::ColorF::Black, 50, L"Yu Gothic");
	//WriteManager::Get().m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
//	WriteManager::Get().m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	// 스카이 박스
	m_pSkyBox = new GameObject(L"SkyBox", { new SkySphere(20, L"SkySphere", L"CubeMap/grassenvmap1024.dds"), new CTransformer(Vector3::Zero, Quaternion::Right * 0.05f, Vector3::Zero) }, EObjType::Dummy);
	m_pSkyBox->SetScale(Vector3::One * 100);
	m_pSkyBox->isGlobal(true);

	// 씬 설정
	m_curScene = m_SceneList[ESceneName::Intro]	= new IntroScene();
	m_SceneList[ESceneName::Main]	= new GameScene();
	m_SceneList[ESceneName::Ending] = new EndingScene();
	///
	SetScene(ESceneName::Intro, false);
	return true;
}


bool MainClass::Frame() noexcept
{
	//map
	I_Input.Frame();
	m_Camera.Frame(Timer::SPF, Timer::AccumulateTime);
	m_pMap->Frame(Timer::SPF, Timer::AccumulateTime);
	m_pMapTree->Frame();
	I_Object.Frame(Timer::SPF, Timer::AccumulateTime);

	//m_pSkyBox->Frame(Timer::SPF, Timer::AccumulateTime);
	//m_curScene->Frame();

	//// 패드 1, 2, 3 키 누르면 씬 전환
	//if (Input::GetKeyState(VK_NUMPAD1) == EKeyState::DOWN)
	//	SetScene(ESceneName::Intro);
	//if (Input::GetKeyState(VK_NUMPAD2) == EKeyState::DOWN)
	//	SetScene(ESceneName::Main);
	//if (Input::GetKeyState(VK_NUMPAD3) == EKeyState::DOWN)
	//	SetScene(ESceneName::Ending);
	
	 //BGM 변경
	//if (Input::Get().GetKeyState(VK_F1) == EKeyState::DOWN)
	//	SoundManager::Get().setBGM("BGM/Mischievous Masquerade");
	//if (Input::Get().GetKeyState(VK_F2) == EKeyState::DOWN)
	//	SoundManager::Get().setBGM("BGM/Sandbag Mini Game");
	//if (Input::Get().GetKeyState(VK_F3) == EKeyState::DOWN)
	//	SoundManager::Get().setBGM("BGM/Brawl Breaks");
	//if (Input::Get().GetKeyState(VK_F4) == EKeyState::DOWN)
	//	SoundManager::Get().setBGM("BGM/PLAY ROUGH");
	return true;
}

bool MainClass::Render() noexcept
{
	// map
	m_pMap->SetMatrix(NULL, &m_Camera.GetViewMatrix(), &m_Camera.GetProjMatrix());
	m_pMap->Render(DxManager::Get().GetDContext());
	I_Object.SetMatrix(&m_Camera.GetViewMatrix(), &m_Camera.GetProjMatrix());
	I_Object.Render(DxManager::Get().GetDContext());
	if (I_Input.KeyCheck(DIK_1) == KEY_PUSH)
	{
		I_Object.ViewColliderSwitch();
	}
	//m_pSkyBox->Render(DxManager::Get().GetDContext());
	//m_curScene->Render();
	//WriteManager::Get().SetFontSize(50);
	//WriteManager::Get().DrawTextW({ getClientRect().right * 0.05f , getClientRect().bottom * 0.03f, 400, 400 }, L"aaa앙앙~ 테스트 Test ~ 123,,");
	return true;
}

bool MainClass::Release() noexcept
{
	// map
	if (m_pMap)		m_pMap->Release();
	if (m_pMapTree) m_pMapTree->Release();
	I_Object.Release();

	m_curScene->Release();
	return true;
}

// 씬 전환
void MainClass::SetScene(const ESceneName& sceneName, const bool& useRelease) noexcept
{
	if(useRelease)
		m_curScene->Release();
	m_curScene = m_SceneList[sceneName];
	// 쓰레드 실행
	std::thread initer(&MainClass::Init, m_SceneList[sceneName]);
	initer.detach();
	//// 쓰레드 대기
	//if (initer.joinable())
	//	initer.join();
}




//					윈도우 핸들,         호출한 윈도우 핸들
//  호출형식(언어)  ?                    보여줄 속성값
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPWSTR	  lpCmdLine, int   nCmdShow)
{
	// 윈도우 생성
	static MainClass mainWindow;
	mainWindow.SetClientRect(250, 250, 1024, 700);

	// 윈도우 설정
	if (mainWindow.SetWindow(hInstance, nCmdShow, L"MyGame"))
	{
		// 윈도우 가동
		mainWindow.GameRun();	
	}
	
	return 0;
	lpCmdLine;	hPrevInstance;
}