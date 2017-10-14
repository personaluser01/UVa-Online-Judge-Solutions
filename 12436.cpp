/*
 * 12436
 * TOPIC: segment tree with lazy updates
 * status: Accepted
 */
#include <cassert>
#include <cctype>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define L(v) ((v)<<1)
#define R(v) (1|L(v))
#define N (1<<22)
#pragma comment(linker, "/STACK:16777216")
typedef long long i64;
using namespace std;

int getnum() {
	register int ch,n = 0,sign = 1;
	static int dig[256] = {0};
	if ( !dig['0'] )
		for ( ch = '0'; ch <= '9'; dig[ch++] = 1 ) ;
	for ( ;(ch = getchar()) != EOF && !(ch=='-'||dig[ch]); ) ;
	if ( ch == EOF ) return -1;
	if ( ch=='-' )
		sign = -1, ch = getchar();
	for ( n=ch-'0'; (ch=getchar())!=EOF && dig[ch]; n=10*n+ch-'0' ) ;
	return sign*n;
}

i64 sum[N],value[N],a0[N],d0[N];
bool pending[N];

class ST {
private:
	i64 *a;
	int n;

	inline void assign_value( int v, int i, int j, i64 newval ) {
		pending[v] = (i<j);
		sum[v] = (j-i+1)*(value[v] = newval);
		a0[v] = d0[v] = 0LL;
	}

	void add_arithmetic_sequence( int v, int i, int j, i64 A, i64 D ) {
		if ( pending[v] ) {
			int k = (i+j)>>1;
			assign_value(L(v),i,k,value[v]), assign_value(R(v),k+1,j,value[v]);
			pending[v] = false, a0[v] = d0[v] = 0;
		}
		a0[v] += A, d0[v] += D;
		sum[v] += (((A+A+(j-i)*D)*(j-i+1)) >> 1);
	}

	inline void push_up( int v, int i, int j ) {
		if ( i < j ) 
			sum[v] = sum[L(v)]+sum[R(v)];
	}

	inline void push_down( int v, int i, int j ) {
		if ( pending[v] ) {
			int k = (i+j)>>1;
			assign_value(L(v),i,k,value[v]), assign_value(R(v),k+1,j,value[v]);
			pending[v] = false, a0[v] = d0[v] = 0;
		}
		else if ( a0[v] || d0[v] ) {
			if ( i < j ) {
				int k = (i+j)>>1;
				add_arithmetic_sequence(L(v),i,k,a0[v],d0[v]);
				add_arithmetic_sequence(R(v),k+1,j,a0[v]+d0[v]*(k-i+1),d0[v]);
				a0[v] = d0[v] = 0LL;
			}
		}
	}

	void build( int v, int i, int j ) {
		pending[v] = false, a0[v] = d0[v] = 0LL;
		if ( i == j ) {
			assign_value(v,i,j,a[i]), pending[v] = false;
			return ;
		}
		int k = (i+j)>>1;
		build(L(v),i,k), build(R(v),k+1,j);
		push_up(v,i,j);
	}

	void batch_assign( int v, int i, int j, int qi, int qj, i64 newval ) {
		if ( qi > j || qj < i ) return ;
		push_down(v,i,j);
		if ( qi <= i && j <= qj ) {
			assign_value(v,i,j,newval);
			return ;
		}
		int k = (i+j)>>1;
		batch_assign(L(v),i,k,qi,qj,newval), batch_assign(R(v),k+1,j,qi,qj,newval);
		push_up(v,i,j);
	}

	void aseq( int v, int i, int j, int qi, int qj, i64 A, i64 D ) {
		if ( qi > j || qj < i ) return ;
		push_down(v,i,j);
		if ( qi <= i && j <= qj ) {
			add_arithmetic_sequence(v,i,j,A+(i-qi)*D,D);
			return ;
		}
		int k = (i+j)>>1;
		aseq(L(v),i,k,qi,qj,A,D), aseq(R(v),k+1,j,qi,qj,A,D);
		push_up(v,i,j);
	}

	i64 query( int v, int i, int j, int qi, int qj ) {
		if ( qi > j || qj < i ) return 0LL;
		push_down(v,i,j);
		if ( qi <= i && j <= qj ) 
			return sum[v];
		int k = (i+j)>>1;
		i64 left = query(L(v),i,k,qi,qj), right = query(R(v),k+1,j,qi,qj);
		push_up(v,i,j);
		return left+right;
	}

public:
	void init( i64 *a, int n ) {
		int m = (n*4)+0x400;
		this->a = a, this->n = n;
		//build(1,0,n-1);
		//for ( int i = 0; i < m; pending[i] = false, d0[i] = a0[i] = sum[i] = 0, ++i ) ;
	}
	ST() {};
	void batch_assign( int qi, int qj, i64 newval ) {
		batch_assign(1,0,n-1,qi,qj,newval);
	}
	void add_arithmetic_sequence( int qi, int qj, i64 A, i64 D ) {
		aseq(1,0,n-1,qi,qj,A,D);
	}
	i64 query( int qi, int qj ) { return query(1,0,n-1,qi,qj); }
} st;

i64 a[N];
int n = 250000;

int main() {
	int i,j,k,qr;
	char comm[0x10];
	i64 newval;
	for ( ;(qr = getnum()) != -1; ) {
		st.init(a,n);
		for ( ;qr--; ) {
			char ch;
			for ( ;!isupper(ch = getchar()); ) ;
			0[comm] = ch;
			i = getnum(), j = getnum();
			--i, --j;
			switch ( 0[comm] ) {
				case 'A': st.add_arithmetic_sequence(i,j,1,1); break ;
				case 'B': st.add_arithmetic_sequence(i,j,j-i+1,-1); break ;
				case 'S': printf("%lld\n",st.query(i,j)); break ;
				case 'C': newval = getnum(); st.batch_assign(i,j,newval); break ;
			}
		}
		break ;
	}
	return 0;
}

