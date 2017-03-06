/*
 * 523. Minimum Transport Cost
 * status; Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
#define N 0x200
#define enc(x,t) ((t)|((x)<<1))
#define oo 0xfffffffful
enum { IN, OUT };

char buff[1 << 18],*ptr;
int n,a[N][N],b[N],p[N][N],prev;
unsigned int g[N][N],d[N][N];

int read_matrix() {
	int i,j,k,t,cnt,u,v;
	for ( FG, cnt = 0, n = 0; 1 == sscanf(buff+cnt,"%d%n",a[0]+n,&k); cnt += k, ++n );
	for ( i = 1; i < n; ++i ) 
		for ( FG, cnt = 0, j = 0; j < n; ++j, cnt += k )
			assert( 1 == sscanf(buff+cnt,"%d%n",a[i]+j,&k) );
	for ( FG, cnt = 0, i = 0; i < n; ++i, cnt += k )
		assert( 1 == sscanf(buff+cnt,"%d%n",b+i,&k) );
	assert( 2*n < N );
	for ( i = 0; i < n; ++i )
		for ( k = IN; k <= OUT; ++k )
			for ( j = 0; j < n; ++j )
				for ( t = IN; t <= OUT; ++t )
					g[enc(i,k)][enc(j,t)] = +oo;
	for ( i = 0; i < n; ++i )
		u = enc(i,OUT), v = enc(i,IN), g[v][u] = b[i];
	for ( i = 0; i < n; ++i )
		for ( j = 0; j < n; ++j )
			if ( i != j && a[i][j] >= 0 ) {
				u = enc(i,OUT), v = enc(j,IN);
				g[u][v] = a[i][j];
			}
	return n;
}

void floyd_warshall() {
	int x,y,z;
	for ( x = 0; x < 2*n; ++x )
		for ( y = 0; y < 2*n; ++y )
			d[x][y]=+oo,p[x][y]=-1;
	for ( x = 0; x < 2*n; ++x )
		for ( y = 0; y < 2*n; ++y )
			if ( g[x][y] < +oo )
				d[x][y] = g[x][y], p[x][y] = x;
	for ( z = 0; z < 2*n; ++z )
		for ( x = 0; x < 2*n; ++x )
			for ( y = 0; y < 2*n; ++y )
				if ( d[x][z] < +oo && d[z][y] < +oo )
					if ( d[x][z]+d[z][y] < d[x][y] )
						d[x][y] = d[x][z]+d[z][y], p[x][y] = p[z][y];
}


int query( int *i, int *j ) { return !(!FG||2!=sscanf(buff,"%d %d",i,j)); }

void dump( int src, int dst ) {
	if ( src != dst ) {
		dump(src,p[src][dst]);
		if ( prev != (dst>>1)+1 )
			printf("-->%d",prev = (dst>>1)+1);
	}
}

int main() {
	int i,j,x,y,ts,cs;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( sscanf(FG,"%d",&ts), FG; ts--; ) {
		assert( read_matrix() );
		for ( cs = 0, floyd_warshall(); query(&i,&j); ) {
			if ( ++cs > 1 ) putchar('\n');
			printf("From %d to %d :\n",(--i)+1,(--j)+1);
			if ( i == j ) {
				printf("Path: %d",1+i);
				printf("\nTotal cost : %u\n",0);
				continue ;
			}
			x = enc(i,OUT), y = enc(j,IN);
			assert( d[x][y] < +oo );
			printf("Path: %d",prev = i+1), dump(x,y);
			printf("\nTotal cost : %u\n",d[x][y]);
		}
		if ( ts ) putchar('\n');
	}
	return 0;
}
