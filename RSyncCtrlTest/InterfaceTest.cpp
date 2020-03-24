#include "stdafx.h"
#include "InterfaceTest.h"

#include <experimental/filesystem>
#include <fstream>
#include <vector>

#include "Poco/UnicodeConverter.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/pointer.h"

#include "Utility.h"
#include "RSyncCtrlTestDlg.h"

CPPUNIT_TEST_SUITE_REGISTRATION(InterfaceTest);


#define _RS_CONTAINER_ID (L"F5BA5CE5-BC9A-49C8-AE47-1825115058D7")
#define _RS_PASSWD (L"12345678")
#define _RS_CERT_ENCRYPT (L"MIID8jCCA5igAwIBAgILIPOoHk2h3atHMfEwCgYIKoEcz1UBg3UwYjELMAkGA1UEBhMCQ04xJDAiBgNVBAoMG05FVENBIENlcnRpZmljYXRlIEF1dGhvcml0eTEtMCsGA1UEAwwkTkVUQ0EgU00yIFRFU1QwMSBhbmQgRXZhbHVhdGlvbiBDQTAxMB4XDTE5MTEwMTA0NTgyNloXDTI0MTEwMTA0NTgyNlowgdExCzAJBgNVBAYTAkNOMQ8wDQYDVQQIDAZGdWppYW4xMzAxBgNVBAcMKuemj+W7uuecgeemj+W3nuW4gum8k+alvOWMuua5luS4nOi3rzE4OOWPtzE9MDsGA1UECgw056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMu+8iTE9MDsGA1UEAww056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMu+8iTBZMBMGByqGSM49AgEGCCqBHM9VAYItA0IABJ1jTugwIT4TlNF2IxsxVxv\/exGmo+Io3Upj\/SJv+epJQgo5ehOjD\/jAMZq413KCqF41gIaS7Ec3BSVNXJsWjvOjggHDMIIBvzAMBgNVHRMBAf8EAjAAMB0GA1UdDgQWBBT8CyNZp3dl6nPw8AoQTyAVLBKlGDAfBgNVHSMEGDAWgBQMe+ticwN1+oxKJAz2jzshZX4X6TBrBgNVHSAEZDBiMGAGCisGAQQBgZJIDQowUjBQBggrBgEFBQcCARZEaHR0cDovL3d3dy5jbmNhLm5ldC9jcy9rbm93bGVkZ2Uvd2hpdGVwYXBlci9jcHMvbmV0Q0F0ZXN0Y2VydGNwcy5wZGYwMwYDVR0fBCwwKjAooCagJIYiaHR0cDovL3Rlc3QuY25jYS5uZXQvY3JsL1NNMkNBLmNybDAOBgNVHQ8BAf8EBAMCAzgwNAYKKwYBBAGBkkgBDgQmDCQ1MjE2MDc4NmMwYTM3MmZjOGMzMzBhMDJiMTZjYmE2M0BTMDIwgYYGCCsGAQUFBwEBBHoweDBNBggrBgEFBQcwAYZBaHR0cDovLzE5Mi4xNjguMC43OS9vY3NwY29uc29sZS9vY3NwL29jc3BfY2hlY2tfdXNlcmNlcnRfc3RhdGUuZG8wJwYIKwYBBQUHMAGGG2h0dHA6Ly8xNzIuMC4wLjE6ODAvdGVzdHVybDAKBggqgRzPVQGDdQNIADBFAiBUQE+fdAD1eH6OyCuSURjv\/vp+x0MYv8Hkh8S4Ks\/svQIhANdkoJyTiNlij5wckuzhWDJLokcGIyup+y5JYS4xmt7D")

