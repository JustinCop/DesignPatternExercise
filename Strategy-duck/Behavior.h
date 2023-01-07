#pragma once
#include <iostream>
using namespace std;

// The interface of Fly behavior
class IFlyBehavior
{
public:
    virtual ~IFlyBehavior() {}
    virtual void fly() = 0;
protected:
    IFlyBehavior() {}
};


class FlyFast : public IFlyBehavior
{
public:
    virtual void fly() { cout << "I fly so fast!" << endl; }
};


class FlySlow :public IFlyBehavior
{
public:
    virtual void fly() { cout << "I fly so slow!" << endl; }
};





// The interface of Quack behavior
class IQuackBehavior
{
public:
    virtual ~IQuackBehavior() {}
    virtual void quack() = 0;
protected:
    IQuackBehavior() {}
};

class QuackLoudly : public IQuackBehavior
{
public:
    virtual ~QuackLoudly() {}
    virtual void quack() { cout << "I quack so loud!" << endl; }
};

class QuackQuietly :public IQuackBehavior
{
public:
    virtual ~QuackQuietly() {}
    virtual void quack() { cout << "I quack so quiet, sheee..." << endl; }
};