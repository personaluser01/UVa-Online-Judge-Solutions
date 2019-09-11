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

bool f( int covered, int cur, int t ) {
    if ( t >= n ) {
        ok= cur == covered;
        return true ;
    }
    for ( int len,i,j,k= t, ncur= cur; ncur-covered < M and k < n; ++k ) {
        for ( len= 0, x[++ncur]= s[k], i= covered+1, j= k+1; j < n and i <= ncur and x[i] == s[j] and ++len; ++i, ++j ) ;
        if ( len and f(i-1,ncur,j) )
            return true ;
    }
    return false ;
}

int main() {
    int ts,i,j,k;
    for ( cin >> ts; ts--; ) {
        cin >> s; n= s.size();
        if ( f(-1,-1,0) ) {
            if ( ok ) cout << out[0] << endl;
            else cout << out[1] << endl;
        }
        else cout << out[2] << endl;
    }
    return 0;
}

