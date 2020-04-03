#include "stdafx.h"
#include "InterfaceTest.h"

#include "util.h"

InterfaceTest::InterfaceTest()
{
}

InterfaceTest::~InterfaceTest()
{
}

void InterfaceTest::setUp()
{
}

void InterfaceTest::tearDown()
{
}

void InterfaceTest::test1()
{
	BSTR str = L"a";
	std::string u = _com_util::ConvertBSTRToString(str);
	CString str2(u.data());

	_bstr_t ss = "a";
	BSTR ss2(ss);
	std::string u2 = _com_util::ConvertBSTRToString(ss2);


	//CDRS_CertSafe p;
	//p.Create(NULL, WS_CHILD, CRect(0, 0, 1, 1), nullptr, NULL);
	//CPPUNIT_ASSERT(p.RS_CertLogin(L"", L""));
	//CRSyncCtrlTestDlg dlg;
	//AfxMessageBox(dlg.getCtrl()->RS_CertLogin(L"", L""));

}

void InterfaceTest::testGetCertInfo()
{
	using namespace rapidjson;

	//Ԥ��ʧ��1 type����
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"-1"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) != "0000");
	}

	//Ԥ��ʧ��2 ֤�鲻��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(L"#$^%$&@fg", L"1"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) != "0000");
	}

	//Ԥ�ڳɹ�1 ֤��汾
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"1"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�2 ֤�����к�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"2"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�3 ֤��䷢����Ϣ
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"5"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�4 ֤��ӵ������Ϣ
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"7"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�5 ֤����Ч��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"6"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�6 ֤��䷢��CN
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"33"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�7 ֤��䷢��O
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"34"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�8 ֤��䷢��OU
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"35"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�9 ֤��ӵ������ϢCN
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"49"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�10 ֤��ӵ������ϢO
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"50"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�11 ֤��ӵ������ϢOU
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"51"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�12 ֤��ӵ������ϢEMAIL
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"52"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�13 ����֤�����֤��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"53"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�14 ��ҵͳһ������ô���
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"54"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�15 ֤��ʹ������Կ��ʶ��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"55"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�16 ֤��Ψһ��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"300"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

}

void InterfaceTest::testGetUserList()
{
	using namespace rapidjson;
	//Ԥ�ڳɹ�1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetUserList(); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(std::string(code->GetString()) == "0000");

		const Value* userlist = GetValueByPointer(jsonDoc, "/data/userlist");
		CPPUNIT_ASSERT(userlist&&userlist->IsString());
		std::wstring userlistContent = to_wstr(userlist->GetString());
	}

	//Ԥ��ʧ��
	{

	}
}
void InterfaceTest::testGetCertBase64String()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, 1); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* certBase64 = GetValueByPointer(jsonDoc, "/data/certBase64");
		CPPUNIT_ASSERT(certBase64&&certBase64->IsString());
		std::string certBase64Content = certBase64->GetString();
	}

	//Ԥ�ڳɹ�2
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, 2); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* certBase64 = GetValueByPointer(jsonDoc, "/data/certBase64");
		CPPUNIT_ASSERT(certBase64&&certBase64->IsString());
		std::string certBase64Content = certBase64->GetString();
	}

	//Ԥ��ʧ��1 type����Ҫ��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, -9); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}

	//Ԥ��ʧ��2 ֤�鲻��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(L"@$^%^%$fd", 2); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}
}

void InterfaceTest::testGetPinRetryCount()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetPinRetryCount(_RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* retryCount = GetValueByPointer(jsonDoc, "/data/retryCount");
		CPPUNIT_ASSERT(retryCount&&retryCount->IsString());
		std::string retryCountContent = retryCount->GetString();
		CPPUNIT_ASSERT(!retryCountContent.empty());
		CPPUNIT_ASSERT(std::all_of(retryCountContent.begin(), retryCountContent.end(), ::isdigit));
	}

	//Ԥ��ʧ��1 ֤�鲻��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetPinRetryCount(L"@$^%^%$fd"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}
}

void InterfaceTest::testGetTransid()
{
	//100020191120141710102

	using namespace rapidjson;

	//Ԥ�ڳɹ�1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetTransid(L"1000"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* transid = GetValueByPointer(jsonDoc, "/data/transid");
		CPPUNIT_ASSERT(transid&&transid->IsString());
		std::string transidContent = transid->GetString();
		//CPPUNIT_ASSERT(transidContent.length() == 21);
		CPPUNIT_ASSERT(!transidContent.empty());
		CPPUNIT_ASSERT(std::all_of(transidContent.begin(), transidContent.end(), ::isdigit));
	}
}

