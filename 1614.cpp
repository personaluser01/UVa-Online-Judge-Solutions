/*
 * 1614. Hell on the Markets
 * TOPIC: ad hoc, sorting, maths
 * status: Accepted
 * NOTES: no idea why, have to prove the claim
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define value first
#define pos second
#define N 100001

vector<pair<int,int> > v;
int n,used[N],yes;
long long T;

int main() {
	int i,j,k;
	while ( 1 == scanf("%d",&n) ) {
		for ( T = 0,  v.clear(), i = 0; i < n; ++i )
			scanf("%d",&k), v.push_back(make_pair(k,i)), T += k;
		if ( (T&1) ) {
			puts("No");
			continue ;
		}
		sort(v.begin(),v.end(),greater<pair<int,int> >()), puts("Yes");
		for ( ++yes, T>>=1, i = 0; i < n && T; ++i ) 
			if ( v[i].value <= T )
				T -= v[i].value, used[v[i].pos] = yes;
		for ( k = 0, i = 0; i < n; ++i ) {
			if ( ++k > 1 ) putchar(' ');
			if ( used[i] != yes ) 
				putchar('-');
			putchar('1');
		}
		putchar('\n');
	}
	return 0;
}

