/*
 已知一个函数
 author: Yuwei Xie
 date: 2/26/2023
*/
#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include "SA.h"

double CSimulate::func(double &x, double &y)
{
	return sin(x) + cos(y) + 0.2 * (x + y);
}

double CSimulate::realDist(double lower, double upper)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine gen(seed);
	std::uniform_real_distribution<double> dist_x(lower, upper);
	return dist_x(gen);
}

int CSimulate::getSgn(double &num)
{
	if (num < 0) return 1;
	if (num > 0) return -1;
	return 0;
}

double CSimulate::getBoundary(double &num, double &lower, double &upper)
{
	if (num < lower) return lower;
	if (num > upper) return upper;
	return num;
}

double CSimulate::SA(double &Tmax, double &Tmin, double &Tk, int &kMaxSteps, double &xLower, double &xUpper, double &yLower, double &yUpper)
{
	srand(time(nullptr));
	double currT = Tmax;
	double x_best = 1, y_best = 1;
	double energy_best = func(x_best, y_best);
	double x_current = 0, y_current = 0, x_new = 0, y_new = 0, energy_current = 0, energy_new = 0;
	while (currT > Tmin)
	{
		x_current = x_best, y_current = y_best;
		energy_current = energy_best;
		for (int i = 0; i < kMaxSteps; ++i)
		{
			double u_x = realDist(-1.0, 1.0), u_y = realDist(-1.0, 1.0);
			double x_new = x_current + 2 * (xUpper - xLower) * getSgn(u_x) * currT * (pow(1 + (1.0 / currT), fabs(u_x)) - 1.0);
			double y_new = y_current + 2 * (yUpper - yLower) * getSgn(u_y) * currT * (pow(1 + (1.0 / currT), fabs(u_y)) - 1.0);

			x_new = getBoundary(x_new, xLower, xUpper);
			y_new = getBoundary(y_new, yLower, yUpper);
			//更新energy
			energy_new = func(x_new, y_new);
			//Metropolis
			double delta_energy = energy_new - energy_current;
			double acc_propability = exp(-delta_energy / currT), pro = realDist(0, 1);
			if (delta_energy < 0 || acc_propability > pro)
			{
				x_current = x_new, y_current = y_new;
				energy_current = energy_new;
				if (energy_new < energy_best)
				{
					x_best = x_new, y_best = y_new;
					energy_best = energy_new;
				}
			}
			std::cout << energy_new << std::endl;

		}
		currT *= Tk;
	}
	return energy_best;
}

int main()
{
	srand(time(nullptr));
	CSimulate test;
	double Tmax = 100;
	double Tmin = 1e-09;
	double Tk = 0.7;
	int kMaxSteps = 10;
	double xLower = -4;
	double xUpper = 6;
	double yLower = -6;
	double yUpper = 6;
	double min_energy = test.SA(Tmax, Tmin, Tk, kMaxSteps, xLower, xUpper, yLower, yUpper);
	std::cout << "Minimum energy found: " << min_energy << std::endl;
	return 0;
}

