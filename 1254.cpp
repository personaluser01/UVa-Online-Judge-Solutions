/*
 * 1254. Top 10
 * TOPIC: aho-corasick
 * status: Accepted
 */
#include <cassert>
#include <iostream>
#include <algorithm>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define N (1 << 18)
#define A 26
using namespace std;

int n,qr;
char s[1<<17];

typedef struct myword {
	char *s;
	size_t len;
	int idx;
	myword( char *a, int idx ) {
		this->len = strlen(a);
		this->s = (char *)malloc((this->len+1)*sizeof *(this->s));
		strcpy(this->s,a);
		this->idx = idx;
	}
	myword() {this->s=NULL;this->len=0;}
} myword;

myword w[N];

bool operator < ( const myword &x, const myword &y ) {
	if ( x.len==y.len ) {
		int i;
		if ( 0==(i=strcmp(x.s,y.s)) )
			return x.idx<y.idx;
		return i<0;
	}
	return x.len<y.len;
}

typedef struct cell {
	struct cell *p,*link,*son[A];
	set<myword *> s;
	cell ( cell *pp ) {
		this->s.clear(), this->link = NULL;
		for ( int i = 0; i < A; this->son[i++] = NULL );
		this->p = pp;
	}
} cell ;

cell *root,*sink;

void push( cell *root, myword *a ) {
	char *s = a->s;
	cell *x;
	for ( x = root; *s; x = x->son[*s++-'a'] ) 
		if ( !x->son[*s-'a'] ) 
			x->son[*s-'a'] = new cell(x);
	x->s.insert(a);
}

queue<cell *> q;
set<int> E[1<<21];

void bfs( cell *src ) {
	cell *x,*y,*z;
	int i;
	for ( q.push(src); !q.empty(); ) 
		for ( x = q.front(), q.pop(), i = 0; i < A; ++i )
			if ( y = x->son[i] ) {
				for ( q.push(y), z=x->link; !z->son[i]; z=z->link );
				for ( set<myword *>::iterator it=(y->link=z->son[i])->s.begin(); it!=y->link->s.end(); y->s.insert(*it++) );
			}
}

void traverse( cell *root, myword *r, int pos ) {
	char *s = r->s;
	int i;
	for ( cell *x = root; *s; ) {
		for(;!x->son[*s-'a'];x=x->link);
		x=x->son[*s++-'a'];
		for ( set<myword *> :: iterator it = x->s.begin(); it != x->s.end(); ++it ) {
			E[i = (*it)->idx].insert(pos);
			if ( E[i].size() > 10 ) {
				set<int> :: reverse_iterator jt = E[i].rbegin();
				E[i].erase(*jt);
			}
		}
	}
}

char qw[1 << 21];

int main() {
	int i,j,k;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	root = new cell(NULL), sink = new cell(NULL);
	for ( root->link = sink, i = 0; i < A; sink->son[i++] = root );
	for ( scanf("%d",&n), i = 0; i < n; ++i ) {
		scanf("%s",s), k = strlen(s), w[i].s = (char *)calloc(k+1,sizeof *w[i].s);
		w[i].len = k, strcpy(w[i].s,s), w[i].s[k] = '\0', w[i].idx = i;
	}
	for ( sort(w,w+n), k = 0, scanf("%d",&qr); qr-- && scanf("%s",qw); push(root,new myword((char *)qw,k)),E[k++].clear() );
	for ( bfs(root), i = 0; i < n; traverse(root,&w[i],i), ++i );
	for ( i = 0; i < k; ++i ) {
		j = 0;
		if ( E[i].size() == 0 ) { puts("-1"); continue ; }
		for ( set<int> :: iterator it = E[i].begin(); it != E[i].end() && j < 10; ++it, ++j ) {
			if ( j ) putchar(' ');
			printf("%d",w[*it].idx+1);
		}
		putchar('\n');
	}
	return 0;
}

