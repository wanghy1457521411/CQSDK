#include "GroupMsgEvent.h"

#include "API.h"


CQ::GroupMsgEvent::GroupMsgEvent(int subType, int msgId, long long fromGroup, long long fromQQ, const char * fromAnonymous, const char * msg, int font)
	:MsgEvent(subType, msgId, fromQQ, msg, font), fromGroup(fromGroup), fromAnonymousToken(fromAnonymous), fromAnonymousInfo()
{}

CQ::GroupMsgEvent::~GroupMsgEvent()
{
	if (fromAnonymousInfo != nullptr)
		delete fromAnonymousInfo;
}

bool CQ::GroupMsgEvent::isAnonymous() const { return fromQQ == 80000000; }

AnonymousInfo & CQ::GroupMsgEvent::getFromAnonymousInfo() //throw(std::exception_ptr)
{
	if (isAnonymous())
		return
		fromAnonymousInfo != nullptr
		? *fromAnonymousInfo
		: *(fromAnonymousInfo = new AnonymousInfo(fromAnonymousToken));
	else
		throw std::exception_ptr();
}

bool CQ::GroupMsgEvent::setGroupKick(bool refusedAddAgain)
{
	return !CQ::setGroupKick(fromGroup, fromQQ, refusedAddAgain);
}

bool CQ::GroupMsgEvent::setGroupBan(long long banTime)
{
	if (isAnonymous()) {
		return !CQ::setGroupAnonymousBan(fromGroup, fromAnonymousToken, banTime);
	}
	else {
		return !CQ::setGroupBan(fromGroup, fromQQ, banTime);
	}
}

bool CQ::GroupMsgEvent::setGroupAdmin(bool isAdmin)
{
	return !CQ::setGroupAdmin(fromGroup, fromQQ, isAdmin);
}

bool CQ::GroupMsgEvent::setGroupSpecialTitle(std::string 专属头衔, long long 过期时间)
{
	return !CQ::setGroupSpecialTitle(fromGroup, fromQQ, 专属头衔, 过期时间);
}

bool CQ::GroupMsgEvent::setGroupWholeBan(bool 开启禁言)
{
	return CQ::setGroupWholeBan(fromGroup, 开启禁言);
}

bool CQ::GroupMsgEvent::setGroupAnonymous(bool 开启匿名)
{
	return CQ::setGroupAnonymous(fromGroup, 开启匿名);
}

bool CQ::GroupMsgEvent::setGroupCard(std::string 新名片_昵称)
{
	return CQ::setGroupCard(fromGroup, fromQQ, 新名片_昵称);
}

bool CQ::GroupMsgEvent::setGroupLeave(bool 是否解散)
{
	return CQ::setGroupLeave(fromGroup, 是否解散);
}

GroupMemberInfo CQ::GroupMsgEvent::getGroupMemberInfo(bool 不使用缓存)
{
	return CQ::getGroupMemberInfo(fromGroup, fromQQ, 不使用缓存);
}

std::vector<GroupMemberInfo> CQ::GroupMsgEvent::getGroupMemberList()
{
	return CQ::getGroupMemberList(fromGroup);
}
int CQ::GroupMsgEvent::sendMsg(const char * msg) const { return sendGroupMsg(fromGroup, msg); }
int CQ::GroupMsgEvent::sendMsg(std::string msg) const { return sendGroupMsg(fromGroup, msg); }
MsgSend CQ::GroupMsgEvent::sendMsg()const { return MsgSend(fromGroup, msgtype::群); }