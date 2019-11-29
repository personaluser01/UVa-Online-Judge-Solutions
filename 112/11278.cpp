/**
 * 11278: Right-handed Typist
 * TOPIC: STL
 * status: Accepted
 */
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

const string qs= "`1234567890-=\tqwertyuiop[]\\asdfghjkl;'zxcvbnm,./ ";
const char *l=   "`1234567890-=\tqwertyuiop[]\\asdfghjkl;'zxcvbnm,./ ";
const string QS= "~!@#$%^&*()_+\tQWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ";
const char *L=   "~!@#$%^&*()_+\tQWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>? ";
const string ds= "`123qjlmfp/[]\t456.orsuyb;=\\789aehtdck-0zx,inwvg' ";
const char *r=   "`123qjlmfp/[]\t456.orsuyb;=\\789aehtdck-0zx,inwvg' ";
const string DS= "~!@#QJLMFP?{}\t$%^>ORSUYB:+|&*(AEHTDCK_)ZX<INWVG\" ";
const char *R=   "~!@#QJLMFP?{}\t$%^>ORSUYB:+|&*(AEHTDCK_)ZX<INWVG\" ";

map<char,char> q2d;

int main() {
#ifndef ONLINE_JUDGE
    freopen("11278.in","r",stdin);
#endif
    assert( qs == string(l) );
    assert( QS == string(L) );
    assert( ds == string(r) );
    assert( DS == string(R) );

    assert( qs.size() == QS.size() );
    assert( ds.size() == DS.size() );
    auto q= qs+QS, d= ds+DS;
    assert( d.size() == q.size() );
    for ( int i= 0; i < q.size(); ++i )
        q2d[q[i]]= d[i];
    for ( string s; getline(cin,s); ) {
        transform( s.begin(),s.end(), s.begin(), [&]( char x ) { return q2d[x]; } );
        cout << s << endl;
    }
    return 0;
}
