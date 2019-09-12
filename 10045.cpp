/*
 * 10045. Echo
 * TOPIC: simulation
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>
#include <map>
#include <algorithm>
#define N 0x400
#define M (11)
using namespace std;
using t_position= size_t;

string s;
size_t n;
const string out[]= {"An echo string with buffer size ten",
                     "Not an echo string, but still consistent with the theory",
                     "Not consistent with the theory"};
bool ok;
char x[N];
vector<t_position> pos[256];
vector<t_position>::iterator precalc[256][N];

bool f( int covered, int cur, int t ) {
    if ( t >= n ) {
        ok= covered == cur;
        return true ;
    }
    auto ch= x[covered+1];
    int ncur= cur,i= t,j,k;
    for ( auto it= precalc[ch][t+1]; it < end(pos[ch]); ++it ) {
        assert( s[*it] == ch );
        for ( ;i < *it and ncur-covered < M and ncur+1 < N; x[++ncur]= s[i++] ) ;
        if ( ncur-covered >= M ) break ;
        for ( j= covered+1, k= *it; j <= ncur and k < n and x[j] == s[k]; ++j, ++k ) {
            if ( f(j,ncur,k+1) )
                return true ;
        }
    }
    return false ;
}

int main() {
    int ts,i,j,k;
    vector<char> alphabet;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    alphabet.clear();
    for ( auto ch= 'a'; ch <= 'z'; ++ch )
        alphabet.emplace_back(ch);
    for ( auto ch= 'A'; ch <= 'Z'; ++ch )
        alphabet.emplace_back(ch);
    for ( auto ch= '0'; ch <= '9'; ++ch )
        alphabet.emplace_back(ch);
    for ( cin >> ts; ts--; ) {
        cin >> s; n= s.size();
        for ( const auto ch: alphabet )
            pos[ch].clear();
        for ( i= 0; i < n; ++i )
            pos[s[i]].push_back(i);
        for ( const auto ch: alphabet )
            if ( not pos[ch].empty() )
                for ( j= 0; j <= n; ++j )
                    precalc[ch][j]= lower_bound(begin(pos[ch]),end(pos[ch]),j);
        ok= false, x[0]= s[0];
        if ( f(-1,0,1) ) {
            if ( ok ) cout << out[0] << endl;
            else cout << out[1] << endl;
        }
        else cout << out[2] << endl;
    }
    return 0;
}

