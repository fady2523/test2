#include <iostream> //header file For input/output (cout, cin).
#include <fstream> //header file For file handling (reading/writing files).
#include <cctype> // header file For character checking functions like isalpha(), isdigit(), isspace().
#include <cstring> //header file For string handling functions like strcpy().

using namespace std;  // This lets you use cout, cin, ifstream without writing std:: every time.

/* Global declarations */
int charClass; //This variable stores the class of the character: LETTER, DIGIT, or UNKNOWN.
char lexeme[100]; // Array to store the current word/identifier or number from the input.
char nextChar; //Stores the current character being read from the file.
int lexLen; // Stores the length of the current lexeme.
int token; //  These hold the current token code (type of the item read).
int nextToken; // These hold the current token code (type of the item read).
ifstream in_fp; // File pointer object for reading from a file.

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);
// These are function prototypes (functions declared but defined later).
/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
// Constants for identifying the type of character.

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
// Constants to represent tokens: For example, ADD_OP means '+' operator.

/******************************************************/
/* Main driver */
//Program execution starts here.
int main() {
    in_fp.open("front.in"); // Opens the file "front.in" for reading.

    if (!in_fp) {
        cout << "ERROR - cannot open front.in" << endl; //If the file doesn't open Show error message.
    }
    else {
        getChar();
        do {
            lex();
        } while (nextToken != EOF); //If file opens: Call getChar() to read first character. Keep calling lex() until End Of File(EOF).
    }
    in_fp.close(); //Close the file after reading.
    return 0; // End of the main function.
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses */
int lookup(char ch) { //Identifies operators and parentheses.
    switch (ch) { //Checks the character and assigns the correct token.
    case '(':
        addChar();
        nextToken = LEFT_PAREN;  //If it's (, add to lexeme and assign token  LEFT_PAREN.
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN; //If it's ), add to lexeme and assign token RIGHT_PAREN.
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;   //If it's +, add to lexeme and assign token ADD_OP.
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;   //If it's -, add to lexeme and assign token SUB_OP.
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;  //If it's *, add to lexeme and assign token MULT_OP.
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;  //If it's /, add to lexeme and assign token DIV_OP.
        break;
    default:
        addChar();
        nextToken = EOF;   //If unknown character treat as EOF.
        break;
    }
    return nextToken;
}

/*****************************************************/
/* addChar - add nextChar to lexeme */
void addChar() { // Adds nextChar to lexeme[].
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';         // Adds character and updates lexeme length, ends with null character for string.
    }
    else {
        cout << "Error - lexeme is too long" << endl;
    }
}

/*****************************************************/
/* getChar - get the next character and determine its class */
void getChar() {  //Reads next character from file.
    if (in_fp.get(nextChar)) { //If read successfully.
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    } // Identify the character class.
    else {
        charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - skip whitespace */
void getNonBlank() {
    while (isspace(nextChar))
        getChar();  //Skip any white spaces.
}

/*****************************************************/
/* lex - simple lexical analyzer */
int lex() { //Main lexical analyzer that identifies tokens.
    lexLen = 0;
    getNonBlank();  //Reset lexeme length and skip spaces.

    switch (charClass) { //Check what kind of token to process.
    case LETTER: //Read complete identifier (like variable name).
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;

    case DIGIT: //Read complete number.
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;

    case UNKNOWN: // Handle operators or parentheses.
        lookup(nextChar);
        getChar();
        break;

    case EOF: //End of file reached.
        nextToken = EOF;
        strcpy(lexeme, "EOF");
        break;
    }

    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl; //Display the token code and its value.
    return nextToken;
}
