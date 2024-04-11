#include<bits/stdc++.h>
using namespace std;

class history
{
private:
    queue <string> histo;
    queue <string> temp;
public:
    void addtohis(string s, double ans)
    {
        string addd;
        string n;
        n=to_string(ans);
        addd=s+"= "+n;
        histo.push(addd);
        return;
    }
    void showhis()
    {
        if(histo.empty()) {
            cout<<"history is empty"<<endl ;
        }
        while(!histo.empty()) {
            cout<<histo.front()<<endl;
            temp.push(histo.front());
            histo.pop();
        }
        while(!temp.empty()) {
            histo.push(temp.front());
            temp.pop();
        }
        cout << endl;
        return;
    }
    void clearhis()
    {
        while(!histo.empty()) {
            histo.pop();
        }
        cout<<"History has been cleared!!"<<endl << endl;
        return;
    }
    void delone()
    {
        cout<<histo.front()<<" has been deleted!!"<<endl << endl;
        histo.pop();
        return;
    }

};

template <typename DataType>
class order
{
private:
    struct Node {
        DataType data;
        Node* next;
    };
    Node* head;
public:
    order()
    {
        head = NULL;
    }

    void push(DataType element, bool output = false)
    {
        //   cout << "element being pushed: " <<element << endl;
        struct Node* newNode;
        newNode = new Node();
        newNode->data = element;
        newNode->next = head;
        head = newNode;
    }
    void loop()
    {
        struct Node* temp;
        temp = head;
        while (temp != NULL) {
            temp = temp->next;
        }
    }
    DataType pop()
    {
        struct Node* temp;
        temp = head;
        DataType poppedValue = head->data;
        head = head->next;
        temp->next = NULL;
        free(temp);
        return poppedValue;
    }

    DataType top()
    {
        return head->data;
    }

    bool empty()
    {
        if (head == NULL)
            return true;
        else
            return false;
    }
};

class Calculator
{
private:
    string infix;
    order <double> operands;
    order <char> operators;

public:
    Calculator()
    {
        infix = "";
    }
    Calculator(string userExpr)
    {
        infix = userExpr;
    }

    bool isLegal(string infix)
    {
        bool legal = true;
        int parenthesisCount = 0;
        try {
            for (size_t i = 0; i < infix.length(); i++) {
                switch (infix[i]) {
                case '(':
                    parenthesisCount++;
                    break;
                case ')':
                    parenthesisCount--;
                    break;
                default:
                    break;
                }
            }
            if (parenthesisCount != 0) {
                legal = false;
                throw 0;
            }
        } catch (...) {
            cout<<"Error: Unmatched Parenthesis (Brackets)"<<endl<<endl;;
        }
        return legal;
    }

    bool isOperand(char number)
    {
        if ((number >= '0' && number <= '9')||number=='p')
            return true;
        else
            return false;
    }

    bool isOperator(char op)
    {
        if (op == '+' || op == '-' || op == '*' || op == '/' || op == '(' || op == ')' ||op == '[' || op == ']' || op == '{' || op == '}' || op == '^') {
            return true;
        } else {
            return false;
        }
    }

    bool isSpace(char character)
    {
        if (character == ' ' || character == '\r' || character == '\n')
            return true;
        else
            return false;
    }

    bool isTrigonometry(char character)
    {
        if (character == 's' || character == 'c' || character == 't')
            return true;
        else
            return false;
    }

    bool isExtended(char character)
    {
        if(character == 'x' || character == 'y' || character == 'z')
            return true;
        else
            return false;
    }

    int precedence(char character)
    {
        if (character == '^')
            return 4;
        else if (character == '*' || character == '/')
            return 3;
        else if (character == 's' || character == 'c' || character == 't' || character == 'x' || character == 'y' || character == 'z')
            return 2;
        else if (character == '+' || character == '-')
            return 1;
        else if (character == '(' || character == ')' || character == '[' || character == ']' || character == '{' || character == '}')
            return 0;
        else
            return -1;
    }

    double operate(double valueOne, double valueTwo, char op)
    {
        switch (op) {
        case '+':
            return valueOne + valueTwo;
            break;
        case '-':
            return valueOne - valueTwo;
            break;
        case '*':
            return valueOne * valueTwo;
            break;
        case '/':
            return valueOne / valueTwo;
            break;
        case '^':
            return (double)pow(valueOne, valueTwo);
            break;
        default:
            return 0; // Return default value or handle error
            break;
        }
    }

    double trigonometry(char character, double value)
    {
        double result = 0.0;
        switch(character) {
            case 's':
                result = sin(value);
                break;
            case 'c':
                result = cos(value);
                break;
            case 't':
                result = tan(value);
                break;
            default:
                cout << "Invalid trigonometric function." << endl;
                break;
        }
        return result;
    }

    double extended(char character, double value)
    {
        double result = 0.0;
        switch(character) {
            case 'x':
                result = sqrt(value);
                break;
            case 'y':
                result = log10(value);
                break;
            case 'z':
                result = log(value);
                break;
            default:
                cout << "Invalid extended function." << endl;
                break;
        }
        return result;
    }

