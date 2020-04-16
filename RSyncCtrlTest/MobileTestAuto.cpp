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
	//TODO: ����ö�Σ����Լ��ٵ��ô���
	if (!login()) { AfxMessageBox(L"��¼ʧ�ܣ��������������޷�����"); }
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
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GetTransid, L"1000");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto transid = getStrMember(jsonDoc, "/data/transid");
		LOG_ASSERT(transid.first);
		std::string& transidContent = transid.second;
		//LOG_ASSERT(transidContent.length() == 21);
		LOG_ASSERT(!transidContent.empty());
		LOG_ASSERT(std::all_of(transidContent.begin(), transidContent.end(), ::isdigit));
		LOG_END();FOR_END();
	}

#if UNNECISSARY_ASSERT
	//Ԥ��ʧ�� joinCodeλ������
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetTransid(L"100000000"); });
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
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
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudLoginAuth, transId.data());
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto action = getStrMember(jsonDoc, "/data/action");
		LOG_ASSERT(action.first);
		std::string& actionContent = action.second;

		auto authIdent = getStrMember(jsonDoc, "/data/authIdent");
		LOG_ASSERT(authIdent.first);
		std::string& authIdentContent = authIdent.second;
		LOG_END();FOR_END();
	}

}

//��ã���һ�Σ�����¼Ȩ�޻�ȡ���
void MobileTestAuto::testCloudGetAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//Ԥ�ڷ�����Ȩ�ɹ�
	{
		bool isEncryptAuthSuccessful=(encryptAuth());//������Ȩ
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudGetAuth, transId.data());
		LOG_ASSERT(isEncryptAuthSuccessful);
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto authResult = getStrMember(jsonDoc, "/data/authResult");
		LOG_ASSERT(authResult.first);
		std::string& authResultContent = authResult.second;
		LOG_ASSERT(authResultContent == "0" || authResultContent == "1" || authResultContent == "2"
			|| authResultContent == "3" || authResultContent == "4" || authResultContent == "5");

		//LOG_ASSERT(authResultContent == "1");//TODO: ���ֻ�ɨ��

		auto token = getStrMember(jsonDoc, "/data/token");
		LOG_ASSERT(token.first);
		std::string& tokenContent = token.second;
		//TODO: authTypeΪ0ʱ����ֵ

		auto keySn = getStrMember(jsonDoc, "/data/keySn");
		LOG_ASSERT(keySn.first);
		std::string& keySnContent = keySn.second;
		//TODO: authTypeΪ1ʱ��ֵ
		LOG_END();FOR_END();
	}

#if UNNECISSARY_ASSERT
	//Ԥ�ڷ�����Ȩʧ��
	//TODO: ���ﷵ�صĲ�����ʵʱ���µ�״̬��������һ�εĽ���ı��档����������û�б�Ҫ����
	{
		LOG_ASSERT(logoutAuth(getLoginToken()));//ע����Ȩ
		transId = getTransid();
		LOG_ASSERT(!transId.empty());
		GDoc jsonDoc = parseJson([&transId]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudGetAuth(transId.data()); });
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto authResult = getStrMember(jsonDoc, "/data/authResult");
		LOG_ASSERT(authResult.first);
		std::string& authResultContent = authResult.second;
		LOG_ASSERT(authResultContent == "0" || authResultContent == "1" || authResultContent == "2"
			|| authResultContent == "3" || authResultContent == "4" || authResultContent == "5");

		LOG_ASSERT(authResultContent != "1");
	}
#endif
	
}

//���ɶ�ά��
void MobileTestAuto::testGreateQRCode()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�
	{
		FOR();
		std::wstring outFile = to_wstr(Poco::Path::current()) + L"test_create_qrcode_out.bmp";
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GreateQRCode, TEST_DATA_W, outFile.data());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));
		LOG_ASSERT(Poco::File(to_u8(outFile)).exists());
		LOG_END();FOR_END();
	}

	//Ԥ��ʧ�� ���Ŀ¼����
	{
		FOR();
		std::wstring outFile = L"lsdkfjgl";
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_GreateQRCode, TEST_DATA_W, outFile.data());
		LOG_ASSERT(!Poco::File(to_u8(outFile)).exists());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}

