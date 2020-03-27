
#include "stdafx.h"
#include "util.h"



std::pair<bool, std::wstring> getParameter(const std::wstring & cmd)
{
	GDoc jsonDoc = parseJson([&cmd]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(cmd.data()); });
	if (hasParseError(jsonDoc)) { return { false, L"" }; }
	if (!isSuccessful(jsonDoc)) { return { false, L"" }; }
	if(!jsonDoc.HasMember("data")) { return { false, L"" }; }
	if (!jsonDoc["data"].HasMember(to_utf8(cmd).data())) { return { false, L"" }; }

	return { true, to_wstr(jsonDoc["data"][to_utf8(cmd).data()].GetString()) };
}

std::pair<bool, std::wstring> getCertBase64(const std::wstring & containerId, short type)
{
	auto cert = parseJsonAndGetMember([&containerId, type]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(containerId.data(), type); }, "/data/certBase64");
	if (!cert.first) { return { false, L"" }; }

	return { true, to_wstr(cert.second) };
}

bool getUserlist(std::vector<std::pair<std::wstring, std::wstring>>& dst)
{
	using namespace rapidjson;

	//预期成功1 不带原文
	{
		auto userlist=parseJsonAndGetMember([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetUserList(); }, "/data/userlist");
		if (!userlist.first) { return false; }

		std::vector<std::wstring> tmp;
		std::vector<std::wstring> tmp2;
		split<wchar_t>(to_wstr(userlist.second), tmp, L"&&&");
		for (auto& el : tmp)
		{
			tmp2.clear();
			split<wchar_t>(el, tmp2, L"||");
			if (!(tmp2.size() != 2 || tmp2[0].empty() || tmp2[1].empty()))
			{
				dst.push_back({ tmp2[0], tmp2[1] });
			}
		}
	}
	return true;
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

bool login(const std::wstring& pw)
{
	using namespace rapidjson;

	//预期成功1 不带原文
	{
		GDoc jsonDoc = parseJson([&pw]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, pw.data()); });
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

