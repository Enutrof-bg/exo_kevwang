#include "vect33.hpp"

vect2::vect2()
{
	x = 0;
	y = 0;
}

vect2::vect2(int a, int b)
{
	x = a;
	y = b;
}

vect2::~vect2()
{
	
}

vect2::vect2(const vect2 &copy)
{
	// x = copy.x;
	// y = copy.y;
	*this = copy;
}

vect2 &vect2::operator=(const vect2 &other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
	}
	return *this;
}

int vect2::operator[](int index)
{
	if (index == 0)
		return x;
	return y;
}

int vect2::operator[](int index) const
{
	if (index == 0)
		return x;
	return y;
}

vect2 &vect2::operator++()
{
	x++;
	y++;
	return *this;
}

vect2 vect2::operator++(int)
{
	vect2 temp = *this;
	x++;
	y++;
	return temp;
}

vect2 &vect2::operator--()
{
	x--;
	y--;
	return *this;
}

vect2 vect2::operator--(int)
{
	vect2 temp = *this;
	x--;
	y--;
	return temp;
}

vect2 &vect2::operator+=(const vect2 &other)
{
	x += other.x;
	y += other.y;
	return *this;
}

vect2 &vect2::operator-=(const vect2 &other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

vect2 &vect2::operator*=(const vect2 &other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

vect2 vect2::operator*(int num) const
{
	vect2 temp = *this;
	temp.x *= num;
	temp.y *= num;
	return temp;
}

vect2 vect2::operator+(const vect2 &other) const
{
	vect2 temp = *this;
	temp.x += other.x;
	temp.y += other.y;
	return temp;
}

vect2 vect2::operator-(const vect2 &other) const
{
	vect2 temp = *this;
	temp.x -= other.x;
	temp.y -= other.y;
	return temp;
}

vect2 vect2::operator-()
{
	vect2 temp(*this);
	temp.x = -temp.x;
	temp.y = -temp.y;
	return temp;
}

vect2 &vect2::operator*=(int num)
{
	x *= num;
	y *= num;
	return *this;
}

std::ostream &operator<<(std::ostream &out, const vect2 &vec)
{
	out << "{" << vec[0] << ", "<< vec [1]<<"}";
	return out;
}

vect2 operator*(int num, const vect2 &other)
{
	vect2 temp(other);
	temp *= num;
	return temp;
}