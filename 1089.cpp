/*
 * 1089. Suffix Replacement Grammar
 * TOPIC: floyd-warshall
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <map>
#include <vector>
#include <set>
#include <iostream>
using namespace std;
#define oo (1LL<<61)
#define M 0x20
#define N 0x80
#define V 0x400
typedef long long i64;

char src[M],dst[M],
	 a[N][M],b[N][M];
int n;

map<string,int> m[M];
set<pair<string,string> > rules;
vector<string> vec[M];

void ins( string s ) {
	int len = s.length();
	if ( !m[len].count(s) ) {
		int label = m[len].size();
		m[len][s] = label++;
		vec[len].push_back(s);
	}
}

i64 d[V][V],pre[V][V];

int main() {
	int i,j,k,cs = 0,p,v,l;
#ifndef ONLINE_JUDGE
	freopen("1089.in","r",stdin);
#endif
	for (;3 == scanf("%s %s %d",src,dst,&n);) {
		if ( 0[src] == '.' ) break ;
		printf("Case %d: ",++cs);
		for ( i = 0; i < M; vec[i].clear(), m[i++].clear() );
		for ( rules.clear(), k = 0; k < n; ++k ) {
			string aa,bb;
			cin >> aa >> bb;
			rules.insert(make_pair(aa,bb));
			for ( l = aa.length(), i = 0; i < l; ++i )
				ins(aa.substr(i)), ins(bb.substr(i));
		}
		string A = string(src), B = string(dst);
		for ( n = A.length(), i = 0; i < n; ++i )
			ins(A.substr(i)), ins(B.substr(i));
		for ( p = 1; p <= n; ++p ) {
			v = m[p].size();
			assert( vec[p].size() == v );
			for ( i = 0; i < v; ++i )
				for ( j = 0; j < v; ++j ) {
					if ( i == j ) {
						d[i][j] = 0;
						continue ;
					}
					d[i][j] = +oo;
					if ( rules.count(make_pair(vec[p][i],vec[p][j])) ) 
						d[i][j] = min(d[i][j],1LL);
					if ( p > 1 && vec[p][i][0] == vec[p][j][0] ) {
						int pi = m[p-1][vec[p][i].substr(1)], pj = m[p-1][vec[p][j].substr(1)];
						d[i][j] = min(d[i][j],pre[pi][pj]);
					}
				}
			for ( k = 0; k < v; ++k )
				for ( i = 0; i < v; ++i )
					for ( j = 0; j < v; ++j )
						if ( d[i][k]<+oo && d[k][j]<+oo )
							if ( d[i][j]>d[i][k]+d[k][j] ) 
								d[i][j]=d[i][k]+d[k][j];
			for ( i = 0; i < v; ++i )
				for ( j = 0; j < v; ++j )
					pre[i][j] = d[i][j];
		}
		int st = m[n][A], ed = m[n][B];
		long long D = d[st][ed];
		if ( D < +oo )
			printf("%lld\n",D);
		else puts("No solution");
	}
	return 0;
}