void InterfaceTest::testCertLogin1()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, _RS_PASSWD); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");
	}

	//Ԥ��ʧ��1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, L"$%^@$^DSFGSA@#$%"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}
}

void InterfaceTest::testCertLoginNoPwd()
{

}

void InterfaceTest::testConfigParameters()
{
}

void InterfaceTest::testGetParameters()
{
	using namespace rapidjson;

	const wchar_t* cmds[] = { L"authCode", L"rsigncloud", L"authType", L"keySn", L"signAndVerify" };
	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(L"authCode"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* authCode = GetValueByPointer(jsonDoc, "/data/authCode");
		CPPUNIT_ASSERT(authCode&&authCode->IsString());
	}

	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(L"rsigncloud"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* rsigncloud = GetValueByPointer(jsonDoc, "/data/rsigncloud");
		CPPUNIT_ASSERT(rsigncloud&&rsigncloud->IsString());
	}

	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(L"authType"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* authType = GetValueByPointer(jsonDoc, "/data/authType");
		CPPUNIT_ASSERT(authType&&authType->IsString());
	}

	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(L"keySn"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* keySn = GetValueByPointer(jsonDoc, "/data/keySn");
		CPPUNIT_ASSERT(keySn&&keySn->IsString());
	}

	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(L"signAndVerify"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signAndVerify = GetValueByPointer(jsonDoc, "/data/signAndVerify");
		CPPUNIT_ASSERT(signAndVerify&&signAndVerify->IsString());
	}

	//Ԥ��ʧ��1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(L""); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}
}

void InterfaceTest::testKeySignByP7()
{
	using namespace rapidjson;

	CPPUNIT_ASSERT(login());
	//Ԥ�ڳɹ�1 ����ԭ��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"1", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string tt = signdMsg->GetString();
	}

	//Ԥ�ڳɹ�2 ��ԭ��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"0", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string tt = signdMsg->GetString();
	}

	//Ԥ��ʧ��1 container_id ����
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"1", L"random-45634562456"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}

	CPPUNIT_ASSERT(logout());//TODO: logout��Ч
	//Ԥ��ʧ��2 δ��¼
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"1", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}
}

void InterfaceTest::testVerifySignByP7()
{
	using namespace rapidjson;

	CPPUNIT_ASSERT(login());

	//Ԥ�ڳɹ�1 ����ԭ��
	{
		//��ȡsignedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"1", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP7(L"1234", to_wstr(signedMsgContent).data(), L"1"); });
			CPPUNIT_ASSERT(!jsonDoc.HasParseError());
			const Value* code = GetValueByPointer(jsonDoc, "/code");
			CPPUNIT_ASSERT(code&&code->IsString());
			std::string strCode = code->GetString();
			CPPUNIT_ASSERT(strCode == "0000");
		}
	}
	//Ԥ�ڳɹ�2 ��ԭ��
	{
		//��ȡsignedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"0", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP7(L"", to_wstr(signedMsgContent).data(), L"0"); });
			CPPUNIT_ASSERT(!jsonDoc.HasParseError());
			const Value* code = GetValueByPointer(jsonDoc, "/code");
			CPPUNIT_ASSERT(code&&code->IsString());
			std::string strCode = code->GetString();
			CPPUNIT_ASSERT(strCode == "0000");
		}
	}

	//Ԥ��ʧ��1 ǩ��ֵ��ʽ����
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP7(L"1234", L"43673456547", L"1"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}

	//Ԥ��ʧ��2 flag������ʵ��
	{
		//��ȡsignedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"1", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP7(L"", to_wstr(signedMsgContent).data(), L"0"); });
			CPPUNIT_ASSERT(!jsonDoc.HasParseError());
			const Value* code = GetValueByPointer(jsonDoc, "/code");
			CPPUNIT_ASSERT(code&&code->IsString());
			std::string strCode = code->GetString();
			CPPUNIT_ASSERT(strCode != "0000");
		}
	}

	
	//Ԥ��ʧ��3 δ��¼
	{
		//��ȡsignedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"1", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			CPPUNIT_ASSERT(logout());//TODO: logout��Ч
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP7(L"1234", to_wstr(signedMsgContent).data(), L"1"); });
			CPPUNIT_ASSERT(!jsonDoc.HasParseError());
			const Value* code = GetValueByPointer(jsonDoc, "/code");
			CPPUNIT_ASSERT(code&&code->IsString());
			std::string strCode = code->GetString();
			CPPUNIT_ASSERT(strCode != "0000");
		}
	}
}

