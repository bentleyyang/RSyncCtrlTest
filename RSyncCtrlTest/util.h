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
#include "rapidjson/prettywriter.h"

#include "filesystem.hpp"
#include "convert.hpp"
#include "json.h"
#include "flossy.h"


std::pair<bool, std::wstring> getParameter(const std::wstring& cmd);
bool setParameter(const std::wstring& cmd, const std::wstring& val);
std::pair<bool, std::wstring> getCertBase64(const std::wstring& containerId, short type);
bool getUserlist(std::vector<std::pair<std::wstring, std::wstring>>& dst);
bool login();
bool login(const std::wstring& pw);
bool logout();
std::wstring getTransid();
std::wstring getLoginToken();
std::wstring getEncryptToken();
std::wstring getDecryptToken();
std::wstring getSealToken();
std::wstring getCertToken();

struct seal {
	std::wstring keySn;
	std::wstring signSn;
	std::wstring certBase64;
};
std::pair<bool, std::vector<seal>> getSealList();

bool encryptAuth();
bool logoutAuth(const std::wstring& token);

inline std::string jsonDocToStr(const GDoc& doc)
{
	assert(!doc.HasParseError());
	rapidjson::GenericStringBuffer<rapidjson::UTF8<char>> buffer;
	rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>>> writer(buffer);
	doc.Accept(writer);
	return buffer.GetString();
}

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

inline std::string getCode(const GDoc & _doc)
{
	using namespace rapidjson;
	const Value* code = GetValueByPointer(_doc, "/code");
	if (!(code&&code->IsString())) { return ""; }
	return code->GetString();
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

inline GDoc parseJson(CString &StrJson)
{
	using namespace rapidjson;
	std::string u8 = to_u8(StrJson.GetBuffer());

	fs::ofstream ofs(fs::current_path().append(L"/recv_log.txt"), std::ios::app);
	ofs << u8 << "\n";

	//CPPUNIT_ASSERT(!u8.empty());//是否收到数据
	GDoc jsonDoc;
	jsonDoc.Parse(u8.data());
	return jsonDoc;
}

template<typename __Fn>
inline GDoc parseJson(__Fn _fn)
{
	using namespace rapidjson;

	CString StrJson = _fn();
	std::string u8 = to_u8(StrJson.GetBuffer());

	fs::ofstream ofs(fs::current_path().append(L"/recv_log.txt"), std::ios::app);
	ofs << u8 << "\n";

	//CPPUNIT_ASSERT(!u8.empty());//是否收到数据
	GDoc jsonDoc;
	jsonDoc.Parse(u8.data());
	return jsonDoc;
}

template<typename __Fn, typename CharType, size_t N>
inline std::pair<bool, std::string> parseJsonAndGetMember(__Fn _fn, const CharType(&_member_name)[N])
{
	using namespace rapidjson;

	CString StrJson = _fn();
	std::string u8 = to_u8(StrJson.GetBuffer());

	fs::ofstream ofs(fs::current_path().append(L"/recv_log.txt"), std::ios::app);
	ofs << u8 << "\n";

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
