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
		fa = new FA();
	}

	TEST_METHOD_CLEANUP(MethodCleanup)
	{
		delete fa;
	}

	TEST_METHOD(re_to_fa_conversion)
	{
		re.setReString("a(a|b)|a");

		fa = Conversions::reToFA(re);
		fa->determinize();
		QVector<DetFAState> det_fa = fa->getDetStates();

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

		fa = Conversions::grToFA(rg);

		QVector<FAState> states = fa->getStates();
		Assert::IsTrue("0" == states[0]._state_name);
		Assert::IsTrue(states[0]._transitions[0].size() == 0 );
		Assert::IsTrue(states[0]._transitions[1][0] == "2");
		Assert::IsTrue("1" == states[1]._state_name);
		Assert::IsTrue(states[1]._transitions[0][0] == "2");
		Assert::IsTrue(states[1]._transitions[1][0] == "2");
		Assert::IsTrue("2" == states[2]._state_name);
		Assert::IsTrue(states[2]._transitions[0].size() == 0);
	}


	static RE re;
	static FA* fa;
	static RG rg;
};

RE ConversionsTest::re;
FA* ConversionsTest::fa = NULL;
RG ConversionsTest::rg;
#endif // !__RETEST_H__
