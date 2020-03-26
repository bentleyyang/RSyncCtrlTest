#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class MobileInterfaceTest :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(MobileInterfaceTest);
	CPPUNIT_TEST(testGetTransid);
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

