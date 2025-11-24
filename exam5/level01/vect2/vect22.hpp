#pragma once

#include <iostream>
#include <string>

class vect2
{
private:
	int x;
	int y;
public:
	vect2();
	vect2(int a, int b);
	~vect2();
	vect2 &operator=(const vect2 &other);
	vect2(const vect2 &vect2);

	int &operator[](int index);
	const int operator[](int index) const;

	vect2 operator++();
	vect2 operator++(int);

	vect2 operator--();
	vect2 operator--(int);

	vect2 operator+(const vect2 &other) const;
	vect2 operator-(const vect2 &other) const;

	vect2 &operator+=(const vect2 &other);
	vect2 &operator-=(const vect2 &other);
	vect2 &operator*=(int num);

	vect2 operator*(int num) const;

	vect2 operator-();
	// vect2 operator+(const vect2 &other) const;
	bool operator==(const vect2 &other);
	bool operator!=(const vect2 &other);
};


std::ostream &operator<<(std::ostream &out, const vect2 &vec);

vect2 operator*(int num, const vect2 &other);