#include <set>
using namespace std;
#include "Observer.h"

int main()
{
    WeatherReport wr;
    wr.setTemperature(23);
    wr.setWeather("Warm");

    WeatherReportObserver wrob;
    wrob.subscribe(&wr);
    
    wrob.printHikingAdvice();

    wr.setTemperature(10);
    wr.setWeather("Cold");

    wrob.printHikingAdvice();


    return 0;
}