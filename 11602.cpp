//
// Created by sj on 13/09/19.
// 11602: SMS for Blinds
// TOPIC: bitmasks, rearrangement inequality, bitwise operations, DP, pruning, backtracking
// status: Accepted
//
#include <bits/stdc++.h>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(u) ((u)&(~(u)+1ull))
using namespace std;
#define N 0x400
#define A 19
#define C 5

char which[1<<20],buff[N],layout[A+1],alphabet[A+1],bts[1<<20],kth[1<<A][A];
const char *a= "_abcdefghilmnoprstu";
int w[256],target,new_id[256],
    sum_freq[1<<A],
    smallest_possible[1<<A],
    largest_possible[1<<A];
unsigned int present,same_frequency[N];

bool f( unsigned int covered, int i, int cur_cost ) {
    auto remaining= ((~covered) & present);
    if ( not remaining )
        return cur_cost == target;
    if ( cur_cost > target )
        return false ;
    if ( A-i < bts[remaining] )
        return false ;
    if ( sum_freq[remaining]*i+smallest_possible[remaining]+cur_cost > target )
        return false ;
    if ( sum_freq[remaining]*(A-bts[remaining])+largest_possible[remaining]+cur_cost < target )
        return false ;
    assert( remaining );
    int low= i, high= A-bts[remaining], mid;
    assert( sum_freq[remaining]*high+largest_possible[remaining]+cur_cost >= target );
    int j= i;
#if 1
    if ( sum_freq[remaining]*low+largest_possible[remaining]+cur_cost >= target )
        j= low;
    else {
        assert( sum_freq[remaining]*low+largest_possible[remaining]+cur_cost < target );
        for ( ;low+1 < high; )
            sum_freq[remaining]*(mid=(low+high)/2)+largest_possible[remaining]+cur_cost >= target ? (high= mid):(low= mid);
        j= high;
    }
#endif
    assert( j < A );
    if ( sum_freq[remaining]*j+smallest_possible[remaining]+cur_cost > target )
        return false ;
    int sum_needed= target-cur_cost-sum_freq[remaining]*j;
    for ( int l= i; l <= j-1; layout[l++]= '\0' ) ;
    auto discarded= remaining & ~remaining;
    low= 0, high= bts[remaining]-1;
    unsigned int initial= remaining, rr= remaining&~BIT(kth[remaining][low]);
    if ( w[alphabet[kth[remaining][low]]]*(j+1)+sum_freq[rr]+smallest_possible[rr]+cur_cost <= target )
        initial= remaining;
    else {
        for (; low + 1 < high;) {
            mid = (low + high) / 2;
            rr = remaining & ~BIT(kth[remaining][mid]);
            if (w[alphabet[kth[remaining][mid]]] * (j + 1) + sum_freq[rr] + smallest_possible[rr] + cur_cost > target)
                low = mid;
            else high = mid;
        }
        initial= remaining & ~MASK(kth[remaining][high]);
    }
    for ( unsigned int ch, prev= MASK(A+1), u= initial; u;
            discarded|= (remaining&same_frequency[w[ch]]),
            u&= ~same_frequency[prev= w[ch]] ) {
        ch= alphabet[which[L(u)]];
        if ( w[ch]*(j+1)+sum_freq[remaining&~L(u)]*(j+1)+smallest_possible[remaining&~L(u)]+cur_cost > target )
            continue ;
        assert( w[ch] != prev );
        layout[j] = ch;
        auto x = new_id[ch];
        if ( w[ch]*(j+1)+sum_freq[remaining&~L(u)]*(j+1)+largest_possible[remaining&~L(u)]+cur_cost >= target ) {
            if (f(covered | L(u), j + 1, cur_cost + (j + 1) * w[ch]))
                return true;
        }
        else break ;
    }
    layout[j]= '\0';
    //return false ;
    return f(covered,j+1,cur_cost);
}

int main() {
    int i,j,k,l,n;
    unsigned int u,v;
    int absent[A];
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( i= 0; i < 20; which[BIT(i)]= i, ++i ) ;
    for ( u= 1; u < (1<<20); ++u )
        bts[u]= bts[u>>1]+(u&1);
    for ( u= 1; u < (1<<A); ++u )
        for ( kth[u][0]= which[L(u)], k= 1; k < bts[u]; ++k )
            kth[u][k]= 1+kth[u>>1][k-(u&1)];
    for ( layout[A]= '\0' ;fgets(buff,sizeof buff,stdin) and 0[buff] != '*'; ) {
        for ( n= 0, memset(w,0,sizeof w), i= 0; buff[i] and buff[i] != '\n'; ++w[buff[i++]], ++n ) ;
        for ( l= 0; a[l]; alphabet[l]= a[l], ++l ) ;
        sort(alphabet,alphabet+A,[&]( const char &x, const char &y)->bool {
            return w[x] < w[y];
        });
        for ( i= 0; i < A-1; ++i )
            assert(w[alphabet[i]] <= w[alphabet[i+1]]);
        for ( i= 0; i < A; ++i )
            new_id[alphabet[i]]= i;
        for ( present= 0, i= 0; buff[i] and buff[i] != '\n'; ++i )
            present|= BIT(new_id[buff[i]]);
        for ( u= 1; u < (1<<A); ++u )
            sum_freq[u]= sum_freq[u&~L(u)]+w[alphabet[which[L(u)]]];
        for ( u= 0; u < (1<<A); ++u ) {
            if ( u != (u&present) )
                continue ;
            if ( !(u&(u-1)) ) {
                largest_possible[u]= smallest_possible[u]= sum_freq[u];
                continue ;
            }
            v= u & ~L(u);
            largest_possible[u]= largest_possible[v]+sum_freq[v]+w[alphabet[which[L(u)]]];
            smallest_possible[u]= smallest_possible[v]+w[alphabet[which[L(u)]]]*(1+bts[v]);
            assert( smallest_possible[u] <= largest_possible[u] );
        }
        for ( i= 0; i <= n; same_frequency[i++]= 0 ) ;
        for ( u= present; u; u&= ~L(u) )
            same_frequency[w[alphabet[which[L(u)]]]]|= L(u);
        for ( i= 0, l= 0; i < A; ++i )
            if ( !(present & BIT(i)) )
                absent[l++]= i;
        sscanf(fgets(buff,sizeof buff,stdin),"%d",&target);
        assert( f(0,0,0) );
        for ( i= 0, l= 0; l < A; ++l )
            if ( !layout[l] )
                layout[l]= alphabet[absent[i++]];
        layout[A]= '\0', puts(layout);
    }
    return 0;
}