void InterfaceTest::testEncryptFile()
{
	using namespace rapidjson;
	
	

	//Ԥ�ڳɹ�1
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		fs::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write("1234", 4);
		CPPUNIT_ASSERT(ofs);
		ofs.close();
		CPPUNIT_ASSERT(fs::exists(inFile));
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFile(inFile.data(), outFile.data()); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		CPPUNIT_ASSERT(fs::exists(outFile));
	}

	//Ԥ��ʧ��1 ԭ�ļ�������
	{
		//TODO: ������ֱ���յ������ݣ�û��code
		std::wstring inFile = L"C:/agag2342sdfgsfg";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		CPPUNIT_ASSERT(!fs::exists(inFile));
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFile(inFile.data(), outFile.data()); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}
}

void InterfaceTest::testDevryptFile()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�1
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		fs::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write("1234", 4);
		CPPUNIT_ASSERT(ofs);
		ofs.close();
		CPPUNIT_ASSERT(fs::exists(inFile));
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFile(inFile.data(), outFile.data()); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		CPPUNIT_ASSERT(fs::exists(outFile));

		//
		{
			//std::wstring decryptInFile = std::experimental::filesystem::current_path().wstring() + L"/test_decrypt_file_in.sm4";
			std::wstring decryptOutFile = fs::current_path().wstring() + L"/test_decrypt_file_out.txt";
			//CPPUNIT_ASSERT(copy_file(path(outFile), path(decryptInFile), copy_options::overwrite_existing));
			GDoc jsonDoc = parseJson([&decryptOutFile, &symKey, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_DevryptFile(to_wstr(symKey->GetString()).data(), outFile.data(), decryptOutFile.data()); });
			CPPUNIT_ASSERT(!jsonDoc.HasParseError());
			const Value* code = GetValueByPointer(jsonDoc, "/code");
			CPPUNIT_ASSERT(code&&code->IsString());
			std::string strCode = code->GetString();
			CPPUNIT_ASSERT(strCode == "0000");
			CPPUNIT_ASSERT(fs::exists(decryptOutFile));


			
			fs::ifstream ifs(fs::path(decryptOutFile), std::ios::binary);
			char tt[4];
			ifs.read(tt, 4);
			CPPUNIT_ASSERT(ifs);
			CPPUNIT_ASSERT(std::equal(tt, tt + 4, "1234"));

			//TODO: ������ԵĽ����Դ�ļ�ֻ��4���ֽڳ��ȣ����ܺ���ļ�����Ȼǰ4���ֽ�����ȷ�ģ����������ļ���ǿ�Ʊ��128�ֽڣ����Һ����������
			CPPUNIT_ASSERT(fs::file_size(fs::path(decryptOutFile))==4);
		}
	}

	//Ԥ��ʧ��1 symKey�����Ĳ�ƥ��
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		fs::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write("1234", 4);
		CPPUNIT_ASSERT(ofs);
		ofs.close();
		CPPUNIT_ASSERT(fs::exists(inFile));
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFile(inFile.data(), outFile.data()); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		CPPUNIT_ASSERT(fs::exists(outFile));

		//
		{
			std::wstring decryptOutFile = fs::current_path().wstring() + L"/test_decrypt_file_out.txt";
			GDoc jsonDoc = parseJson([&decryptOutFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_DevryptFile(L"astgagh#$%^$#@^afhsha", outFile.data(), decryptOutFile.data()); });
			CPPUNIT_ASSERT(!jsonDoc.HasParseError());
			const Value* code = GetValueByPointer(jsonDoc, "/code");
			CPPUNIT_ASSERT(code&&code->IsString());
			std::string strCode = code->GetString();
			CPPUNIT_ASSERT(strCode != "0000");
		}
	}
}

