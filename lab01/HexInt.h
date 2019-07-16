#ifndef HEXINT_H
#define HEXINT_H

class HexInt
{
public:
	HexInt(const char* str);
	~HexInt();
	char* toString();
	char* toTrimmedString();
	static HexInt* add(HexInt& lhs, HexInt& rhs);
private:
	char* digits;
};

#endif