//���ǩ��Ȩ��
void MobileTestAuto::testCloudSealAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//Ԥ�ڳɹ�
	{
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudSealAuth, transId.data());
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto action = getStrMember(jsonDoc, "/data/action");
		LOG_ASSERT(action.first);
		std::string& actionContent = action.second;

		auto authIdent = getStrMember(jsonDoc, "/data/authIdent");
		LOG_ASSERT(authIdent.first);
		std::string& authIdentContent = authIdent.second;
		LOG_END();FOR_END();
	}
}

//��ȡӡ���б�
void MobileTestAuto::testCloudGetSealList()
{
	using namespace rapidjson;
	std::wstring token = getSealToken();
	

	//Ԥ�ڳɹ�
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudGetSealList, token.data());
		LOG_ASSERT(!token.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		const Value* data = GetValueByPointer(jsonDoc, "/data");
		LOG_ASSERT(data&&data->IsArray());
		auto dataContent = data->GetArray();
		for (const auto& elm : dataContent)
		{
			LOG_ASSERT(elm.HasMember("keySn"));
			LOG_ASSERT(elm.HasMember("signSn"));
			LOG_ASSERT(elm.HasMember("certBase64"));
		}
		LOG_END();FOR_END();
	}

	//Ԥ��ʧ�� token����
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudGetSealList, L"-1e");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}

	//Ԥ��ʧ�� tokenΪ��
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudGetSealList, L"");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}

//p7ǩ��
void MobileTestAuto::testCloudSignByP7()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getSealToken();
	std::wstring keySn = m_SealList[0].keySn;

	//Ԥ�ڳɹ�
	{
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudSignByP7, TEST_DATA_W, keySn.data(), transId.data(), token.data());
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!token.empty());
		LOG_ASSERT(!keySn.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}

	//Ԥ��ʧ�� token����
	{
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudSignByP7, TEST_DATA_W, keySn.data(), transId.data(), L"");
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!keySn.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}

	//Ԥ��ʧ�� keySn����
	{
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudSignByP7, TEST_DATA_W, L"", transId.data(), token.data());
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!token.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}

//��ü���Ȩ��
void MobileTestAuto::testCloudEncryptAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//Ԥ�ڳɹ�
	{
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudEncryptAuth, transId.data());
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto action = getStrMember(jsonDoc, "/data/action");
		LOG_ASSERT(action.first);
		std::string& actionContent = action.second;

		auto authIdent = getStrMember(jsonDoc, "/data/authIdent");
		LOG_ASSERT(authIdent.first);
		std::string& authIdentContent = authIdent.second;
		LOG_END();FOR_END();
	}
}

//��������
void MobileTestAuto::testCloudEncryptData()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getEncryptToken();
	

	//Ԥ�ڳɹ�
	{
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudEncryptData, TEST_DATA_W, transId.data(), token.data());
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!token.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto encReachKey = getStrMember(jsonDoc, "/data/encReachKey");
		LOG_ASSERT(encReachKey.first);
		std::string& encReachKeyContent = encReachKey.second;
		LOG_END();FOR_END();
	}

	//Ԥ��ʧ�� token����
	{
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudEncryptData, TEST_DATA_W, transId.data(), L"");
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}

