#pragma once
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class CommonTestAutoLogout :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CommonTestAutoLogout);
	CPPUNIT_TEST_SUITE_END();
public:
	CommonTestAutoLogout();
	~CommonTestAutoLogout();

	void setUp();
	void tearDown();

public:

};

