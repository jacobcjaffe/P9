#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

int findMin(std::string str);

int main(int argc, char * argv[]) {

	std::ofstream outstream;
	std::ifstream instream;
    if (argc != 3) {
		std::cout << "ERROR: Input and output files must be specified." << std::endl;
        return -1;
    }
    instream.open(argv[1]);
	outstream.open(argv[2]);
	
	std::string firstStr;
	std::string secondStr;
	instream >> firstStr;
	instream >> secondStr;
	unsigned long long min1, min2, base1, base2;
	while(!instream.eof()) {	
		// find the smallest base possible, impossible to convert to smaller bases
		min1 = findMin(firstStr);
		min2 = findMin(secondStr);
		base1 = 0;
		base2 = 0;
		for(int i = 2; i <= 36; i++) {
			if(i < min1) continue;
			for (int j = 2; j <=36; j++) {
				if(j < min2) continue;
				// check if their values are same in the two bases
				if(std::stoull(firstStr, nullptr, i) == std::stoull(secondStr, nullptr, j)) {
					base1 = i;
					base2 = j;
					goto stop;
				}
			}
		}
	stop:
		if(base1 != 0) {
			outstream << firstStr << " (base " << base1 << ") = ";
			outstream << secondStr << " (base " << base2 << ")" << std::endl;
		}
		else {
			outstream << firstStr << " is not equal to " << secondStr;
			outstream << " in any base 2..36" << std::endl;
		}
		instream >> firstStr >> secondStr;
	}
	return 0;
}

int findMin(std::string str) {
	int min = 0;
	int dummy;	
	for(int i = 0; i < str.length(); i++) {
		if(str[i] <= 90 && str[i] >= 65) {
			dummy = str[i] - 55;
		}
		else {
			dummy = str[i] - 48;
		}
		// keep track of minimum base, which is 1 more than the max digit
		if(dummy+1 > min) {
			min = dummy+1;
		}
	}
	return min;
}
