/**
 * TOPIC: quadratic equations, brute force
 * status: Accepted
 */
#include <bits/stdc++.h>
using namespace std;
using i64= long long;

int N,m,n,p;
set<tuple<i64,i64,i64>> soln;

int main() {
    int i,j,k,cs= 0;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( ;cin >> N; ) {
        if ( N < 0 ) break ;
        cout << "Case " << ++cs << ":" << endl;
        if ( N == 1 ) {
            cout << "0 0 0" << endl;
            continue ;
        }
        if ( N == 2 ) {
            cout << "0 0 1" << endl;
            cout << "0 1 0" << endl;
            cout << "1 0 0" << endl;
            continue ;
        }
        assert( N >= 3 );
        soln.clear();
        for ( m= 0; m < 100; ++m )
            for ( p= 0; p < 100; ++p ) {
                i64 a= 1, b= 4*m+6*p-1, c= 2+2*m*(m-1)+3*p*(p-1)-N+6*m*p;
                i64 d= b*b-4*a*c;
                if ( d < 0 ) continue ;
                double s= sqrt(d);
                i64 is= (i64)(s+1e-7);
                if ( is*is != d ) continue ;
                for ( auto nn: {-b+is,-b-is} )
                    if ( (nn%(2*a)) == 0 )
                        if ( nn/(2*a) >= 0 )
                            if ( nn/(2*a) < 20000 )
                                soln.insert(make_tuple(m,nn/(2*a),p));
            }
        if ( soln.empty() ) {
            cout << "Impossible." << endl;
            continue ;
        }
        //for ( auto [x,y,z]: soln )
        for ( auto it: soln )
            cout << get<0>(it) << " " << get<1>(it) << " " << get<2>(it) << endl;
    }
    return 0;
}

