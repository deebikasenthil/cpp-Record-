#include <iostream>
#include <cassert>
using namespace std;

class Matrix
{
private:
    static const int SIZE = 2;
    int data[SIZE][SIZE];

public:
    // Default constructor
    Matrix()
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                data[i][j] = 0;
            }
        }
    }

    // Parameterized constructor
    Matrix(int a, int b, int c, int d)
    {
        data[0][0] = a;
        data[0][1] = b;
        data[1][0] = c;
        data[1][1] = d;
    }

    // Overload + operator
    Matrix operator+(const Matrix &m) const
    {
        Matrix result;

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                result.data[i][j] = data[i][j] + m.data[i][j];
            }
        }

        return result;
    }

    // Overload * operator
    Matrix operator*(const Matrix &m) const
    {
        Matrix result;

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < SIZE; k++)
                {
                    result.data[i][j] += data[i][k] * m.data[k][j];
                }
            }
        }

        return result;
    }

    // Overload [] operator
    int* operator[](int index)
    {
        assert(index >= 0 && index < SIZE);
        return data[index];
    }

    // Read-only element access
    const int* operator[](int index) const
    {
        assert(index >= 0 && index < SIZE);
        return data[index];
    }

    // Display matrix
    friend ostream& operator<<(ostream &out, const Matrix &m)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                out << m.data[i][j] << "\t";
            }
            out << '\n';
        }

        return out;
    }
};

int main()
{
    Matrix A(1, 2, 3, 4);
    Matrix B(5, 6, 7, 8);

    // Perform operations
    Matrix sum = A + B;
    Matrix product = A * B;

    // Verify results
    assert(sum[0][0] == 6);
    assert(sum[0][1] == 8);
    assert(sum[1][0] == 10);
    assert(sum[1][1] == 12);

    assert(product[0][0] == 19);
    assert(product[0][1] == 22);
    assert(product[1][0] == 43);
    assert(product[1][1] == 50);

    // Display results
    cout << "===== MATRIX OPERATIONS =====\n\n";

    cout << "Matrix A:\n" << A << '\n';
    cout << "Matrix B:\n" << B << '\n';

    cout << "A + B (Addition):\n" << sum << '\n';
    cout << "A * B (Multiplication):\n" << product << '\n';

    cout << "All unit tests passed successfully!\n";

    return 0;
}