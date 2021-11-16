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
	double operand2, operand1;
	char working_operator;
	double result;


public:

	string getMsg();
	double solve_exp();
	int precedence(char);
	double eval(double, double, char);
	void perform_operation();
	void handle_negation();
	void check_digit_amt();


};
