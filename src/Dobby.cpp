#include <iostream>
#include "Dobby.h"

using namespace std;

int main()
{
	MediumA mediumA(1, 2, 3);
	MediumB mediumB(10, 20, 30);
	BigA bigA(mediumA, 100, 200);
	BigB bigB(mediumB, 1000, 1000);
	UltraBigAB ultraBigAB(bigA, bigB, 10000, 20000);

	CapturedDobby capturedDobby;
	cout << "capturedDobby something : " << capturedDobby.doSomethingBad(50, ultraBigAB) << endl;

	ReleasedDobby releasedDobby;
	auto delegate = [&ultraBigAB](int x) {
		return x + ultraBigAB.doSomethingA() + ultraBigAB.doSomethingB();
	};
	cout << "releasedDobby : " << releasedDobby.doSomethingGood(50, delegate) << endl;

	// for test
	ReleasedDobby testDobby;
	auto testDelegate = [](int x) { return x + 10 + 20; };
	cout << "testDobby test caseA : " << testDobby.doSomethingGood(50, testDelegate) << endl;

	FakeUltraBigAB fakeUltraBigAB(10000, 20000);
	fakeUltraBigAB.setFakeValueForBigA(306);
	fakeUltraBigAB.setFakeValueForBigB(2060);
	auto testDelegateUsingFake = [&fakeUltraBigAB](int x) {
		return x + fakeUltraBigAB.doSomethingA() + fakeUltraBigAB.doSomethingB();
	};
	cout << "testDobby test caseB : " << testDobby.doSomethingGood(50, testDelegateUsingFake) << endl;

	return 0;
}
