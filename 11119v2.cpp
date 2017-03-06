/*
 * 11119. Chemical Attraction
 * TOPIC: bipartite matching, stable matching
 * status: surprisingly WA, although the solution is checked with asserts; possily some I/O format bug
 */
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
#define N 0x400
#define MAXC 0x800
#include <queue>
#include <algorithm>
#include <map>
using namespace std;
enum { S, T };

void Assert( int x ) {
	if ( !x ) { int trap = 1/0; }
}

map<string,int> mp[2];
int id[2][MAXC],n[2],
	m[2][N][N],compounds,
	u[2][N],len[2],_cnt[N],
	_rank[2][N][N],
	ptr[N],mate[2][N],
	has_proposed[N][N],yes;
string name[2][N];
vector<pair<int,int> > male_preferences[N];
queue<int> q;

int main() {
	int i,j,k,t,cs = 0,mx,x,y,nx,ny;
	char a[0x10];
#ifndef ONLINE_JUDGE
	freopen("11119.in","r",stdin);
#endif
	for (;1==scanf("%d",&n[S])&&n[S];) {
		mp[S].clear(), mp[T].clear();
		for ( i = 0; i < n[S]; ++i ) {
			char A[3];
			scanf("%s",A);
			string aa(2,'a');
			aa[0] = A[0]; aa[1] = A[1];
			//aa[0] = a[0], aa[1] = a[1];
			mp[S][name[S][i]=aa] = i;
		}
		for ( scanf("%d",&n[T]), i = 0; i < n[T]; ++i ) {
			char B[3];
			scanf("%s",B);
			string aa(2,'a');
			aa[0] = B[0]; aa[1] = B[1];
			//aa[0] = a[0], aa[1] = a[1];
			mp[T][name[T][i]=aa] = i;
		}
		for ( t = S; t <= T; ++t ) 
			for ( i = 0; i < n[t]; ++i )
				for ( j = 0; j < n[t^1]; ++j )
					scanf("%d",&m[t][i][j]), _rank[t][i][--m[t][i][j]] = j;
		for ( ++cs, mx = 0; 1 == scanf("%d",&compounds) && compounds; ) {
			memset(mate,-1,sizeof mate);
			cout << "Scenario " << cs << ", Mixture "<<(++mx)<<":"<<endl;
			for ( len[S]=len[T]=0, i = 0; i < compounds; ++i ) {
				scanf("%s",a);
				string aa(2,'a'), bb(2,'a');
				aa[0] = a[0], aa[1] = a[1];
				bb[0] = a[2], bb[1] = a[3];
				assert( mp[S].find(aa) != mp[S].end() );
				assert( mp[T].find(bb) != mp[T].end() );
				x = mp[S][aa], y = mp[T][bb];
				u[S][len[S]++]=x; u[T][len[T]++]=y;
			}
			assert( len[S] == len[T] );
			assert( len[S] == compounds );
			for ( i = 0; i < len[S]; ++i ) {
				male_preferences[i].clear();
				for ( j = 0; j < len[T]; ++j )
					male_preferences[i].push_back(make_pair(_rank[S][u[S][i]][u[T][j]],j));
				sort(male_preferences[i].begin(),male_preferences[i].end(),std::greater<pair<int,int> >());
				assert( male_preferences[i].size() == len[T] );
			}
			//assert( q.empty() );
			for ( i = 0; i < len[S]; q.push(i), _cnt[i] = 0, ptr[i++] = 0 );
			/*
			for ( ++yes; !q.empty(); ) {
				x = q.front(), q.pop(), nx = u[S][x];
				assert( ptr[x] >= 0 && mate[S][x] < 0 );
				for ( ;ptr[x] >= 0 && has_proposed[x][y=male_preferences[x][ptr[x]].second] == yes; --ptr[x] );
				assert( ptr[x] >= 0 );
				assert( has_proposed[x][y] != yes );
				ny = u[T][y], --ptr[x];
				has_proposed[x][y] = yes, ++_cnt[x];
				assert( _cnt[x] <= len[T] );
				if ( mate[T][y] < 0 || _rank[T][ny][nx] > _rank[T][ny][u[S][mate[T][y]]] ) {
					if ( mate[T][y] >= 0 ) {
						assert( mate[S][mate[T][y]] == y );
						mate[S][mate[T][y]] = -1, q.push(mate[T][y]);
					}
					mate[S][mate[T][y] = x] = y;
				}
				else q.push(x);
			}
			*/
			for ( i = 0; i < len[S]; ++i ) {
				int man = i;
				while ( man >= 0 ) {
					int wom;
					while ( 1  ) {
						wom = male_preferences[man][ptr[man]++].second;
						if ( mate[T][wom] < 0 || _rank[T][u[T][wom]][u[S][man]] > _rank[T][u[T][wom]][u[S][mate[T][wom]]] ) break ;
					}
					int hubby = mate[T][wom];
					mate[S][mate[T][wom] = man] = wom;
					man = hubby;
				}
			}

			for ( i = 0; i < len[T]; ++i )
				assert( mate[T][i] >= 0 );
			for ( i = 0; i < len[S]; ++i )
				assert( mate[S][i] >= 0 );
			set<int> st;
			assert( st.empty() );
			for ( i = 0; i < len[S]; ++i )
				st.insert(mate[S][i]);
			assert( st.size() == len[T] );
			for ( st.clear(), i = 0; i < len[T]; ++i )
				st.insert(mate[T][i]);
			assert( st.size() == len[S] );
			for ( i = 0; i < len[S]; ++i )
				for ( j = 0; j < len[S]; ++j )
					if ( i != j ) {
						int aa = u[S][i], bb = u[T][mate[S][i]],
							cc = u[S][j], dd = u[T][mate[S][j]];
						assert( !(_rank[S][aa][dd] > _rank[S][aa][bb] && _rank[T][dd][aa] > _rank[T][dd][cc]) );
					}
			assert( len[S] == len[T] );
			for ( i = 0; i < len[S]; ++i ) {
				if ( i ) cout << " ";
				cout<<name[S][u[S][i]]<<name[T][u[T][mate[S][i]]];
				/*
				printf("%d",name[S][u[S][i]].size());
				printf("%d",name[T][u[T][mate[S][i]]].size());
				*/
			}
			cout << endl << endl;
		}
	}
	return 0;
}


