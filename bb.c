/*
 * 11647. Judgement Day
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 0x80*2
#define MAXE (MAXV*8)
typedef long long i64;
#include <float.h>
#define oo (DBL_MAX-1024)

i64 min(i64 x,i64 y) {return x<y?x:y;}
i64 max(i64 x,i64 y) {return x>y?x:y;}

int ts,cs,demand[MAXV],last[MAXV],E,V,m,n,isdig[256],src = 0,
	next[MAXE],to[MAXE],seen[MAXE],yes,prev[MAXV],it,olla[MAXV][MAXV],
	pos[MAXV],st[MAXV],*head,*top,satisfied[MAXV],id[MAXV],par[MAXV][MAXV];

i64 cap[MAXE],flow[MAXE],cost[MAXE],Total,lower_bound[MAXE],
	Inf,curr[MAXV],delta[MAXV][MAXV];
double mu;

char unneeded[MAXV];

void add_arcs( int x, int y, i64 c, i64 w, i64 lb ) {
	int i = E++, j = E++;
	assert( lb <= c );
	to[i] = y, next[i] = last[x], last[x] = i, cap[i] =  c,  cost[i] =  w, flow[i] = 0, lower_bound[i] = lb;
	to[j] = x, next[j] = last[y], last[y] = j, cap[j] = -lb, cost[j] = -w, flow[j] = 0, lower_bound[j] = -c;
}

int karp( int *rx, int *rk ) {
	int i,j,k,x,y,xx,kk;
	double MU;

	for ( olla[1][0] = ++yes, delta[1][0] = 0, k = 1; k <= V; ++k ) {
		for ( i = 0; i < E; ++i ) {
			x = to[i^1], y = to[i];
			if ( olla[x][k-1] != yes )
				continue ;
			if ( flow[i^1]>lower_bound[i^1] && (olla[y][k] != yes||delta[y][k]>delta[x][k-1]+cost[i]) )
				delta[y][k]=delta[x][k-1]+cost[i], par[y][k] = 0|(i<<1), olla[y][k] = yes;
			if ( flow[i]<cap[i] && (olla[y][k] != yes||delta[y][k]>delta[x][k-1]+cost[i]) )
				delta[y][k]=delta[x][k-1]+cost[i], par[y][k] = 1|(i<<1), olla[y][k] = yes;
		}
	}
	for ( mu = +oo, x = 1; x <= V; ++x )
		if ( olla[x][V] == yes ) {
			for ( MU = -oo, k = 0; k <= V-1; ++k )
				if ( olla[x][k] == yes )
					if ( (delta[x][V]-delta[x][k]+.00)/(V-k) > MU )
						MU = (delta[x][V]-delta[x][k]+.00)/(V-k), j = k;
			if ( MU < mu )
				mu = MU, kk = j, xx = x;
		}
	if ( mu < 0 ) {
		*rx = xx, *rk = kk;
		return 1;
	}
	return 0;
}

void inc_flow( int x, int y, i64 df ) {
	int i;
	for ( i = last[x]; i >= 0 && !(to[i] == y && cap[i] > 0); i = next[i] );
	assert( i >= 0 );
	assert( to[i] == y );
	assert( flow[i] <= cap[i]-df );
	assert( flow[i^1]-df >= lower_bound[i^1] );
	flow[i] += df, flow[i^1] -= df;
	if ( lower_bound[i] > 0 && 1 <= x && x <= m && 1+m <= y && y <= 2*m ) {
		if ( flow[i] >= lower_bound[i] )
			satisfied[x] = yes;
		else curr[x] = flow[i];
	}
}

i64 getnum() {
	i64 n = 0,ch;
	while ( (ch = getchar()) != EOF && !isdig[ch] );;
	for ( n = ch-'0'; (ch = getchar()) != EOF && isdig[ch]; )
		n = (n<<1)+(n<<3)+(ch-'0');
	return n;
}

void putnum( i64 n ) { (n<10)?(putchar(n+'0')):(putnum(n/10),putchar((n%10)+'0')); }

#if 0
int dijkstra() {
	int x,y,i,o[MAXV],*ptr = o;

	memset(in,0,sizeof(in));
	for ( cnt = 0, sen[1] = ++yes, push(1); cnt; ) {
		extracted[x = pop()] = yes;
		for ( i = last[x]; i >= 0; i = next[i] ) {
			y = to[i];
			if ( flow[i^1]>lower_bound[i^1] && (seen[y]!=yes||d[y]>d[x]+pi[x]-pi[y]-cost[i^1]) ) {
				if ( seen[y] != yes ) *ptr++ = y;
				seen[y] = yes;
				d[y] = d[x]+pi[x]-pi[y]-cost[i^1];
				push(y);
			}
			if ( flow[i] < cap[i] && (seen[y]!=yes||d[y]>d[x]+pi[x]-pi[y]+cost[i]) ) {
				if ( seen[y] != yes ) *ptr++ = y;
				seen[y] = yes;
				d[y] = d[x]+pi[x]-pi[y]+cost[i];
				push(y);
			}
		}
	}
	for (;--ptr >= o; pi[*ptr] += d[*ptr] );
}
#endif

int main() {
	int i,j,k,l,t,x,y,*tmp,left[MAXV],right[MAXV],gen[MAXV],flag,rx,rk;
	i64 bot,fcost,G,res,dd,W;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = '0'; i <= '9'; ++i ) isdig[i] = 1;
	for ( ts = getnum(); ts-- && ++yes; ) {
		n = getnum(), m = getnum();
		E=0,V=2*m,Total=0;
		for ( i = src; i <= V; ++i ) last[i] = -1;
		for ( i = 1; i <= m; ++i ) 
			Total+=(demand[i]=getnum());
		Inf = n*Total;
		for ( i = 1; i <= m; ++i )
			add_arcs(i,i+m,Inf,0,demand[i]);
		for ( i = 1; i <= m-1; ++i )
			add_arcs(i+m,i+1,Inf,0,0);
		memset(unneeded,0,sizeof(unneeded));
		memset(curr,0,sizeof(curr));
		for ( W = 0, i = 1; i <= n; ++i ) {
			k = getnum(), l = getnum(), t = getnum();
			/*if ( k > l ) j = k, k = l, l = j;*/
			if ( k > l )
				unneeded[i] = 1;
			left[i] = k, right[i] = l, gen[i] = t;
			W += t;
		}

		for ( i = 1; i <= n; ++i )
			if ( !unneeded[i] )
				for ( j = 1; j <= n; ++j )
					if ( i != j )
						if ( gen[i] <= gen[j] )
							if ( left[i] <= left[j] && right[j] <= right[i] )
								unneeded[j] = 1;

		do {
			for ( flag = 0, i = 1; i <= n; ++i )
				if ( !unneeded[i] )
					for ( j = 1; j <= n; ++j )
						if ( !unneeded[j] && i != j )
							if ( left[i] <= left[j] && left[j] <= right[i] && right[i] <= right[j] )
								for ( k = 1; k <= n; ++k )
									if ( !unneeded[k] && k != i && k != j )
										if ( gen[i] <= gen[k] && gen[j] <= gen[k] )
											if ( min(left[i],left[j]) <= left[k] && right[k] <= max(right[j],right[i]) )
												unneeded[k] = 1, flag = 1;
		} while ( flag );

		for ( x = 1; x <= n; ++x ) {
			if ( unneeded[i = x] ) 
				continue ;
			k = left[i], l = right[i], t = gen[i];
			for ( dd = 0, j = k; j <= l; ++j )
				if ( satisfied[j] != yes && dd < demand[j]-curr[j] )
					dd = demand[j]-curr[j];
			add_arcs(l+m,k,Inf,((i64)t),0);
			if ( !dd ) continue ;
			inc_flow(l+m,k,dd);
			for ( j = k; j < l; ++j )
				inc_flow(j,j+m,dd), inc_flow(j+m,j+1,dd);
			inc_flow(l,l+m,dd);
		}
		while ( karp(&rx,&rk) ) {
			for ( top = head = st+V+2, x = rx, k = V, ++yes; seen[x] != yes; --k ) {
				*--top = i = par[x][k], pos[x] = top-st, seen[x] = yes;
				x = to[(i>>1)^1];
			}
			for ( bot = Inf, tmp = top; top <= st+pos[x];) {
				i = *top++;
				if ( i&1 ) bot = min(bot,cap[i>>1]-flow[i>>1]);
				else bot = min(bot,flow[(i>>1)^1]-lower_bound[(i>>1)^1]);
			}
			assert( bot > 0 );
			for ( top = tmp; top <= st+pos[x];) {
				i = *top++;
				if ( flow[i>>1]+bot <= cap[i>>1] )
					flow[i>>1] += bot, flow[(i>>1)^1] -= bot;
			}
		}

		putchar('C'), putchar('a'), putchar('s'), putchar('e'), putchar(' '), putnum(++cs), putchar(':');
		for ( x = 1; x <= n; ++x ) {
			if ( unneeded[x] ) {
				putchar(' ');
				putchar('0');
				continue ;
			}
			for ( i = last[right[x]+m]; i >= 0 && !(to[i] == left[x] && cap[i] > 0); i = next[i] );
			putchar(' ');
			if ( i < 0 ) {
				putchar('0');
				continue ;
			}
			assert( i >= 0 );
			res = flow[i];
			if ( res <= 0 ) putchar('0');
			else putnum(res);
		}
		puts("");
	}
	return 0;
}

