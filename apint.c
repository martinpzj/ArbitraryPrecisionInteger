//CREATED 4-25-18 Martin Perez
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "apint.h"

//create apintObj
typedef struct apintObj{
	int sign;
	int lengthOfInt;
	int lengthOfString;
	int* array;
} apintObj;

//default constructor for apint
apint newApint(){
	apint temp = malloc(sizeof(apintObj));
	temp->sign = 0;
	temp->lengthOfInt = 0;
	temp->lengthOfString = 0;
	temp->array = (int *)calloc(100, sizeof(int));
	return temp;
}

//destructor for apint
void freeApint(apint* ap){
	(*ap)->sign = 0;
	(*ap)->lengthOfInt = 0;
	(*ap)->lengthOfString = 0;
	free(*ap);
	*ap = NULL;
}

//constructor for converion of Strings
apint strApint(char* number){
	apint temp = malloc(sizeof(apintObj));
	temp->array = (int *)calloc(100, sizeof(int));
	/*Checks to see if string contains a negative symbol.
	If it does enter the block of code and store every digit in
	array*/
	if(number[0] == '-'){
		temp->sign = -1; //set sign to -1
		temp->lengthOfString = strlen(number);
		temp->lengthOfInt = strlen(number)-1;
		for(int i = 1; i < temp->lengthOfString; i++)
			temp->array[i-1] = number[i]-'0';
		//multiply the first digit in the array by -1
		temp->array[0] = temp->array[0]*-1;
	}
	/*If the string is positive, proceed to this section 
	and store every digit into the array*/
	else{
		temp->lengthOfInt = temp->lengthOfString = strlen(number);
		temp->sign = 1;
		for(int i = 0; i < temp->lengthOfString; i++)
			temp->array[i] = number[i]-'0';
	}
	return temp;
}

//constructor for conversion of ints
apint intApint(int number){
	apint temp = malloc(sizeof(apintObj));
	temp->array = (int *)calloc(100, sizeof(int));
	//Check to see if the value passed is negative
	if(number < 0){
		temp->sign = -1; //set the sign to -1
		/*Subtract by one to ignore the negative symbol being counted
		towards the length*/
		temp->lengthOfInt = floor(log10(abs(number))+1);
		int tempLength = temp->lengthOfInt;
		/*convert our negative number into positive so our while loop
		can work*/
		number = number*-1;
		while(number > 0 && tempLength >= 0){
			temp->array[tempLength-1] = number%10;
			number = number/10;
			tempLength--;
		}
		//convert the first digit in the array to negative
		temp->array[0] = temp->array[0]*-1;
	}
	//this branch of code runs when the number is positive
	else{
		temp->sign = 1;
		temp->lengthOfInt = floor(log10(abs(number))+1);
		int tempLength = temp->lengthOfInt;
		while(number > 0 && tempLength >= 0){
			temp->array[tempLength-1] = number%10;
			number = number/10;
			tempLength--;
		}
	}
	return temp;
}

//method for printing
void print(apint number){
	/*This block of code is only used to print a string constructor*/
	if(number->lengthOfString > 0){
		if(number->sign == -1){
			for(int i = 0; i < number->lengthOfString-1; i++)
				printf("%d",number->array[i]);
			printf("\n");
		}
		else{
			for(int i = 0; i < number->lengthOfString; i++)
				printf("%d",number->array[i]);
			printf("\n");
		}
	}
	/*This will work for everything else */
	else{
		for(int i = 0; i < number->lengthOfInt; i++)
			printf("%d", number->array[i]);
		printf("\n");
	}
}
//***********************************************************************

