//
// Created by sj on 13/09/19.
//
#include <bits/stdc++.h>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(u) ((u)&(~(u)+1ull))
using namespace std;
#define N 0x400
#define A 19

char which[1<<20],buff[N],layout[A+1];
const char *a= "_abcdefghilmnoprstu";
int id[256],w[A],target,c[A],len,pos[A],
    highest_freq[1<<A],sum_freq[1<<A],
    smallest_possible[1<<A],
    largest_possible[1<<A];
unsigned int present,same_frequency[N];

bool f( unsigned int covered, int i, int cur_cost ) {
    if ( i == len )
        return cur_cost == target;
    assert( i < len );
    if ( cur_cost > target )
        return false ;
    assert( i < len and covered != present );
    auto remaining= ~covered & present;
    if ( (target-cur_cost) < (i+1)*w[highest_freq[remaining]] )
        return false ;
    if ( (i+1)*sum_freq[~covered & present]+cur_cost > target )
        return false ;
    if ( A*sum_freq[~covered & present]+cur_cost < target )
        return false ;
    if ( sum_freq[remaining]*i+smallest_possible[remaining]+cur_cost > target )
        return false ;
    if ( sum_freq[remaining]*(A-__builtin_popcount(remaining))+largest_possible[remaining]+cur_cost < target )
        return false ;
    for ( unsigned int ch, prev= MASK(A+1), u= remaining; u; u&= ~same_frequency[prev= w[id[ch]]] ) {
        ch= a[which[L(u)]];
        assert( w[id[ch]] != prev );
        pos[id[layout[i] = ch]] = i;
        auto x = id[ch];
        if ( f(covered|L(u), i+1, cur_cost+(pos[x]+1)*w[x]) )
            return true;
    }
    return f(covered,i+1,cur_cost);
}

int main() {
    int i,j,k;
    unsigned int u,v;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( i= 0; i < 20; which[BIT(i)]= i, ++i ) ;
    for ( i= 0; a[i]; id[a[i]]= i, ++i ) ;
    for ( layout[A]= '\0' ;fgets(buff,sizeof buff,stdin) and 0[buff] != '*'; ) {
        for ( memset(w,0,sizeof w), i= 0; buff[i] and buff[i] != '\n'; ++w[id[buff[i++]]] ) ;
        for ( len= 0, present= 0, i= 0; buff[i] and buff[i] != '\n'; ++i )
            present|= BIT(id[buff[i]]);
        for ( u= present; u; u= (u-1)&present )
            for (highest_freq[u] = -1, v = u; v; v &= ~L(v))
                if (highest_freq[u] == -1 or w[highest_freq[u]] < w[which[L(v)]])
                    highest_freq[u] = which[L(v)];
        for ( u= 1; u < (1<<A); ++u )
            sum_freq[u]= sum_freq[u&~L(u)]+w[which[L(u)]];
        int indices[A];
        for ( u= 0; u < (1 << A); ++u ) {
            for ( k= 0, i= 0; i < A; ++i )
                if ( u & BIT(i) )
                    indices[k++]= i;
            sort(indices,indices+k,[&]( const auto &a, const auto &b )->bool {
                return w[a] < w[b];
            });
            smallest_possible[u]= largest_possible[u]= 0;
            for ( i= 0; i < k; ++i )
                largest_possible[u] += (i+1)*w[indices[i]];
            for ( j= 0, i= k-1; i >= 0; --i, ++j )
                smallest_possible[u]+= (j+1)*w[indices[i]];
            assert( smallest_possible[u] <= largest_possible[u] );
        }
        memset(same_frequency,0,sizeof same_frequency);
        for ( u= present; u; u&= ~L(u) )
            same_frequency[w[which[L(u)]]]|= L(u);
        for ( u= present; u; u&= ~L(u) )
            c[len++]= a[which[L(u)]];
        assert( len == __builtin_popcount(present) );
        sscanf(fgets(buff,sizeof buff,stdin),"%d",&target);
        u= (~present & MASK(A));
        if ( not f(0,0,0) )
            for ( i= 0; i < len; ++i )
                layout[i]= c[i];
        //else printf("Success\n")    ;
        for ( i= len; i < A; ++i )
            layout[i]= a[which[L(u)]], u&= ~L(u);
        printf("%s\n",layout);
    }
    return 0;
}

