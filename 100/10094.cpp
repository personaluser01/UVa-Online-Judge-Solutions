/**
 * 10094: Place the Guards
 * TOPIC: spotting the pattern, constructive, STL
 * status: Accepted
 */
#include <bits/stdc++.h>
using namespace std;
#define N 0x1000

int n;
vector<int> a,b,sol;
bool diag[2][N], row[N], col[N];

namespace checker {
    bool diag[2][N], row[N], col[N];
    bool valid_assignment(const vector<int> &sol) {
        int n= sol.size(),i,j,k;
        memset(diag,0,sizeof diag);
        memset(row,0,sizeof row);
        memset(col,0,sizeof col);
        for ( j= 0; j < sol.size(); ++j ) {
            if ( row[sol[j]] ) return false ;
            row[sol[j]] = true ;
            if ( col[j+1] ) return false ;
            col[j + 1] = true ;
            if ( diag[0][j+1+sol[j]] )
                return false ;
            diag[0][j + 1 + sol[j]] = true ;
            if ( diag[1][j+1-sol[j]+0x400] )
                return false ;
            diag[1][j + 1 - sol[j] + 0x400] = true;
        }
        return true ;
    }
}

int main() {
    int i,j,k;
#ifndef ONLINE_JUDGE
    freopen("10094.in","r",stdin);
#endif
    for (;cin >> n;) {
        if ( n == 0 ) break ;
        memset(diag,0,sizeof diag);
        memset(row,0,sizeof row);
        memset(col,0,sizeof col);
        if ( n <= 3 ) {
            cout << "Impossible" << endl;
            continue ;
        }
        a.clear(), b.clear(), sol.clear();
        if ( (n%6) == 2 or (n%6) == 3 ) {
            // Find the value of k.
            k= n/6;
            // Then print form 2*k+2 ... upto n,
            a.resize(n), iota(a.begin(),a.end(),1);
            transform(a.begin(),a.end(),a.begin(),[&](int x){return 2*k+2*x;});
            auto it= remove_if(a.begin(),a.end(),[&](int x){ return x>n; });
            a.resize(distance(a.begin(),it));

            // then print 2, 4 ... upto 2*k.
            b.resize(k), iota(b.begin(),b.end(),1);
            transform(b.begin(),b.end(),b.begin(),[](int x){return 2*x;});
            sol= move(a), sol.insert(sol.end(),make_move_iterator(b.begin()),make_move_iterator(b.end()));

            for ( j= 0; j < sol.size(); ++j )
                row[sol[j]]= col[j+1]= diag[0][j+1+sol[j]]= diag[1][j+1-sol[j]+0x400]= true;

            vector<int> odds;
            odds.clear(), odds.resize(n), iota(odds.begin(),odds.end(),0);
            transform(odds.begin(),odds.end(),odds.begin(),[](int x){return 2*x+1;});
            it= remove_if(begin(odds),end(odds),[&](int x){return x>n;});
            odds.resize(distance(odds.begin(),it));
            // Check if 1, 3, ... is valid, if not then start from 3, 5, ..., if not start from 5, 7... and so on.
            for ( i= 0; i < odds.size(); ++i ) {
                bool flag= true ;
                for ( j= i, k= 0; k < odds.size() and flag; ++k, ++j, j%= odds.size() )
                    if ( diag[0][sol.size()+k+1+odds[j]] or diag[1][sol.size()+k+1-odds[j]+0x400] )
                        flag= false ;
                if ( flag ) {
                    rotate(odds.begin(),odds.begin()+i,odds.end());
                    break ;
                }
            }
            sol.insert(sol.end(),make_move_iterator(odds.begin()),make_move_iterator(odds.end()));
        }
        else {

            // Print 2, 4, 6 ... upto n
            a.clear(), a.resize(n), iota(a.begin(),a.end(),1);
            transform(a.begin(),a.end(),a.begin(),[](int x){return 2*x;});
            auto it= remove_if(a.begin(),a.end(),[&](int x){return x>n;});
            a.resize(distance(a.begin(),it));

            // then print 1, 3, 5 ... upto n, goto step 7.
            b.clear(), b.resize(n), iota(b.begin(),b.end(),0);
            transform(b.begin(),b.end(),b.begin(),[](int x){return 2*x+1;});
            it= remove_if(b.begin(),b.end(),[&](int x) { return x > n;});
            b.resize(distance(b.begin(),it));
            sol= move(a), sol.insert(sol.end(),make_move_iterator(b.begin()),make_move_iterator(b.end()));
        }
        assert( sol.size() == n );
        assert( checker::valid_assignment(sol) );
        for ( i= 0; i < sol.size(); ++i ) {
            if ( i ) cout << ' ';
            cout << sol[i];
        }
        cout << endl;
    }
    return 0;
}
