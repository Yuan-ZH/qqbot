#include <CQEVE.h>
#include <CQLogger.h>
#include <CQAPI_EX.h>
#include "APPINFO.h"

#include <sqlite3.h>
#include <string>
using namespace std;
using namespace CQ;

//�����static,��ʾ���loggerֻ�б�cpp��Ч
static Logger logger("��Q����Ӧ��");

string a = "1";
sqlite3 * db;
EVE_Enable(Enable2)
{
	
	
	
	int res = sqlite3_open("test.db", &db);

	if (res != SQLITE_OK) {

		CQ::sendPrivateMsg(295087430, "���ݿ�ʧ��");

		return 0;

	}

	else {

		CQ::sendPrivateMsg(295087430, "���ݿ�ok");

	}
	
	logger.Info("Ӧ�ñ�����");
	string s = "����";

	return 0;
}

EVE_Disable(Disable2)
{
	logger.Info("Ӧ�ñ�ͣ��");
	CQ::sendPrivateMsg(295087430, "���ݿ�ر�");
	sqlite3_close(db);
	return 0;
}

MUST_AppInfo_RETURN(CQAPPID)