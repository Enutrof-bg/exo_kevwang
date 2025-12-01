#include "bigint2.hpp"


bigint::bigint()
{
	std::stringstream ss;
	ss << 0;
	ss >> str;
}
bigint::bigint(unsigned int n)
{
	std::stringstream ss;
	ss << n;
	ss >> str;
}

bigint::~bigint(){}

bigint::bigint(const bigint &copy)
{
	*this = copy;
}

bigint &bigint::operator=(const bigint &other)
{
	if (this != &other)
	{
		str = other.str;
	}
	return *this;
}

std::string addition(const bigint &a, const bigint &b)
{
	std::string tempa = a.getStr();
	std::string tempb = b.getStr();

	std::string result;
	
	reverse(tempa.begin(), tempa.end());
	reverse(tempb.begin(), tempb.end());

	int s1 = tempa.size();
	int s2 = tempb.size();
	 if (s2 > s1)
	 {
		int diff = s2 - s1;
		while (diff > 0)
		{
			tempa.push_back('0');
			diff--;
		}
	 }
	 else if (s2 < s1)
	 {
		int diff = s1 - s2;
		while (diff > 0)
		{
			tempb.push_back('0');
			diff--;
		}
	 }

	//  std::cout << tempa << std::endl;
	//  std::cout << tempb << std::endl;

	int retenue = 0;
	int value = 0;
	std::string::iterator it = tempa.begin();
	std::string::iterator itb = tempb.begin();
	for (; it != tempa.end(); it++)
	{
		value = *it-48 + *itb-48;
		// std::cout << value << std::endl;
		if (retenue > 0)
		{
			value += retenue;
			retenue = 0;
		}
		if (value > 9)
		{
			value = value % 10;
			retenue = retenue / 10;
		}
		result.push_back(value + 48);
		itb++;
	}
	reverse(result.begin(), result.end());
	return result;
}

bigint bigint::operator+(const bigint &other) const
{
	bigint temp;

	temp.str = addition(*this, other);

	return temp;
}

bigint &bigint::operator+=(const bigint &other)
{
	bigint temp;

	temp.str = addition(*this, other);
	*this = temp;
	return *this;
}

bigint bigint::operator++()
{
	this->str = addition(*this, bigint(1));
	return *this;
}

bigint bigint::operator++(int)
{
	bigint temp(*this);
	this->str = addition(*this, bigint(1));
	return temp;
}


bigint bigint::operator<<(int num)
{
	bigint temp(*this);
	while (num > 0)
	{
		temp.str.push_back('0');
		num--;
	}
	return temp;
}

bigint &bigint::operator<<=(int num)
{
	// bigint temp(*this);
	while (num > 0)
	{
		this->str.push_back('0');
		num--;
	}
	return *this;
}

bigint bigint::operator>>(int num)
{
	bigint temp(*this);
	while (num > 0)
	{
		temp.str.erase(temp.str.size() - 1);
		num--;
	}
	return temp;
}

bigint &bigint::operator>>=(int num)
{
	// bigint temp(*this);
	while (num > 0)
	{
		this->str.erase(str.size() - 1);
		num--;
	}
	return *this;
}


unsigned int bigint::touint(const bigint &other)
{
	std::stringstream ss;
	ss << other.getStr();

	unsigned int num;
	ss >> num;
	return num;
}

bigint &bigint::operator>>=(const bigint &other)
{
	std::stringstream ss(other.getStr());
	unsigned int num;
	ss >> num;
	while (num > 0)
	{
		this->str.erase(str.size() - 1);
		num--;
	}
	return *this;
}

bigint bigint::operator<<(const bigint &other)
{
	bigint temp;
	unsigned int num = touint(other);
	temp = *this << num;
	return temp;
}

bigint &bigint::operator<<=(const bigint &other)
{
	unsigned int num = touint(other);
	*this = *this <<= num;
	return *this;
}

bigint bigint::operator>>(const bigint &other)
{
	bigint temp;
	unsigned int num = touint(other);
	temp = *this >> num;
	return temp;
}



bool bigint::operator<(const bigint &other)
{
	std::string str1 = this->getStr();
	std::string str2 = other.getStr();

	if (str1.size() != str2.size())
		return (str1.size() < str2.size());
	return (str1 < str2);
}

bool bigint::operator>(const bigint &other)
{
	return (!(*this < other));
}

bool bigint::operator==(const bigint &other)
{
	if (this->getStr() == other.getStr())
		return true;
	return false;
}

bool bigint::operator!=(const bigint &other)
{
	return (!(*this == other));
}

bool bigint::operator<=(const bigint &other)
{
	return ((*this<other) || (*this==other));
}

bool bigint::operator>=(const bigint &other)
{
	return (!((*this<other) || (*this==other)));
}

std::string bigint::getStr() const
{
	return str;
}

std::ostream &operator<<(std::ostream &out, const bigint &big)
{
	std::string temp = big.getStr();
	out << temp;
	return out;
}