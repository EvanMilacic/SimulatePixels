#include "pch.h"
#include "CppUnitTest.h"
#include "../TestScreenOutput/Domain.h"
#include "../TestScreenOutput/Domain.cpp"
#include "../TestScreenOutput/Enums.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<>
			static std::wstring ToString<enum MatType>(const enum MatType& type) {
				return L"i = " + std::to_wstring((int)type);
			}
		}
	}
}

namespace UnitTests {

	TEST_CLASS(TestDomain) {
public:
	TEST_METHOD(Constructor) {
		int width = 10;
		int height = 12;
		int size = width * height;
		simulate::Domain testDomain(width, height);

		Assert::AreEqual(size, testDomain.getSize());
	}

	TEST_METHOD(Set2D) {
		simulate::Domain testDomain(5, 5);
		testDomain.set(2, 2, MatType::Sand);
		Assert::AreEqual(MatType::Sand, testDomain.at(2, 2));
	}

	TEST_METHOD(Set1D) {
		simulate::Domain testDomain(5, 5);
		testDomain.set(15, MatType::Sand);
		Assert::AreEqual(MatType::Sand, testDomain.at(15));
	}

	TEST_METHOD(OnEdgeTest) {
		simulate::Domain testDomain(5, 5);
		Assert::IsTrue(testDomain.isOnEdge(4));
		Assert::IsTrue(testDomain.isOnEdge(5));
		Assert::IsTrue(testDomain.isOnEdge(24));
		Assert::IsFalse(testDomain.isOnEdge(15));
	}

	TEST_METHOD(Move) {
		Index2 start{ 2,2 };
		simulate::Domain testDomain(5, 5);
		testDomain.set(start, MatType::Sand);
		bool testBool = testDomain.move(start, MoveDirs::Up);
		Assert::AreEqual(MatType::Sand, testDomain.at(start,MoveDirs::Up));
	}

	};

}