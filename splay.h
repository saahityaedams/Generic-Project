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
	Iterator begin();	//DONE

	//Returns iterator to last element of set
	Iterator end();		//DONE

	//Inserts element and returns iterator to that element
	pair<Iterator, bool> insert(const value& val);

	//Not sure whether to erase given a value or given an iterator
	pair<Iterator, bool> erase(const value& val);

	//Finds value and returns iterator to it
	pair<Iterator, bool> find(const value& val);

	//Checks whether set is empty
	bool empty() const;	//DONE

private:
	struct node
	{
		value node_value_;
		node* left_child_;
		node* right_child_;
		node* parent_;

		node(const value& val): node_value_(val) {}
	};

	node* head, *tail;
	node* root;
	
	comparator comp;
	size_t size;
	
	node* insert_node( node* root, node* parent_node, const value& val);

	void rotate_up(node* child) const;

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

template<typename value, typename comparator>
splay_tree<value, comparator>::splay_tree(splay_tree&& rhs)
: size(rhs.size), comp(rhs.comp), root(rhs.root), tail(rhs.tail), head(rhs.head)
{
	rhs.root = rhs.tail = rhs.head = nullptr;
}

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

template<typename value, typename comparator>
splay_tree<value, comparator>::~splay_tree()
{
	destroy_tree(root);
}

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

template<typename value, typename comparator>
void splay_tree<value, comparator>::destroy_tree(node* parent) 
{
	if(parent == nullptr)	
		return;
	destroy_tree(parent->left_child_);
	destroy_tree(parent->right_child_);
	delete parent;
}

template<typename value, typename comparator>
typename splay_tree<value, comparator>::Iterator
	splay_tree<value, comparator>::begin()
{
	return Iterator(head);
}

template<typename value, typename comparator>
typename splay_tree<value, comparator>::Iterator
	splay_tree<value, comparator>::end()
{
	return Iterator(tail);
}

template<typename value, typename comparator>
bool splay_tree<value, comparator>::empty() const
{
	return (size == 0);
}
template<typename value, typename comparator>
pair<typename splay_tree<value, comparator>::Iterator, bool>
	splay_tree<value, comparator>::insert(const value& val)
{
	//first searching in the tree if the value exists
	auto find_pair = find(val);
	//if already exists returning the iterator and false 
	if(find_pair.second)	return pair<typename splay_tree<value, comparator>::Iterator, bool>(find_pair.first, !find_pair.second);	
	node* new_node = new node(val);
	//if empty make new node and assign appropriately and returns
	if(empty())
	{
			head = tail = root = new_node;
			return pair<Iterator, bool>(Iterator(head), true);
	}
	insert_node(root, nullptr,  val);

}

//should  set the parent pointer
template<typename value, typename comparator>
typename splay_tree<value, comparator>::node* 
	insert_node(typename splay_tree<value, comparator>::node* node_, typename splay_tree<value, comparator>::node* parent_node_, const value& val)
{
	if (node_ == nullptr)
	{ 
		typename splay_tree<value, comparator>::node *new_node_ = typename splay_tree<value, comparator>::node(val);
		new_node_->parent = parent_node_;
		return new_node_; 
	}
	if (val < node_->node_value_) 
		node_->left  = insert_node(node_->left_child_, node_, val); 
	else if (val > node_->node_value_) 
		node_->right = insert_node(node_->right_child_, node_ , val);    
	//this case shouldnt happen
	return node_; 
}
#endif
