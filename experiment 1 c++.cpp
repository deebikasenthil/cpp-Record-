#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    int rollNo;
    string name;

public:
    // Parameterized constructor
    Student(int r, const string& n)
        : rollNo(r), name(n)
    {
        cout << "Student object created successfully!" << endl;
    }

    // Member function to display student details
    void display() const
    {
        cout << "\n----- Student Details -----" << endl;
        cout << "Roll Number : " << rollNo << endl;
        cout << "Name        : " << name << endl;
        cout << "---------------------------" << endl;
    }

    // Destructor
    ~Student()
    {
        cout << "Student object destroyed successfully!" << endl;
    }
};

int main()
{
    cout << "Creating student object..." << endl;

    Student s1(101, "Arun");

    s1.display();

    cout << "\nProgram is ending..." << endl;

    return 0;
}