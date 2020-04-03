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

//ע����Ӧ�ӿڵ�Ȩ��
void MobileTestManual::testCloudLogoutAuth()
{
	using namespace rapidjson;
	std::wstring token = getLoginToken();
	CPPUNIT_ASSERT(!token.empty());

	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([&token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudLogoutAuth(token.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ�� token����
	{
		GDoc jsonDoc = parseJson([&token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudLogoutAuth(L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//ע����¼
void MobileTestManual::testCloudLogout()
{

}