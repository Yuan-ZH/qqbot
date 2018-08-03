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
#include<random>
using namespace std;
using namespace CQ;
bool debugx = true;//debugģʽ����
long long debugqq = 295087430;//debugqq��
long long groupid = 248639786;//Ⱥ����
#define DEBUG(x) if(debugx==true)CQ::sendPrivateMsg(debugqq, ((string(x)).c_str()));
map<long long, int>mapp;
map<long long, int>ban;
std::mt19937 rng;
std::uniform_int_distribution<int> rand4(2, 4);
std::uniform_int_distribution<int> rand100(0, 100);
class users {
public: users(long long uid, int uspeak) { id = uid; speak = uspeak; }
		long long id; int speak; string nickname;
		bool operator < (const users& b)const {
			return speak < b.speak;
		}
};
EVE_Enable(Enable) {
	rng.seed(std::random_device()());
	fstream f("db.txt",ios::in);
	if (!f) {
		f.close();
		fstream f1("db.txt", ios::out);

		f1.close();
		f.open("db.txt", ios::in);
	}
	else {
		while (!f.eof()) {
			long long id;
			int times;
			f >> id >> times;
			if (times > 999999)continue;
			mapp.insert(make_pair(id, times));
		}
	}
	f.close();
	DEBUG("start");
	return 0;
}

EVE_Disable(Disable)
{
	fstream f("db.txt", ios::out);
	for (auto x : mapp) 	f << x.first << " " << x.second << "\n";
	f.close();
	DEBUG("save");
	mapp.clear();
	return 0;
}
class banmoretalk {
public:long long qqid;
	   int times;
	   int len;
	   banmoretalk() { qqid = 0; times = 0; len = 0; }
};
map<long long, string> lastmessage;
map<long long, string> lastmessage2;
map<long long, long long> lastsendqq;
map<long long, banmoretalk>bantalk;
string atinfo = "[CQ:at,qq=1442766687";
long long lastmsgid = 0;
long long getlastmsgid() {
	return lastmsgid;
}

EVE_GroupMsg_EX(Group1) {
	bool fudu = false;
	string msg = eve.message;
	long long fromgroup = eve.fromGroup;
	long long qqid = eve.fromQQ;
	long long msgid = eve.msgId;
	/*if (fromgroup == 725516089) {
		lastmsgid = msgid;
		std::future<int> f1 = std::async(std::launch::async, [](long long di, long long groupid) {
			//DEBUG(string("��ʼ����"));
			Sleep(60 * 1000 * 5 + 3);
			long long msgid2 = getlastmsgid();
			if (di == msgid2) {
				DEBUG("ok");
				sendGroupMsg(groupid, "�Ѿ������û�������˹�ϲ¥�ϳ�Ϊ��Ⱥ��");
			}

			return 8;
		}, lastmsgid, 725516089);

	}*/
	if (msg.find(atinfo) != -1) {
		DEBUG("�յ�@" + msg);
		eve.sendMsg("����������ά��");
		return;
		DEBUG(eve.messageRAW);
		fudu = true;
	}
	if (msg == lastmessage2[fromgroup]&&!fudu)
	{ eve.sendMsg(msg);
	fudu = true;
	lastmessage2[fromgroup] = "";
	}
	else {
		lastmessage2[fromgroup] = msg;
	}
	if ((msg.find("��")!=-1||msg.find("?") != -1)&& rand4(rng) == 3&&!fudu) {
		fudu = true;
		sendGroupMsg(eve.fromGroup, msg);
	}
	if (msg.find("����������@��Ϣ") != -1) {
		//atinfo = msg.substr(0, 20);
		DEBUG("����@��ϢΪ" + atinfo);
	}
	if (msg.find("��") != -1 && rand4(rng) == 3&&!fudu) {
		fudu = true;
		sendGroupMsg(eve.fromGroup, "������");
	}
	string msg1 = eve.messageRAW;
	
	/*
	if (rand100(rng) == 60) { 
		auto msg = eve.sendMsg();
		msg<<code::image("����.jpg")<<send;
		DEBUG("����");
	}*/
	if (!(eve.fromGroup == groupid||eve.fromGroup== 849690401))return;
	if (qqid == bantalk[fromgroup].qqid) {
		if (msg == lastmessage[fromgroup]&& (getGroupMemberInfo(groupid, qqid, true).permissions < 2)) {
			setGroupBan(groupid, qqid, 60);
			eve.sendMsg("��⵽���⸴��");
			lastmessage[fromgroup] = "";
		}
		bantalk[fromgroup].times++;
		bantalk[fromgroup].len+=msg.length();
		if (bantalk[fromgroup].times >= 6) {
			if (getGroupMemberInfo(groupid, qqid, true).permissions < 2) {
				setGroupBan(groupid, qqid, 60);
				eve.sendMsg("��⵽����ˮȺ");
				lastmessage[fromgroup] = "";
			}
		}
	}
	else {
		bantalk[fromgroup].len = 0;
		bantalk[fromgroup].qqid = qqid;
		bantalk[fromgroup].times = 1;
	}
	lastmessage[fromgroup] = msg;
	
	//mapp[qqid]++;

	if ((msg.find("С�ɰ�") != -1) && (msg.find("ˮȺ") != -1)) {
		ban[qqid]++;
		if (ban[qqid] >= rand4(rng) ){
			GroupMemberInfo i = getGroupMemberInfo(groupid, qqid, true);
			
			string resmsg;
			if (i.permissions >= 2) {		
				resmsg="��������";
			}
			else {
				setGroupBan(fromgroup, qqid, 60);
				resmsg = "���㻰��";
			}
			string nickname = i.��Ƭ;
			string sx = "@" + nickname + resmsg;
			sendGroupMsg(fromgroup,sx);
			ban[qqid] = 0;
			return;
		}
		DEBUG("��@" + eve.message);
		priority_queue<users>que;
		for (auto x : mapp)que.push(users(x.first, x.second));
		int times = 0;
		string strs = "����ˮȺ����";
		while (!que.empty()) {
			if (times++ >= 5)break;
			auto x = que.top();
			GroupMemberInfo i = getGroupMemberInfo(groupid, x.id, true);
			string nickname = i.��Ƭ;
			que.pop();
			strs += "\n"+nickname + "  " + to_string(x.speak) + "��";
		}
		long long mesid = sendGroupMsg(fromgroup, strs);
	}
	if (msg.find(atinfo) != -1&&(msg.find("ˮ")!=-1)&&(msg.find("��") != -1)&& (msg.find("��¼")!=-1||msg.find("����") != -1)) {
		//setGroupBan(groupid, qqid, 120);
		sendGroupMsg(fromgroup, string(to_string(mapp[qqid])+"��").c_str());
		
	
	}
	

}