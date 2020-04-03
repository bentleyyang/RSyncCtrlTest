#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class MobileTestAutoLogout :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(MobileTestAutoLogout);
	CPPUNIT_TEST_SUITE_END();
public:
	MobileTestAutoLogout();
	~MobileTestAutoLogout();
	void setUp();
	void tearDown();
public:
};

