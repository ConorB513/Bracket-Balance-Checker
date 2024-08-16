/*
Name: Conor Benson
Help:
1. Help with File input and checking status of file (is_open method)
-> https://www.geeksforgeeks.org/how-to-open-and-close-file-in-cpp/
2. Code beautify used to format code nicely 
-> https://codebeautify.org/cpp-formatter-beautifier
*/

#include<iostream>
#include<fstream>
#include<string>
#include "StackDLL.hpp"

using namespace std;

int main() {

    string currentLine; //Keeps track of currentLine in input file
    string fileName; //Keeps track of the name of the file being "scanned"
    fstream inputFile; //Creates file object for the input file
    bool imbalanceFlag = false; //Variable becomes true if an imbalance of brackets is detected
    char currentChar; //Keeps track of current char being iterated through 
    int lineNumber = 0; //Counter of num of lines of input file
    int currentLineSize = 0; //Keeps track of size of currentLine
    DLLStack < char > * bracketStack = new DLLStack < char > ; //Creates a stack to store opening brackets

    cout << "Please enter the name of the file: ";
    cin >> fileName;

    //InputFile object opens a file based of input name
    inputFile.open(fileName);

    //Condition checks if file exists by seeing if its open, if it isn't, quit the program 
    if (!inputFile.is_open()) {
        cout << "Cannot open the file ... quitting the program" << endl;
        return 0;

    }

    //While loop iterates through each line of the input file as long as no imbalance is triggered
    while (getline(inputFile, currentLine) && !imbalanceFlag) {

        currentLineSize = currentLine.size();

        //For loop iterates through each char of the currentLine
        for (int i = 0; i < currentLineSize; i++) {
            currentChar = currentLine.at(i);

            // If the current char is an opening bracket, add it to the stack
            if (currentChar == '(' ||
                currentChar == '[' ||
                currentChar == '{') {

                bracketStack -> push(currentChar);
            } else if (currentChar == ')' ||
                currentChar == ']' ||
                currentChar == '}') {

                /*If the current Char is a closing bracket, the stack is not empty 
                and the top of the stack has the corresponding opening bracket 
                pop the top bracket from the stack 
                */
                if (!bracketStack -> empty() && (
                        (currentChar == ')' && bracketStack -> top() == '(') ||
                        (currentChar == ']' && bracketStack -> top() == '[') ||
                        (currentChar == '}' && bracketStack -> top() == '{'))) {
                    bracketStack -> pop();

                }

                /*If the stack is empty or if the top bracket of the stack doesn't correspond
                to the current closing bracket, set the statues of imbalanceFlag to true 
                */
                else {
                    imbalanceFlag = true;
                }

            }

        }
        lineNumber++;
    }

    //If an imbalance was triggered, notify the user and include the line num
    if (imbalanceFlag) {
        cout << "Imbalanced triggered at line " << lineNumber << endl;
    }

    /*If the stack is not empty after the whole file is scanned, there exsits
    an imbalance of opening brackets, notify the user and include the number 
    of opening brackets left in the stack  

    */
    else if (!bracketStack -> empty()) {
        //Number of unbalanced opening brackets will be the number of nodes in the stack
        cout << bracketStack -> size() <<
            " opening brackets(s) do(es) not have a matching closing bracket." << endl;
    } else {
        cout << "All brackets are balanced" << endl;
    }

    //Delete excess contents of stack before quitting program
    delete(bracketStack);

    return 0;
}

