/*
 * 10045. Echo
 * TOPIC: simulation, bfs, bitmasks
 * status: Accepted
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>
#include <map>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <set>

#define N 0x400
#define M (11)
using namespace std;
using t_position= size_t;
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
using u64= unsigned long long;

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
    int ncur= cur,i= t,j,k,len;
    for ( auto it= precalc[ch][t+1]; it < end(pos[ch]); ++it ) {
        assert( s[*it] == ch );
        for ( ;i < *it and ncur-covered < M and ncur+1 < N; x[++ncur]= s[i++] ) ;
        if ( ncur-covered >= M ) break ;
        for ( j= covered+1, len= 0, k= *it; j <= ncur and k < n and x[j] == s[k] and len < M; ++j, ++k, ++len ) {
            if ( f(j,ncur,k+1) )
                return true ;
        }
    }
    return false ;
}

using t_state= pair<u64,unsigned short>;
set<t_state> Q;
queue<t_state> q;
#define symbol(u,i) (((u)>>(i*6))&63)
u64 E[256];
char imapping[64];

bool bfs() {
    t_state u{0,0},v;
    bool flag= false ;
    for ( Q.clear(), Q.insert(u), q.push(u); not q.empty(); ) {
        u= q.front(); q.pop();
        u64 str= (u.first >> 4);
        auto len= (u.first & 0xfull);
        auto idx= u.second;
        if ( idx == n ) {
            ok|= (len == 0);
            flag= true ;
        }
        auto ch= s[idx];
        if ( ch == imapping[symbol(str,0)] and len >= 1 ) {
            v= {(len-1) | ((str >> 6) << 4), idx+1};
            if ( Q.find(v) == Q.end() )
                Q.insert(v), q.push(v);
        }
        if ( len+1 < M ) {
            v= {(((E[ch] << (6*len)) | str) << 4) | (len+1), idx+1};
            if ( Q.find(v) == Q.end() )
                Q.insert(v), q.push(v);
        }
    }
    return flag;
}

int main() {
    int ts,i,j,k;
    vector<char> alphabet;
    /*
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
     */
    alphabet.clear();
    for ( auto ch= 'a'; ch <= 'z'; ++ch )
        alphabet.emplace_back(ch);
    for ( auto ch= 'A'; ch <= 'Z'; ++ch )
        alphabet.emplace_back(ch);
    for ( auto ch= '0'; ch <= '9'; ++ch )
        alphabet.emplace_back(ch);
    for ( i= 0; i < alphabet.size(); ++i )
        imapping[E[alphabet[i]]= i]= alphabet[i];
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
        if ( bfs() ) {
            if ( ok ) cout << out[0] << endl;
            else cout << out[1] << endl;
        }
        else cout << out[2] << endl;
    }
    return 0;
}

