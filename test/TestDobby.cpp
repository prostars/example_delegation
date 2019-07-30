#include "../src/Dobby.h"
#include "gtest/gtest.h"

class TestHalfReleasedDobby : public HalfReleasedDobby, public testing::Test {};

TEST_F(TestHalfReleasedDobby, TestDobbySimple) {
	auto testDelegate = [](int x) { return x + 10 + 20; };
	int result = doSomethingGood(50, testDelegate);
	ASSERT_EQ(result, 80);
}

TEST_F(TestHalfReleasedDobby, TestDobbyUsingFake) {
	FakeUltraBigAB fakeUltraBigAB(10000, 20000);
	fakeUltraBigAB.setFakeValueForBigA(306);
	fakeUltraBigAB.setFakeValueForBigB(2060);
	auto testDelegateUsingFake = [&fakeUltraBigAB](int x) {
		return x + fakeUltraBigAB.doSomethingA() + fakeUltraBigAB.doSomethingB();
	};
	int result = doSomethingGood(50, testDelegateUsingFake);
	ASSERT_EQ(result, 62416);
}
