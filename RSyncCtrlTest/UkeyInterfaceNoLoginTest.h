#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class UkeyInterfaceNoLoginTest :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(UkeyInterfaceNoLoginTest);
	//CPPUNIT_TEST(testGetTransid);
	CPPUNIT_TEST_SUITE_END();
public:
	UkeyInterfaceNoLoginTest();
	~UkeyInterfaceNoLoginTest();

	void setUp();
	void tearDown();
public:
	void testGetUserList();
	void testGetCertBase64String();
	void testCertLogin();
	void testCertLoginNoPwd();
	void testGetPinRetryCount();
	void testChangePassWd();
	void testVerifyIdentity();
	void testKeyGetKeySn();
	void testKeyGetDeviceInfo();
	void testKeyDigitalSignByP1();
	void testVerifyDigitalSignByP1();
	void testKeySignByP1();
	void testVerifySignByP1();
	void testKeySignByP7();
	void testKeyEncryptData();
	void testKeyDecryptData();
	void testKeyEncryptFile();
	void testKeyDecryptFile();
	void testKeyEncryptByDigitalEnvelope();
	void testKeyDecryptByDigitalEnvelope();
	void testKeyStatus();
};