//�����ļ�
void MobileTestAuto::testCloudEncryptFile()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getEncryptToken();
	
	auto fn = []()->std::tuple<bool, std::wstring, std::wstring> 
	{
		bool isFileCreated = true;
		std::wstring inFile = to_wstr(Poco::Path::current()) + L"test_encrypt_file_in.txt";
		std::wstring outFile = to_wstr(Poco::Path::current()) + L"test_encrypt_file_out.txt";
		Poco::FileStream ofs(to_u8(inFile), std::ios::binary);
		isFileCreated = isFileCreated && (ofs);
		ofs.write(TEST_DATA, sizeof(TEST_DATA) - 1);
		isFileCreated = isFileCreated && (ofs);
		ofs.close();
		isFileCreated = isFileCreated && (Poco::File(to_u8(inFile)).exists());
		return { isFileCreated, inFile, outFile };
	};

	//Ԥ�ڳɹ�
	{
		bool isCreatedFile;
		std::wstring inFile;
		std::wstring outFile;
		std::tie(isCreatedFile, inFile, outFile) = fn();
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudEncryptFile, inFile.data(), outFile.data(), transId.data(), token.data());
		LOG_ASSERT(isCreatedFile);
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!token.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));
		LOG_ASSERT(Poco::File(to_u8(outFile)).exists());

		auto signCertBase64 = getStrMember(jsonDoc, "/data/signCertBase64");
		LOG_ASSERT(signCertBase64.first);
		std::string& signCertBase64Content = signCertBase64.second;

		auto encCertBase64 = getStrMember(jsonDoc, "/data/encCertBase64");
		LOG_ASSERT(encCertBase64.first);
		std::string& encCertBase64Content = encCertBase64.second;
		LOG_END();FOR_END();
	}

	//Ԥ��ʧ�� ԭ�ļ�������
	{
		//TODO: ������ֱ���յ������ݣ�û��code
		bool isFileNotCreated = true;
		std::wstring inFile = L"C:/agag2342sdfgsfg";
		std::wstring outFile = to_wstr(Poco::Path::current()) + L"test_encrypt_file_out.txt";
		isFileNotCreated = isFileNotCreated && (!Poco::File(to_u8(inFile)).exists());

		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudEncryptFile, inFile.data(), outFile.data(), transId.data(), token.data());
		LOG_ASSERT(isFileNotCreated);
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!token.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}

	//Ԥ��ʧ�� token����
	{
		bool isCreatedFile;
		std::wstring inFile;
		std::wstring outFile;
		std::tie(isCreatedFile, inFile, outFile) = fn();
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudEncryptFile, inFile.data(), outFile.data(), transId.data(), L"");
		LOG_ASSERT(isCreatedFile);
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}

//�ǶԳƼ������ݽӿڣ�base64��Կ֤�飩
void MobileTestAuto::testEncryptDataBase64()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_EncryptDataBase64, TEST_DATA_W, _RS_CERT_ENCRYPT);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto encReachKey = getStrMember(jsonDoc, "/data/encReachKey");
		LOG_ASSERT(encReachKey.first);
		std::string& encReachKeyContent = encReachKey.second;
		LOG_END();FOR_END();
	}

	//Ԥ��ʧ�� ֤��base64����
	{
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_EncryptDataBase64, TEST_DATA_W, L"");
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}

//�ǶԳƼ����ļ��ӿڣ�base64��Կ֤�飩
void MobileTestAuto::testEncryptFileBase64()
{
	using namespace rapidjson;

	auto fn = []()->std::tuple<bool, std::wstring, std::wstring>
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
		return { isCreatedFile, inFile, outFile };
	};

	//Ԥ�ڳɹ�
	{
		
		bool isCreatedFile;
		std::wstring inFile;
		std::wstring outFile;
		std::tie(isCreatedFile, inFile, outFile) = fn();
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_EncryptFileBase64, inFile.data(), outFile.data(), _RS_CERT_ENCRYPT);
		LOG_ASSERT(isCreatedFile);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));
		LOG_ASSERT(Poco::File(to_u8(outFile)).exists());
		LOG_END();FOR_END();
	}

	//Ԥ��ʧ�� ԭ�ļ�������
	{
		//TODO: ������ֱ���յ������ݣ�û��code
		bool isFileNotCreated;
		std::wstring inFile = L"C:/agag2342sdfgsfg";
		std::wstring outFile = to_wstr(Poco::Path::current()) + L"test_encrypt_file_out.txt";
		isFileNotCreated=(!Poco::File(to_u8(inFile)).exists());
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_EncryptFileBase64, inFile.data(), outFile.data(), _RS_CERT_ENCRYPT);
		LOG_ASSERT(isFileNotCreated);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}

	//Ԥ��ʧ�� ֤��base64����
	{
		bool isCreatedFile;
		std::wstring inFile;
		std::wstring outFile;
		std::tie(isCreatedFile, inFile, outFile) = fn();
		FOR();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_EncryptFileBase64, inFile.data(), outFile.data(), L"");
		LOG_ASSERT(isCreatedFile);
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}

