#include "stdafx.h"
#include "UkeyTestAutoLogout.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UkeyTestAutoLogout, REGISTRY_NAME_AUTO_LOGOUT);
UkeyTestAutoLogout::UkeyTestAutoLogout()
{
}


UkeyTestAutoLogout::~UkeyTestAutoLogout()
{
}

void UkeyTestAutoLogout::setUp()
{
}

void UkeyTestAutoLogout::tearDown()
{
}

void UkeyTestAutoLogout::testKeyEncryptData()
{
	using namespace rapidjson;
	//Ô¤ÆÚÊ§°Ü
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyEncryptData(L"123456aAX", _RS_CERT_ENCRYPT); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(getCode(jsonDoc) == "9030");
	}
}
