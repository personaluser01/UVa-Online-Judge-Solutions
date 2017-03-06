/*
 * 1232. SKYLINE
 * TOPIC: lazy propagation
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (1<<18)
#define oo (1<<29)
#ifndef max
#define max(x,y) ((x)<(y)?(y):(x))
#endif
#ifndef min
#define min(x,y) ((x)>(y)?(y):(x))
#endif
#define L(k) ((k)<<1)
#define R(k) (1|L(k))
enum { MI, MA };

typedef struct cell { int mn,mx,label; } cell;

cell t[N<<1];
int n,overlap;

void update( int x ) { t[x].mn = min(t[L(x)].mn,t[R(x)].mn), t[x].mx = max(t[L(x)].mx,t[R(x)].mx); };

void propagate( int x ) {
	if ( t[x].label ) {
		t[L(x)].mn = t[L(x)].mx = t[L(x)].label = t[x].label;
		t[R(x)].mn = t[R(x)].mx = t[R(x)].label = t[x].label;
		t[x].label = 0;
	}
};

void modify( int x, int i, int j, int qi, int qj, int h ) {
	int k = (i+j)/2;
	if ( i>j || qi>j || qj<i || t[x].mn>h ) return ;
	if ( i < j ) propagate(x);
	if ( qi <= i && j <= qj ) {
		if ( t[x].mx <= h ) {
			overlap += (j-i+1);
			t[x].mx = t[x].mn = t[x].label = h;
			return ;
		}
	}
	if ( qi >= k+1 )
		modify(R(x),k+1,j,qi,qj,h);
	else if ( qj <= k )
		modify(L(x),i,k,qi,qj,h);
	else 
		modify(L(x),i,k,qi,qj,h), modify(R(x),k+1,j,qi,qj,h);
	update(x);
};

int main() {
	int i,j,k,h,l,ts;
#ifndef ONLINE_JUDGE
	freopen("1232.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n) && n > 0; printf("%d\n",overlap) ) {
		for ( i = 0; i < (N<<1); t[i].mn = t[i].mx = t[i].label = 0, ++i );
		for ( overlap = 0; n-- && 3==scanf("%d %d %d",&i,&j,&h); modify(1,0,N-1,i,--j,h) );
	}
	return 0;
}

