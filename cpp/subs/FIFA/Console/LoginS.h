#pragma once
/*
@author zhp
@date 2014/4/9 13:45
@purpose for login
*/
#include "Net/server.h"
#include "Common/UsefulClass.h"
#include <Net/JsonCall.h>
#include "../Login/P_LoginMsg.h"

class LoginServer : public Server, public Singleton<LoginServer, Singleton_Instance>{
public:
	LoginServer();

private:
	bool OnConnected( IoConnectBase* connect );
	void OnDisconnect( IoConnectBase* connect );
	virtual Session* CreateSession();
};

class LoginS;
class LoginOperS : public JsonEchoBase{
public:
	LoginOperS( LoginS& login_s );
	//帐号或密码输入错误
	bool AcOrPwdErr();
	//帐号被冻结
	bool AcFreeze();
	//Check login ver
	void OnCheckLoginVersion( bool res );
	//长时间未响应
	void LoginUnRespond();

protected:
	virtual bool OnThisMemCall( const stThisCallHelper& helper );

private:
	LoginS&				login_s_;
};

class LoginS : public Session{
public:
	LoginS( Server& server );
	//get json echo
	JsonEcho& GetJsonEcho();

protected:
	//关联pid
	bool OnBindLoginPid( P_Exec_BindLoginPid& msg );

private:
	virtual bool OnUserMsg( P_MsgNT msg_num, void* param, size_t param_size );
	bool OnConnected( IoConnectBase* connect );

private:
	JsonEcho				json_echo_;
	LoginOperS				login_oper_;
};