void InterfaceTest::testEncryptData()
{
	using namespace rapidjson;
	//Ԥ�ڳɹ�1
	{

		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(L"1234"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		std::string symKeyContent = symKey->GetString();

		const Value* encDataStr = GetValueByPointer(jsonDoc, "/data/encDataStr");
		CPPUNIT_ASSERT(encDataStr&&encDataStr->IsString());
		std::string encDataStrContent = encDataStr->GetString();
	}

	////Ԥ��ʧ��1 ���������ݳ��ȴ���1024
	//{
	//	std::vector<wchar_t> tt(1024, L'A' ); tt[1023] = L'\0';
	//
	//	GDoc jsonDoc = parseJson([&tt]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(tt.data()); });
	//	CPPUNIT_ASSERT(!jsonDoc.HasParseError());
	//	const Value* code = GetValueByPointer(jsonDoc, "/code");
	//	CPPUNIT_ASSERT(code&&code->IsString());
	//	std::string strCode = code->GetString();
	//	CPPUNIT_ASSERT(strCode != "0000");
	//}
}

void InterfaceTest::testDevryptData()
{
	using namespace rapidjson;
	//Ԥ�ڳɹ�1
	{

		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(L"1234"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		std::string symKeyContent = symKey->GetString();

		const Value* encDataStr = GetValueByPointer(jsonDoc, "/data/encDataStr");
		CPPUNIT_ASSERT(encDataStr&&encDataStr->IsString());
		std::string encDataStrContent = encDataStr->GetString();

		{
			GDoc jsonDoc = parseJson([&symKeyContent, &encDataStrContent]()->CString {return s_pDRS_CertSafeCtrl->RS_DevryptData(to_wstr(symKeyContent).data(), to_wstr(encDataStrContent).data()); });
			CPPUNIT_ASSERT(!jsonDoc.HasParseError());
			const Value* code = GetValueByPointer(jsonDoc, "/code");
			CPPUNIT_ASSERT(code&&code->IsString());
			std::string strCode = code->GetString();
			CPPUNIT_ASSERT(strCode == "0000");

			const Value* dncDataStr = GetValueByPointer(jsonDoc, "/data/dncDataStr");
			std::string dncDataContent = dncDataStr->GetString();
			CPPUNIT_ASSERT(dncDataContent == "1234");
		}
	}

	//Ԥ��ʧ��1 ��Կ����
	{

		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(L"1234"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		std::string symKeyContent = symKey->GetString();

		const Value* encDataStr = GetValueByPointer(jsonDoc, "/data/encDataStr");
		CPPUNIT_ASSERT(encDataStr&&encDataStr->IsString());
		std::string encDataStrContent = encDataStr->GetString();

		{
			GDoc jsonDoc = parseJson([&symKeyContent, &encDataStrContent]()->CString {return s_pDRS_CertSafeCtrl->RS_DevryptData(L"$%^FGH", to_wstr(encDataStrContent).data()); });
			CPPUNIT_ASSERT(!jsonDoc.HasParseError());
			const Value* code = GetValueByPointer(jsonDoc, "/code");
			CPPUNIT_ASSERT(code&&code->IsString());
			std::string strCode = code->GetString();
			CPPUNIT_ASSERT(strCode != "0000");

		}
	}

	//Ԥ��ʧ��1 ���Ĳ���
	{

		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(L"1234"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		std::string symKeyContent = symKey->GetString();

		const Value* encDataStr = GetValueByPointer(jsonDoc, "/data/encDataStr");
		CPPUNIT_ASSERT(encDataStr&&encDataStr->IsString());
		std::string encDataStrContent = encDataStr->GetString();

		{
			GDoc jsonDoc = parseJson([&symKeyContent, &encDataStrContent]()->CString {return s_pDRS_CertSafeCtrl->RS_DevryptData(to_wstr(symKeyContent).data(), L"4321"); });
			CPPUNIT_ASSERT(!jsonDoc.HasParseError());
			const Value* code = GetValueByPointer(jsonDoc, "/code");
			CPPUNIT_ASSERT(code&&code->IsString());
			std::string strCode = code->GetString();
			CPPUNIT_ASSERT(strCode != "0000");

		}
	}
}

void InterfaceTest::testKeySignByP1()
{
	using namespace rapidjson;

	CPPUNIT_ASSERT(login());
	//Ԥ�ڳɹ�1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string tt = signdMsg->GetString();
	}

	//Ԥ��ʧ��1 container_id ����
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", L"random-45634562456"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}

	CPPUNIT_ASSERT(logout());//TODO: logout��Ч
	//Ԥ��ʧ��2 δ��¼
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}
}

void InterfaceTest::testVerifySignByP1()
{
	using namespace rapidjson;

	CPPUNIT_ASSERT(login());

	//Ԥ�ڳɹ�1
	{
		//��ȡsignedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(_RS_CERT_SIGN, L"1234", to_wstr(signedMsgContent).data()); });
			CPPUNIT_ASSERT(!jsonDoc.HasParseError());
			const Value* code = GetValueByPointer(jsonDoc, "/code");
			CPPUNIT_ASSERT(code&&code->IsString());
			std::string strCode = code->GetString();
			CPPUNIT_ASSERT(strCode == "0000");
		}
	}

	//Ԥ��ʧ��1 ǩ��֤���ʽ����
	{
		//��ȡsignedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(L"$%^&%#&SHH", L"1234", to_wstr(signedMsgContent).data()); });
			CPPUNIT_ASSERT(!jsonDoc.HasParseError());
			const Value* code = GetValueByPointer(jsonDoc, "/code");
			CPPUNIT_ASSERT(code&&code->IsString());
			std::string strCode = code->GetString();
			CPPUNIT_ASSERT(strCode != "0000");
		}
	}

	//Ԥ��ʧ��2 ��ǩ��ԭ�Ĳ���
	{
		//��ȡsignedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(_RS_CERT_SIGN, L"4321", to_wstr(signedMsgContent).data()); });
			CPPUNIT_ASSERT(!jsonDoc.HasParseError());
			const Value* code = GetValueByPointer(jsonDoc, "/code");
			CPPUNIT_ASSERT(code&&code->IsString());
			std::string strCode = code->GetString();
			CPPUNIT_ASSERT(strCode != "0000");
		}
	}

	//Ԥ��ʧ��2 ǩ��ֵ����
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(_RS_CERT_SIGN, L"1234", L"#^@&^$d"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}


	//Ԥ��ʧ��3 δ��¼
	{
		//��ȡsignedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			CPPUNIT_ASSERT(logout());//TODO: logout��Ч
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(_RS_CERT_SIGN, L"1234", to_wstr(signedMsgContent).data()); });
			CPPUNIT_ASSERT(!jsonDoc.HasParseError());
			const Value* code = GetValueByPointer(jsonDoc, "/code");
			CPPUNIT_ASSERT(code&&code->IsString());
			std::string strCode = code->GetString();
			CPPUNIT_ASSERT(strCode != "0000");
		}
	}
}

