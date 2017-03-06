/*
 * 11859. Division Game
 * TOPIC: prime decomposition, nim, sprague-grundy
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x80, Q = 10001, MSK = (1<<15)-1, oo = (1<<29);
	int m,n,P,top;
	int [][]g = new int[N][N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	Map<Integer,int[]> q = new TreeMap<Integer,int[]>();
	boolean []isprime = new boolean[Q];
	int []p, st = new int[Q], id = new int[Q];
	List<Integer> signature( int n ) {
		int i,k=0;
		List<Integer> res = new ArrayList<Integer>();
		for ( i = 0; i < P && p[i] <= n; ++i ) {
			for ( k = 0; 0 == (n%p[i]); ++k, n /= p[i] );
			if ( k>0 ) res.add(p[i]|(k<<15));
		}
		if ( n > 1 ) res.add(n|(1<<15));
		return res;
	}
	void f( int ax, int pos, List<Integer> L ) {
		int i,j,k,s,x;
		if ( pos == L.size() ) {
			if ( ax != 1 ) 
				st[++top] = ax;
			return ;
		}
		for ( s = 1, k = L.get(pos)>>15, x=L.get(pos)&MSK, i = 0; i <= k; ++i, s*=x ) 
			f(ax*s,pos+1,L);
	}
	int []sg = new int[Q];
	int calc_sg( int x ) {
		int i,j,k;
		if ( sg[x] < +oo )
			return sg[x];
		if ( x == 1 )
			return sg[x] = 0;
		Set<Integer> s = new HashSet<Integer>();
		int []e = q.get(x);
		for ( i = 0; i < e.length; ++i ) {
			assert 0 == (x%e[i]);
			s.add(calc_sg(x/e[i]));
		}
		for ( k = 0; s.contains(k); ++k );
		return sg[x] = k;
	}
	void go() throws Exception {
		int i,j,k,l,t,cs=0,ts,res;
		for ( i = 3; i < Q; isprime[i] = true, i += 2 );
		for ( isprime[2] = true, i = 3; i < Q; i += 2 )
			for ( j = i+i; isprime[i] && j < Q; isprime[j] = false, j += i );
		for ( i = 0; i < Q; ++i )
			if ( isprime[i] ) ++P;
		// System.out.println("P = "+P);
		p = new int[P];
		for ( i = 0; i < Q; id[i++] = -1 );
		for ( i = 0; i < Q; sg[i++] = +oo );
		for ( k = 0, i = 0; i < Q; ++i )
			if ( isprime[i] ) { id[p[k] = i] = k; ++k; }
		assert k == P;
		for ( q.put(1,new int[0]), k = 2; k < Q; ++k ) {
			List<Integer> lst = signature(k);
			int []r = new int[lst.size()];
			for ( i = 0; i < lst.size(); ++i )
				r[i] = lst.get(i);
			q.put(k,r);
		}
		for ( ts = scan.nextInt(); ts-->0; ) {
			m = scan.nextInt(); n = scan.nextInt();
			System.out.print("Case #"+(++cs)+": ");
			for ( res = 0, i=0; i<m; ++i, res ^= t ) {
				int []cnt = new int[P], a;
				for ( t=0,j=0; j<n; ++j ) {
					l=(a=q.get(g[i][j]=scan.nextInt())).length;
					for ( k = 0; k < l; ++k ) {
						assert id[a[k]&MSK] != -1;
						assert isprime[a[k]&MSK];
						cnt[id[a[k]&MSK]] += (a[k]>>15);
						t += (a[k]>>15);
					}
				}
			}
			System.out.println(res==0?"NO":"YES");
		}
	}
};


