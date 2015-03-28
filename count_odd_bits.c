#include<stdio.h>

#define MASK 0x01

int count_odd_bits(long unsigned int number){
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

	long unsigned int num;
	printf("Please enter an unsigned number: \n");
	scanf("%lu",&num);
	printf("Number of set bits in the number is: %lu\n", count_odd_bits(num));
	
	return 0;
}
