#ifndef __CONVERSIONSTEST_H__
#define __CONVERSIONSTEST_H__



#include "CppUnitTest.h"

#include "model/Conversions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(ConversionsTest)
{
public:

	ConversionsTest()
	{

	}

	~ConversionsTest()
	{

	}

	TEST_METHOD_INITIALIZE(MethodInitialize)
	{
		re = RE();
	}

	TEST_METHOD_CLEANUP(MethodCleanup)
	{
	}

	TEST_METHOD(re_to_fa_conversion)
	{
		re.setReString("a(a|b)|a");

		fa = Conversions::reToFA(re);
		fa.determinize();
		QVector<DetFAState> det_fa = fa.getDetStates();

		QVector<QString> valid_states = { "0", "1-4", "2", "3" };

		for (DetFAState state : det_fa)
		{
			Assert::IsTrue(valid_states.contains(state._state_name));
		}
	}

	TEST_METHOD(rg_to_fa)
	{
		rg.addProduction("S", "a");
		rg.addProduction("S", "aA");
		rg.addProduction("A", "a");
		rg.addProduction("A", "b");

		rg.setInitial("S");

		Assert::IsTrue(&Conversions::grToFA(rg) == NULL);
	}


	static RE re;
	static FA fa;
	static RG rg;
};

RE ConversionsTest::re;
FA ConversionsTest::fa;
RG ConversionsTest::rg;
#endif // !__RETEST_H__
