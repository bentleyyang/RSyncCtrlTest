#include "stdafx.h"
#include "UkeyInterfaceNoLoginTest.h"
#include "util.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UkeyInterfaceNoLoginTest, "无登录测试(拔掉key)");

UkeyInterfaceNoLoginTest::UkeyInterfaceNoLoginTest()
{
}


UkeyInterfaceNoLoginTest::~UkeyInterfaceNoLoginTest()
{
}

void UkeyInterfaceNoLoginTest::setUp()
{

}

void UkeyInterfaceNoLoginTest::tearDown()
{

}

void UkeyInterfaceNoLoginTest::testGetUserList()
{
	using namespace rapidjson;
	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetUserList(); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* userlist = GetValueByPointer(jsonDoc, "/data/userlist");
		CPPUNIT_ASSERT(userlist&&userlist->IsString());
		std::wstring userlistContent = to_wstr(userlist->GetString());
	}

	//预期失败
	{

	}
}
void UkeyInterfaceNoLoginTest::testGetCertBase64String()
{
	using namespace rapidjson;

	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, 1); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* certBase64 = GetValueByPointer(jsonDoc, "/data/certBase64");
		CPPUNIT_ASSERT(certBase64&&certBase64->IsString());
		std::string certBase64Content = certBase64->GetString();
	}

	//预期成功2
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, 2); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* certBase64 = GetValueByPointer(jsonDoc, "/data/certBase64");
		CPPUNIT_ASSERT(certBase64&&certBase64->IsString());
		std::string certBase64Content = certBase64->GetString();
	}

	//预期失败1 type不符要求
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, -9); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//预期失败2 证书不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(L"@$^%^%$fd", 2); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyInterfaceNoLoginTest::testCertLogin()
{
	using namespace rapidjson;

	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, _RS_PASSWD); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//预期失败1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, L"$%^@$^DSFGSA@#$%"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyInterfaceNoLoginTest::testCertLoginNoPwd()
{
	return;
	using namespace rapidjson;

	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		//CPPUNIT_ASSERT(strCode == "0000");
	}
}

void UkeyInterfaceNoLoginTest::testGetPinRetryCount()
{
	using namespace rapidjson;

	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetPinRetryCount(_RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* retryCount = GetValueByPointer(jsonDoc, "/data/retryCount");
		CPPUNIT_ASSERT(retryCount&&retryCount->IsString());
		std::string retryCountContent = retryCount->GetString();
		CPPUNIT_ASSERT(!retryCountContent.empty());
		CPPUNIT_ASSERT(std::all_of(retryCountContent.begin(), retryCountContent.end(), ::isdigit));
	}

	//预期失败1 证书不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetPinRetryCount(L"@$^%^%$fd"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyInterfaceNoLoginTest::testKeySignByP7()
{
	using namespace rapidjson;

	CPPUNIT_ASSERT(login());
	//预期成功1 不带原文
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"1", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string tt = signdMsg->GetString();
	}

	//预期成功2 带原文
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"0", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string tt = signdMsg->GetString();
	}

	//预期失败1 container_id 不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"1", L"random-45634562456"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	CPPUNIT_ASSERT(logout());//TODO: logout无效
	//预期失败2 未登录
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"1", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyInterfaceNoLoginTest::testKeySignByP1()
{
	using namespace rapidjson;

	CPPUNIT_ASSERT(login());
	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string tt = signdMsg->GetString();
	}

	//预期失败1 container_id 不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", L"random-45634562456"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	CPPUNIT_ASSERT(logout());//TODO: logout无效
	//预期失败2 未登录
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyInterfaceNoLoginTest::testVerifySignByP1()
{
	using namespace rapidjson;

	CPPUNIT_ASSERT(login());

	//预期成功1
	{
		//获取signedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(_RS_CERT_SIGN, L"1234", to_wstr(signedMsgContent).data()); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(isSuccessful(jsonDoc));
		}
	}

	//预期失败1 签名证书格式错误
	{
		//获取signedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(L"$%^&%#&SHH", L"1234", to_wstr(signedMsgContent).data()); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
		}
	}

	//预期失败2 代签名原文不符
	{
		//获取signedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(_RS_CERT_SIGN, L"4321", to_wstr(signedMsgContent).data()); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
		}
	}

	//预期失败2 签名值不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(_RS_CERT_SIGN, L"1234", L"#^@&^$d"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}


	//预期失败3 未登录
	{
		//获取signedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			CPPUNIT_ASSERT(logout());//TODO: logout无效
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(_RS_CERT_SIGN, L"1234", to_wstr(signedMsgContent).data()); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
		}
	}
}

