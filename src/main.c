#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "integrate.h"

// -----------------------------------------------------------------------------
// FUNCTION PROTOTYPES
// -----------------------------------------------------------------------------

bool isNumber(char *numberString);

bool processIntegralLinear(int numberArguments, char **arguments, double *integralResult);

bool processIntegralQuadratic(int numberArguments, char **arguments, double *integralResult);

bool processIntegralSin(int numberArguments, char **arguments, double *integralResult);

bool processIntegralCos(int numberArguments, char **arguments, double *integralResult);

// -----------------------------------------------------------------------------
// GLOBAL VARIABLES
// -----------------------------------------------------------------------------

char *functionName[FUNCTION_NUMBER] = {"linear", "quadratic", "sin", "cos"};
bool (*processIntegral[FUNCTION_NUMBER])(int, char**, double*) = {&processIntegralLinear, &processIntegralQuadratic, &processIntegralSin, &processIntegralCos};

// -----------------------------------------------------------------------------
// MAIN CODE
// -----------------------------------------------------------------------------

int main(int argc, char **argv) {

	bool correctFunctionName = false; 
	bool correctIntegralArguments = false;	
	
	if(argc < 2) {
		puts("integrate: error: Not enough arguments!");
		return 1;
	}
	
	for(int i = 0; i < argc; i++) {
		if(strcmp(argv[i], "--help") == 0) {
			puts("integrate: usage: integral [function] [args] [a] [b].");
			puts("  functions:\t'linear'. \targs: 'a' and 'b', as in 'a*x + b'.");
			puts("\t\t'quadratic'. \targs: 'a', 'b' and 'c', as in 'a*x^2 + b*x + c'.");
			puts("\t\t'sin'. \targs: 'a', 'w' and 'phi', as in 'a*sin(wx + phi)'.");
			puts("\t\t'cos'. \targs: 'a', 'w' and 'phi', as in 'a*cos(wx + phi)'.");
			puts("  a and b of the integral stands for the limits: 'integral of f(x), from a to b'.");
			return 0;
		}
		else if(strcmp(argv[i], "--version") == 0) {
			puts("integrate 1.0.0\nCopyright (C) 2022 Pedro Botelho");
			return 0;
		}
	}
	
	double integralResult = 0;
	for(int i = 0; i < FUNCTION_NUMBER; i++) {
		if(strcmp(argv[1], functionName[i]) == 0) {
			correctFunctionName = true;
			correctIntegralArguments = processIntegral[i](argc - 2, argv + 2, &integralResult);
			break;
		}
	}
	
	if(!correctFunctionName) {
		puts("integrate: error: Invalid function name!");
		return 1;
	}
	if(!correctIntegralArguments) {
		puts("integrate: error: Invalid integral arguments (function arguments and/or limits)!");
		return 1;
	}
	
	printf("integrate: %s: %f\n", argv[1], integralResult);
	
	return 0;
}

// -----------------------------------------------------------------------------
// FUNCTION IMPLEMENTATIONS
// -----------------------------------------------------------------------------

bool isNumber(char *numberString) {
	bool floatingPoint = false;
	
     for(int i = 0; numberString[i] != '\0'; i++) {
          if(numberString[i] == '-' || numberString[i] == '+') {
               if(i == 0) {
                    continue;
               }
               else {
                    return false;
               }
          }
		else if((numberString[i] < '0' || numberString[i] > '9') || (numberString[i] == ',')) {
               if(numberString[i] == '.' && !floatingPoint) {
			     floatingPoint = true;
                    continue;
               }
			return false;
		}
	}
	return true;
}

bool processIntegralLinear(int numberArguments, char **arguments, double *integralResult) {
	if(numberArguments != 4) {
		return false;
	}
	
	for(int i = 0; i < numberArguments; i++) {
		if(!isNumber(arguments[i])) {
			return false;
		}
	}
	
	Linear linearFunction = {};
	
	linearFunction.a = atof(arguments[0]);
	linearFunction.b = atof(arguments[1]);
	double a = atof(arguments[2]);
	double b = atof(arguments[3]);

     if(a > b) {
          return false;
     }
	
     double area = integrateLinear(&linearFunction, a, b);
	*integralResult = (fabs(area) >= 0.000001) ? area : 0;
	return true; 
}

bool processIntegralQuadratic(int numberArguments, char **arguments, double *integralResult) {
	if(numberArguments != 5) {
		return false;
	}
	
	for(int i = 0; i < numberArguments; i++) {
		if(!isNumber(arguments[i])) {
			return false;
		}
	}
	
	Quadratic quadraticFunction = {};
	
	quadraticFunction.a = atof(arguments[0]);
	quadraticFunction.b = atof(arguments[1]);
	quadraticFunction.c = atof(arguments[2]);
	double a = atof(arguments[3]);
	double b = atof(arguments[4]);

     if(a > b) {
          return false;
     }
	
	double area = integrateQuadratic(&quadraticFunction, a, b);
	*integralResult = (fabs(area) >= 0.000001) ? area : 0;
	return true; 
}

bool processIntegralSin(int numberArguments, char **arguments, double *integralResult) {
	if(numberArguments != 5) {
		return false;
	}
	
	for(int i = 0; i < numberArguments; i++) {
		if(!isNumber(arguments[i])) {
			return false;
		}
	}
	
	Sinusoid sinFunction = {};
	
	sinFunction.a = atof(arguments[0]);
	sinFunction.w = atof(arguments[1]);
	sinFunction.phi = atof(arguments[2]);
	double a = atof(arguments[3]);
	double b = atof(arguments[4]);

     if(a > b) {
          return false;
     }
	
	double area = integrateSin(&sinFunction, a, b);
	*integralResult = (fabs(area) >= 0.000001) ? area : 0;
	return true; 
}

bool processIntegralCos(int numberArguments, char **arguments, double *integralResult) {
	if(numberArguments != 5) {
		return false;
	}
	
	for(int i = 0; i < numberArguments; i++) {
		if(!isNumber(arguments[i])) {
			return false;
		}
	}
	
	Sinusoid cosFunction = {};
	
	cosFunction.a = atof(arguments[0]);
	cosFunction.w = atof(arguments[1]);
	cosFunction.phi = atof(arguments[2]);
	double a = atof(arguments[3]);
	double b = atof(arguments[4]);

     printf("f(x) = %.2f*cos(%.2fx + %.2f), from %.2f to %.2f.\n", cosFunction.a, cosFunction.w, cosFunction.phi, a, b);

     if(a > b) {
          return false;
     }
	
	double area = integrateCos(&cosFunction, a, b);
	*integralResult = (fabs(area) >= 0.000001) ? area : 0;
	return true;
}