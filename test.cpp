#include "splay.h"
#include <functional>

using namespace std;

int main() {
	splay_tree<int> st, cp;
	st.insert(10);
	st.insert(30);
	cout <<"Hallelujah "<<  *(st.find(10).first) << endl;
	cout <<"Hallelujah "<<  *(st.find(20).first) << endl;
	cout <<"Hallelujah "<<  *(st.find(30).first) << endl;
	cout <<"Hallelujah "<<  *(st.find(30).first) << endl;
	if(st.begin() == st.end())	cout << "Hello" << endl;	//this is clearly wrong
	// auto it = st.begin();
	// ++it;
	// cout << *it << endl;
}