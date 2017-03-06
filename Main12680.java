/*
 * 12680. Shopping Malls
 * TOPIC: shortest paths
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st;
	double S( double x ) { return x*x; };
	final int N = 0x200, M = 0x800;
	int m,n,E,yes;
	int []to = new int[M], next = new int[M], last = new int[N];
	double []cost = new double[M], d = new double[N];
	public static void main( String [] args ) throws Exception { new Main().go(); };
	class Cell {
		int x,y,z;
		Cell() { x=y=z=0; };
		Cell( int X, int Y, int Z ) { x = X; y = Y; z = Z; };
		double distTo( Cell other ) { return Math.sqrt(S(x-other.x)+S(y-other.y)+S(z-other.z)); };
	};
	Cell []c = new Cell[N];
	void addArcs( int x, int y, String s ) {
		int i = E++, j = E++;
		to[i] = y; next[i] = last[x]; last[x] = i;
		to[j] = x; next[j] = last[y]; last[y] = j;
		if ( s.equals("walking") ) 
			cost[i] = cost[j] = c[x].distTo(c[y]);
		else if ( s.equals("lift") ) 
			cost[i] = cost[j] = 1;
		else if ( s.equals("stairs") ) 
			cost[i] = cost[j] = c[x].distTo(c[y]);
		else {
			cost[i] = 1;
			cost[j] = 3*c[x].distTo(c[y]);
		}
	};
	class Cmp implements Comparator<Integer> {
		public int compare( Integer x, Integer y ) {
			if ( d[x] == d[y] ) return 0;
			return d[x]<d[y]?-1:1;
		};
	};
	PriorityQueue<Integer> pq;
	int []seen = new int[N], p = new int[N];
	String dump( int src, int x ) {
		if ( x == src ) return Integer.toString(x); 
		return dump(src,to[p[x]^1])+" "+Integer.toString(x);
	};
	String dijkstra( int src, int dst ) {
		int x,y,i,j,k;
		pq = new PriorityQueue<Integer>(new Cmp());
		for ( seen[src] = ++yes, p[src] = -1, d[src] = 0, pq.add(src); !pq.isEmpty(); )
			for ( i = last[x = pq.poll()]; i >= 0; i = next[i] ) 
				if ( seen[y=to[i]] != yes || d[y] > d[x]+cost[i] ) {
					seen[y] = yes; d[y] = d[x]+cost[p[y] = i];
					pq.add(y);
				}
		return dump(src,dst);
	};
	void go() throws Exception {
		int i,j,k,ts = 0;
		String s;
		for (;(s=br.readLine())!=null;br.readLine()) {
			if ( ++ts > 1 ) System.out.println();
			st = new StringTokenizer(s);
			n = Integer.parseInt(st.nextToken());
			m = Integer.parseInt(st.nextToken());
			for ( E = 0, i = 0; i < n; last[i++] = -1 );
			for ( i = 0; i < n; ++i ) {
				st = new StringTokenizer(s = br.readLine());
				int zz = 5*(Integer.parseInt(st.nextToken())-1), xx = Integer.parseInt(st.nextToken()), yy = Integer.parseInt(st.nextToken());
				c[i] = new Cell(xx,yy,zz);
			}
			for ( k = 0; k < m; ++k ) {
				s = br.readLine();
				st = new StringTokenizer(s);
				i = Integer.parseInt(st.nextToken());
				j = Integer.parseInt(st.nextToken());
				addArcs(i,j,st.nextToken());
			}
			for ( k = Integer.parseInt(br.readLine()); k-- > 0; ) {
				st = new StringTokenizer(br.readLine());
				i = Integer.parseInt(st.nextToken());
				j = Integer.parseInt(st.nextToken());
				System.out.println(dijkstra(i,j));
			}
		}
	}
};

