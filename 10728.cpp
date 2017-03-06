/*
 * 10728. Help!
 * status: Accepted
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
#include <map>
using namespace std;
enum { S = 0, T = 1 };
#define N 1024

char buff[2][0x400];
int n[2][2],g[N][N],yes,len[2];
map<string,int> m[2][2];
map<int,string> inv_map[2][2];
pair<int,char> v[2][N];
bool Apocalypse;

int Insert( int i, int t, string s ) {
	if ( m[i][t].find(s) == m[i][t].end() )
		inv_map[i][t][m[i][t][s] = n[i][t]++] = s;
	return m[i][t][s];
}

bool both_same() {
	int i;
	for ( i = 0; i < len[0]; ++i ) {
		if ( v[0][i].second != v[1][i].second )
			return false;
		if ( v[0][i].second == S )
			return false;
		if ( inv_map[0][T][v[0][i].first] != inv_map[1][T][v[1][i].first] )
			return false;
	}
	return true;
}

void change_double_placeholders() {
	int i,j,k,t[2],idx[2],
		fr[2];

	for ( i = 0; i < len[0]; ++i ) {
		t[0] = v[0][i].second, t[1] = v[1][i].second;
		fr[0] = v[0][i].first, fr[1] = v[1][i].first;
		if ( t[0] == t[1] && t[0] == S ) {
			for ( k = 0; k <= 1; ++k ) {
				idx[k] = Insert(k,T,string("foo"));
				v[k][i] = make_pair(idx[k],(char)T);
			}
			for ( j = 0; j < len[0]; ++j )
				for ( k = 0; k <= 1; ++k )
					if ( v[k][j].second == S && v[k][j].first == fr[k] )
						v[k][j] = make_pair(idx[k],(char)T);
			return ;
		}
	}
}

bool alter() {
	int i,j,k,t[2],new_idx,l,fr[2];
	bool ok = false;

	for ( i = 0; i < (int)len[0] && !ok; ++i ) {
		t[0] = v[0][i].second, t[1] = v[1][i].second;
		fr[0] = v[0][i].first, fr[1] = v[1][i].first;
		if ( t[0] == T && t[1] == T ) {
			if ( inv_map[0][T][v[0][i].first] != inv_map[1][T][v[1][i].first] ) {
				Apocalypse = true;
				return false;
			}
			continue ;
		}
		if ( t[0] != t[1] ) {
			if ( t[0] == T ) l = 0;
			else l = 1;
		}
		else continue ;
		new_idx = Insert(1-l,T,inv_map[l][T][v[l][i].first]);
		ok = true;
		for ( j = 0; j < (int)len[1-l]; ++j )
			if ( v[1-l][j].second == S && v[1-l][j].first == fr[1-l] )
				v[1-l][j] = make_pair(new_idx,(char)T);
	}
	return ok;
}

int main() {
	int i,j,k,t,cn,ts,l;
	char tmp[0x400];
	string str;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d\n",&ts); ts-- && ++yes; ) {		
		for ( t = 0; t < 2; ++t )
			for ( i = S; i <= T; ++i )
				m[t][i].clear(), n[t][i] = 0, inv_map[t][i].clear();
		for (t=0;t<2;++t) {
			fgets(buff[t],sizeof(buff[t]),stdin), len[t] = 0;
			for ( l = 0, cn = 0; *(buff[t]+cn) != '\n' && 1 == sscanf(buff[t]+cn,"%s%n",tmp,&j); cn += j, ++l ) {
				if ( tmp[0] == '\n' ) break;
				if ( 0[tmp] == '<' ) {
					str = string(tmp+1,strlen(tmp)-2), k = S;
				}
				else {
					str = string(tmp,strlen(tmp)), k = T;
				}
				if ( m[t][k].find(str) == m[t][k].end() )
					inv_map[t][k][m[t][k][str] = n[t][k]++] = str;
				v[t][l] =  make_pair(m[t][k][str],k);
			}
			len[t] = l;
		}
		if ( len[0] != len[1] ) {
			nx : puts("-");
			continue ;
		}
		for ( Apocalypse = false; !Apocalypse && !both_same(); ) {
			while ( alter() );
			if ( Apocalypse ) goto nx;
			change_double_placeholders();
		}
		if ( Apocalypse )
			goto nx;
		for ( i = 0; i < len[0]-1; ++i )
			printf("%s ",inv_map[0][T][v[0][i].first].c_str());
		printf("%s\n",inv_map[0][T][v[0][i].first].c_str());
	}
	return 0;
}

