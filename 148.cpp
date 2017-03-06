/*
 * 148 Anagram Checker
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
using namespace std;

set<pair<string,multiset<char> > > s;
char buff[0x400],*ptr;
string T,sol[0x400];
multiset<char> target;
int tail;

bool read_dict() {
	int cnt[26] = {0};
	if ( !FG )
		return false;
	s.clear();
	if ( *ptr == '#' )
		return true;
	do {
		string str = "";
		for (;*ptr && *ptr != '\n'; ++cnt[*ptr-'A'], str += *ptr++ );
		multiset<char> m;
		m.clear();
		for ( int i = 'A'; i <= 'Z'; ++i )
			for (;cnt[i-'A']; --cnt[i-'A'], m.insert(i));
		s.insert( make_pair(str,m) );
	} while ( FG && *ptr != '#' );
	return true;
}

void f( multiset<char> cur, set<pair<string,multiset<char> > >::iterator it ) {
	set<pair<string,multiset<char> > >::iterator q;
	if ( cur == target ) {
		for ( int i = 0; i < tail; ++i ) {
			if ( i ) putchar(' ');
			printf("%s",sol[i].c_str());
		}
		putchar('\n');
		return ;
	}
	for ( q = it; q != s.end(); ++q ) {
		multiset<char> tmp;
		tmp.clear();
		for ( multiset<char>::iterator p = q->second.begin(); p != q->second.end(); ++p ) {
			tmp.insert(*p);
		}
		for ( multiset<char>::iterator p = cur.begin(); p != cur.end(); ++p ) {
			tmp.insert(*p);
		}
		sol[tail++] = q->first, f( tmp, q+1 ), --tail;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( read_dict() ) {
		while ( FG && *ptr != '#' ) {
			for ( target.clear(); *ptr && *ptr != '\n'; target.insert(*ptr++) );
		}
	}
	return 0;
}

