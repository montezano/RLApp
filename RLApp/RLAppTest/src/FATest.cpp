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

	TEST_METHOD(creation)
	{
		FA fa = FA();
		fa.setFA("string");

		Assert::IsTrue(0 == fa.getRe().compare(QString("string")));
		Assert::IsFalse(0 == re.getRe().compare(QString("string2")));
	}

};