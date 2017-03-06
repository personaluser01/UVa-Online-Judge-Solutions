/*
 * 425. Enigmatic Encryption
 * TOPIC: ad hoc
 * status: Accepted
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include <unistd.h>
using namespace std;

struct comp {
	bool operator() ( string a, string b ) {
		return a.size() < b.size();
	}
};

set<string> s;
char enc[0x400];
vector<string> vec,q;
string mid[] = {"0","2","4","8"};
string salt = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";

void generate_salt() {
	for ( int i = 0; i < salt.size(); ++i )
		for ( int j = 0; j < salt.size(); ++j ) {
			string t;
			t.push_back(salt[i]);
			t.push_back(salt[j]);;
			q.push_back(t);
		}
}

int next_word( char *c ) {
	int len = 0,ch;
	while ( (ch = getchar()) != EOF && !isalpha(ch) );
	if ( ch == EOF ) return len;
	for ( c[len++] = tolower(ch); (ch = getchar()) != EOF && isalpha(ch); c[len++] = tolower(ch) );
	c[len] = '\0';
	return len;
}

void solve() {
	int i,j,k,l;
	char c[0x400];
	scanf("%s",enc);
	string slq;
	slq.push_back(enc[0]);
	slq.push_back(enc[1]);
	for ( s.clear(); next_word(c); ) {
		string t(c);
		if ( t.size() <= 1 ) continue ;
		if ( t.size() >= 6 ) continue ;
		s.insert(t);
	}
	vec.clear();
	for ( set<string>::iterator it = s.begin(); it != s.end(); vec.push_back(*it++) );
	sort(vec.begin(),vec.end(),comp());
	for ( i = 0; i < (int)vec.size(); ++i )
		for ( j = 0; j < (int)vec.size(); ++j ) {
			if ( i == j ) continue ;
			if ( vec[i].size()+vec[j].size() >= 8 ) break ;
			if ( j > 0 ) assert(vec[j-1].size() <= vec[j].size());
			for ( k = 0; k < 4; ++k ) {
				string key = vec[i]+mid[k]+vec[j];
				char *passw = crypt(key.c_str(),slq.c_str());
				if ( 0 == strcmp(passw,enc) ) {
					printf("%s\n",key.c_str());
					return ;
				}
			}
		}
}

int main() {
	generate_salt(), solve();
	return 0;
}

