#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>
#include<locale.h>
#include<limits.h>

typedef double(*Tfun)(double);
double integral(double, double, int, double, Tfun, double);
double fun1(double x);
double fun2(double x);
double fun3(double x);
double fun4(double x);

int main()
{
	int i = 0, n = 10;
	double x, y,
		s1, s2, s3, s4, s5;
	double eps = 0.000001,
		   s = 0;
	setlocale(LC_ALL, "Russian");
	std::cout << "\nВведите координаты точки: x, y ";
	std::cin >> x >> y;
	if (((x + 1) * (x + 1) + y * y > 1) && (x * x + y * y > 1) && ((x + 1) * (x
		+ 1) + (y - 1) * (y - 1) < 1))
	{
		std::cout << "Точка в области M1. " << std::endl; i = 1;
	}
	else if ((x * x + y * y < 1) && (x > 0) && (x * x + (y + 1) * (y + 1) > 1)
		&& (x * x + (y - 1) * (y - 1) > 1) && ((x - 1) * (x - 1) + (y - 1) * (y - 1) > 1))
	{
		std::cout << "Точка в области М2. " << std::endl; i = 2;
	}
	else if ((x * x + y * y < 1) && ((x + 1) * (x + 1) + y * y < 1) && (x * x +
		(y + 1) * (y + 1) < 1) && ((x + 1) * (x + 1) + (y + 1) * (y + 1) < 1))
	{
		std::cout << "Точка в области М3. " << std::endl; i = 3;
	}
	else if (((x + 1) * (x + 1) + (y + 1) * (y + 1) < 1) && ((x + 1) * (x + 1)
		+ y * y > 1) && (x * x + (y + 1) * (y + 1) > 1))
	{
		std::cout << "Точка в области М4. " << std::endl; i = 4;
	}
	else if ((x * x + (y + 1) * (y + 1) < 1) && ((x + 1) * (x + 1) + (y + 1) *
		(y + 1) > 1) && (x * x + y * y > 1) && ((x - 1) * (x - 1) + y * y > 1) && (x * x + y * y > 1))
	{
		std::cout << "Точка в области М5. " << std::endl; i = 5;
	}
	else
	{
		std::cout << "Точка вне выделенных областей";
	}
	std::cout.precision(4);
	switch (i)
	{
	case 1: std::cout << "Formula: S1 = " << (s1 = 1 + M_PI / 4) << std::endl;
		std::cout << "Integral: S1 = " << (s1 = integral(-2, -1, n, eps, fun3, s) + integral(-1, 0, n, eps, fun1, s)) << std::endl;
		break;
	case 2: std::cout << "Formula: S2 = " << (s2 = 1 - M_PI / 4) << std::endl;
		std::cout << "Integral: S2 = " << (s2 = integral(0, 1, n, eps, fun3, s) - integral(0, 1, n, eps, fun2, s)) << std::endl;
		break;
	case 3: std::cout << "Formula: S3 = " << (s3 = M_PI / 3 + 1 - sqrt(3)) << std::endl;
		std::cout << "Integral: S3 = " << (s3 = integral(0, 1, n, eps, fun3, s) - (integral(0.5, 1, n, eps, fun4, s) - integral(0.5, 1, n, eps, fun2, s)) * 4) << std::endl;
		break;
	case 4: std::cout << "Formula: S4 = " << (s4 = M_PI / 12 + sqrt(3) / 2) << std::endl;
		std::cout << "Integral: S4 = " << (s4 = integral(0, 1, n, eps, fun2, s) + (integral(0.5, 1, n, eps, fun4, s) - integral(0.5, 1, n, eps, fun2, s)) * 2) << std::endl;
		break;
	case 5: std::cout << "Formula: S5 = " << (s5 = 1) << std::endl;
		std::cout << "Integral: S5 = " << (s5 = integral(0, 1, n, eps, fun3, s)) << std::endl;
		break;
	}
	std::cout << "\n Повторить-1, Выход-2: ";
	std::cin >> i;
	if (i == 1) main();
	return 0;
}

// нахождение определенного интеграла методом прямоугольных трапеций
double integral(double a, double b, int n, double eps, Tfun fun, double s1)
{
	double x1, x2, h, s = 0;
	h = (b - a) / n;
	for (int i = 0; i < n; i++)
	{
		x1 = a + i * h;
		x2 = a + i * h + h;
		if (x2 < b)
			s += (fun(x1) + fun(x2)) / 2;
	}
	s *= h;
	if (fabs(s - s1) > eps)
		s = integral(a, b, 2 * n, eps, fun, s);
	return s;
}

// левая окружность
double fun1(double x)
{
	return sqrt(- x * x - 2 * x);
}

// центральная окружность
double fun2(double x)
{
	return sqrt(1 - x * x);
}

// квадрат
double fun3(double x)
{
	return 1;
}

// правая окружность
double fun4(double x)
{
	return sqrt(-x * x + 2 * x);
}