#define _RS_CERT_SIGN (L"MIID8jCCA5igAwIBAgILENzv3NBdilQmXGUwCgYIKoEcz1UBg3UwYjELMAkGA1UEBhMCQ04xJDAiBgNVBAoMG05FVENBIENlcnRpZmljYXRlIEF1dGhvcml0eTEtMCsGA1UEAwwkTkVUQ0EgU00yIFRFU1QwMSBhbmQgRXZhbHVhdGlvbiBDQTAxMB4XDTE5MTEwMTA0NTgyNloXDTI0MTEwMTA0NTgyNlowgdExCzAJBgNVBAYTAkNOMQ8wDQYDVQQIDAZGdWppYW4xMzAxBgNVBAcMKuemj+W7uuecgeemj+W3nuW4gum8k+alvOWMuua5luS4nOi3rzE4OOWPtzE9MDsGA1UECgw056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMu+8iTE9MDsGA1UEAww056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMu+8iTBZMBMGByqGSM49AgEGCCqBHM9VAYItA0IABJPDjH4qPGIXcKopl6CYXTOqOAE2dmRchTE3TTlDtg7zTPFbe\/fOUFj+zlkUfrLWwopPAJOCA0cG\/ufkffHbhjejggHDMIIBvzAMBgNVHRMBAf8EAjAAMB0GA1UdDgQWBBQJVOszT+dSIPLoT8mIVl01gK37OTAfBgNVHSMEGDAWgBQMe+ticwN1+oxKJAz2jzshZX4X6TBrBgNVHSAEZDBiMGAGCisGAQQBgZJIDQowUjBQBggrBgEFBQcCARZEaHR0cDovL3d3dy5jbmNhLm5ldC9jcy9rbm93bGVkZ2Uvd2hpdGVwYXBlci9jcHMvbmV0Q0F0ZXN0Y2VydGNwcy5wZGYwMwYDVR0fBCwwKjAooCagJIYiaHR0cDovL3Rlc3QuY25jYS5uZXQvY3JsL1NNMkNBLmNybDAOBgNVHQ8BAf8EBAMCBsAwNAYKKwYBBAGBkkgBDgQmDCQ1MjE2MDc4NmMwYTM3MmZjOGMzMzBhMDJiMTZjYmE2M0BTMDIwgYYGCCsGAQUFBwEBBHoweDBNBggrBgEFBQcwAYZBaHR0cDovLzE5Mi4xNjguMC43OS9vY3NwY29uc29sZS9vY3NwL29jc3BfY2hlY2tfdXNlcmNlcnRfc3RhdGUuZG8wJwYIKwYBBQUHMAGGG2h0dHA6Ly8xNzIuMC4wLjE6ODAvdGVzdHVybDAKBggqgRzPVQGDdQNIADBFAiEA8njyShJt4\/DvEvFRIwusHppJT8pjm0Gu3234oVF6ovACIEKVRMxL5F\/FfyaBJOJd8T4aEWdMIrOTwrX0r+NSftx1")
typedef rapidjson::GenericValue<rapidjson::UTF8<char>> GValue;
typedef rapidjson::GenericDocument<rapidjson::UTF8<char>> GDoc;
namespace fs { using namespace std::experimental::filesystem; };

inline std::string to_utf8(const std::wstring& _str)
{
	std::string ret;
	Poco::UnicodeConverter::toUTF8(_str, ret);
	return ret;
}

inline std::wstring to_wstr(const std::string& _u8)
{
	std::wstring ret;
	Poco::UnicodeConverter::toUTF16(_u8, ret);
	return ret;
}

template<typename __Fn>
inline GDoc parseJson(__Fn _fn)
{
	using namespace Reach::ActiveX;
	using namespace rapidjson;

	CString StrJson = _fn();
	std::string u8 = to_utf8(StrJson.GetBuffer());

	std::ofstream ofs("D:/dd.txt", std::ios::app);
	ofs << u8<<std::endl;

	//CPPUNIT_ASSERT(!u8.empty());//是否收到数据
	GDoc jsonDoc;
	jsonDoc.Parse(u8.data());
	return jsonDoc;
}

bool login()
{
	using namespace rapidjson;

	//预期成功1 不带原文
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, _RS_PASSWD); });
		if (jsonDoc.HasParseError()) { return false; }
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		if (!(code&&code->IsString())) { return false; }
		std::string strCode = code->GetString();
		return strCode == "0000";
	}
}

bool logout()
{
	using namespace rapidjson;

	//预期成功1 不带原文
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CloudLogout(_RS_CONTAINER_ID); });
		if (jsonDoc.HasParseError()) { return false; }
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		if (!(code&&code->IsString())) { return false; }
		std::string strCode = code->GetString();
		return strCode == "0000";
	}
}

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

}

