/*
 * 1600. Patrol Robot
 * TOPIC: bfs
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x20, oo = (1<<29);
	int m,n,K;
	int [][]g = new int[N][N];
	int [][][]d = new int[N][N][N];
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	boolean validCell( int x, int y ) { return 0<=x && x<=m-1 && 0<=y && y<=n-1; }
	class Foo {
		int x,y,k;
		Foo( int x, int y, int k ) { this.x = x; this.y = y; this.k = k; }
	}
	Queue<Foo> q = new LinkedList<Foo>();
	void go() throws Exception {
		int i,j,k,x,y,nx,ny,dx,dy,ts = scan.nextInt(),w;
		for ( ;ts-- > 0; ) {
			m = scan.nextInt();
			n = scan.nextInt();
			K = scan.nextInt();
			for ( i = 0; i < m; ++i ) 
				for ( j = 0; j < n; ++j ) 
					g[i][j] = scan.nextInt();
			for ( i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j )
					for ( k = 0; k <= K; ++k )
						d[i][j][k] = +oo;
			if ( g[0][0] == 1 ) {
				if ( K >= 1 ) {
					d[0][0][1] = 1; 
					q.add(new Foo(0,0,1)); 
				}
			}
			else {
				d[0][0][0] = 1;
				q.add(new Foo(0,0,0));
			}
			for ( w = +oo; q.size() > 0; ) {
				Foo r = q.poll();
				if ( r.x == m-1 && r.y == n-1 ) 
					if ( w > d[r.x][r.y][r.k] ) w = d[r.x][r.y][r.k];
				if ( d[r.x][r.y][r.k] >= w ) continue ;
				for ( dx = r.x-1; dx <= r.x+1; ++dx )
					for ( dy = r.y-1; dy <= r.y+1; ++dy )
						if ( Math.abs(dx-r.x)+Math.abs(dy-r.y) == 1 )
							if ( validCell(dx,dy) ) {
								if ( g[dx][dy] == 1 ) {
									if ( r.k+1 <= K && d[dx][dy][r.k+1] > d[r.x][r.y][r.k]+1 ) {
										d[dx][dy][r.k+1] = d[r.x][r.y][r.k]+1;
										q.add(new Foo(dx,dy,r.k+1));
									}
								}
								else {
									if ( d[dx][dy][0] > d[r.x][r.y][r.k]+1 ) {
										d[dx][dy][0] = d[r.x][r.y][r.k]+1;
										q.add(new Foo(dx,dy,0));
									}
								}
							}
			}
			System.out.println(w<+oo?w-1:-1);
		}
	}
};
