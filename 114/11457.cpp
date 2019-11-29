/**
 * 11457: Classified
 * TOPIC: LCA in DAG, data structures, processing queries
 * @see https://www3.cs.stonybrook.edu/~bender/pub/JALG05-daglca.pdf
 * status: W.I.P.
 */
#include <bits/stdc++.h>
#define N (10007)
using namespace std;
using node_type= int;
using level_type= int;
using size_type= int;

size_type num_users, num_docs, qr;
level_type users[N],docs[N];

class dag {
private:
    vector<node_type> adj[N];
    size_type n,m;
    node_type super_source;
    vector<node_type> sources;
    size_type d[N],indeg[N];
    dag &determine_depths() {
        queue<node_type> q;
        // put all sources into the queue
        for_each(begin(sources),end(sources),[&]( node_type x ) {
            q.push(x), d[x]= 0;
        });
        // do an updating BFS
        // TODO: might be better to do something akin to Dijkstra
        for (;not q.empty();) {
            auto x= q.front(); q.pop();
            for ( auto y: adj[x] )
                if ( d[y] < d[x]+1 )
                    d[y]= d[x]+1, q.push(y);
        }
        // checking if all the nodes have been reached
        assert( find_if(d,d+n,[](int x){return x==std::numeric_limits<size_type>::min();})==d+n );
        return *this;
    }
    dag &assign_new_depths() {
        vector<node_type> v(n);
        iota(begin(v),end(v),0);
        // sort the nodes by depths
        sort(begin(v),end(v),[&]( node_type x, node_type y ) {
            return d[x] < d[y];
        });
        // assign new depths as ranks in this sorted order
        for ( auto i= 0; i < v.size(); d[v[i]]= i, ++i ) ;
        return *this;
    }

    vector<pair<node_type,size_type>> wadj[N];
    vector<tuple<node_type,node_type,size_type>> edges;
    size_type w[N];

    dag &assign_weights() {
        // assign weights to arcs
        for ( node_type x= 0; x < n; ++x )
            for ( auto y: adj[x] ) {
                assert( d[y] >= d[x] );
                wadj[x].emplace_back(y,d[y]-d[x]);
            }
        return *this;
    }

    dag &find_sources() {
        vector<node_type> v;
        iota(begin(v),end(v),0);
        copy_if(begin(v),end(v),back_inserter(sources),[&]( int x ) {return indeg[x] == 0;});
        return *this;
    }

    dag &extend_the_graph() {
        // from x's copy in G' draw an arc of weight 0 to the original node
        for ( node_type x= 0; x < n; ++x )
            wadj[x+n].emplace_back(x,static_cast<size_type>(0));
        // reverse the arcs for G'
        for ( node_type x= 0; x < n; ++x )
            for ( const auto &pr: wadj[x] )
                wadj[pr.first+n].emplace_back(x+n,pr.second);
        super_source= (n<<=1);
        return *this;
    }

    size_type distance( node_type x, node_type y ) const {
        return labs(w[x]-w[y]); //FIXME
    }

    dag &all_pairs_shortest_paths() {
        // populate the edges
        for ( auto x= 0; x < n; ++x ) {
            for_each(begin(wadj[x]), end(wadj[x]), [&](const pair<node_type, size_type> &e) {
                edges.emplace_back(x, e.first, e.second);
            });
            edges.emplace_back(super_source,x,0); // draw an arc from super-source to each node
        }
        // all pairs shortest paths
        for_each(w,w+n,[](size_type &x) {x= numeric_limits<size_type>::max();});
        w[super_source]= 0;
        bool flag= true;
        for ( size_type i= 0; i < n and flag; ++i ) {
            flag= false;
            for (const auto &tpl: edges) {
                auto x = get<0>(tpl), y = get<1>(tpl);
                auto weight = get<2>(tpl);
                if (w[x] < numeric_limits<size_type>::max() and w[y] > w[x] + weight)
                    w[y] = w[x] + weight, flag = true;
            }
        }
        return *this;
    }

public:

    dag( dag &&other ) = delete;
    dag( const dag &other ) = delete;
    dag &operator = ( const dag &other ) = delete;
    dag &operator = ( dag &&other ) = delete;

    dag() = default;

    dag &init( std::istream &is= std::cin ) {
        size_type i,j,k;
        cin >> n >> m >> num_users >> num_docs >> qr;
        edges.clear(), sources.clear();
        for ( i= 0; i < n; indeg[i]= 0, wadj[i].clear(), adj[i++].clear() ) ;
        for ( k= 0; k < m; ++k, cin >> i >> j, adj[--i].push_back(--j), ++indeg[j] ) ;
        for ( i= 0; i < num_users; cin >> users[i++], --users[i-1] ) ;
        for ( i= 0; i < num_docs; cin >> docs[i++], --docs[i-1] );
        for ( i= 0; i < n; d[i++]= std::numeric_limits<size_type>::min() ) ;
        return *this;
    }
    node_type lca( node_type x, node_type y ) {
        //TODO
        // since we have original nodes here, x and y
        // we are converting them to (x+n) and y
        return 0; //FIXME
    }
    void preprocess() {
        find_sources().determine_depths()
        .assign_new_depths().assign_weights()
        .extend_the_graph()
        .all_pairs_shortest_paths();
    }
} G;


int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("11457.in","r",stdin);
#endif
    int i,j,ts;
    for ( cin >> ts; ts--; ) {
        G.init(cin).preprocess();
        for ( string action; qr--; ) {
            cin >> i >> action >> j, --i, --j;
            auto &level_of_user= users[i], &level_of_doc= docs[j];
            auto z= static_cast<level_type>(
                    G.lca(
                            static_cast<node_type>(level_of_user),
                            static_cast<node_type>(level_of_doc)
                         )
                    );
            action.front()=='r'?(level_of_user= z):(level_of_doc= z);
        }
    }
    return 0;
}