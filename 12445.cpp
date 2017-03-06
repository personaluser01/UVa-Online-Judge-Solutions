/*
 * 12445. Happy 12
 * TOPIC: bfs
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <queue>
using namespace std;
typedef unsigned long long u64;
#define M 6
#define N 12
#include <map>
#define MOD (1ULL << 21)
#define SH 4
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define oo (1ULL<<29)

int n = 12;

map<u64,int> h[MOD];
map<u64,int> m[MOD];
queue<u64> q;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
		    std::stringstream ss(s);
			    std::string item;
				    while (std::getline(ss, item, delim)) {
							        elems.push_back(item);
									    }
					    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
		    std::vector<std::string> elems;
			    split(s, delim, elems);
				    return elems;
}

u64 p[M];

	u64 getItemAt( u64 u, int k ) { return (u>>(k*SH))&MASK(SH); }
	u64 setItemAt( u64 u, int k, u64 val ) {
		u &= ~(MASK(SH)<<(k*SH));
		u |= (val << (k*SH));
		return u;
	}
		u64 permFromArray( u64 *c ) {
			u64 u = 0;
			for ( int i = 0; i < n; ++i )
				u = setItemAt(u,i,c[i]);
			return u;
		}
		u64 permFromString( string s ) {
			u64 u = 0;
			vector<string> tokens = split(s,',');
			assert( tokens.size() == n );
			for ( int i = 0; i < n; ++i )
				u = setItemAt(u,i,atoi(tokens[i].c_str())-1);
			return u;
		}
		u64 Multiply( u64 u, u64 other ) {
			u64 v = 0;
			for ( int i = 0; i < n; ++i ) 
				v = setItemAt(v,i,getItemAt(other,(int)getItemAt(u,i)));
			return v;
		}

	int H( u64 p ) { return (int)(p & (MOD-1ULL)); }

	void bfs( u64 src, u64 lim ) {
		u64 i,j,k,w = +oo;
		for(;q.size()>0;q.pop());
		for ( i = 0; i < MOD; ++i ) m[i].clear();
		m[H(src)][src] = 0L; q.push(src);
		for(;q.size()>0;) {
			u64 u = q.front(),v; k = m[H(u)][u]; q.pop();
			if ( h[H(u)].find(u) != h[H(u)].end() ) {
				if ( h[H(u)][u]+k < w ) w = h[H(u)][u]+k;
				break ;
				continue ;
			}
			if ( k >= w ) continue ;
			for ( i = 0; k+lim <= 17 && i < M; ++i ) {
				v = Multiply(u,p[i]);
				if ( m[H(v)].find(v) == m[H(v)].end() ) 
				{ m[H(v)][v] = k+1; q.push(v); }
			}
		}
		printf("%llu\n",w<(1L<<29)?w:19);
		/*
		if ( w == +oo ) w = 19;
		for ( i = 0; i < MOD; ++i )
		for ( map<u64,int>::iterator it = m[i].begin(); it != m[i].end(); ++it )
			h[H(it->first)][it->first] = it->second;
		*/
	}

void display( u64 u ) {
	for ( int i = 0; i < n; ++i )
		printf("%llu ",getItemAt(u,i));
	puts("");
}

u64 them[0x80],cs;
#include <set>
set<u64> interest;

	u64 Target;
	void precalc( u64 lim ) {
		u64 i,j,k,ky;
		for ( i = 0; i < MOD; ++i )
			h[(int)i].clear();
		for(;q.size()>0;q.pop());
		h[H(Target)][Target]=0L; q.push(Target);
		for(;!q.empty();) {
			u64 u = q.front(),v; q.pop(); k = h[H(u)][u];
			/*if ( interest.find(u) != interest.end() ) {
				set<u64>::iterator it = interest.find(u);
				interest.erase(*it);
			}
			printf("%d\n",k);
			*/
			// display(u);
			for ( i = 0; k < lim && i < M; ++i ) {
				ky = H(v = Multiply(u,p[(int)i]));
				if ( h[ky].find(v) == h[ky].end() ) 
				{ h[(int)ky][v] = k+1; q.push(v); }
			}
		}
	}

	string a[] = {"2,3,4,5,6,12,7,8,9,10,11,1",
				  "12,1,2,3,4,5,7,8,9,10,11,6",
				  "1,2,3,4,5,12,6,7,8,9,10,11",
				  "1,2,3,4,5,7,8,9,10,11,12,6",
				  "2,3,4,5,6,7,8,9,10,11,12,1",
				  "12,1,2,3,4,5,6,7,8,9,10,11"};
	string T = 	  "1,2,3,4,5,6,7,8,9,10,11,12";

int main() {
	int i,j,k,ts;
	u64 c[N],b[N];
	Target = permFromString(T);
	for ( i = 0; i < M; ++i )
		p[i] = permFromString(a[i]);
	interest.clear();
	precalc(k = 9);
	for ( scanf("%d",&ts); ts--; ) {
		for ( i = 0; i < n; ++i ) 
			scanf("%llu",c+i), b[--c[i]] = i;
		interest.insert(them[cs++] = permFromArray(b));
		// bfs(permFromArray(b),k);
	}
	for ( i = 0; i < cs; ++i )
		bfs(them[i],k);
	/*
	for ( i = 0; i < cs; ++i )
		if ( h[H(them[i])].find(them[i]) == h[H(them[i])].end() )
			puts("19");
		else
			printf("%d\n",h[H(them[i])][them[i]]);
			*/
	return 0;
}