void InterfaceTest::testChangePassWd()
{
	
}

void InterfaceTest::testVerifyIdentity()
{
	using namespace rapidjson;
	//Ԥ�ڳɹ�1 ����֤��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifyIdentity(_RS_CERT_ENCRYPT, _RS_AUTH_CODE); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		//TODO: �ĵ�����������/data�У��������������/data/data�������/data��
		//const Value* data = GetValueByPointer(jsonDoc, "/data");
		//CPPUNIT_ASSERT(data&&data->IsString());
		//std::string dataContent = data->GetString();
		const Value* data = GetValueByPointer(jsonDoc, "/data/data");
		CPPUNIT_ASSERT(data&&data->IsString());
		std::string dataContent = data->GetString();
	}

	//Ԥ�ڳɹ�2 ǩ��֤��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifyIdentity(_RS_CERT_SIGN, _RS_AUTH_CODE); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		//TODO: �ĵ�����������/data�У��������������/data/data�������/data��
		//const Value* data = GetValueByPointer(jsonDoc, "/data");
		//CPPUNIT_ASSERT(data&&data->IsString());
		//std::string dataContent = data->GetString();
		const Value* data = GetValueByPointer(jsonDoc, "/data/data");
		CPPUNIT_ASSERT(data&&data->IsString());
		std::string dataContent = data->GetString();
	}

	//Ԥ��ʧ��1 ֤�鲻����Ҫ��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifyIdentity(L"kglijdshgsd96785", _RS_AUTH_CODE); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}
}

