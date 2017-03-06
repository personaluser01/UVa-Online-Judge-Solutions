/*
 * 10194. Football (aka Soccer)
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string.h>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
#define FG(ptr) (fgets(ptr,sizeof(ptr),stdin))
#define N 0x20

char tname[0x80],buff[0x400];
string nm[N];
int n,g[2],gm,ts;

typedef struct {
	int score,wins,against,goals,games,id,losses;
} team;

bool operator<( const team &a, const team &b ) {
	if ( a.score == b.score ) {
		if ( a.wins == b.wins ) {
			if ( a.goals-a.against== b.goals-b.against ) {
				if ( a.goals == b.goals ) {
					if ( a.games == b.games ) {
						for ( int i = 0; i < (int)nm[a.id].size() && i < (int)nm[b.id].size(); ++i ) {
							int t =strcasecmp(nm[a.id].c_str(),nm[b.id].c_str());
							return t < 0;
						}
					}
					return a.games < b.games;
				}
				return a.goals > b.goals;
			}
			return a.goals-a.against> b.goals-b.against;
		}
		return a.wins > b.wins;
	}
	return a.score > b.score;
}

team T[N];
map<string,int> m;

int main() {
	char t[2][0x80],tmp[0x400];
	int i,j,k,cnt,x,y;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d\n",&ts); ts-- && FG(tname) && scanf("%d\n",&n); ) {
		m.clear();
		for ( i = 0; i < n; ++i )
			scanf("%[^\n]\n",tmp),m[nm[i]=string(tmp)]=i,T[i].id=i,T[i].score=T[i].losses=T[i].wins=T[i].goals=T[i].against=T[i].games=0;
		for ( scanf("%d\n",&gm), k = 0; k < gm; ++k ) {
			sscanf(FG(buff),"%[^#]#%d@%d#%[^\n]",t[0],g,g+1,t[1]);
			// printf("%s %s\n",t[0],t[1]);
			x = m[string(t[0])], y = m[string(t[1])];
			T[x].id = x, T[x].score += (g[0]>g[1]?3:(g[0]==g[1]?1:0));
			T[y].id = y, T[y].score += (g[1]>g[0]?3:(g[0]==g[1]?1:0));
			T[x].goals += g[0], T[y].goals += g[1], T[x].against += g[1], T[y].against += g[0];
			++T[x].games, ++T[y].games;
			T[x].wins += (g[0]>g[1]?1:0);
			T[y].wins += (g[1]>g[0]?1:0);
			T[x].losses += (g[1]>g[0]?1:0);
			T[y].losses += (g[0]>g[1]?1:0);
		}
		sort(T,T+n);
		printf("%s",tname);
		for ( i = 0; i < n; ++i ) {
			printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",i+1,nm[T[i].id].c_str(),T[i].score,T[i].games,T[i].wins,T[i].games-T[i].wins-T[i].losses,T[i].losses,T[i].goals-T[i].against,T[i].goals,T[i].against);
		}
		if ( ts ) putchar('\n');
	}
	return 0;
}
