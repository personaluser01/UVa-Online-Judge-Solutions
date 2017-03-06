/*
 * 801. Flight Planning
 * TOPIC: dijkstra
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define tol 1e-12
#define K 0x80
#define N (1<<20)
#define enc(h,k) ( (h)|((k)<<10) )
#include <float.h>
#define oo (LDBL_MAX)
typedef unsigned int state;
#define VCRUISE 400
#define AOPT 30000
#define GPHOPT 200
#define GPHEXTRA 1
#define CLIMBCOST 5
typedef long long i64;

long double len[K],wind[K][2],d[N],best;
state heap[N<<1],p[N];
int cnt,pos[N],n,seen[N],yes;
long double get_wind( int height, int k ) { return (wind[k][0]+(wind[k][1]-wind[k][0])*((height-20000)/20000.00)); }

void push( state s ) {
	int i,j;
	if ( pos[s]<0 ) 
		pos[heap[cnt]=s]=cnt, ++cnt;
	for ( j=pos[s]; j && d[heap[i=(j-1)>>1]]>d[heap[j]]; bubble,j=i );
};

state pop() {
	int i,j;
	state s = *heap;
	if ( (cnt+=(pos[s]=-1)) )
		pos[*heap=heap[cnt]] = 0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j<cnt-1 && d[heap[j]]>d[heap[j+1]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return s;
};

void dump( state u, int depth ) { assert( u != -1 ); if ( depth >= 1 ) dump(p[u],depth-1), printf("%d ",u&1023); };

/*
int rnd( long double x ) {
	int dx=(int)(x+tol),ux=dx+1;
	return x-dx<=ux-x?dx:ux;
};
*/

state q[N],*head,*tail;

state dijkstra() {
	state u,v,dst = -1;
	long double cost,w,velocity,dh;
	int x,y,i,j,k,l,t,h;
	static int visited[K] = {0}, indeed = 0;

	for ( best = +oo, x = 0; x <= n; ++x )
		for ( t = 0; t <= 40; ++t )
			d[u=enc(t,x)]=+oo,pos[u]=-1;
	head = tail = q;
	for ( visited[0]=++indeed,cnt=0,p[u=enc(0,0)]=-1,seen[u]=++yes,d[u]=0,push(u); cnt; ) {
		u=pop(),k=(u>>10),h=(u&1023);
		visited[k] = indeed;
		if ( d[u] >= best ) continue ;
		if ( k == n ) {
			if ( best>d[u] )
				best=d[dst=u];
			continue ;
		}
		for ( t = 20; t <= 40; ++t ) {
			dh = t-h;
			if ( dh > 0 )
				cost = CLIMBCOST*dh;
			else cost = 0;
			dh = fabs(AOPT/1000-t);
			velocity = VCRUISE+get_wind(t*1000,k);
			if ( velocity <= 0 ) continue ;
			cost+=(len[k]/velocity)*(dh*GPHEXTRA+GPHOPT);
			/*assert( cost < +oo );*/
			if ( seen[v=enc(t,k+1)]!=yes || d[v]>d[u]+cost )
				d[v]=d[p[v]=u]+cost,push(v),seen[v]=yes,visited[k+1]=indeed;
		};
	};
	/* Runtime error probably here */
	/*
	for ( i = 0; i <= n; ++i )
		assert( visited[i] == indeed );*/
	return dst;
};

i64 rnd( long double x ) {
	i64 dx=(i64)(x+tol), ux=dx+1;
	/*printf("%.2Lf %lld %lld\n",x,dx,ux);*/
	if ( fabs(dx-x) < tol ) return dx;
	return ux;
	return 2*x<=ux+dx?dx:ux;
}

int main() {
	int i,j,k,ts,cs = 0;
#ifndef ONLINE_JUDGE
	freopen("801.in","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&n); ) {
		if ( n == 0 ) { printf("Flight %d: 0\n",++cs); continue; };
		for ( i = 0; i < n; scanf("%Lf %Lf %Lf",len+i,wind[i],wind[i]+1), ++i );
		printf("Flight %d: ",++cs), dump(dijkstra(),n), printf("%lld\n",rnd((best+tol)*10));
	}
	return 0;
};

