#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

class bigint
{

private:
	std::string num;

public:
	bigint();
	bigint(unsigned int val);
	~bigint();
	bigint(const bigint &copy);
	bigint &operator=(const bigint &other);

	std::string getNum() const;

	bigint operator+(const bigint &a) const;

	bigint &operator+=(const bigint &a);

	bigint operator++();
	bigint operator++(int);

	bigint operator<<(unsigned int n);
	bigint &operator<<=(unsigned int n);

	bigint operator>>(unsigned int n);
	bigint &operator>>=(unsigned int n);


	bigint &operator>>=(const bigint &other);
	bigint operator>>(const bigint &other);
	bigint &operator<<=(const bigint &other);
	bigint operator<<(const bigint &other);

	bool operator<(const bigint &other);
	bool operator>(const bigint &other);
	bool operator<=(const bigint &other);
	bool operator>=(const bigint &other);
	bool operator==(const bigint &other);
	bool operator!=(const bigint &other);
};

std::ostream &operator<<(std::ostream &out, const bigint &bigint);