#pragma once


#include <iostream>
#include <string>

class vect2
{
private:
	int x1;
	int x2;
public:
	vect2();
	vect2(int x1, int x2);
	~vect2();
	vect2(const vect2 &copy);
	vect2 &operator=(const vect2 &other);

	int getx1() const;
	int getx2() const;

	int &operator[](int index);
	const int &operator[](int index) const;

	vect2 operator++(void);
	vect2 operator++(int);
	vect2 operator--(void);
	vect2 operator--(int);

	vect2 &operator+=(const vect2 &other);
	vect2 &operator*=(int num);
	vect2 &operator-=(const vect2 &other);

	vect2 operator+(const vect2 &other) const;
	vect2 operator*(const vect2 &other) const;
	vect2 operator-(const vect2 &other) const;
	vect2 &operator/(const vect2 &other);

	vect2 operator*(int m) const;

	vect2 operator-() const;
	
	bool operator==(const vect2 &other) const;
	bool operator!=(const vect2 &other) const;
};

std::ostream &operator<<(std::ostream &out, const vect2 &vect);

vect2 operator*(int num, const vect2 &vect);