/*


#include <CQEVE.h>
#include <CQLogger.h>
#include <CQAPI_EX.h>
#include "APPINFO.h"

#include <string>
using namespace std;
using namespace CQ;

//�����static,��ʾ���loggerֻ�б�cpp��Ч
static Logger logger("��Q����Ӧ��");


EVE_Enable(Enable2)
{


	logger.Info("Ӧ�ñ�����");


	return 0;
}

EVE_Disable(Disable2)
{
	logger.Info("Ӧ�ñ�ͣ��");

	return 0;
}

MUST_AppInfo_RETURN(CQAPPID)




#include <CQEVE_RequestAddGroup.h>
#include <CQMsgCode.h>

#include <string>

using namespace std;
using namespace CQ;


EVE_Request_AddGroup_EX(AddGroup) {
	if (eve.subType != 1)return;//���Ǳ���������Ⱥ������

	MsgCode mc(eve.msg);//��������

	if (!mc.find("at"))return;//�����Ƿ��п�q��:[CQ:at,qq=xxxx]

	string qq = mc.get("qq");//��ȡqq
}


#include <CQEVE_GroupMsg.h>
#include <CQcode.h>

#include <string>

using namespace std;
using namespace CQ;

EVE_GroupMsg_EX(Speak) {
	static string msgs("Speak:");

	if (eve.message.compare(0, msgs.size(), msgs)) return;

	auto txt = eve.message.substr(msgs.size());

	//eve.sendMsg() << code::record("out.wav", txt) << send;
	//record �ĵ�һ������ָʾ���������ɵ��ĸ��ļ�(����ڿ�Q������Ŀ¼)
	//record �ĵڶ�������ָʾ��ָ��������������
	//����һЩ����������,�������а汾��window��֧�ִ���Ŀ
}


#include <CQEVE_GroupMsg.h>
#include <CQEVE_PrivateMsg.h>
#include <CQMsgSend.h>
#include <CQAPI_EX.h>
#include <INItool.h>

#include <string>
using namespace std;
using namespace CQ;

int  Thesaurus(�ı��� msg, MsgSend send) {
	return 0;
}

EVE_Enable(ThesaurusE) {
	auto file = string(getAppDirectory()) + "Thesaurus.ini";
	return 0;
}

EVE_PrivateMsg(ThesaurusP) {
	return Thesaurus(msg, MsgSend(fromQQ, msgtype::����));
}
EVE_GroupMsg(ThesaurusG) {
	return Thesaurus(msg, MsgSend(fromGroup, msgtype::Ⱥ));
}

#include <CQEVE_PrivateMsg.h>
#include <CQcode.h>
#include <CQLogger.h>
#include <CQAPI_EX.h>

#include <string>
using namespace std;
using namespace CQ;

//�����static,��ʾ���loggerֻ�б�cpp��Ч
static Logger logger("SendMsg");

EVE_PrivateMsg_EX(SendMsg) {
	logger.Debug() << DEBUGINFO << eve.message;

	// ���һ�����¼��йص���Ϣ����
	// �����Ϣ�����Ѿ��Զ������¼���Ӧ��Ⱥ���ߺ���
	auto msg = eve.sendMsg();
	// ���������ض����˷�����Ϣ,�������123456
	// ������ֱ�ӵ���API
	//sendPrivateMsg(123456, "���");
	// ����ʹ��MsgSend
	//MsgSend P123456(123456, msgtype::����);
	//P123456 << "���" << send;

	auto message = eve.message;

	// ��ͨ�ķ���һ����Ϣ
	extern string a;
	if (!message.compare("1"))
		eve.sendMsg(a);

	// ʹ��<<��������Ϣ
	if (!message.compare("CQ:msg2"))
		//һ��Ҫĩβ����<<send�Żᷢ�ͳ�ȥ
		msg << "�յ���Ϣ��!" << send;

	// ǿ�����Ϣ���ͷ�ʽ
	if (!message.compare("CQ:msg3"))
		// ���������ɶ���������
		msg
		<< "������Ϊ:" << eve.fromQQ
		<< ",��ϢΪ:" << eve.message
		<< send;

	if (!message.compare("CQ:image")) {
		logger.Debug() << "rawģʽ:" << msg.isRAW() << send;
		// ����һ��ͼƬ
		msg << code::image("123.png") << send;
	}

	if (!message.compare("CQ:face"))
		//����һ������
		msg << code::face(face::����) << send;

	if (!message.compare("CQ:raw"))
		msg
		// RAW ��ʾ�������Ϣ����ԭ������
		// �����ǽ�����CQ��,���������й���,���緢��ͼƬ
		<< RAW << code::at(eve.fromQQ)
		// CODE ��ʾ�������Ϣ��������ΪCQ��
		// Ĭ�Ͻ���
		<< CODE << code::face(face::����)
		<< send;

	if (!message.compare("CQ:effect"))
		// ����һ��ħ������,��CQ����뵥��һ����Ϣ
		eve.sendMsg(code::effect("art", 2003, "ħ����Ϣ"));
}
*/