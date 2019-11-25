/**
 * 11079: What Is The Time?
 * TOPIC: fast simulation, LCM, invariants
 * status: Accepted
 */
#include <bits/stdc++.h>
using namespace std;
#define N (12)
#define MAXL (55440)
using i64= long long;

i64 p[N],K,T,primes[]= {2,3,5,7,11};
vector<i64> level,c;
int n;

// the contribution of "i" at the end of moment "t", where t >= 0
i64 contrib( int i, int t ) {
    return (t/(2*p[i]))*c[i]*p[i] + c[i]*min(p[i],1+(t%(2*p[i])));
}

i64 simulate( int t ) {
    i64 ans= 0ll;
    for ( int i= 0; i < n; ans+= contrib(i++,t) ) ;
    return max(ans,0ll);
}

int main() {
    int i,j,k,t,cs= 0;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( ;cin >> n >> K; ) {
        if ( n == 0 and K == 0 ) break ;
        for ( c.resize(n), i= 0; i < n; cin >> p[i] >> c[i], ++i ) ;
        cin >> T;
        if ( T < K )
            swap(K,T), transform(c.begin(),c.end(),c.begin(),[](i64 x) { return -x; });
        assert( T >= K );
        // trivial case when we already have enough
        if ( T == K ) {
            cout << "Case " << ++cs << ": " << "0.00000000" << endl;
            continue ;
        }

        i64 LCM= [&] {
            int d[5]= {0};
            for ( int l= 0; l < n; ++l ) {
                auto pp= 2*p[l];
                for ( auto t= 0; t < 5; ++t ) {
                    int mx= 0;
                    for (;pp and not(pp%primes[t]); pp/= primes[t], ++mx ) ;
                    d[t]= max(d[t],mx);
                }
            }
            i64 ax= 1LL;
            for ( int t= 0; t < 5; ++t )
                for ( ;d[t]--; ax*= primes[t] ) ;
            return ax;
        }();
        assert( LCM <= MAXL );
        // simulation
        for ( level.resize(LCM), t= 0; t < LCM; level[t]= simulate(t), ++t ) ;
        // search inside the cycle
        assert( T > K );
        auto it= find_if(begin(level),end(level),[&]( i64 x ) {
            return max(0ll,K+x) >= T;
        });
        if ( it == end(level)  ) {
            auto itogo= max(0ll,level.back());
            if ( itogo == 0 or level.back() <= 0 ) {
                cout << "Case " << ++cs << ": " << "Impossible." << endl;
                continue ;
            }
            // determine the number of cycles needed
            auto jt= max_element(begin(level),end(level));
            assert( max(0ll,K+*jt) < T );
            auto num_needed_cycles= static_cast<i64>(ceil((T-max(0ll,*jt+K)+0.00)/itogo));
            assert( num_needed_cycles*itogo < T );
            assert( T <= num_needed_cycles*itogo + max(0ll,*jt+K) );
            T-= num_needed_cycles*itogo;
            jt= find_if(level.begin(),level.end(),[&](i64 x){
                return max(0ll,x+K) >= T;
            });
            assert( jt != end(level) );
            t= jt-begin(level);
            assert( t >= 0 and (t==0 or max(0ll,K+level[t-1]) < T) and T <= max(0ll,K+level[t]) );
            auto pre_level= t==0?K:max(0ll,K+level[t-1]);
            // find the time
            i64 volume= 0;
            for ( i= 0; i < n; ++i )
                volume+= [&] {
                    auto rem= (t % (2*p[i]));
                    return rem < p[i] ? c[i]:0;
                }();
            // at moment "t" volume of substance is being added
            cout << "Case " << ++cs << ": " << std::fixed << setprecision(8) << num_needed_cycles*LCM +
            t+(T-pre_level+0.00)/volume << endl;
        }
        else {
            // pinpoint the time
            t= it-begin(level);
            assert( t >= 0 and (t==0 or max(0ll,K+level[t-1]) < T) and T <= max(0ll,K+level[t]) );
            auto pre_level= t==0?K:max(0ll,K+level[t-1]);
            // find the time
            i64 volume= 0;
            for ( i= 0; i < n; ++i )
                volume+= [&] {
                    auto rem= (t % (2*p[i]));
                    return rem < p[i] ? c[i]:0;
                }();
            // at moment "t" volume of substance is being added
            cout << "Case " << ++cs << ": " << std::fixed << setprecision(8) << t+(T-pre_level+0.00)/volume << endl;
        }
    }
    return 0;
}

