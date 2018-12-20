#include "EndingScene.h"



bool EndingScene::Init() noexcept
{



	return true;
}


// ������
bool EndingScene::Frame() noexcept
{
	DxManager::Get().Frame();
	ObjectManager::Get().Frame(Timer::SPF, Timer::AccumulateTime);
	SoundManager::Get().Frame();
	return true;
}

// ����
bool EndingScene::Render() noexcept
{
	DxManager::Get().Render();
	ObjectManager::Get().Render(DxManager::Get().GetDContext());
	SoundManager::Get().Render();
	return true;
}

// ������
bool EndingScene::Release() noexcept
{
	// ������
	ObjectManager::Get().Release();
	//DxManager::Get().Release();
	//SoundManager::Get().Release();
	return true;
}