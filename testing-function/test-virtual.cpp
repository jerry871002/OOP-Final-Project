#include <iostream>

using namespace std;

class A {
public:
    virtual void printSomething() = 0;
};

class B {
public:
    void sayHi() {
        cout << "Hi" << endl;
    }
};

class C : public A, public B {
    void printSomething() {
        cout << "something" << endl;
        sayHi();
    }
};


int main(int argc, char const *argv[]) {
    /* code */
    A* someA;
    C someC;
    someA = &someC;
    someA->printSomething();
    someA->sayHi();
    return 0;
}
