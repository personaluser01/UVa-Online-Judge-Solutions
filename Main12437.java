/*
 * 12437. Kisu Pari Na 2
 * TOPIC: trees, diameter, dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	InputStreamReader r = new InputStreamReader(System.in);
	private final static int N = (1<<21);
	int []to = new int[N], next = new int[N], last = new int[N], used = new int[N], d = new int[N], diameter = new int[N], p = new int[N], card = new int[N], z = new int[N];
	Queue q = new LinkedList();
	int n,m,E,V,yes;
	void addArcs( int x, int y ) {
		int i = E++, j = E++;
		to[i] = y; next[i] = last[x]; last[x] = i;
		to[j] = x; next[j] = last[y]; last[y] = j;
	}
	int rd() throws IOException {
		int c,n = 0;
		for (;(c=r.read())!=-1 && !('0'<=(char)c && (char)c<='9'); );
		for ( n=c-'0'; (c=r.read())!=-1 && '0'<=(char)c && (char)c<='9'; n=10*n+c-'0' );
		return n;
	}
	public static void main( String ... args ) throws Exception {
		new Main().go();
	}
	int bfs( int src, boolean []seen, List dst, List lst ) {
		int x,y,i,j,r = -1, D = -1;
		for ( q.add(src), used[src] = yes, d[src] = 0, seen[src] = true; !q.isEmpty(); ) {
			x = (Integer)q.poll();
			if ( lst != null )
				lst.add(x);
			if ( d[x] > D ) { D = d[r = x]; }
			for ( i = last[x]; i >= 0; i = next[i] ) {
				if ( seen[y = to[i]] ) continue ;
				seen[y] = true ;
				used[y] = yes;
				d[y] = d[x]+1;
				q.add(y);
			}
		}
		assert D >= 0;
		if ( dst != null ) {
			dst.add(D);
			// System.out.println("Assigning "+dist);
		}
		return r;
	}
	private class Tree implements Comparable<Tree> {
		int diameter, numNodes;
		Tree( int d, int n ) {
			this.diameter = d;
			this.numNodes = n;
		}
		@Override
		public int compareTo( Tree other ) {
			if ( this.numNodes == other.numNodes ) 
				return other.diameter - this.diameter;
			return this.numNodes - other.numNodes;
		}
	}
	void go() throws Exception {
		int i,j,k,l,qr,K;
		Integer dist,dd = Integer.valueOf(-1);
		List lst,fathers,dst;
		for ( int cs = 0, ts = rd(); ts-->0; ) {
			n = rd(); m = rd();
			fathers = new ArrayList();
			dst = new ArrayList();
			lst = new ArrayList();
			for ( E = 0, i = 0; i < n; last[i++] = -1 );
			for ( l = 0; l < m; ++l ) addArcs(rd()-1,rd()-1);
			for ( ++yes, i = 0; i < n; ++i ) 
				if ( used[i] != yes ) {
					j = bfs(i,new boolean[n],null,null);
					diameter[i] = -1;
					dst.clear();
					lst.clear();
					bfs(j,new boolean[n],dst,lst);
					diameter[i] = (Integer)dst.get(0);
					assert diameter[i] >= 0;
					for ( Object o: lst ) 
						p[(Integer)o] = i;
					fathers.add(i);
					card[i] = lst.size();
				}
			m = fathers.size();
			Tree []t = new Tree[m];
			assert t != null;
			k = 0;
			assert m > 0;
			for ( Object o: fathers ) {
				i = (Integer)o;
				t[k++] = new Tree(diameter[i],card[i]);
			}
			assert k == m;
			for ( i = 0; i <= n; z[i++] = -1 );
			for ( i = 0; i < m; i = j ) {
				for ( j = i+1; j < m && t[i].numNodes == t[j].numNodes; ++j );
				z[t[i].numNodes] = t[i].diameter;
			}
			for ( k = n; k >= 0 && z[k] == -1; --k );
			for ( ;k-->0; ) 
				z[k] = Math.max(z[k],z[k+1]);
			bw.write("Case "+(++cs)+":\n");
			Arrays.sort(t);
			for ( qr = rd(); qr-->0; ) {
				K = rd();
				/*Tree tmp = new Tree(N,K);
				i = Arrays.binarySearch(t,tmp);
				assert i < 0;
				i = -i-1;
				if ( i == t.length ) {
					bw.write("impossible\n");
					continue ;
				}
				assert i >= 0;
				assert i < t.length;
				int diam = t[i].diameter;
				assert t[i].numNodes >= K;
				assert i == 0 || t[i-1].numNodes < K;
				*/
				if ( K > n || z[K] == -1 ) {
					bw.write("impossible\n");
					continue ;
				}
				bw.write(""+(2*(K-1)-Math.min(K-1,z[K]))+"\n");
			}
		}
		bw.flush();
	}
}


