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

#define _RS_CONTAINER_ID (L"F5BA5CE5-BC9A-49C8-AE47-1825115058D7")
#define _RS_PASSWD (L"12345678")
#define _RS_AUTH_CODE (L"")
#define _RS_CERT_ENCRYPT (L"MIID8jCCA5igAwIBAgILIPOoHk2h3atHMfEwCgYIKoEcz1UBg3UwYjELMAkGA1UEBhMCQ04xJDAiBgNVBAoMG05FVENBIENlcnRpZmljYXRlIEF1dGhvcml0eTEtMCsGA1UEAwwkTkVUQ0EgU00yIFRFU1QwMSBhbmQgRXZhbHVhdGlvbiBDQTAxMB4XDTE5MTEwMTA0NTgyNloXDTI0MTEwMTA0NTgyNlowgdExCzAJBgNVBAYTAkNOMQ8wDQYDVQQIDAZGdWppYW4xMzAxBgNVBAcMKuemj+W7uuecgeemj+W3nuW4gum8k+alvOWMuua5luS4nOi3rzE4OOWPtzE9MDsGA1UECgw056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMu+8iTE9MDsGA1UEAww056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMu+8iTBZMBMGByqGSM49AgEGCCqBHM9VAYItA0IABJ1jTugwIT4TlNF2IxsxVxv\/exGmo+Io3Upj\/SJv+epJQgo5ehOjD\/jAMZq413KCqF41gIaS7Ec3BSVNXJsWjvOjggHDMIIBvzAMBgNVHRMBAf8EAjAAMB0GA1UdDgQWBBT8CyNZp3dl6nPw8AoQTyAVLBKlGDAfBgNVHSMEGDAWgBQMe+ticwN1+oxKJAz2jzshZX4X6TBrBgNVHSAEZDBiMGAGCisGAQQBgZJIDQowUjBQBggrBgEFBQcCARZEaHR0cDovL3d3dy5jbmNhLm5ldC9jcy9rbm93bGVkZ2Uvd2hpdGVwYXBlci9jcHMvbmV0Q0F0ZXN0Y2VydGNwcy5wZGYwMwYDVR0fBCwwKjAooCagJIYiaHR0cDovL3Rlc3QuY25jYS5uZXQvY3JsL1NNMkNBLmNybDAOBgNVHQ8BAf8EBAMCAzgwNAYKKwYBBAGBkkgBDgQmDCQ1MjE2MDc4NmMwYTM3MmZjOGMzMzBhMDJiMTZjYmE2M0BTMDIwgYYGCCsGAQUFBwEBBHoweDBNBggrBgEFBQcwAYZBaHR0cDovLzE5Mi4xNjguMC43OS9vY3NwY29uc29sZS9vY3NwL29jc3BfY2hlY2tfdXNlcmNlcnRfc3RhdGUuZG8wJwYIKwYBBQUHMAGGG2h0dHA6Ly8xNzIuMC4wLjE6ODAvdGVzdHVybDAKBggqgRzPVQGDdQNIADBFAiBUQE+fdAD1eH6OyCuSURjv\/vp+x0MYv8Hkh8S4Ks\/svQIhANdkoJyTiNlij5wckuzhWDJLokcGIyup+y5JYS4xmt7D")

#define _RS_CERT_SIGN (L"MIID8jCCA5igAwIBAgILENzv3NBdilQmXGUwCgYIKoEcz1UBg3UwYjELMAkGA1UEBhMCQ04xJDAiBgNVBAoMG05FVENBIENlcnRpZmljYXRlIEF1dGhvcml0eTEtMCsGA1UEAwwkTkVUQ0EgU00yIFRFU1QwMSBhbmQgRXZhbHVhdGlvbiBDQTAxMB4XDTE5MTEwMTA0NTgyNloXDTI0MTEwMTA0NTgyNlowgdExCzAJBgNVBAYTAkNOMQ8wDQYDVQQIDAZGdWppYW4xMzAxBgNVBAcMKuemj+W7uuecgeemj+W3nuW4gum8k+alvOWMuua5luS4nOi3rzE4OOWPtzE9MDsGA1UECgw056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMu+8iTE9MDsGA1UEAww056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMu+8iTBZMBMGByqGSM49AgEGCCqBHM9VAYItA0IABJPDjH4qPGIXcKopl6CYXTOqOAE2dmRchTE3TTlDtg7zTPFbe\/fOUFj+zlkUfrLWwopPAJOCA0cG\/ufkffHbhjejggHDMIIBvzAMBgNVHRMBAf8EAjAAMB0GA1UdDgQWBBQJVOszT+dSIPLoT8mIVl01gK37OTAfBgNVHSMEGDAWgBQMe+ticwN1+oxKJAz2jzshZX4X6TBrBgNVHSAEZDBiMGAGCisGAQQBgZJIDQowUjBQBggrBgEFBQcCARZEaHR0cDovL3d3dy5jbmNhLm5ldC9jcy9rbm93bGVkZ2Uvd2hpdGVwYXBlci9jcHMvbmV0Q0F0ZXN0Y2VydGNwcy5wZGYwMwYDVR0fBCwwKjAooCagJIYiaHR0cDovL3Rlc3QuY25jYS5uZXQvY3JsL1NNMkNBLmNybDAOBgNVHQ8BAf8EBAMCBsAwNAYKKwYBBAGBkkgBDgQmDCQ1MjE2MDc4NmMwYTM3MmZjOGMzMzBhMDJiMTZjYmE2M0BTMDIwgYYGCCsGAQUFBwEBBHoweDBNBggrBgEFBQcwAYZBaHR0cDovLzE5Mi4xNjguMC43OS9vY3NwY29uc29sZS9vY3NwL29jc3BfY2hlY2tfdXNlcmNlcnRfc3RhdGUuZG8wJwYIKwYBBQUHMAGGG2h0dHA6Ly8xNzIuMC4wLjE6ODAvdGVzdHVybDAKBggqgRzPVQGDdQNIADBFAiEA8njyShJt4\/DvEvFRIwusHppJT8pjm0Gu3234oVF6ovACIEKVRMxL5F\/FfyaBJOJd8T4aEWdMIrOTwrX0r+NSftx1")
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

bool login();

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
