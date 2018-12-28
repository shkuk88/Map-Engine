#pragma once
#include "IBasis.h"
#include "Window.h"
#include <mutex>

class Timer : public IBasis
{
private:
	static int	FPS;				// �ʴ� ������

	int		m_FrameCnt;				// ������ ���³�
	int		m_DirFrame;				// ��ǥ ������
	float	m_kDirTick;				// ��ǥ ������ ����
	float	m_ElapseTime;			// ���� �����Ӻ��� ��� �ð�
	float	m_GameSpeed;			// ���� �ӵ�
	
	LARGE_INTEGER	m_Frequency;	// �ʴ� ���ļ�
	LARGE_INTEGER	m_CurrentTick;	// ���� ƽ
	LARGE_INTEGER   m_BeforeTick;	// ���� ������ ƽ

	wostringstream  m_InfoStream;
public:
	static Timer*	Instance;
	static float	SPF;			// ���� �����Ӵ� �ð�
	static float	AccumulateTime;	// �� ���� �ð�
	static bool		isPlaying;		// ������?

	std::mutex		m_mutex;
	std::condition_variable m_FrameEvent;		// ������ �̺�Ʈ ���, �˸� �߻��� ������� ������ ����
	std::condition_variable m_RenderEvent;
public:
	void ResetSPF()			noexcept;
	void setDirFrame(const int& dirFrame);
	void setGameSpeed(const float& speedRate);

	virtual bool Init()		noexcept override;
	virtual bool Frame()	noexcept override;
	virtual bool Render()	noexcept override;
	virtual bool Release()	noexcept override;

	Timer();
	virtual ~Timer();
};