#include "vect22.hpp"

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
	*this = copy;
}

vect2 &vect2::operator=(const vect2 &other)
{
	if (this != &other){
		x = other.x;
		y = other.y;
	}
	return *this;
}

int &vect2::operator[](int index){
	if (index == 0)
		return x;
	return y;
}

const int vect2::operator[](int index) const
{
	if (index == 0)
		return x;
	return y;
}

vect2 vect2::operator++()
{
	x++;
	y++;
	return *this;
}

vect2 vect2::operator++(int)
{
	vect2 temp(*this);
	x++;
	y++;
	return temp;
}

vect2 vect2::operator--()
{
	x--;
	y--;
	return *this;
}

vect2 vect2::operator--(int)
{
	vect2 temp(*this);
	x--;
	y--;
	return temp;
}

// vect2 operator+(const vect2 &other)
// {
// 	vect2 temp(this);
// }

vect2 &vect2::operator+=(const vect2 &other){
	// vect2 test(*this);
	x = x + other.x;
	y = y + other.y;
	return *this;
}

vect2 &vect2::operator-=(const vect2 &other){
	// vect2 test(*this);
	x = x - other.x;
	y = y - other.y;
	return *this;
}

vect2 vect2::operator*(int num) const
{
	vect2 temp(*this);
	temp.x = temp.x * num;
	temp.y = temp.y * num;
	return temp;
}

vect2 vect2::operator+(const vect2 &other) const
{
	vect2 temp(*this);
	temp.x = temp.x + other.x;
	temp.y = temp.y + other.y;
	return temp;
}


vect2 vect2::operator-(const vect2 &other) const
{
	vect2 temp(*this);
	temp.x = temp.x - other.x;
	temp.y = temp.y - other.y;
	return temp;
}


vect2 &vect2::operator*=(int num)
{
	x = x * num;
	y = y * num;
	return *this;
}

vect2 vect2::operator-()
{
	vect2 temp(*this);
	temp.x = -temp.x;
	temp.y = -temp.y;
	return temp;
}


bool vect2::operator==(const vect2 &other)
{
	if (x == other.x && y == other.y)
		return true;
	return false;
}

bool vect2::operator!=(const vect2 &other)
{
	if (x == other.x && y == other.y)
		return false;
	return true;
}

std::ostream &operator<<(std::ostream &out, const vect2 &vec)
{
	out << "{" << vec[0] << "," << vec[1] << "}"<<std::endl;
	return out;
}


vect2 operator*(int num, const vect2 &other)
{
	vect2 temp(other);
	temp *= num;
	return temp;

}