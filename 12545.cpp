/*
 * 12545: Bits Equalizer
 * TOPIC: ad hoc, greedy, interview
 * status: Accepted
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    int i,j,k,ts,cs= 0;
    string s,t;
    for ( cin >> ts; ts--; ) {
        cin >> s >> t;
        int ones_required= 0, zeros_required= 0, qmarks= 0, o= 0;
        for ( k= 0, i= 0; i < s.size(); ++i )
            if ( s[i] == '?' ) {
                ++qmarks;
                if ( t[i] == '1' )
                    ++o;
            }
            else if ( s[i] != t[i] ) {
                if ( s[i] == '0' )
                    ++ones_required;
                else ++zeros_required;
            }
        auto swaps= min(ones_required,zeros_required);
        k= swaps;
        ones_required-= swaps, zeros_required-= swaps;
        if ( ones_required ) {
            assert( not zeros_required );
            k+= ones_required+qmarks;
        }
        else if ( zeros_required ) {
            assert( not ones_required );
            if ( zeros_required > o ) {
                k= -1;
                goto next;
            }
            swaps= zeros_required;
            k+= 2*swaps, k+= qmarks-swaps;
        }
        else {
            k+= qmarks;
        }
        next:;
        printf("Case %d: %d\n",++cs,k);
    }
    return 0;
}
