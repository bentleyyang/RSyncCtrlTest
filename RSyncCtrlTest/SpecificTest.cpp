#include "stdafx.h"
#include "SpecificTest.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(SpecificTest, "其它");
SpecificTest::SpecificTest()
{
}


SpecificTest::~SpecificTest()
{
}

void SpecificTest::setUp()
{
}

void SpecificTest::tearDown()
{
}

void SpecificTest::testGetUserListNoKey()
{
#if TEST_WITH_INFO_POPUP
	AfxMessageBox(L"请确保移除所有key后继续");
#endif
	using namespace rapidjson;
	//预期失败
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetUserList(); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(getCode(jsonDoc)=="9001");
	}

}

void SpecificTest::testGetUserListTwoKey()
{
#if TEST_WITH_INFO_POPUP
	AfxMessageBox(L"请确保同时插入2把key后继续");
#endif
	using namespace rapidjson;
	//预期失败
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetUserList(); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(getCode(jsonDoc) == "9002");
	}
}

void SpecificTest::testGetUserListCloseDev()
{
#if TEST_WITH_INFO_POPUP
	AfxMessageBox(L"请确保关闭设备后继续");
#endif
	using namespace rapidjson;
	//预期失败
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetUserList(); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(getCode(jsonDoc) == "9008");
	}
}

void SpecificTest::testCertLoginNoKey()
{
#if TEST_WITH_INFO_POPUP
	AfxMessageBox(L"请确保移除所有key后继续");
#endif
	using namespace rapidjson;

	//预期失败1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, _RS_PASSWD); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(getCode(jsonDoc) == "9001");
	}
}

void SpecificTest::testCertLoginTwoKey()
{
#if TEST_WITH_INFO_POPUP
	AfxMessageBox(L"请确保同时插入2把key后继续");
#endif
	using namespace rapidjson;

	//预期失败1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, _RS_PASSWD); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(getCode(jsonDoc) == "9002");
	}
}

void SpecificTest::testGetCertBase64StringNoKey()
{
#if TEST_WITH_INFO_POPUP
	AfxMessageBox(L"请确保移除所有key后继续");
#endif
	using namespace rapidjson;
	//预期失败
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, 1); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(getCode(jsonDoc) == "9001");
	}
}

void SpecificTest::testGetCertBase64StringTwoKey()
{
#if TEST_WITH_INFO_POPUP
	AfxMessageBox(L"请确保同时插入2把key后继续");
#endif
	using namespace rapidjson;
	//预期失败
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, 1); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(getCode(jsonDoc) == "9002");
}
}

void SpecificTest::testKeyGetKeySnNoKey()
{
#if TEST_WITH_INFO_POPUP
	AfxMessageBox(L"请确保移除所有key后继续");
#endif
	using namespace rapidjson;
	//预期失败
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyGetKeySn(); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(getCode(jsonDoc) == "9001");
	}
}

void SpecificTest::testKeyGetKeySnTwoKey()
{
#if TEST_WITH_INFO_POPUP
	AfxMessageBox(L"请确保同时插入2把key后继续");
#endif
	using namespace rapidjson;
	//预期失败
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyGetKeySn(); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(getCode(jsonDoc) == "9002");
	}
}
