#include "stdafx.h"
#include "CommonTestAuto.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(CommonTestAuto, REGISTRY_NAME_AUTO_LOGIN);
CommonTestAuto::CommonTestAuto()
{
}


CommonTestAuto::~CommonTestAuto()
{
}

void CommonTestAuto::setUp()
{

}

void CommonTestAuto::tearDown()
{

}

void CommonTestAuto::testGetCertInfo()
{
	using namespace rapidjson;

	//Ԥ��ʧ��1 type����
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"-1"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ��2 ֤�鲻��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(L"#$^%$&@fg", L"1"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//Ԥ�ڳɹ�1 ֤��汾
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"1"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�2 ֤�����к�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"2"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�3 ֤��䷢����Ϣ
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"5"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�4 ֤��ӵ������Ϣ
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"7"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�5 ֤����Ч��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"6"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�6 ֤��䷢��CN
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"33"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�7 ֤��䷢��O
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"34"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�8 ֤��䷢��OU
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"35"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�9 ֤��ӵ������ϢCN
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"49"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�10 ֤��ӵ������ϢO
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"50"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�11 ֤��ӵ������ϢOU
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"51"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�12 ֤��ӵ������ϢEMAIL
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"52"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�13 ����֤�����֤��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"53"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�14 ��ҵͳһ������ô���
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"54"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�15 ֤��ʹ������Կ��ʶ��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"55"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

	//Ԥ�ڳɹ�16 ֤��Ψһ��
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetCertInfo(_RS_CERT_ENCRYPT, L"300"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* info = GetValueByPointer(jsonDoc, "/data/info");
		CPPUNIT_ASSERT(info&&info->IsString());
	}

}


void CommonTestAuto::testConfigParameters()
{
	return;
	using namespace rapidjson;

	//TODO: cmd��Ӧ��ֵӦ����д����

	//Ԥ�ڳɹ�1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ConfigParameters(L"authCode", L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//Ԥ�ڳɹ�2
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ConfigParameters(L"rsigncloud", L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//Ԥ�ڳɹ�3
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ConfigParameters(L"authType", L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//Ԥ�ڳɹ�4
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ConfigParameters(L"keySn", L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//Ԥ�ڳɹ�5
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ConfigParameters(L"signAndVerify", L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ�� cmd����
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ConfigParameters(L"#&&#s", L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ�� cmd��Ӧ��ֵ����
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ConfigParameters(L"authCode", L"$%*cv"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void CommonTestAuto::testConfigParamsByBussSys()
{
	return;
	using namespace rapidjson;

	//TODO: ��Ŀ������д����

	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ConfigParamsByBussSys(L"bussName", L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ�� cmd����
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ConfigParamsByBussSys(L"@#^fdg", L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ�� ��Ŀ���Ʋ���
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_ConfigParamsByBussSys(L"bussName", L"fghsdfg"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void CommonTestAuto::testGetParameters()
{
	using namespace rapidjson;

	const wchar_t* cmds[] = { L"authCode", L"rsigncloud", L"authType", L"keySn", L"signAndVerify" };
	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(L"authCode"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* authCode = GetValueByPointer(jsonDoc, "/data/authCode");//TODO: ���ĵ�˵���Ĳ�һ��
		CPPUNIT_ASSERT(authCode&&authCode->IsString());
	}

	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(L"rsigncloud"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* rsigncloud = GetValueByPointer(jsonDoc, "/data/rsigncloud");
		CPPUNIT_ASSERT(rsigncloud&&rsigncloud->IsString());
	}

	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(L"authType"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* authType = GetValueByPointer(jsonDoc, "/data/authType");
		CPPUNIT_ASSERT(authType&&authType->IsString());
	}

	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(L"keySn"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* keySn = GetValueByPointer(jsonDoc, "/data/keySn");
		CPPUNIT_ASSERT(keySn&&keySn->IsString());
	}

	//Ԥ�ڳɹ�
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(L"signAndVerify"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signAndVerify = GetValueByPointer(jsonDoc, "/data/signAndVerify");
		CPPUNIT_ASSERT(signAndVerify&&signAndVerify->IsString());
	}

	//Ԥ��ʧ��1
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_GetParameters(L""); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}



void CommonTestAuto::testVerifySignByP7()
{
	using namespace rapidjson;

	CPPUNIT_ASSERT(login());

	//Ԥ�ڳɹ�1 ����ԭ��
	{
		//��ȡsignedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(TEST_DATA_W, L"1", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP7(TEST_DATA_W, to_wstr(signedMsgContent).data(), L"1"); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(isSuccessful(jsonDoc));
		}
	}
	//Ԥ�ڳɹ�2 ��ԭ��
	{
		//��ȡsignedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(TEST_DATA_W, L"0", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP7(L"", to_wstr(signedMsgContent).data(), L"0"); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(isSuccessful(jsonDoc));
		}
	}

	//Ԥ��ʧ��1 ǩ��ֵ��ʽ����
	{
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP7(TEST_DATA_W, L"43673456547", L"1"); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}

	//Ԥ��ʧ��2 flag������ʵ��
	{
		//��ȡsignedMsg
		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_KeySignByP7(TEST_DATA_W, L"1", _RS_CONTAINER_ID); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* signdMsg = GetValueByPointer(jsonDoc, "/data/signdMsg");
		CPPUNIT_ASSERT(signdMsg&&signdMsg->IsString());
		std::string signedMsgContent = signdMsg->GetString();

		{
			GDoc jsonDoc = parseJson([&signedMsgContent]()->CString {return s_pDRS_CertSafeCtrl->RS_VerifySignByP7(L"", to_wstr(signedMsgContent).data(), L"0"); });
			CPPUNIT_ASSERT(!hasParseError(jsonDoc));
			CPPUNIT_ASSERT(hasCode(jsonDoc));
			CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
		}
	}
}

void CommonTestAuto::testEncryptFile()
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
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFile(inFile.data(), outFile.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(isSuccessful(jsonDoc));

		const Value* symKey = GetValueByPointer(jsonDoc, "/data/symKey");
		CPPUNIT_ASSERT(symKey&&symKey->IsString());
		CPPUNIT_ASSERT(fs::exists(outFile));
	}

	//Ԥ��ʧ��1 ԭ�ļ�������
	{
		//TODO: ������ֱ���յ������ݣ�û��code
		std::wstring inFile = L"C:/agag2342sdfgsfg";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		CPPUNIT_ASSERT(!fs::exists(inFile));
		GDoc jsonDoc = parseJson([&inFile, &outFile]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptFile(inFile.data(), outFile.data()); });
		CPPUNIT_ASSERT(!hasParseError(jsonDoc));
		CPPUNIT_ASSERT(hasCode(jsonDoc));
		CPPUNIT_ASSERT(!isSuccessful(jsonDoc));
	}
}

void CommonTestAuto::testDevryptFile()
{
	using namespace rapidjson;

	//Ԥ�ڳɹ�1
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		fs::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write(TEST_DATA, sizeof(TEST_DATA) - 1);
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



			fs::ifstream ifs(fs::path(decryptOutFile), std::ios::binary);
			char tt[sizeof(TEST_DATA) - 1];
			ifs.read(tt, sizeof(TEST_DATA) - 1);
			CPPUNIT_ASSERT(ifs);
			CPPUNIT_ASSERT(std::equal(tt, tt + (sizeof(TEST_DATA) - 1), TEST_DATA));

			//TODO: ������ԵĽ����Դ�ļ�ֻ��4���ֽڳ��ȣ����ܺ���ļ�����Ȼǰ4���ֽ�����ȷ�ģ����������ļ���ǿ�Ʊ��128�ֽڣ����Һ����������
			CPPUNIT_ASSERT(fs::file_size(fs::path(decryptOutFile)) == (sizeof(TEST_DATA) - 1));
		}
	}

	//Ԥ��ʧ��1 symKey�����Ĳ�ƥ��
	{
		std::wstring inFile = fs::current_path().wstring() + L"/test_encrypt_file_in.txt";
		std::wstring outFile = fs::current_path().wstring() + L"/test_encrypt_file_out.txt";
		fs::ofstream ofs(fs::path(inFile), std::ios::binary);
		CPPUNIT_ASSERT(ofs);
		ofs.write(TEST_DATA, sizeof(TEST_DATA) - 1);
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

void CommonTestAuto::testEncryptData()
{
	using namespace rapidjson;
	//Ԥ�ڳɹ�1
	{

		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(TEST_DATA_W); });
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

	////Ԥ��ʧ��1 ���������ݳ��ȴ���1024
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

void CommonTestAuto::testDevryptData()
{
	using namespace rapidjson;
	//Ԥ�ڳɹ�1
	{

		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(TEST_DATA_W); });
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
			CPPUNIT_ASSERT(dncDataContent == TEST_DATA);
		}
	}

	//Ԥ��ʧ��1 ��Կ����
	{

		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(TEST_DATA_W); });
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

	//Ԥ��ʧ��1 ���Ĳ���
	{

		GDoc jsonDoc = parseJson([]()->CString {return s_pDRS_CertSafeCtrl->RS_EncryptData(TEST_DATA_W); });
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
