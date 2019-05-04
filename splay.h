#ifndef SPLAY_TREE
#define SPLAY_TREE
#include <iostream>
#include <utility>
#include <functional>
using namespace std;

template<typename value, typename comparator = 	less<value> >
class splay_tree
{
public:
	//Constructor
//	splay_tree();

	//Default constructor when given conparator
	splay_tree(comparator comp = comparator()); //DONE

	//Copy Constructor
	splay_tree(const splay_tree& rhs);	//DONE
	
	//Copy Assignment
	splay_tree& operator=(const splay_tree& rhs);	//DONE
	
	//Move Constructor
	splay_tree(splay_tree&& rhs);	//DONE
	
	//Move Assignment
	splay_tree& operator=(splay_tree&& rhs);	//DONE
	
	//Destructor
	~splay_tree();	//DONE

	//Iterator Class
	class Iterator;
	
	//Returns iterator to first element of set
	Iterator begin() const;	//DONE

	//Returns iterator to last element of set
	Iterator end();		//DONE

	//Inserts element and returns iterator to that element
	pair<Iterator, bool> insert(const value& val);

	//Not sure whether to erase given a value or given an iterator
	pair<Iterator, bool> erase(const value& val) const;

	//Finds value and returns iterator to it
	pair<Iterator, bool> find(const value& val) const;
	
	//Checks whether set is empty
	bool empty() const;	//DONE

private:
	struct node
	{
		value node_value_;
		node* left_child_;
		node* right_child_;
		node* parent_;

		node(const value& val): node_value_(val) {} //Is this allowed? Do we need to malloc?
	};

	node* head, *tail;
	node* root;
	
	comparator comp;
	size_t size;
	
	// node* insert_node( node* root, node* parent_node, const value& val);
 node* insert_node(node* node_, node* parent_node_, const value& val)
{
	if (node_ == nullptr)
	{ 
		node *new_node_ = new splay_tree<value, comparator>::node(val);
		new_node_->parent_ = parent_node_;
		return new_node_; 
	}
	if (val < node_->node_value_) 
		node_->left_child_  = insert_node(node_->left_child_, node_, val); 
	else if (val > node_->node_value_) 
		node_->right_child_ = insert_node(node_->right_child_, node_ , val);    
	//this case shouldnt happen
	return node_; 
}

	void rotate_up(node* node_);

	void splay(node* n) const;
	
	node* clone_tree(node * clone_from, node * parent);
	
	void destroy_tree(node * parent);

	pair<node*, node*> find_node(const value& val) const;
		
};

//Comparison Operators

template <typename value, typename comparator>
bool operator<(const splay_tree<value, comparator>& lhs, const splay_tree<value, comparator>& rhs);

template <typename value, typename comparator>
bool operator<=(const splay_tree<value, comparator>& lhs, const splay_tree<value, comparator>& rhs);

template <typename value, typename comparator>
bool operator==(const splay_tree<value, comparator>& lhs, const splay_tree<value, comparator>& rhs);

template <typename value, typename comparator>
bool operator!=(const splay_tree<value, comparator>& lhs, const splay_tree<value, comparator>& rhs);

template <typename value, typename comparator>
bool operator>=(const splay_tree<value, comparator>& lhs, const splay_tree<value, comparator>& rhs);

template <typename value, typename comparator>
bool operator>(const splay_tree<value, comparator>& lhs, const splay_tree<value, comparator>& rhs);


//Implementation

//Default constructor when given conparator
template<typename value, typename comparator>
splay_tree<value, comparator>::splay_tree(comparator comp) : comp(comp) 
{
	root = head = tail = nullptr;
	size = 0;
}

//Copy Constructor
template<typename value, typename comparator>
splay_tree<value, comparator>::splay_tree(const splay_tree& rhs) 
{
	size = rhs.size;
	comp = rhs.comp;

	root = clone_tree(rhs.root, nullptr);
	
	tail = head = root;
	if(head != nullptr) {
		while(head->left_child_)head = head->left_child_;
		while(tail->right_child_)tail = tail->right_child_;
	}
}

//Copy Assignment
template<typename value, typename comparator>
splay_tree<value, comparator>& 
	splay_tree<value, comparator>::operator=(const splay_tree& rhs) 
{
	destroy_tree(root);
	
	size = rhs.size;
	comp = rhs.comp;

	root = clone_tree(rhs.root, nullptr);
	tail = head = root;
	if(head != nullptr) {
		while(head->left_child_)	
			head = head->left_child_;
		while(tail->right_child_)	
			tail = tail->right_child_;
	}
}

//Move Constructor
template<typename value, typename comparator>
splay_tree<value, comparator>::splay_tree(splay_tree&& rhs)
: size(rhs.size), comp(rhs.comp), root(rhs.root), tail(rhs.tail), head(rhs.head)
{
	rhs.root = rhs.tail = rhs.head = nullptr;
}

//Move Assignment
template<typename value, typename comparator>
splay_tree<value, comparator>& 
splay_tree<value, comparator>::operator=(splay_tree<value, comparator>&& rhs)
{
	if(this != &rhs)
	{
		destroy_tree(root);
//		delete head;
//		delete tail;
		root = rhs.root;
		head = rhs.head;
		tail = rhs.tail;
		rhs.root = rhs.tail = rhs.head = nullptr;
		size = rhs.size;
		comp = rhs.comp;
	}
	return *this;
}

