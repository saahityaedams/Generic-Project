#ifndef SPLAY_TREE
#define SPLAY_TREE
#include <utility>
#include <functional>
using namespace std;

template<typename value, typename comparator = 	less<value> >
class splay_tree
{
public:
	//Constructor
	splay_tree(comparator comp = comparator());
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

		node(const value& val): node_value_(val) {}
	};

	node* head, *tail;
	node* root;
	comparator comp;
	size_t size;

	void rotate_up(node* child) const;

	void splay(node* n) const;
	
	node* clone_tree(node * clone_from, node * parent);
	
	node* destroy_tree(node * clone_from);

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
//
// Implementation starts here
//
template<typename value, typename comparator>
splay_tree<value, comparator>::splay_tree(comparator comp) : comp(comp) {
	root = head = tail = nullptr;
	size = 0;
}

template<typename value, typename comparator>
splay_tree<value, comparator>::splay_tree(const splay_tree& rhs) {
	size = rhs.size;
	comp = rhs.comp;

	root = clone_tree(rhs.root, nullptr);
	
	tail = head = root;
	while(head->left)head = head->left;
	while(head->right)head = head->right;
}

template<typename value, typename comparator>
splay_tree<value, comparator>& 
splay_tree<value, comparator>::operator=(const splay_tree& rhs) {
	destroy_tree(root);
	
	size = rhs.size;
	comp = rhs.comp;

	root = clone_tree(rhs.root, nullptr);

	tail = head = root;
	while(head->left_child_)head = head->left_child_;
	while(head->right_child_)head = head->right_child_;	
}

template<typename value, typename comparator>
typename splay_tree<value, comparator>::node* 
splay_tree<value, comparator>::clone_tree(node* clone_from, node* parent) {
	if(clone_from == nullptr)	return nullptr;
	node* new_node = new node(clone_from->node_value_);
	new_node->node_value_ = clone_from->node_value_;
	new_node->parent_ = parent;
	new_node->left_child_ = clone_tree(clone_from->left_child_,new_node);
	new_node->right_child_ = clone_tree(clone_from->right_child_, new_node);
}

template<typename value, typename comparator>
typename splay_tree<value, comparator>::node* 
splay_tree<value, comparator>::destroy_tree(node * clone_from) {
	
}

template<typename value, typename comparator>
splay_tree<value, comparator>::~splay_tree(){
	
}
#endif
