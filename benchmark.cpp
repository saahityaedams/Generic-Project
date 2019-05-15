#include<climits>
#include<set>
#include<iostream>
#include<chrono>
#include<cstdlib>
#include "splay.h"
using namespace std;

int main()
{
    using clock = std::chrono::steady_clock;
    // cout << INT_MIN << endl;   
    // cout << INT_MAX << endl;
//time to sequence insert
#if 0

    set<int> myset;
    int temp = 0;
    clock::time_point start_set = clock::now();
    while(temp != 10000)
    {
        myset.insert(temp++);
    }
    clock::time_point end_set = clock::now();
    clock::duration execution_time_set = end_set - start_set;
    cout << execution_time_set.count() << endl;

    splay_tree<int> mysplaytree;
    temp = 0;
    clock::time_point start_splaytree = clock::now();
    while(temp != 10000)
    {
        mysplaytree.insert(temp++);
    }
    clock::time_point end_splaytree = clock::now();
    clock::duration execution_time_splaytree = end_splaytree - start_splaytree;
    cout << execution_time_splaytree.count() << endl;

#endif

//time to sequence find
#if 0   

    set<int> myset;
    int temp = 0;
    while(temp != 10000)
    {
        myset.insert(temp++);
    }
    clock::time_point start_set = clock::now();
    temp = 0;
    while(temp != 10000)
    {
        myset.find(temp++);
    }
    clock::time_point end_set = clock::now();
    clock::duration execution_time_set = end_set - start_set;
    cout << execution_time_set.count() << endl;

    splay_tree<int> mysplaytree;
    temp = 0;
    while(temp != 10000)
    {
        mysplaytree.insert(temp++);
    }
    clock::time_point start_splaytree = clock::now();
    temp = 0;
    while(temp != 10000)
    {
        mysplaytree.find(temp++);
    }
    clock::time_point end_splaytree = clock::now();
    clock::duration execution_time_splaytree = end_splaytree - start_splaytree;
    cout << execution_time_splaytree.count() << endl;

#endif

//time to repeated find
#if 0

    set<int> myset;
    int temp = 0;
    while(temp != 10000)
    {
        myset.insert(temp++);
    }
    clock::time_point start_set = clock::now();
    temp = 0;
    int check_in = random()%10000;
    while(temp != 10000)
    {
        myset.find(check_in);
        ++temp;
    }
    clock::time_point end_set = clock::now();
    clock::duration execution_time_set = end_set - start_set;
    cout << execution_time_set.count() << endl;

    splay_tree<int> mysplaytree;
    temp = 0;
    while(temp != 10000)
    {
        mysplaytree.insert(temp++);
    }
    clock::time_point start_splaytree = clock::now();
    temp = 0;
    check_in = random()%10000;
    while(temp != 10000)
    {
        mysplaytree.find(check_in);
        ++temp;
    }
    clock::time_point end_splaytree = clock::now();
    clock::duration execution_time_splaytree = end_splaytree - start_splaytree;
    cout << execution_time_splaytree.count() << endl;

#endif

//time to random find
#if 0

    set<int> myset;
    int temp = 0;
    while(temp != 10000)
    {
        myset.insert(rand()%10000);
        ++temp;
    }
    clock::time_point start_set = clock::now();
    temp = 0;
    while(temp != 10000)
    {
        myset.find(rand()%10000);
        ++temp;
    }
    clock::time_point end_set = clock::now();
    clock::duration execution_time_set = end_set - start_set;
    cout << execution_time_set.count() << endl;
  
    splay_tree<int> mysplaytree;
    temp = 0;
    while(temp != 10000)
    {
        mysplaytree.insert(rand()%10000);
        ++temp;
    }
    clock::time_point start_splaytree = clock::now();
    temp = 0;
    while(temp != 10000)
    {
        mysplaytree.find(rand()%10000);
        ++temp;
    }
    clock::time_point end_splaytree = clock::now();
    clock::duration execution_time_splaytree = end_splaytree - start_splaytree;
    cout << execution_time_splaytree.count() << endl;

#endif

//time to random find big no
#if 1

    set<int> myset;
    int temp = 0;
    while(temp != 1000000)
    {
        myset.insert(rand()%1000000);
        ++temp;
    }
    clock::time_point start_set = clock::now();
    temp = 0;
    while(temp != 1000000)
    {
        myset.find(rand()%1000000);
        ++temp;
    }
    clock::time_point end_set = clock::now();
    clock::duration execution_time_set = end_set - start_set;
    cout << execution_time_set.count() << endl;
  
    splay_tree<int> mysplaytree;
    temp = 0;
    while(temp != 1000000)
    {
        mysplaytree.insert(rand()%1000000);
        ++temp;
    }
    clock::time_point start_splaytree = clock::now();
    temp = 0;
    while(temp != 1000000)
    {
        mysplaytree.find(rand()%1000000);
        ++temp;
    }
    clock::time_point end_splaytree = clock::now();
    clock::duration execution_time_splaytree = end_splaytree - start_splaytree;
    cout << execution_time_splaytree.count() << endl;

#endif


//bazillion size set and splaytree
//time to sequence find
#if 0

    set<int> myset;
    int temp = INT_MIN;
    while(temp != INT_MAX)
    {
        myset.insert(temp++);
    }
    clock::time_point start_set = clock::now();
    temp = 0;
    while(temp != INT_MAX)
    {
        myset.find(temp++);
    }
    clock::time_point end_set = clock::now();
    clock::duration execution_time_set = end_set - start_set;
    cout << execution_time_set.count() << endl;
    
    temp = 0; 
    splay_tree<int> mysplaytree;
    temp = 0;
    while(temp != 10000)
    {
        mysplaytree.insert(temp++);
    }
    clock::time_point start_splaytree = clock::now();
    temp = 0;
    while(temp != 10000)
    {
        mysplaytree.find(temp++);
    }
    clock::time_point end_splaytree = clock::now();
    clock::duration execution_time_splaytree = end_splaytree - start_splaytree;
    cout << execution_time_splaytree.count() << endl;

#endif


}