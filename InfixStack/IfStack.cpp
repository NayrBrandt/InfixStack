/*
Ryan Brandt
CSC 331H
Professor Salvati
Infix Stack Evaluation Project
*/

#include <iostream>
#include <string>
#include "IfStack.h"

using namespace std;

string IfStack::getMsg()
{
	string express;
	cout << "Type your infix operators: \n";

	cin.ignore();
	getline(cin, express);

	return express;	
}	

double IfStack::solve_exp()
{
    string user_exp = getMsg();

    double val1, val2;
    char op;

    for (int i = 0; i < user_exp.length(); i++) 
    {

        if (user_exp[i] == ' ')
            continue;

        else if (user_exp[i] == '(')
            operators.push(user_exp[i]);

        else if (isdigit(user_exp[i]))
            working_exp.push(user_exp[i]);

        





             
        else if (user_exp[i] == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                val2 = working_exp.top();
                working_exp.pop();

                val1 = working_exp.top();
                working_exp.pop();

                op = operators.top();
                operators.pop();

                working_exp.push(eval(val1, val2, op));
            }

            if (!operators.empty())
                operators.pop();
        }
            
        else
        {
            while ((!operators.empty()) && precedence(operators.top())
                >= precedence(user_exp[i])) {
                val2 = working_exp.top();
                working_exp.pop();

                val1 = working_exp.top();
                working_exp.pop();

                op = operators.top();
                operators.pop();

                working_exp.push(eval(val1, val2, op));
            }

            operators.push(user_exp[i]);
        }
    }

    while (!operators.empty()) {
        val2 = working_exp.top();
        working_exp.pop();

        val1 = working_exp.top();
        working_exp.pop();

        op = operators.top();
        operators.pop();

        working_exp.push(eval(val1, val2, op));
    }

    return working_exp.top();
    
}


int IfStack::precedence(char n)
{
	int prec = 0;
	if (n == '*' || n == '/')
		prec = 2;
	if (n == '+' || n == '-')
		prec = 1;
	return prec;
}

double IfStack::eval(double a, double b, char n) 
{
	switch (n) 
		{
			case '+': 
				return a + b;
			case '-': 
				return a - b;
			case '*': 
				return a * b;
			case '/': 
				return a / b;
		}
}



