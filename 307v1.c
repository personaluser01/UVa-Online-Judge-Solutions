/*
 * 307. Sticks
 * status: Accepted
 * TOPIC: partitions, subset sum, DP, backtracking, lexicographical order, heuristics, bitmasks
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L 51
#define N 0x80
#define B(u) ((u)&((~(u))+1ULL))
typedef unsigned long long u64;
#define DBG 0

int min( int x, int y ) { 
    if ( x < y ) return x;
    return y;
}

char which[BIT(22)];
int m,n,sum,d,c[N],cnt[L],a[L*N][L],weight[L],K,buckets,
	left,h[L][N*L],yes,is_bad[L*N],
    quo[L],T,seen[2][L*N],indeed[2];

int who( u64 u ) {
    if ( !u || u >= BIT(K) ) return L;
    assert( !(u&(u-1UL)) );
    if ( u < BIT(21) )
        return which[u];
    if ( u < BIT(42) )
        return 21+which[u>>21];
    return 42+which[u>>42];
}

u64 u,v,mask[N],ways[2][L*N];

int cmp( const void *a, const void *b ) {
    int *x = (int *)a,
        *y = (int *)b;
    return -(*x)*cnt[*x] + (*y)*cnt[*y];
    if ( cnt[*x] > cnt[*y] ) return -1;
    if ( cnt[*x] < cnt[*y] ) return 1;
    return (*x)*cnt[*x] - (*y)*cnt[*y];
}

int suspect( int d ) {
    int k,q = sum/d;
    for ( k = 1; k*d <= sum; ++k )
        if ( seen[T][k*d] != indeed[T] || ways[T][k*d] < sum/(k*d) )
            return 0;
    return 1;
}

int max_possible_sum( int t, int pos ) {
    int i,j,k,l,s,best = 0;

    for ( i = pos; i < K; ++i )
        if ( a[t-1][i] ) {
            for ( s = 0, j = pos; j < i; ++j )
                s += a[t-1][j]*weight[j];
            for ( s += (a[t-1][i]-1)*weight[i], j = i+1; j < K; ++j )
                s += cnt[weight[j]]*weight[j];
            if ( s > best ) best = s;
        }
    return best;
}

int lex_less( int i, int j ) {
	int k;
	for ( k = 0; k < K; ++k )
		if ( a[i][k] != a[j][k] )
			return a[i][k] <= a[j][k];
	return 1;
}


int f( int t, int curlen, int pos, int is_equal ) {
    int i,j,k,res = 0;
    u64 w;

    if ( left == 0 || left == d ) return 1;
    
    if ( curlen == d ) {
        j = who(B(u));
#if DBG
		if ( d == 9 && sum == 162 && t == 12 ) {
			printf("%d %d\n",who(B(u)),!(mask[t]&MASK(j)));
		}
#endif
        k = f(t+1,0,j,!(mask[t]&MASK(j)));
#if DBG
        if ( !k ) {
            printf("[sum = %d, d = %d] Failure at t = %d, out of %d buckets\n",sum,d,t+1,buckets);
            for ( i = 0; i < K; ++i )
                printf("cnt[%d] = %d\n",weight[i],cnt[weight[i]]);
			for ( j = 0; j <= t; ++j ) {
				printf("[t = %02d] ",j); 
				for ( i = 0; i < K; ++i )
					printf("%d ",a[j][i]);
				puts("");
			}
			puts("----------------------------");
			for ( j = 0; j <= t-1; ++j )
				if ( !lex_less(j+1,j) ) {
					printf("Look at %d and %d\n",j,j+1);
					assert( 0 );
				}
        }
#endif
        return k;
    }

	/*
	if ( t == buckets-2 && d-curlen <= 2*(L-1) ) {
		for ( i = 1; i < L; ++i ) {
			if ( !((d-curlen) % i) && (d-curlen)/i <= cnt[i] )
				return 1;
			if ( cnt[i] && (j = d-curlen-i) < L )
				if ( i != j && cnt[j] ) return 1;
		}
	}
	*/

    if ( pos >= L || curlen > d || h[0][d-curlen] != yes ) return 0;

    if ( (buckets-t)*quo[pos] < cnt[weight[pos]] )
        return 0;

    assert( cnt[weight[pos]] >= 1 );
    assert( curlen < d );
    
    if ( !is_equal ) {
        for ( k = 0, i = pos; i < K; ++i )
            k += weight[i]*cnt[weight[i]];
        if ( k+curlen < d )
            return 0;
		for ( k = 1<<29, i = pos; i < K; ++i )
			if ( cnt[weight[i]] && weight[i] < k )
				k = weight[i];
		if ( curlen+k > d )
			return 0;
    }
	/*
    else {
        if ( max_possible_sum(t,pos)+curlen < d )
            return 0;
		for ( k = (1<<29), i = pos; i < K; ++i )
			if ( a[t-1][i] && cnt[weight[i]] && weight[i] < k )
				k = weight[i];
		if ( curlen+k > d )
			return 0;
    }
	*/

    k = min(cnt[weight[pos]],(d-curlen)/weight[pos]+2);
    if ( is_equal ) k = min(k,a[t-1][pos]);
    assert( k <= cnt[weight[pos]] );

    if ( !(u&MASK(pos)) && t>=1 && !(mask[t-1]&MASK(pos)) ) 
        i = cnt[weight[pos]]/(buckets-t);
    else i = 0;

    for ( ;k >= i; --k ) 
        if ( curlen+k*weight[pos] <= d ) {
            if ( curlen == 0 && !(u&MASK(pos)) && cnt[weight[pos]] > k*(buckets-t) ) 
                break ;
            if ( h[pos+1][d-curlen-k*weight[pos]] != yes )
                continue ;
            left -= k*weight[pos];
            if ( !(cnt[weight[pos]]-=(a[t][pos]=k)) )
                u &= ~BIT(pos);
            if ( k ) mask[t] |= BIT(pos);
            w = (u&~MASK(pos+1)), j = (who(B(w))-pos-1);
			assert( !(is_equal && a[t-1][pos] < k) );
			if ( k > a[t-1][pos] )
				assert( !is_equal );
            res = quo[pos]*(buckets-t-1)>=cnt[weight[pos]]&&f(t,curlen+k*weight[pos],who(B(w)),is_equal&&(t&&k==a[t-1][pos])&&!((MASK(j)<<(pos+1))&mask[t-1]) );
            left += k*weight[pos];
            if ( cnt[weight[pos]] += k )
                u |= BIT(pos);
            mask[t] &= ~BIT(pos), a[t][pos] = 0;
            if ( res ) return 1;
        }
    return 0;
}

