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


	static RE re;
	static FA fa;
};

RE ConversionsTest::re;
FA ConversionsTest::fa;
#endif // !__RETEST_H__
