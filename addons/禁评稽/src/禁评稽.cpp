#include <CQEVE_GroupMsg.h>
#include <CQcode.h>
#include <CQLogger.h>
#include <CQAPI_EX.h>
#include<Windows.h>
#include <string>
#include<cstdlib>
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
#include<list>
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




map<long long, list<CQ::EVEGroupMsg> >msgList;//��Ϣlist Ⱥ������

EVE_GroupMsg_EX(Group) {
	if (groupList.count(eve.fromGroup) == 0)return;
	long long fromgroup = eve.fromGroup;
	long long fromqq = eve.fromQQ;
	string msg = eve.message;
	auto &msglist = msgList[fromgroup];
	//ά����Ϣlist
	msglist.push_front(eve);
	if (msglist.size() > 50) {
		msglist.pop_back();//��Ϣ���� ɾ��
	}
	//���⸴��
	{
		long long sameQq;
		int times = 0;
		string sameMsg = "nullx";
		for (auto x : msglist) {
			if (sameMsg == "nullx") { sameMsg = x.message; sameQq = x.fromQQ; }
			if (sameMsg == x.message)times++;
			else break;
			if (times == 2) {
				setGroupBan(fromgroup, fromqq, 60);
				return;
			}
		}
	}
	//ˮȺ����
	{
		long long sameQq=0;
		int times = 0;
		for (auto x : msglist) {
			if (sameQq == 0) { sameQq = x.fromQQ; }
			if (sameQq != x.fromQQ)break;
			times++;
			if (times >= 6) {
				setGroupBan(fromgroup, fromqq, 60);
				auto x1 = CQ::EVEGroupMsg(x);
				x1.fromQQ = -1;
				x1.message = "nullxx";
				msglist.push_front(x1);
				return;
			}
		}
	}
}
EVE_PrivateMsg_EX(Speak) {

}


EVE_Enable(Enable) {
	msgList.clear();
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
			else if (s == "debug") {
				f >> debugx;
			}
		}
	}
	debuglog += " debugqq=" + to_string(debugqq) + "\n";
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