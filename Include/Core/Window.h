#pragma once
#include "header.h"

class Window
{
private:
	static MSG		message;					// �޼��� �����̳�
	static RECT		m_winRect;					// ������ ũ�� �Ӽ�
	static RECT		m_realWinRect;				// ��¥ ������ ����
	static RECT	    m_clientRect;				// Ŭ���̾�Ʈ ����
public:
	static HWND				m_hWnd;				// ������ �ڵ�
	static HINSTANCE		m_hInstance;		// ���� ��ü �ڵ�
	static Window*			Instance;			// ���ٿ�
public:
	static void			ResizeWindow(const RECT& rect)	noexcept;
	static RECT&		getClientRect();
	static RECT&		GetWinRect();
	static D3DXVECTOR2	GetWinCenter();
	static D3DXVECTOR2	GetClientCenter();
	static void			UpdateWindowRect()				noexcept;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);							// �޼��� ó�� �ݹ��Լ�
	bool SetWindow(const HINSTANCE& hInstance, const int& nCmdShow, const TCHAR* title = L"SampleWin") noexcept;	// ������ Ȱ��ȭ
	void SetClientRect(const int& x, const int& y, const int& width, const int& height) noexcept;						// ȭ�� ũ�� ����
	bool MessageProcess();					// ������ �޼��� �ؼ�, ó��
	virtual void MsgEvent(const MSG& message) = 0;	// ���콺 �̺�Ʈ �ڵ鸵��
public:
	Window()
	{ Instance = this; }
	virtual ~Window() = default;
};