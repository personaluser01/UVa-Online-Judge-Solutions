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

#define M (11)
using namespace std;
using t_position= size_t;

string s;
size_t n;
const string out[]= {"An echo string with buffer size ten",
                     "Not an echo string, but still consistent with the theory",
                     "Not consistent with the theory"};
#define N 0x400
bool used[N];
bool ok;
map<char,vector<t_position>> pos;
t_position ipos[N];
int whose[N];
/*
 * i and j point to the next available positions to match
 */
bool case1( t_position i, t_position j, size_t matched_so_far )  {
    t_position t,l;
    /*
    if ( matched_so_far*2 == n )
        return i >= n or j >= n;
        */
    if ( j >= n ) {
        ok= matched_so_far*2 == n;
        return true ;
    }
    if ( j-i+1 > M or j < i or i >= n ) //FIXME
        return false ;
    //if ( matched_so_far*2+(n-i) < n )
    //    return false ;
    if ( i >= n or j >= n ) return false ;
    assert( not used[i] and not used[j] );
    //for ( t_position k= j; k < n and k-i+1 <= M; ++k )
    //for ( auto it= upper_bound(begin(pos[s[i]]),end(pos[s[i]]),i); it < end(pos[s[i]]); ++it ) {
    auto sz= pos[s[i]].size();
    const auto &mp= pos[s[i]];
    for ( auto it= ipos[i]+1; it < sz; ++it ) {
        auto k = mp[it];
        if ( k >= n or k - i + 1 > M ) break;
        if ( not used[k] ) {
            used[i] = used[k] = true;
            for (t = i + 1; t < n and used[t]; ++t);
            for (l = max(t, k) + 1; l < n and used[l]; ++l);
            if (case1(t, l, matched_so_far + 1))
                return true;
            used[i] = used[k] = false;
        }
    }
    return false ;
}

bool case2( t_position i, t_position j, size_t matched_so_far ) {
    t_position t,l;
    if ( j >= n )
        return true ;
    if ( j-i+1 > M or j < i or i >= n ) //FIXME
        return false ;
    if ( i >= n or j >= n ) return false ;
    assert( not used[i] and not used[j] );
    for ( auto it= upper_bound(begin(pos[s[i]]),end(pos[s[i]]),i); it < end(pos[s[i]]); ++it ) {
        auto k = *it;
        if (k >= n or k - i + 1 > M) break;
        if ((not used[k]) and s[i] == s[k]) {
            used[i] = used[k] = true;
            for (t = i + 1; t < n and used[t]; ++t);
            for (l = max(t, k) + 1; l < n and used[l]; ++l);
            if (case2(t, l, matched_so_far + 1))
                return true;
            used[i] = used[k] = false;
        }
    }
    return false ;
}

bool easy_check() {
    map<char,int> cnt;
    for ( const auto &c: s )
        if ( cnt.find(c) == cnt.end() )
            cnt[c]= 1;
        else ++cnt[c];
    for ( const auto &it: cnt )
        if ( it.second & 1 )
            return false ;
    return true ;
}

int main() {
    int ts,i,j,k;
    for ( cin >> ts; ts--; ) {
        cin >> s; n= s.size();
        pos.clear();
        for ( auto t= 0; t < s.size(); ++t ) {
            if ( pos.find(s[t]) == pos.end() )
                pos[s[t]].clear();
            pos[s[t]].push_back(t);
            ipos[t]= pos[s[t]].size()-1;
        }
        /*
        if ( not(n&1) and easy_check() and case1(0,1,0) )
            cout << out[0] << endl;
        else if ( case2(0,1,0) )
            cout << out[1] << endl;
        else cout << out[2] << endl;
         */
        ok= false;
        if ( case1(0,1,0) ) {
            if ( ok )
                cout << out[0] << endl;
            else cout << out[1] << endl;
        }
        else cout << out[2] << endl;
        memset(used,0,sizeof used);
    }
    return 0;
}

