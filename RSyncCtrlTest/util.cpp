
#include "stdafx.h"
#include "util.h"



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
	return true;
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

std::wstring getTransid()
{
	//100020191120141710102

	using namespace rapidjson;
	std::wstring ret(L"");
	GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetTransid(L"1000"); });
	if (jsonDoc.HasParseError()) { return ret; }
	const Value* code = GetValueByPointer(jsonDoc, "/code");
	if (!(code&&code->IsString())) { return ret; }
	std::string strCode = code->GetString();
	if (!(strCode == "0000")) { return ret; }

	const Value* transid = GetValueByPointer(jsonDoc, "/data/transid");
	if (!(transid&&transid->IsString())) { return ret; }
	std::string transidContent = transid->GetString();
	if (!(!transidContent.empty())) { return ret; }
	if (!(std::all_of(transidContent.begin(), transidContent.end(), ::isdigit))) { return ret; }
	ret = to_wstr(transidContent);
	return ret;
}