//��ý���Ȩ��
void MobileTestAuto::testCloudDevryptAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//Ԥ�ڳɹ�
	{
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudDevryptAuth, transId.data());
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto action = getStrMember(jsonDoc, "/data/action");
		LOG_ASSERT(action.first);
		std::string& actionContent = action.second;

		auto authIdent = getStrMember(jsonDoc, "/data/authIdent");
		LOG_ASSERT(authIdent.first);
		std::string& authIdentContent = authIdent.second;
		LOG_END();FOR_END();
	}
}

//��������
void MobileTestAuto::testCloudDevryptData()
{
	using namespace rapidjson;

	auto fn = []()->std::pair<bool, std::string> 
	{
		bool isSuc = true;
		std::wstring transId;
		std::wstring token;
		transId = getTransid();
		isSuc = isSuc && (!transId.empty());
		token = getEncryptToken();
		isSuc = isSuc && (!token.empty());
		GDoc jsonDoc = parseJson([&transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudEncryptData(TEST_DATA_W, transId.data(), token.data()); });
		isSuc = isSuc && (!hasParseError(jsonDoc));
		isSuc = isSuc && (hasCode(jsonDoc));
		isSuc = isSuc && (isSuccessful(jsonDoc));

		auto encReachKey = getStrMember(jsonDoc, "/data/encReachKey");
		isSuc = isSuc && (encReachKey.first);
		std::string& encReachKeyContent = encReachKey.second;
		return { isSuc, encReachKeyContent };
	};

	std::wstring transId;
	std::wstring token;

	//Ԥ�ڳɹ�
	{
		bool isEncrypted;
		std::string encReachKeyContent;
		std::tie(isEncrypted, encReachKeyContent) = fn();
		token = getDecryptToken();

		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudDevryptData, to_wstr(encReachKeyContent).data(), L"", transId.data(), token.data());
		LOG_ASSERT(isEncrypted);
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!token.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto symKey = getStrMember(jsonDoc, "/data/symKey");
		LOG_ASSERT(symKey.first);
		std::string& symKeyContent = symKey.second;
		LOG_ASSERT(symKeyContent == TEST_DATA);
		LOG_END();FOR_END();
	}
}

