#pragma once
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class UkeyTestManualLogout :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(UkeyTestManualLogout);
	CPPUNIT_TEST_SUITE_END();
public:
	UkeyTestManualLogout();
	~UkeyTestManualLogout();

	void setUp();
	void tearDown();
public:

};

