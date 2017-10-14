/*
 * 11468. Substring
 * TOPIC: Aho-Corasick
 * status: Accepted
 */
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#define tol (1e-13)
using namespace std;
#define L(k) ((k)&((~(k))+1ULL))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
typedef unsigned long long u64;
#define A (26+26+10)
#define MAXNODES (20*21)
#include <queue>
#pragma comment( linker, "/STACK:1024000000,1024000000")
#define N 101

char which[1<<21],id[256];
int n;
double probability[A];
vector<int> available;

class ACmachine {
private:
	struct cell {
		cell *slink;
		double z[N];
		map<int,cell *> son;
		bool flag;
		cell() { memset(z,0,sizeof z), flag = false, slink = NULL, son.clear(); }
		bool is_terminal() const { return flag; }
		void set_terminal() { flag = true; }
		cell *find( int ch ) {
			if ( son.find(ch) != son.end() )
				return son[ch];
			return NULL;
		}
		cell *failure_transition( int ch ) {
			if ( find(ch) ) return find(ch);
			son[ch] = slink->failure_transition(ch);
			return find(ch);
		}
	} pool[MAXNODES], *ptr, *root, *q0;
	cell *init_node() {
		cell *x = ptr++;
		memset(x->z,0,sizeof (x->z));
		x->slink = NULL; x->son.clear(); x->flag = false;
		return x;
	}
	void add_son( cell *x, int ch ) { x->son[ch]=init_node(); }
	void add_son( cell *x, int ch, cell *y ) { x->son[ch]=y; }
public:
	ACmachine() {
		ptr = pool, root = init_node(), q0 = init_node(), root->slink = q0;
		for ( int i = 0; i < A; add_son(q0,i++,root) ) ;
		//assert( q0->u == MASK(A) );
	}
	void build() {
		queue<cell *> q;
		cell *x,*y,*z;
		u64 u;
		int ch;
		for ( ;!q.empty(); q.pop() );
		for ( q.push(root); !q.empty(); ) {
			map<int,cell *> :: iterator it;
			for ( x=q.front(), q.pop(), it = x->son.begin(); it != x->son.end();  ++it, q.push(y) ) {
				ch = it->first;
				y = x->find(ch);
				assert( y == it->second );
				//assert( y );
				for ( z = x->slink; z && !(z->find(ch)); z = z->slink ) ;
				//assert( z );
				//assert( z->find(ch) );
				y->slink = z->find(ch);
				if ( y->slink->is_terminal() )
					y->set_terminal();
			}
		}
	}
	void push( char *s ) {
		cell *x = root;
		char *p = s;
		for ( int ch; *s && (ch=id[*s++]) >= 0; x = x->find(ch) ) 
			if ( !(x->find(ch)) )
				add_son(x,ch);
		x->set_terminal();
	}
	double DP( int n ) {
		queue<pair<cell *,int> > q;
		cell *x,*y,*z;
		int i,j,k;
		u64 u;
		double ans = 0;
		for ( ;!q.empty(); q.pop() ) ;
		for ( root->z[0] = 1.00, q.push(make_pair(root,0)); !q.empty(); ) {
			pair<cell *,int> r = q.front(); q.pop();
			x = r.first, k = r.second;
			if ( k == n ) {
				ans += x->z[n];
				continue ;
			}
			//assert( k+1 <= n );
			for ( int l = 0; l < (int)available.size(); ++l ) {
				i = available[l];
				//assert( i < A );
				//assert( BIT(i) < 0xffffffffffffffffull );
				if ( NULL == x->find(i) ) {
						/*
					for ( z = x->slink; z && !z->find(i); z = z->slink ) ;
					assert( z );
					assert( z->find(i) );
					add_son(x,i,z->find(i));
					assert( x->find(i) );*/
					x->failure_transition(i);
				}
				y = x->find(i);
				//assert( y );
				if ( !y->is_terminal() ) 
					y->z[k+1] += probability[i]*(x->z[k]);
			}
			if ( q.empty() ) 
				for ( z = pool; z < ptr; ++z )
					if ( z->z[k+1] >= tol )
						q.push(make_pair(z,k+1));
		}
		return ans;
	}
	void init() {
		ptr = pool, root = init_node(), q0 = init_node(), root->slink = q0;
		for ( int i = 0; i < A; add_son(q0,i++,root) ) ;
		//assert( q0->u == MASK(A) );
	}
} ac;

int main() {
	int i,j,k,cs = 0,ts,K;
	char pattern[0x20];
	double tmp;
	for ( k = 0; k < 21; which[BIT(k)] = k, ++k ) ;
	memset(id,-1,sizeof id);
	for ( k = 0, i = '0'; i <= '9'; id[i++] = k++ ) ;
	for ( i = 'A'; i <= 'Z'; id[i++] = k++ ) ;
	for ( i = 'a'; i <= 'z'; id[i++] = k++ ) ;
	for ( scanf("%d",&ts); ts-- && 1 == scanf("%d",&K); ) {
		for ( ac.init(), i = 0; i < K; scanf("%s",pattern), ac.push(pattern), ++i ) ;
		memset(probability,0,sizeof probability), available.clear();
		for ( ac.build(), scanf("%d",&n), i = 0; i < n; ++i ) {
			scanf("%s %lf",pattern,&tmp);
			available.push_back(id[*pattern]);
			probability[id[0[pattern]]] = tmp;
		}
		scanf("%d",&n), printf("Case #%d: %lf\n",++cs,ac.DP(n));
	}
	return 0;
}

