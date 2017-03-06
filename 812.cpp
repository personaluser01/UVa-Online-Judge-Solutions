/*
 * status: Accepted
 * TOPIC: DP
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#define B 64
#define N 64
#include <set>
using namespace std;

int m,cs,pref[N][N],n[N],len[N];
vector<int> v[B];
vector<pair<int,int> > lst[N];
set<int> s;

bool my_less( const pair<int,int> &a, const pair<int,int> &b ) {
	if ( a.first > b.first )
		return true;
	if ( a.first < b.first )
		return false;
	return a.second < b.second;
}

void form_them( int idx, int k ) {
	if ( idx == m ) {
		s.insert(k);
		return ;
	}
	for ( int i = 0; i < len[idx]; ++i )
		form_them(idx+1,k+lst[idx][i].second);
}

int main() {
	int i,j,k,w;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&m) && m > 0 ) {
		for ( i = 0; i < m; ++i ) {
			for ( lst[i].clear(), v[i].clear(), v[i].push_back(0), scanf("%d",&k); k-- && 1 == scanf("%d",&j); v[i].push_back(j) );
			for ( n[i] = v[i].size()-1, j = 1; j <= n[i]; ++j )
				pref[i][j] = pref[i][j-1]+v[i][j];
			for ( j = 0; j <= n[i]; ++j )
				lst[i].push_back(make_pair(10*j-pref[i][j],j));
			sort(lst[i].begin(),lst[i].end(),my_less);
			for ( j = 0; j < lst[i].size() && lst[i][0].first == lst[i][j].first; ++j );
			len[i] = j;
		}
		s.clear(), form_them(0,0);
		for ( w = 0, i = 0; i < m; ++i )
			w += lst[i][0].first;
		if ( ++cs > 1 ) putchar('\n');
		printf("Workyards %d\n",cs);
		printf("Maximum profit is %d.\n",w);
		printf("Number of pruls to buy:");
		k = 0;
		for ( set<int>::iterator it = s.begin(); it != s.end() && k < 10; ++it, ++k )
			printf(" %d",*it);
		putchar('\n');
	}
	return 0;
}

