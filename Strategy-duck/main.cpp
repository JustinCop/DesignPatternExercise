#include "Duck.h"
#include "Behavior.h"

// 策略模式 - 鸭子的不同行为。
// 节选自 Head First Design Pattern
// 有了灵活设置行为的方法，就不用从Duck各种继承Duck的子类了。

int main()
{
    Duck cityDuck(new FlySlow, new QuackQuietly);
    cityDuck.fly();
    cityDuck.quack();

    Duck countryDuck(new FlyFast, new QuackLoudly);
    countryDuck.fly();
    countryDuck.quack();

    return 0;
}