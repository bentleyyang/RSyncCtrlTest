#include "stdafx.h"
#include "UkeyTestAuto.h"
#include "util.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(UkeyTestAuto, REGISTRY_NAME_AUTO_LOGIN);
UkeyTestAuto::UkeyTestAuto()
{
}


UkeyTestAuto::~UkeyTestAuto()
{
}

void UkeyTestAuto::setUp()
{

}

void UkeyTestAuto::tearDown()
{

}

void UkeyTestAuto::testGetUserList()
{
	using namespace rapidjson;
	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetUserList(); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* userlist = GetValueByPointer(jsonDoc, "/data/userlist");
		CPPUNIT_ASSERT(userlist&&userlist->IsString());
		std::wstring userlistContent = to_wstr(userlist->GetString());
	}

	//预期失败
	{

	}
}
void UkeyTestAuto::testGetCertBase64String()
{
	using namespace rapidjson;

	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, 1); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* certBase64 = GetValueByPointer(jsonDoc, "/data/certBase64");
		CPPUNIT_ASSERT(certBase64&&certBase64->IsString());
		std::string certBase64Content = certBase64->GetString();
	}

	//预期成功2
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, 2); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* certBase64 = GetValueByPointer(jsonDoc, "/data/certBase64");
		CPPUNIT_ASSERT(certBase64&&certBase64->IsString());
		std::string certBase64Content = certBase64->GetString();
	}

	//预期失败1 type不符要求
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, -9); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//预期失败2 证书不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(L"@$^%^%$fd", 2); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyTestAuto::testCertLogin()
{
	using namespace rapidjson;

	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, _RS_PASSWD); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//预期失败1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, L"$%^@$^DSFGSA@#$%"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyTestAuto::testGetPinRetryCount()
{
	using namespace rapidjson;

	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetPinRetryCount(_RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* retryCount = GetValueByPointer(jsonDoc, "/data/retryCount");
		CPPUNIT_ASSERT(retryCount&&retryCount->IsString());
		std::string retryCountContent = retryCount->GetString();
		CPPUNIT_ASSERT(!retryCountContent.empty());
		CPPUNIT_ASSERT(std::all_of(retryCountContent.begin(), retryCountContent.end(), ::isdigit));
	}

	//预期失败1 证书不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetPinRetryCount(L"@$^%^%$fd"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyTestAuto::testKeySignByP7()
{
	using namespace rapidjson;

	CPPUNIT_ASSERT(login());
	//预期成功1 不带原文
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(TEST_DATA_W, L"1", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string tt = signdMsg->GetString();
	}

	//预期成功2 带原文
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(TEST_DATA_W, L"0", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string tt = signdMsg->GetString();
	}

	//预期失败1 container_id 不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(TEST_DATA_W, L"1", L"random-45634562456"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyTestAuto::testKeySignByP1()
{
	using namespace rapidjson;

	CPPUNIT_ASSERT(login());
	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(TEST_DATA_W, _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string tt = signdMsg->GetString();
	}

	//预期失败1 container_id 不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(TEST_DATA_W, L"random-45634562456"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyTestAuto::testVerifySignByP1()
{
	using namespace rapidjson;

	CPPUNIT_ASSERT(login());

	//预期成功1
	{
		//获取signedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(TEST_DATA_W, _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(_RS_CERT_SIGN, TEST_DATA_W, to_wstr(signedMsgContent).data()); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(isSuccessful(jsonDoc));
		}
	}

	//预期失败1 签名证书格式错误
	{
		//获取signedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(TEST_DATA_W, _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(L"$%^&%#&SHH", TEST_DATA_W, to_wstr(signedMsgContent).data()); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
		}
	}

	//预期失败2 代签名原文不符
	{
		//获取signedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(TEST_DATA_W, _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(_RS_CERT_SIGN, L"4321", to_wstr(signedMsgContent).data()); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
		}
	}

	//预期失败2 签名值不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP1(_RS_CERT_SIGN, TEST_DATA_W, L"#^@&^$d"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyTestAuto::testChangePassWd()
{
	//return;

	using namespace rapidjson;

	//先获取重试次数，保证不被锁住
	{
		auto retryCount = parseJsonAndGetMember([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetPinRetryCount(_RS_CONTAINER_ID); }, "/data/retryCount");
		CPPUNIT_ASSERT(retryCount.first);
		std::string retryCountContent = retryCount.second;
		CPPUNIT_ASSERT(!retryCountContent.empty());
		CPPUNIT_ASSERT(std::all_of(retryCountContent.begin(), retryCountContent.end(), ::isdigit));
		int cnt = atoi(retryCountContent.c_str());
		CPPUNIT_ASSERT(cnt > 3);

	}

	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ChangePassWd(_RS_CONTAINER_ID, _RS_PASSWD, L"87654321"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//预期失败 containerId 错误
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ChangePassWd(L"AAAAAAA123", L"87654321", _RS_PASSWD); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//预期失败 原密码错误
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ChangePassWd(_RS_CONTAINER_ID, L"#&%&H", _RS_PASSWD); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//预期成功，改回初始密码
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ChangePassWd(_RS_CONTAINER_ID, L"87654321", _RS_PASSWD); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}
}

void UkeyTestAuto::testVerifyIdentity()
{
	using namespace rapidjson;
	//预期成功1 加密证书
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifyIdentity(_RS_CERT_ENCRYPT, _RS_AUTH_CODE); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		//TODO: 文档中数据是在/data中，这里测试了是在/data/data里，并不是/data里
		//const Value* data = GetValueByPointer(jsonDoc, "/data");
		//CPPUNIT_ASSERT(data&&data->IsString());
		//std::string dataContent = data->GetString();
		const Value* data = GetValueByPointer(jsonDoc, "/data/data");
		CPPUNIT_ASSERT(data&&data->IsString());
		std::string dataContent = data->GetString();
	}

	//预期成功2 签名证书
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifyIdentity(_RS_CERT_SIGN, _RS_AUTH_CODE); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		//TODO: 文档中数据是在/data中，这里测试了是在/data/data里，并不是/data里
		//const Value* data = GetValueByPointer(jsonDoc, "/data");
		//CPPUNIT_ASSERT(data&&data->IsString());
		//std::string dataContent = data->GetString();
		const Value* data = GetValueByPointer(jsonDoc, "/data/data");
		CPPUNIT_ASSERT(data&&data->IsString());
		std::string dataContent = data->GetString();
	}

	//预期失败1 证书不符合要求
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifyIdentity(L"kglijdshgsd96785", _RS_AUTH_CODE); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyTestAuto::testKeyGetKeySn()
{
	using namespace rapidjson;
	//预期成功
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyGetKeySn(); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* keySn = GetValueByPointer(jsonDoc, "/data/keySn");
		CPPUNIT_ASSERT(keySn&&keySn->IsString());
		std::string keySnContent = keySn->GetString();

		//TODO: 文档中示例有containerId，但实际获取数据里并没有这个字段
		//const Value* containerId = GetValueByPointer(jsonDoc, "/data/containerId");
		//CPPUNIT_ASSERT(containerId&&containerId->IsString());
		//std::string containerIdContent = containerId->GetString();
	}
}

