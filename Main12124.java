/*
 * 12124. Assemble
 * TOPIC: sorting, greedy, binary search
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x400;
	int n,b,V;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int []len = new int[N];
	class Foo implements Comparable<Foo> {
		int t,w,q;
		Foo( int t, int w, int q ) { this.t = t; this.w = w; this.q = q; }
		public int compareTo( Foo other ) {
			if ( this.w == other.w ) {
				if ( this.q == other.q ) 
					return this.t-other.t;
				if ( this.q > other.q )
					return -1;
				return 1;
			}
			if ( this.w < other.w )
				return -1;
			return 1;
		}
	}
	Foo [][]adj = new Foo[N][N];
	class cmp01 implements Comparator<Foo> {
		public int compare( Foo a, Foo b ) {
			if ( a.q == b.q ) {
				if ( a.w == b.w ) 
					return a.t-b.t;
				if ( a.w < b.w )
					return -1;
				return 1;
			}
			if ( a.q > b.q )
				return -1;
			return 1;
		}
	}
	Foo getWeakest( Set<Foo> s ) {
		return Collections.max(s,new cmp01());
	}
	boolean f( int L ) {
		int i,j,k,cost = 0;
		for ( i = 0; i < V; ++i ) {
			Foo e = null;
			for ( j = 0; j < len[i]; ++j )
				if ( adj[i][j].q >= L ) {
					if ( e == null ) e = adj[i][j];
					else if ( e.w > adj[i][j].w ) 
						e = adj[i][j];
				}
			if ( e == null || e.w+cost > b ) return false ;
			cost += e.w;
		}
		return true ;
	}
	void go() throws Exception {
		int i,j,k,t,ts = scan.nextInt(),cost,ncost=0,good,bad,mid;
		boolean flag;
		Foo ne;
		for (;ts-->0;) {
			Map<String,Integer> m = new TreeMap<String,Integer>();
			n = scan.nextInt(); b = scan.nextInt();
			for ( V = i = 0; i < n; ++i ) {
				String tmp = scan.next();
				if ( !m.containsKey(tmp) ) { m.put(tmp,V); len[V++] = 0; }
				k = m.get(tmp); scan.next();
				j = scan.nextInt(); t = scan.nextInt();
				adj[k][len[k]++] = new Foo(k,j,t);
			}
			for ( good = -1, bad = 1000000001; good+1 < bad; )
				if ( f(mid=(good+bad)/2) ) good = mid;
				else bad = mid;
			System.out.println(good);
		}
	}
};