int main() {
    int i,j,k,l,t,c0,best;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( i = 0; i < 22; ++i ) which[BIT(i)] = i;
    for (;1 == scanf("%d",&m) && m; printf("%d\n",d) ) {
        memset(cnt,0,sizeof cnt);
        for ( sum = 0, u = 0, c0 = -1, k = 0, i = 0, n = 0; i < m; ++i ) {
            assert( 1 == scanf("%d",&k) );
            if ( k < L && k > 0 ) {
                ++cnt[c[n++] = k], sum += k;
                if ( c0 < k ) c0 = k;
            }
        }
        for ( K = 0, i = 1; i < L; ++i )
            if ( cnt[i] ) weight[K++] = i;
        qsort(weight,K,sizeof *weight,cmp), u = MASK(K);
        for ( left = sum, best = sum, ++yes, i = K; i >= 1; --i )
            for ( h[i][0] = yes, ways[T][0] = 1ULL, T ^= 1, k = 0; k <= sum; ++k )
                if ( h[i][k] == yes )
                    for ( l = 0; l <= cnt[weight[i-1]]; ++l )
                        h[i-1][k+l*weight[i-1]] = yes;
        for ( T = 0, ways[T][0] = 1ULL, seen[T][0] = ++indeed[T], i = 0; i < n; ++i ) {
            for ( ++indeed[T^=1], k = 0; k <= sum; ++k )
                if ( seen[T^1][k] == indeed[T^1] )
                    seen[T][k] = indeed[T], ways[T][k] = ways[T^1][k];
            for ( k = 0; k <= sum; ++k )
                if ( seen[T^1][k] == indeed[T^1] ) {
                    if ( seen[T][k+c[i]] != indeed[T] )
                        seen[T][k+c[i]] = indeed[T], ways[T][k+c[i]] = ways[T^1][k];
                    else ways[T][k+c[i]] += ways[T^1][k];
                }
        }
        assert( seen[T][sum] == indeed[T] );
        assert( ways[T][sum] == 1 );
		/*
        for ( v = u, d = sum-1; d >= 1; --d ) {
           if ( (sum%d)||!suspect(d)||is_bad[d]==yes ) continue ;
            for ( i = 0; i < K; ++i ) quo[i]=d/weight[i];
            if ( f(0,0,0,0) ) {
                best = d;
                continue ;
            }
            else
                for ( k = 1; k <= d; ++k )
                    if ( !(d%k) ) is_bad[k] = yes;
        }
		*/
        for ( v = u, d = c0; d < best; ++d ) {
            /*
            for ( v = u; v; v &= ~B(v) )
                printf("%d %d %d\n",who(B(v)), weight[who(B(v))],cnt[weight[who(B(v))]] );
                */
            if ( (sum%d)||!suspect(d)||is_bad[d]==yes ) continue ;
            buckets = sum/d;
            for ( i = 0; i < K; ++i ) quo[i]=d/weight[i];
            if ( f(0,0,0,0) ) { best = d; break ; }
            assert( left == sum );
        }
        d = best;
    }
    return 0;
}

