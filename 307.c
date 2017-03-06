/*
 * 307. Sticks
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define L 51
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define B(k) ((k)&((~(k))+1ULL))
typedef unsigned long long u64;

int min( int x, int y ) {
    if ( x < y ) return x;
    return y;
}

int c[N],m,n,d,sum,cnt[L],sum_left,a[1<<14][L],is[50001],yes,maxlen,h[L+1][50100],indeed[2],T,aha[2][50100],seen[51000][L];
u64 ways[2][50100];
char which[1 << 22];
u64 u,mask[1 << 14],v;

int who( u64 u ) {
	if ( !u ) return L;
	if ( u < (1ULL<<21) )
		return which[u];
	if ( u < (1ULL<<42) )
		return 21+which[u>>21];
	return 42+which[u>>42];
}

char G( u64 x ) { if ( !x ) return 0; return 1; }

int f( int t, int curlen, int pos, int is_less ) {
	int k,i,j,ds;
    u64 w;

	if ( sum_left == 0 || sum_left == d )
		return 1;

	if ( curlen == d ) {
        assert( mask[t+1] == 0 );
		return f(t+1,0,who(B(u)),0);
    }

	if ( curlen>d || pos>=L || curlen+pos>d || is[d-curlen]!=yes )
        return 0;

	assert( cnt[pos] >= 1 );

    /* if ( !(rand()&31) ) return 0; */

    /*
    for ( ds = 0, w = (u&~MASK(pos+1)), j = pos; j < L; j = who(B(w)), w &= ~MASK(j+1) )
        ds += cnt[j]*j;
    if ( ds+curlen < d ) return 0;
    */

    i = is_less || (mask[t]&(mask[t]^mask[t-1]));
    for ( w = v, j = who(B(w)); j <= pos-1 && !i && w; w &= ~B(w), j = who(B(w)) ) {
        i |= (a[t][j]<a[t-1][j]);
        assert(i||a[t][j]==a[t-1][j]);
    }
    
    if ( i ) k = min(cnt[pos],(d-curlen)/pos+1);
    else { assert( t >= 1 ); k = min((d-curlen)/pos+1,min(a[t-1][pos],cnt[pos])); }
	/*for ( k = 0; k<=cnt[pos] && curlen+k*pos<=d && (i||k<=a[t-1][pos]); ++k ) {*/
	for(;k>=0;--k){
        if ( k > cnt[pos] || curlen+k*pos > d ) continue ;
        if ( h[who(B(u&~MASK(pos+1)))][d-curlen-k*pos] != yes )
            continue ;
		sum_left -= k*pos;
		if ( !(cnt[pos]-=(a[t][pos]=k)) ) u &= ~BIT(pos);
		if ( k ) mask[t] |= BIT(pos);
		if ( f(t,curlen+k*pos,who(B(u&~MASK(pos+1))),i||(k<a[t-1][pos])) ) {
			a[t][pos] = 0, sum_left += k*pos;
			mask[t] &= ~BIT(pos);
			if ( cnt[pos]+=k ) u |= BIT(pos);
			return 1;
		}
		sum_left += k*pos, a[t][pos] = 0;
		mask[t] &= ~BIT(pos);
		if ( cnt[pos]+=k ) u |= BIT(pos);
	}
	return 0;
}

int suspect( int d ) {
    int q = sum/d,k;
    for ( k = 1; k <= q; ++k )
        if ( aha[T][k*d] != indeed[T] || ways[T][k*d] < sum/(k*d) )
            return 0;
    return ways[T][d] >= sum/d;
}

int main() {
	int i,j,k,l,res;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( i = 0; i < 22; ++i ) which[1ULL<<i] = i;
	for (;1 == scanf("%d",&m) && m > 0 && ++yes; printf("%d\n",d) ) {
		for ( i = 0, n = 0; i < m; ++i ) 
			if ( 1 == scanf("%d",&k) && k < L && k > 0 && (c[n++] = k) );
		for ( sum = 0, i = 0; i < n; sum += c[i++] );
        for ( u = 0, k = 0; k < L; cnt[k++] = 0 );
		for ( i = 0; i < n; ++cnt[c[i++]] );
        for ( is[0] = yes, i = 0; i < n; ++i )
            for ( k = 0; k <= sum; ++k )
                if ( is[k] == yes )
                    is[c[i]+k] = yes;
        for ( m = 0, i = 1; i < L; ++i )
			for (;cnt[i]; c[m++] = i, --cnt[i] );
		assert( m == n );
        for ( i = 0, j = n-1; i < j; ++i, --j )
            k = c[i], c[i] = c[j], c[j] = k;

        for ( i = 0; i <= sum; ++i ) {
            ways[0][i] = ways[1][i] = 0;
            aha[0][i] = aha[1][i] = 0;
            indeed[0] = indeed[1] = 0;
        }

        for ( ways[T=0][0] = 1, aha[T][0] = ++indeed[T], i = 0; i < n; ++i )
            for ( ++indeed[T^=1], k = 0; k <= sum; ++k )
                if ( aha[T^1][k] == indeed[T^1] ) {
                    if ( aha[T][k] != indeed[T] )
                        aha[T][k] = indeed[T], ways[T][k] = ways[T^1][k];
                    else ways[T][k] += ways[T^1][k];
                    if ( aha[T][k+c[i]] != indeed[T] ) 
                        aha[T][k+c[i]] = indeed[T], ways[T][k+c[i]] = ways[T^1][k], seen[k+c[i]][c[i]] = yes;
                    else if ( seen[k+c[i]][c[i]] != yes ) ways[T][k+c[i]] += ways[T^1][k];
                }

        assert( aha[T][sum] == indeed[T] );
        assert( ways[T][sum] == 1 );
		for ( sum_left = sum, i = 0; i < n; u|=BIT(c[i++]), ++cnt[c[i-1]] );
        for ( i = L; i >= 2; --i )
            for ( h[i][0] = yes, k = 0; k <= sum; ++k )
                if ( h[i][k] == yes )
                    for ( j = 0; j <= cnt[i-1]; ++j )
                        h[i-1][k+j*(i-1)] = yes;
        for ( v = u, d = c[0]; d <= sum; ++d )
            if ( !(sum%d) && suspect(d) && f(0,0,who(B(u)),1) ) break ;
	}
	return 0;
}

