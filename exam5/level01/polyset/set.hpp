#pragma once

#include "searchable_bag.hpp"

class set
{
private:
	searchable_bag &bag;

public:
	set() = delete;
	set(searchable_bag &s_bag);
	~set();
	set(const set &copy) = delete;
	set &operator=(const set &other) = delete;

	void insert (int x);
	void insert (int *data, int x);
	void print() const;
	void clear();

	bool has(int x);

	searchable_bag &get_bag();
};