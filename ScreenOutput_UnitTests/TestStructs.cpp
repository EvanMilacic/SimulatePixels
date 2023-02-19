#include "pch.h"
#include "CppUnitTest.h"
#include "../TestScreenOutput/Index2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<>
			static std::wstring ToString<struct Index2>(const struct Index2& ind) {
				return L"i = " + std::to_wstring(ind.i) + L" and j =" + std::to_wstring(ind.j);
			}
		}
	}
}

namespace UnitTests {

	TEST_CLASS(TestIndex) {
		//Test class to test the Index2 implementations
public:

	//Tests the operator overload +
	TEST_METHOD(Add) {
		Index2 ind{ 0,0 };
		Index2 add{ 0,1 };
		Index2 result = ind + add;
		Assert::AreEqual(add, result);
	}
	//Tests the operator overload +=
	TEST_METHOD(AddIs) {
		const Index2 ind{ 0,0 };
		const Index2 add{ 0,1 };
		Index2 result = ind;
		result += add;
		Assert::AreEqual(add, result);
	}
	//Tests the operator overload -
	TEST_METHOD(Sub) {
		Index2 ind{ 0,0 };
		Index2 sub{ 0,1 };
		Index2 truth{ 0,-1 };
		Index2 result = ind - sub;
		Assert::AreEqual(truth, result);
	}

	//Tests the operator overload -=
	TEST_METHOD(SubIs) {
		Index2 ind{ 0,0 };
		Index2 sub{ 0,1 };
		Index2 truth{ 0,-1 };
		Index2 result = ind;
		result -= sub;
		Assert::AreEqual(truth, result);
	}

	TEST_METHOD(IsEqual) {
		Index2 a{ 1,0 };
		Index2 b{ 0,0 };
		Index2 c{ 0,0 };

		bool ab = (a == b);
		bool bc = (b == c);

		Assert::AreNotEqual(ab, bc);
	}

	};

}