void UkeyInterfaceNoLoginTest::testChangePassWd()
{

}

void UkeyInterfaceNoLoginTest::testVerifyIdentity()
{
	using namespace rapidjson;
	//预期成功1 加密证书
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifyIdentity(_RS_CERT_ENCRYPT, _RS_AUTH_CODE); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		//TODO: 文档中数据是在/data中，这里测试了是在/data/data里，并不是/data里
		//const Value* data = GetValueByPointer(jsonDoc, "/data");
		//CPPUNIT_ASSERT(data&&data->IsString());
		//std::string dataContent = data->GetString();
		const Value* data = GetValueByPointer(jsonDoc, "/data/data");
		CPPUNIT_ASSERT(data&&data->IsString());
		std::string dataContent = data->GetString();
	}

	//预期成功2 签名证书
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifyIdentity(_RS_CERT_SIGN, _RS_AUTH_CODE); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		//TODO: 文档中数据是在/data中，这里测试了是在/data/data里，并不是/data里
		//const Value* data = GetValueByPointer(jsonDoc, "/data");
		//CPPUNIT_ASSERT(data&&data->IsString());
		//std::string dataContent = data->GetString();
		const Value* data = GetValueByPointer(jsonDoc, "/data/data");
		CPPUNIT_ASSERT(data&&data->IsString());
		std::string dataContent = data->GetString();
	}

	//预期失败1 证书不符合要求
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifyIdentity(L"kglijdshgsd96785", _RS_AUTH_CODE); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyInterfaceNoLoginTest::testKeyGetKeySn()
{
	using namespace rapidjson;
	//预期成功
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyGetKeySn(); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* keySn = GetValueByPointer(jsonDoc, "/data/keySn");
		CPPUNIT_ASSERT(keySn&&keySn->IsString());
		std::string keySnContent = keySn->GetString();

		//TODO: 文档中示例有containerId，但实际获取数据里并没有这个字段
		//const Value* containerId = GetValueByPointer(jsonDoc, "/data/containerId");
		//CPPUNIT_ASSERT(containerId&&containerId->IsString());
		//std::string containerIdContent = containerId->GetString();
	}
}

void UkeyInterfaceNoLoginTest::testKeyGetDeviceInfo()
{
	using namespace rapidjson;
	//预期成功1 设备序列号
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyGetDeviceInfo(_RS_CONTAINER_ID, L"1"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
		std::string infoContent = info->GetString();
	}

	//预期失败1 容器名不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyGetDeviceInfo(L"", L"1"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyInterfaceNoLoginTest::testKeyDigitalSignByP1()
{

}

void UkeyInterfaceNoLoginTest::testVerifyDigitalSignByP1()
{

}

void UkeyInterfaceNoLoginTest::testKeyEncryptData()
{

}

void UkeyInterfaceNoLoginTest::testKeyDecryptData()
{

}

void UkeyInterfaceNoLoginTest::testKeyEncryptFile()
{

}

void UkeyInterfaceNoLoginTest::testKeyDecryptFile()
{

}

void UkeyInterfaceNoLoginTest::testKeyEncryptByDigitalEnvelope()
{

}

void UkeyInterfaceNoLoginTest::testKeyDecryptByDigitalEnvelope()
{

}

void UkeyInterfaceNoLoginTest::testKeyStatus()
{

}