/**
 * 10729. Treequivalence
 * TOPIC: tree representations, recursion, parsing
 * status: Accepted
 */
#include <bits/stdc++.h>
using namespace std;
#define N (0x400)
#ifndef ONLINE_JUDGE
#include "../test_runner.h"
#endif

struct node {
    vector<shared_ptr<node>> sons;
    shared_ptr<node> parent= nullptr;
    char label{};
    node() {};
    node( char c ): label(c) { sons.clear(); };
    int id{};
};

int pos_of_closing[N], gid, in[N], out[N], tick;

bool is_ancestor( const shared_ptr<node>& p, const shared_ptr<node> &x ) {
    return in[p->id] <= in[x->id] and out[x->id] <= out[p->id];
}

vector<shared_ptr<node>> parse_from( const shared_ptr<node>& father, const string &s, int i, int j ) {
    if ( i == j )
        return vector<shared_ptr<node>>();
    vector<shared_ptr<node>> res;
    for ( int t= i; t < j; ) {
        assert(isupper(s[t]));
        auto new_node= make_shared<node>(s[t]);
        new_node->parent= father, new_node->id= gid++;
        res.push_back(new_node);
        if ( t+1 == j ) break ;
        if ( s[t+1] == '(' ) {
            new_node->sons= parse_from(new_node,s,t+2,pos_of_closing[t+1]);
            t= pos_of_closing[t+1]+1;
            if ( t < j and s[t] == ',' ) ++t;
        }
        else if ( s[t+1] == ',' ) {
            t+= 2;
            continue ;
        }
    }
    return res;
}

void display( const shared_ptr<node>& x, ostream &os ) {
    if ( x == nullptr ) return ;
    os << x->label;
    if ( x->sons.empty() )
        return ;
    bool flag= true ;
    os << '(';
    for ( const auto& y: x->sons ) {
        if ( not flag ) os << ',';
        display(y,os);
        flag= false ;
    }
    os << ')';
}

string stringify( const shared_ptr<node> &x ) {
    stringstream str;
    display(x,str);
    return std::move(str.str());
}

void display2( const shared_ptr<node>& x, const shared_ptr<node> &nr, ostream &os ) {
    if ( x == nullptr ) return ;
    if ( not is_ancestor(x,nr) ) {
        display(x,os);
        return ;
    }
    os << x->label;
    if ( x->sons.empty() or x->sons.size() == 1 ) {
        if ( x->parent != nullptr ) {
            os << '(';
            display2(x->parent, nr, os);
            os << ')';
        }
    }
    else {
        assert( x->sons.size() >= 2 );
        os << '(';
        auto it= find_if(begin(x->sons),end(x->sons),[&]( const shared_ptr<node> &y ) {
            return is_ancestor(y,nr);
        });
        assert( it != x->sons.end() );
        bool flag= true ;
        for ( auto jt= it; ++jt < end(x->sons); ) {
            if ( not flag )
                os << ',';
            os << stringify(*jt);
            flag= false ;
        }
        if ( x->parent != nullptr ) {
            if ( not flag ) os << ',';
            display2(x->parent,nr,os);
            flag= false ;
        }
        for ( auto jt= begin(x->sons); jt < it; ++jt ) {
            if ( not flag )
                os << ',';
            os << stringify(*jt);
            flag= false ;
        }
        os << ')';
    }
}

string g( const shared_ptr<node> &x, const shared_ptr<node> &nr ) {
    stringstream str;
    display2(x,nr,str);
    return str.str();
}

void f( const shared_ptr<node>& new_root, ostream &os ) {
    vector<string> reprs;
    reprs.clear();
    string anc_path;
    for ( const auto &y: new_root->sons )
        reprs.push_back(stringify(y));
    if ( new_root->parent != nullptr )
        anc_path= g(new_root->parent,new_root);
    if ( reprs.empty() and anc_path.empty() ) {
        os << new_root->label << endl;
        return ;
    }
    for ( int i= 0; i <= reprs.size(); ++i ) {
        os << new_root->label << '(';
        bool flag= true ;
        for ( int j= i; j < reprs.size(); ++j ) {
            if ( not flag ) os << ',';
            os << reprs[j];
            flag= false ;
        }
        if ( new_root->parent != nullptr ) {
            if (not flag) os << ',';
            os << anc_path;
            flag = false;
        }
        for ( int j= 0; j < i; ++j ) {
            os << ',';
            os << reprs[j];
        }
        os << ")\n";
    }
}

void search( const shared_ptr<node>& x, ostream &os ) {
    if ( x == nullptr ) return ;
    f(x,os);
    for ( const auto& y: x->sons )
        search(y,os);
}


void floodfill( const shared_ptr<node> &x ) {
    in[x->id]= ++tick;
    for ( const auto& y: x->sons )
        floodfill(y);
    out[x->id]= ++tick;
}

#ifndef ONLINE_JUDGE
void TestRepresentation() {
    stringstream str("A(B(C,D),E)");
    string s= str.str();
    stack<int> st;
    for ( int i= 0; i < s.size(); ++i ) {
        if ( s[i] == '(' ) {
            st.push(i);
            continue ;
        }
        if ( s[i] == ')' ) {
            pos_of_closing[st.top()]= i;
            st.pop();
            continue ;
        }
    }
    auto root= parse_from(nullptr,s,0,s.size())[0];
    stringstream os;
    display(root,os);
    assert( os.str() == str.str() );
}
#endif

int main() {
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    int i,j,k,ts;
#ifndef ONLINE_JUDGE
    freopen("10729.in","r",stdin);
    //TestRunner tr;
    //RUN_TEST(tr,TestRepresentation);
#endif
    for ( cin >> ts; ts--; ) {
        shared_ptr<node> r[2];
        int sizes[2];
        string repr[2];
        for ( auto t= 0; t <= 1; ++t ) {
            string s;
            cin >> s, gid= 0;
            repr[t]= s;
            stack<int> st;
            for ( i= 0; i < s.size(); ++i ) {
                if ( s[i] == '(' ) {
                    st.push(i);
                    continue ;
                }
                if ( s[i] == ')' ) {
                    pos_of_closing[st.top()]= i;
                    st.pop();
                    continue ;
                }
            }
            assert( st.empty() );
            auto roots = parse_from(nullptr, s, 0, s.size());
            assert(roots.size() <= 1);
            r[t]= roots[0], sizes[t]= gid;
        }
        if ( repr[0] == repr[1] ) {
            cout << "same" << endl;
            continue ;
        }
        if ( sizes[0] == 1 or sizes[1] == 1 ) {
            if ( sizes[0] == sizes[1] and r[0]->label == r[1]->label )
                cout << "same" << endl;
            else cout << "different" << endl;
            continue ;
        }
        if ( sizes[0] != sizes[1] ) {
            cout << "different" << endl;
            continue ;
        }
        stringstream str;
        tick= -1, floodfill(r[0]);
        search( r[0], str );
        istringstream is(str.str());
        //cout << "Target: " << repr[1] << endl;
        for ( string s; getline(is,s); ) {
            //cout << "Candidate: " << s << endl;
            if ( repr[1] == s ) {
                cout << "same" << endl;
                goto nxt;
            }
        }
        cout << "different" << endl;
        nxt: continue ;
    }
    return 0;
}
