#ifndef __FATEST_H__
#define __FATEST_H__



#include "CppUnitTest.h"

#include "model/AF.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(FAtest)
{
public:

	FAtest()
	{

	}

	~FAtest()
	{

	}

	TEST_METHOD_INITIALIZE(MethodInitialize)
	{
		fa = FA();
	}
	
	TEST_METHOD_CLEANUP(MethodCleanup)
	{
	}

	TEST_METHOD(creation)
	{
		//FA dfa = FA();

		//FA fa = FA();
		//fa.setFA("string");

		//Assert::IsTrue(0 == fa.getRe().compare(QString("string")));
		//Assert::IsFalse(0 == re.getRe().compare(QString("string2")));
	}

	TEST_METHOD(add_terminals_true)
	{
		//FA fa = FA();

		fa.addTerminal("a");

		Assert::IsTrue(fa.getTerminals().contains("a"));
	}

	TEST_METHOD(add_transition_false)
	{
		//FA fa = FA();

		fa.addTerminal("a");
		fa.addTerminal("b");

		Assert::IsFalse(fa.getTerminals().contains("c"));
	}

	TEST_METHOD(add_state_wrong_size)
	{
		Assert::IsFalse(fa.addState({ {1}, {2}, {3} }, FINAL));
	}

	TEST_METHOD(add_state_successufully)
	{
		fa.addTerminal("a");
		fa.addTerminal("b");
		fa.addTerminal("c");

		Assert::IsTrue(fa.addState({ {1}, {2}, {3} }, FINAL));
	}

	TEST_METHOD(check_is_empty_one_state)
	{
		fa.addTerminal("a");

		fa.addState({ { 0 } }, FINAL);

		Assert::IsTrue(fa.isEmpty());

	}

	TEST_METHOD(check_is_empty_success)
	{
		fa.addTerminal("a");
		
		fa.addState({ { 1 } }, REGULAR);
		fa.addState({ { 1 } }, FINAL);

		Assert::IsTrue(fa.isEmpty());

	}

	TEST_METHOD(check_is_empty_success_2)
	{
		fa.addTerminal("a");
		fa.addTerminal("b");


		fa.addState({ { 1, 1 }, { 1, 1 } }, REGULAR);
		fa.addState({ { 1, 2 }, { 1, 1 } }, REGULAR);
		fa.addState({ { 1, 3 }, { 1, 1 } }, REGULAR);
		fa.addState({ { 1, 4 }, { 1, 1 } }, REGULAR);
		fa.addState({ { 1, 4 }, { 1, 1 } }, FINAL);



		//fa.addState({ { 1 } }, FINAL);

		Assert::IsTrue(fa.isEmpty());

	}
	//TEST_method(add_state_)

	static FA fa;
};

FA FAtest::fa;
#endif // !__FATEST_H__
