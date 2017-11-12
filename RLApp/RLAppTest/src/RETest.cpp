#ifndef __RETEST_H__
#define __RETEST_H__



#include "CppUnitTest.h"

#include "model/RE.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(REtest)
{
public:

	REtest()
	{

	}

	~REtest()
	{

	}

	TEST_METHOD(creation)
	{
		RE re = RE();
		re.setReString("string");

		Assert::IsTrue(0 == re.getReString().compare(QString("string")));
		Assert::IsFalse(0 == re.getReString().compare(QString("string2")));
	}

};

#endif // !__RETEST_H__
