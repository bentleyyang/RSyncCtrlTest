#include "stdafx.h"
#include "CommonTestAuto.h"
#include <tuple>

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(CommonTestAuto, REGISTRY_NAME_AUTO_LOGIN);
CommonTestAuto::CommonTestAuto()
{
}


CommonTestAuto::~CommonTestAuto()
{
}

void CommonTestAuto::setUp()
{
	if (!login()) { AfxMessageBox(L"登录失败，测试用例可能无法进行"); }
}

void CommonTestAuto::tearDown()
{

}

void CommonTestAuto::testGetCertInfo()
{
	using namespace rapidjson;

#if 0
	//预期失败 type不符
	{
		LOG_BEG2(s_pDRS_CertSafeCtrl->RS_GetCertInfo, L"", L"1");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(getCode(jsonDoc)=="9005");
		LOG_END();FOR_END();
	}

	//预期成功
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"1"); });
		LOG_BEG2(s_pDRS_CertSafeCtrl->RS_GetCertInfo, );
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));
	}

	//预期失败 type不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L""); });
		LOG_BEG2(s_pDRS_CertSafeCtrl->RS_GetCertInfo, );
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(getCode(jsonDoc) == "9015");
	}

	//预期失败
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(L"123456", L"1"); });
		LOG_BEG2(s_pDRS_CertSafeCtrl->RS_GetCertInfo, );
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(getCode(jsonDoc) == "9006");
	}

	//预期失败
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"123456"); });
		LOG_BEG2(s_pDRS_CertSafeCtrl->RS_GetCertInfo, );
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(getCode(jsonDoc) == "9016");
	}

#endif

#if 1
	//预期失败1 type不符
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"-1");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}

	//预期失败2 证书不符
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, L"#$^%$&@fg", L"1");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}

	//预期成功1 证书版本
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"1");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功2 证书序列号
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"2");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功3 证书颁发者信息
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"5");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功4 证书拥有者信息
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"7");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功5 证书有效期
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"6");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功6 证书颁发者CN
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"33");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功7 证书颁发者O
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"34");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功8 证书颁发者OU
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"35");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功9 证书拥有者信息CN
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"49");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功10 证书拥有者信息O
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"50");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功11 证书拥有者信息OU
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"51");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功12 证书拥有者信息EMAIL
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"52");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功13 个人证书身份证号
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"53");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功14 企业统一社会信用代码
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"54");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功15 证书使用者密钥标识符
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"55");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}

	//预期成功16 证书唯一码
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetCertInfo, _RS_CERT_ENCRYPT, L"300");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		LOG_ASSERT(info&&info->IsString());
		LOG_END();FOR_END();
	}
#endif

}


void CommonTestAuto::testConfigParameters()
{
	return;
	using namespace rapidjson;

	//TODO: cmd对应的值应该填写完整

	//预期成功1
	{
		FOR();
		std::wstring valtoset = L"5673673567";
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_ConfigParameters, L"authCode", valtoset.data());
		auto res = getParameter(L"authCode");
		LOG_ASSERT(res.first);
		LOG_ASSERT(res.second==valtoset);
		LOG_END();FOR_END();
	}

	//预期成功2
	{
		FOR();
		std::wstring valtoset = L"5673673567";
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_ConfigParameters, L"rsigncloud", valtoset.data());
		auto res = getParameter(L"rsigncloud");
		LOG_ASSERT(res.first);
		LOG_ASSERT(res.second == valtoset);
		LOG_END();FOR_END();
	}

	//预期成功3
	{
		FOR();
		std::wstring valtoset = L"5673673567";
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_ConfigParameters, L"authType", valtoset.data());
		auto res = getParameter(L"authType");
		LOG_ASSERT(res.first);
		LOG_ASSERT(res.second == valtoset);
		LOG_END();FOR_END();
	}

	//预期成功4
	{
		FOR();
		std::wstring valtoset = L"5673673567";
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_ConfigParameters, L"keySn", valtoset.data());
		auto res = getParameter(L"keySn");
		LOG_ASSERT(res.first);
		LOG_ASSERT(res.second == valtoset);
		LOG_END();FOR_END();
	}

	//预期成功5
	{
		FOR();
		std::wstring valtoset = L"5673673567";
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_ConfigParameters, L"signAndVerify", valtoset.data());
		auto res = getParameter(L"signAndVerify");
		LOG_ASSERT(res.first);
		LOG_ASSERT(res.second == valtoset);
		LOG_END();FOR_END();
	}

