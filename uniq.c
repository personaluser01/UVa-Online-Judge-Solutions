/*
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x40
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define oo (1LL<<60)
#define min(x,y) ((x)<(y)?(x):(y))
#define W 50001
typedef long long i64;

int heap[2*N],pos[N],cnt,n,m,precalc[N],p[N][N];
i64 g[N][N],d[N][N],dist[N],z[N][W];

void push( int x, i64 *d ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt] = x] = cnt, ++cnt;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i );
}

int pop( i64 *d ) {
	int i,j,x = *heap;
	if ( pos[x]=-1,--cnt )
		pos[heap[0]=heap[cnt]]=0;
	for ( j=0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j+1]] < d[heap[j]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return x;
}

void dijkstra( const int src ) {
	int x,y;
	for ( cnt = 0, x = 0; x < n; ++x )
		d[src][x] = +oo, pos[x] = -1;
	for ( d[src][src] = 0, p[src][src] = -1, push(src,d[src]); cnt; )
		for ( x = pop(d[src]), y = 0; y < n; ++y )
			if ( g[x][y] < +oo && d[src][y] > d[src][x]+g[x][y] )
				d[src][y] = d[src][x]+g[x][y], p[src][y] = x, push(y,d[src]);
}

int cmp( const void *a, const void *b ) {
	i64 *x = (i64 *)a,
		*y = (i64 *)b;
	if ( *x == *y )
		return 0;
	return *x<*y?1:-1;
}

int f( int src, int dst, i64 diff, int *res ) {
	int x,y,i,j,k,l,m;
	i64 e[N],w[N],ans,_max[N];

	for ( m = 0, x = p[src][dst]; x != src; e[m++] = g[p[src][x]][x], x = p[src][x] );
	assert( m < N );
	qsort(e,m,sizeof *e,cmp);
	for ( l = 0, i = 0; i < m; w[l++] = e[i], i = j ) 
		for ( j = i; j < m && e[j] == e[i]; ++j );
	diff >>= 1;
	assert( diff < W );
	if ( w[l-1] == 1 ) {
		*res = 2*(diff/w[0]+(diff%w[0]));
		return 1;
	}
	for ( m = l, i = 0; i <= m; ++i )
		for ( _max[i] = -oo, k = 0; k <= diff; ++k )
			z[i][k] = +oo;
	ans = +oo;
	for ( z[0][0] = 0, _max[0] = 0, i = 0; i < m; ++i )
		for ( k = 0; k <= _max[i]; ++k )
			if ( z[i][k] < +oo && z[i][k] < ans ) {
				for ( j = (diff-k)/w[i]; j >= 0; --j )
					if ( z[i+1][j*w[i]+k] > z[i][k]+j ) {
						z[i+1][j*w[i]+k] = z[i][k]+j;
						if ( j*w[i]+k > _max[i+1] )
							_max[i+1] = j*w[i]+k;
					}
				if ( k == diff ) ans = z[i][k];
			}
	if ( z[m][diff] < +oo ) { *res=z[m][diff]*2; return 1; }
	return 0;
}

int main() {
	int i,j,k,l,x,y,ts,qr;
	i64 diff;
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&m); ) {
		for ( i = 0; i < n; ++i )
			for ( precalc[i] = 0, j = 0; j < n; ++j )
				g[i][j] = d[i][j] = +oo, p[i][j] = -1;
		for ( l = m; l-- > 0; ) {
			scanf("%d %d %d",&i,&j,&k), --i, --j;
			k = min(g[i][j],k);
			g[i][j] = g[j][i] = k;
			assert( k >= 0 );
		}
		for ( scanf("%d",&qr); qr--; ) {
			scanf("%d %d %d",&i,&j,&k), --i, --j;
			if ( !precalc[i] ) dijkstra(i), precalc[i] = 1;
			if ( k < d[i][j] ) {
				puts("No");
				continue ;
			}
			if ( k == d[i][j] ) {
				assert( p[i][j] != -1 );
				for ( l = 0, x = j; x != i; ++l ) {
					assert( p[i][x] != -1 );
					assert( p[i][x] != x );
					x = p[i][x];
				}
				printf("Yes %d\n",l);
				continue ;
			}
			diff = k-d[i][j];
			if ( diff&1 ) {
				puts("No");
				continue ;
			}
			if ( !f(i,j,diff,&k) ) {
				puts("No");
				continue ;
			}
			assert( p[i][j] != -1 );
			for ( l = 0, x = j; x != i; ++l ) {
				assert( p[i][x] != -1 );
				assert( p[i][x] != x );
				x = p[i][x];
			}
			printf("Yes %d\n",l+k);
		}
	}
	return 0;
}


