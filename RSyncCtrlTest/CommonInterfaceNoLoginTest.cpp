#include "stdafx.h"
#include "CommonInterfaceNoLoginTest.h"
#include "util.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(CommonInterfaceNoLoginTest, "无登录测试(拔掉key)");

CommonInterfaceNoLoginTest::CommonInterfaceNoLoginTest()
{
}


CommonInterfaceNoLoginTest::~CommonInterfaceNoLoginTest()
{
}

void CommonInterfaceNoLoginTest::setUp()
{

}

void CommonInterfaceNoLoginTest::tearDown()
{

}

void CommonInterfaceNoLoginTest::testGetCertInfo()
{
	using namespace rapidjson;

	//预期失败
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"1"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

}


void CommonInterfaceNoLoginTest::testConfigParameters()
{
}

void CommonInterfaceNoLoginTest::testConfigParamsByBussSys()
{
}

void CommonInterfaceNoLoginTest::testGetParameters()
{
	using namespace rapidjson;

	//预期失败
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(L"authCode"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}



void CommonInterfaceNoLoginTest::testVerifySignByP7()
{
	using namespace rapidjson;

	//预期失败 未登录
	{
		//获取signedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(L"1234", L"1", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			CPPUNIT_ASSERT(logout());//TODO: logout无效
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP7(L"1234", to_wstr(signedMsgContent).data(), L"1"); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
		}
	}
}

void CommonInterfaceNoLoginTest::testEncryptFile()
{
	using namespace rapidjson;



	//预期成功1
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		std::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write("1234", 4);
		CPPUNIT_ASSERT(ofs);
		ofs.close();
		CPPUNIT_ASSERT(fs::exists(inFile));
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFile(inFile.data(), outFile.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		CPPUNIT_ASSERT(fs::exists(outFile));
	}

	//预期失败1 原文件不存在
	{
		//TODO: 这里是直接收到空数据，没有code
		std::wstring inFile = L"C:/agag2342sdfgsfg";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		CPPUNIT_ASSERT(!fs::exists(inFile));
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFile(inFile.data(), outFile.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void CommonInterfaceNoLoginTest::testDevryptFile()
{
	using namespace rapidjson;

	//预期成功1
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		std::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write("1234", 4);
		CPPUNIT_ASSERT(ofs);
		ofs.close();
		CPPUNIT_ASSERT(fs::exists(inFile));
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFile(inFile.data(), outFile.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		CPPUNIT_ASSERT(fs::exists(outFile));

		//
		{
			//std::wstring decryptInFile = std::experimental::filesystem::current_path().wstring() + L"/test_decrypt_file_in.sm4";
			std::wstring decryptOutFile = fs::current_path().wstring() + L"/test_decrypt_file_out.txt";
			//CPPUNIT_ASSERT(copy_file(path(outFile), path(decryptInFile), copy_options::overwrite_existing));
			GDoc jsonDoc = parseJson([&decryptOutFile, &symKey, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_DevryptFile(to_wstr(symKey->GetString()).data(), outFile.data(), decryptOutFile.data()); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(isSuccessful(jsonDoc));
			CPPUNIT_ASSERT(fs::exists(decryptOutFile));



			std::ifstream ifs(fs::path(decryptOutFile), std::ios::binary);
			char tt[4];
			ifs.read(tt, 4);
			CPPUNIT_ASSERT(ifs);
			CPPUNIT_ASSERT(std::equal(tt, tt + 4, "1234"));

			//TODO: 这里测试的结果，源文件只有4个字节长度，解密后的文件，虽然前4个字节是正确的，但是整个文件会强制变成128字节，并且后面的是乱码
			CPPUNIT_ASSERT(fs::file_size(fs::path(decryptOutFile)) == 4);
		}
	}

	//预期失败1 symKey与密文不匹配
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		std::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write("1234", 4);
		CPPUNIT_ASSERT(ofs);
		ofs.close();
		CPPUNIT_ASSERT(fs::exists(inFile));
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFile(inFile.data(), outFile.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		CPPUNIT_ASSERT(fs::exists(outFile));

		//
		{
			std::wstring decryptOutFile = fs::current_path().wstring() + L"/test_decrypt_file_out.txt";
			GDoc jsonDoc = parseJson([&decryptOutFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_DevryptFile(L"astgagh#$%^$#@^afhsha", outFile.data(), decryptOutFile.data()); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
		}
	}
}

void CommonInterfaceNoLoginTest::testEncryptData()
{
	using namespace rapidjson;
	//预期成功1
	{

		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(L"1234"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		std::string symKeyContent = symKey->GetString();

		const Value* encDataStr = GetValueByPointer(jsonDoc, "/data/encDataStr");
		CPPUNIT_ASSERT(encDataStr&&encDataStr->IsString());
		std::string encDataStrContent = encDataStr->GetString();
	}

	////预期失败1 待加密数据长度大于1024
	//{
	//	std::vector<wchar_t> tt(1024, L'A' ); tt[1023] = L'\0';
	//
	//	GDoc jsonDoc = parseJson([&tt]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(tt.data()); });
	//	CPPUNIT_ASSERT(!parseError(jsonDoc));
	//	const Value* code = GetValueByPointer(jsonDoc, "/code");
	//	CPPUNIT_ASSERT(code&&code->IsString());
	//	std::string strCode = code->GetString();
	//	CPPUNIT_ASSERT(strCode != "0000");
	//}
}

void CommonInterfaceNoLoginTest::testDevryptData()
{
	using namespace rapidjson;
	//预期成功1
	{

		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(L"1234"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		std::string symKeyContent = symKey->GetString();

		const Value* encDataStr = GetValueByPointer(jsonDoc, "/data/encDataStr");
		CPPUNIT_ASSERT(encDataStr&&encDataStr->IsString());
		std::string encDataStrContent = encDataStr->GetString();

		{
			GDoc jsonDoc = parseJson([&symKeyContent, &encDataStrContent]()->CString {return s_pDRS_CertSafeCtrl->RS_DevryptData(to_wstr(symKeyContent).data(), to_wstr(encDataStrContent).data()); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(isSuccessful(jsonDoc));

			const Value* dncDataStr = GetValueByPointer(jsonDoc, "/data/dncDataStr");
			std::string dncDataContent = dncDataStr->GetString();
			CPPUNIT_ASSERT(dncDataContent == "1234");
		}
	}

	//预期失败1 密钥不符
	{

		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(L"1234"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		std::string symKeyContent = symKey->GetString();

		const Value* encDataStr = GetValueByPointer(jsonDoc, "/data/encDataStr");
		CPPUNIT_ASSERT(encDataStr&&encDataStr->IsString());
		std::string encDataStrContent = encDataStr->GetString();

		{
			GDoc jsonDoc = parseJson([&symKeyContent, &encDataStrContent]()->CString {return s_pDRS_CertSafeCtrl->RS_DevryptData(L"$%^FGH", to_wstr(encDataStrContent).data()); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(!isSuccessful(jsonDoc));

		}
	}

	//预期失败1 密文不符
	{

		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(L"1234"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		std::string symKeyContent = symKey->GetString();

		const Value* encDataStr = GetValueByPointer(jsonDoc, "/data/encDataStr");
		CPPUNIT_ASSERT(encDataStr&&encDataStr->IsString());
		std::string encDataStrContent = encDataStr->GetString();

		{
			GDoc jsonDoc = parseJson([&symKeyContent, &encDataStrContent]()->CString {return s_pDRS_CertSafeCtrl->RS_DevryptData(to_wstr(symKeyContent).data(), L"4321"); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(!isSuccessful(jsonDoc));

		}
	}
}
