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
    string no_space_express;
	cout << "Type your infix operators: \n";

	getline(cin, express);

    // want to ignore spaces in the formation of the expression
    for(int i = 0; i < express.length(); i++)
    {
        if (express[i] != ' ')
            no_space_express += express[i];
    }
    
	return no_space_express;	
}	



double IfStack::solve_exp()
{
    string user_exp = getMsg();
    

    for (int i = 0; i < user_exp.length(); i++) 
    {
        if (i == 0 && user_exp[i] == '-') // checks if the first part of the string is a unary -
            unary = true;
        // because this processes all - characters I added the other statement to add subtraction - to the operators
        // it worked earlier tonight but I messed it up and now I'm burnt out (11/17/2021)
        else if (user_exp[i] == '-')
        { 
            if (user_exp[i - 1] == '+' ||
                user_exp[i - 1] == '*' ||
                user_exp[i - 1] == '-' ||
                user_exp[i - 1] == '/' ||
                user_exp[i - 1] == '(')
            {
                if (i != user_exp.length() && isdigit(user_exp[i + 1])) {
                    negnum = true; // sets the flag to negate the next number added to the stack
                    
                }
                else
                {
                    unary = true; // sets the flag to negate an operation 
                    
                }
                
            }
        }        

        // push any open parenthesis on the operators stack
        else if (user_exp[i] == '(')
            operators.push(user_exp[i]);

        // push any numbers on the working expression stack        
        else if (isdigit(user_exp[i]))
        {
            string concat_num = "";            
            // TO DO MAYBE: Refactor with for loop, set i to j at the end, use substring

            while (isdigit(user_exp[i])) //concatenates individual digits into any larger numbers
            {
                concat_num += user_exp[i];
                i++;
            }
            i--; // back up one spot so we don't miss the operator 
                 // after adding individual digits. SHOULD REWRITE
            
            if (negnum) {
                // convert the number to negative if the negnum flag is set
                working_exp.push(stod(concat_num) * -1 );
                negnum = false;
            }
            else
                // no negnum flag is set, push the number as is
                working_exp.push(stod(concat_num));

        }            

        // if we find a close parenthesis, want to stop and eval it right away
        else if (user_exp[i] == ')')
        {
            // as long as there are still operators we want to be in this loop
            // unless we hit another open parenthesis
            while (!operators.empty() && operators.top() != '(')
            {
                if (!working_exp.empty() && !operators.empty())
                {                   
                    // Do addition/mult etc... or and if unary flag is set, negate it.
                    unary ? handle_negation() : perform_operation(); 
                }
            }

            if (!operators.empty()) // I only want to pop here to get rid of my '(' in my stack
                operators.pop(); 
        }
                
        else //still working through the user expression
        {
            while ((!operators.empty()) 
                    && precedence(operators.top()) 
                    >= precedence(user_exp[i]))                 
            {
                if (!working_exp.empty() && !operators.empty())
                {
                    // Do addition/mult etc... or and if unary flag is set, negate it.
                    (unary ? handle_negation() : perform_operation());
                }
            }            
            operators.push(user_exp[i]);
        } 
       
    }  // Done handling the parenthesis and adding the user string? 

    while (!operators.empty()) 
    {    // Do addition/mult etc... or and if unary flag is set, negate it.
        (unary ? handle_negation() : perform_operation());    
    }

    return working_exp.top(); // When everything is done, our working_expression stack will
                              // have our final result, which we return.
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


// The same logic as perform_operation, simply multiplies by -1 after the eval step 
// and un-sets the unary flag that sent us here for negation
void IfStack::handle_negation()
{
    operand2 = working_exp.top(); 
    working_exp.pop();

    operand1 = working_exp.top(); 
    working_exp.pop(); 

    working_operator = operators.top();
    operators.pop();
   
    working_exp.push(eval(operand1, operand2, working_operator)* -1);
    unary = false;    
}