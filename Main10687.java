/*
 * 10687. Monitoring the Amazon
 * TOPIC: bfs
 * status: status
 */
import java.io.*;
import java.util.*;

class Main {
	int N = 0x400,n;
	boolean [][]g = new boolean[N][N];
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	class Point2d implements Comparable<Point2d> {
		int x,y,id;
		public int compareTo( Point2d other ) {
			if ( this.x == other.x ) {
				if ( this.y == other.y )
					return this.id-other.id;
				if ( this.y < other.y )
					return -1;
				return 1;
			}
			if ( this.x < other.x )
				return -1;
			return 1;
		}
		Point2d( int x, int y, int id ) { this.x = x; this.y = y; this.id = id; }
		double distTo( Point2d other ) {
			return (this.x-other.x)*(this.x-other.x) + (this.y-other.y)*(this.y-other.y);
		}
	}
	boolean better( Point2d src, Point2d a, Point2d b ) {
		if ( src.distTo(a) < src.distTo(b) )
			return false;
		if ( src.distTo(a) > src.distTo(b) )
			return true;
		return a.compareTo(b) > 0;
	}
	boolean bfs( int src ) {
		Queue<Integer> q = new LinkedList<Integer>();
		int x,y;
		boolean []seen = new boolean[n];
		for ( x = 0; x < n; ++x ) seen[x] = false;
		for ( seen[src] = true, q.add(src); q.size() > 0; )
			for ( x = q.poll(), y = 0; y < n; ++y )
				if ( g[x][y] && !seen[y] ) {
					seen[y] = true; q.add(y);
				}
		for ( x = 0; x < n; ++x )
			if ( !seen[x] )
				return false;
		return true;
	}
	void go() throws Exception {
		int i,j,k,l,t,clos,sec;
		Point2d []p = new Point2d[N];
		while ( (n=scan.nextInt()) != 0 ) {
			for ( i = 0; i < n; ++i )
				for ( g[i][i] = true, j = i+1; j < n; ++j )
					g[i][j]=g[j][i]=false;
			for ( l = 0; l < n; ++l ) {
				i = scan.nextInt();
				j = scan.nextInt();
				p[l] = new Point2d(i,j,l);
			}
			for ( i = 0; i < n; ++i ) {
				clos = (i+1)%n; sec = -1;
				for ( j = 0; j < n; ++j ) {
					if ( i == j ) continue ;
					if ( better(p[i],p[clos],p[j]) ) {
						sec = clos; clos = j;
					}
					else if ( sec == -1 || better(p[i],p[sec],p[j]) )
						sec = j;
				}
				if ( sec == -1 ) sec = clos;
				g[i][clos] = g[i][sec] = true;
			}
			System.out.println(bfs(0)?"All stations are reachable.":"There are stations that are unreachable.");
		}
	}
};

