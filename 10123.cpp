/*
 * 10123. No Tipping
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define NONPOSSUMUS (puts("Impossible"))
using namespace std;
#define L(i) ((i) & ((~(i))+1))
#define N 20
#define Q (1 << N)
#include <cfloat>
#include <climits>
#define oo (DBL_MAX-1024)
#define tol 1e-7

int len,wgt,n,pos[N],weight[N],a[N],b[N],
	z[Q],sum_weights[Q],cur;
char l[Q];
bool ok[Q],seen[Q];

double gc( unsigned int u ) {
	if ( sum_weights[u] == 0 )
		return +oo;
	return z[u]/(sum_weights[u]+.0+wgt);
}

bool f( unsigned int u ) {
	if ( !u )
		return true;
	if ( !ok[u] || seen[u] )
		return false;
	seen[u] = true;
	for ( int i = 0; i < n; ++i )
		if ( 1 & (u>>i) ) {
			unsigned int v = u-(1UL<<i);
			if ( !ok[v] ) continue ;
			a[++cur] = i, b[cur] = i;
			if ( f(v) )
				return true;
			--cur;
		}
	return false;
}

int main() {
	int i,j,k,cs = 0;
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( ok[0] = true, i = 0; i < N; ++i ) l[1 << i] = i;
	for (;3 == scanf("%d %d %d",&len,&wgt,&n) && (len||wgt||n); ) {
		printf("Case %d:\n",++cs);
		for ( i = 0; i < n; ++i )
			scanf("%d %d",pos+i,weight+i);
		for ( u = 1; u < (1 << n); ++u ) {
			i = l[L(u)], v = u-L(u);
			sum_weights[u] = sum_weights[v] + weight[i];
			z[u] = z[v] + weight[i]*pos[i];
			ok[u] = fabs(gc(u)) <= 1.5+tol;
		}
		cur = -1, u = (1<<n)-1;
		memset(seen,0,sizeof(seen));
		if ( !f(u) )
			NONPOSSUMUS;
		else {
			assert( cur == n-1 );
			for ( i = 0; i < n; ++i )
				printf("%d %d\n",pos[a[i]],weight[b[i]]);
		}
	}
	return 0;
}

