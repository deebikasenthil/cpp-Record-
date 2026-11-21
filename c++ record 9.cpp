
#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// Observer Interface
class Observer
{
public:
    virtual void notify(const string& message) = 0;
    virtual ~Observer() {}
};

// Email Notification
class EmailNotification : public Observer
{
private:
    string email;

public:
    EmailNotification(string e)
    {
        email = e;
    }

    void notify(const string& message) override
    {
        cout << "Email notification to " << email
             << ": " << message << endl;
    }
};

// SMS Notification
class SMSNotification : public Observer
{
private:
    string phoneNumber;

public:
    SMSNotification(string number)
    {
        phoneNumber = number;
    }

    void notify(const string& message) override
    {
        cout << "SMS notification to " << phoneNumber
             << ": " << message << endl;
    }
};

// Notification Factory
class NotificationFactory
{
public:
    static shared_ptr<Observer> createNotification(
        const string& type,
        const string& receiver)
    {
        if (type == "EMAIL")
        {
            return make_shared<EmailNotification>(receiver);
        }
        else if (type == "SMS")
        {
            return make_shared<SMSNotification>(receiver);
        }

        return nullptr;
    }
};

// Singleton Event Manager
class EventManager
{
private:
    vector<shared_ptr<Observer>> observers;

    EventManager()
    {
    }

public:
    EventManager(const EventManager&) = delete;

    EventManager& operator=(const EventManager&) = delete;

    static EventManager& getInstance()
    {
        static EventManager instance;
        return instance;
    }

    void subscribe(shared_ptr<Observer> observer)
    {
        observers.push_back(observer);
    }

    void triggerEvent(const string& message)
    {
        cout << "\nNew Event: " << message << endl;

        cout << "Notifying all subscribers...\n";

        for (auto observer : observers)
        {
            observer->notify(message);
        }
    }
};

int main()
{
    // Get Singleton Event Manager
    EventManager& manager = EventManager::getInstance();

    // Create notifications using Factory
    shared_ptr<Observer> emailUser =
        NotificationFactory::createNotification(
            "EMAIL",
            "rahul@gmail.com");

    shared_ptr<Observer> smsUser =
        NotificationFactory::createNotification(
            "SMS",
            "9123456780");

    // Subscribe users
    manager.subscribe(emailUser);
    manager.subscribe(smsUser);

    // Send event notification
    manager.triggerEvent(
        "Annual College Festival will be held next week!");

    return 0;
}
