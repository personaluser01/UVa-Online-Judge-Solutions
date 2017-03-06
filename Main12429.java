/*
 * 12429. Finding Magic Triplets
 * TOPIC: segment trees, number theory, dp, neat
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	InputStreamReader r = new InputStreamReader(System.in);
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	int n,K,m;
	private static final int N = (1<<17), Q = (N<<1);
	private static final double tol = 1e-9;
	int getInt() throws Exception {
		int n = 0,c;
		for ( ;(c=r.read()) != -1 && !('0' <= (char)c && (char)c <= '9'); );
		for ( n = c-'0'; (c=r.read()) != -1 && '0'<=(char)c && (char)c<='9'; n = 10*n+c-'0' );
		return n;
	}
	static class Pair<T,V> {
		T x;
		V y;
		Pair( T x, V y ) {
			this.x = x;
			this.y = y;
		}
	}
	private class SegmentTree {
		private long []tr,h;
		SegmentTree() {
			tr = new long[(K<<2)+0x400];
			h  = new long[(K<<2)+0x400];
		}
		public void update( int qi, int qj, int dt ) {
			update(1,0,K-1,qi,qj,dt);
		}
		private void update( int v, int i, int j, int qi, int qj, long dt ) {
			int k = (i+j)/2;
			if ( qi > j || qj < i ) return ;
			if ( qi <= i && j <= qj ) {
				h[v] += (j-i+1)*dt;
				return ;
			}
			update(2*v,i,k,qi,qj,dt);
			update(2*v+1,k+1,j,qi,qj,dt);
		}
		int findM( int x ) {
			if ( x < K ) {
				return 0;
			}
			if ( 0 == (x%K) )
				return x/K;
			int L = (int)(Math.ceil((x-K+0.00)/K)+tol);
			int R = (int)(Math.floor((x-1+0.00)/K)+tol);
			assert L <= R;
			assert R-L<=1;
			if ( L != R ) System.out.println(L+" "+R);
			assert L == R;
			return L;
		}
		List<Pair<Integer,Integer>> intervals( int L, int R ) {
			List<Pair<Integer,Integer>> lst = new ArrayList<>();
			assert R-L+1 <= K;
			L %= K; R %= K;
			if ( L <= R ) 
				lst.add(new Pair<Integer,Integer>(L,R));
			else {
				lst.add(new Pair<Integer,Integer>(L,K-1));
				lst.add(new Pair<Integer,Integer>(0,R));
			}
			return lst;
		}
		long query( int key ) {
			return query(1,0,K-1,key,key);
		}
		long query( int v, int i, int j, int qi, int qj ) {
			int k = (i+j)/2;
			if ( qi > j || qj < i )
				return 0L;
			if ( qi <= i && j <= qj ) {
				tr[v] += h[v]; h[v] = 0;
				return tr[v];
			}
			if ( h[v] >= 1 ) {
				h[2*v] += h[v]/(j-i+1)*(k-i+1);
				h[2*v+1] += h[v]/(j-i+1)*(j-k);
				tr[v] += h[v];
				h[v] = 0;
			}
			return query(2*v,i,k,qi,qj)+query(2*v+1,k+1,j,qi,qj);
		}
	}
	public static void main( String ... args ) throws Exception {
		new Main().go();
	}
	int T( int x ) {
		long t = x;
		t = t*t*t; t %= K;
		assert 0 <= t && t < K;
		return (int)t;
	}
	void go() throws Exception {
		int ts = getInt(),cs = 0;
		long ans;
		SegmentTree s;
		for (;ts-->0;) {
			n = getInt();
			K = getInt();
			s = new SegmentTree();
			s.update((1+1*1)%K,(1+1*1)%K,1); ans = s.query(T(1));
			for ( int x = 2; x <= n; ++x ) {
				int tau = (int)((((long)x)*((long)x))%K);
				m = s.findM(x);
				if ( m > 0 ) s.update(0,K-1,m);
				if ( m*K+1 <= x ) {
					List<Pair<Integer,Integer>> lst = s.intervals(m*K+1+tau,x+tau);
					for ( Pair<Integer,Integer> p: lst ) 
						s.update(p.x,p.y,1);
				}
				ans += s.query(T(x));
			}
			bw.write("Case "+(++cs)+": "+ans+"\n");
		}
		bw.flush();
	}
}





