//CREATED: 4-25-18 Martin Perez
//Header file for apint ADT

#ifndef _APINT_H_INCLUDE_
#define _APINT_H_INCLUDE_

//Exported reference type
typedef struct apintObj* apint;

//default constructor for apint
apint newApint();

//destructor for apint
void freeApint(apint* ap);

//constructor for conversion of Strings
apint strApint(char* number);

//constructor for conversion of ints
apint intApint(int number);

//method for addition
apint add(apint number1, apint nummber2);

//method for subtraction
apint subtract(apint number1, apint number2);

//method for multiplication
apint multiply(apint number1, apint number2);

//method for printing
void print(apint number);

#endif