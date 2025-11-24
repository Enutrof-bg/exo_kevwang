#include "bigint.hpp"

bigint::bigint()
{
	std::stringstream ss;
	ss << 0;

	ss >> num;

}


bigint::bigint(unsigned int val)
{
	std::stringstream ss;
	ss << val;
	// num = ss;
	ss >> num;
	reverse(num.begin(), num.end());

}

bigint::~bigint(){}

bigint::bigint(const bigint &copy)
{
	num = copy.num;
}

bigint &bigint::operator=(const bigint &other)
{
	if (this != &other)
	{
		num = other.num;
	}

	return *this;
}

std::string bigint::getNum() const
{
	return num;
}


std::string addition(const bigint &str1, const bigint &str2)
{
	// std::cout << str1.getNum() << std::endl; 
	std::string temp1(str1.getNum());
	std::string temp2(str2.getNum());
	
	std::string newstr;
	// char *new
	int retenue = 0;
	int index = 0;
	int value = 0;
	
	std::string::iterator it = temp1.begin();
	std::string::iterator it2 = temp2.begin();

	std::string::iterator itnew = newstr.begin();
	int len1 = temp1.size();
	int len2 = temp2.size();

	int diff;
	if (len1 > len2)
	{
		diff = len1 - len2;
		while (diff > 0)
		{
			temp2.push_back('0');
			diff--;
		}
	}
	else if (len1 < len2)
	{
		diff = len2- len1;
		while (diff > 0)
		{
			temp1.push_back('0');
			diff--;
		}
	}
	// std::cout << "temp1:" << temp1;
	// std::cout << " temp2:"<<temp2 << std::endl;
	for (; it != temp1.end(); it++)
	{
		value = (*it - 48) + (*it2 - 48);
		if (retenue > 0)
			value += retenue;
		if (value > 10)
		{
			retenue = value / 10;
			value = value % 10;
		}
		newstr += (value + 48);
		it2++;
	}
	return (newstr);
}

bigint bigint::operator+(const bigint &a) const
{
	bigint temp;
	temp.num = addition(*this, a);

	return temp;
}

bigint &bigint::operator+=(const bigint &a)
{
// 	bigint temp = *this;
// 	(*this).num = addition(*this,a);
	(*this) = (*this) + a;
	return *this;
}

bigint bigint::operator++()
{
	bigint temp(1);
	(*this) = (*this) + temp;
	return (*this);
}

bigint bigint::operator++(int)
{
	bigint test = *this;
	bigint temp(1);
	(*this) = (*this) + temp;
	return (test);
}

bigint bigint::operator<<(unsigned int n)
{
	bigint temp(*this);
	reverse(temp.num.begin(), temp.num.end());
	while (n > 0)
	{
		temp.num.push_back('0');
		n--;
	}
	reverse(temp.num.begin(), temp.num.end());
	return temp;
}

bigint &bigint::operator<<=(unsigned int n)
{
	reverse(num.begin(), num.end());
	while (n > 0)
	{
		num.push_back('0');
		n--;
	}
	reverse(num.begin(), num.end());
	return *this;
}

bigint bigint::operator>>(unsigned int n)
{
	bigint temp(*this);

	reverse(temp.num.begin(), temp.num.end());
	while (n > 0)
	{
		if (!temp.num.empty())
		{
			temp.num.pop_back();
		}

		n--;
	}

	reverse(temp.num.begin(), temp.num.end());
	return temp;
}

bigint &bigint::operator>>=(unsigned int n)
{
	reverse(num.begin(), num.end());
	while (n > 0)
	{
		if (!num.empty())
		{
			num.pop_back();
		}

		n--;
	}

	reverse(num.begin(), num.end());
	return *this;
}

unsigned int touint(std::string str)
{
	unsigned int res;
	std::stringstream ss(str);
	ss >> res;

	return res;
}
bigint bigint::operator<<(const bigint &other)
{
	bigint temp(*this);
	unsigned int n = touint(other.num);
	// std::cout << "n?" << n << std::endl;
	reverse(temp.num.begin(), temp.num.end());
	while (n > 0)
	{
		if (!temp.num.empty())
		{
			temp.num.push_back('0');
		}

		n--;
	}
	if (temp.num.empty())
		temp.num.push_back('0');
	reverse(temp.num.begin(), temp.num.end());
	return temp;
}

bigint &bigint::operator<<=(const bigint &other)
{
	unsigned int n = touint(other.num);
	// std::cout << "n?" << n << std::endl;
	reverse(num.begin(), num.end());
	while (n > 0)
	{
		if (!num.empty())
		{
			num.push_back('0');
		}

		n--;
	}
	if (num.empty())
		num.push_back('0');
	reverse(num.begin(), num.end());
	return *this;
}

bigint bigint::operator>>(const bigint &other)
{
	bigint temp(*this);
	unsigned int n = touint(other.num);
	// std::cout << "n?" << n << std::endl;
	reverse(temp.num.begin(), temp.num.end());
	while (n > 0)
	{
		if (!temp.num.empty())
		{
			temp.num.pop_back();
		}

		n--;
	}
	if (temp.num.empty())
		temp.num.push_back('0');
	reverse(temp.num.begin(), temp.num.end());
	return temp;
}

bigint &bigint::operator>>=(const bigint &other)
{
	unsigned int n = touint(other.num);
	// std::cout << "n?" << n << std::endl;
	reverse(num.begin(), num.end());
	while (n > 0)
	{
		if (!num.empty())
		{
			num.pop_back();
		}

		n--;
	}
	if (num.empty())
		num.push_back('0');
	reverse(num.begin(), num.end());
	return *this;
}

bool bigint::operator<(const bigint &other)
{
	if (num.size() < other.num.size())
		return true;
	if (num < other.num)
		return true;
	return false;
}

bool bigint::operator>(const bigint &other)
{
	if (num.size() > other.num.size())
		return true;
	if (num > other.num)
		return true;
	return false;
}

bool bigint::operator>=(const bigint &other)
{
	if (num.size() > other.num.size())
		return true;
	if (num > other.num || num == other.num)
		return true;
	return false;
}

bool bigint::operator<=(const bigint &other)
{
	if (num.size() < other.num.size())
		return true;
	if (num < other.num || num == other.num)
		return true;
	return false;
}

bool bigint::operator==(const bigint &other)
{
	if (num == other.num)
		return true;
	return false;
}

bool bigint::operator!=(const bigint &other)
{
	if (num != other.num)
		return true;
	return false;
}


std::ostream &operator<<(std::ostream &out, const bigint &bigint)
{
	std::string temp = bigint.getNum();
	reverse(temp.begin(), temp.end());
	out << temp;

	return out;
}