/*
Ryan Brandt
CSC 331H
Professor Salvati
Infix Stack Evaluation Project
*/

#include <iostream>
#include "IfStack.h"
using namespace std;

int main()
{
	IfStack infix;

	double answer = 0;

	while (answer != 1) 
	{

		answer = infix.solve_exp();

		cout << answer << endl;
	}

	return 0;
}