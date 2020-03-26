#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class CommonInterfaceNoLoginTest :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CommonInterfaceNoLoginTest);
	//CPPUNIT_TEST(testGetTransid);
	CPPUNIT_TEST_SUITE_END();
public:
	CommonInterfaceNoLoginTest();
	~CommonInterfaceNoLoginTest();

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

