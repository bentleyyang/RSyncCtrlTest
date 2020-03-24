#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

class InterfaceTest :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(InterfaceTest);
	CPPUNIT_TEST(test1);
	CPPUNIT_TEST(testCertLogin1);
	CPPUNIT_TEST(testCertLoginNoPwd);
	CPPUNIT_TEST(testConfigParameters);
	CPPUNIT_TEST(testGetParameters);
	CPPUNIT_TEST(testKeySignByP7);
	CPPUNIT_TEST(testVerifySignByP7);
	CPPUNIT_TEST(testEncryptFile);
	CPPUNIT_TEST(testDevryptFile);
	CPPUNIT_TEST(testEncryptData);
	CPPUNIT_TEST(testDevryptData);
	CPPUNIT_TEST(testKeySignByP1);
	CPPUNIT_TEST(testVerifySignByP1);
	CPPUNIT_TEST(testGetCertInfo);
	CPPUNIT_TEST(testGetUserList);
	CPPUNIT_TEST(testGetCertBase64String);
	CPPUNIT_TEST(testGetPinRetryCount);
	CPPUNIT_TEST(testChangePassWd);
	CPPUNIT_TEST(testVerifyIdentity);
	CPPUNIT_TEST(testKeyGetKeySn);
	CPPUNIT_TEST(testKeyGetDeviceInfo);
	CPPUNIT_TEST(testKeyDigitalSignByP1);
	CPPUNIT_TEST(testVerifyDigitalSignByP1);
	
	CPPUNIT_TEST(testKeyEncryptData);
	CPPUNIT_TEST(testKeyDecryptData);
	CPPUNIT_TEST(testKeyEncryptFile);
	CPPUNIT_TEST(testKeyDecryptFile);
	CPPUNIT_TEST(testKeyEncryptByDigitalEnvelope);
	CPPUNIT_TEST(testKeyDecryptByDigitalEnvelope);
	CPPUNIT_TEST(testKeyStatus);
	CPPUNIT_TEST(testGetTransid);
	CPPUNIT_TEST(testCloudLoginAuth);
	CPPUNIT_TEST(testCloudGetAuth);
	CPPUNIT_TEST(testCreateQRCode);
	CPPUNIT_TEST(testCloudSealAuth);
	CPPUNIT_TEST(testCloudGetSealList);
	CPPUNIT_TEST(testCloudSignByP7);
	CPPUNIT_TEST(testCloudGetSignResult);
	CPPUNIT_TEST(testCloudEncryptAuth);
	CPPUNIT_TEST(testCloudEncryptData);
	CPPUNIT_TEST(testCloudEncryptFile);
	CPPUNIT_TEST(testEncryptDataBase64);
	CPPUNIT_TEST(testEncryptFileBase64);
	CPPUNIT_TEST(testCloudDevryptAuth);
	CPPUNIT_TEST(testCloudDevryptData);
	CPPUNIT_TEST(testCloudDevryptFile);
	CPPUNIT_TEST(testCloudReceiveDevryptResult);
	CPPUNIT_TEST(testCloudGetCompanyCert);
	CPPUNIT_TEST(testCloudGetCertAuth);
	CPPUNIT_TEST(testCloudGetCertBase64);
	CPPUNIT_TEST(testCloudLogoutAuth);
	CPPUNIT_TEST(testCloudLogout);
	CPPUNIT_TEST(testCloudLoginAuthEvent);
	CPPUNIT_TEST(testCloudSealAuthEvent);
	CPPUNIT_TEST(testCloudGetSignResultEvent);
	CPPUNIT_TEST(testCloudEncAuthEvent);
	CPPUNIT_TEST(testCloudDevAuthEvent);
	CPPUNIT_TEST(testCloudGetCertAuthEvent);

	CPPUNIT_TEST(testCreateQRCode);
	
	CPPUNIT_TEST_SUITE_END();

public:
	InterfaceTest();
	~InterfaceTest();

public:
	void setUp();
	void tearDown();
	void test1();

	void testGetCertInfo();
	void testGetUserList();
	void testGetCertBase64String();
	void testGetPinRetryCount();
	void testGetTransid();
	void testKeyGetKeySn();
	void testKeyGetDeviceInfo();
	
	

	
	void testCertLogin1();
	void testCertLoginNoPwd();
	void testChangePassWd();
	void testCloudLoginAuth();
	void testCloudGetAuth();
	



	void testConfigParameters();
	void testGetParameters();
	void testKeySignByP7();
	void testVerifySignByP7();
	void testEncryptFile();
	void testDevryptFile();
	void testEncryptData();
	void testDevryptData();
	void testKeySignByP1();
	void testVerifySignByP1();
	
	void testVerifyIdentity();
	void testKeyDigitalSignByP1();
	void testVerifyDigitalSignByP1();
	
	
	void testKeyEncryptData();
	void testKeyDecryptData();
	void testKeyEncryptFile();
	void testKeyDecryptFile();
	void testKeyEncryptByDigitalEnvelope();
	void testKeyDecryptByDigitalEnvelope();
	void testKeyStatus();
	
	void testCreateQRCode();
	void testCloudSealAuth();
	void testCloudSignByP7();
	
	void testCloudEncryptAuth();
	void testCloudEncryptData();
	void testCloudEncryptFile();
	void testEncryptDataBase64();
	void testEncryptFileBase64();
	void testCloudDevryptAuth();
	void testCloudDevryptData();
	void testCloudDevryptFile();
	void testCloudReceiveDevryptResult();
	void testCloudGetSealList();
	void testCloudGetSignResult();
	void testCloudGetCompanyCert();
	void testCloudGetCertAuth();
	void testCloudGetCertBase64();
	void testCloudLogoutAuth();
	void testCloudLogout();
	void testCloudLoginAuthEvent();
	void testCloudSealAuthEvent();
	void testCloudGetSignResultEvent();
	void testCloudEncAuthEvent();
	void testCloudDevAuthEvent();
	void testCloudGetCertAuthEvent();


	

private:
};