//�����ļ�
void MobileTestAuto::testCloudDevryptFile()
{
	using namespace rapidjson;

	auto fn = []()->std::pair<bool, std::wstring>
	{
		//����
		bool isEncrypted=true;
		std::wstring transId;
		std::wstring token;
		transId = getTransid();
		token = getEncryptToken();
		isEncrypted = isEncrypted && (!transId.empty());
		isEncrypted = isEncrypted && (!token.empty());
		std::wstring inFile = to_wstr(Poco::Path::current()) + L"test_encrypt_file_in.txt";
		std::wstring outFile = to_wstr(Poco::Path::current()) + L"test_encrypt_file_out.txt";
		Poco::FileStream ofs(to_u8(inFile), std::ios::binary);
		isEncrypted = isEncrypted && (ofs);
		ofs.write(TEST_DATA, sizeof(TEST_DATA) - 1);
		isEncrypted = isEncrypted && (ofs);
		ofs.close();
		isEncrypted = isEncrypted && (Poco::File(to_u8(inFile)).exists());
		

		GDoc jsonDoc = parseJson([&transId, &token, &inFile, &outFile]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudEncryptFile(inFile.data(), outFile.data(), transId.data(), token.data()); });
		isEncrypted = isEncrypted && (!hasParseError(jsonDoc));
		isEncrypted = isEncrypted && (hasCode(jsonDoc));
		isEncrypted = isEncrypted && (isSuccessful(jsonDoc));
		isEncrypted = isEncrypted && (Poco::File(to_u8(outFile)).exists());

		auto signCertBase64 = getStrMember(jsonDoc, "/data/signCertBase64");
		isEncrypted = isEncrypted && (signCertBase64.first);
		std::string& signCertBase64Content = signCertBase64.second;

		auto encCertBase64 = getStrMember(jsonDoc, "/data/encCertBase64");
		isEncrypted = isEncrypted && (encCertBase64.first);
		std::string& encCertBase64Content = encCertBase64.second;
		return { isEncrypted, outFile };
	};

	std::wstring transId;
	std::wstring token;

	//Ԥ�ڳɹ�
	{
		bool isEncrypted;
		std::wstring outFile;
		std::tie(isEncrypted, outFile) = fn();
		//����
		std::wstring decryptOutFile = to_wstr(Poco::Path::current()) + L"test_decrypt_file_out.txt";
		token = getDecryptToken();

		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudDevryptFile, outFile.data(), decryptOutFile.data(), L"", transId.data(), token.data());
		LOG_ASSERT(isEncrypted);
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!token.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));
		LOG_ASSERT(Poco::File(to_u8(decryptOutFile)).exists());

		Poco::FileInputStream ifs(to_u8(decryptOutFile), std::ios::binary);
		char tt[sizeof(TEST_DATA) - 1];
		ifs.read(tt, sizeof(TEST_DATA) - 1);
		LOG_ASSERT(ifs);
		LOG_ASSERT(std::equal(tt, tt + (sizeof(TEST_DATA) - 1), TEST_DATA));

		//TODO: ������ԵĽ����Դ�ļ�ֻ��4���ֽڳ��ȣ����ܺ���ļ�����Ȼǰ4���ֽ�����ȷ�ģ����������ļ���ǿ�Ʊ��128�ֽڣ����Һ����������
		LOG_ASSERT(Poco::File(to_u8(decryptOutFile)).getSize() == (sizeof(TEST_DATA) - 1));
		LOG_END();FOR_END();
	}

	
}

//���նԳƽ��ܽ���ӿ�
void MobileTestAuto::testCloudReceiveDevryptResult()
{
	using namespace rapidjson;

	auto fn = []()->bool 
	{
		bool ret=true;
		//����
		std::wstring transId;
		std::wstring token;
		transId = getTransid();
		token = getEncryptToken();
		ret = ret && (!transId.empty());
		ret = ret && (!token.empty());
		GDoc jsonDoc = parseJson([&transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudEncryptData(TEST_DATA_W, transId.data(), token.data()); });
		ret = ret && (!hasParseError(jsonDoc));
		ret = ret && (hasCode(jsonDoc));
		ret = ret && (isSuccessful(jsonDoc));

		auto encReachKey = getStrMember(jsonDoc, "/data/encReachKey");
		ret = ret && (encReachKey.first);
		std::string& encReachKeyContent = encReachKey.second;

		{
			//����
			transId = getTransid();
			ret = ret && (!transId.empty());
			token = getDecryptToken();
			ret = ret && (!token.empty());
			GDoc jsonDoc = parseJson([&encReachKeyContent, &transId, &token]()->CString { return s_pDRS_CertSafeCtrl->RS_CloudDevryptData(to_wstr(encReachKeyContent).data(), L"", transId.data(), token.data()); });
			ret = ret && (!hasParseError(jsonDoc));
			ret = ret && (hasCode(jsonDoc));
			ret = ret && (isSuccessful(jsonDoc));

			auto symKey = getStrMember(jsonDoc, "/data/symKey");
			ret = ret && (symKey.first);
			std::string& symKeyContent = symKey.second;
			ret = ret && (symKeyContent == TEST_DATA);
		}
		return ret;
	};

	std::wstring transId;
	std::wstring token;

	//Ԥ�ڳɹ�
	{
		bool isProcessed = fn();
		token = getDecryptToken();
		
		//wchar_t uu[80] = {0};
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudReceiveDevryptResult, transId.data(), token.data(), L"1");
		LOG_ASSERT(isProcessed);
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!token.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}

