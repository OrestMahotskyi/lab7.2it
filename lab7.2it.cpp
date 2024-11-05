#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Функція для створення матриці з випадковими значеннями
void Create(int** a, const int rows, const int cols, const int Low, const int High) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            a[i][j] = Low + rand() % (High - Low + 1);
        }
    }
}

// Функція для виведення матриці
void Print(int** a, const int rows, const int cols) {
    cout << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// Функція для знаходження мінімального елемента у парному стовпці
int FindMinInColumn(int** a, int rows, int col) {
    int minVal = a[0][col];
    for (int i = 1; i < rows; i++) {
        if (a[i][col] < minVal) {
            minVal = a[i][col];
        }
    }
    return minVal;
}

// Функція для знаходження максимального елемента у непарному стовпці
int FindMaxInColumn(int** a, int rows, int col) {
    int maxVal = a[0][col];
    for (int i = 1; i < rows; i++) {
        if (a[i][col] > maxVal) {
            maxVal = a[i][col];
        }
    }
    return maxVal;
}

// Функція для обміну мінімального елемента парного стовпця з максимальним елементом попереднього непарного стовпця
void SwapMinWithMax(int** a, int rows, int cols) {
    for (int j = 1; j < cols; j += 2) { // Починаємо з другого стовпця (індекс 1)
        int minVal = FindMinInColumn(a, rows, j); // Мінімальний у парному стовпці
        int maxVal = FindMaxInColumn(a, rows, j - 1); // Максимальний у непарному стовпці

        // Обмін значеннями
        for (int i = 0; i < rows; i++) {
            if (a[i][j] == minVal) {
                for (int k = 0; k < rows; k++) {
                    if (a[k][j - 1] == maxVal) {
                        swap(a[i][j], a[k][j - 1]);
                        return; // Виходимо після обміну
                    }
                }
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int Low = 7; // Мінімальне значення
    int High = 65; // Максимальне значення
    int rows, cols;

    cout << "Введіть кількість рядків: ";
    cin >> rows;
    cout << "Введіть кількість стовпців: ";
    cin >> cols;

    // Перевірка на коректність введення
    if (rows <= 0 || cols <= 0) {
        cout << "Кількість рядків і стовпців повинна бути більше нуля." << endl;
        return 1; // Вихід з програми при неправильному введенні
    }

    // Динамічне виділення пам'яті для матриці
    int** a = new int*[rows];
    for (int i = 0; i < rows; i++) {
        a[i] = new int[cols];
    }

    Create(a, rows, cols, Low, High); // Створення матриці
    cout << "Початкова матриця:" << endl;
    Print(a, rows, cols); // Виведення початкової матриці

    SwapMinWithMax(a, rows, cols); // Обмін елементів

    cout << "Модифікована матриця:" << endl;
    Print(a, rows, cols); // Виведення модифікованої матриці

    // Вивільнення пам'яті
    for (int i = 0; i < rows; i++) {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}