    double eval()
    {
        double finalAnswer;
        for (size_t i = 0; i < infix.length(); i++) {
            if (isOperand(infix[i]) == true) {
                double currentNumber = 0;
                while (i < infix.length() && ( isOperand(infix[i]) || infix[i] == '.')) {
                    if (infix[i] == '.') {
                        int counter = 0;
                        int dec = 0;
                        i++;
                        for(; i < infix.length(); i++) {
                            if (isOperand(infix[i])) {
                                dec = 10 * dec + (int)(infix[i] - '0');
                                counter++;
                            } else break;
                        }
                        double calculatedDec= (double)dec / (double)(pow(10, counter));
                        currentNumber += calculatedDec;
                    } else {
                        if (infix[i]!='p') {
                            currentNumber = 10 * currentNumber + (double)(infix[i] - '0');
                        }
                        if (infix[i]=='p'&&currentNumber==0) {
                            currentNumber=M_PI;
                        } else if (infix[i]=='p'&&currentNumber!=0) {
                            currentNumber=currentNumber*M_PI;
                        }
                        ++i;
                    }
                }
                operands.push(currentNumber);
                --i;
            }

            else if(isTrigonometry(infix[i])) {
                if (infix[i] == 's' || infix[i] == 'c' || infix[i] == 't') {
                    operators.push(infix[i]);
                }
                char opTrig = operators.pop();
                double val = 0;
                while ( isOperand(infix[i + 1]) == true) {
                    val =  10 * val + (double)(infix[i + 1] - '0');
                    i++;
                }
                double hasilTrig = trigonometry(opTrig, val);
                operands.push(hasilTrig);
            }

            else if(isExtended(infix[i])) {
                if(infix[i] == 'x' || infix[i] == 'y' || infix[i] == 'z') {
                    operators.push(infix[i]);
                }
                char opEx = operators.pop();
                double angka = 0;
                while ( isOperand(infix[i + 1]) == true) {
                    angka =  10 * angka + (double)(infix[i + 1] - '0');
                    i++;
                }
                double hasilEx = extended(opEx, angka);
                operands.push(hasilEx);
            }

            else if (infix[i] == '(')
                operators.push(infix[i]);

            else if (infix[i] == ')') {
                while (operators.top() != '(') {
                    double valueOne = operands.pop();
                    double valueTwo = operands.pop();
                    char op = operators.pop();
                    operands.push(operate(valueTwo,valueOne,op));
                }
                operators.pop();
            }

            else if (isSpace(infix[i]) == true)
                continue;

            else if (isOperator(infix[i]) == true) {
                if (operators.empty() == true || precedence(infix[i]) > precedence(operators.top())) {
                    operators.push(infix[i]);
                } else {
                    double valueTwo = operands.pop();
                    double valueOne = operands.pop();
                    char op = operators.pop();
                    double operatedValue = operate(valueOne, valueTwo, op);
                    cout << valueOne << " " << op << " " << valueTwo << " = " << operatedValue << endl;
                    operands.push(operatedValue);
                    operators.push(infix[i]);
                }
            }
        }

        finalAnswer = operands.top();

        while (!operators.empty()) {
            operands.loop();
            double valueTwo = operands.pop();
            double valueOne = operands.pop();
            char op = operators.pop();

            double operateValue = operate(valueOne, valueTwo, op);

            operands.push(operateValue, true);
            finalAnswer = operateValue;
        }

        return finalAnswer;
    }

    void setExpr(string infixExpr)
    {
        infix = infixExpr;
    }

    string getExpr()
    {
        return infix;
    }
};

void printOpening()
{
    cout << "WELCOME TO IMAM'S CALCULATOR~" << endl << endl;
    cout << "Here is a litle example on how to use this calculator" << endl;
    cout << "--Example of trigonometry-- " << endl;
    cout << "~ s30 means sin(30)" << endl;
    cout << "~ c60 means cos(60)" << endl;
    cout << "~ t90 means tan(90)" << endl << endl;

    cout << "--Example of sqrt, log, ln-- " << endl;
    cout << "~ x4 means sqrt(4)" << endl;
    cout << "~ y20 means log(20)" << endl;
    cout << "~ z8 means ln(8)" << endl << endl;

    cout << "Enter 0 to exit the program" << endl;
    cout << "Enter H to view history" << endl;
    cout << "Enter D to delete first history" << endl;
    cout << "Enter E to Erase all history" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

int main()
{

    history hh;
    string userInput, sentinel = "0";

    printOpening();

    char usIn;

    while (userInput != sentinel)	{
        cout << "Enter an expression: ";
        getline(cin, userInput);
        usIn = toupper(userInput[0]);
        if (userInput == "0")
            break;
        else if(usIn =='H') {
            hh.showhis();
            continue;
        } else if(usIn =='E') {
            hh.clearhis();
            continue;
        } else if(usIn =='D') {
            hh.delone();
            continue;
        }

        Calculator userExpression(userInput);
        if (userExpression.isLegal(userInput) == false)
            continue;
        else {
            double finalValue = userExpression.eval();
            cout << "\nResult: " <<  finalValue << "\n\n";
            hh.addtohis(userInput, finalValue);
        }
    }

    system("pause");

    return 0;
}
