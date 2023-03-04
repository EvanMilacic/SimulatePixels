#include "pch.h"
#include "CppUnitTest.h"
#include "../TestScreenOutput/Field.h"
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

	TEST_CLASS(TestField) {
public:
	TEST_METHOD(Constructor) {
		
	}

	};
}