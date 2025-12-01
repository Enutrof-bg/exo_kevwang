#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

class bigint
{
private:
	std::string str;
public:
	bigint();
	bigint(unsigned int n);
	~bigint();
	bigint(const bigint &copy);
	bigint &operator=(const bigint &other);

	unsigned int touint(const bigint &other);
	std::string getStr() const;

	bigint operator+(const bigint &other) const;
	bigint &operator+=(const bigint &other);

	bigint operator++();
	bigint operator++(int);

	bigint operator<<(int num);
	bigint &operator<<=(int num);
	bigint operator>>(int num);
	bigint &operator>>=(int num);

	bigint operator<<(const bigint &other);
	bigint &operator<<=(const bigint &other);

	bigint operator>>(const bigint &other);
	bigint &operator>>=(const bigint &other);

	bool operator<(const bigint &other);
	bool operator>(const bigint &other);
	bool operator==(const bigint &other);
	bool operator!=(const bigint &other);
	bool operator<=(const bigint &other);
	bool operator>=(const bigint &other);
};

std::ostream &operator<<(std::ostream &out, const bigint &big);