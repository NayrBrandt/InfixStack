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

	getline(cin, express);

	return express;	
}	



/*

Need to handle negative numbers. Can I just * -1 to get to where I want? 
Can have -(x+y) and should negate the whole paren expression
Can have x - -y and should add. Should work natively if I negate y?
Check my operators stack and see if the - is coming after a non ) or number, if so then negate next num?
The - op is unary if after NULL (at beginning of expression) or after a +, -, /, *, or (
*/
double IfStack::solve_exp()
{
    string user_exp = getMsg();
    bool neg = false;

    for (int i = 0; i < user_exp.length(); i++)
    {
        // want to ignore spaces in the formation of the expression
        if (user_exp[i] == ' ')
            continue;

        

        // SHOULD BE ABLE TO PUSH THIS IN THE HANDLE_NEGATION FUNCTION TO WORK BETTER
        if (user_exp[i] == '-')
        {
            if (i > 0 && user_exp[i - 1] == '+' ||
                user_exp[i - 1] == '*' ||
                user_exp[i - 1] == '-' ||
                user_exp[i - 1] == '/' ||
                user_exp[i - 1] == '(' )
            {
                neg = true;                
            }
        }
      
        
        ///////////////////////////////////
        // Maybe handle negatives up here



        // push any open parenthesis on the operators stack
        else if (user_exp[i] == '(')
            operators.push(user_exp[i]);

        // push any numbers on the working expression stack
        // should read in ints and convert them to doubles? 
        else if (isdigit(user_exp[i]))
            working_exp.push(stod(string(1, user_exp[i])));

        // if we find a close parenthesis, want to stop and eval it right away
        else if (user_exp[i] == ')')
        {
            // as long as there are still operators we want to be in this loop
            // unless we hit another open parenthesis
            while (!operators.empty() && operators.top() != '(')
            {
                if (!working_exp.empty() && !operators.empty()) { //does this need to be size >= 2?
                    (neg ? handle_negation() : perform_operation());
                    neg = false;
                }
            }
            // pop...
            if (!operators.empty()) // I only want to pop here to get rid of my '(' in my stack
                operators.pop(); 
        }
                
        else //still working through the user expression
        {
            while ((!operators.empty()) && precedence(operators.top()) 
                    >= precedence(user_exp[i])) 
                // digits should be pushed so val at [i] should be an operator?
            {
                if (!working_exp.empty() && !operators.empty())
                {
                    (neg ? handle_negation() : perform_operation());
                    neg = false;
                }
            }
            /// <summary>
            /// IS THIS WHERE I HANDLE NEGATIVES?
            /// </summary>
            /// <returns></returns>
            operators.push(user_exp[i]);
        }
    }  // Done handling the parenthesis and adding the user string? 

    while (!operators.empty()) {
        (neg ? handle_negation() : perform_operation());
        neg = false;
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

void IfStack::perform_operation()
{
    operand2 = working_exp.top(); //take the first number WHICH IS OUR SECOND OPERAND
    working_exp.pop(); // discard that number to access next

    operand1 = working_exp.top(); // take the second number WHICH IS THE FIRST OPERAND
    working_exp.pop(); // discard that number to access next 

    working_operator = operators.top(); // assumes we've got another operator besides the () in?
    operators.pop(); 

    working_exp.push(eval(operand1, operand2, working_operator)); //pushing the result of the calc of the above numbers

}

void IfStack::handle_negation()
{
    //if (working_exp[i] == '-')


    operand2 = working_exp.top(); //take the first number WHICH IS OUR SECOND OPERAND
    working_exp.pop(); // discard that number to access next

    operand1 = working_exp.top(); // take the second number WHICH IS THE FIRST OPERAND
    working_exp.pop(); // discard that number to access next 

    working_operator = operators.top(); // assumes we've got another operator besides the () in?
    operators.pop();

    working_exp.push(eval(operand1, (operand2 * -1), working_operator)); //pushing the result of the calc of the above numbers


}



