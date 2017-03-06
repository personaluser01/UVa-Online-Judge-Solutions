/*
 * 1395. Slim Span
 * TOPIC: minimum spanning tree, minimum bottleneck spanning tree
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	InputStreamReader r = new InputStreamReader(System.in);
	private final static int oo = (1<<29), N = 0x80;
	int rd() throws Exception {
		int ch,n = 0;
		for(;(ch = r.read()) != -1 && !('0'<=(char)ch&&(char)ch <='9'););
		for (n=ch-'0';(ch=r.read())!= -1 && '0'<=(char)ch&&(char)ch<='9';n=10*n+ch-'0');
		return n;
	}
	public static void main( String ... args ) throws Exception {
		new Main().go();
	}
	class Edge implements Comparable<Edge> {
		int x,y;
		int w,oldw;
		Edge( int x, int y, int w ) {
			this.x = x;
			this.y = y;
			this.oldw = this.w = w;
		}
		public int compareTo( Edge other ) {
			if ( w == other.w ) 
				return 0;
			return w<other.w?-1:1;
		}
	}
	Set<Integer> s;
	Edge []e;
	int m,n;
	int []p = new int[N], rank = new int[N];
	int find( int x ) {
		return p[x] = (p[x]==x?x:find(p[x]));
	}
	void link( int x, int y ) {
		if ( rank[x] > rank[y] )
			p[y] = x;
		else {
			p[x] = y;
			if ( rank[x] == rank[y] )
				++rank[y];
		}
	}
	void merge( int x, int y ) {
		link(find(x),find(y));
	}
	void go() throws Exception {
		int i,j,k,l,curMaxWeight,ans,edges;
		for ( ;; ) {
			n = rd();
			m = rd();
			if ( m == 0 && n == 0 ) break ;
			s = new TreeSet<Integer>();
			e = new Edge[m];
			for ( l = 0; l < m; ++l ) {
				i = rd(); j = rd(); k = rd();
				e[l] = new Edge(--i,--j,k);
				s.add(k);
			}
			ans = +oo;
			for ( Integer weight: s ) {
				for ( i = 0; i < m; ++i ) 
					if ( e[i].oldw < weight )
						e[i].w = +oo;
					else e[i].w = e[i].oldw-weight;
				Arrays.sort(e);
				for ( i = 0; i < n; ++i ) rank[p[i] = i] = 0;
				curMaxWeight = -1; edges = 0;
				for ( l = 0; l < m && e[l].w < +oo; ++l ) {
					i = e[l].x; j = e[l].y;
					if ( find(i) != find(j) ) {
						merge(i,j);
						++edges;
						if ( e[l].w > curMaxWeight ) {
							curMaxWeight = e[l].w;
						}
					}
				}
				assert edges<=n-1;
				if ( edges == n-1 ) {
					assert curMaxWeight >= 0;
				}
				if ( edges == n-1 && curMaxWeight < ans )
					ans = curMaxWeight;
			}
			if ( ans == +oo ) ans = -1;
			bw.write(ans+"\n");
		}
		bw.flush();
	}
}

