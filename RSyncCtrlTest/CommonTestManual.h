#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class CommonTestManual :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CommonTestManual);
	CPPUNIT_TEST_SUITE_END();
public:
	CommonTestManual();
	~CommonTestManual();
	void setUp();
	void tearDown();

public:
};