//Destructor
template<typename value, typename comparator>
splay_tree<value, comparator>::~splay_tree()
{
	destroy_tree(root);
}

//Clone tree
template<typename value, typename comparator>
typename splay_tree<value, comparator>::node* 
	splay_tree<value, comparator>::clone_tree(node* clone_from, node* parent) 
{
	if(clone_from == nullptr)	
		return nullptr;
	node* new_node = new node(clone_from->node_value_);
	new_node->node_value_ = clone_from->node_value_;
	new_node->parent_ = parent;
	new_node->left_child_ = clone_tree(clone_from->left_child_,new_node);
	new_node->right_child_ = clone_tree(clone_from->right_child_, new_node);
	return new_node;
}

//Destroy Tree
template<typename value, typename comparator>
void splay_tree<value, comparator>::destroy_tree(node* parent) 
{
	if(parent == nullptr)	
		return;
	destroy_tree(parent->left_child_);
	destroy_tree(parent->right_child_);
	delete parent;
}

//Return Iterator begin
template<typename value, typename comparator>
typename splay_tree<value, comparator>::Iterator
	splay_tree<value, comparator>::begin() const
{
	return Iterator(head);
}

//Return Iterator end
template<typename value, typename comparator>
typename splay_tree<value, comparator>::Iterator
	splay_tree<value, comparator>::end()
{
	return Iterator(tail);
}

//Return if size of tree is null
template<typename value, typename comparator>
bool splay_tree<value, comparator>::empty() const
{
	return (size == 0);
}

// Insert value into tree
template<typename value, typename comparator>
pair<typename splay_tree<value, comparator>::Iterator, bool>
splay_tree<value, comparator>::insert(const value& val)
{
	//first searching in the tree if the value exists
	auto find_pair = find(val);
	// //if already exists returning the iterator and false 
	if(find_pair.second)	
		return pair<typename splay_tree<value, comparator>::Iterator, bool>(find_pair.first, !find_pair.second);	
	node* new_node = new node(val);
	//if empty make new node and assign appropriately and returns
	if(empty())
	{
			head = tail = root = new_node;
			return pair<typename splay_tree<value, comparator>::Iterator, bool>(typename splay_tree<value, comparator>::Iterator(head), true);
	}
	insert_node(root, nullptr,  val);
	find_pair = find(val);
	return find_pair;
}
template<typename value, typename comparator>
pair<typename splay_tree<value, comparator>::Iterator, bool> 
splay_tree<value, comparator>::find(const value& val) const
{
	// begin();
	return pair<typename splay_tree<value, comparator>::Iterator, bool>(begin(), true);
}

template<typename value, typename comparator>
void splay_tree<value, comparator>::rotate_up(splay_tree<value, comparator>::node* node_)
{
	node* parent, grandparent;
	if(node_->parent_)
		parent = node_->parent_;
	else
		return;

	if(node_->parent_->parent_)
		grandparent = node_->parent_->parent_;

	if(node_->parent_->left_child_ == node_)
	{
		node* child = node_->right_child_;
		node_->right_child_ = parent;
		if(child)
		{
			parent->left_child_ = child;
			child->parent_ = parent;
		}
		else
			parent->left_child = nullptr;
	}

	else
	{
		node* child = node_->left_child_;
		node_->left_child_ = parent;
		if(child)
		{
			parent->right_child = child;
			child->parent_ = parent;
		}
		else
			parent->right_child = nullptr;
	}
	parent->parent_ = node_;
	if(grandparent)
	{
		node_->parent_ = grandparent;
		if(grandparent->left_child_ == parent)
			grandparent->left_child_ = node_;
		else
			grandparent->right_child_ = node_;
	}
	else
		node_->parent_ = nullptr;	
}

template<typename value, typename comparator>
class splay_tree<value, comparator>::Iterator
{
public:
	explicit Iterator(node* node_ = nullptr) : iter(node_){	}
	bool operator==(const Iterator& rhs) const
	{
		return iter == rhs.iter;
	}
	bool operator!=(const Iterator& rhs) const
	{
		return !(*this == rhs);
	}
	value operator*()const
	{
		return iter->node_value_;;
	}
	Iterator& operator++()	//pre increment
	{
		//logic to move forward in binary tree
		if(iter->right_child_)
		{
			iter = iter->right_child_;
			return *this;
		}
		if(iter->parent_)
		{
			if(iter->parent_->left_child_ == iter) //left_child with no children
			{
				iter = iter->parent_;
				return *this;
			}
			else
			{
				if(iter->parent_->parent_)
					iter = iter->parent_;
				/*else
					cout << "Cannot increment further";*/
			}
			
		}
		return *this;
	}
	Iterator operator++(int)	//post increment
	{
		Iterator temp(*this);
		++*this;
		return temp;
	}
	Iterator& operator--()	//pre decrement
	{
		//logic to move backward in binary tree
		if(iter->left_child_)
		{
			iter = iter->left_child_;
			return *this;
		}
		if(iter->parent_)
		{
			if(iter->parent_->right_child_ == iter) //right child with no children
			{
				iter = iter->parent_;
				return *this;
			}
			else
			{
				if(iter->parent_->parent_)
					iter = iter->parent_;
				/*else
					cout << "Cannot decrement further";*/
			}
			
		}
		return *this;
	}
	Iterator operator--(int)	//post decrement
	{
		Iterator temp(*this);
		--*this;
		return temp;
	}

private:
	node* iter;
};

#endif
