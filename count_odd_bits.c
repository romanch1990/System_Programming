#include<stdio.h>

#define MASK 0x01



int count_odd_bits(unsigned int number){
	int counter = 0;
	

	while(number){
		
		if ((number&MASK))
			counter++;
		number = number >> 1;
	}	
	return counter;
}

int main(){

	int num;
	printf("Please enter an unsigned number: \n");
	scanf("%u",&num);
	printf("Number of set bits in the number is: %u\n", count_odd_bits(num));
	
	return 0;
}