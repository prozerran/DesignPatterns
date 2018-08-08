
#include "stdafx.h"
#include "gtest/gtest.h"

namespace DesignPattern
{
	/****  Google Test Fixture Object Creation *****/

	class TestPattern : public ::testing::Test {
	protected:

		// calls once
		TestPattern()			{}
		virtual ~TestPattern()	{}

		// calls each time a TEST_F() is run
		virtual void SetUp()	{}
		virtual void TearDown() {}

	protected:

		void* m_pObj;	// pointer to object that can be accessed in TEST_F()
	};

	/************************************************/

	TEST_F(TestPattern, Template) 
	{
		ASSERT_TRUE(m_pObj != NULL);		
	}
}