//
// Created by sj on 16/09/19.
// 11653: Stick Makes Gold
// TOPIC: segment tree, decomposition of updates into simpler form, lazy propagation, (possibly rank space reduction)
// status: Accepted
//
#include <bits/stdc++.h>
#define MOD (0xffffffffffffffffull)
//#define Q (100100)
#define Q (N)
#define N (1000001)
#define MAXT (1<<21)
using namespace std;
using u64= unsigned long long;
#define LEVO(k) ((k)<<1)
#define PRAVO(k) (LEVO(k)+1)

int tp[Q],lft[Q],rgt[Q],n,
    qrp[Q],queries,rnk[N],len,
    unique_pts[3*Q],original[N];

void enlist( int x ) {
    unique_pts[len++]= x;
}

void rank_space_reduction( int *x, int xlen ) {
    for ( int i= 0; i < xlen; ++i ) {
        auto it= lower_bound(unique_pts,unique_pts+n,x[i]);
        assert( *it == x[i] );
        //original[rnk[x[i]]= it-unique_pts]= x[i];
        original[x[i]]= x[i];
        //assert( 0 <= rnk[x[i]] and rnk[x[i]] < n );
        //x[i]= rnk[x[i]];
    }
}

u64 prefix[3][N];
using segment= pair<int,int>;

class composite_sum {
private:
    u64 alpha, beta, gamma, delta;
public:
    composite_sum() {
        alpha= beta= gamma= delta= 0;
    }
    composite_sum( u64 a, u64 b, u64 c, u64 d ) {
        alpha= a, beta= b, gamma= c, delta= d;
    }
    u64 operator () ( const u64 n ) {
        if ( n == 0 ) return 0;
        return alpha*n + beta*prefix[0][n-1] + gamma*prefix[1][n-1] + delta*prefix[2][n-1];
    }
    composite_sum &operator += ( const composite_sum &rhs ) {
        alpha+= rhs.alpha;
        beta += rhs.beta;
        gamma+= rhs.gamma;
        delta+= rhs.delta;
        return *this;
    }
    composite_sum split( int i, int k ) const {
        assert( i <= k );
        if ( i == k )
            return *this;
        u64 m= (k-i), m2= ((m*m)&MOD), m3= ((m2*m)&MOD);
        return {
                alpha+beta*m+gamma*m2+ m3*delta,
                      beta+2*gamma*m+3*m2*delta,
                             gamma+   3*m*delta,
                                          delta
               };
    }
    static composite_sum C( u64 a ) {
        return {a,0,0,0};
    }
    static composite_sum L( u64 a ) {
        return {a,1,0,0};
    }
    static composite_sum S( u64 a ) {
        return {a*a,2*a,1,0};
    }
    static composite_sum T( u64 a ) {
        return {a*a*a,3*a*a,3*a,1};
    }
    composite_sum &operator = ( const int x ) {
        alpha= beta= gamma= delta= x;
        return *this;
    }

    explicit operator bool() const {
        return alpha != 0 or beta != 0 or gamma != 0 or delta != 0;
    }
    static composite_sum uno() {
        return {1,0,0,0};
    }
    static composite_sum linear() {
        return {0,1,0,0};
    }
    static composite_sum square() {
        return {0,0,1,0};
    }
    static composite_sum triple() {
        return {0,0,0,1};
    }
    friend composite_sum operator + ( const composite_sum &a, const composite_sum &b ) ;
    friend composite_sum operator * ( const composite_sum &lhs, u64 rhs ) ;
    friend ostream& operator << ( ostream &o, const composite_sum &c ) ;
};

ostream& operator << ( ostream &o, const composite_sum &c ) {
    return o << c.alpha << ", " << c.beta << ", " << c.gamma << ", " << c.delta << endl;
}

composite_sum operator * ( const composite_sum &lhs, const u64 rhs ) {
    return {(lhs.alpha*rhs)&MOD, (lhs.beta*rhs)&MOD, (lhs.gamma*rhs)&MOD, (lhs.delta*rhs)&MOD};
}

