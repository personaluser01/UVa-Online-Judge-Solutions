/*
 * 904. Overlapping Air Traffic Control Zones
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define N 0x20
#define DIM 3
#define tol 1e-11
typedef long long i64;
enum { Red, Black };
enum { L, R };
i64 max( i64 x, i64 y ) { return x < y ? y : x; }
i64 min( i64 x, i64 y ) { return x > y ? y : x; }
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
typedef unsigned int long u64;
#define LSB(i) ((i)&((~(i))+1))
#define oo (1 << 29)

i64 u[N][2][DIM],z[1 << 16][2][DIM];
int n,m;
char deg[1 << 20],bts[1 << 20];
unsigned int c[1 << 20];

int cmp_qsort( const void *a, const void *b ) {
	unsigned int x = *(unsigned int *)a,
				 y = *(unsigned int *)b;
	return bts[x]-bts[y];
}

int Log( u64 k ) {
	assert( !(k & (k-1)) );
	return deg[k];
}

int is_less( const int l, unsigned int x, unsigned int y ) {
	int tx = (x&1),ty = (y&1),i = (x>>1),j = (y>>1);
	return u[i][tx][l]==u[j][ty][l]?(tx==R&&ty==L):(u[i][tx][l]<u[j][ty][l]);
}

void heap_push( const int l, unsigned int *heap, int *pos, int *cnt, unsigned int e ) {
	int i,j;
	if ( pos[e] < 0 ) pos[heap[*cnt] = e] = *cnt, ++(*cnt);
	for ( j = pos[e]; j && !is_less(l,heap[i = (j-1)>>1],heap[j]); bubble, j = i );
}


void heap_pop ( const int l, unsigned int *heap, int *pos, int *cnt, unsigned int *e ) {
	int i,j;
	if ( e ) *e = *heap;
	pos[*heap] = -1, --(*cnt);
	if ( *cnt )
		pos[*heap = heap[*cnt]] = 0;
	for ( j = 0;; bubble ) {
		i = j, j <<= 1, ++j;
		if ( j > *cnt-1 ) break ;
		if ( j < *cnt-1 && is_less(l,heap[j+1],heap[j]) ) ++j;
		if ( is_less(l,heap[i],heap[j]) ) break;
	}
}

i64 find_union( const int l, u64 mask ) {
	int pos[N],cnt,t,i,k,j;
	i64 prev = -oo,ax = 0,dt,left,right,a[N],b[N];
	unsigned int heap[N],e;
	u64 nmask = 0;

	if ( !mask ) return 0;

	if ( l == DIM-1 ) {
		for ( k = 0; mask; i = Log(LSB(mask)), (a[k] = u[i][L][l]), (b[k] = u[i][R][l]), ++k, mask&=~LSB(mask) );
		for ( j = 1;j;)
			for ( i = j = 0; i < k-1; ++i )
				if ( a[i] > a[i+1] )
					++j, xchg(a[i],a[i+1]),xchg(b[i],b[i+1]);
		for ( left = a[0], right = b[0], i = 1; i < k; ++i )
			if ( a[i] <= right ) 
				right = max(right,b[i]);
			else 
				ax += (right-left), left = a[i], right = b[i];
		return ax+(right-left);
	}

	memset(pos,-1,sizeof(pos)), cnt = 0;
	for (;mask; heap_push(l,heap,pos,&cnt,(Log(LSB(mask))<<1)), mask&=~LSB(mask) );
	for (;cnt; prev = u[i][t][l] ) {
		heap_pop(l,heap,pos,&cnt,&e), t = (e&1), i = (e>>1);
		assert( prev == -oo||u[i][t][l] >= prev );
		if ( t == L ) {
			heap_push(l,heap,pos,&cnt,e^1),nmask|=(1ULL<<i);
			continue ;
		}
		if ( dt = (u[i][R][l]-prev) )
			ax += dt*find_union(l+1,nmask);
		nmask&=~(1ULL<<i);
	}
	return ax;
}

i64 Volume( i64 z[2][DIM] ) {
	i64 ax = 1LL,j;
	assert( z );
	for ( j = 0; j < DIM; ++j ) {
		ax *= (z[R][j]-z[L][j]);
		ax = max(ax,0);
	}
	return ax;
}

i64 W( int k ) {
	int low,high,mid,i;
	i64 ax = 0;
	if ( k == 0 ) return 0;
	assert( bts[c[m-1]] == n );
	for(low=0,high=m-1;low+1<high;bts[c[mid=(low+high)/2]]<k?(low=mid):(high=mid));
	assert( bts[c[high]] == k && bts[c[low]] == k-1 );
	for ( i = high; i<m&&bts[c[i]] == bts[c[high]]; ax += Volume(z[c[i++]]) );
	return ax;
}

int main() {
	int i,j,k,t;
	unsigned int v,w;
	i64 U;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( v = 1; v < (1UL<<20); ++v )
		bts[v] = bts[v>>1]+(v&1);
	for ( i = 0; i < 20; ++i ) deg[1<<i] = i;
	for (;1 == scanf("%d",&n);) {
		for ( i = 0; i < n; ++i ) 
			for ( t = L; t <= R; ++t )
				for ( j = 0; j < DIM; scanf("%lld",&u[i][t][j++]) );
		for ( i = 0; i < n; ++i ) 
			for ( v=(1<<i), j = 0; j < DIM; ++j )
				for ( t = L; t <= R; ++t )
					z[v][t][j] = u[i][t][j];
		for ( w = 1; w < (1UL<<n); ++w )
			if ( bts[w] >= 2 ) {
				t = Log(LSB(w)), v = (w&~LSB(w));
				for ( j = 0; j < DIM; ++j ) {
					z[w][L][j] = max(u[t][L][j],z[v][L][j]);
					z[w][R][j] = min(u[t][R][j],z[v][R][j]);
					if ( z[w][R][j] <= z[w][L][j] )
						z[w][R][j] = z[w][L][j] = 0;
				}
			}
		for ( v = 0, m = 0; v < (1UL<<n); c[m++] = v++ );
		qsort(c,m,sizeof *c,cmp_qsort);
		for ( i = 0; i < m-1; ++i )
			assert( bts[c[i]] <= bts[c[i+1]] );
		/*U = find_union(0,(1ULL<<n)-1ULL);*/
		/*printf("U = %lld,  ",U);*/
		for ( U = 0, i = 1; i <= n; ++i )
			if ( i & 1 )
				U += W(i);
			else U -= W(i);
		for ( i = 0; i <= n-1; ++i )
			if ( i & 1 )
				U += (i+1)*W(i+1);
			else U -= (i+1)*W(i+1);
		printf("%lld\n",U);
	}
	return 0;
}
