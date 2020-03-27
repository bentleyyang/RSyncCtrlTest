#include "stdafx.h"
#include "MobileInterfaceTest.h"
#include "util.h"

//CPPUNIT_TEST_SUITE_REGISTRATION(MobileInterfaceTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(MobileInterfaceTest, "登录测试");


MobileInterfaceTest::MobileInterfaceTest()
{
}


MobileInterfaceTest::~MobileInterfaceTest()
{
}

void MobileInterfaceTest::setUp()
{

}

void MobileInterfaceTest::tearDown()
{

}

void MobileInterfaceTest::testGetTransid()
{
	//100020191120141710102

	using namespace rapidjson;

	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetTransid(L"1000"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto transid = getStrMember(jsonDoc, "/data/transid");
		CPPUNIT_ASSERT(transid.first);
		std::string& transidContent = transid.second;
		//CPPUNIT_ASSERT(transidContent.length() == 21);
		CPPUNIT_ASSERT(!transidContent.empty());
		CPPUNIT_ASSERT(std::all_of(transidContent.begin(), transidContent.end(), ::isdigit));
	}

	//预期失败 joinCode位数不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetTransid(L"100000000"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void MobileInterfaceTest::testCloudLoginAuth()
{

}

void MobileInterfaceTest::testCloudGetAuth()
{

}

void MobileInterfaceTest::testCloudSealAuth()
{

}

void MobileInterfaceTest::testCloudGetSealList()
{

}

void MobileInterfaceTest::testCloudSignByP7()
{

}

void MobileInterfaceTest::testCloudEncryptAuth()
{

}

void MobileInterfaceTest::testCloudEncryptData()
{

}

void MobileInterfaceTest::testCloudEncryptFile()
{

}


void MobileInterfaceTest::testEncryptDataBase64()
{

}

void MobileInterfaceTest::testEncryptFileBase64()
{

}

void MobileInterfaceTest::testCloudDevryptAuth()
{

}

void MobileInterfaceTest::testCloudDevryptData()
{

}

void MobileInterfaceTest::testCloudDevryptFile()
{

}

void MobileInterfaceTest::testCloudReceiveDevryptResult()
{

}

void MobileInterfaceTest::testCloudGetCompanyCert()
{

}

void MobileInterfaceTest::testCloudGetCertAuth()
{

}

void MobileInterfaceTest::testCloudGetCertBase64()
{

}

void MobileInterfaceTest::testCloudLogoutAuth()
{

}

void MobileInterfaceTest::testCloudLogout()
{

}



void MobileInterfaceTest::testCloudGetSignResult()
{
	using namespace rapidjson;

	//预期成功
	{
		std::wstring transid = getTransid();
		CPPUNIT_ASSERT(!transid.empty());
		GDoc jsonDoc = parseJson([&transid]()->CString {return s_pDRS_CertSafeCtrl->RS_CloudGetSignResult(transid.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
		
		auto signResult = getStrMember(jsonDoc, "/data/signResult");
		CPPUNIT_ASSERT(signResult.first);
		std::string &signResultContent = signResult.second;
		CPPUNIT_ASSERT(signResultContent == "0" || signResultContent == "1" || signResultContent == "2");

		CPPUNIT_ASSERT(hasStrMember(jsonDoc, "/data/signdMsg"));
		CPPUNIT_ASSERT(hasStrMember(jsonDoc, "/data/certBase64"));
	}

	//预期失败1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CloudGetSignResult(L"456dfdfhsdg3"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

}

