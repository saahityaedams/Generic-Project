#include "splay.h"
#include <functional>

using namespace std;

int main() {
	splay_tree<int, greater<int>> st, cp;
	st.insert(10);
	st.insert(40);
	st.insert(100);
	st.insert(30);
	st.insert(20);

	auto f10 = st.find(10);
	auto f20 = st.find(20);
	auto f30 = st.find(50);

	cout <<"Hallelujah "<<  *(f10.first) << endl;
	cout <<"Hallelujah "<<  *(f20.first) << endl;
	cout <<"Hallelujah "<<  *(f30.first) << endl;
	cout <<"Hallelujah "<<  (f10.second) << endl;
	cout <<"Hallelujah "<<  (f20.second) << endl;
	cout <<"Hallelujah "<<  (f30.second) << endl;
	st.erase(10);
	f10 = st.find(10);
	cout <<"Hallelujah "<<  *(f10.first) << endl;
	cout <<"Hallelujah "<<  (f10.second) << endl;
	// cout <<"Hallelujah "<<  *(st.find(100).first) << endl;
	// st.erase(100);
	// cout <<"Hallelujah "<<  *(st.find(100).first) << endl;
	//if(st.begin() == st.end())	cout << "Hello" << endl;	//this is clearly wrong
	// auto it = st.begin();
	// ++it;
	// cout << *it << endl;
}