#if UNNECISSARY_ASSERT
	//预期失败 cmd不符
	{
		std::wstring valtoset = L"5673673567";
		LOG_BEG2(s_pDRS_CertSafeCtrl->RS_ConfigParameters, L"#&&#s", valtoset.data());
		auto res = getParameter(L"#&&#s");
		LOG_ASSERT(res.first);
		LOG_ASSERT(res.second == valtoset);
		LOG_END();FOR_END();
	}

	//预期失败 cmd对应的值不符
	{
		std::wstring valtoset = L"$%*cv";
		LOG_BEG2(s_pDRS_CertSafeCtrl->RS_ConfigParameters, L"authCode", valtoset.data());
		auto res = getParameter(L"authCode");
		LOG_ASSERT(res.first);
		LOG_ASSERT(res.second == valtoset);
		LOG_END();FOR_END();
	}
#endif
}

void CommonTestAuto::testConfigParamsByBussSys()
{
	return;
	using namespace rapidjson;

	//TODO: 项目名称填写完整

	//预期成功
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_ConfigParamsByBussSys, L"bussName", L"");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}

	//预期失败 cmd不符
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_ConfigParamsByBussSys, L"@#^fdg", L"");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}

	//预期失败 项目名称不符
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_ConfigParamsByBussSys, L"bussName", L"fghsdfg");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}

void CommonTestAuto::testGetParameters()
{
	using namespace rapidjson;

	//预期成功
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetParameters, L"authCode");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* authCode = GetValueByPointer(jsonDoc, "/data/authCode");//TODO: 与文档说明的不一致
		LOG_ASSERT(authCode&&authCode->IsString());
		LOG_END();FOR_END();
	}

	//预期成功
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetParameters, L"rsigncloud");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* rsigncloud = GetValueByPointer(jsonDoc, "/data/rsigncloud");
		LOG_ASSERT(rsigncloud&&rsigncloud->IsString());
		LOG_END();FOR_END();
	}

	//预期成功
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetParameters, L"authType");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* authType = GetValueByPointer(jsonDoc, "/data/authType");
		LOG_ASSERT(authType&&authType->IsString());
		LOG_END();FOR_END();
	}

	//预期成功
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetParameters, L"keySn");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* keySn = GetValueByPointer(jsonDoc, "/data/keySn");
		LOG_ASSERT(keySn&&keySn->IsString());
		LOG_END();FOR_END();
	}

	//预期成功
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetParameters, L"signAndVerify");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* signAndVerify = GetValueByPointer(jsonDoc, "/data/signAndVerify");
		LOG_ASSERT(signAndVerify&&signAndVerify->IsString());
		LOG_END();FOR_END();
	}

	//预期失败1
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetParameters, L"");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}



void CommonTestAuto::testVerifySignByP7()
{
	using namespace rapidjson;

	auto fnGetSign = [](const std::wstring &type)->std::pair<bool, std::string> 
	{
		bool isSignSuccessful = true;
		std::string signedMsgContent;
		GDoc jsonDoc = parseJson([&type]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(TEST_DATA_W, type.data(), _RS_CONTAINER_ID); });
		isSignSuccessful = isSignSuccessful && (!hasParseError(jsonDoc));
		isSignSuccessful = isSignSuccessful && (hasCode(jsonDoc));
		isSignSuccessful = isSignSuccessful && (isSuccessful(jsonDoc));
		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		isSignSuccessful = isSignSuccessful && (signdMsg&&signdMsg->IsString());
		signedMsgContent = signdMsg->GetString();
		return { isSignSuccessful, signedMsgContent };
	};
	
	//预期成功1 不带原文
	{
		auto signRes = fnGetSign(L"1");//获取signedMsg
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_VerifySignByP7, TEST_DATA_W, to_wstr(signRes.second).data(), L"1");
		LOG_ASSERT(signRes.first);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
	//预期成功2 带原文
	{
		auto signRes = fnGetSign(L"0");//获取signedMsg
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_VerifySignByP7, TEST_DATA_W, to_wstr(signRes.second).data(), L"0");
		LOG_ASSERT(signRes.first);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}

	//预期失败1 签名值格式错误
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_VerifySignByP7, TEST_DATA_W, L"43673456547", L"1");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}

	//预期失败2 flag不符合实际
	{
		auto signRes = fnGetSign(L"1");//获取signedMsg
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_VerifySignByP7, L"", to_wstr(signRes.second).data(), L"0");
		LOG_ASSERT(signRes.first);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}

