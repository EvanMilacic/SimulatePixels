#include "pch.h"
#include "CppUnitTest.h"
#include "../TestScreenOutput/Structs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TestIndex2) {
public:
	TEST_METHOD(TestAddition) {
		Index2 ind{ 0,0 };
		Index2 add{ 0,1 };
		Index2 result = ind + add;
		Assert::AreEqual(ind, result);
	}
};
}