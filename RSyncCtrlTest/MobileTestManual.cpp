#include "stdafx.h"
#include "MobileTestManual.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(MobileTestManual, REGISTRY_NAME_MANUAL_LOGIN);
MobileTestManual::MobileTestManual()
{
}


MobileTestManual::~MobileTestManual()
{
}

void MobileTestManual::setUp()
{
}

void MobileTestManual::tearDown()
{
}

//注销相应接口的权限
void MobileTestManual::testCloudLogoutAuth()
{
	using namespace rapidjson;
	std::wstring token = getLoginToken();
	CPPUNIT_ASSERT(!token.empty());

	//预期成功
	{
		GDoc jsonDoc = parseJson([&token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudLogoutAuth(token.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//预期失败 token错误
	{
		GDoc jsonDoc = parseJson([&token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudLogoutAuth(L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//注销登录
void MobileTestManual::testCloudLogout()
{

}