#include "stdafx.h"
#include "MobileTestAuto.h"
#include "util.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(MobileTestAuto, REGISTRY_NAME_AUTO_LOGIN);
MobileTestAuto::MobileTestAuto()
{
}


MobileTestAuto::~MobileTestAuto()
{
}

void MobileTestAuto::setUp()
{

}

void MobileTestAuto::tearDown()
{

}

//获取流水号
void MobileTestAuto::testGetTransid()
{
	//100020191120141710102

	using namespace rapidjson;

	//预期成功1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetTransid(L"1000"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto transid = getStrMember(jsonDoc, "/data/transid");
		CPPUNIT_ASSERT(transid.first);
		std::string& transidContent = transid.second;
		//CPPUNIT_ASSERT(transidContent.length() == 21);
		CPPUNIT_ASSERT(!transidContent.empty());
		CPPUNIT_ASSERT(std::all_of(transidContent.begin(), transidContent.end(), ::isdigit));
	}

#if UNNECISSARY_ASSERT
	//预期失败 joinCode位数不符
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetTransid(L"100000000"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
#endif
	
}

//取得登录权限
void MobileTestAuto::testCloudLoginAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//预期成功
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudLoginAuth(transId.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto action = getStrMember(jsonDoc, "/data/action");
		CPPUNIT_ASSERT(action.first);
		std::string& actionContent = action.second;

		auto authIdent = getStrMember(jsonDoc, "/data/authIdent");
		CPPUNIT_ASSERT(authIdent.first);
		std::string& authIdentContent = authIdent.second;
	}

}

