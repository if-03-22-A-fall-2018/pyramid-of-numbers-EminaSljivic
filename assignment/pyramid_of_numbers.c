/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: 2AHIF
 * ---------------------------------------------------------
 * Exercise Number: 05
 * Title:			Pyramid of Numbers
 * Author:			Emina SLJIVIC
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>

/// The maximum number of digits allowed in a big int.
#define MAX_DIGITS 80

/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt {
	/** number of digits of the big int. */
	int digits_count;

	/** array of digits of big int. */
	unsigned int the_int[MAX_DIGITS];
};

/** strtobig_int converts a string into a BigInt. If strtobig_int runs
*** against a character not between '0' and '9' the conversion stops
*** at this point.
*** @param *str The string to be converted.
*** @param len Number of characters in string to be converted.
*** @param *big_int The converted string now as BigInt.
* @return The number of characters converted.
*/
int strtobig_int(const char *str, int len, struct BigInt *big_int);

/** print_big_int() prints a BigInt.
*** @param *big_int The BigInt to be printed.
*/
void print_big_int(const struct BigInt *big_int);

/** multiply() multiplies a BigInt by an int.
*** @param big_int The BigInt to be multiplied.
*** @param factor The int value which is multiplied by BigInt.
*** @param *big_result The result of the multiplication.
*/
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result);

/** divide() multiplies a BigInt by an int.
*** @param big_int The BigInt to be divided.
*** @param divisor The int value by which we want to devide big_int.
*** @param *big_result The result of the division.
*/
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result);

/** copy_big_int() copies a BigInt to another BigInt.
*** @param from The source where we want to copy from.
*** @param *to The target where we want to copy to.
*/
void copy_big_int(const struct BigInt *from, struct BigInt *to);

/**
*** main() reads the base number from which the pyramid has to be calculated
*** into an array of char. The max. length of this number is MAX_DIGITS.
*** The number is checked to contain only digits. If not the program exits.
*** Then inputted number is converted into a big int by calling the
*** function strtobig_int().
*** After the conversion the tower is calculated by calling the functions
*** multiply(), print_big_int(), and copy_big_int() consecutively from 2 to
*** 9 and then again with divide() instead of multiply() from 2 to 9.
***
*/
int main(int argc, char *argv[])
{
	char input[MAX_DIGITS];
	struct BigInt big_int;

	printf("Please enter a number: ");
	scanf("%s",input);

	big_int.digits_count=strtobig_int(input,strlen(input),&big_int);

	if(big_int.digits_count==strlen(input))
	{
		for (int i = 2; i <= 9; i++) {
			print_big_int(&big_int);
			multiply(&big_int,i,&big_int);
			printf(" * %d = ",i);
			print_big_int(&big_int);
			printf("\n");
		}

		for (int i = 2; i <= 9; i++) {
			print_big_int(&big_int);
			divide(&big_int,i,&big_int);
			printf(" / %d = ",i);
			print_big_int(&big_int);
			printf("\n");
		}
	}
	return 0;
}

int strtobig_int(const char *str, int len, struct BigInt *big_int)
{
	int count=0;

	for (int i = len-1; i >=0 ; i--)
	{
		if(str[i]>='0'&&str[i]<='9')
		{
			big_int->the_int[count]=str[i]-'0';
			count++;
		}
		else
		{
			return count;
		}
	}
	return count;
}

void print_big_int(const struct BigInt *big_int)
{
	for (int i = big_int->digits_count-1; i >= 0; i--) {
		printf("%d",big_int->the_int[i]);
	}
}

void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result)
{
	int overflow=0;
	int num;
	for (int i = 0; i <big_int->digits_count; i++) {
		num=big_int->the_int[i]*factor + overflow;
		big_result->the_int[i]=num%10;

		if(num>=10)
		{
			overflow=num/10;
		}
		else{
			overflow=0;
		}
		if(overflow!=0 && i==big_int->digits_count-1)
		{
			big_result->digits_count++;
		}
	}
}

void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result)
{
	int num = 0;
	int remainder = 0;
	int counter = 0;

	for (int i = big_int->digits_count-1; i >=0; i--)
	{
		num = big_int->the_int[i] + remainder*10 ;
		big_result->the_int[i] = num/divisor;
		remainder = num %divisor;
		counter += big_result->the_int[i];

		if (counter == 0)
		{
			big_result->digits_count--;
		}
	}
}
