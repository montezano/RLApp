#ifndef __RETEST_H__
#define __RETEST_H__



#include "CppUnitTest.h"

#include "model/RE.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(RETest)
{
public:

	RETest()
	{

	}

	~RETest()
	{

	}

	TEST_METHOD_INITIALIZE(MethodInitialize)
	{
		re = RE();
	}

	TEST_METHOD_CLEANUP(MethodCleanup)
	{
	}

	TEST_METHOD(set_re_original)
	{
		re.setReString("string");

		Assert::IsTrue(0 == re.getOriginalReString().compare(QString("string")));
		Assert::IsFalse(0 == re.getOriginalReString().compare(QString("string2")));
	}

	TEST_METHOD(set_re_dot)
	{
		re.setReString("string");

		Assert::AreEqual("s.t.r.i.n.g", re.getDotReString().toStdString().c_str());
		Assert::IsFalse(0 == re.getDotReString().compare(QString("string")));
	}

	TEST_METHOD(set_re_dot_with_operators)
	{
		re.setReString("s*(tr | n*g)");

		Assert::AreEqual("s*.(t.r|n*.g)", re.getDotReString().toStdString().c_str());
		Assert::IsFalse(0 == re.getDotReString().compare(QString("s*(tr | n*g)")));
	}

	TEST_METHOD(set_re_dot_with_operators_2)
	{
		re.setReString("s*(tr | n*g)(a*)");

		Assert::AreEqual("s*.(t.r|n*.g).(a*)", re.getDotReString().toStdString().c_str());
		Assert::AreNotEqual("s*(tr | n*g)(a*)", re.getDotReString().toStdString().c_str());
	}

	TEST_METHOD(parse_disjunction_operator_1)
	{
		re.setReString("s*(tr) | (n*g)(a*)");

		QList<QString> parsed_string = re.parseSymbol(DISJUNCT);

		Assert::AreEqual("s*.(t.r)", parsed_string[0].toStdString().c_str());
		Assert::AreNotEqual("(n*.g)(a*)", parsed_string[1].toStdString().c_str());
	}

	TEST_METHOD(parse_disjunction_operator_2)
	{
		re.setReString("s*(tr) | (n* | g)(a*)");

		QList<QString> parsed_string = re.parseSymbol(DISJUNCT);

		Assert::AreEqual("s*.(t.r)", parsed_string[0].toStdString().c_str());
		Assert::AreNotEqual("(n*|g)(a*)", parsed_string[1].toStdString().c_str());
	}

	TEST_METHOD(parse_conjunction_operator)
	{
		re.setReString("s(a|b)|c");

		re.parse();
		Node* tree = re.getDiSimoneTree();

		Assert::IsTrue('|' == tree->symbol);
		Assert::IsTrue('.' == tree->left_children->symbol);
		Assert::IsTrue('s' == tree->left_children->left_children->symbol);
		Assert::IsTrue('|' == tree->left_children->right_children->symbol);
		Assert::IsTrue('a' == tree->left_children->right_children->left_children->symbol);
		Assert::IsTrue('b' == tree->left_children->right_children->right_children->symbol);
		Assert::IsTrue('c' == tree->right_children->symbol);
	}


	static RE re;
};

RE RETest::re;
#endif // !__RETEST_H__
