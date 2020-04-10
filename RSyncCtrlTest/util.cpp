
#include "stdafx.h"
#include "util.h"



std::pair<bool, std::wstring> getParameter(const std::wstring & cmd)
{
	GDoc jsonDoc = parseJson([&cmd]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(cmd.data()); });
	if (hasParseError(jsonDoc)) { return { false, L"" }; }
	if (!isSuccessful(jsonDoc)) { return { false, L"" }; }
	if(!jsonDoc.HasMember("data")) { return { false, L"" }; }
	if (!jsonDoc["data"].HasMember(to_u8(cmd).data())) { return { false, L"" }; }

	return { true, to_wstr(jsonDoc["data"][to_u8(cmd).data()].GetString()) };
}

bool setParameter(const std::wstring & cmd, const std::wstring & val)
{
	GDoc jsonDoc = parseJson([&cmd, &val]()->CString {return s_pDRS_CertSafeCtrl->RS_ConfigParameters(cmd.data(), val.data()); });
	//if (hasParseError(jsonDoc)) { return false; }
	//if (!isSuccessful(jsonDoc)) { return false; }

	return true;
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
		std::pair<bool, std::string> userlist;
		try {
			userlist = parseJsonAndGetMember([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetUserList(); }, "/data/userlist");
		}
		catch (std::exception& e) { return false; }
		
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

std::wstring getLoginToken()
{
	using namespace rapidjson;
	std::wstring ret(L"");

#if 1
	ret = m_TokenLogin;
#else
#endif

	return ret;
}

std::wstring getEncryptToken()
{
	using namespace rapidjson;
	std::wstring ret(L"");

#if 1
	ret = m_TokenEncrypt;
#else
#endif
	
	return ret;
}

std::wstring getDecryptToken()
{
	using namespace rapidjson;
	std::wstring ret(L"");

#if 1
	ret = m_TokenDecrypt;
#else
#endif

	return ret;
}

std::wstring getSealToken()
{
	using namespace rapidjson;
	std::wstring ret(L"");

#if 1
	ret = m_TokenSeal;
#else
#endif

	return ret;
}

std::wstring getCertToken()
{
	using namespace rapidjson;
	std::wstring ret(L"");

#if 1
	ret = m_TokenCert;
#else
#endif

	return ret;
}

std::pair<bool, std::vector<seal>> getSealList()
{
	using namespace rapidjson;
	std::vector<seal> ret(0);
	std::wstring token = getSealToken();
	GDoc jsonDoc;
	try
	{
		jsonDoc = parseJson([&token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetSealList(token.data()); });
	}
	catch (const std::exception&)
	{
		return { false, ret };
	}
	
	if (hasParseError(jsonDoc)|| !isSuccessful(jsonDoc))
	{
		return { false, ret };
	}

	const Value* data = GetValueByPointer(jsonDoc, "/data");
	if (!data || !data->IsArray()) { return { false, ret }; }
	auto dataContent = data->GetArray();
	for (const auto& elm : dataContent)
	{
		if (!elm.HasMember("keySn")
			|| !elm.HasMember("signSn")
			|| !elm.HasMember("certBase64")) {
			return { false, std::vector<seal>(0) };
		}
		
		ret.emplace_back(seal{ to_wstr(elm["keySn"].GetString()),to_wstr(elm["signSn"].GetString()),to_wstr(elm["certBase64"].GetString()) });
	}
	return { true, ret };
}

bool encryptAuth()
{
	//TODO: 生成二维码，并弹出对话框扫二维码，然后轮询结果？
	//TODO: 能否提供模拟手机扫码动作的接口？
	using namespace rapidjson;
	std::wstring transId = getTransid();
	if (transId.empty()) { return false; }

	
	GDoc jsonDoc = parseJson([&transId]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudEncryptAuth(transId.data()); });
	if (hasParseError(jsonDoc))
	{
		return false;
	}
	if (!isSuccessful(jsonDoc))
	{
		return false;
	}

	auto action = getStrMember(jsonDoc, "/data/action");
	if (!action.first) { return false; }
	std::string& actionContent = action.second;

	auto authIdent = getStrMember(jsonDoc, "/data/authIdent");
	if (!authIdent.first) { return false; }
	std::string& authIdentContent = authIdent.second;
	return true;
}

bool logoutAuth(const std::wstring & token)
{
	using namespace rapidjson;

	GDoc jsonDoc = parseJson([&token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudLogoutAuth(token.data()); });
	if (hasParseError(jsonDoc))
	{
		return false;
	}
	if (!isSuccessful(jsonDoc))
	{
		return false;
	}
	return true;
}

