#include "GameScene.h"



bool GameScene::Init() noexcept
{

	
	return true;
}


// ������
bool GameScene::Frame() noexcept
{
	DxManager::Get().Frame();
	ObjectManager::Get().Frame(Timer::SPF, Timer::AccumulateTime);
	SoundManager::Get().Frame();
	return true;
}

// ����
bool GameScene::Render() noexcept
{
	DxManager::Get().Render();
	ObjectManager::Get().Render(DxManager::Get().GetDContext());
	SoundManager::Get().Render();
	return true;
}

// ������
bool GameScene::Release() noexcept
{
	ObjectManager::Get().Release();
	return true;
}