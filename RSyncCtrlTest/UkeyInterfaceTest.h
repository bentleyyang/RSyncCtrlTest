#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class UkeyInterfaceTest :public CPPUNIT_NS::TestFixture
{
	
	CPPUNIT_TEST_SUITE(UkeyInterfaceTest);
	CPPUNIT_TEST(testGetUserList );
	CPPUNIT_TEST(testGetCertBase64String );
	CPPUNIT_TEST(testCertLogin );
	CPPUNIT_TEST(testCertLoginNoPwd );
	CPPUNIT_TEST(testGetPinRetryCount );
	CPPUNIT_TEST(testChangePassWd );
	CPPUNIT_TEST(testVerifyIdentity );
	CPPUNIT_TEST(testKeyGetKeySn );
	CPPUNIT_TEST(testKeyGetDeviceInfo );
	CPPUNIT_TEST(testKeyDigitalSignByP1 );
	CPPUNIT_TEST(testVerifyDigitalSignByP1 );
	CPPUNIT_TEST(testKeySignByP1 );
	CPPUNIT_TEST(testVerifySignByP1 );
	CPPUNIT_TEST(testKeySignByP7 );
	CPPUNIT_TEST(testKeyEncryptData );
	CPPUNIT_TEST(testKeyDecryptData );
	CPPUNIT_TEST(testKeyEncryptFile );
	CPPUNIT_TEST(testKeyDecryptFile );
	CPPUNIT_TEST(testKeyEncryptByDigitalEnvelope );
	CPPUNIT_TEST(testKeyDecryptByDigitalEnvelope );
	CPPUNIT_TEST(testKeyStatus );
	CPPUNIT_TEST_SUITE_END();

public:
	UkeyInterfaceTest();
	~UkeyInterfaceTest();

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