composite_sum upd[MAXT];
u64 total[MAXT];

composite_sum operator + ( const composite_sum &a, const composite_sum &b ) {
    return {a.alpha+b.alpha, a.beta+b.beta, a.gamma+b.gamma, a.delta+b.delta};
}

inline bool intersect( int i, int j, int qi, int qj ) {
    return not(qi > j or i > qj);
}

void build( int v, int i, int j ) {
    total[v]= 0, upd[v]= 0;
    if ( i < j ) {
        auto k= (i+j)>>1;
        build(LEVO(v),i,k), build(PRAVO(v),k+1,j);
    }
}

void push_down( int v, int i, int j ) {
    if ( not upd[v] ) return ;
    if ( i < j ) {
        upd[LEVO(v)]+= upd[v];
        upd[PRAVO(v)]+= upd[v].split(original[i],(original[i]+original[j])/2+1);
    }
    total[v]+= upd[v](original[j]-original[i]+1), total[v]&= MOD;
    upd[v]= 0;
}

void push_up( int v, int i, int j ) {
    if ( i < j )
        total[v]= total[LEVO(v)]+total[PRAVO(v)], total[v]&= MOD;
}

void update( int v, int i, int j, int qi, int qj, const composite_sum &c ) {
    push_down(v,i,j);
    if ( not intersect(i,j,qi,qj) ) return ;
    if ( qi <= i and j <= qj ) {
        assert( not upd[v] );
        upd[v]+= c.split(original[qi],original[i]);
        push_down(v,i,j);
        return ;
    }
    auto k= (i+j)>>1;
    update(LEVO(v),i,k,qi,qj,c), update(PRAVO(v),k+1,j,qi,qj,c);
    push_up(v,i,j);
}

u64 query( int v, int i, int j, int qi, int qj ) {
    push_down(v,i,j);
    if ( not intersect(i,j,qi,qj) )
        return 0;
    if ( qi <= i and j <= qj ) {
        assert( not upd[v] );
        return total[v];
    }
    auto k= (i+j)>>1;
    auto ans= (query(LEVO(v),i,k,qi,qj)+query(PRAVO(v),k+1,j,qi,qj)) & MOD;
    push_up(v,i,j);
    return ans;
}

int main() {
    int i,ts,cs= 0,m,qr;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( u64 u= 1; u < N; ++u ) {
        prefix[0][u] = prefix[0][u - 1] + u;
        prefix[1][u] = prefix[1][u - 1] + ((u*u)&MOD);
        prefix[2][u] = prefix[2][u - 1] + ((((u*u) & MOD)*u)&MOD);
        for ( i= 0; i < 3; ++i )
            prefix[i][u] &= MOD;
    }
    for ( scanf("%d",&ts); ts-- and 2 == scanf("%d %d",&n,&m); ) {
        for ( len= 0, enlist(0), i= 0; i < m; ++i )
            scanf("%d %d %d",tp+i,lft+i,rgt+i), ++lft[i], enlist(lft[i]), enlist(rgt[i]);
        for ( scanf("%d",&qr), queries= 0; qr-- and 1 == scanf("%d",&qrp[queries++]); enlist(qrp[queries-1]) ) ;
        /*
        sort(unique_pts,unique_pts+len);
        n= unique(unique_pts,unique_pts+len)-unique_pts;
        rank_space_reduction(lft,m), rank_space_reduction(rgt,m);
        rank_space_reduction(qrp,queries);
         */
        for ( i= 0; i <= n; ++i )
            original[i]= i;
        for ( build(1,0,n), i= 0; i < m; ++i )
            update(1,0,n,lft[i],rgt[i],
                    tp[i]==1?composite_sum::L(1):\
                    tp[i]==2?composite_sum::S(1):\
                             composite_sum::T(1));
        for ( printf("Case %d:\n",++cs), i= 0; i < queries; printf("%llu\n",query(1,0,n,0,qrp[i++])) ) ;
    }
    return 0;
}

