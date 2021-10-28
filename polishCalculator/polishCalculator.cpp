// polishCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
typedef double Stack_entry;
#include "stack.h"

using namespace std;

Extended_stack stored_numbers;


void get_command(string argv);

void introduction()
{
    cout << "This is a postfix calculator which takes in elements and calculates them by using stacks" << endl;
    cout << "Standard input looks like 1 2 3 + and the output would be 5 " << endl;
    cout << "It is important to add space bar after each arithmetic operation, 3 4+= is okay but 3 4+5+= wont work" << endl;
}


void inputFromPrompt()
{
    string s;
    vector<string> save;
    string temp = "";
    getline(cin, s);
    //cout << "input was " << s << endl;

    for (int j = 0; j < s.size(); j++)
    {
       
        //cout << "s[j] is " << s[j] << endl;
        if (s[j] != ' ')
        {
            temp += s[j];
        }

        if (s[j] == ' ' || s[j+1] == '\0')
        {
            //cout << "temp is here " << temp << endl;
            save.push_back(temp);
            temp = "";
        }
    }
    for (int i = 0; i < save.size(); i++)
    {
        //cout<<save[i]<<endl;
        get_command(save[i]);
    }
}


void instructions()
{
    cout << "The valid commands are:" << endl
        << "[=]print top" << endl
        << "[+] [_] [*] [/]   are arithmetic operations" << endl
        << "[x] to switch top 2 entries      [s] to add all elements in the stack" << endl
        << "[a] average of the sum      [%] to calculate remainder "<<endl
        << "[^] Raise to power      [v] Square root     [Q]uit." << endl;
    inputFromPrompt();
}



bool do_command(char command, Extended_stack& numbers)
/*
Pre:  The first parameter specifies a valid calculator command.
Post: The command specified by the first parameter
      has been applied to the Stack of numbers given by the second parameter.
      A result of true is returned unless command == 'q'.
Uses: The class Stack.
*/

{
    double p, q, temp = 0;
    int size = 0;
   // cout << command << endl;
    switch (command) {

    case '=':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else
            cout << p << endl;

        break;

    case '+':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                if (numbers.push(q + p) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case '_':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                if (numbers.push(q - p) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case '*':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                if (numbers.push(q * p) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case '/':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                if (numbers.push(q / p) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case 'x':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            //cout << "Here is p" << p << endl;
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }
            //
            else {
                numbers.push(p);
                numbers.top(p);
                numbers.pop();
                if (numbers.top(q) == underflow)
                {
                    cout << "Stack should have more than one number" << endl;
                }
                else
                {
                    numbers.top(q);
                    numbers.pop();
                    numbers.push(p);
                    numbers.push(q);
                }
            }
        }
        break;
        //   Add options for further user commands.

    case 's':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }
            else {
                numbers.push(p);
                while (!numbers.empty())
                {
                    numbers.top(p);
                    temp += p;
                    numbers.pop();
                }
                numbers.push(temp);
            }

        }
        break;

    case 'a':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }
            else {
                numbers.push(p);
                size = numbers.size();
                while (!numbers.empty())
                {
                    numbers.top(p);
                    temp += p;
                    numbers.pop();
                }
                numbers.push(temp / size);
            }

        }
        break;


    case '%':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                temp = fmod(q, p);
                if (numbers.push(temp) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case '^':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                temp = pow(q, p);
                if (numbers.push(temp) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case 'v':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.top(p);
            temp = sqrt(p);
            if (numbers.push(temp) == overflow)
                cout << "Warning: Stack full, lost result" << endl;
        }
        break;

    case 'q':
        cout << "Calculation finished.\n";
        return false;
    }
    return true;
}

void get_command(string argv)
{
    char command;
    string temp = "";
    string store = "";
    string x = "";
    double p;
    //bool waiting = true;
    //cout << "Select command and press <Enter>:";
   // cout << "Argument received is " << argv << endl;
    
    //cout << "command is " << command << endl;
    for (int x = 0; x < argv.size(); x++)
    {
        command = argv[x];
        if (command == '0' || command == '1' || command == '2' ||
            command == '3' || command == '4' || command == '5' ||
            command == '6' || command == '7' || command == '8' ||
            command == '9' || command == '.')
        {
            temp += argv[x];
            store = temp;
        }
    }

    //cout << "Temp here is" << temp << endl;

    for (int i = 0; i < argv.size(); i++)
    {
        command = argv[i];
        
        if (temp.size() > 1)
        {
            for (int i = 0; i < temp.size(); i++)
            {
                //cout << "MAde i t here" << endl;
                x += temp[i];
                //cout << "Number push " << x << " Number got " << temp[i] << endl;
                
            }
            p = stod(x);
            //cout << "i push x " << p << endl;
            stored_numbers.push(p);
            x = "";
            temp = "";
        }
        else if (temp.size() == 1)
        {
            p = stod(temp);
            //cout << "Value of p is " << p << endl;
            temp = "";
            //cout << "i push y = " << p << endl;
            stored_numbers.push(p);
        }

        if (command == '+' || command == '_' || command == '*' ||
            command == '/' || command == '=' || command == 'q' ||
            command == '^' || command == 'v' || command == 'a' ||
            command == '%' || command == 'x' || command == 's')
        {
            //cout << "command input is " << command << endl;
            do_command(command, stored_numbers);
        }
        
    }
       
}


int main(int argc, const char * argv[])
/*
Post: The program has executed simple arithmetic
      commands entered by the user.
Uses: The class Stack and the functions
      introduction, instructions, do_command, and get_command.
*/

{
    string s = "";

    if (argc == 1)
    {
        introduction();
        instructions();
    }

    if (argc == 2 || argv[1][0] == 'p')
    {
        cout << "prompt input was truggered" << endl;
        introduction();
        instructions();
    }
    else
    {
        
        //cout << argc << endl;
        for (int i = 1; i < argc; i++)
        {
            s = "";
            for (int j = 0; argv[i][j] != '\0'; j++)
            {
                s += argv[i][j];
            }
            //cout << "Value of s is here " << s << " " << endl;
            s += " ";
            get_command(s);
            //do_command(get_command(s), stored_numbers);
        }
    }
    
    //while (do_command(get_command(), stored_numbers));
}





