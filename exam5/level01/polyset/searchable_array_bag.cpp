#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag()
{}

searchable_array_bag::~searchable_array_bag(){}

searchable_array_bag::searchable_array_bag(const searchable_array_bag &copy) : array_bag(copy)
{
	// if (this != &other)
	// {
	// 	array_bag::operator=(source);
	// }
	// return *this;
}

searchable_array_bag &searchable_array_bag::operator=(const searchable_array_bag &other)
{

	if (this != &other)
	{
		array_bag::operator=(other);
	}
	return *this;
}

bool searchable_array_bag::has(int x) const
{
	for (int i = 0; i < size; i++)
	{
		if (data[i] == x) 
			return true;
	}
	return false;
}