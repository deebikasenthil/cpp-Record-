#include <iostream>
#include <memory>
using namespace std;

// Resource Management Class
class Device
{
public:
    Device()
    {
        cout << "Device resource allocated successfully." << endl;
    }

    ~Device()
    {
        cout << "Device resource released successfully." << endl;
    }

    void operate()
    {
        cout << "Device is operating..." << endl;
    }
};

// Custom Smart Pointer using RAII
class CustomPointer
{
private:
    Device* ptr;

public:
    // Constructor
    CustomPointer(Device* p)
    {
        ptr = p;
        cout << "Custom pointer initialized." << endl;
    }

    // Destructor
    ~CustomPointer()
    {
        delete ptr;
        cout << "Custom pointer destroyed." << endl;
    }

    // Overloading arrow operator
    Device* operator->()
    {
        return ptr;
    }

    // Prevent copying
    CustomPointer(const CustomPointer&) = delete;
    CustomPointer& operator=(const CustomPointer&) = delete;
};

int main()
{
    cout << "===== CUSTOM RAII POINTER =====" << endl;

    {
        CustomPointer devicePtr(new Device());
        devicePtr->operate();
    }

    cout << "\n===== UNIQUE POINTER =====" << endl;

    {
        unique_ptr<Device> uniqueDevice =
            make_unique<Device>();

        uniqueDevice->operate();

        cout << "Unique pointer is managing one device." << endl;
    }

    cout << "\n===== SHARED POINTER =====" << endl;

    {
        shared_ptr<Device> device1 =
            make_shared<Device>();

        shared_ptr<Device> device2 = device1;

        device1->operate();

        cout << "Number of shared owners: "
             << device1.use_count() << endl;
    }

    cout << "\n===== PROGRAM EXECUTION COMPLETED =====" << endl;

    return 0;
}