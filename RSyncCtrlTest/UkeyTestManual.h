#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class UkeyTestManual :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(UkeyTestManual);
	CPPUNIT_TEST(testCertLoginNoPwd);
	CPPUNIT_TEST_SUITE_END();
public:
	UkeyTestManual();
	~UkeyTestManual();

	void setUp();
	void tearDown();
public:
	void testCertLoginNoPwd();
};

