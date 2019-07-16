#include "HexInt.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		cout << "Error: Not enough arguments!" << endl;
		return 1;
	}

	ifstream input(argv[1]);
	ofstream output(argv[2]);

	while(!input.eof())
	{
		string line;
		//read input
		getline(input, line);
		//parse
		string firstNum;
		string secondNum;

		int splitter = line.find('+'); //where to split into the two numbers
		
		firstNum = line.substr(0, splitter);
		secondNum = line.substr(splitter+1);

		HexInt oneHex = HexInt(firstNum.c_str());
		HexInt twoHex = HexInt(secondNum.c_str());

		//compute
		HexInt* sum = HexInt::add(oneHex, twoHex); // use class name so compiler knows where to find it
		//output
		output << sum->toTrimmedString() << endl;
	}

	return 0;
}