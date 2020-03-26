#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class CommonInterfaceTest :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CommonInterfaceTest);
	CPPUNIT_TEST(testConfigParameters);
	CPPUNIT_TEST(testConfigParamsByBussSys);
	CPPUNIT_TEST(testGetParameters);
	CPPUNIT_TEST(testVerifySignByP7);
	CPPUNIT_TEST(testEncryptFile);
	CPPUNIT_TEST(testDevryptFile);
	CPPUNIT_TEST(testEncryptData);
	CPPUNIT_TEST(testDevryptData);
	CPPUNIT_TEST(testGetCertInfo);
	CPPUNIT_TEST_SUITE_END();

public:
	CommonInterfaceTest();
	~CommonInterfaceTest();

	void setUp();
	void tearDown();

public:
	void testConfigParameters();
	void testConfigParamsByBussSys();
	void testGetParameters();
	void testVerifySignByP7();
	void testEncryptFile();
	void testDevryptFile();
	void testEncryptData();
	void testDevryptData();
	void testGetCertInfo();
	
};

