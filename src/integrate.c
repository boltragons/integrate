#include "integrate.h"

#include <math.h>
#include <stdio.h>

double integrateLinear(Linear *function, double a, double b) {
	double area = 0;
	area += function->a*(pow(b, 2)/2 - pow(a, 2)/2);
	area += function->b*(b - a);
	return area;
}

double integrateQuadratic(Quadratic *function, double a, double b) {
	double area = 0;
	area += function->a*(pow(b, 3)/3 - pow(a, 3)/3);
	area += function->b*(pow(b, 2)/2 - pow(a, 2)/2);
	area += function->c*(b - a);
	return area;
}

double integrateSin(Sinusoid *function, double a, double b) {
	double area = 0;
	area += function->a*(cos(function->w*a + function->phi) - cos(function->w*b + function->phi));
	return area;
}

double integrateCos(Sinusoid *function, double a, double b) {
	double area = 0;
	area += function->a*(sin(function->w*b + function->phi) - sin(function->w*a + function->phi));
	return area;
}