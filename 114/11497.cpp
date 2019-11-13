// Created by sj on 15/09/19.
// 11497: Set
// TOPIC: convexity, ad hoc, inequalities, modelling, greedy, simulation, modulus, observations
// status: Accepted
#include <bits/stdc++.h>
#define N 3
using namespace std;
using i64= long long;
#define tol (1e-7)
#define MAXX (531441)

bool is_int( double x ) {
    return fabs(floor(x)-x) < tol;
}
template<int rows= 9, int cols= 21>
class solver {
private:
    double a[rows][cols]{};
    double b[rows]{};
    bool find_pivot( int ii, int jj, int &r, int &c ) {
        double w= 0;
        for ( int i= ii; i < rows; ++i )
            for ( int j= jj; j < cols; ++j )
                if ( w < fabs(a[i][j]) )
                    w= fabs(a[r= i][c= j]);
        return w > tol;
    }
    int id[cols]{};
    static_assert( rows <= cols );
    void swap_rows( int i1, int i2 ) {
        for ( int j= 0; j < cols; ++j )
            swap(a[i1][j],a[i2][j]);
        swap(b[i1],b[i2]);
    }
    void swap_cols( int j1, int j2 ) {
        for ( int i= 0; i < rows; ++i )
            swap(a[i][j1],a[i][j2]);
        swap(id[j1],id[j2]);
    }
public:
    solver();
    void set_item( int i, int j, double x ) {
        a[i][j]= x;
    }
    void set_rhs( int i, double x ) {
        b[i]= x;
    }
    double get_sum_rhs() {
        int i,j,k,r,c;
        /*
        for ( k= 0; k < rows and find_pivot(k,k,r,c); ++k ) {
            swap_rows(k,r), swap_cols(k,c);
            for ( i= k+1; i < rows; ++i ) {
                double cf= a[i][k]/a[k][k];
                for ( j= k; j < cols; ++j )
                    a[i][j]-= cf*a[k][j];
                assert( fabs(a[i][k]) < tol );
                b[i]-= cf*b[k];
            }
        }
        assert( k == rows );
         */
        double ans= 0;
        for ( i= 0; i < rows; ++i ) {
            ans += b[i];
            if ( b[i] < 0 or not is_int(b[i]) ) return 0;
        }
#if 0
        for ( i= 0; i < rows; ++i ) {
            for ( j= rows; j < cols; ++j )
                printf("%.lf ",a[i][j]);
            printf("%.lf\n",b[i]);
        }
#endif
        int x[12];
        for (unsigned int w= 0; w < MAXX; ++w ) {
            auto ww= w;
            for ( i= 0; i < 12; ++i )
                x[i]= ww%3, ww/= 3;
            for ( i= 0; i < rows; ++i ) {
                double sm= 0;
                for ( j= rows; j < cols; ++j )
                    sm+= x[j-rows]*a[i][j];
                if ( not(b[i] >= sm and is_int(b[i]-sm) and ((int)(b[i]-sm))%3 == 0) )
                    goto nnxt;
            }
            return ans;
            nnxt: continue ;
        }
        return 0;
        /*
        vector<double> x(cols);
        for ( i= rows-1; i >= 0; --i ) {
        }
         */
    }
};

template<int rows, int cols>
solver<rows, cols>::solver() {
    for ( int i= 0; i < cols; id[i]= i, ++i ) ;
    memset(a,0,sizeof a);
}

int fst[256],sec[256];
i64 a[N][N],c[N*N];
vector<tuple<int,int,int>> confs= {{0,4,8},{0,5,7},{1,3,8},{1,5,6},{2,4,6},{2,3,7},{0,1,2},{3,4,5},{6,7,8},
                                   {0,3,6},{1,4,7},{2,5,8}};
const vector<vector<string>> images= {
        {"111","000","000"},
        {"000","111","000"},
        {"000","000","111"},
        {"100","100","100"},
        {"010","010","010"},
        {"001","001","001"},
        {"100","010","001"},
        {"100","001","010"},
        {"010","100","001"},
        {"010","001","100"},
        {"001","010","100"},
        {"001","100","010"}
};

set<unsigned int> masks;
set<unsigned int> good_profiles;

unsigned int calc_mask( const vector<string> &v ) {
    unsigned int u= 0;
    for ( int k= 0, i= 0; i < v.size(); ++i )
        for ( int j= 0; j < v[i].size(); ++j, ++k )
            if ( v[i][j] == '1' )
                u|= (1u << k);
    return u;
}

bool good_profile( unsigned int u ) {
    unsigned int v= 0;
    for ( int i= 0; i < N*N; ++i, u /= 3 )
        if ( u%3 ) v|= (1u<<i);
    for ( auto x: masks )
        if ( (x&v) == x )
            return false;
    return true ;
}

int matrix[N*N][12+N*N];

void print_profile( unsigned int u ) {
    for ( int i= 0; i < N; ++i, putchar('\n') )
        for ( int j= 0; j < N; printf("%d ",u%3), ++j, u/= 3 );
}

vector<int> my_map[MAXX];

