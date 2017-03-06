/*
 * 12841. Puzzleland(II)
 * TOPIC: TSP, bitmasks, dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	int ts,n,m,cs = 0;
	final int N = 0x10;
	int []deg = new int[N];
	TreeMap<String,Integer> h;
	String []a = new String[N];
	Scanner scan = new Scanner(System.in);
	int [][]adj = new int[N][N];
	boolean [][]z = new boolean[N][1<<N];
	public static void main ( String [] args ) throws Exception { new Main().go(); }

	class mp implements Comparable<mp> {
			int i,u;
			mp( int i, int u ) {
				this.i = i;
				this.u = u;
			}
			public int compareTo( mp other ) {
				if ( this.i == other.i ) {
					if ( this.u < other.u )
						return -1;
					if ( this.u > other.u )
						return 1;
					return 0;
				}
				return this.i-other.i;
			}
	};
	int [][] parent = new int[N][1<<N];
	int enc( int i, int u ) { return u | (i<<N); }

	String dump( int i, int u ) {
		if ( i == 0 )
			return a[0];
		return dump(parent[i][u]>>N,parent[i][u]&((1<<N)-1))+a[i];
	}

	void go() throws Exception {
		int i,j,k,l,u,v;
		String s1,s2;
		for ( ts = scan.nextInt(); ts-- > 0; ) {
			n = scan.nextInt();
			m = scan.nextInt();
			h = new TreeMap<String,Integer>();
			h.clear();
			for ( i = 0; i < n; ++i )
				deg[i] = 0;
			for ( i = 0; i < n; ++i ) {
				a[i] = scan.next();
				h.put(a[i],i);
			}
			for ( l = 0; l < m; ++l ) {
				i = h.get(s1 = scan.next());
				j = h.get(s2 = scan.next());
				adj[i][deg[i]++] = j;
				adj[j][deg[j]++] = i;
			}
			for ( i = 0; i < n; ++i ) 
				for ( j = 1; j >= 1; )
					for ( j = 0, k = 0; k < deg[i]-1; ++k )
						if ( a[adj[i][k]].compareTo(a[adj[i][k+1]]) > 0 ) {
							l = adj[i][k]; adj[i][k] = adj[i][k+1]; adj[i][k+1] = l; ++j;
						}
			for ( i = 0; i < n; ++i )
				for ( u = 0; u < (1<<n); ++u )
					z[i][u] = false;
			Queue<Integer> q = new LinkedList<Integer>();
			q.add(enc(0,1));
			z[0][1] = true;
			parent[0][1] = -1;
			for ( ;q.size() > 0 && !z[n-1][(1<<n)-1]; ) {
				int nn,mm = q.poll();
				u = mm&((1<<N)-1); i = mm>>N;;
				for ( l = 0; l < deg[i]; ++l ) {
					j = adj[i][l];
					if ( (0 == ((u>>j)&1)) && !z[j][u|(1<<j)] ) {
						z[j][u|(1<<j)] = true;
						parent[j][u|(1<<j)] = mm;
						q.add(enc(j,u|(1<<j)));
					}
				}
			}
			System.out.print("Case "+(++cs)+": ");
			if ( !z[n-1][(1<<n)-1] ) {
				System.out.println("impossible");
				continue ;
			}
			System.out.println(dump(n-1,(1<<n)-1));
		}
	}
}
