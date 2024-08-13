#include <iostream>

// NOTE!: all the comments assume this was compiled in x86
// the same things will happen in x64 but with different offsets due to the different ptr size

class Base1 {
protected:
	// Field in base1
	int c = 256;
public:
	virtual void DummyVirt() {
		std::cout << "This is a dummy virtual function" << std::endl;
	}
};

class Base2 {
protected:
	// Field in base2
	int d = 128;
public:
	// Virtual function in base2
	virtual int GetC() {
		return 0;
	}
};

class Derived : public Base1, public Base2 {
public:
	// Field in derived
	int e = 64;
public:
	void DummyVirt() override {
		Base1::DummyVirt();
	}

	// Get field in base1 by overriding function in base2
	int GetC() override {
		// everything will be offset by sizeof(Base1) because "this" is a Derived* offset to be a Base2*
		// sizeof(Base1) = 8 bytes
		
		// will be this + -4 in ghidra, when it is Derived + 0x4, dif = +8
		int c = this->c;
		// will be this + 4 in ghidra, when it is Derived + 0xc, dif = +8
		int d = this->d;
		// will be this + 8 in ghidra, when it is Derived + 0x10, dif = +8
		int e = this->e;
		// ^ these are all offset in relation to the Base2 vftable instead, aka the start of the Base2 struct
		return c + d + e;
	}
};

int main() {
	Derived* derived = new Derived;
	// Calling getC here will pass in the ptr to the Base2_vftable in derived for "this"
	std::cout << derived->GetC() << std::endl;

	delete derived;
}
