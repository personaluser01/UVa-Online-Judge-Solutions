/*
 * 12430. Grand Wedding
 * TOPIC: binary search, bfs, odd cycles, bipartite graphs
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	InputStreamReader r = new InputStreamReader(System.in);
	private static final int N = (1<<21), L = 21;
	int m,n,E,V,yes;
	int []to = new int[N], next = new int[N], w = new int[N], last = new int[N], d = new int[N],seen = new int[N], parent = new int[N];
	Queue<Integer> q = new LinkedList<>();
	int rd() throws Exception {
		int n = 0, c;
		for (;(c = r.read()) != -1 && !('0'<=(char)c && (char)c<='9'););
		for ( n = c-'0'; (c=r.read()) != -1 && '0'<=(char)c && (char)c<='9'; n = 10*n+c-'0' );
		return n;
	}
	int [][]anc = new int[N][L];
	void addArcs( int x, int y, int cost ) {
		int i = E++, j = E++;
		to[i] = y; next[i] = last[x]; last[x] = i; w[i] = cost;
		to[j] = x; next[j] = last[y]; last[y] = j; w[j] = cost;
	}
	public static void main( String ... args ) throws Exception {
		new Main().go();
	}
	boolean bfs( int src, int K ) {
		int x,y,i;
		for ( q.clear(), q.add(src),parent[src] = -1,  d[src] = 0, seen[src] = yes; !q.isEmpty(); )
			for ( i = last[x = q.poll()]; i >= 0; i = next[i] )
				if ( parent[x] != (y = to[i]) && w[i] < K && seen[y] != yes ) {
					d[y] = d[x]+1;
					seen[y] = yes;
					parent[y] = x;
					q.add(y);
				}
				else if ( parent[x] != y && seen[y] == yes && w[i] < K && d[y] == d[x] )
					return false ;
		return true ;
	}
	boolean bicolorable( int K ) {
		++yes;
		for ( int x = 0; x < n; ++x )
			if ( seen[x] != yes && !bfs(x,K) ) 
				return false ;
		return true ;
	}
	void go() throws Exception {
		int i,j,k,l,ts = rd(),good,bad,mid,cs = 0;
		for ( ;ts-->0; ) {
			n = rd(); m = rd();
			// if ( ++cs == 307 ) System.out.println("Here "+n+" "+m);
			for ( good = (1<<29), bad = 0, E = 0, V = n, i = 0; i < n; last[i++] = -1 );
			for ( l = 0; l < m; ++l ) {
				i = rd()-1;
				j = rd()-1;
				k = rd();
				addArcs(i,j,k);
				bad = Math.max(bad,k);
				good = Math.min(good,k);
			}
			if ( bicolorable(++bad) ) {
				bw.write("0\n");
				continue ;
			}
			l = good;
			assert bicolorable(good);
			for ( ;good+1<bad; ) {
				mid = (good+bad)/2;
				if ( bicolorable(mid) ) 
					good = mid;
				else bad = mid;
			}
			assert !bicolorable(bad);
			if ( good == l ) bw.write("-1\n");
			else bw.write(good+"\n");
		}
		bw.flush();
	}
}

