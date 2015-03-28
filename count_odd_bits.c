/*
 ============================================================================
 Name        : count_off_bits.c
 Author      : Roman Chikunov
 Version     :
 Copyright   : 
 Description : This programs counts the odd bits only if they are set ('1')
 			   and than it prints how many odd set bits there are
 ============================================================================
 */



#include<stdio.h>

#define MASK 0x01

int count_odd_bits(int unsigned long number){
	int counter = 0;
	number >>= 1;

	while(number){
		
		if ((number&MASK))
			counter++;
		number = number >> 2;
	}	
	return counter;
}

int main(){

	int unsigned long num;
	printf("Please enter an unsigned number: \n");
	scanf("%lu",&num);
	printf("Number of odd bits that are '1' in the number is: %d\n", count_odd_bits(num));
	
	return 0;
}
