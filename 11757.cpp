/*
 * 11757. Winger Trial
 */
#include <iostream>
#include <set>
#include <map>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define N 0x80
#define Q (N*N*8)
#define S(x) ((x)*(x))
#define oo 0xfffffffful
#define is_active(x) (x!=src&&x!=sink&&label[x]<4*V&&excess[x]>0)
using namespace std;

int min(int x,int y) {return x<y?x:y;}
set<pair<int,int> > m;

int n,src,sink,len,wid,r,*head,*tail,q[Q],E,label[N],excess[N],
	to[Q],next[Q],last[N],cap[Q],seen[N],yes,V,cur[N],cx[N],cy[N];
unsigned int d[N];

void add_arcs( int x, int y, int c ) {
	int i,j;
	i = E++, j = E++, to[i] = y, cap[i] = c, to[j] = x, cap[j] = 0;
	next[i] = last[x], last[x] = i, next[j] = last[y], last[y] = j;
}

int bfs() {
	int i,j,x,y;
	for(x=src;x<=sink;d[x++]=+oo);
	for(head=tail=q,d[*tail++=sink]=0;head<tail;)
		for(i=last[x=*head++];i>=0;i=next[i])
			if (d[y=to[i]]>d[x]+1&&cap[i^1]&&(d[*tail++=y]=d[x]+1));
	return d[src]<+oo;
}

int dfs( int x, int df ) {
	int i,y,w;
	if ( x==sink )
		return df;
	for ( seen[x]=yes, i = last[x]; i >= 0; i = next[i] )
		if (d[y=to[i]]<+oo&&d[y]+1==d[x]&&cap[i]&&seen[y]!=yes)
			if (w=dfs(y,min(df,cap[i]))) {
				cap[i]-=w,cap[i^1]+=w;
				return w;
			}
	return 0;
}

int Push( int x ) {
	int i,y,pre,pos,delta;
	if ( !is_active(x) )
		return 0;
	if ( label[y = to[i = cur[x]]] != label[x]-1 )
		return 0;
	if ( !cap[i] )
		return 0;
	pre = is_active(y);
	delta = min(excess[x],cap[i]);
	excess[x]-=delta,excess[y]+=delta,cap[i]-=delta,cap[i^1]+=delta;
	pos = is_active(y);
	if ( !pre && pos ) *tail++ = y;
	return 1;
}

int Relabel( int x ) {
	int i,y;
	if ( !is_active(x) )
		return 0;
	label[x] = 4*V;
	for ( i = last[x]; i >= 0 ; i = next[i] ) {
		if ( !cap[i] )
			continue ;
		label[x] = min(label[x],label[to[i]]+1);
	}
	return 1;
}

void push_relabel( int x ) {
	if ( !Push(x) ) 
		if ( (cur[x] = next[cur[x]]) == -1 )
			cur[x] = last[x], Relabel(x);
}

int main() {
	int i,j,k,cs = 0,R,K;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for (;4==scanf("%d %d %d %d",&len,&wid,&n,&r)&&(len||r||wid||n);) {
		for ( m.clear(), i = 1; i <= n; ++i ) {
			scanf("%d %d",cx+i,cy+i),last[i]=-1;
			assert( cx[i] <= len );
			assert( cy[i] <= wid );
			if ( m.find(make_pair(cx[i],cy[i])) == m.end() )
				m.insert(make_pair(cx[i],cy[i]));
		}
		n = 0;
		for ( set<pair<int,int> >::iterator it = m.begin(); it != m.end(); ++it )
			cx[++n] = it->first, cy[n] = it->second;
		last[src = 0] = last[sink = n+1] = -1, V = n+2, E = 0, R = 4*r*r;
		for ( i = 1; i <= n; ++i ) {
			if ( wid-cy[i] < r ) 
				add_arcs(src,i,1);
			if ( cy[i] < r )
				add_arcs(i,sink,1);
		}
		for ( i = 1; i <= n; ++i )
			for ( j = i+1; j <= n; ++j )
				if ( cx[i]!=cx[j]||cy[i]!=cy[j] )
					if (S(cx[i]-cx[j])+S(cy[i]-cy[j])<R)
						add_arcs(i,j,1),add_arcs(j,i,1);
#if 1
		for(k=0;bfs();) for(++yes;i=dfs(src,(1<<29));k+=i);
		printf("Case %d: %d\n",++cs,k);
#else
		for ( i = src; i <= sink; ++i )
			excess[i] = 0, label[i] = 0, cur[i] = last[i];
		for(label[src]=V,i=last[src];i>=0;i=next[i])
			--cap[i], ++cap[i^1], ++excess[to[i]];
		for ( head = tail = q, i = 1; i <= n; ++i )
			if ( is_active(i) )
				*tail++ = i;
		while(head<tail) {
			for ( k = label[i = *head++]; excess[i]>0&&k == label[i]; push_relabel(i) );
			if ( is_active(i) ) *tail++ = i;
		}
		printf("Case %d: %d\n",++cs,excess[sink]);
#endif
	}
	return 0;
}

