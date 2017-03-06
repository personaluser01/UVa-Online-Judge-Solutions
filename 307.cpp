/*
 * 307. Sticks
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
using namespace std;
#define L 51
#define N (1L<<21)
typedef long long i64;
#define left 0
#define right 1
#define DBG 1

typedef struct cell { struct cell *nx[2]; int w; } cell ;
i64 sum_left;

void add_after( cell **item, int w ) {
    cell *p = (cell *)malloc(sizeof *p);
    p->w = w, p->nx[left] = p->nx[right] = p;
    if ( !(*item) ) *item = p;
    else {
        if ( p->nx[right] = (*item)->nx[right] )
            (*item)->nx[right]->nx[left] = p;
        p->nx[left] = (*item), (*item)->nx[right] = p;
    }
}

typedef struct {
    cell *head,*tail;
    size_t knt;
} dlist;

dlist *init() {
    dlist *d = (dlist *)malloc(sizeof *d);
    d->head = d->tail = NULL, d->knt = 0;
    return d;
}

void push( dlist *d, int w ) {
    add_after(&d->tail,w);
    if ( !d->knt++ )
        d->head = d->tail;
    else
        d->tail = d->tail->nx[right];
}

int n,m,c[N],K,deg[1 << 12],Q,t;
bool isprime[1 << 12];
i64 sum,p[1<<12],pr[1<<12],d[N];
map<i64,i64> q[2];
dlist *D;

void factorize( i64 n, i64 *pr, int *deg, int *m ) {
    *m = 0;
    for ( int i = 0; i < K && p[i] <= n; ++i ) {
        if ( n%p[i] ) continue ;
        for ( ++(*m), deg[*m-1] = 0, pr[*m-1] = p[i]; !(n%p[i]); ++deg[*m-1], n/=p[i] );
    }
    if ( n > 1 )
        ++(*m), pr[*m-1] = n, deg[*m-1] = 1;
}

void generate( i64 *pr, int *deg, const int m, int k, i64 n ) {
    i64 x,i;
    if (k==m) { d[Q++]=n; return; }
    assert( k < m );
    for ( x = 1LL, i = 0; i <= deg[k]; ++i, x *= pr[k] )
        generate(pr,deg,m,k+1,n*x);
}

bool f( const i64 len, int knt, i64 cur_len, cell *h ) {
    int k;
    i64 prev = -1;
    cell *ptr,*nx[2];

    if ( sum_left == len || !knt ) return true;

    if ( cur_len > len  ) return false;

    if ( cur_len == len ) return f(len,knt,0,h);
    // printf("knt = %d, cur_len = %lld\n",knt,cur_len);
    assert( cur_len < len );

    for ( k = knt, ptr = h; k-- > 0; prev = ptr->w, ptr = ptr->nx[right] ) {
        nx[left] = ptr->nx[left], nx[right] = ptr->nx[right];
        nx[right]->nx[left] = nx[left], nx[left]->nx[right] = nx[right];
        sum_left -= ptr->w;
        if ( ptr->w != prev && cur_len+ptr->w <= len && f(len,knt-1,ptr->w+cur_len,ptr==h?ptr->nx[right]:h) )
            return true;
        sum_left += ptr->w;
        nx[left]->nx[right] = nx[right]->nx[left] = ptr;
    }

    return false;

}

int main() {
    i64 i,j,k,low,high,mid;
    map<i64,i64> :: iterator it,qt;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( isprime[2] = true, i = 3; (i+=2) < (1<<12); isprime[i] = true );
    for ( i = 3; i < (1<<12); ++i )
        for ( j = i+i; isprime[i] && j < (1<<12); j += i )
            isprime[j] = false;
    for ( K = 0, i = 0; i < (1<<12); ++i )
        if ( isprime[i] )
            p[K++] = i;
    for ( i = 0; i < K; ++i )
        assert( p[i] >= 2 );
    for(;1==scanf("%d",&m)&&m>0;){
        for (n=i=0;i<m;++i) {
            scanf("%lld",&k);
            if ( k >= L ) continue ;
            c[n++] = k;
        }
        if ( n == 1 ) {
            printf("%d\n",c[n-1]);
            continue ;
        }
        assert( n >= 2 );
        for ( sort(c,c+n), sum = 0, i = 0; i < n; sum += c[i++] );
        for ( D = init(), i = 0; i < n; push(D,c[i++]) );
#if DBG
        for ( q[0].clear(), q[1].clear(), q[t=0][0] = 1, i = 0; i < n; ++i ) {
            for ( q[t^=1].clear(), it = q[t^1].begin(); it != q[t^1].end(); ++it ) {
                if ( q[t].find(it->first+c[i]) == q[t].end() )
                    q[t][it->first+c[i]] = it->second;
                else q[t][it->first+c[i]] += it->second;
            }
            for ( it = q[t^1].begin(); it != q[t^1].end(); ++it )
                if ( q[t].find(it->first) == q[t].end() )
                    q[t][it->first] = it->second;
                else q[t][it->first] += it->second;
        }
#endif
        factorize(sum,pr,deg,&m), Q = 0, d[Q++] = 0, generate(pr,deg,m,0,1LL);
        printf("sum = %lld, Q = %d\n",sum,Q);
        sort(d,d+Q);
        for ( i = 1; i < Q; ++i )
            printf("%lld [%lld]\n",d[i],sum/d[i]);

        /*
        for ( i = 0; i < Q; ++i )
            printf("divisor %lld\n",d[i]);
        */

        for (  low = 0, high = Q-1; low+1<high; ) {
            mid = (low+high)/2;
            if ( d[mid] < c[n-1] )
                low = mid;
            else high = mid;
        }
        assert( high >= 1 );
        // printf("d[high] = %lld\n",d[high]);
        // printf("%lld %lld\n",q[t][d[high]],sum/d[high]);
#if DBG
        for ( i = high; i < Q && !(q[t].find(d[i])!=q[t].end()&&q[t][d[i]]>=sum/d[i]&&(sum_left=sum)>=0&&f(d[i],n,0,D->head)); ++i )
#else
        for(i=high;i<Q&&!((sum_left=sum)>=0&&printf("[%lld] Trying %lld\n",sum,d[i])&&f(d[i],n,0,D->head));++i);
#endif
        assert( i < Q );
        printf("%lld\n",d[i]);
    }
    return 0;
}

