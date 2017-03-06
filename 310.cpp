/*
 * 310. L-System
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#define L 20
using namespace std;
#define FG fgets(buff,sizeof(buff),stdin)

set<string> seen;
string w[2],omega,T;
queue<string> q;
char buff[0x400];

string trans( char *a ) {
	string s = "";
	while ( *a && *a != '\n' )
		s += *a++;
	return s;
}

string derive( string s ) {
	string r = "";
	for ( int i = 0; i < (int)s.size(); r += w[s[i++]-'a'] );
	return r;
}

int main() {
	int i,j,k;
	string p,r;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( FG ) {
		w[0] = trans(buff);
		FG, w[1] = trans(buff);
		FG, omega = trans(buff);
		FG, T = trans(buff);
		q.push(omega), seen.clear(), seen.insert(omega);
		bool ok = false;
		while ( !q.empty() ) {
			p = q.front(), q.pop();
			if ( p.find(T) != string::npos ) {
				ok = true;
				break ;
			}
			r = derive(p);
			if ( r != "" && seen.find(r) == seen.end() ) 
				seen.insert(r), q.push(r);
		}
		while ( !q.empty() ) q.pop();
		if ( ok ) puts("YES");
		else puts("NO");
	}
	return 0;
}

