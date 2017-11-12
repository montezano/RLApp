#ifndef __FATEST_H__
#define __FATEST_H__



#include "CppUnitTest.h"

#include "model/AF.h"

//#define A 1
//#define B 2
//#define C 3 
//#define D 4
//#define F 5 
//#define G 6 
//#define H 7 
//#define I 8 
//#define J 9 
//#define K 10 
//#define L 11
//#define M 12 
//#define N 13
//#define O 14
//#define P 15
//#define Q 16

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

		Assert::IsFalse(fa.isEmpty());

	}

	TEST_METHOD(check_is_empty_success)
	{
		fa.addTerminal("a");
		
		fa.addState({ { 1 } }, REGULAR);
		fa.addState({ { 1 } }, FINAL);

		Assert::IsFalse(fa.isEmpty());

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

		Assert::IsFalse(fa.isEmpty());

	}

	TEST_METHOD(check_is_not_empty)
	{
		fa.addTerminal("a");
		fa.addTerminal("b");


		fa.addState({ { 1 },{ 1, 1 } }, REGULAR);
		fa.addState({ { 1 },{ 1, 1 } }, REGULAR);
		fa.addState({ { 1 },{ 1, 1 } }, REGULAR);
		fa.addState({ { 1 },{ 1, 1 } }, REGULAR);
		fa.addState({ { 1 },{ 1, 1 } }, FINAL);



		//fa.addState({ { 1 } }, FINAL);

		Assert::IsTrue(fa.isEmpty());

	}

	TEST_METHOD(check_is_finite)
	{
		fa.addTerminal("a");
		fa.addTerminal("b");


		fa.addState({ { 1, 1 },{ 1, 1 } }, REGULAR);
		fa.addState({ { 2, 2 },{ 2, 2 } }, REGULAR);
		fa.addState({ { 3, 3 },{ 3, 3 } }, REGULAR);
		fa.addState({ { 4, 4 },{ 4, 4 } }, REGULAR);
		fa.addState({ { 5, 5 },{ 5, 5 } }, FINAL);

		Assert::IsFalse(fa.isInfinite());
	}


	TEST_METHOD(check_is_infinite)
	{
		fa.addTerminal("a");
		fa.addTerminal("b");


		fa.addState({ { 1 },{ 0 } }, REGULAR);
		fa.addState({ { 2 },{ 2 } }, REGULAR);
		fa.addState({ { 3 },{ 1 } }, REGULAR);
		fa.addState({ { 4 },{ 4 } }, REGULAR);
		fa.addState({ { 4 },{ 4 } }, FINAL);

		Assert::IsTrue(fa.isInfinite());
	}

	TEST_METHOD(check_is_infinite_2)
	{
		fa.addTerminal("a");
		fa.addTerminal("b");


		fa.addState({ { 1 },{ 1 } }, REGULAR);
		fa.addState({ { 2 },{ 2 } }, REGULAR);
		fa.addState({ { 3 },{ 3 } }, REGULAR);
		fa.addState({ { 4 },{ 4 } }, REGULAR);
		fa.addState({ { 4 },{ 4 } }, FINAL);

		Assert::IsTrue(fa.isInfinite());
	}

	TEST_METHOD(epsilon_transition_closure_without_E)
	{
		fa.addTerminal("a");
		fa.addTerminal("b");

		QVector<TR> test_state = QVector<TR>({ { 1 },{ 1 } });
		fa.addState(test_state, REGULAR);
		fa.addState({ { 2 },{ 2 } }, REGULAR);
		fa.addState({ { 3 },{ 3 } }, REGULAR);
		fa.addState({ { 4 },{ 4 } }, REGULAR);
		fa.addState({ { 4 },{ 4 } }, FINAL);

		Assert::IsTrue(fa.getEStateClosure(0) == test_state);
	}

	TEST_METHOD(epsilon_transition_closure_with_E_1)
	{
		fa.addTerminal("a");
		fa.addTerminal("&");

		QVector<TR> test_state = QVector<TR>({ { 1, 2, 3, 4 },{ 1, 2, 3, 4 } });
		fa.addState({ { 1 },{ 1 } }, REGULAR);
		fa.addState({ { 2 },{ 2 } }, REGULAR);
		fa.addState({ { 3 },{ 3 } }, REGULAR);
		fa.addState({ { 4 },{ 4 } }, REGULAR);
		fa.addState({ { 4 },{ 4 } }, FINAL);

		Assert::IsTrue(fa.getEStateClosure(0) == test_state);
	}

	TEST_METHOD(epsilon_transition_closure_with_E_2)
	{
		fa.addTerminal("a");
		fa.addTerminal("&");

		QVector<TR> test_state = QVector<TR>({ { 1 },{ 1, 2, 3, 4 } });
		fa.addState({ { 1 },{ 1 } }, REGULAR);
		fa.addState({ { 1 },{ 2 } }, REGULAR);
		fa.addState({ { 1 },{ 3 } }, REGULAR);
		fa.addState({ { 1 },{ 4 } }, REGULAR);
		fa.addState({ { 1 },{ 1 } }, FINAL);

		Assert::IsTrue(fa.getEStateClosure(0) == test_state);
	}

	TEST_METHOD(epsilon_transition_closure_with_E_3)
	{
		fa.addTerminal("a");
		fa.addTerminal("&");

		QVector<TR> test_state = QVector<TR>({ { 1 },{ } });
		fa.addState({ { 1 },{  } }, REGULAR);
		fa.addState({ { 1 },{  } }, REGULAR);
		fa.addState({ { 1 },{  } }, REGULAR);
		fa.addState({ { 1 },{  } }, REGULAR);
		fa.addState({ { 1 },{ 1 } }, FINAL);

		Assert::IsTrue(fa.getEStateClosure(0) == test_state);
	}

	TEST_METHOD(remove_E_transition)
	{
		fa.addTerminal("a");
		fa.addTerminal("&");

		QVector<TR> test_state = QVector<TR>({ { 0, 1, 2 }});
		fa.addState({ { 0 },{ 1 } }, REGULAR);
		fa.addState({ { 1 },{ 2 } }, REGULAR);
		fa.addState({ { 2 },{ 2 } }, FINAL);

		fa.removeETransition();
		Assert::IsTrue( fa.getStates()[0]._transitions == test_state);
	}

	TEST_METHOD(remove_E_transition_without_E_trans)
	{
		fa.addTerminal("a");

		QVector<TR> test_state = QVector<TR>({ { 0 } });
		fa.addState({ { 0 } }, REGULAR);
		fa.addState({ { 1 } }, REGULAR);
		fa.addState({ { 2 } }, FINAL);

		fa.removeETransition();
		Assert::IsTrue(fa.getStates()[0]._transitions == test_state);
	}

	TEST_METHOD(determinize_1_no_E)
	{
		QVector<TR> test_state = QVector<TR>({ { 0, 1, 2 } });

		fa.addTerminal("a");

		fa.addState({ { 0, 1 } }, REGULAR);
		fa.addState({ { 2 } }, REGULAR);
		fa.addState({ { 2 } }, FINAL);

		fa.determinize();
		Assert::IsTrue(fa.getDetStates()[2]._transitions == test_state);
	}

	TEST_METHOD(determinize_2_no_E)
	{
		QVector<TR> test_state = QVector<TR>({ { 2 }, { 1, 2} });

		fa.addTerminal("a");
		fa.addTerminal("b");

		fa.addState({ { 0, 1 }, { 1, 2 } }, REGULAR);
		fa.addState({ { 2 }, { 2 } }, REGULAR);
		fa.addState({ { 2 }, { 1 } }, FINAL);

		fa.determinize();
		Assert::IsTrue(fa.getDetStates("1-2")._transitions == test_state);
	}

	TEST_METHOD(remove_dead_states)
	{
		QVector<TR> test_state = QVector<TR>({ { 2 },{ -1 } });

		fa.addTerminal("a");
		fa.addTerminal("b");

		/*0-*/fa.addState({ { 2 },{ 1 } }, REGULAR);
		/*1-*/fa.addState({ { 1 },{ 1 } }, REGULAR);
		/*2-*/fa.addState({ { 2 },{ 2 } }, FINAL);

		fa.determinize();
		fa.removeDeadStates();
		Assert::IsTrue(fa.getDetStates("0")._transitions == test_state);
		Assert::AreEqual(2, fa.getDetStates().size());
	}

	TEST_METHOD(equivalence_class)
	{
		QVector<TR> test_state = QVector<TR>({ { 0, 1 },{ 1 , 2 } });

		fa.addTerminal("a");
		fa.addTerminal("b");

		fa.addState({ { 0, 1 },{ 1, 2 } }, REGULAR);
		fa.addState({ { 2 },{ 2 } }, REGULAR);
		fa.addState({ { 2 },{ 1 } }, FINAL);

		fa.determinize();
		fa.removeDeadStates();
		fa.removeEquivalenceClasses();
		Assert::IsTrue(fa.getDetStates("0")._transitions == test_state);
	}

	TEST_METHOD(minimize)
	{
		QVector<TR> test_state_2 = QVector<TR>({ { 1 },{ 2 } });

		fa.addTerminal("a");
		fa.addTerminal("b");

		/*A*/fa.addState({ { 6 },{ 1 } }, FINAL);
		/*B*/fa.addState({ { 5 },{ 4 } }, REGULAR);
		/*C*/fa.addState({ { 2 },{ 6 } }, REGULAR);
		/*D*/fa.addState({ { 0 },{ 7 } }, FINAL);
		/*E*/fa.addState({ { 4 },{ 0 } }, REGULAR);
		/*F*/fa.addState({ { 1 },{ 2 } }, REGULAR);
		/*G*/fa.addState({ { 6 },{ 5 } }, FINAL);
		/*H*/fa.addState({ { 7 },{ 3 } }, REGULAR);
		

		fa.determinize();
		fa.removeDeadStates();
		fa.removeEquivalenceClasses();
		Assert::AreEqual(fa.getDetStates().size(), 3);
		Assert::IsTrue(fa.getDetStates("1")._transitions == test_state_2);
	}

	//#define A 0
	//#define B 1
	//#define C 2 
	//#define D 3
	//#define E 4
	//#define F 5 
	//#define G 6 
	//#define H 7 
	//#define I 8 
	//#define J 9
	//TEST_METHOD(remove_E_transition)
	//{
	//	Assert::isTru
	//}
	//TEST_method(add_state_)

	static FA fa;
};

FA FAtest::fa;
#endif // !__FATEST_H__
