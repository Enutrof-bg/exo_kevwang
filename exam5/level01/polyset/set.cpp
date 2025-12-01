#include "set.hpp"

// set::set(){}

set::set(searchable_bag &s_bag): bag(s_bag)
{

}

set::~set(){}

// set::set(const set &copy){}

// set &set::operator=(const set &other){}

void set::insert(int x)
{
	bag.insert(x);
}

void set::insert(int *data, int x)
{
	bag.insert(data, x);
}

void set::print() const
{
	bag.print();
}

void set::clear()
{
	bag.clear();
}

bool set::has(int x)
{
	return (bag.has(x));
}

searchable_bag &set::get_bag()
{
	return bag;
}