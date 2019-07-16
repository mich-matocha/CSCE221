#include "HexInt.h"
#include <iostream>
#include <cstring>

using namespace std;

HexInt::HexInt(const char* str) //this works now!! good job mich
{
	digits = new char[21];
	for(int i = 0; i < 21; ++i) //init digits with zeros
	{
		digits[i] = '0';
	}
	int len = strlen(str);
	int strCounter = 0;

	//now adding the str digits where they belong, leaving
	//space for the newline character
	for(int j = 20 - len; j < 21; ++j)
	{
		digits[j] = str[strCounter];
		++strCounter;
	}
}

HexInt::~HexInt()
{}

char* HexInt::toString() //also needs to be fixed
{
	char* ret = new char[21];
	for(int i = 0; i < 21; i++)
	{
		ret[i] = digits[i];
	}
	return ret;
}

char* HexInt::toTrimmedString() //this needs to be fixed
{
	bool numStart = false;
	char* copy = this->toString();
	char* ret = new char[21];

	int retCounter = 0;
	for(int i = 0; i < 21; ++i)
	{
		if(copy[i] != '0')
		{
			numStart = true;
			ret[retCounter] = copy[i];
			++retCounter;
		}
		else if(numStart)
		{
			numStart = true;
			ret[retCounter] = copy[i];
			++retCounter;
		}
	}
	return ret;
}

HexInt* HexInt::add(HexInt& lhs, HexInt& rhs) //don't put static in the function definition!
{
	char* result = new char[21];
	char* lh = lhs.toString();
	char* rh = rhs.toString();
	int digitL;
	int digitR;
	int carry = 0;
	int sum = 0;
	char charSum;

	for(int i = 19; i >= 0; --i)
	{
		if(lh[i] <= '9') //converting hex to decimal
		{
			digitL = lh[i] - '0';
		}
		else
		{
			digitL = lh[i] - 'A' + 10;
		}
		if(rh[i] <= '9')
		{
			digitR = rh[i] - '0';
		}
		else
		{
			digitR = rh[i] - 'A' + 10;
		}

		sum = digitL + digitR + carry;

		carry = sum / 16;
		sum %= 16;

		if(sum <= 9)
		{
			charSum = sum + '0';
		}
		else
		{
			charSum = sum + 'A' - 10;
		}

		result[i] = charSum; //error here

	}

	HexInt* ret = new HexInt(result);
	return ret;
}
