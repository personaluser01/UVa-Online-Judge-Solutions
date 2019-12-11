/**
 * 10088. Trees on My Island
 * status: Accepted
 * TOPIC: Pick's theorem, STL, gcd
 */
#include <bits/stdc++.h>
#define N (0x400)
using i64= std::int64_t;
using t_coord= std::pair<i64,i64>;

int n;
std::vector<t_coord> c,d;

int main() {
#ifndef ONLINE_JUDGE
    freopen("10088.in","r",stdin);
#endif
    while ( (std::cin >> n) and n ) {
        assert( n >= 3 );
        c.resize(n);
        for ( auto &x: c )
            std::cin >> x.first >> x.second;
        // Area = I+B/2-1, I-interior, B-boundary
        d= c, std::rotate(std::begin(d),std::next(std::begin(d)),std::end(d));
        std::vector<i64> res;
        std::transform(c.begin(),c.end(),d.begin(),std::back_inserter(res),[]( const t_coord &a, const t_coord &b ) {
            return (a.first-b.first)*(a.second+b.second);
        });
        auto area= labs(std::accumulate(res.begin(),res.end(),0ll,[]( i64 acc, i64 x ) {
            return acc+x;
        }))/2;
        res.clear(), std::transform(c.begin(),c.end(),d.begin(),std::back_inserter(res),[]( const t_coord &a, const t_coord &b) {
            return std::__gcd(labs(a.first-b.first),labs(a.second-b.second))-1;
        });
        auto B= std::accumulate(res.begin(),res.end(),0ll,[]( i64 acc, i64 x ) {
            return acc+x;
        })+n;
        std::cout << (area+1)-B/2 << std::endl;
    }
    return 0;
}
