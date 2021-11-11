/*
Ryan Brandt
CSC 331H
Professor Salvati
Infix Stack Evaluation Project
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;
#pragma once

class IfStack
{

private:
	stack<char> operators;
	stack<double> working_exp;
	double result;
	




public:

	string getMsg();
	double solve_exp();
	int precedence(char);
	double eval(double, double, char);


};
