//#pragma once
//#include "../../include/server/ServerBasic.h"
//#include "../../include/server/MyProtocol.h"
//
//// + Sender���� ������ ��Ŷ ������ Recver���� �޾Ƽ� ��ŶǮ�� ������, Worker���� ó��
//constexpr WORD MaxBufferSize = 10000;
//
//class DxClientRecv : public ServerBasic
//{
//protected:
//	UPACKET*  m_pUPacket = nullptr;		// ���� Ȯ�ο� ������
//	UPACKET*  m_pPacket = nullptr;		// ������ ��Ŷ
//	int		  m_popPos = 0;		// = ���� ���涧 ����
//	char	  m_packetBuffer[MaxBufferSize] = { 0, };
//
//	//WSABUF	  m_WSABuffer = { MaxBufferSize, m_packetBuffer };
//	int		  m_pushPos = 0;			// ���� ������ ��
//	//WORD & m_MsgType;
//protected:
//	bool Run() override;
//	void PushData(const int& size) noexcept;
//public:
//	//DxClientRecv(WORD& msgType) : m_MsgType(msgType) {};
//	DxClientRecv() = default;
//	virtual ~DxClientRecv() = default;
//};
//
//class DxClientSend : public ServerBasic
//{
//protected:
//	//WORD & m_MsgType;
//	bool Run() override;
//public:
//	//DxClientSend(WORD& msgType) : m_MsgType(msgType) {};
//	bool Start(const USHORT& portNum, const string_view& address, const bool& isClient = false) override;
//	DxClientSend() = default;
//	virtual ~DxClientSend() = default;
//};