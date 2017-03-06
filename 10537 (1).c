/*
 * 10537. The Toll! Revisited
 * TOPIC: dijkstra, binary search, comparison function, binary heap with update, printing the path, lex order
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 0x100
#define Q (2*N)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define oo (1LL<<61)
typedef long long i64;
#define in(x)  (0|((x)<<1))
#define out(x) (1|((x)<<1))

int cs,n,is[256],yes,g[256][256],m,id[256],a[N][N],src,dst,heap[Q],pos[N],cnt,p[N],pr,
	deg[N],adj[N][N],seen[N];
i64 d[N],de;
char v[256],prev;

int cmp( int x, int y ) {
	/*
	if ( v[x>>1] == v[y>>1] ) {
		if ( d[x] == d[y] )
			return 0;
		if ( d[x] > d[y] )
			return -1;
		return 1;
	}
	if ( v[x>>1] < v[y>>1] )
		return -1;
	return 1;
	*/
	if ( d[x] == d[y] ) {
		if ( v[x>>1] == v[y>>1] )
			return 0;
		if ( v[x>>1] < v[y>>1] )
			return -1;
		return 1;
	}
	if ( d[x] > d[y] )
		return -1;
	return 1;
}

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 ) pos[heap[cnt]=x]=cnt,++cnt;
	for ( j = pos[x]; j && cmp(heap[i=(j-1)>>1],heap[j]) > 0; bubble, j = i );
}

int pop() {
	int i,j,x = *heap;
	if ( (pos[x]=-1),--cnt )
		pos[*heap = heap[cnt]] = 0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j < cnt-1 && cmp(heap[j],heap[j+1]) > 0 ) ++j;
		if ( cmp(heap[i],heap[j]) <= 0 ) break ;
	}
	return x;
}

int is_city( int x ) { 
	assert( isalpha(v[x>>1]) );
	return 'A'<=v[x>>1]&&v[x>>1]<='Z';
}

i64 toll( i64 T, int x ) {
	if ( x&1 ) return 0;
	if ( is_city(x) ) {
		if ( T%20 ) T /= 20, ++T;
		else T /= 20;
		return T;
	}
	return 1;
}

i64 dijk( int src, int dst, i64 D ) {
	int x,y,z,i,j,k,t;
	i64 dw;
	for ( x = 0; x < n; d[x++] = -oo );
	for ( cnt = 0, memset(pos,-1,sizeof pos), p[src] = -1, d[src] = D, push(src); cnt; )
		for ( x = pop(), i = 0; i < deg[x] && (z = adj[x][i]) >= 0; ++i )
			if ( d[z] < d[x]-(dw = toll(d[x],z)) )
				d[z] = d[p[z]=x]-dw, push(z);
	return d[dst];
}

void dump( int src, int x ) {
	if ( p[x] != -1 ) dump(src,p[x]);
	if ( prev == v[x>>1] ) return ;
	if ( ++pr > 1 ) putchar('-');
	printf("%c",prev = v[x>>1]);
}

int q[1 << 20],*head,*tail;

int lex_smaller( int x, int y ) {
	int path[2][N],*ptr[2],z,i,j,k,t;
	ptr[0] = path[0], ptr[1] = path[1];
	for ( z = x; z != -1; *ptr[0]++ = z, z = p[z] );
	for ( z = y; z != -1; *ptr[1]++ = z, z = p[z] );
	for ( k = 0; k < 2; ++k )
		for ( i = 0, j = ptr[k]-path[k]-1; i < j; ++i, --j )
			t = path[k][i], path[k][i] = path[k][j], path[k][j] = t;
	for ( i = 0; i < ptr[0]-path[0] && i < ptr[1]-path[1]; ++i )
		if ( path[0][i] != path[1][i] )
			return path[0][i] < path[1][i];
	return ptr[0]-path[0] < ptr[1]-path[1];
}

void bfs( int src, int dst, i64 D ) {
	int x,y,i;
	i64 dw;
	for ( x = 0; x < n; d[x++] = -oo );
	for ( head = tail = q, d[*tail++ = src] = D; head < tail; )
		for ( x = *head++, i = 0; i < deg[x] && d[x] >= de; ++i )
			if ( d[y = adj[x][i]] < d[x]-(dw = toll(d[x],y)) || (d[y] == d[x]-dw && lex_smaller(x,p[y])) )
				d[*tail++ = y] = d[p[y] = x]-dw;
}

int dfs( int dst, int x, i64 D ) {
	int y,i;
	if ( x == dst && D == de )
		return 1;
	if ( x == dst ||  D < de ) 
		return 0;
	for ( i = 0; i < deg[x] && (y=adj[x][i]) >= 0; ++i )
		if ( seen[y] != yes ) {
			p[y] = x, seen[y] = yes;
			if ( dfs(dst,y,D-toll(D,y)) )
				return 1;
			seen[y] = 0;
		}
	return 0;
}

int main() {
	int i,j,k,src,dst;
	char tmp0[0x20],tmp1[0x20];
	i64 low,high,mid,ans;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
	for ( ;1 == scanf("%d",&n) && n != -1 && ++yes; ) {
		printf("Case %d:\n",++cs);
		for ( k = 0; k < n; ++k ) {
			scanf("%s %s",tmp0,tmp1);
			/*if ( *tmp0 == *tmp1 ) continue ;*/
			is[*tmp0] = is[*tmp1] = yes;
			g[*tmp0][*tmp1] = g[*tmp1][*tmp0] = yes;
		}
		for ( n = 0, i = 'A'; i <= 'Z'; ++i )
			/*if ( is[i] == yes )*/ v[id[i] = n++] = i;
		for ( i = 'a'; i <= 'z'; ++i )
			/*if ( is[i] == yes )*/ v[id[i] = n++] = i;
		memset(a,0,sizeof a);
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				if ( g[v[i]][v[j]]==yes )
					a[out(i)][in(j)]=1;
		for ( i = 0; i < n; ++i ) a[in(i)][out(i)]=1;
		for ( n <<= 1, i = 0; i < n; ++i )
			for ( deg[i] = 0, j = 0; j < n; ++j )
				if ( a[i][j] )
					adj[i][deg[i]++] = j;
		scanf("%lld %s %s",&de,tmp0,tmp1);
		src = out(id[*tmp0]), dst = out(id[*tmp1]);
		if ( dijk(src,dst,low=0) >= de ) 
			ans = low;
		else {
			for ( low = 0, high = +oo; low+1 != high; )
				if ( dijk(src,dst,mid=(low>>1)+(high>>1))<de )
					low = mid;
				else high = mid;
			ans = high;
		}
		bfs(src,dst,ans);
		printf("%lld\n",ans);
		prev = -1, pr = 0, dump(src,dst);
		putchar('\n');
	}
    return 0;
}

