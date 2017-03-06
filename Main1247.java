/*
 * 1247. Interstar Transport
 * TOPIC: floyd-warshall
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 32, oo = (1<<29);
	Scanner scan = new Scanner(System.in);
	int []deg = new int[N];
	char []o = new char[N];
	int n,m,L;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int [][]d = new int[N][N], p = new int[N][N];
	class Edge {
		int y,cost;
		Edge( int y, int cost ) { this.y = y; this.cost = cost; }
	}
	Edge [][]adj = new Edge[N][N];
	void dump( int x, int y ) {
		if ( x == y ) {
			return ;
		}
		if ( p[x][y] == x ) {
			o[L++] = (char)(x+'A');
			return ;
		}
		dump(x,p[x][y]);
		// o[L++] = (char)(p[x][y]+'A');
		dump(p[x][y],y);
	}
	void go() throws Exception {
		int i,j,k,qr;
		n = scan.nextInt();
		m = scan.nextInt();
		for ( i = 0; i < N; ++i ) deg[i] = 0;
		for ( i = 0; i < N; ++i )
			for ( p[i][i] = i, d[i][i] = 0, j = i+1; j < N; ++j )
				d[j][i] = d[i][j] = +oo;
		for ( ;m-- > 0; ) {
			i = scan.next().charAt(0)-'A';
			j = scan.next().charAt(0)-'A';
			k = scan.nextInt();
			adj[i][deg[i]++] = new Edge(j,k);
			adj[j][deg[j]++] = new Edge(i,k);
			d[i][j] = d[j][i] = k;
			p[i][j] = i; p[j][i] = j;
		}
		for ( k = 0; k < N; ++k )
			for ( i = 0; i < N; ++i )
				for ( j = 0; j < N; ++j )
					if ( d[i][k] < +oo && d[k][j] < +oo )
						if ( d[i][k]+d[k][j] < d[i][j] ) {
							d[i][j] = d[i][k]+d[k][j];
							p[i][j] = k;
						}
		for ( qr = scan.nextInt(); qr-- > 0; ) {
			i = scan.next().charAt(0)-'A';
			j = scan.next().charAt(0)-'A';
			for ( L = 0, dump(i,j), i = 0; i < L; System.out.print(o[i++]+" ") );
			System.out.println((char)(j+'A'));
		}
	}
};

