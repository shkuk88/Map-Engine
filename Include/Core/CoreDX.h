#pragma once
#include "Timer.h"
#include "ObjectManager.h"
#include "WriteManager.h"
#include "SoundManager.h"
//#include "../../include/server/ClientServer.h"


class Core : public Window, public IBasis
{
private:
	static Timer   m_Timer;
	Input&		   m_Input = Input::GetInstance();
	SoundManager&  m_SoundManager  = SoundManager::GetInstance();	// ���� ����
	DxManager&	   m_DxManager	   = DxManager::GetInstance();		// DirectX ����
	ObjectManager& m_ObjectManager = ObjectManager::GetInstance();	// ������Ʈ ����
	WriteManager&  m_WriteManager  = WriteManager::GetInstance();	// ���� ��� ����
	//ClientServer&  m_ClientServer = ClientServer::GetInstance();	// Ŭ��-����
public:
	static bool isPlaying;		// ���α׷� ���� �÷���
public:
	virtual bool GameRun()		noexcept final;
private:
	virtual bool GameInit()		noexcept final;
	virtual bool GameFrame()	noexcept final;
	virtual bool GameRender()	noexcept final;
	virtual bool GameRelease()	noexcept final;
protected:
	virtual void MsgEvent(const MSG& message) noexcept override;
	virtual bool Init()			noexcept = 0;
	virtual bool Frame()		noexcept = 0;
	virtual bool Render()		noexcept = 0;
	virtual bool Release()		noexcept = 0;

	Core() = default;
	virtual ~Core() = default;
};