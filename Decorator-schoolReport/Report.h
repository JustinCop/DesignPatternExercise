#pragma once
#include <iostream>
using namespace std;

// 抽象成绩单类
class SchoolReport
{
public:
    virtual ~SchoolReport() {}

    // 报告成绩
    virtual void report() = 0;

    // 请家长签字
    virtual void sign(const char* name) = 0;
protected:
    SchoolReport() {}
};


// 具体的四年级成绩单类
class FourthGradeReport :public SchoolReport
{
public:
    virtual ~FourthGradeReport() {};

    virtual void report() override
    {
        cout << "Dear xxx parent:" << endl;
        cout << "    ......" << endl;
        cout << "    Chinese 62    Math 65    English 70" << endl;
        cout << "    ......" << endl;
        cout << "            Parent signature:    " << endl;
    }

    virtual void sign(const char* name) override
    {
        cout << "Parent signed as: " << name << endl;
    }
};


// 成绩单的修饰器
// 既 is-a SchoolReport，又 has-a SchoolReport
class Decorator: public SchoolReport
{
public:
    virtual ~Decorator() {}

    virtual void report() override
    {
        this->m_pSR->report();
    }
    virtual void sign(const char* name) override
    {
        this->m_pSR->sign(name);
    }

protected:
    Decorator(SchoolReport* pSR) :m_pSR(pSR) {}


private:
    SchoolReport* m_pSR;    // 最核心，最原初的那个SchoolReport（当然不是SchoolReport这个抽象类，而是其某个具体子类的实例）

};

// 每个具体的修饰器都要自己重写report()和sign()

// 具体的修饰器1：要先汇报最高成绩的修饰器
class HighScoreDecorator : public Decorator
{
public:
    HighScoreDecorator(SchoolReport* pSR) :Decorator(pSR) {}
    virtual ~HighScoreDecorator() {}

    virtual void report() override
    {
        // 在调用被修饰者的方法前，可以先用自己的方法修饰一下
        this->reportHighScore();
        // 然后调用被修饰者的方法
        Decorator::report();
    }

private:
    // 我的装饰方法
    void reportHighScore()
    {
        cout << "High score:    Chinese 70    Math 72    English 76" << endl;
    }
};


// 具体的修饰器2：要汇报我的排名
class SortDecorator : public Decorator
{
public:
    SortDecorator(SchoolReport* pSR) :Decorator(pSR) {}
    virtual ~SortDecorator() {}

    virtual void report() override
    {
        // 也可以先调用被修饰者的方法
        Decorator::report();
        // 然后再调用我的修饰方法
        this->reportOrder();
    }
private:
    // 我的装饰方法
    void reportOrder()
    {
        cout << "I am number 10." << endl;
    }
};