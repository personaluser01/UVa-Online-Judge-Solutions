/**
 * 10747: Maximum Subsequence
 * TOPIC: greedy, constructive
 * status:
 */
#include <bits/stdc++.h>
using namespace std;
#define N (10007)
using i64= int64_t;

int m,n;
vector<i64> c;
i64 pos_sum[N],neg_sum[N];
double dp[N],dn[N];

int main() {
    i64 i,j,k;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( ;(cin >> n >> m) and (m or n); ) {
        for ( c.clear(), i= 0; i < n; ++i ) {
            cin >> k, c.push_back(k);
            assert( -10000 <= k and k <= 10000 );
        }

        if ( m == n ) {
            cout << accumulate(begin(c),end(c),0,plus<i64>()) << endl;
            continue ;
        }

        auto sign= [](i64 x)-> int {
            return (x>0?2:x==0?0:1);
        };
        sort(begin(c),end(c),[&](i64 x, i64 y){
            return sign(x) > sign(y);
        });

        vector<i64>::iterator pos, end_pos, neg, end_neg, zero, end_zero;

        pos= find_if(begin(c),end(c),[](i64 x){ return x > 0;});
        end_pos= find_if(begin(c),end(c),[](i64 x){ return x <= 0;});
        if ( pos == end(c) ) end_pos= end(c);

        neg= find_if(begin(c),end(c),[](i64 x){ return x < 0;});
        end_neg= find_if(begin(c),end(c),[](i64 x){ return x == 0;});
        if ( neg == end(c) ) end_neg= end(c);

        zero= find_if(begin(c),end(c),[](i64 x){ return x == 0;});
        end_zero= end(c);

        auto by_abs= [](i64 x, i64 y) { return labs(x) > labs(y); };

        if ( pos < end_pos )
            sort(pos,end_pos,by_abs);
        if ( neg < end_neg )
            sort(neg,end_neg,by_abs);

        pos= find_if(begin(c),end(c),[](i64 x){ return x > 0;});
        end_pos= find_if(begin(c),end(c),[](i64 x){ return x <= 0;});
        if ( pos == end(c) ) end_pos= end(c);

        neg= find_if(begin(c),end(c),[](i64 x){ return x < 0;});
        end_neg= find_if(begin(c),end(c),[](i64 x){ return x == 0;});
        if ( neg == end(c) ) end_neg= end(c);

        zero= find_if(begin(c),end(c),[](i64 x){ return x == 0;});
        end_zero= end(c);

        for ( auto it= pos; it < end_pos; ++it ) {
            assert( begin(c) <= it and it < end(c) );
            assert( *it > 0 );
        }
        for ( auto it= neg; it < end_neg; ++it ) {
            assert( begin(c) <= it and it < end(c) );
            assert( *it < 0 );
        }
        for ( auto it= zero; it < end_zero; ++it ) {
            assert( begin(c) <= it and it < end(c) );
            assert( *it == 0 );
        }
#if 0
        for ( i= 0; i < n; ++i ) {
            cout << c[i] << " ";
            if ( i+1 == end_pos-pos )
                cout << "|";
            else if ( i+1 == end_neg-pos )
                cout << "|";
        }
        cout << endl;
#endif

        int num_zeros= end_zero-zero, num_pos= end_pos-pos, num_neg= end_neg-neg;
        i64 ans= 0;

        // all zeros: nothing to think about
        if ( num_pos == 0 and num_neg == 0 ) {
            cout << 0 << endl;
            continue ;
        }

        // you absolutely have to take zeroes in
        if ( num_pos+num_neg < m ) {
            llx:
            for ( k= m; k>0 and pos < end_pos; --k, ans+= *pos++ ) ;
            for ( ;zero < end_zero and k>0; ++zero, --k ) ;
            for ( ;end_neg > neg and k>0; --k, ans+= *--end_neg ) ;
            cout << ans << endl;
            continue ;
        }

        // all non-negative: greedily take all top m positives,
        // and fill the rest with zeros
        if ( num_neg == 0 ) {
            for ( k= m; pos < end_pos and k>0; ans+= *pos++, --k ) ;
            cout << ans << endl;
            continue ;
        }

        // all negative: we should have enough of them (n >= m)
        // we take the top-m (by abs value) if m is even, and smallest m (by abs value)
        // if m is odd
        if ( num_neg == n ) {
            for ( k= m; neg < end_neg and k>0; --k, ans+= (m&1)?*--end_neg:(*neg++) ) ;
            cout << ans << endl;
            continue ;
        }

        if ( num_zeros == 0 ) goto nxx;

        if ( num_pos == 0 ) {
            // if there not enough negatives OR there is enough, but we are forced
            // to take an odd number of them: we fill our choice with zeroes
            if ( (num_neg < m) or (m&1) ) {
                assert( num_zeros >= 1 );
                for ( k= m-num_zeros; k>0 and end_neg > neg; --k, ans+= *--end_neg ) ;
                cout << ans << endl;
                continue ;
            }
            // otherwise, multiply together an even number of negatives to get the best product, hence the sum
            assert( num_neg >= m and !(m&1) );
            cout << accumulate(neg, neg + m, 0, plus<i64>()) << endl;
            continue ;
        }

        assert( num_pos > 0 and num_neg > 0 );

        nxx:
        if ( num_pos+num_neg == m ) {
            if ( num_zeros == 0 ) {
                assert( m == n );
                cout << accumulate(begin(c),end(c),0,plus<i64>()) << endl;
                continue ;
            }
            if ( 0 == (num_neg&1) ) {
                cout << accumulate(pos, end_pos, 0, plus<i64>()) + accumulate(neg, end_neg, 0, plus<i64>()) << endl;
                continue ;
            }
            goto llx;
        }

        assert( num_pos+num_neg > m );
        pos_sum[0]= 0;
        for ( auto pt= pos; pt < end_pos; ++pt ) {
            pos_sum[pt-pos+1]= pos_sum[pt-pos] + *pt;
            dp[pt-pos+1]= log(*pt)+dp[pt-pos];
        }
        neg_sum[0]= 0;
        for ( auto nt= neg; nt < end_neg; ++nt) {
            assert( *nt < 0 );
            neg_sum[nt-neg+1]= neg_sum[nt-neg] + *nt;
            if ( !((nt-neg+1)&1) and (nt-neg+1) >= 2 )
                dn[nt-neg+1]= log(*(nt) * *(nt-1)) + dn[nt-neg-1];
        }
        i64 best_sum= numeric_limits<i64>::min();
        double best_prod= numeric_limits<double>::min();
        bool flag= false;
        for ( auto nt= neg; nt <= end_neg; nt+= 2 ) {
            if ( m < nt-neg ) continue ;
            auto pt= pos+(m-(nt-neg));
            if ( pt > end_pos or not (pt >= pos) ) continue ;
            assert( pt <= end(c) );
            assert( nt <= end(c) );
            assert( neg <= nt and nt <= end_neg );
            assert( pos <= pt and pt <= end_pos );
            assert( (pt-pos)+(nt-neg) == m );
            assert( pt <= end_pos and nt <= end_neg );
#if 0
            cout << "Considering: " << endl;
            for ( auto ppt= pos; ppt < pt; ++ppt )
                cout << *ppt << " ";
            cout << "| ";
            for ( auto nnt= neg; nnt < nt; ++nnt )
                cout << *nnt << " ";
            cout << endl;
            cout << "Product: " << dp[pt-pos]+dn[nt-neg] << endl;
            cout << "Sum: " << pos_sum[pt-pos]+neg_sum[nt-neg] << endl;
#endif
            //[neg,nt), [pos,pt)
            assert( 0 == ((nt-neg) & 1) );
            if ( (not flag) or dp[pt-pos]+dn[nt-neg] > best_prod or \
                 (fabs(dp[pt-pos]+dn[nt-neg]-best_prod) < 1e-7 and pos_sum[pt-pos]+neg_sum[nt-neg] > best_sum) ) {
                 best_prod= dp[pt-pos]+dn[nt-neg];
                 best_sum= pos_sum[pt-pos]+neg_sum[nt-neg];
                 flag= true ;
            }
        }
        assert( best_sum != numeric_limits<i64>::min() );
        cout << best_sum << endl;
    }
    return 0;
}
