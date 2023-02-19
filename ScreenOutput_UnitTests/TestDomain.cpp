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

	TEST_METHOD(Clear) {
		simulate::Domain testDomain(5, 5);
		testDomain.set(24, MatType::Blood);
		testDomain.clear(24);
		Assert::AreEqual(testDomain.at(24), MatType::Default);
	}
	TEST_METHOD(CalcIndexTesting) {
		
		//Test conversion to 1D
		simulate::Domain test1D(4, 6);
		test1D.set(3,5, MatType::Sand);
		Assert::AreEqual(test1D.at(23),MatType::Sand);

		//Test conversion to 2D
		simulate::Domain test2D(4, 6);
		test2D.set(23, MatType::Sand);
		Assert::AreEqual(test2D.at(23), MatType::Sand);
	}

	TEST_METHOD(OnEdgeTest) {
		simulate::Domain testDomain(4, 6);
		Assert::IsTrue(testDomain.isOnEdge(0));
		Assert::IsTrue(testDomain.isOnEdge(4));
		Assert::IsTrue(testDomain.isOnEdge(8));
		Assert::IsTrue(testDomain.isOnEdge(23));
		Assert::IsFalse(testDomain.isOnEdge(5));
	}

	TEST_METHOD(Move) {
		Index2 start{ 2,2 };
		simulate::Domain testDomain(5, 5);
		testDomain.set(start, MatType::Sand);
		bool testBool = testDomain.move(start, MoveDirs::Up);
		Assert::AreEqual(MatType::Sand, testDomain.at(start,MoveDirs::Up));
	}

	TEST_METHOD(Flip) {
		simulate::Domain testDomain(4, 6);
		Index2 ind1{ 3,5 };
		Index2 ind2{ 0,0 };
		testDomain.set(ind1, MatType::Blood);
		testDomain.set(ind2, MatType::Smoke);
		testDomain.flip(ind1,ind2);
		Assert::AreEqual(testDomain.at(ind1), MatType::Smoke);
		Assert::AreEqual(testDomain.at(ind2), MatType::Blood);
	}

	TEST_METHOD(GetDirectionIndex) {

	}

	TEST_METHOD(GetMotionVector) {

	}

	};

}