//method for addition
apint add(apint number1, apint number2){
	apint sum = malloc(sizeof(apintObj));
	sum->array = (int *)calloc(100,sizeof(int));
	int len_num1 = number1->lengthOfInt;
	int len_num2 = number2->lengthOfInt;
	int newLength;
	int carryOut = 0;
	int newVal;
	/*newLength = the array w/ the most digits.
	This will also be the length of our new array*/
	if(len_num2 >= len_num1)
		sum->lengthOfInt = newLength = len_num2;
	else
		sum->lengthOfInt = newLength = len_num1;

	//(-10)+(-5)
	if(number2->array[0] < 0 && number1->array[0] < 0){
		number2->array[0] = number2->array[0]*-1;
		number1->array[0] = number1->array[0]*-1;
		sum = add(number1,number2);
		sum->array[0] = sum->array[0]*-1;
		return sum;
	}
	//10+(-5)
	else if(number2->array[0] < 0){
		number2->array[0] = number2->array[0]*-1;
		sum = subtract(number1,number2);
		return sum;
	}
	//(-10)+5
	else if(number1->array[0] < 0){
		number1->array[0] = number1->array[0]*-1;
		sum = subtract(number1,number2);
		sum->array[0] = sum->array[0]*-1;
		return sum;
	} 
	else{
		//We get here if both numbers we are adding are positive
		for(int i = 1; i <= newLength; i++){
			/*if one array falls off the edge drop the contents of
			the array that hasn't fallen off into our new array*/
			if(len_num2-i<0 && len_num1-i >= 0){
				if(number1->array[len_num1-i]+carryOut > 9 &&
					len_num1-i == 0)
					sum->array[newLength-i]=number1->array[len_num1-i]+carryOut;
				else if(number1->array[len_num1-i]+carryOut>9
						&& len_num1-i != 0){
					newVal = number1->array[len_num1-i]+carryOut;
					carryOut = newVal/10;
					newVal = newVal%10;
					//store newVal into sum->array
					sum->array[newLength-i] = newVal;
				}
				else{
					sum->array[newLength-i] = number1->array[len_num1-i]+carryOut;
					carryOut = 0;	//reset carryOut
				}
			}
			else if(len_num2-i>=0 && len_num1-i<0){
				if(number2->array[len_num2-i]+carryOut>9 &&
					len_num2-i == 0)
					sum->array[newLength-i] = number2->array[len_num2-i]+carryOut;
				else if(number2->array[len_num2-i]+carryOut>9
				        && len_num2-i != 0){
					newVal = number2->array[len_num2-i]+carryOut;	
					carryOut = newVal/10;	//get the quotient
					newVal = newVal % 10;	//get remainder
					//store newVal into object array
					sum->array[newLength-i] = newVal;
				}
				else{
					sum->array[newLength-i] = number2->array[len_num2-i]+carryOut;
					carryOut = 0;	//reset carryOut
				}
			}
			/*if none of the arrays have fallen off the edge, add the
			 digits starting from the end of each corresponding array*/
			else{
				/*if both arrays have reached the first index drop the
			  	 final value into our new array*/
				if(len_num2-i==0 && len_num1-i==0){
			  		newVal = number2->array[len_num2-i]+number1->array[len_num1-i]+carryOut;
			  		//store newVal into our new array
			  		sum->array[newLength-i] = newVal;
			  	}
			  	else{
			  		//add the two digits in the wanted indices w/ carryOut if any
			  		newVal = number2->array[len_num2-i]+number1->array[len_num1-i]+carryOut;	
			  		carryOut = newVal/10;	//get the quotient
			  		newVal = newVal % 10;	//get remainder
			  		//store newVal into object array
			  		sum->array[newLength-i] = newVal;
			  	}
			}
		}
	}

	return sum;
}

//method for subtraction
apint subtract(apint number1, apint number2){
	apint sub = malloc(sizeof(apintObj));
	sub->array = (int *)calloc(100,sizeof(int));
	int len_num1 = number1->lengthOfInt;
	int len_num2 = number2->lengthOfInt;
	int newLength = 0;
	int newVal;
	/*newLength = the array w/ the most digits.
	This will also be the length of our new array*/
	if(len_num1 >= len_num2)
		sub->lengthOfInt = newLength = len_num1;
	else
		sub->lengthOfInt = newLength = len_num2;

	//(-a)-(-b) = (-a)+b
	if(number1->array[0] < 0 && number2->array[0] < 0){
		number2->array[0]=number2->array[0]*-1;
		sub = add(number1,number2);
		return sub;
	}
	//a-(-b) = a + b
	else if(number2->array[0] < 0){
		number2->array[0]=number2->array[0]*-1;
		sub = add(number1,number2);
		return sub;
	}
	//(-a)-b = -(a+b)
	else if(number1->array[0] < 0){
		number1->array[0]=number1->array[0]*-1;
		sub = add(number1,number2);
		sub->array[0]=sub->array[0]*-1;
		return sub;
	}
	/*We reach here when the two values we are subtracting are both
	positive*/
	else{
		for(int i = 1; i <= newLength; i++){
			/*this if statement is used for borrowimg when we are
			 subtracting*/
			if(len_num2-i >=0){
				if(number1->array[len_num1-i]<number2->array[len_num2-i]){
					number1->array[len_num1-i]+= 10; 
					number1->array[len_num1-i-1] -= 1;
				}
			}
			//if one of the arrays falls off the edge
			if(len_num1-i >= 0 && len_num2-i < 0){
				sub->array[newLength-i] = number1->array[len_num1-i];
			}
			else{
				newVal=number1->array[len_num1-i]-number2->array[len_num2-i];
				sub->array[newLength-i] = newVal;
			}
		}//end of for loop
		/*Check if both arrays have the same length and if the digits in
		 the first index are the same. If both conditions are true then
		 move every digit from our sub array to left 1 and decrease
		 lengthOfInt. */
		if(len_num1 == len_num2 && 
			number1->array[0] == number2->array[0]){
			for(int i = 0; i<newLength; i++){
				sub->array[i] = sub->array[i+1];
			}
			sub->array[newLength-1] = 0;
			sub->lengthOfInt-=1;
		}
		else if(sub->array[0]==0 && len_num1 != len_num2){
			sub->array[0] = sub->array[1];
			sub->array[1] = 0;
			sub->lengthOfInt-=1;
		}
	}//end of outer else
	return sub;
}

