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
	// const char* it = temp1.data();
	// const char* it2 = temp2.data();

	// std::cout << "test:" << it << it2 << std::endl;
	// int i = 0;
	// while (it[i] && it[i])
	// {
	// 	value = it[i] + it2[i];
	// 	std::cout <<"value" << value << std::endl;
	// 	i++;
	// }
	for (; it != temp1.end(); it++)
	{
		// std::cout << "caca:" << *it << " | "<< *it2<< std::endl;
		value = (*it - 48) + (*it2 - 48);
		if (retenue > 0)
			value += retenue;
		// std::cout << "value:" << value << std::endl;
		if (value > 10)
		{
			retenue = value / 10;
			value = value % 10;
		}
		// std::cout << "value2:" << value << std::endl;

		newstr += (value + 48);
		// itnew++;
		it2++;
	}

	for (; it2 != temp2.end() ; it2++)
	{
		value = (*it2 -48) + retenue;

		newstr += value + 48;
	}
	// std::cout << "newstr: "<<newstr << std::endl;

	// std::string test("caca");
	return (newstr);
}

bigint bigint::operator+(const bigint &a) const
{
	bigint temp;
	temp.num = addition(*this, a);

	return temp;
}

std::ostream &operator<<(std::ostream &out, const bigint &bigint)
{
	std::string temp = bigint.getNum();
	reverse(temp.begin(), temp.end());
	out << temp;

	return out;
}