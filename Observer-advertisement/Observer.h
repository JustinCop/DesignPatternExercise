#pragma once
#include <iostream>
#include <set>

using namespace std;

class IObserver;

// The subject interface. The subject can be called as an Observable, a Publisher, etc.
// All concreate subject must implement this interface.
class ISubject
{
public:
    virtual ~ISubject() {}
    virtual void addObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notify() = 0;

protected:
    ISubject() {}
};

class IObserver
{
public:
    virtual ~IObserver() {}
    virtual void update() = 0;

    void subscribe(ISubject* subject)
    {
        m_subscribedSubject = subject;
        subject->addObserver(this);
    }

    void unsubscribe()
    {
        if (m_subscribedSubject)
        {
            m_subscribedSubject->removeObserver(this);
            m_subscribedSubject = nullptr;
        }
    }

protected:
    IObserver(): m_subscribedSubject(nullptr) {};
    ISubject* m_subscribedSubject;
};



class WeatherReport : public ISubject
{
public:
    void addObserver(IObserver* observer) override
    {
        m_ObserverSet.insert(observer);
        notify();
    }

    void removeObserver(IObserver* observer) override
    {
        m_ObserverSet.erase(observer);
    }

    void notify() override
    {
        cout << "There are " << m_ObserverSet.size() << " observers subscribing WeatherReport." << endl;
        for (auto iter = m_ObserverSet.begin(); iter != m_ObserverSet.end(); iter++)
        {
            (*iter)->update();
        }
    }

    // Business Logic
    void setTemperature(double temperature)
    {
        m_temperature = temperature;
        notify();
    }

    void setWeather(string weather)
    {
        m_weather = weather;
        notify();
    }

    double getTemperature() const { return m_temperature; }
    string getWeather() const { return m_weather; }

private:
    set<IObserver*> m_ObserverSet;

    double m_temperature;
    string m_weather;
};



class WeatherReportObserver : public IObserver
{
public:
    void update() override
    {
        WeatherReport* pWeatherReport = static_cast<WeatherReport*>(m_subscribedSubject);
        double temperature = pWeatherReport->getTemperature();
        if (temperature >= 20 && temperature <= 25)
        {
            m_hikingAdvice = "Go out for a walk!";
        }
        else
        {
            m_hikingAdvice = "Stay at home!";
        }
        m_hikingAdvice += " The weather is: ";
        m_hikingAdvice += pWeatherReport->getWeather();
    }

    void printHikingAdvice()
    {
        cout << m_hikingAdvice << endl;
    }
private:

    string m_hikingAdvice;
};