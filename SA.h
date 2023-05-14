#pragma once
#ifndef SA_H
#define SA_H
#endif // !SA_H

class CSimulate
{
public:
	CSimulate() {}
	CSimulate(double &Tmax, double &Tmin, double &Tk, int &kMaxSteps, double &xLower, double &xUpper, double &yLower, double &yUpper) 
	{
		this->Tmax = Tmax;
		this->Tmin = Tmin;
		this->Tk = Tk;
		this->kMaxSteps = kMaxSteps;
		this->xLower = xLower;
		this->xUpper = xUpper;
		this->yLower = yLower;
		this->yUpper = yUpper;
	}
	~CSimulate() {}
	/****************************
	* func: define a curve function
	* Params: x,y: variables
	* output: value of the function
	*****************************/
	double func(double &x, double &y);
	double realDist(double lower, double upper);
	int getSgn(double &num);
	double getBoundary(double &num, double &lower, double &upper);
	double SA(double &Tmax, double &Tmin, double &Tk, int &kMaxSteps, double &xLower, double &xUpper, double &yLower, double &yUpper);

private:
	double Tmax,Tmin,Tk;
	int kMaxSteps;
	double xLower,xUpper,yLower,yUpper;
};

