#include "stdafx.h"
#include "UkeyTestManual.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UkeyTestManual, REGISTRY_NAME_MANUAL_LOGIN);
UkeyTestManual::UkeyTestManual()
{
}


UkeyTestManual::~UkeyTestManual()
{
}

void UkeyTestManual::setUp()
{
}

void UkeyTestManual::tearDown()
{
}

void UkeyTestManual::testCertLoginNoPwd()
{
	return;
	using namespace rapidjson;

	//Ô¤ÆÚ³É¹¦1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		const Value* code = GetValueByPointer(jsonDoc, "/code");
		CPPUNIT_ASSERT(code&&code->IsString());
		std::string strCode = code->GetString();
		//CPPUNIT_ASSERT(strCode == "0000");
	}
}