/**
 * 11279: Keyboard Comparison
 * TOPIC: STL
 * status: Accepted
 */
#include <bits/stdc++.h>
using namespace std;

string qs[]= {      string("`1234567890-= "),
                    string(" qwertyuiop[]\\"),
                    string(" asdfghjkl;\'  "),
                    string(" zxcvbnm,./   ")
                   };
string QS[]= {      string("~!@#$%^&*()_+ "),
                    string(" QWERTYUIOP{}|"),
                    string(" ASDFGHJKL:\" "),
                    string(" ZXCVBNM<>\?   ")
                    };
string ds[]= {
                    string("`123qjlmfp/[] "),
                    string(" 456.orsuyb;=\\"),
                    string(" 789aehtdck-  "),
                    string(" 0zx,inwvg\'   ")
                    };
string DS[]= {
                    string("~!@#QJLMFP\?{} "),
                    string(" $%^>ORSUYB:+|"),
                    string(" &*(AEHTDCK_  "),
                    string(" )ZX<INWVG\"  ")
                    };

using t_coords= pair<int,int>;

map<char,t_coords> q,d,Q,D;

void fill( map<char,t_coords> &m, const string arr[], int rows= 4 ) {
    for ( auto i= 0; i < rows; ++i )
        for ( auto j= 0; j < arr[i].size(); ++j )
            if ( not isspace(arr[i][j]) ) {
                assert( not m.count(arr[i][j]) );
                m[arr[i][j]]= make_pair(i,j);
            };
}

enum class LAYOUT {
    QWERTY,
    DVORAK
};

enum class MODE {
    TWO_HAND,
    ONE_HAND
};

using t_config= pair<LAYOUT,MODE>;

const map<t_config,string> home_keys=
                            {{{LAYOUT::QWERTY,MODE::TWO_HAND},"ASDFJKL;"},
                            {{LAYOUT::QWERTY,MODE::ONE_HAND},"FGHJ"},
                            {{LAYOUT::DVORAK,MODE::ONE_HAND},"EHTD"}};


string normalize( string s ) {
    string res;
    copy_if(begin(s),end(s),back_inserter(res),[](char ch) {
        return not isspace(ch);
    });
    //cout << "Copied from " << s << " to get " << res << endl;
    s= move(res), res.clear();
    return move(s);
    /*
    if ( lt == LAYOUT::QWERTY ) {
        transform(begin(s),end(s),back_inserter(res),[&]( char ch ) {
            if ( Q.count(ch) ) return ch;
            assert( shift_modifier.count({lt,ch}) );
            auto x= shift_modifier[{lt,ch}];
            if ( not Q.count(x) ) {
                cerr << "Could not find: " << x << endl;
            }
            assert( Q.count(x) );
            return x;
        });
    }
    else {
        transform(begin(s),end(s),back_inserter(res),[&]( char ch ) {
            if ( D.count(ch) ) return ch;
            assert( shift_modifier.count({lt,ch}) );
            auto x= shift_modifier[{lt,ch}];
            assert( D.count(x) );
            return x;
        });
    }
    return res;
     */
}

t_coords my_location( LAYOUT layout, char ch ) {
    if ( layout == LAYOUT::QWERTY ) {
        if ( q.count(ch) )
            return q[ch];
        assert( Q.count(ch) );
        return Q[ch];
    }
    if ( d.count(ch) )
        return d[ch];
    assert( D.count(ch) );
    return D[ch];
}

double dist( t_coords a, t_coords b ) {
    return hypot(a.first-b.first,a.second-b.second);
}

t_coords find_closest( t_config c, char ch ) {
    t_coords ans;
    double best_dist= numeric_limits<double>::max();
    char best_key;
    const auto loc= my_location(c.first,ch);
    assert( home_keys.count(c) );
    for ( char x: home_keys.find(c)->second ) {
        auto home= my_location(c.first,x);
        if ( dist(loc,home) < best_dist )
            best_dist= dist(loc,home), ans= home, best_key= x;
    }
    if ( ch == 'P' ) {
        /*
        cerr << "Closest to " << ch << " for " << static_cast<int>(c.first) << " is " << best_key << endl;
        cerr << "Coords: " << ans.first << ", " << ans.second << " vs " << loc.first << ", " << loc.second << endl;
        cerr << "Distance: " << dist(ans,loc) << endl;
         */
    }
    assert( best_dist < numeric_limits<double>::max() );
    return ans;
}

double calc( t_config c, string s ) {
    return accumulate(make_move_iterator(begin(s)),make_move_iterator(end(s)),0.00,[&](double acc,char ch) {
        return acc+dist(my_location(c.first,ch),find_closest(c,ch));
    });
}

vector<t_config> configs= {
                           make_pair(LAYOUT::QWERTY,MODE::TWO_HAND),
                           make_pair(LAYOUT::QWERTY,MODE::ONE_HAND),
                           make_pair(LAYOUT::DVORAK,MODE::ONE_HAND)
                          };

int main() {
    int i;
#ifndef ONLINE_JUDGE
    freopen("11279.in","r",stdin);
#endif
    fill(q,std::move(qs)), fill(Q,std::move(QS)), fill(d,std::move(ds)), fill(D,std::move(DS));
    for ( string s; getline(cin,s); ) {
        vector<double> ans;
        transform(begin(configs),end(configs),back_inserter(ans),[&]( t_config c ) {
            //cerr << s << endl;
            auto normalized= normalize(s);
            return 2*calc(c,normalize(s));
        });
        cout << fixed << setprecision(2);
        for ( i= 0; i < 3; ++i ) {
            if ( i ) cout << " ";
            cout << ans[i];
        }
        cout << endl;
    }
    return 0;
}
