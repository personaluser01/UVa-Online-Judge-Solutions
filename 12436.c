/*
 * 12436. Rip Van Winkle's Code
 * TOPIC: segment tree
 * status: in progress
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 250100
typedef long long i64;

i64 t[2*N];

i64 ladderAscending( int qi, int qj, int i, int j ) {
	return (j+i-2*qi+2)*(j-i+1)/2;
}

i64 ladderDescending( int qi, int qj, int i, int j ) {
	return (2*qj-j-i-+2)*(j-i)/2;
}

void updateTypeA( int v, int i, int j, int qi, int qj ) {
	if ( i > qj || qi > j ) return ;
	if ( qi <= i && j <= qj ) {
		t[v] += ladderAscending(qi,qj,i,j);
		return ;
	}
	updateTypeA(2*v,i,(i+j)/2,qi,qj);
	updateTypeA(2*v+1,(i+j)/2+1,j,qi,qj);
} ;

void updateTypeB( int v, int i, int j, int qi, int qj ) {
	if ( i > qj || qi > j ) return ;
	if ( qi <= i && j <= qj ) {
		t[v] += ladderDescending(qi,qj,i,j);
		return ;
	}
	updateTypeB(2*v,i,(i+j)/2,qi,qj);
	updateTypeB(2*v+1,(i+j)/2+1,j,qi,qj);
} ;

void updateTypeC( int v, int i, int j, int qi, int qj, int addval ) {
	if ( i > qj || qi > j ) return ;
	if ( qi <= i && j <= qj ) {
		t[v] = (j-i+1)*addval;
		return ;
	}
	updateTypeC(2*v,i,(i+j)/2,qi,qj,addval);
	updateTypeC(2*v+1,(i+j)/2+1,j,qi,qj,addval);
} ;

i64 query( int v, int i, int j, int qi, int qj ) {
	if ( qi > j || i > qj ) return 0;
	if ( qi <= i && j <= qj ) return t[v];
	return query(2*v,i,(i+j)/2,qi,qj)+query(2*v+1,(i+j)/2+1,j,qi,qj);
} ;

int main() {
	int i,j,k,qr,n;
	i64 dt;
	char op[0x400];
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&qr), n = 250000; qr-- && 1==scanf("%s",op); ) 
		switch ( 0[op] ) {
			case 'A': assert( 2 == scanf("%d %d",&i,&j) );
					  updateTypeA(1,1,n,i,j);
					  break ;
			case 'B': assert( 2 == scanf("%d %d",&i,&j) );
					  updateTypeB(1,1,n,i,j);
					  break ;
			case 'C': assert( 3 == scanf("%d %d %lld",&i,&j,&dt) );
					  updateTypeC(1,1,n,i,j,dt);
					  break ;
			default:  printf("%lld\n",query(1,1,n,i,j)) ; 
					  break ;
		}
	return 0;
} ;

