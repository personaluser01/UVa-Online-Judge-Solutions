/*
 * 1392. DNA Regions
 * TOPIC: binary search, segment tree
 * status: Accepted
 */
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#define tol (1e-13)
using namespace std;
#define N (150100)
#define oo (1<<30)

int mymax( int x, int y ) {
	return x < y ? y : x;
}
int mymin( int x, int y ) {
	return x < y ? x : y;
}

char a[N],b[N];
int n,perc,str[N];
long double c[N],pref[N];

long double _sum( int i, int j ) { return pref[j]-pref[i-1]; }

typedef int (*func) ( int, int ) ;

int build_tree( int *tr, int *vals, int v, int i, int j, func comp ) {
	int k = (i+j)/2;
	assert( i <= j );
	if ( i == j ) 
		return tr[v] = vals[i];
	return tr[v] = comp(build_tree(tr,vals,2*v,i,k,comp),build_tree(tr,vals,2*v+1,k+1,j,comp));
}

int rmq( int *tr, int v, int i, int j, int qi, int qj, func comp, int neutral ) {
	int k = (i+j)/2;
	assert( i <= j ) ;
	if ( qi > j || qj < i || qi > qj ) return neutral;
	assert( qi <= qj ) ;
	if ( qi <= i && j <= qj )
		return tr[v];
	return comp(rmq(tr,2*v,i,k,qi,qj,comp,neutral),rmq(tr,2*v+1,k+1,j,qi,qj,comp,neutral));
}

int f( int left, int right ) {
	if ( left == right ) 
		return c[left]>=0?1:0;
	assert( left < right );
	int k = (left+right)/2, ans = max(f(left,k),f(k+1,right));
	map<long double,int> left_map, right_map;
	left_map.clear(), right_map.clear();
	for ( int t = k; t >= left; --t )
		left_map[_sum(t,k)] = t;
	for ( int t = k+1; t <= right; ++t )
		right_map[_sum(k+1,t)] = t;
	int nl = left_map.size(), nr = right_map.size();
	int *ltree = new int[(nl<<2)+4],*rtree = new int[(nr<<2)+4],
		*ll = new int[nl], *rr = new int[nr];
	long double *lvals = new long double[nl], *rvals = new long double[nr];
	int i = 0, j = 0;
	for ( map<long double,int> :: iterator it = left_map.begin(); it != left_map.end(); ++it )
		lvals[i] = it->first, ll[i++] = it->second;
	for ( map<long double,int> :: iterator it = right_map.begin(); it != right_map.end(); ++it )
		rvals[j] = it->first, rr[j++] = it->second;
	assert( i == nl && j == nr );
	assert( left == build_tree(ltree,ll,1,0,nl-1,mymin) );
   	assert ( right == build_tree(rtree,rr,1,0,nr-1,mymax) );
	for ( int t = k+1; t <= right; ++t ) {
		long double val = -_sum(k+1,t);
		int low,high,mid;
		if ( lvals[nl-1] < val ) continue ;
		if ( lvals[0] >= val ) {
			ans = max(ans,t-left+1);
			continue ;
		}
		assert( lvals[low=0] < val && lvals[high=nl-1] >= val );
		for ( ;low+1<high; lvals[mid=(low+high)/2]<val?(low=mid):(high=mid) ) ;
		assert( lvals[low] < val && lvals[high] >= val );
		ans = max(ans,t-rmq(ltree,1,0,nl-1,high,nl-1,mymin,+oo)+1);
	}
	for ( int t = k; t >= left && ans < (right-left+1); --t ) {
		long double val = -_sum(t,k);
		int low,high,mid;
		if ( rvals[nr-1] < val ) continue ;
		if ( rvals[0] >= val ) {
			ans = max(ans,right-t+1);
			continue ;
		}
		assert( rvals[high = nr-1] >= val && rvals[low = 0] < val ) ;
		for ( ;low+1 < high; rvals[mid = (low+high)/2]<val?(low=mid):(high=mid) ) ;
		ans = max(ans,rmq(rtree,1,0,nr-1,high,nr-1,mymax,-oo)-t+1);
	}
	delete(ll), delete(rr), delete(rvals), delete(lvals), delete(rtree), delete(ltree);
	return ans;
}

int main() {
	int i,j,k,left,right,best;
	long double low,high,mid,sum;
	for ( ;2 == scanf("%d %d",&n,&perc) && n; ) {
		scanf("%s %s",a+1,b+1);
		for ( perc=100-perc, i = 1; i <= n; ++i )
			str[i] = (a[i]==b[i]?1:0);
		for ( i = 1; i <= n; ++i )
			pref[i] = (c[i]=100*str[i]-perc)+pref[i-1];
		/*
		vector<pair<long double,pair<int,int> > > vec;
		for ( best = -1, left = 0, right = -1, sum = 0, i = 1; i <= n; ) {
			assert( sum >= 0 );
			if ( sum+c[i] < 0 ) {
				if ( right != -1 )
					vec.push_back(make_pair(sum,make_pair(left,right)));
				++i, sum = 0, left = 0, right = -1;
				continue ;
			}
			sum += c[i];
			if ( right == -1 ) left = right = i;
			else ++right;
			++i;
			assert( right == i-1 );
		}
		if ( sum >= 0 && right != -1 )
			vec.push_back(make_pair(sum,make_pair(left,right)));
		for ( i = 1; i <= n; ++i )
			pref[i] = pref[i-1]+c[i];
		best = -1;
		for ( int l = 0; l < (int)vec.size(); ++l ) {
			sum = vec[l].first, left = vec[l].second.first, right = vec[l].second.second;
			int good, bad;
			if ( pref[right] >= 0 ) {
				best = max(best,right);
				continue ;
			}
			assert( left >= 2 );
			if ( pref[right]-pref[left-2] >= 0 ) {
				for ( bad = 1, good = left-1; bad+1<good; ) {
					k = (good+bad)/2;
					if ( pref[right]-pref[k-1] < 0 )
						bad = k;
					else good = k;
				}
				best = max(best,right-good+1);
			}
			else best = max(best,right-left+1);
		}
		if ( best == -1 ) puts("No solution.");
		else printf("%d\n",best);*/
		best = f(1,n);
		if ( !best )
			puts("No solution.");
		else printf("%d\n",best);
	}
	return 0;
}

