#include <CQEVE_GroupMsg.h>
#include <CQcode.h>
#include <CQLogger.h>
#include <CQAPI_EX.h>

#include <string>
#include<cstdlib>
#include<vector>
#include<future>
#include<map>
#include<queue>
#include<fstream>
using namespace std;
using namespace CQ;
bool debugx = true;//debugģʽ����
long long debugqq = 295087430;//debugqq��
long long groupid = 248639786;//Ⱥ����
#define DEBUG(x) if(debugx==true)CQ::sendPrivateMsg(debugqq, ((string(x)).c_str()));
map<long long, int>mapp;
map<long long, int>ban;
class users {
public: users(long long uid, int uspeak) { id = uid; speak = uspeak; }
		long long id; int speak; string nickname;
		bool operator < (const users& b)const {
			return speak < b.speak;
		}
};
EVE_Enable(Enable) {
	fstream f("db.txt",ios::in);
	if (!f) {
		f.close();
		fstream f1("db.txt", ios::out);
		f1.close();
		f.open("db.txt", ios::in);
	}
	while (!f.eof()) {
		long long id;
		int times;
		f >> id >> times;
		mapp[id] = times;
	}
	f.close();
	DEBUG("start");
	return 0;
}
EVE_Disable(Disable)
{
	fstream f("db.txt", ios::out);
	for (auto x : mapp) 	f << x.first << " " << x.second << endl;
	f.close();
	DEBUG("save");
	return 0;
}

EVE_GroupMsg_EX(Group1) {
	if (eve.fromGroup != groupid)return;
	
	long long qqid = eve.fromQQ;
	string msg = eve.message;
	mapp[qqid]++;
	
	if ((msg.find("С�ɰ�") != -1) && (msg.find("ˮȺ") != -1)) {
		ban[qqid]++;
		if (ban[qqid] >= 2) {
			setGroupBan(groupid, qqid, 60);
			string nickname= getGroupMemberInfo(groupid,qqid, true).��Ƭ;

			string sx = "@" + nickname + "��̫���� Ъһ��";
			sendGroupMsg(groupid,sx);
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
		long long mesid = sendGroupMsg(groupid, strs);
	}
	fstream f("db.txt", ios::out);
	for (auto x : mapp) 	f << x.first << " " << x.second << endl;
	f.close();
}