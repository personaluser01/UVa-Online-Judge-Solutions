/*
 * 12678. Mixing Colours
 * TOPIC: cyk, probability, dp
 * status: Accepted
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <vector>
#define N 0x80
#define MAXK 0x200
#define FG (ptr = fgets(buff,sizeof buff,stdin))
#include <cfloat>
#define oo (DBL_MAX-0x400)
using namespace std;

map<string,int> m;
int rules,g[N][N],n,K;
char buff[0x400],*ptr;
vector<pair<int,double> > v[MAXK];
double z[MAXK][MAXK][N];
string nm[N];

int ins( string t ) {
	int V = m.size();
	if ( !m.count(t) )
		nm[m[t] = V++] = t;
	return m[t];
}

int main() {
	int i,j,k,l,t,ts,cs = 0,a,b;
	double prob,w;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("12678.in","r",stdin);
#endif
	for ( ;1 == scanf("%d",&rules) && rules; ) {
		if ( ++cs > 1 ) putchar('\n');
		memset(g,-1,sizeof g);
		for ( m.clear(), l = 0; l < rules; ++l ) {
			string tmp0,tmp1,tmp2;
			cin >> tmp0 >> tmp1 >> tmp2;
			i = ins(tmp0), j = ins(tmp1), k = ins(tmp2);
			assert( g[i][j] < 0 || g[i][j] == k );
			g[i][j] = k;
			swap(i,j);
			assert( g[i][j] < 0 || g[i][j] == k );
			g[i][j] = k;
		}
		for ( n = m.size(), scanf("%d",&ts); ts--; ) {
		    for ( scanf("%d\n",&K), i = 0; i < K; ++i ) 
				for ( FG, v[i].clear(); 1==sscanf(ptr,"%s%n",tmp,&j) && strcmp(tmp,"END"); ptr += j ) 
					sscanf(ptr+=j,"%lf%n",&prob,&j), k=ins(string(tmp)), v[i].push_back(make_pair(k,log(prob)));
			for ( i = 0; i < K; ++i )
				for ( j = 0; j < K; ++j )
					for ( t = 0; t < n; ++t )
						z[i][j][t] = -oo;
			for ( i = 0; i < K; ++i )
				for ( l = 0; l < (int)v[i].size(); ++l )
					z[i][i][v[i][l].first] = v[i][l].second;
			for ( k = 2; k <= K; ++k )
				for ( i = 0; (j=i+k-1) < K; ++i )
					for ( t = i; t <= j-1; ++t )
						for ( a = 0; a < n; ++a )
							if ( z[i][t][a] > -oo )
								for ( b = 0; b < n; ++b )
									if ( z[t+1][j][b] > -oo )
										if ( g[a][b] >= 0 )
											z[i][j][g[a][b]] = max(z[i][j][g[a][b]],z[i][t][a]+z[t+1][j][b]);
			for ( w = -oo, a = -1, t = 0; t < n; ++t )
				if ( z[0][K-1][t] > w )
					w = z[0][K-1][a = t];
			if ( a == -1 ) {
				puts("GAMEOVER");
				continue ;
			}
			printf("%s\n",nm[a].c_str());
		}
	}
	return 0;
}

