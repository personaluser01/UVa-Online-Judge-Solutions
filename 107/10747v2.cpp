/**
 * 10747: Maximum Subsequence
 * TOPIC: greedy, case analysis, STL
 * status: Accepted
 */
#include <bits/stdc++.h>
#include <iterator>
using namespace std;
#define N (10001)
using i64= int64_t;

vector<i64> c;
double dp[N];

struct state {
    bool has_value;
    pair<double,i64> val;
    state( bool f, double l, i64 s ): has_value(f), val{l,s} {}
};

template<typename RandomIter>
state f( RandomIter it1, RandomIter jt1, RandomIter it2, RandomIter jt2, int m ) {
    auto k= 0;
    double res= 0.00;
    i64 sum= 0ll;
    for ( ;it1+1 < jt1 and it2+1 < jt2; ) {
        if ( k == m or k == m-1 ) break ;
        auto &winner= (*it1 * *(it1+1)) >= (*it2 * *(it2+1))? it1:it2;
        res+= dp[*winner], res+= dp[*(winner+1)], k+= 2;
        if ( winner == it1 )
            sum+= *winner++, sum+= *winner++;
        else
            sum-= *winner++, sum-= *winner++;
    }
    for (;it1+1 < jt1 and k<m-1; res+= dp[*it1],res+= dp[*(it1+1)], sum+= *it1++, sum+= *it1++, k+= 2 ) ;
    for (;it2+1 < jt2 and k<m-1; res+= dp[*it2],res+= dp[*(it2+1)], sum-= *it2++, sum-= *it2++, k+= 2 ) ;
    if ( k == m ) return state(true,res,sum);
    if ( k == m-1 and it1+1 == jt1 ) {
        res+= dp[*it1], sum+= *it1++;
        return state(true,res,sum);
    }
    return state(false,res,sum);
}

pair<double,i64> take_zeroes( const vector<i64> &p, const vector<i64> &q, int n, int m ) {
    auto positives_taken= min(m,(int)p.size());
    auto how_many_zeros= n-p.size()-q.size();
    auto sum= accumulate(begin(p),min(begin(p)+m,end(p)),0ll);
    int what_is_left= (m-positives_taken)-how_many_zeros;
    if ( what_is_left >= 1 ) {
        assert( not q.empty() );
        assert( q.size() >= what_is_left );
        sum -= accumulate(q.rbegin(), q.rbegin()+what_is_left, 0ll);
    }
    return {numeric_limits<double>::min(),sum};
}

bool operator > ( const state &a, const state &b ) {
    if ( a.has_value and b.has_value )
        return a.val.first > b.val.first or (fabs(a.val.first - b.val.first) < 1e-7 and a.val.second > b.val.second);
    return a.has_value;
}

int main() {
    int i,j,k,m,n;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( i= 1; i < N; dp[i]= log(i), ++i ) ;
    for ( ;(cin >> n >> m) and (n or m); ) {
        c.resize(n);
        for ( auto &x: c ) cin >> x;
        sort(begin(c),end(c),[]( i64 x, i64 y ) { return labs(x) > labs(y); });
        vector<i64> p,q;
        copy_if(begin(c),end(c),back_inserter(p),[]( i64 x ) { return x > 0; });
        copy_if(begin(c),end(c),back_inserter(q),[]( i64 x ) { return x < 0; });
        transform(begin(q),end(q),begin(q),[](i64 x) { return -x; });

        if ( p.size() + q.size() == m ) {
            if ( !(q.size() & 1) or p.size()+q.size() == n ) {
                cout << accumulate(begin(p),end(p),0ll) - accumulate(begin(q),end(q),0ll) << endl;
                continue ;
            }
            cout << take_zeroes(p,q,n,m).second << endl;
            continue ;
        }
        // if we absolutely have to take zeroes
        if ( p.size()+q.size() < m ) {
            cout << take_zeroes(p,q,n,m).second << endl;
            continue ;
        }

        if ( p.empty() ) {
            if ( q.size() < m or (m&1) ) {
                cout << take_zeroes(p,q,n,m).second << endl;
                continue ;
            }
            assert( q.size() >= m and 0 == (m&1) );
            cout << -accumulate(begin(q),begin(q)+m,0ll) << endl;
            continue ;
        }
        if ( q.empty() ) {
            cout << accumulate(begin(p),min(begin(p)+m,end(p)),0ll) << endl;
            continue ;
        }

        assert( not p.empty() and not q.empty() );
        assert( p.size()+q.size() > m );

        auto res1= f(begin(p),end(p),begin(q),end(q),m);
        auto res2 = p.empty()?state(false,0,0):f(begin(p)+1,end(p),begin(q),end(q),m-1);
        if ( res2.has_value )
            res2.val.first+= dp[p.front()], res2.val.second+= p.front();
        auto result= res1;
        result= res2>result?res2:result;
        if ( p.size() + q.size() < n ) {
            auto with_zeroes= take_zeroes(p,q,n,m);
            auto candidate= state(true,with_zeroes.first,with_zeroes.second);
            if ( candidate > result )
                result= candidate;
        }
        cout << result.val.second << endl;
    }
    return 0;
}

