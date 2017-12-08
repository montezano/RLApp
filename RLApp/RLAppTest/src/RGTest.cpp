#ifndef __RGTEST_H__
#define __RGTEST_H__



#include "CppUnitTest.h"

#include "model/RG.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(RGTest)
{
public:

	RGTest()
	{

	}

	~RGTest()
	{

	}

	TEST_METHOD_INITIALIZE(MethodInitialize)
	{
		rg = RG();
	}

	TEST_METHOD_CLEANUP(MethodCleanup)
	{
	}

	TEST_METHOD(add_rg_production)
	{
		Assert::IsTrue(rg.addProduction("A", "a"));
	}

	TEST_METHOD(add_multi_rg_production)
	{
		rg.addProduction("S", "a");
		rg.addProduction("S", "aS");

		Assert::AreEqual(2, rg.getProduction("S").size());
		Assert::AreEqual(0, rg.getProduction("A").size());
	}

	TEST_METHOD(add_rg_production_fail)
	{
		rg.addProduction("Z", "aA");
		rg.addProduction("Z", "bB");
		rg.addProduction("Z", "&");
		rg.addProduction("S", "aA");
		rg.addProduction("S", "bB");
		rg.addProduction("A", "aS");
		rg.addProduction("A", "bC");
		rg.addProduction("A", "a");
		rg.addProduction("B", "aC");
		rg.addProduction("B", "bS");
		rg.addProduction("B", "b");
		rg.addProduction("C", "aB");
		rg.addProduction("C", "bA");
		
	}





	static RG rg;
};

RG RGTest::rg;
#endif // !__RETEST_H__
