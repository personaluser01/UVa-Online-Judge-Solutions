//
// Created by Owner on 9/19/2019.
// 11612: Sultan and Khairun
// TOPIC: computational geometry, constructive, polar angles, neat
// status: Accepted
//
#include <bits/stdc++.h>
#define N 0x400
#define DIM 2
#define tol (1e-9)
using namespace std;

template<typename T>
struct cell {
    int id;
    double angle, dist;
    T d[DIM];
    T &operator []( int i ) {
        return d[i];
    }
    const T &operator []( int i ) const {
        return d[i];
    }
    cell() = default;
    explicit cell( T *x ) {
        for ( auto i= 0; i < DIM; ++i )
            d[i]= x[i];
    }
};

template<typename T>
cell<T> operator + ( const cell<T> &a, const cell<T> &b ) {
    cell<T> res;
    for ( auto i= 0; i < DIM; ++i )
        res[i]= a[i]+b[i];
    return res;
}
template<typename T>
cell<T> operator - ( const cell<T> &a, const cell<T> &b ) {
    cell<T> res;
    for ( auto i= 0; i < DIM; ++i )
        res[i]= a[i]-b[i];
    return res;
}

template<typename T>
bool operator < ( const cell<T> &a, const cell<T> &b ) {
    for ( auto i= 0; i < DIM; ++i )
        if ( fabs(a[i]-b[i]) > tol )
            return a[i] < b[i];
    return false ;
}

template<typename T>
istream &operator >> ( istream &i, cell<T> &c ) {
    for ( auto t= 0; t < DIM; i >> c[t++] ) ;
    return i;
}

template<typename T>
double operator ^ ( const cell<T> &a, const cell<T> &b ) {
    double hyp= hypot(
                    static_cast<double>(a[0]-b[0]),
                    static_cast<double>(a[1]-b[1])
                );
    return asin(static_cast<double>(b[1]-a[1])/hyp);
}

template<typename T>
double operator | ( const cell<T> &a, const cell<T> &b ) {
    return hypot(
                    static_cast<double>(a[0]-b[0]),
                    static_cast<double>(a[1]-b[1])
                );
}

int n;
cell<double> c[N];

template<typename T>
struct comp {
    bool operator() ( const cell<T> &a, const cell<T> &b ) {
        if ( fabs(a.angle-b.angle) >= tol )
            return a.angle < b.angle;
        return a.dist > b.dist;
    }
};

int main() {
    int i,j,k;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( ;(cin >> n) and n > 0; ) {
        for ( i= 0; i < n; cin >> c[i++], c[i-1].id= (i-1) ) ;
        sort(c,c+n);
        auto &pole= c[0];
        for ( i= 1; i < n; ++i )
            c[i].angle= pole^c[i], c[i].dist= pole|c[i];
        sort(c+1,c+n,comp<double>());
        bool flag= false ;
        for ( i= 2; i < n and fabs(c[i].angle-c[1].angle) < tol; ++i ) ;
        flag|= (i < n);
        if ( not flag ) {
            cout << "no solution" << endl;
            continue ;
        }
        vector<int> ans;
        //transform(c,c+n,back_inserter(ans),[]( const auto &x ) {return x.id;});
        for ( i= 2; i < n and fabs(c[i].angle-c[1].angle) <= tol; ++i ) ;
        assert( i < n );
        for ( ans.push_back(c[0].id), j= i; --i >= 1; ans.push_back(c[i].id) ) ;
        for ( i= j; i < n; ans.push_back(c[i++].id) ) ;

        for ( i= 0; i < n and ans[i] != 0; ++i ) ;
        assert( i < n );
        for ( j= 0; j < n; ++j, ++i, i%= n )
            cout << ans[i] << " ";
        cout << "0" << endl;
    }
    return 0;
}

