/*
 * 11647. Judgement Day
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 0x80*3
#define MAXE (MAXV*4*2)
typedef long long i64;

i64 min(i64 x,i64 y) {return x<y?x:y;}

int ts,cs,demand[MAXV],last[MAXV],E,V,m,n,src,sink,isdig[256],
	next[MAXE],to[MAXE],seen[MAXE],yes,prev[MAXV],it,
	pos[MAXV],st[MAXV],*head,*top;

i64 cap[MAXE],flow[MAXE],cost[MAXE],Total,lower_bound[MAXE],
	dist[MAXV],Inf;
char unneeded[MAXV];

void add_arcs( int x, int y, i64 c, i64 w, i64 lb ) {
	int i = E++, j = E++;
	assert( lb <= c );
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] =  c,  cost[i] =  w, flow[i] = 0, lower_bound[i] = lb;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = -lb, cost[j] = -w, flow[j] = 0, lower_bound[j] = -c;
}

int bellman_ford() {
	int i,j,k,x,y,flag = 1;

	for ( dist[1]=0, seen[1]=++yes, i = 1; i <= it-1 && flag; ++i )
		for ( flag = 0, k = 0; k < E; ++k ) {
			x = to[k^1], y = to[k];
			if ( seen[x] != yes )
				continue ;
			if ( flow[k^1]>lower_bound[k^1] && (seen[y] != yes||dist[y]>dist[x]+cost[k]) )
				dist[y]=dist[x]+cost[k], prev[y] = 0|(k<<1), flag = 1, seen[y] = yes;
			if ( flow[k]<cap[k] && (seen[y] != yes||dist[y]>dist[x]+cost[k]) )
				dist[y]=dist[x]+cost[k], prev[y] = 1|(k<<1), flag = 1, seen[y] = yes;
		}
	if ( i <= it-1 ) return -1;
	for ( k = 0; k < E; ++k ) {
		x = to[k^1], y = to[k];
		if ( seen[x] != yes )
			continue ;
		if ( flow[k^1]>lower_bound[k^1] && (seen[y] != yes||dist[y]>dist[x]+cost[k]) ) {
			dist[y]=dist[x]+cost[k], prev[y] = 0|(k<<1), flag = 1;
			return 0|(k<<1);
		}
		if ( flow[k]<cap[k] && (seen[y] != yes||dist[y]>dist[x]+cost[k]) ) {
			dist[y]=dist[x]+cost[k], prev[y] = 1|(k<<1), flag = 1;
			return 1|(k<<1);
		}
	}
	return -1;
}

void inc_flow( int x, int y, i64 df ) {
	int i;
	for ( i = last[x]; i >= 0 && to[i] != y; i = next[i] );
	assert( i >= 0 );
	assert( to[i] == y );
	assert( flow[i]+df <= cap[i] );
	assert( flow[i^1]-df >= lower_bound[i^1] );
	flow[i] += df, flow[i^1] -= df;
}

i64 getnum() {
	i64 n = 0,ch;
	while ( (ch = getchar()) != EOF && !isdig[ch] );;
	for ( n = ch-'0'; (ch = getchar()) != EOF && isdig[ch]; )
		n = (n<<1)+(n<<3)+(ch-'0');
	return n;
}

void putnum( i64 n ) { (n<10)?putchar(n+'0'):(putnum(n/10),putchar((n%10)+'0')); }

int main() {
	int i,j,k,l,t,x,y,*tmp,left[MAXV],right[MAXV],gen[MAXV],flag;
	i64 bot,fcost,G,res,dd;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = '0'; i <= '9'; ++i ) isdig[i] = 1;
	for ( ts = getnum(); ts-- && ++yes; ) {
		n = getnum(), m = getnum();
		E=0,V=2*m+n,Total=0;
		for ( i = 0; i <= V; ++i ) last[i] = -1;
		for ( i = 1; i <= m; ++i ) 
			Total+=(demand[i]=getnum());
		Inf = n*Total;
		for ( i = 1; i <= m; ++i )
			add_arcs(i,i+m,Inf,0,demand[i]);
		for ( i = 1; i <= m-1; ++i )
			add_arcs(i+m,i+1,Inf,0,0);
		for ( i = 1; i <= n; ++i ) {
			k = getnum(), l = getnum(), t = getnum();
			if ( k > l ) j = k, k = l, l = j;
			assert( k <= l );
			left[i] = k, right[i] = l, gen[i] = t;
		}

		memset(unneeded,0,sizeof(unneeded));
		for ( i = 1; i <= n; ++i )
			for ( j = 1; j <= n; ++j )
				if ( i != j )
					if ( gen[i] <= gen[j] && unneeded[i] != 1 )
						if ( left[i] <= left[j] && right[j] <= right[i] )
							unneeded[j] = 1;
		/*
		do {
			for ( flag = 0, i = 1; i <= n; ++i )
				if ( !unneeded[i] && left[i] <= right[i] )
					for ( j = 1; j <= n; ++j )
						if ( i != j && !unneeded[j] && left[j] <= right[j] )
							if ( left[i] <= left[j] && left[j] <= right[i] && right[i] <= right[j] ) {
								if ( gen[i] < gen[j] )
									left[j] = right[i]+1, ++flag;
								else if ( gen[i] > gen[j] )
									right[i] = left[j]-1, ++flag;
							}
				for ( i = 1; flag && i <= n; ++i )
					if ( left[i] > right[i] )
						unneeded[i] = 1;
		} while ( flag );
		*/

		for ( it = V, i = 1; i <= n; ++i )
			if ( unneeded[i] ) --it;

		for ( i = 1; i <= n; ++i ) {
			if ( unneeded[i] ) 
				continue ;
			k = left[i], l = right[i], t = gen[i];
			for ( dd = 0, j = k; j <= l; ++j )
				if ( dd < demand[j] )
					dd = demand[j];
			add_arcs(i+2*m,k,Inf,((i64)t),0);
			inc_flow(i+2*m,k,dd);
			add_arcs(l+m,i+2*m,Inf,0,0);
			inc_flow(l+m,i+2*m,dd);
			for ( j = k; j < l; ++j )
				inc_flow(j,j+m,dd), inc_flow(j+m,j+1,dd);
			inc_flow(l,l+m,dd);
		}

		while ( (k = bellman_ford()) >= 0 ) {
			for ( top = head = st+V+2, ++yes, y = x = to[(k>>1)^1]; seen[x] != yes; ) {
				*--top = i = prev[x], seen[x] = yes, pos[x] = top-st;
				x = to[(i>>1)^1];
			}
			for ( bot = Inf, tmp = top; top <= st+pos[x];) {
				i = *top++;
				if ( i&1 ) bot = min(bot,cap[i>>1]-flow[i>>1]);
				else bot = min(bot,flow[(i>>1)^1]-lower_bound[(i>>1)^1]);
			}
			for ( top = tmp; top <= st+pos[x];) 
				i = *top++, flow[i>>1] += bot, flow[(i>>1)^1] -= bot;
		}
		putchar('C'), putchar('a'), putchar('s'), putchar('e'), putchar(' '), putnum(++cs), putchar(':');
		for ( x = 2*m+1; x <= 2*m+n; ++x ) {
			for ( res = 0, i = last[x]; i >= 0 && !res; i = next[i] )
				if ( flow[i] > 0 && (1 <= (y=to[i]) && y <= m) ) res += flow[i];
			putchar(' ');
			if ( !res ) putchar('0');
			else putnum(res);
		}
		puts("");
	}
	return 0;
}

