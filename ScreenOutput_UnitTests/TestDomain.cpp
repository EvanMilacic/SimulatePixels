#include "pch.h"
#include "CppUnitTest.h"
#include "../TestScreenOutput/Domain.h"
#include "../TestScreenOutput/Domain.cpp"
#include "../TestScreenOutput/Enums.h"
#include "../TestScreenOutput/FieldData.h"
#include <iostream>

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
		FieldData fData = { 10,12,120 };
		simulate::Domain testDomain(fData);

		Assert::AreEqual(fData.Size, testDomain.getSize());
	}

	TEST_METHOD(Set2D) {
		FieldData fData = { 5,5,25 };
		simulate::Domain testDomain(fData);
		Index2 ind = { 2,2 };
		testDomain.set(ind, MatType::Sand);
		Assert::AreEqual(MatType::Sand, testDomain.at(ind));
	}

	TEST_METHOD(Clear) {
		FieldData fData = { 5,5,25 };
		simulate::Domain testDomain(fData);
		testDomain.set({3,4}, MatType::Blood);
		testDomain.clear({3,4});
		Assert::AreEqual(testDomain.at({3,4}), MatType::Default);
	}

	TEST_METHOD(OnEdgeTest) {
		FieldData fData = {4,6,24};
		simulate::Domain testDomain(fData);
		Assert::IsTrue(testDomain.isOnEdge({0,1}));
		Assert::IsTrue(testDomain.isOnEdge({2,0}));
		Assert::IsTrue(testDomain.isOnEdge({ 0,5 }));
		Assert::IsTrue(testDomain.isOnEdge({3,5}));
		Assert::IsFalse(testDomain.isOnEdge({2,2}));
	}

	TEST_METHOD(Move) {
		Index2 start{ 2,2 };
		FieldData fData = { 5,5,25 };
		simulate::Domain testDomain(fData);
		testDomain.set(start, MatType::Sand);
		bool testBool = testDomain.move(start, MoveDirs::Up);
		Assert::AreEqual(MatType::Sand, testDomain.at(start,MoveDirs::Up));
	}

	TEST_METHOD(Flip) {
		FieldData fData = { 4,6,24 };
		simulate::Domain testDomain(fData);
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