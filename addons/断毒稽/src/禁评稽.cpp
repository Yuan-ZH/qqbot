#include <CQEVE_GroupMsg.h>
#include <CQcode.h>
#include <CQLogger.h>
#include <CQAPI_EX.h>
#include <windows.h>
#include <string>
#include<cstdlib>
#include <list>
#include<vector>
#include<future>
#include<map>
#include<queue>
#include<fstream>
#include<sstream>
#include<random>
#include <CQEVE.h>
#include "APPINFO.h"
#include <CQEVE_RequestAddGroup.h>
#include <CQMsgCode.h>
#include <CQEVE_PrivateMsg.h>
#include <CQMsgSend.h>
#include<set>
#include <INItool.h>
using namespace std;
using namespace CQ;
bool debugx = true;//debugģʽ����
long long nowqq;
long long debugqq; // debugqq��
set<long long>groupList;

#define ainb(x,y) (((string(y)).find((string(x)))!=-1))

#define DEBUG(x) if(debugx==true)CQ::sendPrivateMsg(debugqq, ((string(x)).c_str()));

MUST_AppInfo_RETURN(CQAPPID)							  //appinfo����


EVE_Enable(Enable) {
	string debuglog;
	nowqq = getLoginQQ();
	debugqq = nowqq;
	debuglog += "��½qq" + to_string(nowqq);
	string filePath = getAppDirectory();
	filePath += "option.ini";
	fstream f(filePath, ios::in);
	if (f)DEBUG("�Ҳ���ini�����ļ�");
	{
		string s;
		while (f >> s) {
			if (s == "debugqq") {
				f >> debugqq;
			}
			else if (s == "grouplist") {
				getline(f, s);
				stringstream ss(s);
				long long groupid;
				while (ss >> groupid) {
					groupList.insert(groupid);
				}
			}
			else if (s=="debug") {
				f >> debugx;
			}
		}
	}
	debuglog += " debugqq="+to_string(debugqq)+"\n";
	for (auto x : groupList) {
		debuglog += " qȺ:" + to_string(x) + "\n";
	}
	DEBUG("start");
	DEBUG(debuglog);
	return 0;

}
EVE_Disable(Disable) {
	DEBUG("end");
	return 0;
}

map<long long, list<CQ::EVEGroupMsg> >msgList;//��Ϣlist Ⱥ������
EVE_GroupMsg_EX(Group) {
	if (groupList.count(eve.fromGroup) == 0)return;
	long long fromgroup = eve.fromGroup;
	long long fromqq = eve.fromQQ;
	string msg = eve.message;
	auto msgStream = eve.sendMsg();
	auto &msglist = msgList[fromgroup];
	//ά����Ϣlist
	msglist.push_front(eve);
	if (msglist.size() > 50) {
		msglist.pop_back();//��Ϣ���� ɾ��
	}
	//���⸴��
	{
		int times = 0;
		string sameMsg = "nullx";
		for (auto x : msglist) {
			if (sameMsg == "nullx") { sameMsg = x.message;}//��ʼ��msg
			if (sameMsg == x.message)times++;
			else break;
			if (times >= 4) {
				msgStream << code::image("break1.png") << send;
				msglist.clear();
				break;
			}
		}
	}
	
	if ( fromgroup == 933387304||fromgroup==810135023 ) {
		if (( msg.find('?') != -1 ||msg.find('��')!=-1)&& msg.find("��") != -1 ) {
			msgStream << "https://www.baidu.com \n�ٶ�һ���ӽ��\n��Ⱥ�ﴵ��СʱţB" << send;
		}
	}


}
EVE_PrivateMsg_EX(Speak) {

}