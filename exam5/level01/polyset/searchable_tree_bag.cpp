#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag()
{}

searchable_tree_bag::~searchable_tree_bag(){}


searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &copy) : tree_bag(copy)
{

}

searchable_tree_bag &searchable_tree_bag::operator=(const searchable_tree_bag &other)
{

	if (this != &other)
	{
		tree_bag::operator=(other);
	}
	return *this;
}

bool searchable_tree_bag::search(node *node, const int value) const
{
	if(node == nullptr)
		return(false);
	if(node->value == value)
		return(true);
	else if(value < node->value)
	{
		return(search(node->l, value));
	}
	else
		return(search(node->r, value));
}

bool searchable_tree_bag::has(int x) const
{
	return search(this->tree, x);
}