int main() {
    int i,j,k,n,l,t;
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
#endif
    for ( const auto &vec: images )
        masks.insert(calc_mask(vec));
    unsigned int MX= 1;
    for ( i= 0; i < N*N; ++i, MX*= 3 ) ;
    for ( unsigned int u= 0; u < MX; ++u )
        if ( good_profile(u) )
            good_profiles.insert(u);
        /*
    cout << good_profiles.size() << endl;
    for ( auto v: good_profiles ) {
        unsigned int w= v;
        for ( k= 0, i= 0; i < N; ++i ) {
            for ( j= 0; j < N; ++j, ++k ) {
                cout << (w%3) << " ";
                w /= 3;
            }
            cout << endl;
        }
        cout << "Next" << endl;
    }
         */
    for ( t= 0, k= 0; k < N*N; ++k, ++t )
        matrix[t][k]= 3;
    for ( k= N*N; k < images.size()+N*N; ++k ) {
        for ( t= 0, i= 0; i < N; ++i )
            for ( j= 0; j < N; ++j, ++t )
                matrix[t][k]= images[k-N*N][i][j]-'0';
    }
    /*
    for ( i= 0; i < N*N; ++i ) {
        for ( j= 0; j < 21; ++j )
            cout << matrix[i][j] << " ";
        cout << "\n";
    }
     */
    for ( unsigned int ww= 0; ww < MAXX; ++ww ) {
        int xx[12];
        unsigned int www= ww;
        for ( i= 0; i < 12; ++i )
            xx[i]= www%3, www/= 3;
        vector<int> vv;
        for ( i= 0; i < N*N; ++i ) {
            int sm= 0;
            for (j = N * N; j < 21; ++j)
                sm += xx[j - N*N] * matrix[i][j];
            vv.push_back(sm);
        }
        my_map[ww]= move(vv);
    }

    /*
    for ( i= 0; i < N*N; ++i ) {
        for ( j= 0; j < 21; ++j )
            cout << matrix[i][j] << " ";
        cout << endl;
    }
     */
    fst['u']= 0, fst['d']= 1, fst['t']= 2;
    sec['c']= 0, sec['q']= 1, sec['t']= 2;
    assert( good_profiles.count(0) );
    for ( ;(cin >> n) and n > 0; ) {
        memset(a,0,sizeof a), memset(c,0,sizeof c);
        for ( i= 0; i < n; ++i ) {
            string aa,bb;
            cin >> aa >> bb;
            j= fst[aa[0]], k= sec[bb[0]];
            assert( 0 <= min(j,k) and max(j,k) <= 2 );
            ++a[j][k], ++c[j*N+k];
        }
        int ans= 0;
        for ( const auto &it: my_map ) {
            const auto &vec= it;
            unsigned int vv= 0;
            int sm;
            for ( i= 0; i < N*N; ++i )
                if ( c[i] < vec[i] )
                    goto nxt;
                else vv*= 3, vv+=(c[i]-vec[i])%3;
            if ( good_profiles.count(vv) ) {
                sm= 0;
                for ( i= 0; i < N*N; ++i )
                    sm+= (c[i]-((c[i]-vec[i])%3));
                ans= max(ans,sm/3);
            }
            nxt: continue ;
        }
        cout << ans << endl;
        /*
        solver<> slv;
        int answer= 0;
        double dans= 0;
        for ( l= 0; l < good_profiles.size(); ++l ) {
            unsigned int w= good_profiles[l];
            double res;
            for ( i= 0; i < N*N; ++i ) {
                if ( c[i] < (w%3) )
                    goto nxt;
                slv.set_rhs(i,c[i]-(w%3)), w/= 3;
            }
            for ( i= 0; i < N*N; ++i )
                for ( j= 0; j < 21; ++j )
                    slv.set_item(i,j,matrix[i][j]);
            res= slv.get_sum_rhs();
            if ( fabs(((int)res)-res) < tol ) {
                int ires= (int)(floor(res)); dans= res;
                if ( ires % 3 ) goto nxt;
                if ( ires/3 > answer ) {
                    answer = ires / 3;
                    // print_profile(good_profiles[l]);
                }
            }
            nxt: continue ;
        }
        cout << answer << endl;
         */
        /*
        i64 ans= numeric_limits<i64>::min();
        for ( i64 d1= 0; d1 <= min(a[3][1],a[1][3]); ++d1 )
            for ( i64 d2= 0; d2 <= a[2][2]-d1 and d2 <= min(a[1][1],a[3][3]); ++d2 ) {
                i64 uc1= min(a[2][1],min(a[1][1]-d2,a[3][1]-d1)),c1,c2,c3;
                i64 uc2= min(a[1][2],min(a[2][2]-d1-d2,a[3][2]));
                i64 uc3= min(a[1][3],min(a[2][3],a[3][3]-d2));
                assert( uc1 >= 0 and uc2 >= 0 and uc3 >= 0 );
                for ( unsigned int u= 0; u < 8; ++u ) {
                    c1= (u&1)?0:uc1;
                    c2= (u&2)?0:uc2;
                    c3= (u&4)?0:uc3;
                    i64 r1= min(a[1][1]-c1-d2,min(a[1][2]-c2,a[1][3]-c3-d1));
                    i64 r2= min(a[2][1]-c1,min(a[2][2]-c2-d1-d2,a[2][3]-c3));
                    i64 r3= min(a[3][1]-c1-d1,min(a[3][2]-c2,a[3][3]-c3-d2));
                    assert( r1 >= 0 and r2 >= 0 and r3 >= 0 );
                    ans= max(ans,r1+r2+r3+c1+c2+c3+d1+d2);
                }
            }
        cout << ans << endl;
         */
    }
    return 0;
}

