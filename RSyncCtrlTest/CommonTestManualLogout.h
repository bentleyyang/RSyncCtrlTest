#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class CommonTestManualLogout :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CommonTestManualLogout);
	CPPUNIT_TEST_SUITE_END();
public:
	CommonTestManualLogout();
	~CommonTestManualLogout();

	void setUp();
	void tearDown();

public:
};

