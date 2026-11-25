// Правка из ветки master
﻿// Правка из ветки ДополнительнаяВетвь
#include <iostream>
#include <cmath> // Подключили стандартную математическую библиотеку С++

#include <vector> 

using namespace std; // Теперь можно не записывать префикс std

const double eps = 1e-6; // Погрешность

double func1(double x)
{
	return (1.0 / 4.0) * pow(x, 3); // Гарантировали получение вещественного значения, применили функцию из cmath
}

double func2(double x)
{
	return 2 * x;
}

// Функция FindIntersections
vector<double> FindIntersections(double f1(double), double f2(double), double left, double right, double step = 0.01)
{
	vector<double> result; // !!!
	double a = left;
	double b = left + step;
	while (b <= right)
	{
		if ((f1(a) - f2(a)) * (f1(b) - f2(b)) < 0)
		{
			while (b - a > eps) // !!!
			{
				double c = (a + b) / 2;
				if ((f1(a) - f2(a)) * (f1(c) - f2(c)) < 0)
					b = c;
				else
					a = c;
			}
			result.push_back((a + b) / 2); // !!! 
		}
		a = b;
		b += step;
	}
	return result;
}

// Перегруженная FindIntersections
vector<double> FindIntersections(double f1(double), double left, double right, double step = 0.01) // !!!
{
	vector<double> result;
	double a = left;
	double b = left + step;
	while (b <= right)
	{
		if (f1(a) * f1(b) < 0)
		{
			while (b - a > eps)
			{
				double c = (a + b) / 2;
				if (f1(a) * f1(c) < 0)
					b = c;
				else
					a = c;
			}
			result.push_back((a + b) / 2);
		}
		a = b;
		b += step;
	}
	return result;
}

// Численное интегрирование методом трапеций
double Integrate(double f1(double), double left, double right)
{
	double a = left, b = right; // !!!
	int n = 10000;
	double h = (b - a) / n;
	double res = 0.5 * (f1(a) + f1(b)); 
	for (int i = 1; i < n; ++i) // Смотри полную формулу трапеций при делении промежутка на одинаковые отрезки
		res += f1(a + i * h); 
	res *= h;
	return res;
}

/* Проверка чисел, близких к нулю
* (применяется в численных методах).
* Необходима для избежания ошибки округления вещественных чисел компьютером.
*/
double CheckResult(double x)
{
	if (fabs(x) < eps) // Модуль обязателен
		return 0;
	else
		return x;
}

// Разность функций
double Difference(double x) // !!!
{
	return func1(x) - func2(x); 
}

int main() 
{
	double left = -5, right = 5;

	vector<double> Intersections = FindIntersections(func1, func2, left, right);
	double x_left = Intersections[0];
	double x_middle = Intersections[1];
	double x_right = Intersections[2];

	// Вычисляем приближённое значения площади
	double Area = 2 * fabs(Integrate(Difference, 0.0, x_right)); // ТОЛЬКО АРГУМЕНТЫ!
	cout << "Area is: " << Area << endl;

	// Вывод точек пересечения двух функций func1 и func2
	cout << "Intersection of two functions: " << endl;
	cout << "y = " << CheckResult(func1(x_left)) << ", x = " << CheckResult(x_left) << endl;
	cout << "y = " << CheckResult(func1(x_middle)) << ", x = " << CheckResult(x_middle) << endl;
	cout << "y = " << CheckResult(func1(x_right)) << ", x = " << CheckResult(x_right) << endl;

	// Вывод точек пересечения функции func1 с осью абсцисс
	cout << "Intersection with the x-axis of the func1: ";
	vector<double> ResultXIntersections = FindIntersections(func1, left, right); 
	for (double i : ResultXIntersections) cout << CheckResult(i) << endl; // Цикл по дипазону, исп-ся, чтобы не работать с индексами

	// Вывод точек пересечения функции func2 с осью абсцисс
	cout << "Intersection with the x-axis of the func2: ";
	ResultXIntersections = FindIntersections(func2, left, right);
	for (double i : ResultXIntersections) cout << CheckResult(i); 

	return 0;
}
// Ещё одна правка
// И ещё одна очередная правка, чтобы продемонстрировать коммиты