#include <iostream>

//Task 1
float** tableOfDifferences1(int n, float(*x), float(*y))
{
    float** array = new float* [n];
    for (int i = 0; i < n; i++)
    {
        array[i] = new float[n + 1];
        for (int j = 0; j < n + 1; j++)
        {
            array[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++)
    {
        array[i][0] = x[i];
        array[i][1] = y[i];
    }
    for (int i = 2; i < n + 1; i++)
    {
        for (int j = 0; j <= n - i; j++)
        {
            array[j][i] = (array[j + 1][i - 1] - array[j][i - 1]) / (x[j + i - 1] - x[j]);
        }
    }
    return array;
}

float multiplication(float xt, float(*x), int n)
{
    float temp = 1;
    for (int i = 0; i < n; i++)
    {
        temp *= (xt - x[i]);
    }
    return temp;
}

void task1(float xt, float(*x), float(*y), int n)
{
    std::cout << "xt = " << xt;
    std::cout << "\nx: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << x[i] << ' ';
    }
    std::cout << "\ny: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << y[i] << ' ';
    }
    std::cout << "\n\n";
    float** table = tableOfDifferences1(n, x, y);
    float result = 0;
    for (int i = 0; i < n; i++)
    {
        result += table[0][i + 1] * multiplication(xt, x, i);
    }
    std::cout << result << '\n';
}

//Task2
float** tableOfDifferences2(int n, float(*x), float(*y), int accuracy)
{
    float** array = new float* [n * 2 - 1];
    for (int i = 0; i < n * 2 - 1; i++)
    {
        array[i] = new float[2 + accuracy];
        for (int j = 0; j < 2 + accuracy; j++)
        {
            array[i][j] = 0;
        }
    }
    for (int i = 0; i < n - 1; i ++)
    {
        array[i * 2][0] = x[i];
        array[i * 2][1] = y[i];
    }
    array[(n - 1) * 2][0] = x[n - 1];
    array[(n - 1) * 2][1] = y[n - 1];
    for (int i = 2; i < 2 + accuracy; i++)
    {
        for (int j = i - 1; j <= (n * 2) - i; j += 2)
        {
            array[j][i] = (array[j + 1][i - 1] - array[j - 1][i - 1]);
        }
    }
    return array;
}

float downNewton(float xt, float** table, int n, float h, int accuracy)
{
    int i = 0;
    while ((xt - table[i][0]) > h) i += 2;
    float q = (xt - table[i][0])/h;
    float qTemp = q;
    float factorial = 1;
    float temp = table[i][1];
    for (int j = 2; j < 2 + accuracy; j++)
    {
        i += 1;
        temp += table[i][j] * qTemp / factorial;
        factorial *= j;
        qTemp *= (q - j) + 1;
    }
    return temp;
}

float upNewton(float xt, float **table, int n, float h, int accuracy)
{
    int i = n * 2 - 2;
    while ((table[i][0] - xt) > h) i -= 2;
    float q = (xt - table[i][0]) / h;
    float qTemp = q;
    float factorial = 1;
    float temp = table[i][1];
    for (int j = 2; j < 2 + accuracy; j++)
    {
        i -= 1;
        temp += table[i][j] * qTemp / factorial;
        std::cout << table[i][j] << ' ' << qTemp << ' ' << factorial << ' ' << table[i][j] * qTemp / factorial << '\n';
        factorial *= j;
        qTemp *= q + j - 1;
    }
    return temp;
}

void task2(float xt, float(*x), float(*y), int n, int accuracy)
{
    std::cout << "\nxt = " << xt;
    std::cout << "\nx: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << x[i] << ' ';
    }
    std::cout << "\ny: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << y[i] << ' ';
    }
    std::cout << "\n";

    float** table = tableOfDifferences2(n, x, y, accuracy);

    float result;

    if (x[n / 2] > xt)
    {
        result = downNewton(xt, table, n, x[1] - x[0], accuracy);
    }
    else
    {
        result = upNewton(xt, table, n, x[1] - x[0], accuracy);
    }
    std::cout << "Answer is " << result << '\n';
}

#include <iostream>

int main()
{
    std::cout << "This is the third lab of project design.\n\n";
    std::cout << "First task is to execute the Newton polinom by the net of not equidistant nodes.\n";
    /*std::cout << "Example:\n";
    float xt01 = 0.552;
    float x01[6] = { 0.35, 0.41, 0.47, 0.51, 0.56, 0.64 };
    float y01[6] = { 2.73951, 2.30080, 1.96464, 1.78776, 1.59502, 1.34310 };
    task1(xt01, x01, y01, 6);*/
    float xt = 0.154;
    float x1[8] = { 0.05, 0.19, 0.21, 0.27, 0.32, 0.34, 0.39, 0.45 };
    float y1[8] = { 4.4817, 4.9530, 5.4739, 6.0496, 6.6859, 7.3891, 8.1662, 9.0250 };
    task1(xt, x1, y1, 8);
    //Task two
    std::cout << "\nSecond task is to execute y=f(x) by Newton formula for interpolation up and down.\n";

    /*std::cout << "Example:\n";
    float xt02 = 0.4675;
    float x02[12] = { 0.45, 0.46, 0.47, 0.48, 0.49, 0.50, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56 };
    float y02[12] = { 20.1946, 19.6133, 18.9425, 18.1746, 17.3010, 16.3123, 15.1984, 13.9484, 12.5508, 10.9937, 9.2647, 7.3510 };
    task2(xt02, x02, y02, 12, 4);
    xt02 = 0.5410;
    task2(xt02, x02, y02, 12, 4);*/

    xt = 4.413;
    float x2[10] = { 4.35, 4.60, 4.85, 5.10, 5.35, 5.60, 5.85, 6.10, 6.35, 6.60 };
    float y2[10] = { 16.3597, 17.7334, 18.7686, 20.0334, 22.2846, 23.5973, 25.0811, 26.5278, 28.3944, 29.9902 };
    task2(xt, x2, y2, 8, 4);
}
