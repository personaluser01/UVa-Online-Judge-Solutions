/*
 * 1282. Fibonaci Words
 * TOPIC: dp
 * status: Accepted
 */
#include <bits/stdc++.h>
#include <map>
using namespace std;
#define N 0x80
#define M (1<<17)
#define oo 0xfffffffful
#define INF 0xffffffffffffffffull
typedef long long i64;
typedef unsigned long long u64;

int n,m;
i64 pref[N],ones[N],q[M];
char t[M];
unsigned int s[N][M],p[N][M];
u64 len[N],z[N];
map<pair<int,int>,bool> mp;

bool is_equal( int n, int i, int j ) {
	if ( len[n] != j-i+1 ) return false ;
	if ( n == 0 || n == 1 )
		return t[i]==n+'0';
	/*
	if ( mp.find(make_pair(n,i)) != mp.end() )
		return mp[make_pair(n,i)];*/
	//return mp[make_pair(n,i)] = is_equal(n-1,i,i+len[n-1]-1) && is_equal(n-2,i+len[n-1],j);
	return ones[n]==q[j]-(i==0?0:q[i-1]) && is_equal(n-1,i,i+len[n-1]-1) && is_equal(n-2,i+len[n-1],j);
}

unsigned int calc_s( int n, int k ) {
	if ( s[n][k] < +oo )
		return s[n][k];
	if ( len[n] < k ) return s[n][k] = 0;
	if ( n <= 1 )
		return s[n][k] = t[0]=='0'+n;
	if ( len[n-2] >= k ) 
		return s[n][k] = calc_s(n-2,k);
	return s[n][k] = calc_s(n-1,k-len[n-2])*is_equal(n-2,k-len[n-2],k-1);
}

unsigned int calc_p( int n, int k ) {
	if ( p[n][k] < +oo )
		return p[n][k];
	if ( len[n] < k ) return p[n][k] = 0;
	if ( n <= 1 )
		return p[n][k] = t[m-1]=='0'+n;
	if ( len[n-1] >= k )
		return p[n][k] = calc_p(n-1,k);
	return p[n][k] = is_equal(n-1,m-k,m-k+len[n-1]-1)*calc_p(n-2,k-len[n-1]);
}

u64 calc_z( int n ) {
	int k;
	if ( z[n] < INF )
		return z[n];
	if ( n <= 1 )
		return z[n] = calc_s(n,m);
	for ( z[n] = calc_z(n-1)+calc_z(n-2), k = 1; k <= m-1; ++k )
		z[n] += calc_s(n-1,k)*calc_p(n-2,m-k);
	return z[n];
}

int main() {
	int i,j,k,cs = 0;
	for ( len[0]=len[1]=1,pref[1]=1,ones[1]=1,i=2;i<N;len[i]=len[i-1]+len[i-2],ones[i]=ones[i-1]+ones[i-2],pref[i]=pref[i-1]+ones[i],++i );
	while ( 2 == scanf("%d %s",&n,t) ) {
		mp.clear(), m = strlen(t), memset(s,0xff,sizeof s), memset(p,0xff,sizeof p), memset(z,0xff,sizeof z);
		for ( q[0] = (t[0]=='1')?1:0, i = 1; i < m; ++i ) q[i] = q[i-1]+(t[i]=='1'?1:0);
		printf("Case %d: %llu\n",++cs,calc_z(n));
	}
	return 0;
}