void UkeyTestAuto::testKeyGetDeviceInfo()
{
	using namespace rapidjson;
	//预期成功1 设备序列号
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyGetDeviceInfo(_RS_CONTAINER_ID, L"1"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
		std::string infoContent = info->GetString();
	}

	//预期失败1 容器名不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyGetDeviceInfo(L"", L"1"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyTestAuto::testKeyDigitalSignByP1()
{

}

void UkeyTestAuto::testVerifyDigitalSignByP1()
{

}

void UkeyTestAuto::testKeyEncryptData()
{
	using namespace rapidjson;
	//预期成功1
	{
		auto encRsKey = parseJsonAndGetMember([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyEncryptData(TEST_DATA_W, _RS_CERT_ENCRYPT); }, "/data/encRsKey");
		CPPUNIT_ASSERT(encRsKey.first);
		std::string& encRsKeyContent = encRsKey.second;
		CPPUNIT_ASSERT(!encRsKeyContent.empty());
	}

	//预期失败1 证书不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyEncryptData(TEST_DATA_W, L"#$@sdf"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyTestAuto::testKeyDecryptData()
{
	using namespace rapidjson;
	//预期成功1
	{
		auto encRsKey = parseJsonAndGetMember([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyEncryptData(TEST_DATA_W, _RS_CERT_ENCRYPT); }, "/data/encRsKey");
		CPPUNIT_ASSERT(encRsKey.first);
		std::string& encRsKeyContent = encRsKey.second;
		CPPUNIT_ASSERT(!encRsKeyContent.empty());

		{
			auto rsKey = parseJsonAndGetMember([&encRsKeyContent]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyDecryptData(to_wstr(encRsKeyContent).data(), _RS_CONTAINER_ID); }, "/data/rsKey");
			CPPUNIT_ASSERT(rsKey.first);
			std::string& rsKeyContent = rsKey.second;
			CPPUNIT_ASSERT(rsKeyContent == TEST_DATA);
		}
	}

	//预期失败1 待解密密文不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyDecryptData(L"sdflk76585", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//预期失败1 containerId不符
	{
		auto encRsKey = parseJsonAndGetMember([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyEncryptData(TEST_DATA_W, _RS_CERT_ENCRYPT); }, "/data/encRsKey");
		CPPUNIT_ASSERT(encRsKey.first);
		std::string& encRsKeyContent = encRsKey.second;
		CPPUNIT_ASSERT(!encRsKeyContent.empty());

		{
			GDoc jsonDoc = parseJson([&encRsKeyContent]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyDecryptData(to_wstr(encRsKeyContent).data(), L"kjhjk345"); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
		}
	}
}

void UkeyTestAuto::testKeyEncryptFile()
{
	using namespace rapidjson;

	//预期成功1
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		fs::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write(TEST_DATA, sizeof(TEST_DATA)-1);
		CPPUNIT_ASSERT(ofs);
		ofs.close();
		CPPUNIT_ASSERT(fs::exists(inFile));

		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyEncryptFile(inFile.data(), outFile.data(), _RS_CERT_ENCRYPT); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		CPPUNIT_ASSERT(fs::exists(outFile));
	}

	//预期失败1 原文件不存在
	{
		//TODO: 这里是直接收到空数据，没有code
		std::wstring inFile = L"C:/agag2342sdfgsfg";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		CPPUNIT_ASSERT(!fs::exists(inFile));
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyEncryptFile(inFile.data(), outFile.data(), _RS_CERT_ENCRYPT); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void UkeyTestAuto::testKeyDecryptFile()
{
	using namespace rapidjson;

	//预期成功1
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		fs::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write(TEST_DATA, sizeof(TEST_DATA)-1);
		CPPUNIT_ASSERT(ofs);
		ofs.close();
		CPPUNIT_ASSERT(fs::exists(inFile));

		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyEncryptFile(inFile.data(), outFile.data(), _RS_CERT_ENCRYPT); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		CPPUNIT_ASSERT(fs::exists(outFile));

		{
			std::wstring decryptOutFile = fs::current_path().wstring() + L"/test_decrypt_file_out.txt";
			GDoc jsonDoc = parseJson([&decryptOutFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyDecryptFile(outFile.data(), decryptOutFile.data(), _RS_CONTAINER_ID); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(isSuccessful(jsonDoc));
			CPPUNIT_ASSERT(fs::exists(decryptOutFile));

			fs::ifstream ifs(fs::path(decryptOutFile), std::ios::binary);
			char tt[sizeof(TEST_DATA) - 1];
			ifs.read(tt, sizeof(TEST_DATA) - 1);
			CPPUNIT_ASSERT(ifs);
			CPPUNIT_ASSERT(std::equal(tt, tt + (sizeof(TEST_DATA) - 1), TEST_DATA));

			//TODO: 这里测试的结果，源文件只有4个字节长度，解密后的文件，虽然前4个字节是正确的，但是整个文件会强制变成128字节，并且后面的是乱码
			CPPUNIT_ASSERT(fs::file_size(fs::path(decryptOutFile)) == (sizeof(TEST_DATA) - 1));
		}
	}
}

void UkeyTestAuto::testKeyEncryptByDigitalEnvelope()
{

}

void UkeyTestAuto::testKeyDecryptByDigitalEnvelope()
{

}


/*
参数：
	containerId:容器名
返回：Json格式的字符串
	例：
	{"code":"0000","msg":"执行成功。","data":""}
功能：获取指定介质key的打开状态，code值为0000表示已登录，非0000表示未登录。
*/
void UkeyTestAuto::testKeyStatus()
{
	//预期成功1
	{
		CPPUNIT_ASSERT(login());
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyStatus(_RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));//这里测试的结果应该是0000，未登录情况应该非0000
	}
}