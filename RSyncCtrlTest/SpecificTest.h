#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
class SpecificTest :public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(SpecificTest);
	CPPUNIT_TEST(testGetUserListNoKey );
	CPPUNIT_TEST(testGetUserListTwoKey );
	CPPUNIT_TEST(testGetUserListCloseDev );
	CPPUNIT_TEST(testCertLoginNoKey );
	CPPUNIT_TEST(testCertLoginTwoKey );
	CPPUNIT_TEST(testGetCertBase64StringNoKey );
	CPPUNIT_TEST(testGetCertBase64StringTwoKey );
	CPPUNIT_TEST(testKeyGetKeySnNoKey );
	CPPUNIT_TEST(testKeyGetKeySnTwoKey );
	CPPUNIT_TEST_SUITE_END();
public:
	SpecificTest();
	~SpecificTest();

	void setUp();
	void tearDown();
public:
	void testGetUserListNoKey();
	void testGetUserListTwoKey();
	void testGetUserListCloseDev();

	void testCertLoginNoKey();
	void testCertLoginTwoKey();

	void testGetCertBase64StringNoKey();
	void testGetCertBase64StringTwoKey();

	void testKeyGetKeySnNoKey();
	void testKeyGetKeySnTwoKey();
};

