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
};

std::ostream &operator<<(std::ostream &out, const bigint &bigint);