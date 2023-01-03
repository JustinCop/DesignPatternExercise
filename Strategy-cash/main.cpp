#include <algorithm>
#include <iostream>
using namespace std;

// 策略模式-现金收银台
// 节选自《大话设计模式》


// Strategy Interface
class ICashStrategy
{
public:
    virtual ~ICashStrategy() {};

    virtual double calculateFinalPrice(double originalPrice) = 0;
protected:
    ICashStrategy() {}; // 构造函数放到protected，外界就不能实例化这个抽象类，但又要能实例化子类（即：子类要能访问这个类的构造），所以不能放在private里。
};

// 每种收费策略都打包成一个类（接口），可以在CashContext中随时替换。
class CashStrategyNormal :public ICashStrategy
{
public:
    virtual double calculateFinalPrice(double originalPrice)
    {
        return originalPrice;
    }
};


class CashStrategyRebate :public ICashStrategy
{
public:
    CashStrategyRebate(double ratio) :finalPriceRatio(ratio) {}
    virtual double calculateFinalPrice(double originalPrice)
    {
        return originalPrice * finalPriceRatio;
    }
private:
    double finalPriceRatio;
};


class CashStrategyReturn :public ICashStrategy
{
public:
    CashStrategyReturn(double condition, double ret) :condition(condition), ret(ret) {}
    virtual double calculateFinalPrice(double originalPrice)
    {
        int n = floor(originalPrice / condition);
        return originalPrice - n * ret;
    }
private:
    double condition;   // 每满condition，就减ret。例如，每满300减100。
    double ret;
};



// Strategy Context
class CashContext
{
public:
    CashContext(ICashStrategy* pStrategy): m_pStrategy(pStrategy) {}
    void SetStrategy(ICashStrategy* pStrategy) {
        if (m_pStrategy)
        {
            delete m_pStrategy;
        }
        m_pStrategy = pStrategy;
    }
    double calculateFinalPrice(double originalPrice) {
        return m_pStrategy->calculateFinalPrice(originalPrice);
    }
private:
    ICashStrategy* m_pStrategy;
};


int main()
{
    // 缺点：对客户暴露了所有策略的类（CashStrategyNormal，CashStrategyRebate，CashStrategyReturn等）
    CashContext cc(new CashStrategyNormal);
    double price = cc.calculateFinalPrice(1000);
    cout << price << endl;

    cc.SetStrategy(new CashStrategyRebate(0.6));
    price = cc.calculateFinalPrice(1000);
    cout << price << endl;

    cc.SetStrategy(new CashStrategyReturn(300, 100));
    price = cc.calculateFinalPrice(1000);
    cout << price << endl;

    return 0;
}