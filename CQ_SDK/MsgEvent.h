#pragma once

#include "BasicEvent.h"
#include "MsgSend.h"

#include <string>

inline
namespace CQ {
	//��Ϣ�¼�����
	struct MsgEvent :public BasicEvent
	{
		//������
		int subType;
		//��ϢID
		int msgId;
		//��ԴQQ
		long long fromQQ;
		//��Ϣ
		std::string message;
		char* messageRAW;
		//����
		//Font font;
		int font;

		MsgEvent(int subType, int msgId, long long fromQQ, const char* message, int font);

		//��ʵ�û�
		bool isUser() const;
		//�Ƿ���ϵͳ�û�
		bool isSystem() const;

		virtual int sendMsg(const char*) const = 0;
		virtual int sendMsg(std::string) const = 0;
		virtual MsgSend sendMsg() const = 0;
	};
}