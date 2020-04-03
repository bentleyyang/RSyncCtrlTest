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
	//Ԥ�ڳɹ�1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetUserList(); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* userlist = GetValueByPointer(jsonDoc, "/data/userlist");
		CPPUNIT_ASSERT(userlist&&userlist->IsString());
		std::wstring userlistContent = to_wstr(userlist->GetString());
	}

	//Ԥ��ʧ��
	{

	}
}
void UkeyTestAuto::testGetCertBase64String()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, 1); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* certBase64 = GetValueByPointer(jsonDoc, "/data/certBase64");
		CPPUNIT_ASSERT(certBase64&&certBase64->IsString());
		std::string certBase64Content = certBase64->GetString();
	}

	//Ԥ�ڳɹ�2
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, 2); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* certBase64 = GetValueByPointer(jsonDoc, "/data/certBase64");
		CPPUNIT_ASSERT(certBase64&&certBase64->IsString());
		std::string certBase64Content = certBase64->GetString();
	}

	//Ԥ��ʧ��1 type����Ҫ��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertBase64String(_RS_CONTAINER_ID, -9); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ��2 ֤�鲻��
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

	//Ԥ�ڳɹ�1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_CertLogin(_RS_CONTAINER_ID, _RS_PASSWD); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ��1
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

	//Ԥ�ڳɹ�1
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

	//Ԥ��ʧ��1 ֤�鲻��
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
	//Ԥ�ڳɹ�1 ����ԭ��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(TEST_DATA_W, L"1", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string tt = signdMsg->GetString();
	}

	//Ԥ�ڳɹ�2 ��ԭ��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(TEST_DATA_W, L"0", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string tt = signdMsg->GetString();
	}

	//Ԥ��ʧ��1 container_id ����
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
	//Ԥ�ڳɹ�1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP1(TEST_DATA_W, _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string tt = signdMsg->GetString();
	}

	//Ԥ��ʧ��1 container_id ����
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

	//Ԥ�ڳɹ�1
	{
		//��ȡsignedMsg
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

	//Ԥ��ʧ��1 ǩ��֤���ʽ����
	{
		//��ȡsignedMsg
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

	//Ԥ��ʧ��2 ��ǩ��ԭ�Ĳ���
	{
		//��ȡsignedMsg
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

	//Ԥ��ʧ��2 ǩ��ֵ����
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

	//�Ȼ�ȡ���Դ�������֤������ס
	{
		auto retryCount = parseJsonAndGetMember([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetPinRetryCount(_RS_CONTAINER_ID); }, "/data/retryCount");
		CPPUNIT_ASSERT(retryCount.first);
		std::string retryCountContent = retryCount.second;
		CPPUNIT_ASSERT(!retryCountContent.empty());
		CPPUNIT_ASSERT(std::all_of(retryCountContent.begin(), retryCountContent.end(), ::isdigit));
		int cnt = atoi(retryCountContent.c_str());
		CPPUNIT_ASSERT(cnt > 3);

	}

	//Ԥ�ڳɹ�1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ChangePassWd(_RS_CONTAINER_ID, _RS_PASSWD, L"87654321"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ�� containerId ����
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ChangePassWd(L"AAAAAAA123", L"87654321", _RS_PASSWD); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ�� ԭ�������
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ChangePassWd(_RS_CONTAINER_ID, L"#&%&H", _RS_PASSWD); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//Ԥ�ڳɹ����Ļس�ʼ����
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
	//Ԥ�ڳɹ�1 ����֤��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifyIdentity(_RS_CERT_ENCRYPT, _RS_AUTH_CODE); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		//TODO: �ĵ�����������/data�У��������������/data/data�������/data��
		//const Value* data = GetValueByPointer(jsonDoc, "/data");
		//CPPUNIT_ASSERT(data&&data->IsString());
		//std::string dataContent = data->GetString();
		const Value* data = GetValueByPointer(jsonDoc, "/data/data");
		CPPUNIT_ASSERT(data&&data->IsString());
		std::string dataContent = data->GetString();
	}

	//Ԥ�ڳɹ�2 ǩ��֤��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifyIdentity(_RS_CERT_SIGN, _RS_AUTH_CODE); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		//TODO: �ĵ�����������/data�У��������������/data/data�������/data��
		//const Value* data = GetValueByPointer(jsonDoc, "/data");
		//CPPUNIT_ASSERT(data&&data->IsString());
		//std::string dataContent = data->GetString();
		const Value* data = GetValueByPointer(jsonDoc, "/data/data");
		CPPUNIT_ASSERT(data&&data->IsString());
		std::string dataContent = data->GetString();
	}

	//Ԥ��ʧ��1 ֤�鲻����Ҫ��
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
	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyGetKeySn(); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* keySn = GetValueByPointer(jsonDoc, "/data/keySn");
		CPPUNIT_ASSERT(keySn&&keySn->IsString());
		std::string keySnContent = keySn->GetString();

		//TODO: �ĵ���ʾ����containerId����ʵ�ʻ�ȡ�����ﲢû������ֶ�
		//const Value* containerId = GetValueByPointer(jsonDoc, "/data/containerId");
		//CPPUNIT_ASSERT(containerId&&containerId->IsString());
		//std::string containerIdContent = containerId->GetString();
	}
}

void UkeyTestAuto::testKeyGetDeviceInfo()
{
	using namespace rapidjson;
	//Ԥ�ڳɹ�1 �豸���к�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyGetDeviceInfo(_RS_CONTAINER_ID, L"1"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
		std::string infoContent = info->GetString();
	}

	//Ԥ��ʧ��1 ����������
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
	//Ԥ�ڳɹ�1
	{
		auto encRsKey = parseJsonAndGetMember([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyEncryptData(TEST_DATA_W, _RS_CERT_ENCRYPT); }, "/data/encRsKey");
		CPPUNIT_ASSERT(encRsKey.first);
		std::string& encRsKeyContent = encRsKey.second;
		CPPUNIT_ASSERT(!encRsKeyContent.empty());
	}

	//Ԥ��ʧ��1 ֤�鲻��
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
	//Ԥ�ڳɹ�1
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

	//Ԥ��ʧ��1 ���������Ĳ���
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyDecryptData(L"sdflk76585", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ��1 containerId����
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

	//Ԥ�ڳɹ�1
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

	//Ԥ��ʧ��1 ԭ�ļ�������
	{
		//TODO: ������ֱ���յ������ݣ�û��code
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

	//Ԥ�ڳɹ�1
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

			//TODO: ������ԵĽ����Դ�ļ�ֻ��4���ֽڳ��ȣ����ܺ���ļ�����Ȼǰ4���ֽ�����ȷ�ģ����������ļ���ǿ�Ʊ��128�ֽڣ����Һ����������
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
������
	containerId:������
���أ�Json��ʽ���ַ���
	����
	{"code":"0000","msg":"ִ�гɹ���","data":""}
���ܣ���ȡָ������key�Ĵ�״̬��codeֵΪ0000��ʾ�ѵ�¼����0000��ʾδ��¼��
*/
void UkeyTestAuto::testKeyStatus()
{
	//Ԥ�ڳɹ�1
	{
		CPPUNIT_ASSERT(login());
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeyStatus(_RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));//������ԵĽ��Ӧ����0000��δ��¼���Ӧ�÷�0000
	}
}