/*
 * 665. False Coin
 * TOPIC: logic, tricky interview question, IQ
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#define N 0x80
#include <vector>
using namespace std;

vector<int> v[2][N];
int m,n,len[N];
char res[N][4];
set<int> suspects,ans,Less,More;

int main() {
	int i,j,k,cs = 0,ts,t;
	bool ambi;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&m); ) {
		for ( k = 0; k < m; ++k ) {
			for ( i = 0; i < 2; v[i++][k].clear() );
			scanf("%d",len+k);
			for ( i = 0; i < 2; ++i )
				for ( j = 0; j < len[k]; ++j )
					scanf("%d",&t), v[i][k].push_back(t);
			scanf("%s",res[k]);
		}
		for ( Less.clear(), More.clear(), i = 1; i <= n; ++i )
			Less.insert(i), More.insert(i);
		for ( k = 0; k < m; ++k ) {
			set<int> l,r;
			for ( j = 0; j < len[k]; ++j )
				l.insert(v[0][k][j]), r.insert(v[1][k][j]);
			switch ( 0[res[k]] ) {
					case '=': for ( set<int>::iterator it = l.begin(); it != l.end(); ++it )
									 Less.erase(*it), More.erase(*it);
							  for ( set<int>::iterator it = r.begin(); it != r.end(); ++it )
									 Less.erase(*it), More.erase(*it);
							  break ;
					case '>': for ( set<int>::iterator it = l.begin(); it != l.end(); ++it )
									 Less.erase(*it);
							  for ( set<int>::iterator it = r.begin(); it != r.end(); ++it )
									 More.erase(*it);
							  break ;
					case '<': for ( set<int>::iterator it = l.begin(); it != l.end(); ++it )
									 More.erase(*it);
							  for ( set<int>::iterator it = r.begin(); it != r.end(); ++it )
									 Less.erase(*it);
							  break ;
			}
		}
		ans.clear();
		for ( set<int>::iterator it = Less.begin(); it != Less.end(); ++it )
			ans.insert(*it);
		for ( set<int>::iterator it = More.begin(); it != More.end(); ++it )
			ans.insert(*it);
		if ( ans.size() == 1 ) {
			set<int>::iterator it = ans.begin();
			printf("%d\n",*it);
		}
		else puts("0");
		if ( ts ) putchar('\n');
	}
	return 0;
}


