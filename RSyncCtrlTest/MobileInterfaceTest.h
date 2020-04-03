#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class MobileInterfaceTest :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(MobileInterfaceTest);
	CPPUNIT_TEST(testGetTransid );
	CPPUNIT_TEST(testCloudLoginAuth );
	CPPUNIT_TEST(testCloudGetAuth );
	CPPUNIT_TEST(testGreateQRCode );
	CPPUNIT_TEST(testCloudSealAuth );
	CPPUNIT_TEST(testCloudGetSealList );
	CPPUNIT_TEST(testCloudSignByP7 );
	CPPUNIT_TEST(testCloudGetSignResult );
	CPPUNIT_TEST(testCloudEncryptAuth );
	CPPUNIT_TEST(testCloudEncryptData );
	CPPUNIT_TEST(testCloudEncryptFile );
	CPPUNIT_TEST(testEncryptDataBase64 );
	CPPUNIT_TEST(testEncryptFileBase64 );
	CPPUNIT_TEST(testCloudDevryptAuth );
	CPPUNIT_TEST(testCloudDevryptData );
	CPPUNIT_TEST(testCloudDevryptFile );
	CPPUNIT_TEST(testCloudReceiveDevryptResult );
	CPPUNIT_TEST(testCloudGetCompanyCert );
	CPPUNIT_TEST(testCloudGetCertAuth );
	CPPUNIT_TEST(testCloudGetCertBase64 );
	CPPUNIT_TEST(testCloudLogoutAuth );
	CPPUNIT_TEST(testCloudLogout );
	CPPUNIT_TEST_SUITE_END();
	

public:
	MobileInterfaceTest();
	~MobileInterfaceTest();

	void setUp();
	void tearDown();
public:
	void testGetTransid();
	void testCloudLoginAuth();
	void testCloudGetAuth();
	void testGreateQRCode();
	void testCloudSealAuth();
	void testCloudGetSealList();
	void testCloudSignByP7();
	void testCloudGetSignResult();
	void testCloudEncryptAuth();
	void testCloudEncryptData();
	void testCloudEncryptFile();
	void testEncryptDataBase64();
	void testEncryptFileBase64();
	void testCloudDevryptAuth();
	void testCloudDevryptData();
	void testCloudDevryptFile();
	void testCloudReceiveDevryptResult();
	void testCloudGetCompanyCert();
	void testCloudGetCertAuth();
	void testCloudGetCertBase64();
	void testCloudLogoutAuth();
	void testCloudLogout();

};

