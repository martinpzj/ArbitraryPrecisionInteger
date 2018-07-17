//CREATED: 4-25-18 Martin Perez
//Test file for apint.c

#include <stdio.h>
#include <stdlib.h>
#include "apint.h"

int main(){
	//Testing constructor for conversion of Strings
	apint testString = strApint("49140147592285");
	printf("TESTING STRING CONSTRUCTOR: ");
	print(testString);
	apint negativeString = strApint("-5235325243401");
	printf("TESTING NEGATIVE STRING CONSTRUCTOR: ");
	print(negativeString);
	freeApint(&testString);
	freeApint(&negativeString);

	//Testing constructor for conversion of ints
	apint testInt = intApint(97249743);
	printf("TESTING CONSTRUCTOR FOR CONVERSION OF INTS: ");
	print(testInt);
	apint negativeInt = intApint(-35239352);
	printf("TESTING CONSTRUCTOR FOR CONVERSION OF NEGATIVE INTS: ");
	print(negativeInt);
	freeApint(&testInt);
	freeApint(&negativeInt);

	//Testing addition method
	apint testAdd = strApint("954396709353235");
	apint testAdd2 = strApint("902538902523932");
	apint sum = add(testAdd,testAdd2);
	printf("TESTING METHOD FOR ADDITION: \n");
	printf("954396709353235 + 902538902523932 = ");
	print(sum);
	freeApint(&testAdd);
	freeApint(&testAdd2);
	freeApint(&sum);
	apint testAdd3 = intApint(54843893);
	apint testAdd4 = intApint(-3859385);
	apint sum2 = add(testAdd3,testAdd4);
	printf("54843893 + (-3859385) = ");
	print(sum2);
	freeApint(&testAdd3);
	freeApint(&testAdd4);
	freeApint(&sum2);

	//Testing subtraction method
	apint testSub = strApint("8390320950853");
	apint testSub2 = strApint("5852353857235");
	apint sub = subtract(testSub,testSub2);
	printf("TESTING METHOD FOR SUBTRACTION: \n");
	printf("8390320950853 - 5852353857235 = ");
	print(sub);
	freeApint(&testSub);
	freeApint(&testSub2);
	freeApint(&sub);
	apint testSub3 = intApint(-31943);
	apint testSub4 = intApint(5959);
	apint sub2 = subtract(testSub3,testSub4);
	printf("(-31943) - 5959 = ");
	print(sub2);
	freeApint(&testSub3);
	freeApint(&testSub4);
	freeApint(&sub2);

	//Testing multiplication method
	apint testMult = strApint("42095239290578321049124");
	apint testMult2 = strApint("78532890527389523905");
	apint mult = multiply(testMult,testMult2);
	printf("TESTING METHOD FOR MULTIPLICATION: \n");
	printf("42095239290578321049124 * 78532890527389523905 = ");
	print(mult);
	freeApint(&testMult);
	freeApint(&testMult2);
	freeApint(&mult);
	apint testMult3 = intApint(-624828);
	apint testMult4 = intApint(-452399);
	apint mult2 = multiply(testMult3,testMult4);
	printf("-624828 * -452399 = ");
	print(mult2);
	freeApint(&testMult3);
	freeApint(&testMult4);
	freeApint(&mult2);
}