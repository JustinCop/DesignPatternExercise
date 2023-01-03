#pragma once
#include "Behavior.h"

// Duck is the strategy context
class Duck
{
public:
    Duck(IFlyBehavior* pFB, IQuackBehavior* pQB): m_pFB(pFB), m_pQB(pQB) {}
    ~Duck() {
        if (m_pFB)
        {
            delete m_pFB;
        }
        if (m_pQB)
        {
            delete m_pQB;
        }
    }

    void fly() { m_pFB->fly(); }
    void quack() { m_pQB->quack(); }

private:
    IFlyBehavior* m_pFB;
    IQuackBehavior* m_pQB;

};