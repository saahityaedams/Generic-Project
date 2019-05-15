#include "splay.h"
#include <functional>

using namespace std;

template<typename T>
struct Less
{
	bool operator()(const T& x, const T& y)
	{
		return x > y;
	}
};

struct MyDate
{
	public:
	MyDate():dd_(0),mm_(0), yy_(0) {} 
	MyDate(int dd, int mm, int yy) : dd_(dd), mm_(mm), yy_(yy) { }
	friend ostream& operator<<(ostream&, const MyDate&);
	friend bool operator<(const MyDate& lhs, const MyDate& rhs);
	friend bool compare_date(const MyDate& lhs, const MyDate& rhs);
	private:
	int dd_;
	int mm_;
	int yy_;
	
};
ostream& operator<<(ostream& o, const MyDate& d)
{
	return o << d.dd_ << "-" << d.mm_ << "-" << d.yy_ << "\n";
}

bool operator<(const MyDate& lhs, const MyDate& rhs)
{
	if(lhs.yy_ < rhs.yy_)
		return true;
	if(lhs.yy_ == rhs.yy_ && lhs.mm_ < rhs.mm_)
		return true;
	if(lhs.yy_ == rhs.yy_ && lhs.mm_ == rhs.mm_ && lhs.dd_ < rhs.dd_)
		return true;
	return false;


}

template<typename ptr_t>
void disp(ptr_t first, ptr_t last)
{
	while(first != last) // while(first < last)
	{
		cout << *first << "\t";
		++first; // first += 1
	}
	cout << "\n";
}
bool compare_date(const MyDate& lhs, const MyDate& rhs)
{
	return lhs.dd_ < rhs.dd_;
}
struct MyLess
{
	bool operator()(int x, int y) { return x < y; }
};
struct MyPred
{
	bool operator()(int x, int y) { return x % 10 < y % 10; }
};
struct MyDatePred
{
//	bool operator()(const MyDate& x, const MyDate& y) { return x  < y ; }
	bool operator()(const MyDate& x, const MyDate& y) { return compare_date(x, y); }
};

int main() {
	splay_tree<int, greater<int>> st;
	splay_tree<int, greater<int>> cp;
	st.insert(10);
	st.insert(40);
	st.insert(100);
	st.insert(30);
	st.insert(20);
	cout << boolalpha;
	cout << st.find(20).second << endl;
	cout << st.find(20).second << endl;
	cout << st.find(20).second << endl;
	cout << st.find(20).second << endl;

	// cp.insert(10);
	// cp.insert(40);
	// cp.insert(100);
	// cp.insert(30);

	//cp.insert(20);
// 		bool q = st == cp;
// cout << "Q: " << q <<endl;
// cout << st;
// 	cout <<"DISPLAYING";
// 	for(auto it = st.begin(); it!=st.end(); ++it)
// 		cout << *it << " ";
// 	for(auto it = st.rbegin(); it!=st.rend(); --it)
// 		cout << *it << " ";
// 		cout << "DISPLAY";// << *st.begin() << " "<<*st.end();
// 	auto p = st.begin();
// 	p++;
// 	cout << *p;
// 	p++;
// 	cout << *p;
// 	p++;
// 	cout << *p;
// 	p++;
// 	cout << *p;
// 	p++;
// 	cout << *p;

	// if(p == st.end())
	// 	cout <<"END";
	// cout << endl << endl;
	// cout << "size of st is " << st.size() << endl;
	// //for(auto it = st.begin(); it!=st.end(); ++it)
	// //	cout << *it << " ";
	// auto f10 = st.find(10);
	// auto f20 = st.find(20);
	// auto f30 = st.find(40);
	// 	auto f40 = st.find(30);
	// auto f50 = st.find(100);
	// cout <<"Hallelujah "<<  *(f10.first) << endl;
	// cout <<"Hallelujah "<<  *(f20.first) << endl;
	// cout <<"Hallelujah "<<  *(f30.first) << endl;
	// cout <<"Hallelujah "<<  *(f40.first) << endl;
	// cout <<"Hallelujah "<<  *(f50.first) << endl;

	// cout <<"Hallelujah "<<  (f10.second) << endl;
	// cout <<"Hallelujah "<<  (f20.second) << endl;
	// cout <<"Hallelujah "<<  (f30.second) << endl;

	// st.erase(10);
	// f10 = st.find(10);
	// cout <<"Hallelujah "<<  *(f10.first) << endl;
	// cout <<"Hallelujah "<<  (f10.second) << endl;
	// MyDate d[] = {
	// 	{26, 12, 2004},
	// 	{11, 9, 2001},	
	// 	{11, 1, 1966},
	// 	{26, 12, 2004},
	// 	{11, 9, 2001},	
	// 	{26, 1, 2001},
	// 	{30, 1, 1948},
	// 	{11, 9, 2001},	
	// 	{26, 12, 2004} 
	// };
	// splay_tree<MyDate, MyDatePred> s4;
	// for(auto it : d)
	// 	s4.insert(it);
	// cout << s4;
	// // cout <<"Hallelujah "<<  *(st.find(100).first) << endl;
	// // st.erase(100);
	// // cout <<"Hallelujah "<<  *(st.find(100).first) << endl;
	// //if(st.begin() == st.end())	cout << "Hello" << endl;	//this is clearly wrong
	// // auto it = st.begin();
	// // ++it;
	// // cout << *it << endl;
}
