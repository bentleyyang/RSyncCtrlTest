#pragma once
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class UkeyTestAutoLogout :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(UkeyTestAutoLogout);
	CPPUNIT_TEST_SUITE_END();
public:
	UkeyTestAutoLogout();
	~UkeyTestAutoLogout();

	void setUp();
	void tearDown();
public:
};

