#ifndef INTEGRATE_H
#define INTEGRATE_H

#define FUNCTION_NUMBER 4

typedef struct {
	double a;
	double b;
	double c;
} Quadratic;

typedef struct {
	double a;
	double b;
} Linear;

typedef struct {
	double a;
	double w;
	double phi;
} Sinusoid;

double integrateLinear(Linear *function, double a, double b);

double integrateQuadratic(Quadratic *function, double a, double b);

double integrateSin(Sinusoid *function, double a, double b);

double integrateCos(Sinusoid *function, double a, double b);

#endif