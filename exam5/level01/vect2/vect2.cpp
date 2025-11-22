#include "vect2.hpp"

vect2::vect2(): x1(0), x2(0)
{

}

vect2::vect2(int x1, int x2): x1(x1) , x2(x2)
{

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
	x1 = other.x1;
	x2 = other.x2;
	return *this;
}

int &vect2::operator[](int index)
{
	if (index == 0)
		return (x1);
	if (index == 1)
		return (x2);
	return (x1);
}

const int vect2::operator[](int index) const
{
	if (index == 0)
		return (x1);
	if (index == 1)
		return (x2);
	return (x1);
}

vect2 vect2::operator++(void)
{
	this->x1++;
	this->x2++;
	return *this;
}

vect2 vect2::operator++(int)
{
	vect2 temp = *this;
	++x1;
	++x2;
	return temp;
}

vect2 vect2::operator--(void)
{
	this->x1--;
	this->x2--;
	return *this;
}

vect2 vect2::operator--(int)
{
	vect2 temp = *this;
	--x1;
 	--x2;
	return temp;
}

vect2 &vect2::operator+=(const vect2 &other)
{
	x1 = x1 + other.x1;
	x2 = x2 + other.x2;
	return *this;
}

vect2 &vect2::operator*=(int num)
{
	x1 = x1 * num;
	x2 = x2 * num;
	return *this;
}

vect2 &vect2::operator-=(const vect2 &other)
{
	x1 = x1 - other.x1;
	x2 = x2 - other.x2;
	return *this;
}

vect2 vect2::operator+(const vect2 &other) const
{
	vect2 temp = *this;
	temp.x1 = temp.x1 + other.x1;
	temp.x2 = temp.x2 + other.x2;
	return temp;
}

vect2 vect2::operator*(const vect2 &other) const
{
	vect2 temp = *this;
	temp.x1 = temp.x1 * other.x1;
	temp.x2 = temp.x2 * other.x2;
	return temp;

	// return (vect2(other2));
}

vect2 vect2::operator-(const vect2 &other) const
{
	vect2 temp = *this;
	temp.x1 = temp.x1 - other.x1;
	temp.x2 = temp.x2 - other.x2;
	return temp;
}

vect2 &vect2::operator/(const vect2 &other)
{
	x1 = x1 / other.x1;
	x2 = x2 / other.x2;
	return *this;
}

vect2 vect2::operator*(int m) const
{
	vect2 temp = *this;
	temp.x1 = temp.x1 * m;
	temp.x2 = temp.x2 * m;
	return temp;	
}

bool vect2::operator==(const vect2 &other) const
{
	if (x1 == other.x1 && x2 == other.x2)
		return true;
	return false;
}

bool vect2::operator!=(const vect2 &other) const
{
	if (x1 != other.x1 || x2 != other.x2)
		return true;
	return false;
}

vect2 vect2::operator-() const
{
	vect2 temp = *this;
	temp.x1 = -x1;
	temp.x2 = -x2;
	return (temp);
}

int vect2::getx1() const
{
	return x1;
}

int vect2::getx2() const
{
	return x2;
}

std::ostream &operator<<(std::ostream &out, const vect2 &vect)
{
	out << "{" << vect.getx1() << ", " << vect.getx2() << "}" << std::endl;
	return out;
}

vect2 operator*(int num, const vect2 &vect)
{
	vect2 temp(vect);
	temp *= num;
	return temp;
}