#pragma once

#ifndef RSYNCCTRLTEST_UTIL
#define RSYNCCTRLTEST_UTIL

#include <experimental/filesystem>
#include <fstream>
#include <vector>

#include "Poco/UnicodeConverter.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/pointer.h"

#include "Utility.h"

#define _RS_CONTAINER_ID (m_ContainerId.GetBuffer())
#define _RS_PASSWD (m_PassWord.GetBuffer())
#define _RS_AUTH_CODE (m_AuthCode.GetBuffer())
#define _RS_CERT_ENCRYPT (m_CertEncrypt.GetBuffer())
#define _RS_CERT_SIGN (m_CertSign.GetBuffer())

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

template<typename __Ch>
void split(const std::basic_string<__Ch>& s, std::vector<std::basic_string<__Ch>>& tokens
	, const std::basic_string<__Ch>& delimiters)
{
	std::string::size_type lastPos = s.find_first_not_of(delimiters, 0);
	std::string::size_type pos = s.find_first_of(delimiters, lastPos);
	while (std::string::npos!=pos||std::string::npos!=lastPos)
	{
		tokens.emplace_back(s.substr(lastPos, pos - lastPos));
		lastPos = s.find_first_not_of(delimiters, pos);
		pos = s.find_first_of(delimiters, lastPos);
	}
}

template<typename __Fn>
inline GDoc parseJson(__Fn _fn)
{
	using namespace Reach::ActiveX;
	using namespace rapidjson;

	CString StrJson = _fn();
	std::string u8 = to_utf8(StrJson.GetBuffer());

	std::ofstream ofs(fs::current_path().append(L"/recv_log.txt"), std::ios::app);
	ofs << u8 << std::endl;

	//CPPUNIT_ASSERT(!u8.empty());//是否收到数据
	GDoc jsonDoc;
	jsonDoc.Parse(u8.data());
	return jsonDoc;
}

std::pair<bool, std::wstring> getParameter(const std::wstring& cmd);
std::pair<bool, std::wstring> getCertBase64(const std::wstring& containerId, short type);
bool getUserlist(std::vector<std::pair<std::wstring, std::wstring>>& dst);
bool login();
bool login(const std::wstring& pw);

bool logout();

std::wstring getTransid();

inline bool hasParseError(const GDoc & _doc)
{
	return _doc.HasParseError();
}

inline bool hasCode(const GDoc & _doc)
{
	using namespace rapidjson;
	const Value* code = GetValueByPointer(_doc, "/code");
	if (!(code&&code->IsString())) { return false; }
	return true;
}

inline bool isSuccessful(const GDoc & _doc)
{
	using namespace rapidjson;
	const Value* code = GetValueByPointer(_doc, "/code");
	if (!(code&&code->IsString())) { return false; }
	if (!(std::string(code->GetString()) == "0000")) { return false; }
	return true;
}

template <typename CharType, size_t N>
bool hasStrMember(const GDoc& _doc, const CharType(&_member_name)[N])
{
	using namespace rapidjson;
	const Value* o = GetValueByPointer(_doc, _member_name);
	if (!(o&&o->IsString())) { return false; }
	return true;
}

template <typename CharType, size_t N>
std::pair<bool, std::string> getStrMember(const GDoc& _doc, const CharType(&_member_name)[N])
{
	using namespace rapidjson;
	const Value* o = GetValueByPointer(_doc, _member_name);
	if (!(o&&o->IsString())) { return { false, "" }; }
	return { true, o->GetString() };
}

template<typename __Fn, typename CharType, size_t N>
inline std::pair<bool, std::string> parseJsonAndGetMember(__Fn _fn, const CharType(&_member_name)[N])
{
	using namespace Reach::ActiveX;
	using namespace rapidjson;

	CString StrJson = _fn();
	std::string u8 = to_utf8(StrJson.GetBuffer());

	std::ofstream ofs(fs::current_path().append(L"/recv_log.txt"), std::ios::app);
	ofs << u8 << std::endl;

	//CPPUNIT_ASSERT(!u8.empty());//是否收到数据
	GDoc jsonDoc;
	jsonDoc.Parse(u8.data());
	if (jsonDoc.HasParseError()) { return {false, ""}; }

	if (!isSuccessful(jsonDoc)) { return { false, "" }; }

	const Value* o = GetValueByPointer(jsonDoc, _member_name);
	if (!(o&&o->IsString())) { return { false, "" }; }
	return { true, o->GetString() };
}

#endif // !RSYNCCTRLTEST_UTIL
