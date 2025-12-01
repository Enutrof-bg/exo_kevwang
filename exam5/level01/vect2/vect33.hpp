#pragma once

#include <string>
#include <iostream>

class vect2
{
private:
	int x;
	int y;

public:
	vect2();
	vect2(int a, int b);
	~vect2();
	vect2(const vect2 &copy);
	vect2 &operator=(const vect2 &other);

	int operator[](int index);
	int operator[](int index) const;

	vect2 &operator++();
	vect2 operator++(int);
	vect2 &operator--();
	vect2 operator--(int);

	vect2 &operator+=(const vect2 &other);
	vect2 &operator-=(const vect2 &other);
	vect2 &operator*=(const vect2 &other);

	vect2 operator*(int num) const;
	vect2 operator+(const vect2 &other) const;
	vect2 operator-(const vect2 &other) const;
	vect2 operator-(int num) const;

	vect2 &operator*=(int num);

	vect2 operator-();
};

std::ostream &operator<<(std::ostream &out, const vect2 &vec);

vect2 operator*(int num, const vect2 &other);