/*
 * status: Accepted
 */
#include <bits/stdc++.h>
using namespace std;
#define MAXV (101)
using i64= int64_t;
#define eps (0.001)
#define tol (1e-7)

struct t_rat {
    i64 x,y;
    t_rat() {x= 0, y= 1;}
    t_rat( i64 x, i64 y ) {
        auto g= __gcd(x,y);
        this->x= x/g, this->y= y/g;
    }
    t_rat ( i64 x ) : x(x), y(1) {
    }
    t_rat ( int x ) : x(x), y(1) {
    }
    double to_double() const {
        return (double)x/(y+0.00);
    }
};

ostream &operator << ( ostream &os, const t_rat &r ) {
    if ( r.y == 1 )
        return os << r.x;
    return os << r.x << " / " << r.y;
}

t_rat operator + ( const t_rat &a, const t_rat &b ) {
    i64 u= a.x*b.y+a.y*b.x, d= a.y*b.y;
    return {u,d};
}

t_rat operator - ( const t_rat &a, const t_rat &b ) {
    i64 u= a.x*b.y-a.y*b.x, d= a.y*b.y;
    return {u,d};
}

t_rat operator * ( const t_rat &a, const t_rat &b ) {
    i64 u= a.x*b.x, d= a.y*b.y;
    return {u,d};
}

t_rat operator / ( const t_rat &a, const t_rat &b ) {
    i64 u= a.x*b.y, d= a.y*b.x;
    return {u,d};
}

int cn[MAXV],n,a,b,Y;
set<t_rat> points_of_interest;
list<int> present;
t_rat alpha;
const t_rat oo= {0xffffffff,1};

// return the smallest x such that ceil(k/j) == x
double smallest( double k, double j ) {
    double low= k/j-eps, high= k/j+eps, mid;
    assert( (int)ceil(k/high) <= j );
    assert( (int)ceil(k/low) > j );
    for ( ;fabs(high-low) >= tol; (int)ceil(k/(mid= (low+high)/2)) > j ? (low= mid):(high= mid) ) ;
    assert( (int)ceil(k/high) == j );
    return high;
}

double largest( double k, double j ) {
    double low= k/j-eps, high= k/j+eps, mid;
    assert( (int)ceil(k/high) <= j );
    assert( (int)ceil(k/low) > j );
    for ( ;fabs(high-low) >= tol;(int)ceil(k/(mid= (low+high)/2)) <= j ? (high= mid):(low= mid) ) ;
    assert( (int)ceil(k/high) == j );
    return high;
}

// return the interval [l,r] such that ceil(k/x) == j <=> x <- [l,r]
pair<double,double> f( int k, int j ) {
    return {
        smallest(k,j), largest(k,j)
    };
}

t_rat cost( t_rat S ) {
    t_rat ans= {0,1};
    for ( auto it: present ) {
        ans= ans+a*cn[it]*((S*(i64)ceil((it/S).to_double()))-it);
        ans= ans+b*cn[it]*(i64)ceil((it/S).to_double());

    }
    return ans;
}

t_rat make_rational( int k, int j ) {
    if ( j == 1 )
        return {k,1};
    if ( j == 2 ) {
        if ( (k&1) )
            return {k,2};
        return {k/2,1};
    }
    if ( j == 3 ) {
        if ( 0 == (k%3) )
            return {k/3,1};
        return {k,3};
    }
    return {k,3};
}

t_rat compute( t_rat S ) {
    t_rat ans= {0,1}, coeff= (S*alpha+1);
    for ( auto it= present.begin(); it != present.end(); it= next(it) ) {
        //ans = ans + cn[*it] * ((i64) ceil((*it / S).to_double()));
        t_rat x= ((i64) ceil((*it / S).to_double()));
        if ( x.to_double() > 3 )
            return oo;
        ans = ans+cn[*it]*x;
    }
    return coeff*ans;
}

bool operator < ( const t_rat &lhs, const t_rat &rhs ) {
    return lhs.to_double() < rhs.to_double();
}

bool operator > ( const t_rat &lhs, const t_rat &rhs ) {
    return lhs.to_double() > rhs.to_double();
}

bool operator == ( const t_rat &lhs, const t_rat &rhs ) {
    return fabs(lhs.to_double()-rhs.to_double()) < tol;
}

int main() {
    int i,j,k;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    for ( k= 1; k < MAXV; ++k )
        for ( j= 1; j <= 3; ++j ) {
            auto r= make_rational(k,j);
            points_of_interest.insert(r);
            /*
            auto pr= f(k,j);
            printf("ceil(%d/x) == %d <=> x <- [%lf,%lf]\n",k,j,pr.first,pr.second);
            assert( fabs(pr.first-pr.second) < tol );
            points_of_interest.insert(convert(pr.first));
             */
        }
    for (;(cin >> n) and n;) {
        memset(cn,0,sizeof cn);
        cin >> a >> b, present.clear();
        alpha= t_rat(a,b);
        for ( i= 0; i < n; ++i )
            if ( (cin >> k), ++cn[k] == 1 )
                present.push_back(k);
        t_rat best= oo, S;
        for ( auto it : points_of_interest ) {
            auto res= compute(it);
            if ( res < best )
                best= res, S= it;
        }
        cout << cost(S) << endl;
    }
    return 0;
}