void CommonTestAuto::testEncryptFile()
{
	using namespace rapidjson;



	//预期成功1
	{
		bool isFileCreated = true;
		std::wstring inFile = to_wstr(Poco::Path::current()) + L"test_encrypt_file_in.txt";
		std::wstring outFile = to_wstr(Poco::Path::current()) + L"test_encrypt_file_out.txt";
		Poco::FileStream ofs(to_u8(inFile), std::ios::binary);
		isFileCreated = isFileCreated && (ofs);
		ofs.write(TEST_DATA, sizeof(TEST_DATA)-1);
		isFileCreated = isFileCreated && (ofs);
		ofs.close();
		isFileCreated = isFileCreated && (Poco::File(to_u8(inFile)).exists());
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_EncryptFile, inFile.data(), outFile.data());
		LOG_ASSERT(isFileCreated);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		LOG_ASSERT(symKey&&symKey->IsString());
		LOG_ASSERT(Poco::File(to_u8(outFile)).exists());
		LOG_END();FOR_END();
	}

	//预期失败1 原文件不存在
	{
		//TODO: 这里是直接收到空数据，没有code
		bool isFileNotCreated = true;
		std::wstring inFile = L"C:/agag2342sdfgsfg";
		std::wstring outFile = to_wstr(Poco::Path::current()) + L"test_encrypt_file_out.txt";
		isFileNotCreated = isFileNotCreated && (!Poco::File(to_u8(inFile)).exists());

		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_EncryptFile, inFile.data(), outFile.data());
		LOG_ASSERT(isFileNotCreated);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}

void CommonTestAuto::testDevryptFile()
{
	using namespace rapidjson;

	auto fn = []()->std::tuple<bool, std::wstring, std::string> 
	{
		bool isCreatedFile = true;
		std::wstring inFile = to_wstr(Poco::Path::current()) + L"test_encrypt_file_in.txt";
		std::wstring outFile = to_wstr(Poco::Path::current()) + L"test_encrypt_file_out.txt";
		Poco::FileStream ofs(to_u8(inFile), std::ios::binary);
		isCreatedFile = isCreatedFile && (ofs);
		ofs.write(TEST_DATA, sizeof(TEST_DATA) - 1);
		isCreatedFile = isCreatedFile && (ofs);
		ofs.close();
		isCreatedFile = isCreatedFile && (Poco::File(to_u8(inFile)).exists());
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFile(inFile.data(), outFile.data()); });
		isCreatedFile = isCreatedFile && (!hasParseError(jsonDoc));
		isCreatedFile = isCreatedFile && (hasCode(jsonDoc));
		isCreatedFile = isCreatedFile && (isSuccessful(jsonDoc));

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		isCreatedFile = isCreatedFile && (symKey&&symKey->IsString());
		isCreatedFile = isCreatedFile && (Poco::File(to_u8(outFile)).exists());
		return { isCreatedFile, outFile, isCreatedFile ? symKey->GetString() : "" };
	};
	//预期成功1
	{
		auto encryptInfo = fn();
		bool isEncrypted = std::get<0>(encryptInfo);
		std::wstring outFile = std::get<1>(encryptInfo);
		std::string symkey = std::get<2>(encryptInfo);
		std::wstring decryptOutFile = to_wstr(Poco::Path::current()) + L"test_decrypt_file_out.txt";
		//LOG_ASSERT(copy_file(path(outFile), path(decryptInFile), copy_options::overwrite_existing));
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_DevryptFile, to_wstr(symkey).data(), outFile.data(), decryptOutFile.data());
		LOG_ASSERT(isEncrypted);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));
		LOG_ASSERT(Poco::File(to_u8(decryptOutFile)).exists());

		Poco::FileInputStream ifs(to_u8(decryptOutFile), std::ios::binary);
		char tt[sizeof(TEST_DATA) - 1];
		ifs.read(tt, sizeof(TEST_DATA) - 1);
		LOG_ASSERT(ifs);
		LOG_ASSERT(std::equal(tt, tt + (sizeof(TEST_DATA) - 1), TEST_DATA));

		//TODO: 这里测试的结果，源文件只有4个字节长度，解密后的文件，虽然前4个字节是正确的，但是整个文件会强制变成128字节，并且后面的是乱码
		LOG_ASSERT(Poco::File(to_u8(decryptOutFile)).getSize() == (sizeof(TEST_DATA) - 1));
		LOG_END();FOR_END();
	}

	//预期失败1 symKey与密文不匹配
	{
		auto encryptInfo = fn();
		bool isEncrypted = std::get<0>(encryptInfo);
		std::wstring outFile = std::get<1>(encryptInfo);
		std::string symkey = std::get<2>(encryptInfo);
		std::wstring decryptOutFile = to_wstr(Poco::Path::current()) + L"test_decrypt_file_out.txt";
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_DevryptFile, L"astgagh#$%^$#@^afhsha", outFile.data(), decryptOutFile.data());
		LOG_ASSERT(isEncrypted);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}