//method for multiplication
apint multiply(apint number1, apint number2){
	apint mult = malloc(sizeof(apintObj));
	mult->array = (int *)calloc(100,sizeof(int));
	int len_num1 = number1->lengthOfInt;
	int len_num2 = number2->lengthOfInt;
	int index;
	int multCarryOut = 0;
	int addCarryOut = 0;
	int newLength = mult->lengthOfInt = len_num1+len_num2-1;
	int newVal;
	int temp;

	/*If either one of the values we are multiplying is negative,
	make it positive by multiplying it with its own sign */
	if(number1->array[0]<0 || number2->array[0]<0){
		number1->array[0]*=number1->sign;
		number2->array[0]*=number2->sign;
	}
	for(int i = 1; i <= len_num2; i++){
		for(int j =1; j <= len_num1; j++){
			/*This section of code only runs after the first 
			iteration of the outer loop*/
			if(i > 1){
				index = 1;
				while(index > 0 && j == 1){
					mult->array[newLength-1]+=0;
					newLength--;
					index--;
				}//end of while
				newVal=number1->array[len_num1-j]*number2->array[len_num2-i]+multCarryOut;
				/*if we are multiplying the last value in the array 
				and it is bigger than 9 drop it down into our new
				array*/
				if((j==len_num1) && (i != len_num2) && 
					(number1->array[len_num1-j]*number2->array[len_num2-i]+multCarryOut)>9){
					temp=number1->array[len_num1-j]*number2->array[len_num2-i]+multCarryOut;
					multCarryOut = temp/10;
					temp = temp%10;
					mult->array[newLength-j]=mult->array[newLength-j]+temp+addCarryOut;
					mult->array[newLength-j-1] += multCarryOut;
					addCarryOut = 0;
					//reset the multCarryOut because it was already used
					multCarryOut = 0;
				}
				/*if we have reached the end of both our arrays and
				are multiplying the last values in the array and it
				is bigger than 9 drop it down into our new array*/
				else if((j == len_num1) && (i == len_num2) && 
					(number1->array[len_num1-j]*number2->array[len_num2-i]+multCarryOut)>9){
					temp=number1->array[len_num1-j]*number2->array[len_num2-i]+multCarryOut;
					mult->array[newLength-j]=mult->array[newLength-j]+temp+addCarryOut;
					addCarryOut = 0;
					//reset the multCarryOut because it was already used
					multCarryOut = 0;
				}
				else{
					multCarryOut = newVal/10;
					newVal = newVal%10;;
					/*This section of code runs when the value we
					want to add into our array is greater than 9.*/
					if(mult->array[newLength-j]+newVal+addCarryOut>9){
						if((j==len_num1) && (i==len_num2)){
							temp=mult->array[newLength-j]+newVal+addCarryOut;
							mult->array[newLength-j] = temp;
						}
						/*if we are multiplying the last digit in array
						number1 with array number2 and array number2 still has digits to
						go, drop down the value into our new array*/
						else if((j == len_num1) && (i != len_num2)){
							temp = mult->array[newLength-j]+newVal+addCarryOut;
							mult->array[newLength-j]=temp;
							//reset because we already used it
							addCarryOut = 0;
						}
						else{
							temp=mult->array[newLength-j]+newVal+addCarryOut;
							addCarryOut = temp/10;
							newVal = temp%10;
							mult->array[newLength-j]=newVal;
						}
					}
					else{
						mult->array[newLength-j]=mult->array[newLength-j]+newVal+addCarryOut;
						//reset carry out because none will be produced
						addCarryOut = 0;
					}
				}
			}
			//We only run this section when i = 1
			else{
				/*if we are multiplying the last value in the array
				and it is bigger than 9 drop it down into our new 
				array*/
				if((j == len_num1) && 
					(number1->array[len_num1-j]*number2->array[len_num2-i]+multCarryOut)>9){
					temp=number1->array[len_num1-j]*number2->array[len_num2-i]+multCarryOut;
					multCarryOut = temp/10;
					temp = temp%10;
					mult->array[newLength-j] = temp;
					mult->array[newLength-j-1] = multCarryOut;
					//reset the multCarryOut because it was already used
					multCarryOut = 0;
				}
				else{
					newVal=number1->array[len_num1-j]*number2->array[len_num2-i]+multCarryOut;
					multCarryOut = newVal/10;
					newVal = newVal%10;
					mult->array[newLength-j] = newVal;
				}
			}
		}//end of inner for loop
	}//end of outer for loop

	/* Multiply first element in our new array by negative one if at
	most one of the values we are multiplying is negative. If both
	are are negative, then leave our final value as positive */
	if(number1->sign<0 && number2->sign<0){
		mult->array[0]*=1;
		mult->sign = 1;
	}
	else if(number1->sign < 0){
		mult->array[0]*=number1->sign;
		mult->sign = -1;
	}
	else{
		mult->array[0]*=number2->sign;
		mult->sign = -1;
	}
	return mult;
}