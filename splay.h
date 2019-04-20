#ifndef SPLAY_TREE
#define SPLAY_TREE
#include <utility>

using namespace std;

template<typename value, typename comparator = 	less<value>>
class splay_tree
{
public:
	//Constructor
	splay_tree();

	//Copy Constructor
	splay_tree(const splay_tree& rhs);
	
	//Copy Assignment
	splay_tree& operator=(const splay_tree& rhs);
	
	//Move Constructor
	splay_tree(splay_tree&& rhs);
	
	//Move Assignment
	splay_tree& operator=(splay_tree&& rhs);
	
	//Destructor
	~splay_tree();

	//Iterator Class
	class Iterator;
	
	//Returns iterator to first element of set
	Iterator begin();

	//Returns iterator to last element of set
	Iterator end();

	//Inserts element and returns iterator to that element
	Iterator insert(const value& val);

	//Not sure whether to erase given a value or given an iterator
	Iterator erase(const value& val);

	//Finds value and returns iterator to it
	Iterator find(const value& val);

	//is operator[] needed for set?

	//Checks whether set is empty
	bool empty() const;

private:
	struct node
	{
		value node_value_;
		node* left_child_;
		node* right_child_;
		node* parent_;

		node(const value& val);
	};

	node* head, *tail;
	node* root;
	comparator comp;
	size_t size;

	void rotate_up(node* child) const;

	void splay(node* n) const;

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

splay_tree::splay_tree(splay_tree&& rhs):
{

}

#endif