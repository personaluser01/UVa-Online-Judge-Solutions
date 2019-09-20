//
// Created by Owner on 9/20/2019.
//
#include <bits/stdc++.h>
#define N (0x400)
using i64= long long;
using namespace std;

const string pattern= "([-+])(\\d*)([x]?)([\\^]?)(\\d*)";

template<typename T>
struct poly {
    T c[N];
    T const &operator [] ( int idx ) const {
        return c[idx];
    }
    T &operator [] ( int idx ) {
        return c[idx];
    }
    poly() { memset(c,0,sizeof c); }
};

template<typename T>
istream &operator >> ( istream &is, poly<T> &p ) {
    memset(p.c,0,sizeof p.c);
    regex re(pattern);
    smatch matches;
    string str;
    if ( !(is >> str) )
        return is;
    if ( str[0] != '-' and str[0] != '+' )
        str= "+"+str;
    for ( ;!str.empty() and regex_search(str,matches,re); ) {
        string sgn= matches.str(1);
        string coeff= matches.str(2);
        string x= matches.str(3);
        string degree_sign= matches.str(4);
        string power= matches.str(5);
        int deg= x==""?0:(degree_sign== ""?1:strtol(power.c_str(),nullptr,10));
        int cf= (coeff== ""?1:strtol(coeff.c_str(),nullptr,10));
        int sign= (sgn=="+"?1:-1);
        p[deg]+= sign*cf;
        str= matches.suffix();
    }
    return is;
}

template<typename T>
ostream &operator << ( ostream &out, const poly<T> &p ) {
    int i;
    for ( i= N-1; i >= 0 and not p[i]; --i ) ;
    if ( i < 0 ) {
        out << "0";
        return out;
    }
    bool first= true ;
    for ( ;i >= 0; --i )
        if ( p[i] ) {
            if ( labs(p[i]) == 1 and i > 0 ) {
                if ( p[i] > 0 and not first )
                    out << "+";
                else if ( p[i] < 0 )
                    out << "-";
            }
            else {
                if (p[i] > 0 and not first)
                    out << "+";
                out << p[i];
            }
            if ( i >= 1 )
                out << "x";
            if ( i >= 2 )
                out << "^" << i;
            first= false ;
        }
    return out;
}

template<typename T>
poly<T> operator * ( const poly<T> &lhs, const poly<T> &rhs ) {
    poly<T> res;
    for ( int i= 0; i < N; ++i )
        for ( int j= 0; (i+j) < N; ++j )
            res[i+j]+= lhs[i]*rhs[j];
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( poly<i64> a,b; cin >> a >> b; ) {
        // cout << a << endl << b << endl;
        cout << a*b << endl;
    }
    return 0;
}

