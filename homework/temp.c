#include <stdio.h>
#include <math.h>

// Подынтегральная функция
double InFunction(double x) {
    return 1 / ((25 * x * x + 1) * sqrt(3 * x - x * x));
}

// Функция для точного значения интеграла

// Функция для вычисления интеграла методом средних прямоугольников
double CalcIntegral(double a, double b, int n) {
    double result = 0.0;
    double h = (b - a) / n; // Длина шага

    for (int i = 0; i < n; i++) {
        result += InFunction(a + (i + 0.5) * h); // Высота прямоугольника в средней точке
    }
    
    result *= h; // Умножаем на ширину прямоугольника
    return result;
}

int main() {
    double a = 0.0; // Нижний предел интегрирования
    double b = 3.0; // Верхний предел интегрирования
    int n = 32;     // Количество подынтервалов

    double approx = CalcIntegral(a, b, n); // Приближенное значение интеграла
    double exact = 0.5916870519;     // Точное значение интеграла
    double error = fabs(approx - exact);    // Погрешность


    // printf("Точное значение: %.6f\n", exact);
    printf("Погрешность: %.10f\n", error);

    return 0;
}
