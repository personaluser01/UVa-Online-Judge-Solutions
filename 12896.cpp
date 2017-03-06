/*
 * 12896. Mobile SMS
 * TOPIC: easy simulation, easy interview question
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <map>
#define N 0x80
using namespace std;

int n,key[N],c[N];
string s[] = {" ",".,?\"","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
map<pair<int,int>,char>  m;

int main() {
	int i,j,k,cs;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < 10; ++i )
		for ( j = 0; j < (int)s[i].size(); ++j ) 
			m[make_pair(i,j)] = s[i][j];
	for ( scanf("%d",&cs); cs--; ) {
		scanf("%d",&n);
		for ( i = 0; i < n; ++i )
			scanf("%d",key+i);
		for ( i = 0; i < n; ++i )
			scanf("%d",c+i);
		for ( i = 0; i < n; ++i )
			putchar(m[make_pair(key[i],c[i]-1)]);
		putchar('\n');
	}
	return 0;
}


