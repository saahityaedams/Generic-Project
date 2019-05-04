#include "splay.h"
#include <functional>

using namespace std;

int main() {
	splay_tree<int> st, cp;
	st.insert(10);
	st.insert(30);
	st.find(10);
	if(st.begin() == st.end())	cout << "You suck period" << endl;
	auto it = st.begin();
	++it;
	cout << *it << endl;
}
