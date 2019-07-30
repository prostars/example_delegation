#include <functional>

class MediumA {
public:
	MediumA(int valueA, int valueB, int valueC) : valueA(valueA), valueB(valueB), valueC(valueC) {}
	int doSomething() { return valueA + valueB + valueC; }
private:
	int valueA;
	int valueB;
	int valueC;
};

class MediumB {
public:
	MediumB(int valueA, int valueB, int valueC) : valueA(valueA), valueB(valueB), valueC(valueC) {}
	int doSomething() { return valueA + valueB + valueC; }
private:
	int valueA;
	int valueB;
	int valueC;
};

class BigA {
public:
	BigA(const MediumA &mediumA, int valueA, int valueB)
		: mediumA(mediumA), valueA(valueA), valueB(valueB) {}
	int doSomething() { return mediumA.doSomething() + valueA + valueB; };

private:
	MediumA mediumA;
	int valueA;
	int valueB;
};

class BigB {
public:
	BigB(const MediumB &mediumB, int valueA, int valueB)
			: mediumB(mediumB), valueA(valueA), valueB(valueB) {}
	int doSomething() { return mediumB.doSomething() + valueA + valueB; };

private:
	MediumB mediumB;
	int valueA;
	int valueB;
};


class UltraBigAB {
public:
	UltraBigAB(const BigA &bigA, const BigB &bigB, int valueA, int valueB)
		: bigA(bigA), bigB(bigB), valueA(valueA), valueB(valueB) {}
	int doSomethingA() { return bigA.doSomething() + valueA + valueB; }
	int doSomethingB() { return bigB.doSomething() + valueA + valueB; }
private:
	BigA bigA;
	BigB bigB;
	int valueA;
	int valueB;
};

class FakeUltraBigAB {
public:
	FakeUltraBigAB(int valueA, int valueB)
			: valueA(valueA), valueB(valueB), fakeValueForBigA(0), fakeValueForBigB(0) {}
	void setFakeValueForBigA(int value) { fakeValueForBigA = value; }
	void setFakeValueForBigB(int value) { fakeValueForBigB = value; }
	int doSomethingA() { return fakeValueForBigA + valueA + valueB; }
	int doSomethingB() { return fakeValueForBigB + valueA + valueB; }
private:
	int valueA;
	int valueB;
	int fakeValueForBigA;
	int fakeValueForBigB;
};

class CapturedDobby {
public:
	int getSomeValue() { return 42; }
	int doSomethingBad(int x, UltraBigAB &ultraBigAB) {
		// do something

		int result = x + ultraBigAB.doSomethingA() + ultraBigAB.doSomethingB();

		// do something
		return result;
	}
};

class ReleasedDobby {
public:
	int getSomeValue() { return 42; }
	int doSomethingGood(int x, const std::function<int(int)> &delegate) {
		// do something

		int result = delegate(x);

		// do something
		return result;
	}
};

class HalfReleasedDobby {
public:
	int getSomeValue() { return 42; }
	int doSomething(int x, UltraBigAB &ultraBigAB) {
		// do something

		auto delegate = [&ultraBigAB](int x) {
			return x + ultraBigAB.doSomethingA() + ultraBigAB.doSomethingB();
		};
		int result = doSomethingGood(x, delegate);

		// do something
		return result;
	}
protected:
	int doSomethingGood(int x, const std::function<int(int)>& delegate) {
		// do something

		int result = delegate(x);

		// do something
		return result;
	}
};