void InterfaceTest::testGetUserList()
{

}
void InterfaceTest::testGetCertBase64String()
{
	using namespace rapidjson;

	//预期成功1
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

	//预期成功2
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

	//预期失败1 type不符要求
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, -9); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}
}

void InterfaceTest::testGetPinRetryCount()
{

}

void InterfaceTest::testCertLogin1()
{
	using namespace rapidjson;

	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, _RS_PASSWD); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");
	}

	//预期失败1
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
	//预期成功
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

	//预期成功
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

	//预期成功
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

	//预期成功
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

	//预期成功
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

	//预期失败1
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
	//预期成功1 不带原文
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

	//预期成功2 带原文
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

	//预期失败1 container_id 不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"1", L"random-45634562456"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}

	CPPUNIT_ASSERT(logout());//TODO: logout无效
	//预期失败2 未登录
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

	//预期成功1 不带原文
	{
		//获取signedMsg
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
	//预期成功2 带原文
	{
		//获取signedMsg
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

	//预期失败1 签名值格式错误
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP7(L"1234", L"43673456547", L"1"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}

	//预期失败2 flag不符合实际
	{
		//获取signedMsg
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

	
	//预期失败3 未登录
	{
		//获取signedMsg
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
			CPPUNIT_ASSERT(logout());//TODO: logout无效
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
	
	

	//预期成功1
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		std::ofstream ofs(fs::path(inFile), std::ios::binary);
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

	//预期失败1 原文件不存在
	{
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

	//预期成功1
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		std::ofstream ofs(fs::path(inFile), std::ios::binary);
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

			std::ifstream ifs(fs::path(decryptOutFile), std::ios::binary);
			char tt[4];
			ifs.read(tt, 4);
			CPPUNIT_ASSERT(ifs);
			CPPUNIT_ASSERT(std::equal(tt, tt + 4, "1234"));
		}
	}

	//预期失败1 symKey与密文不匹配
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		std::ofstream ofs(fs::path(inFile), std::ios::binary);
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
	//预期成功1
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

	////预期失败1 待加密数据长度大于1024
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
	//预期成功1
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

	//预期失败1 密钥不符
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

	//预期失败1 密文不符
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
	//预期成功1
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

	//预期失败1 container_id 不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(L"1234", L"random-45634562456"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}

	CPPUNIT_ASSERT(logout());//TODO: logout无效
	//预期失败2 未登录
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

	//预期成功1
	{
		//获取signedMsg
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

	//预期失败1 签名证书格式错误
	{
		//获取signedMsg
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

	//预期失败2 代签名原文不符
	{
		//获取signedMsg
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

	//预期失败2 签名值不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(_RS_CERT_SIGN, L"1234", L"#^@&^$d"); });
		CPPUNIT_ASSERT(!jsonDoc.HasParseError());
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}


	//预期失败3 未登录
	{
		//获取signedMsg
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
			CPPUNIT_ASSERT(logout());//TODO: logout无效
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

}

void InterfaceTest::testKeyGetKeySn()
{

}

void InterfaceTest::testKeyGetDeviceInfo()
{

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

void InterfaceTest::testGetTransid()
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
参数：
symKey:待加密数据
certBase64:加密证书base64编码
返回：Json格式的字符串
	例：
	{"code":"0000","msg":"执行成功。","data":{"encReachKey":""}}
encReachKey:加密后的密文
功能：非对称加密数据。
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

	//预期成功
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CloudGetSignResult(L"456dfg3"); });
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode == "0000");

		const Value* signResult = GetValueByPointer(jsonDoc, "/data/signResult");
		CPPUNIT_ASSERT(signResult);
		CPPUNIT_ASSERT(signResult->IsString());

		const Value* certBase64 = GetValueByPointer(jsonDoc, "/data/certBase64");
		CPPUNIT_ASSERT(certBase64);
		CPPUNIT_ASSERT(certBase64->IsString());
	}

	//预期失败1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CloudGetSignResult(L"456dfg3"); });
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		CPPUNIT_ASSERT(code->IsString());
		std::string strCode = code->GetString();
		CPPUNIT_ASSERT(strCode != "0000");
	}

}

