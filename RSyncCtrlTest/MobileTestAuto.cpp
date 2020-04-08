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

//��ȡ��ˮ��
void MobileTestAuto::testGetTransid()
{
	//100020191120141710102

	using namespace rapidjson;

	//Ԥ�ڳɹ�1
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
	//Ԥ��ʧ�� joinCodeλ������
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetTransid(L"100000000"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
#endif
	
}

//ȡ�õ�¼Ȩ��
void MobileTestAuto::testCloudLoginAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//Ԥ�ڳɹ�
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

//��ã���һ�Σ�����¼Ȩ�޻�ȡ���
void MobileTestAuto::testCloudGetAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//Ԥ�ڷ�����Ȩ�ɹ�
	{
		CPPUNIT_ASSERT(encryptAuth());//������Ȩ
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

		//CPPUNIT_ASSERT(authResultContent == "1");//TODO: ���ֻ�ɨ��

		auto token = getStrMember(jsonDoc, "/data/token");
		CPPUNIT_ASSERT(token.first);
		std::string& tokenContent = token.second;
		//TODO: authTypeΪ0ʱ����ֵ

		auto keySn = getStrMember(jsonDoc, "/data/keySn");
		CPPUNIT_ASSERT(keySn.first);
		std::string& keySnContent = keySn.second;
		//TODO: authTypeΪ1ʱ��ֵ
	}

#if UNNECISSARY_ASSERT
	//Ԥ�ڷ�����Ȩʧ��
	//TODO: ���ﷵ�صĲ�����ʵʱ���µ�״̬��������һ�εĽ���ı��档����������û�б�Ҫ����
	{
		CPPUNIT_ASSERT(logoutAuth(getLoginToken()));//ע����Ȩ
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

//���ɶ�ά��
void MobileTestAuto::testGreateQRCode()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�
	{
		std::wstring outFile = fs::current_path().wstring() + L"/test_create_qrcode_out.bmp";
		GDoc jsonDoc = parseJson([&outFile]()->CString { return s_pDRS_CertSafeCtrl->RS_GreateQRCode(TEST_DATA_W, outFile.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
		CPPUNIT_ASSERT(fs::exists(fs::path(outFile)));
	}

	//Ԥ��ʧ�� ���Ŀ¼����
	{
		std::wstring outFile = L"lsdkfjgl";
		GDoc jsonDoc = parseJson([&outFile]()->CString { return s_pDRS_CertSafeCtrl->RS_GreateQRCode(TEST_DATA_W, outFile.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//���ǩ��Ȩ��
void MobileTestAuto::testCloudSealAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//Ԥ�ڳɹ�
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

//��ȡӡ���б�
void MobileTestAuto::testCloudGetSealList()
{
	using namespace rapidjson;
	std::wstring token = getSealToken();
	CPPUNIT_ASSERT(!token.empty());

	//Ԥ�ڳɹ�
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

	//Ԥ��ʧ�� token����
	{
		GDoc jsonDoc = parseJson([&token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetSealList(L"-1e"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ�� tokenΪ��
	{
		GDoc jsonDoc = parseJson([&token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetSealList(L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//p7ǩ��
void MobileTestAuto::testCloudSignByP7()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getSealToken();
	CPPUNIT_ASSERT(!token.empty());
	std::wstring keySn = m_SealList[0].keySn;
	CPPUNIT_ASSERT(!keySn.empty());

	//Ԥ�ڳɹ�
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId, &token, &keySn]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudSignByP7(TEST_DATA_W, keySn.data(), transId.data(), token.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ�� token����
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId, &token, &keySn]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudSignByP7(TEST_DATA_W, keySn.data(), transId.data(), L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ�� keySn����
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId, &token, &keySn]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudSignByP7(TEST_DATA_W, L"", transId.data(), token.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//��ü���Ȩ��
void MobileTestAuto::testCloudEncryptAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//Ԥ�ڳɹ�
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

//��������
void MobileTestAuto::testCloudEncryptData()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getEncryptToken();
	CPPUNIT_ASSERT(!token.empty());

	//Ԥ�ڳɹ�
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

	//Ԥ��ʧ�� token����
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudEncryptData(TEST_DATA_W, transId.data(), L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//�����ļ�
void MobileTestAuto::testCloudEncryptFile()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getEncryptToken();
	CPPUNIT_ASSERT(!token.empty());

	//Ԥ�ڳɹ�
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

	//Ԥ��ʧ�� ԭ�ļ�������
	{
		//TODO: ������ֱ���յ������ݣ�û��code
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

	//Ԥ��ʧ�� token����
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

//�ǶԳƼ������ݽӿڣ�base64��Կ֤�飩
void MobileTestAuto::testEncryptDataBase64()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString { return s_pDRS_CertSafeCtrl->RS_EncryptDataBase64(TEST_DATA_W, _RS_CERT_ENCRYPT); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		auto encReachKey = getStrMember(jsonDoc, "/data/encReachKey");
		CPPUNIT_ASSERT(encReachKey.first);
		std::string& encReachKeyContent = encReachKey.second;
	}

	//Ԥ��ʧ�� ֤��base64����
	{
		GDoc jsonDoc = parseJson([]()->CString { return s_pDRS_CertSafeCtrl->RS_EncryptDataBase64(TEST_DATA_W, L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

//�ǶԳƼ����ļ��ӿڣ�base64��Կ֤�飩
void MobileTestAuto::testEncryptFileBase64()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�
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

	//Ԥ��ʧ�� ԭ�ļ�������
	{
		//TODO: ������ֱ���յ������ݣ�û��code
		std::wstring inFile = L"C:/agag2342sdfgsfg";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		CPPUNIT_ASSERT(!fs::exists(inFile));
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFileBase64(inFile.data(), outFile.data(), _RS_CERT_ENCRYPT); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ�� ֤��base64����
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

//��ý���Ȩ��
void MobileTestAuto::testCloudDevryptAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//Ԥ�ڳɹ�
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

//��������
void MobileTestAuto::testCloudDevryptData()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token;

	//Ԥ�ڳɹ�
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

//�����ļ�
void MobileTestAuto::testCloudDevryptFile()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token;

	//Ԥ�ڳɹ�
	{
		//����
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
			//����
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

			//TODO: ������ԵĽ����Դ�ļ�ֻ��4���ֽڳ��ȣ����ܺ���ļ�����Ȼǰ4���ֽ�����ȷ�ģ����������ļ���ǿ�Ʊ��128�ֽڣ����Һ����������
			CPPUNIT_ASSERT(fs::file_size(fs::path(decryptOutFile)) == (sizeof(TEST_DATA) - 1));
		}
	}

	
}

//���նԳƽ��ܽ���ӿ�
void MobileTestAuto::testCloudReceiveDevryptResult()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token;

	//Ԥ�ڳɹ�
	{
		//����
		{
			//Ԥ�ڳɹ�
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
					//����
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

//��ȡ��ҵ֤����Ϣ�ӿ�
void MobileTestAuto::testCloudGetCompanyCert()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getEncryptToken();
	CPPUNIT_ASSERT(!token.empty());

	//Ԥ�ڳɹ�
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

	//Ԥ��ʧ�� token����
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

//��ȡ֤��֤��Ȩ��
void MobileTestAuto::testCloudGetCertAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//Ԥ�ڳɹ�
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

//��ȡ֤�鹫Կ��Ϣ�ӿ�
void MobileTestAuto::testCloudGetCertBase64()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getCertToken();
	CPPUNIT_ASSERT(!token.empty());

	//Ԥ�ڳɹ�
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

	//Ԥ��ʧ�� token����
	{
		transId = getTransid();
		CPPUNIT_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetCertBase64(transId.data(), L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));

	}
}


//��ȡǩ�����
void MobileTestAuto::testCloudGetSignResult()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�
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

