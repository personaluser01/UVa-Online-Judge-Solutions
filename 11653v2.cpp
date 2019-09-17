//
// Created by sj on 16/09/19.
//
#include <bits/stdc++.h>
#define MOD (0xffffffffffffffffull)
#define Q (100100)
#define N (1000001)
#define MAXT (1<<21)
using namespace std;
using u64= unsigned long long;
#define enlist(x) (unique_pts[len++]= x)

int tp[Q],lft[Q],rgt[Q],n,
    qrp[Q],queries,rnk[3*Q],len,
    unique_pts[3*Q],original[3*Q];
u64 ans[Q],tr[MAXT];

void rank_space_reduction( int *x, int n ) {
    for ( int i= 0; i < n; ++i ) {
        rnk[x[i]]= lower_bound(unique_pts, unique_pts + len, x[i]) - unique_pts;
        original[rnk[x[i]]]= x[i];
        x[i]= rnk[x[i]];
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
        return alpha*n + beta*prefix[0][n] + gamma*prefix[1][n] + delta*prefix[2][n];
    }
    void operator += ( const composite_sum &rhs ) {
        alpha+= rhs.alpha;
        beta += rhs.beta;
        gamma+= rhs.gamma;
        delta+= rhs.delta;
    }
    pair<composite_sum,composite_sum> split( int l, int r ) {
        auto m= (l+r)>>1;
        u64 k= m+1-l, k2= ((k*k)&MOD), k3= ((k2*k)&MOD);
        return make_pair(composite_sum(alpha,beta,gamma,delta),
                composite_sum(
                        alpha+beta*k+gamma*k2+delta*k3,
                        beta+2*gamma*k+3*k2*delta,
                        gamma+3*delta*k,
                        delta));
    }
    void operator = ( const int x ) {
        alpha= beta= gamma= delta= 0;
    }
    operator bool() const {
        return (alpha or beta or gamma or delta);
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
};

composite_sum operator * ( const composite_sum &lhs, const u64 rhs ) {
    return {(lhs.alpha*rhs)&MOD, (lhs.beta*rhs)&MOD, (lhs.gamma*rhs)&MOD, (lhs.delta*rhs)&MOD};
}

composite_sum upd[MAXT];
u64 total[MAXT];

composite_sum operator + ( const composite_sum &a, const composite_sum &b ) {
    return {a.alpha+b.alpha, a.beta+b.beta, a.gamma+b.gamma, a.delta+b.delta};
}

void build( int v, int i, int j ) {
    total[v]= 0, upd[v]= 0;
    if ( i < j ) {
        auto k= (i+j)>>1;
        build(2*v,i,k), build(2*v+1,k+1,j);
    }
}

void push_down( int v, int i, int j ) {
    if ( i < j and upd[v] ) {
        // FIXME: j-i+1 should be something like original[j]-original[i]+1
        total[v]+= upd[v](j-i+1), total[v]&= MOD;
        auto pr= upd[v].split(i,j);
        upd[2*v]+= pr.first, upd[2*v+1]+= pr.second;
        upd[v]= 0;
    }
}

void push_up( int v, int i, int j ) {
    if ( i < j )
        total[v]= total[2*v]+total[2*v+1], total[v]&= MOD;
}

void update( int v, int i, int j, int qi, int qj, composite_sum c ) {
    push_down(v,i,j);
    if ( qi > j or qj < i ) return ;
    if ( qi <= i and j <= qj ) {
        //TODO
        // original values start to matter here
        upd[v]= c.trim(i,j);
        return ;
    }
    auto k= (i+j)>>1;
    update(2*v,i,k,qi,qj,c), update(2*v+1,k+1,j,qi,qj,c);
    push_up(v,i,j);
}

u64 query( int v, int i, int j, int qi, int qj ) {
    push_down(v,i,j);
    if ( qi > j or qj < i )
        return 0;
    if ( qi <= i and j <= qj )
        return total[v];
    auto k= (i+j)>>1;
    return (query(2*v,i,k,qi,qj)+query(2*v+1,k+1,j,qi,qj)) & MOD;
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
        len= 0, enlist(0);
        for ( i= 0; i < m; ++i )
            scanf("%d %d %d",tp+i,lft+i,rgt+i), enlist(lft[i]), enlist(rgt[i]);
        for ( scanf("%d",&qr), queries= 0; qr-- and 1 == scanf("%d",&qrp[queries++]); enlist(qrp[queries-1]) ) ;
        sort(unique_pts,unique_pts+len);
        n= len= unique(unique_pts,unique_pts+len)-unique_pts;
        rank_space_reduction(lft,m), rank_space_reduction(rgt,m);
        rank_space_reduction(qrp,queries);
        for ( i= 0; i < m; ++i )
            update(1,0,n-1,lft[i],rgt[i],tp[i]==1?composite_sum::linear():\
                    tp[i]==2?composite_sum::square():composite_sum::triple()); //FIXME
        for ( i= 0; i < queries; ++i )
            ans[i]= query(1,0,n-1,0,qrp[i]);
        printf("Case %d:\n",++cs);
        for ( i= 0; i < queries; printf("%llu\n",ans[i++]) ) ;
    }
    return 0;
}

