#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <iomanip>
using namespace std;

class Student
{
public:
    string name;
    int mark;
    char grade;

    Student(string n, int m)
        : name(n), mark(m), grade(' ')
    {
    }
};

int main()
{
    vector<Student> students = {
        {"Priya", 88},
        {"Divya", 76},
        {"Karthik", 95},
        {"Sneha", 68},
        {"Rahul", 82}
    };

    // Sort students by marks in descending order
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b)
         {
             return a.mark > b.mark;
         });

    // Assign grades using transform
    transform(students.begin(), students.end(),
              students.begin(),
              [](Student s)
              {
                  if (s.mark >= 90)
                      s.grade = 'A';
                  else if (s.mark >= 80)
                      s.grade = 'B';
                  else if (s.mark >= 70)
                      s.grade = 'C';
                  else if (s.mark >= 60)
                      s.grade = 'D';
                  else
                      s.grade = 'F';

                  return s;
              });

    // Find the first student scoring above 85
    auto it = find_if(students.begin(), students.end(),
                      [](const Student& s)
                      {
                          return s.mark > 85;
                      });

    // Calculate total marks
    int total = accumulate(students.begin(), students.end(), 0,
                           [](int sum, const Student& s)
                           {
                               return sum + s.mark;
                           });

    // Calculate average
    double average = static_cast<double>(total) / students.size();

    // Display results
    cout << "========================================\n";
    cout << "       STUDENT GRADE ANALYZER\n";
    cout << "========================================\n\n";

    cout << left << setw(15) << "Name"
         << setw(10) << "Marks"
         << "Grade\n";

    cout << "----------------------------------------\n";

    for (const Student& s : students)
    {
        cout << left << setw(15) << s.name
             << setw(10) << s.mark
             << s.grade << '\n';
    }

    cout << "----------------------------------------\n";

    if (it != students.end())
    {
        cout << "First student scoring above 85: "
             << it->name << " (" << it->mark << ")\n";
    }
    else
    {
        cout << "No student scored above 85.\n";
    }

    cout << "Total Marks: " << total << '\n';
    cout << fixed << setprecision(2);
    cout << "Average Marks: " << average << '\n';

    cout << "\nAnalysis completed successfully.\n";

    return 0;
}