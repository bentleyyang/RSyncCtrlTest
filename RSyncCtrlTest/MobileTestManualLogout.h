#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class MobileTestManualLogout :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(MobileTestManualLogout);
	CPPUNIT_TEST_SUITE_END();
public:
	MobileTestManualLogout();
	~MobileTestManualLogout();
	void setUp();
	void tearDown();
public:
};

