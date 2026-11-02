#include <iostream>
#include <stack>
#include <queue>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

const int N = 3000;

// Custom Stack
template <typename T>
class MyStack
{
private:
    T data[N];
    int topIndex;

public:
    MyStack() : topIndex(-1) {}

    bool push(const T& value)
    {
        if (topIndex >= N - 1)
            return false;

        data[++topIndex] = value;
        return true;
    }

    bool pop()
    {
        if (topIndex < 0)
            return false;

        topIndex--;
        return true;
    }

    bool empty() const
    {
        return topIndex == -1;
    }

    int size() const
    {
        return topIndex + 1;
    }
};

// Custom Circular Queue
template <typename T>
class MyQueue
{
private:
    T data[N];
    int frontIndex;
    int rearIndex;
    int count;

public:
    MyQueue() : frontIndex(0), rearIndex(0), count(0) {}

    bool enqueue(const T& value)
    {
        if (count == N)
            return false;

        data[rearIndex] = value;
        rearIndex = (rearIndex + 1) % N;
        count++;
        return true;
    }

    bool dequeue()
    {
        if (count == 0)
            return false;

        frontIndex = (frontIndex + 1) % N;
        count--;
        return true;
    }

    bool empty() const
    {
        return count == 0;
    }

    int size() const
    {
        return count;
    }
};

long long benchmarkCustomStack()
{
    auto start = high_resolution_clock::now();

    MyStack<int> s;

    for (int i = 0; i < N; i++)
        s.push(i);

    for (int i = 0; i < N; i++)
        s.pop();

    auto end = high_resolution_clock::now();

    return duration_cast<microseconds>(end - start).count();
}

long long benchmarkSTLStack()
{
    auto start = high_resolution_clock::now();

    stack<int> s;

    for (int i = 0; i < N; i++)
        s.push(i);

    for (int i = 0; i < N; i++)
        s.pop();

    auto end = high_resolution_clock::now();

    return duration_cast<microseconds>(end - start).count();
}

long long benchmarkCustomQueue()
{
    auto start = high_resolution_clock::now();

    MyQueue<int> q;

    for (int i = 0; i < N; i++)
        q.enqueue(i);

    for (int i = 0; i < N; i++)
        q.dequeue();

    auto end = high_resolution_clock::now();

    return duration_cast<microseconds>(end - start).count();
}

long long benchmarkSTLQueue()
{
    auto start = high_resolution_clock::now();

    queue<int> q;

    for (int i = 0; i < N; i++)
        q.push(i);

    for (int i = 0; i < N; i++)
        q.pop();

    auto end = high_resolution_clock::now();

    return duration_cast<microseconds>(end - start).count();
}

int main()
{
    long long customStackTime = benchmarkCustomStack();
    long long stlStackTime = benchmarkSTLStack();
    long long customQueueTime = benchmarkCustomQueue();
    long long stlQueueTime = benchmarkSTLQueue();

    cout << "========================================\n";
    cout << "   STACK AND QUEUE PERFORMANCE TEST\n";
    cout << "========================================\n";
    cout << "Number of operations: " << N << "\n\n";

    cout << left << setw(25) << "Implementation"
         << right << setw(15) << "Time (us)" << '\n';

    cout << "----------------------------------------\n";

    cout << left << setw(25) << "Custom Stack"
         << right << setw(15) << customStackTime << '\n';

    cout << left << setw(25) << "STL Stack"
         << right << setw(15) << stlStackTime << '\n';

    cout << left << setw(25) << "Custom Circular Queue"
         << right << setw(15) << customQueueTime << '\n';

    cout << left << setw(25) << "STL Queue"
         << right << setw(15) << stlQueueTime << '\n';

    cout << "========================================\n";
    cout << "\nAll benchmark operations completed.\n";

    return 0;
}