//��ȡ��ҵ֤����Ϣ�ӿ�
void MobileTestAuto::testCloudGetCompanyCert()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getEncryptToken();
	

	//Ԥ�ڳɹ�
	{
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudGetCompanyCert, transId.data(), token.data());
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!token.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto signCertBase64 = getStrMember(jsonDoc, "/data/signCertBase64");
		LOG_ASSERT(signCertBase64.first);
		std::string& signCertBase64Content = signCertBase64.second;

		auto encCertBase64 = getStrMember(jsonDoc, "/data/encCertBase64");
		LOG_ASSERT(encCertBase64.first);
		std::string& encCertBase64Content = encCertBase64.second;
		LOG_END();FOR_END();
	}

	//Ԥ��ʧ�� token����
	{
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudGetCompanyCert, transId.data(), L"");
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}

//��ȡ֤��֤��Ȩ��
void MobileTestAuto::testCloudGetCertAuth()
{
	using namespace rapidjson;
	std::wstring transId;

	//Ԥ�ڳɹ�
	{
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudGetCertAuth, transId.data());
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto action = getStrMember(jsonDoc, "/data/action");
		LOG_ASSERT(action.first);
		std::string& actionContent = action.second;

		auto authIdent = getStrMember(jsonDoc, "/data/authIdent");
		LOG_ASSERT(authIdent.first);
		std::string& authIdentContent = authIdent.second;
		LOG_END();FOR_END();
	}
}

//��ȡ֤�鹫Կ��Ϣ�ӿ�
void MobileTestAuto::testCloudGetCertBase64()
{
	using namespace rapidjson;
	std::wstring transId;
	std::wstring token = getCertToken();
	

	//Ԥ�ڳɹ�
	{
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudGetCertBase64, transId.data(), token.data());
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!token.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto certBase64 = getStrMember(jsonDoc, "/data/certBase64");
		LOG_ASSERT(certBase64.first);
		std::string& certBase64Content = certBase64.second;
		LOG_END();FOR_END();
	}

	//Ԥ��ʧ�� token����
	{
		FOR();
		transId = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudGetCertBase64, transId.data(), L"");
		LOG_ASSERT(!transId.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(!isSuccessful(jsonDoc));
		LOG_END();FOR_END();
	}
}


//��ȡǩ�����
void MobileTestAuto::testCloudGetSignResult()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�
	{
		FOR();
		std::wstring transid = getTransid();
		LOG_BEG(s_pDRS_CertSafeCtrl->RS_CloudGetSignResult, transid.data());
		LOG_ASSERT(!transid.empty());
		LOG_ASSERT(!hasParseError(jsonDoc));
		LOG_ASSERT(hasCode(jsonDoc));
		LOG_ASSERT(isSuccessful(jsonDoc));

		auto signResult = getStrMember(jsonDoc, "/data/signResult");
		LOG_ASSERT(signResult.first);
		std::string &signResultContent = signResult.second;
		LOG_ASSERT(signResultContent == "0" || signResultContent == "1" || signResultContent == "2");

		LOG_ASSERT(hasStrMember(jsonDoc, "/data/signdMsg"));
		LOG_ASSERT(hasStrMember(jsonDoc, "/data/certBase64"));
		LOG_END();FOR_END();
	}

}

