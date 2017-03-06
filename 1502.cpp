/*
 * 1502. GRE Words
 * TOPIC: trie, dp, longest path in DAG, aho-corasick
 * status: in progress
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <set>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;
#define A 26
#define BIT(k) (1ull << (k))
#define TST(u,k) (((u)>>(k))&1ULL)
#define N (1<<21)
#define oo (1<<29)

char s[N],*ptr;
int w[N],n,z[N],pref[N],curlen,len[N],last[N],to[N],next[N],E;
struct cell {
	cell *son[A],*slink,*p;
	//set<int> idx;
	vector<int> idx;
	cell( cell *p ) {
		for ( int i = 0; i < A; ++i ) son[i] = NULL; 
		idx.clear(), this->p = p, this->slink = NULL;
	};
	cell() {};
};

cell *sink,pool[N],*qtr;

void push( cell *root, char *s, int id ) {
	cell *x;
	for ( x = root; x && *s; x = x->son[*s++-'a'] )
		if ( !x->son[*s-'a'] )
			x->son[*s-'a'] = qtr++;
	//x->idx.insert(id);
	x->idx.push_back(id);
};

int calc_z( int x ) {
	if ( z[x] > -oo ) return z[x];
	for ( int y,i = last[x]; i >= 0 && (y=to[i]) >= 0; i = next[i] ) 
		z[x] = max(z[x],max(w[x]+calc_z(y),calc_z(y)));
	return z[x] = max(z[x],max(w[x],0));
};

cell *q[N],**head,**tail;

void bfs( cell *src ) {
	cell *x,*y,*z;
	int i;
	for ( head=tail=q,*tail++=src; head<tail; )
		for ( x = *head++, i = 0; i < A; ++i )
			if ( y = x->son[i] ) {
				for ( z = x->slink; z && !z->son[i]; z = z->slink );
				assert( z );
				y->slink = z->son[i], *tail++=y;
				//for ( set<int>::iterator it = y->slink->idx.begin(); it != y->slink->idx.end(); y->idx.insert(*it++) );
				for ( int l = 0; l < (int)y->slink->idx.size(); y->idx.push_back(y->slink->idx[l++]) );
			}
};

void add_arcs( int x, int y ) {
	int i = E++;
	to[i] = y, next[i] = last[x], last[x] = i;
}

void walk_down( cell *root, char *s, int id ) {
	for ( cell *x = root; *s; ) {
		assert( x->son[*s-'a'] );
		x = x->son[*s++-'a'];
		// for ( set<int>::iterator it = x->idx.begin(); it != x->idx.end() && *it < id; add_arcs(*it++,id) );
		for ( int l = 0; l < (int)x->idx.size() && x->idx[l] < id; add_arcs(x->idx[l++],id) );
	}
};

int main() {
	int i,j,k,l,t,cs=0,ts;
	cell *root;
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; printf("%d\n",k) ) {
		printf("Case #%d: ",++cs);
		for ( scanf("%d\n",&n), i = 0; i < n; z[i] = -oo, last[i++] = -1 );
		for ( qtr = pool, root = qtr++, i = 0; i < A; root->son[i++] = NULL );
		for ( root->slink = sink = qtr++, i = 0; i < A; sink->son[i++] = root );
		for(curlen=0,i=0;i<n;scanf("%s %d",s+curlen,w+i),push(root,s+curlen,i),pref[i]=curlen,len[i]=strlen(s+curlen),curlen+=len[i++]);
		E = 0, bfs(root);
		for ( i = 0; i < n; ++i ) {
			j = s[pref[i]+len[i]], s[pref[i]+len[i]] = '\0';
			walk_down(root,s+pref[i],i);
			s[pref[i]+len[i]] = j;
		}
		for ( k = -oo, i = n-1; i >= 0; k = max(k,calc_z(i--)) );
	}
    return 0;
}


