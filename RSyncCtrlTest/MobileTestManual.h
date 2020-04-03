#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class MobileTestManual :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(MobileTestManual);
	CPPUNIT_TEST(testCloudLogoutAuth);
	CPPUNIT_TEST(testCloudLogout);
	CPPUNIT_TEST_SUITE_END();
public:
	MobileTestManual();
	~MobileTestManual();

	void setUp();
	void tearDown();
public:
	void testCloudLogoutAuth();
	void testCloudLogout();
};

