/*
 * 10256. The Great Divide
 * status: Accepted
 * TOPIC: Convex Hull, Geometry, Left-right turn, Gift Wrapping, queue
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#define tol 1e-9
using namespace std;
#define N 0x400
typedef long long i64;
enum { D, T };
#define DIM 3
#define pi (2*acos(0.00))

struct cell { double x[DIM]; } ;
queue<int> q;

bool operator == ( const cell &a, const cell &b ) {
    for ( int i = 0; i < DIM; ++i )
        if ( fabs(a.x[i]-b.x[i]) >= tol )
            return false;
    return true;
}

bool operator < ( const cell &a, const cell &b ) {
    for ( int i = 0; i < DIM; ++i )
        if ( fabs(a.x[i]-b.x[i]) >= tol )
            return a.x[i] < b.x[i];
    return false;
}

cell operator+( const cell &a, const cell &b ) {
    cell res;
    for ( int i = 0; i < DIM; ++i ) 
        res.x[i] = a.x[i]+b.x[i];
    return res;
}

cell operator-( const cell &a, const cell &b ) {
    cell res;
    for ( int i = 0; i < DIM; ++i ) 
        res.x[i] = a.x[i]-b.x[i];
    return res;
}

double operator,( const cell &a, const cell &b ) {
    double s = 0;
    for ( int i = 0; i < DIM; ++i ) 
        s += a.x[i]*b.x[i];
    return s;
}

cell operator^( const cell &a, const cell &b ) {
    cell res;
    int i,j,k;
    for ( i = 0; i < DIM; ++i ) {
        j = (i+1)%DIM; k = (i+2)%DIM;
        res.x[i] = a.x[j]*b.x[k]-a.x[k]*b.x[j];
    }
    return res;
}

cell operator*( const cell &a, double t ) {
    cell res;
    for ( int i = 0; i < DIM; ++i ) 
        res.x[i] = a.x[i]*t;
    return res;
}

cell operator*( double t, const cell &a ) {
    cell res;
    for ( int i = 0; i < DIM; ++i ) 
        res.x[i] = a.x[i]*t;
    return res;
}

double len( const cell &a ) { return sqrt((a,a)); }

double operator | ( const cell &a, const cell &b ) {
    double A = len(a), B = len(b);
    assert( A >= tol && B >= tol );
    double co = (a,b)/(A*B),
           si = (a^b).x[2]/(A*B);
    if ( fabs(co+1) < tol ) return pi;
    if ( fabs(co-1) < tol ) return 0;
    if ( fabs(si-1) < tol ) return pi/2;
    if ( fabs(si+1) < tol ) return -pi/2;
    if ( co >= 0 && si >= 0 )
        return acos(co);
    if ( co >= 0 && si <= 0 )
        return asin(si);
    if ( co <= 0 && si >= 0 )
        return acos(co);
    return -pi+acos(-co);
}

bool ccw( const cell &a, const cell &b, const cell &c ) { return ((b-a)|(c-b)) >= 0; }

double wn( const cell &a, const cell &b, const cell &c ) { return ((a-c)|(b-c)); }

bool inside( const cell *c, const int n, const cell &p ) {
    double s = 0;
    for ( int i = 0; i < n; ++i ) {
        if ( p == c[i] || p == c[i+1] )
            return true;
        s += wn(c[i],c[i+1],p);
    }
    return fabs(fabs(s)-2*pi) < tol;
}

cell c[2][N],v[2][N];
int next[2][N],n[2],m[2],used[2][N],yes[2];

bool contained( const int t ) {
    int i;
    for ( i = 0; i < m[t]; ++i ) 
        if ( !inside(v[t^1],m[t^1],v[t][i]) )
            return false;
    return true;
}

bool f( const cell &a, const cell &b, const cell &p ) {
    return (p==a||p==b) || ((p-a),(p-b)) <= 0 && fabs(((p-a)^(p-b)).x[2]) < tol;
}

bool intersect( const cell &a, const cell &b, const cell &c, const cell &d ) {
    int i,j,k,ii,jj;
    double t[2],det = 0,w;

    if ( f(c,d,a) || f(c,d,b) || f(a,b,c) || f(a,b,d) )
        return true;

    for ( i = 0; i < DIM; ++i )
        for ( j = i+1; j < DIM; ++j )
            if ( (w = fabs(-(b.x[i]-a.x[i])*(d.x[j]-c.x[j])+(b.x[j]-a.x[j])*(d.x[i]-c.x[i]))) > det )
                det = w, ii = i, jj = j;
    if ( fabs(det) < tol )
        return false;
    i = ii, j = jj, det = (-(b.x[i]-a.x[i])*(d.x[j]-c.x[j])+(b.x[j]-a.x[j])*(d.x[i]-c.x[i]));
    t[0] = (-(d.x[j]-c.x[j])*(c.x[i]-a.x[i])+(c.x[j]-a.x[j])*(d.x[i]-c.x[i]))/det;
    t[1] = ((b.x[i]-a.x[i])*(c.x[j]-a.x[j])-(b.x[j]-a.x[j])*(c.x[i]-a.x[i]))/det;
    return 0 <= min(t[0],t[1]) && max(t[0],t[1]) <= 1;
}

int main() {
    int i,j,k,l,t,ok,cs = 0;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for (;2==scanf("%d %d",n,n+1)&&(n[0]||n[1]);) {
        // printf("Case %d:\n",++cs);
        for ( t = 0; t <= 1; sort(c[t],c[t]+n[t]), c[t][n[t]] = c[t][0], ++t ) {
            for ( i = 0; i < n[t]; ++i ) 
                scanf("%lf %lf",&c[t][i].x[0],&c[t][i].x[1]), c[t][i].x[2] = 0;
            for ( i = 0; i <= n[t]; next[t][i++] = -1 );
        }
        if ( n[0] == 1 && n[1] == 1 ) {
            puts(c[0][0]==c[1][0]?"No":"Yes");
            continue ;
        }
        assert( n[0] >= 2 || n[1] >= 2 );
        for ( t = 0; t <= 1; ++t ) {
            while ( !q.empty() ) q.pop();
            for ( used[t][i=0] = ++yes[t], q.push(i); !q.empty() && used[t][n[t]] != yes[t]; ) {
                i = q.front(), q.pop();
                for ( j = 1; j <= n[t]; ++j )
                    if ( used[t][j] != yes[t] && !(i == 0 && j == n[t]) )
                        next[t][i] = j;
                if ( next[t][i] == -1 ) {
                    assert( n[t] == 1 );
                    next[t][0] = 1;
                    break ;
                }
                assert( next[t][i] != -1 );
                for ( j = 1; j <= n[t]; ++j )
                    if ( used[t][j] != yes[t] )
                        if ( j != next[t][i] )
                            if ( !ccw(c[t][i],c[t][next[t][i]],c[t][j]) )
                                next[t][i] = j;
                used[t][next[t][i]] = yes[t], q.push(next[t][i]);
            }
            for ( m[t]=0,i=0; i!=n[t]; v[t][m[t]++]=c[t][i],i=next[t][i] );
            v[t][m[t]] = c[t][i];
        }
#if 0
        for ( t = 0; t <= 1; ++t ) {
            printf("Convex Hull %d\n",t);
            for ( i = 0; i <= m[t]; ++i )
                printf("(%.lf,%.lf) ",v[t][i].x[0]+tol,v[t][i].x[1]+tol);
            puts("");
        }
#endif
        if ( contained(0) || contained(1) ) {
            puts("No");
            continue ;
        }
        for ( ok = 0, i = 0; i < m[0] && !ok; ++i )
            for ( j = 0; j < m[1] && !ok; ++j )
                ok |= intersect(v[0][i],v[0][i+1],v[1][j],v[1][j+1]);
        puts(ok?"No":"Yes");
    }
    return 0;
}

