// Palindroms.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstring>
#include <list>

void findPalindrome(char*);
bool checkIfNines(char*);
void handleSameNines(char*);
void addOne(char*, unsigned int);
void findPalindromeNumber(char*);

const unsigned int BUFFORSIZE = 1000000;

int main()
{
	unsigned int size;
	std::list<char*> results;
	char *number;
	
	std::cin >> size;

	while (size--) {
		number = new char[BUFFORSIZE];
		std::cin >> number;
		results.push_back(number);
	}
	
	for (auto num : results) {
		findPalindrome(num);
		std::cout << num << std::endl;
		delete[] num;
	}

	return 0;
}

//Put '1' on the beginning and end(one position in right to the previous length). Put zeros in the middle.
void handleSameNines(char *number) { 
	unsigned int length = strlen(number);

	number[length + 1] = number[length];
	number[length] = '1';
	number[0] = '1';
	for (int i = length - 1; i > 0; --i) {
		number[i] = '0';
	}
}

bool checkIfNines(char *number) {
	unsigned int i = 0;

	while (*(number + i) != '\0') {
		if (*(number + i++) != '9') {
			return false;
		}
	}
	
	return true;
}

void addOne(char *number, unsigned int positionToAddOne) {
	++number[positionToAddOne];
	while (number[positionToAddOne] == 58 && positionToAddOne >= 0) {
		number[positionToAddOne] = '0';
		if (positionToAddOne == 0) { //Move all digits 1 position in right, add '1' on beginning.
			for (int i = strlen(number) + 1; i > 0; --i) {
				number[i] = number[i - 1];
			}
			number[0] = '1';
		}
		++number[--positionToAddOne];
	}
}

void findPalindromeNumber(char* number) {
	const unsigned int length = strlen(number);
	const unsigned int centerOfSymmetry = (length + 1) / 2;
	unsigned int digitPostitionFromEnd = length - 1;
	unsigned int digitPostitionFromBeginning = 0;
	
	//Add 1 in order to prevent accept input palindrome as result palindrome.
	addOne(number, digitPostitionFromEnd);
	
	while (digitPostitionFromBeginning < centerOfSymmetry) {
		if (number[digitPostitionFromBeginning] < number[digitPostitionFromEnd]) {
			addOne(number, digitPostitionFromEnd - 1);
		}
		number[digitPostitionFromEnd--] = number[digitPostitionFromBeginning++];
	}
}

void findPalindrome(char* number) {
	if (checkIfNines(number)) {
		handleSameNines(number);
	} else {
		findPalindromeNumber(number);
	}
}