void InterfaceTest::testKeyGetKeySn()
{
	using namespace rapidjson;
	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyGetKeySn(); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* keySn = GetValueByPointer(jsonDoc, "/data/keySn");
		CPPUNIT_ASSERT(keySn&&keySn->IsString());
		std::string keySnContent = keySn->GetString();

		//TODO: �ĵ���ʾ����containerId����ʵ�ʻ�ȡ�����ﲢû������ֶ�
		//const Value* containerId = GetValueByPointer(jsonDoc, "/data/containerId");
		//CPPUNIT_ASSERT(containerId&&containerId->IsString());
		//std::string containerIdContent = containerId->GetString();
	}
}

void InterfaceTest::testKeyGetDeviceInfo()
{
	using namespace rapidjson;
	//Ԥ�ڳɹ�1 �豸���к�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyGetDeviceInfo(_RS_CONTAINER_ID, L"1"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
		std::string infoContent = info->GetString();
	}

	//Ԥ��ʧ��1 ����������
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyGetDeviceInfo(L"", L"1"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}
}

void InterfaceTest::testKeyDigitalSignByP1()
{

}

void InterfaceTest::testVerifyDigitalSignByP1()
{

}

void InterfaceTest::testKeyEncryptData()
{

}

void InterfaceTest::testKeyDecryptData()
{

}

void InterfaceTest::testKeyEncryptFile()
{

}

void InterfaceTest::testKeyDecryptFile()
{

}

void InterfaceTest::testKeyEncryptByDigitalEnvelope()
{

}

void InterfaceTest::testKeyDecryptByDigitalEnvelope()
{

}

void InterfaceTest::testKeyStatus()
{

}

void InterfaceTest::testCloudLoginAuth()
{

}

void InterfaceTest::testCloudGetAuth()
{

}

void InterfaceTest::testCreateQRCode()
{

}

void InterfaceTest::testCloudSealAuth()
{

}

void InterfaceTest::testCloudGetSealList()
{

}

void InterfaceTest::testCloudSignByP7()
{

}

void InterfaceTest::testCloudEncryptAuth()
{

}

void InterfaceTest::testCloudEncryptData()
{

}

void InterfaceTest::testCloudEncryptFile()
{

}

/*string RS_EncryptDataBase64(string symKey, string certBase64)
������
symKey:����������
certBase64:����֤��base64����
���أ�Json��ʽ���ַ���
	����
	{"code":"0000","msg":"ִ�гɹ���","data":{"encReachKey":""}}
encReachKey:���ܺ������
���ܣ��ǶԳƼ������ݡ�
*/
void InterfaceTest::testEncryptDataBase64()
{

}

void InterfaceTest::testEncryptFileBase64()
{

}

void InterfaceTest::testCloudDevryptAuth()
{

}

void InterfaceTest::testCloudDevryptData()
{

}

void InterfaceTest::testCloudDevryptFile()
{

}

void InterfaceTest::testCloudReceiveDevryptResult()
{

}

void InterfaceTest::testCloudGetCompanyCert()
{

}

void InterfaceTest::testCloudGetCertAuth()
{

}

void InterfaceTest::testCloudGetCertBase64()
{

}

void InterfaceTest::testCloudLogoutAuth()
{

}

void InterfaceTest::testCloudLogout()
{

}

void InterfaceTest::testCloudLoginAuthEvent()
{

}

void InterfaceTest::testCloudSealAuthEvent()
{

}

void InterfaceTest::testCloudGetSignResultEvent()
{

}

void InterfaceTest::testCloudEncAuthEvent()
{

}

void InterfaceTest::testCloudDevAuthEvent()
{

}

void InterfaceTest::testCloudGetCertAuthEvent()
{

}



void InterfaceTest::testCloudGetSignResult()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�
	{
		std::wstring transid = getTransid();
		CPPUNIT_ASSERT(!transid.empty());
		GDoc jsonDoc = parseJson([&transid]()->CString {return s_pDRS_CertSafeCtrl->RS_CloudGetSignResult(transid.data()); });
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signResult = GetValueByPointer(jsonDoc, "/data/signResult");
		CPPUNIT_ASSERT(signResult&&signResult->IsString());
		std::string signResultContent = signResult->GetString();
		CPPUNIT_ASSERT(signResultContent == "0" || signResultContent == "1" || signResultContent == "2");

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());

		const Value* certBase64 = GetValueByPointer(jsonDoc, "/data/certBase64");
		CPPUNIT_ASSERT(certBase64&&certBase64->IsString());
	}

	//Ԥ��ʧ��1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CloudGetSignResult(L"456dfdfhsdg3"); });
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}

}