void CommonTestAuto::testEncryptData()
{
	using namespace rapidjson;
	//预期成功1
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_EncryptData, TEST_DATA_W);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		LOG_ASSERT(symKey&&symKey->IsString());
		std::string symKeyContent = symKey->GetString();

		const Value* encDataStr = GetValueByPointer(jsonDoc, "/data/encDataStr");
		LOG_ASSERT(encDataStr&&encDataStr->IsString());
		std::string encDataStrContent = encDataStr->GetString();
		LOG_END();FOR_END();
	}

	////预期失败1 待加密数据长度大于1024
	//{
	//	std::vector<wchar_t> tt(1024, L'A' ); tt[1023] = L'\0';
	//
	//	GDoc jsonDoc = parseJson([&tt]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(tt.data()); });
	//	LOG_ASSERT(!parseError(jsonDoc));
	//	const Value* code = GetValueByPointer(jsonDoc, "/code");
	//	LOG_ASSERT(code&&code->IsString());
	//	std::string strCode = code->GetString();
	//	LOG_ASSERT(strCode != "0000");
	//}
}

void CommonTestAuto::testDevryptData()
{
	using namespace rapidjson;

	auto fn = []()->std::tuple<bool, std::string, std::string> 
	{
		bool isEncrypted = true;
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(TEST_DATA_W); });
		isEncrypted = isEncrypted && (!hasParseError(jsonDoc));
		isEncrypted = isEncrypted && (hasCode(jsonDoc));
		isEncrypted = isEncrypted && (isSuccessful(jsonDoc));

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		isEncrypted = isEncrypted && (symKey&&symKey->IsString());
		std::string symKeyContent = symKey->GetString();

		const Value* encDataStr = GetValueByPointer(jsonDoc, "/data/encDataStr");
		isEncrypted = isEncrypted && (encDataStr&&encDataStr->IsString());
		std::string encDataStrContent = encDataStr->GetString();
		return { isEncrypted, isEncrypted ? symKeyContent : "", isEncrypted ? encDataStrContent : "" };
	};
	//预期成功1
	{
		auto encryptInfo = fn();
		bool isEncrypt = std::get<0>(encryptInfo);
		std::string symkey = std::get<1>(encryptInfo);
		std::string encDataStr = std::get<2>(encryptInfo);
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_DevryptData, to_wstr(symkey).data(), to_wstr(encDataStr).data());
		LOG_ASSERT(isEncrypt);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* dncDataStr = GetValueByPointer(jsonDoc, "/data/dncDataStr");
		std::string dncDataContent = dncDataStr->GetString();
		LOG_ASSERT(dncDataContent == TEST_DATA);
		LOG_END();FOR_END();
	}

	//预期失败1 密钥不符
	{
		auto encryptInfo = fn();
		bool isEncrypt = std::get<0>(encryptInfo);
		std::string symkey = std::get<1>(encryptInfo);
		std::string encDataStr = std::get<2>(encryptInfo);
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_DevryptData, L"$%^FGH", to_wstr(encDataStr).data());
		LOG_ASSERT(isEncrypt);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}

	//预期失败1 密文不符
	{
		auto encryptInfo = fn();
		bool isEncrypt = std::get<0>(encryptInfo);
		std::string symkey = std::get<1>(encryptInfo);
		std::string encDataStr = std::get<2>(encryptInfo);
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_DevryptData, to_wstr(symkey).data(), L"4321");
		LOG_ASSERT(isEncrypt);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}
