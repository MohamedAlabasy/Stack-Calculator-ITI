#include <iostream>

using namespace std;
//==================================================================================//
//						    Stack Class with template	    				        //
//==================================================================================//
template <class T> //to use the class as integer or string
class Stack
{
    int topOfStack;
    int sizeOfArray;
    T* stackArray;
public:
    //constructor with default argument
    Stack(int _size = 50)
    {
        topOfStack = -1;  //Stack array start topOfStack = 0
        sizeOfArray = _size;
        stackArray = new T[sizeOfArray];
    }

    //Add an item in the last available place in stack array
    void push(int _operator)
    {
        if(topOfStack >= sizeOfArray - 1)
        {
            cout <<"Stack is full , You Can't Push"<<endl;
            return; //To out of the push fun
        }
        stackArray[++topOfStack] = _operator; //Add item to last available place in stack array
    }
    //get last item stack array and it
    T pop()
    {
        if(topOfStack < 0)
        {
            cout <<"Stack is empty , You Can't pop"<<endl;
            return 0;
        }
        T val = stackArray[topOfStack--];  //reduce the topOfStack to refer to the last item in stack array
        return val;
    }

    //check if the stack array is empty or not
    bool isEmpty()
    {
        return topOfStack < 0;
    }

    // The lastItem function is similar to the pop function in terms
    //that it returns the top items from a stack Array.
    //But the lastItem function doesn't delete the element , only returns it.
    T lastItem()
    {
        if(topOfStack < 0)
        {
            cout << "Stack is empty"<<endl;
            return 0;
        }
        return stackArray[topOfStack];
    }
    //Destructor used to delete stackArray when Class destroyed
    ~Stack()
    {
        delete[] stackArray;
    }
}; //end of Stack Class
//==================================================================================//
//								function prototype							        //
//==================================================================================//
int isNumber(char _number);// Check is char is a Number or not
int isOperators(char _operator);// Check if char is an operation
int getPrecedence(char _operator);// Determine the precedence of an operation
int operate(int _fNumber, int _sNumber, char _operator);// Evaluate an arithmetic expression
int evaluate(char* _operation); // Evaluate a string

//==================================================================================//
//								   main function   							        //
//==================================================================================//
int main()
{
    cout <<" 1 + 2 * ( 2 * 3 ) + 2 = "<< evaluate("1 + 2 * (2 * 3) + 2") << endl; // 15
    cout<<"=================================================================================="<<endl;
    cout <<" 3 + 4 * 5 = "<< evaluate("3 + 4 * 5") << endl; // 23
    cout<<"=================================================================================="<<endl;
    cout <<" ( 3 + 4 ) * 5 = "<< evaluate("(3 + 4) * 5") << endl; // 35
    cout<<"=================================================================================="<<endl;

    cout <<" 3 * 4 + 5 = "<< evaluate("3 * 4 + 5") << endl; // 17
    cout<<"=================================================================================="<<endl;

    cout <<" ( 3 + 1 ) * 2 * ( 2 * 4 ) + 2 = "<< evaluate("(3 + 1) * 2 * (2 * 4) + 2") <<endl; // 66
    cout<<"=================================================================================="<<endl;

    return 0;
}

// Check is char is a Number or not
int isNumber(char _number)
{
    return (_number >= '0' && _number <= '9');
}

// Check if char is an operation
int isOperators(char _operator)
{
    return (_operator == '+' || _operator == '-' || _operator == '*' ||
            _operator == '/' || _operator == '(' || _operator == ')');
}

// Determine the precedence of an operation
int getPrecedence(char _operator)
{
    switch(_operator)
    {
    case '(':
    case ')':
        return 1;
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    default:
        return -1;
    }
}

// Evaluate an arithmetic expression
int operate(int _fNumber, int _sNumber, char _operator)
{
    if(_operator == '+')
        return _fNumber + _sNumber;
    if(_operator == '-')
        return _fNumber - _sNumber;
    if(_operator == '*')
        return _fNumber * _sNumber;
    if(_operator == '/')
        return _fNumber / _sNumber;
}

// Evaluate a string
int evaluate(char* _operation)
{
    Stack<int> numbers;    //object for numbers in the operation
    Stack<char> operators; //object for operators in the operation

    int numberValue = 0; //refer to number values in the operation
    int position = 0;    //refer to position in the operation
    while (_operation[position])
    {
        char spot = _operation[position];
        if(isNumber(spot))
        {
            //To adding next number for example(15) will be >> 1 >> 10 >> 15
            numberValue = (numberValue * 10) + (int)(spot - '0');
        }
        else if(isOperators(spot))
        {
            if(spot == '(') //check if it's ( to start using curly braces which is the highest Precedence
            {
                operators.push(spot);
                numberValue = 0; //to return to the first value
            }
            else if(numbers.isEmpty())
            {
                numbers.push(numberValue);
                operators.push(spot);
                numberValue = 0;
            }
            else if(spot == ')') //end of curly braces must do the operation
            {
                numbers.push(numberValue);

                while (operators.lastItem() != '(')
                {
                    spot = operators.pop();
                    numberValue = numbers.pop();
                    int prev = numbers.pop();
                    numberValue = operate(prev, numberValue, spot);
                    numbers.push(numberValue);
                }
                operators.pop();
                numbers.pop();
            }
            else
            {
                char prev = operators.lastItem();
                if(getPrecedence(spot) > getPrecedence(prev))
                {
                    numbers.push(numberValue);
                    operators.push(spot);
                    numberValue = 0;
                }
                else
                {
                    int prevval = numbers.pop();
                    int prevop = operators.pop();
                    prevval = operate(prevval, numberValue, prevop);
                    numbers.push(prevval);
                    operators.push(spot);
                    numberValue = 0;
                }
            }
        }
        position++;
    }

    while (!operators.isEmpty())
    {
        int prev = numbers.pop();
        char spot = operators.pop();
        numberValue = operate(prev, numberValue, spot);
    }
    return numberValue;
}


