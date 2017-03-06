/*
 * 11975. Tele-loto
 * TOPIC: easy interview question
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iostream>
#include <set>
#define N 0x400
using namespace std;

bool filled[5][5];
int n,m,b[1<<21],val[4],t[5][5],seen[80],yes;
pair<int,int> place[80];

bool diag0() {
	int i,j;
	for ( i = 0, j = 0; i < 5; ++i, ++j )
		if ( !filled[i][j] )
			return false ;
	return i == 5 && j == 5 ;
}

bool diag1() {
	int i,j;
	for ( i = 0, j = 4; i < 5; ++i, --j )
		if ( !filled[i][j] )
			return false ;
	return i == 5 && j == -1;
}

int winning[N];
vector<int> vec;

int main() {
	int i,j,k,cs = 0,ts,l,cash,F,timing;
	bool midline, corners, diag;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %d",&n,&m);
		//assert( n <= 75 );
		assert( m <= 1000 );
		for ( i = 0; i < n; ++i ) 
			scanf("%d",&b[i]);
		for ( i = 0; i < 4; ++i )
			scanf("%d",&val[i]);
		printf("Case %d:\n",++cs);
		for ( vec.clear(), timing = (1<<29), k = 0; k < m && ++yes; ++k ) {
			for ( i = 0; i < 5; ++i )
				for ( j = 0; j < 5; ++j ) {
					scanf("%d",&t[i][j]);
					if ( !(1 <= t[i][j] && t[i][j] <= 75) ) continue ;
					assert( seen[t[i][j]] != yes );
				   	seen[t[i][j]] = yes, place[t[i][j]] = make_pair(i,j);
				}
			memset(filled,0,sizeof filled);
			corners = midline = diag = false ;
			for ( F = 0, cash = 0, i = 0; i < n; ++i ) {
				if ( i+1 >= 75 || seen[b[i]] != yes || filled[place[b[i]].first][place[b[i]].second] ) continue ;
				filled[place[b[i]].first][place[b[i]].second] = true ;
				if ( i+1 <= 35 && !corners ) 
					if ( filled[0][0] && filled[0][4] && filled[4][0] && filled[4][4] )
						cash += val[0], corners = true ;
				if ( i+1 <= 40 && !midline )
					if ( filled[2][0] && filled[2][1] && filled[2][3] && filled[2][2] && filled[2][4] )
						cash += val[1], midline = true ;
				if ( i+1 <= 45 && !diag )
					if ( diag0() && diag1() ) {
						cash += val[2], diag = true ;
					}
				if ( ++F == 25 ) {
						/*
					if ( timing < i ) continue ;
					if ( i < timing ) {
						vec.clear();
						vec.push_back(k);
						timing = i;
					}
					else */vec.push_back(k);
				}
			}
			winning[k] = cash;
		}
		for ( i = 0; i < (int)vec.size(); ++i )
			winning[vec[i]] += val[3];
		for ( i = 0; i < m; ++i )
			printf("%d\n",winning[i]);
		if ( ts ) putchar('\n');
	}
	return 0;
}


