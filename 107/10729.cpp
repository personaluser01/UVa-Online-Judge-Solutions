/**
 * 10729. Treequivalence
 * TOPIC: canonical representation, preorder label sequence, rotation around a node
 * status:
 */
#include <bits/stdc++.h>
using namespace std;
#define N (0x80)
#ifndef ONLINE_JUDGE
#include "../test_runner.h"
#endif

struct node {
    vector<shared_ptr<node>> sons;
    shared_ptr<node> parent= nullptr;
    char label{};
    node() {};
    node( char c ): label(c), mask(0) {};
    int id{};
    unsigned char mask{0};
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

void dfs( const int dir, const shared_ptr<node>& x, ostream &os, shared_ptr<node> nr ) {
    if ( x == nullptr ) return ;
    if ( is_ancestor(x,nr) ) {
        if ( dir == 1 ) {
            // first walk the children
            // then climb up the parent
            os << x->label;
            if ( x->sons.empty() or x->sons.size() == 1 ) {
                if ( x->parent != nullptr ) {
                    os << '(';
                    dfs(dir, x->parent, os, nr);
                    os << ')';
                }
            }
            else {
                os << '(';
                bool flag= true ;
                for ( const auto& y: x->sons ) {
                    if ( is_ancestor(y,nr) ) continue ;
                    if ( not flag ) os << ',';
                    dfs(dir,y,os,nr);
                    flag= false ;
                }
                if ( x->parent != nullptr ) {
                    if ( not flag ) os << ',';
                    dfs(dir, x->parent, os, nr);
                }
                os << ')';
            }
        }
        else {
            // first climb up the parent
            // then walk the children
            os << x->label;
            if ( x->sons.empty() or x->sons.size() == 1 ) {
                if ( x->parent != nullptr ) {
                    os << '(';
                    dfs(dir, x->parent, os, nr);
                    os << ')';
                }
            }
            else {
                os << '(';
                bool flag= true ;
                if ( x->parent != nullptr ) {
                    dfs(dir, x->parent, os, nr);
                    flag= false ;
                }
                for ( const auto& y: x->sons ) {
                    if ( is_ancestor(y,nr) ) continue ;
                    if ( not flag ) os << ',';
                    dfs(dir,y,os,nr);
                    flag= false ;
                }
                os << ')';
            }
        }
    }
    else {
        os << x->label;
        if ( x->sons.empty() ) return ;
        os << '(';
        bool flag= false ;
        for ( const auto& y: x->sons ) {
            if ( not flag )
                os << ',';
            dfs(dir,y,os,nr);
            flag= true ;
        }
        os << ')';
    }
}

void f( const shared_ptr<node>& new_root, ostream &os ) {
    bool flag= true ;

    assert( new_root->mask );
    const auto dir= (new_root->mask&1);
    // two variants for rotation
    // we assume the size of the tree is >= 2
    if ( dir == 1 ) {
        os << new_root->label << '(';
        for (const auto &y: new_root->sons) {
            if (not flag) os << ',';
            dfs(dir, y, os, new_root);
            flag = false;
        }
        if (new_root->parent != nullptr) {
            if (not flag) os << ',';
            dfs(dir, new_root->parent, os, new_root);
        }
        os << ")\n";
    }
    else {
        os << new_root->label << '(';
        if (new_root->parent != nullptr) {
            dfs(dir, new_root->parent, os, new_root);
            flag = false;
        }
        for (const auto &y: new_root->sons) {
            if (not flag) os << ',';
            dfs(dir, y, os, new_root);
            flag = false;
        }
        os << ")\n";
    }
}

void search( const shared_ptr<node>& x, ostream &os ) {
    if ( x == nullptr ) return ;
    if ( x->mask )
        f(x,os);
    for ( const auto& y: x->sons )
        search(y,os);
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

void floodfill( const shared_ptr<node> &x ) {
    in[x->id]= ++tick;
    if ( not x->sons.empty() ) {
        auto y= x->sons.back();
        y->mask|= (1u<<1);
        y= x->sons.front();
        y->mask|= (1u<<0);
    }
    for ( auto y: x->sons ) {
        floodfill(y);
    }
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
        for ( string s; getline(is,s); ) {
            cout << "Candidate: " << s << endl;
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