//获得（上一次？）登录权限获取结果
void MobileTestAuto::testCloudGetAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//预期返回授权成功
	{
		CPPUNIT_ASSERT(encryptAuth());//请求授权
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetAuth(transId.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto authResult = getStrMember(jsonDoc, "/data/authResult");
		CPPUNIT_ASSERT(authResult.first);
		std::string& authResultContent = authResult.second;
		CPPUNIT_ASSERT(authResultContent == "0" || authResultContent == "1" || authResultContent == "2"
			|| authResultContent == "3" || authResultContent == "4" || authResultContent == "5");

		//CPPUNIT_ASSERT(authResultContent == "1");//TODO: 需手机扫码

		auto token = getStrMember(jsonDoc, "/data/token");
		CPPUNIT_ASSERT(token.first);
		std::string& tokenContent = token.second;
		//TODO: authType为0时，有值

		auto keySn = getStrMember(jsonDoc, "/data/keySn");
		CPPUNIT_ASSERT(keySn.first);
		std::string& keySnContent = keySn.second;
		//TODO: authType为1时有值
	}

#if UNNECISSARY_ASSERT
	//预期返回授权失败
	//TODO: 这里返回的并不是实时更新的状态，而是上一次的结果的保存。因此这种情况没有必要测试
	{
		CPPUNIT_ASSERT(logoutAuth(getLoginToken()));//注销授权
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetAuth(transId.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto authResult = getStrMember(jsonDoc, "/data/authResult");
		CPPUNIT_ASSERT(authResult.first);
		std::string& authResultContent = authResult.second;
		CPPUNIT_ASSERT(authResultContent == "0" || authResultContent == "1" || authResultContent == "2"
			|| authResultContent == "3" || authResultContent == "4" || authResultContent == "5");

		CPPUNIT_ASSERT(authResultContent != "1");
	}
#endif
	
}

//生成二维码
void MobileTestAuto::testGreateQRCode()
{
	using namespace rapidjson;

	//预期成功
	{
		std::wstring outFile = fs::current_path().wstring() + L"/test_create_qrcode_out.bmp";
		GDoc jsonDoc = parseJson([&outFile]()->CString { return s_pDRS_CertSafeCtrl->RS_GreateQRCode(TEST_DATA_W, outFile.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
		CPPUNIT_ASSERT(fs::exists(fs::path(outFile)));
	}

	//预期失败 输出目录错误
	{
		std::wstring outFile = L"lsdkfjgl";
		GDoc jsonDoc = parseJson([&outFile]()->CString { return s_pDRS_CertSafeCtrl->RS_GreateQRCode(TEST_DATA_W, outFile.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//获得签章权限
void MobileTestAuto::testCloudSealAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//预期成功
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudSealAuth(transId.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto action = getStrMember(jsonDoc, "/data/action");
		CPPUNIT_ASSERT(action.first);
		std::string& actionContent = action.second;

		auto authIdent = getStrMember(jsonDoc, "/data/authIdent");
		CPPUNIT_ASSERT(authIdent.first);
		std::string& authIdentContent = authIdent.second;
	}
}

//获取印章列表
void MobileTestAuto::testCloudGetSealList()
{
	using namespace rapidjson;
	std::wstring token = getSealToken();
	CPPUNIT_ASSERT(!token.empty());

	//预期成功
	{
		GDoc jsonDoc = parseJson([&token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetSealList(token.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* data = GetValueByPointer(jsonDoc, "/data");
		CPPUNIT_ASSERT(data&&data->IsArray());
		auto dataContent = data->GetArray();
		for (const auto& elm : dataContent)
		{
			CPPUNIT_ASSERT(elm.HasMember("keySn"));
			CPPUNIT_ASSERT(elm.HasMember("signSn"));
			CPPUNIT_ASSERT(elm.HasMember("certBase64"));
		}
	}

	//预期失败 token错误
	{
		GDoc jsonDoc = parseJson([&token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetSealList(L"-1e"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//预期失败 token为空
	{
		GDoc jsonDoc = parseJson([&token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetSealList(L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//p7签名
void MobileTestAuto::testCloudSignByP7()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getSealToken();
	CPPUNIT_ASSERT(!token.empty());
	std::wstring keySn = m_SealList[0].keySn;
	CPPUNIT_ASSERT(!keySn.empty());

	//预期成功
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId, &token, &keySn]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudSignByP7(TEST_DATA_W, keySn.data(), transId.data(), token.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//预期失败 token错误
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId, &token, &keySn]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudSignByP7(TEST_DATA_W, keySn.data(), transId.data(), L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//预期失败 keySn错误
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId, &token, &keySn]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudSignByP7(TEST_DATA_W, L"", transId.data(), token.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//获得加密权限
void MobileTestAuto::testCloudEncryptAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//预期成功
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudEncryptAuth(transId.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto action = getStrMember(jsonDoc, "/data/action");
		CPPUNIT_ASSERT(action.first);
		std::string& actionContent = action.second;

		auto authIdent = getStrMember(jsonDoc, "/data/authIdent");
		CPPUNIT_ASSERT(authIdent.first);
		std::string& authIdentContent = authIdent.second;
	}
}

//加密数据
void MobileTestAuto::testCloudEncryptData()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getEncryptToken();
	CPPUNIT_ASSERT(!token.empty());

	//预期成功
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudEncryptData(TEST_DATA_W, transId.data(), token.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto encReachKey = getStrMember(jsonDoc, "/data/encReachKey");
		CPPUNIT_ASSERT(encReachKey.first);
		std::string& encReachKeyContent = encReachKey.second;
	}

	//预期失败 token错误
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudEncryptData(TEST_DATA_W, transId.data(), L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//加密文件
void MobileTestAuto::testCloudEncryptFile()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getEncryptToken();
	CPPUNIT_ASSERT(!token.empty());

	//预期成功
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		fs::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write(TEST_DATA, sizeof(TEST_DATA)-1);
		CPPUNIT_ASSERT(ofs);
		ofs.close();
		CPPUNIT_ASSERT(fs::exists(inFile));

		GDoc jsonDoc = parseJson([&transId, &token, &inFile, &outFile]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudEncryptFile(inFile.data(), outFile.data(), transId.data(), token.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
		CPPUNIT_ASSERT(fs::exists(outFile));

		auto signCertBase64 = getStrMember(jsonDoc, "/data/signCertBase64");
		CPPUNIT_ASSERT(signCertBase64.first);
		std::string& signCertBase64Content = signCertBase64.second;

		auto encCertBase64 = getStrMember(jsonDoc, "/data/encCertBase64");
		CPPUNIT_ASSERT(encCertBase64.first);
		std::string& encCertBase64Content = encCertBase64.second;
	}

	//预期失败 原文件不存在
	{
		//TODO: 这里是直接收到空数据，没有code
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		std::wstring inFile = L"C:/agag2342sdfgsfg";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		CPPUNIT_ASSERT(!fs::exists(inFile));
		GDoc jsonDoc = parseJson([&transId, &token, &inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_CloudEncryptFile(inFile.data(), outFile.data(), transId.data(), token.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//预期失败 token错误
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		fs::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write(TEST_DATA, sizeof(TEST_DATA)-1);
		CPPUNIT_ASSERT(ofs);
		ofs.close();
		CPPUNIT_ASSERT(fs::exists(inFile));

		GDoc jsonDoc = parseJson([&transId, &token, &inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_CloudEncryptFile(inFile.data(), outFile.data(), transId.data(), L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//非对称加密数据接口（base64公钥证书）
void MobileTestAuto::testEncryptDataBase64()
{
	using namespace rapidjson;

	//预期成功
	{
		GDoc jsonDoc = parseJson([]()->CString { return s_pDRS_CertSafeCtrl->RS_EncryptDataBase64(TEST_DATA_W, _RS_CERT_ENCRYPT); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto encReachKey = getStrMember(jsonDoc, "/data/encReachKey");
		CPPUNIT_ASSERT(encReachKey.first);
		std::string& encReachKeyContent = encReachKey.second;
	}

	//预期失败 证书base64错误
	{
		GDoc jsonDoc = parseJson([]()->CString { return s_pDRS_CertSafeCtrl->RS_EncryptDataBase64(TEST_DATA_W, L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//非对称加密文件接口（base64公钥证书）
void MobileTestAuto::testEncryptFileBase64()
{
	using namespace rapidjson;

	//预期成功
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		fs::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write(TEST_DATA, sizeof(TEST_DATA)-1);
		CPPUNIT_ASSERT(ofs);
		ofs.close();
		CPPUNIT_ASSERT(fs::exists(inFile));

		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString { return s_pDRS_CertSafeCtrl->RS_EncryptFileBase64(inFile.data(), outFile.data(), _RS_CERT_ENCRYPT); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
		CPPUNIT_ASSERT(fs::exists(outFile));
	}

	//预期失败 原文件不存在
	{
		//TODO: 这里是直接收到空数据，没有code
		std::wstring inFile = L"C:/agag2342sdfgsfg";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		CPPUNIT_ASSERT(!fs::exists(inFile));
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFileBase64(inFile.data(), outFile.data(), _RS_CERT_ENCRYPT); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//预期失败 证书base64错误
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		fs::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write(TEST_DATA, sizeof(TEST_DATA)-1);
		CPPUNIT_ASSERT(ofs);
		ofs.close();
		CPPUNIT_ASSERT(fs::exists(inFile));

		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFileBase64(inFile.data(), outFile.data(), L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//获得解密权限
void MobileTestAuto::testCloudDevryptAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//预期成功
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudDevryptAuth(transId.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto action = getStrMember(jsonDoc, "/data/action");
		CPPUNIT_ASSERT(action.first);
		std::string& actionContent = action.second;

		auto authIdent = getStrMember(jsonDoc, "/data/authIdent");
		CPPUNIT_ASSERT(authIdent.first);
		std::string& authIdentContent = authIdent.second;
	}
}

//解密数据
void MobileTestAuto::testCloudDevryptData()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token;

	//预期成功
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		token = getEncryptToken();
		CPPUNIT_ASSERT(!token.empty());
		GDoc jsonDoc = parseJson([&transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudEncryptData(TEST_DATA_W, transId.data(), token.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto encReachKey = getStrMember(jsonDoc, "/data/encReachKey");
		CPPUNIT_ASSERT(encReachKey.first);
		std::string& encReachKeyContent = encReachKey.second;

		{
			transId = getTransid();
			CPPUNIT_ASSERT(!transId.empty());
			token = getDecryptToken();
			CPPUNIT_ASSERT(!token.empty());
			GDoc jsonDoc = parseJson([&encReachKeyContent, &transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudDevryptData(to_wstr(encReachKeyContent).data(), L"", transId.data(), token.data()); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(isSuccessful(jsonDoc));

			auto symKey = getStrMember(jsonDoc, "/data/symKey");
			CPPUNIT_ASSERT(symKey.first);
			std::string& symKeyContent = symKey.second;
			CPPUNIT_ASSERT(symKeyContent == TEST_DATA);
		}
	}
}

//解密文件
void MobileTestAuto::testCloudDevryptFile()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token;

	//预期成功
	{
		//加密
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		token = getEncryptToken();
		CPPUNIT_ASSERT(!token.empty());
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		fs::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write(TEST_DATA, sizeof(TEST_DATA) - 1);
		CPPUNIT_ASSERT(ofs);
		ofs.close();
		CPPUNIT_ASSERT(fs::exists(inFile));

		GDoc jsonDoc = parseJson([&transId, &token, &inFile, &outFile]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudEncryptFile(inFile.data(), outFile.data(), transId.data(), token.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
		CPPUNIT_ASSERT(fs::exists(outFile));

		auto signCertBase64 = getStrMember(jsonDoc, "/data/signCertBase64");
		CPPUNIT_ASSERT(signCertBase64.first);
		std::string& signCertBase64Content = signCertBase64.second;

		auto encCertBase64 = getStrMember(jsonDoc, "/data/encCertBase64");
		CPPUNIT_ASSERT(encCertBase64.first);
		std::string& encCertBase64Content = encCertBase64.second;

		{
			//解密
			std::wstring decryptOutFile = fs::current_path().wstring() + L"/test_decrypt_file_out.txt";
			transId = getTransid();
			CPPUNIT_ASSERT(!transId.empty());
			token = getEncryptToken();
			CPPUNIT_ASSERT(!token.empty());
			GDoc jsonDoc = parseJson([&transId, &token, &outFile, &decryptOutFile]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudDevryptFile(outFile.data(), decryptOutFile.data(), L"", transId.data(), token.data()); });
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

//接收对称解密结果接口
void MobileTestAuto::testCloudReceiveDevryptResult()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token;

	//预期成功
	{
		//加密
		{
			//预期成功
			{
				transId = getTransid();
				CPPUNIT_ASSERT(!transId.empty());
				token = getEncryptToken();
				CPPUNIT_ASSERT(!token.empty());
				GDoc jsonDoc = parseJson([&transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudEncryptData(TEST_DATA_W, transId.data(), token.data()); });
				CPPUNIT_ASSERT(!hasParseError(jsonDoc));
				CPPUNIT_ASSERT(hasCode(jsonDoc));
				CPPUNIT_ASSERT(isSuccessful(jsonDoc));

				auto encReachKey = getStrMember(jsonDoc, "/data/encReachKey");
				CPPUNIT_ASSERT(encReachKey.first);
				std::string& encReachKeyContent = encReachKey.second;

				{
					//解密
					transId = getTransid();
					CPPUNIT_ASSERT(!transId.empty());
					token = getDecryptToken();
					CPPUNIT_ASSERT(!token.empty());
					GDoc jsonDoc = parseJson([&encReachKeyContent, &transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudDevryptData(to_wstr(encReachKeyContent).data(), L"", transId.data(), token.data()); });
					CPPUNIT_ASSERT(!hasParseError(jsonDoc));
					CPPUNIT_ASSERT(hasCode(jsonDoc));
					CPPUNIT_ASSERT(isSuccessful(jsonDoc));

					auto symKey = getStrMember(jsonDoc, "/data/symKey");
					CPPUNIT_ASSERT(symKey.first);
					std::string& symKeyContent = symKey.second;
					CPPUNIT_ASSERT(symKeyContent == TEST_DATA);
				}
			}
		}
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		token = getEncryptToken();
		CPPUNIT_ASSERT(!token.empty());
		//wchar_t uu[80] = {0};
		GDoc jsonDoc = parseJson([&transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudReceiveDevryptResult(transId.data(), token.data(), L"1"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}
}

//获取企业证书信息接口
void MobileTestAuto::testCloudGetCompanyCert()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getEncryptToken();
	CPPUNIT_ASSERT(!token.empty());

	//预期成功
	CPPUNIT_ASSERT_NO_THROW(
		{
			transId = getTransid();
			CPPUNIT_ASSERT(!transId.empty());
			GDoc jsonDoc = parseJson([&transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetCompanyCert(transId.data(), token.data()); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(isSuccessful(jsonDoc));

			auto signCertBase64 = getStrMember(jsonDoc, "/data/signCertBase64");
			CPPUNIT_ASSERT(signCertBase64.first);
			std::string& signCertBase64Content = signCertBase64.second;

			auto encCertBase64 = getStrMember(jsonDoc, "/data/encCertBase64");
			CPPUNIT_ASSERT(encCertBase64.first);
			std::string& encCertBase64Content = encCertBase64.second;
		});

	//预期失败 token错误
	CPPUNIT_ASSERT_NO_THROW(
		{
			transId = getTransid();
			CPPUNIT_ASSERT(!transId.empty());
			GDoc jsonDoc = parseJson([&transId, &token]()->CString {return s_pDRS_CertSafeCtrl->RS_CloudGetCompanyCert(transId.data(), L""); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
		});
}

//获取证书证书权限
void MobileTestAuto::testCloudGetCertAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//预期成功
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetCertAuth(transId.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto action = getStrMember(jsonDoc, "/data/action");
		CPPUNIT_ASSERT(action.first);
		std::string& actionContent = action.second;

		auto authIdent = getStrMember(jsonDoc, "/data/authIdent");
		CPPUNIT_ASSERT(authIdent.first);
		std::string& authIdentContent = authIdent.second;
	}
}

//获取证书公钥信息接口
void MobileTestAuto::testCloudGetCertBase64()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getCertToken();
	CPPUNIT_ASSERT(!token.empty());

	//预期成功
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetCertBase64(transId.data(), token.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto certBase64 = getStrMember(jsonDoc, "/data/certBase64");
		CPPUNIT_ASSERT(certBase64.first);
		std::string& certBase64Content = certBase64.second;
	}

	//预期失败 token错误
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetCertBase64(transId.data(), L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));

	}
}


//获取签名结果
void MobileTestAuto::testCloudGetSignResult()
{
	using namespace rapidjson;

	//预期成功
	{
		std::wstring transid = getTransid();
		CPPUNIT_ASSERT(!transid.empty());
		GDoc jsonDoc = parseJson([&transid]()->CString {return s_pDRS_CertSafeCtrl->RS_CloudGetSignResult(transid.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto signResult = getStrMember(jsonDoc, "/data/signResult");
		CPPUNIT_ASSERT(signResult.first);
		std::string &signResultContent = signResult.second;
		CPPUNIT_ASSERT(signResultContent == "0" || signResultContent == "1" || signResultContent == "2");

		CPPUNIT_ASSERT(hasStrMember(jsonDoc, "/data/signdMsg"));
		CPPUNIT_ASSERT(hasStrMember(jsonDoc, "/data/certBase64"));
	}

}

