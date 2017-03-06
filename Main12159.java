/*
 * 12159. Gun Fight
 * TOPIC: graphs
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 512, Q = (N+N);
	int n,cs = 0,id01,id02,R,S=0,T=1,yes,head,tail,cnt;
	int [][]v = new int[2][N];
	int []m = new int[2], seen = new int[N], q = new int[Q];
	int [][]mate = new int[2][N], deg = new int[2][N];
	int [][][]adj = new int[2][N][N];
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Ponto {
		public int x,y,w;
		boolean flag;
		Ponto( int x, int y, int w ) { this.x = x; this.y = y; this.w = w; this.flag = false; }
		public int distTo( Ponto other ) { return (this.x-other.x)*(this.x-other.x)+(this.y-other.y)*(this.y-other.y); }
		public void flip() { this.flag = !this.flag; }
	}
	Ponto []p = new Ponto[N];
	int sign( Ponto a, Ponto b, Ponto c ) {
		int u = (c.x-a.x), v = (c.y-a.y), p = (b.x-a.x), q = (b.y-a.y);
		return u*q-v*p>0?1:-1;
	}
	boolean altPath( int x ) {
		int i,y;
		if ( seen[x] == yes ) 
			return false;
		for ( seen[x] = yes, i = 0; i < deg[S][x]; ++i )
			if ( mate[T][y=adj[S][x][i]] == -1 || altPath(mate[T][y]) ) {
				mate[T][mate[S][x]=y]=x;
				return true;
			}
		return false;
	}
	int bpm() {
		int k,x;
		boolean flag;
		for ( head = tail = cnt = 0, x = 0; x < m[S]; ++x ) { q[tail++] = x; tail &= (Q-1); ++cnt; }
		do {
			for ( flag = false, ++yes, k = cnt; k-- > 0; ) {
				x = q[head++]; head &= (Q-1); --cnt;
				if ( altPath(x) ) flag = true;
				else {
					q[tail++] = x; tail &= (Q-1); ++cnt;
				}
			}
		} while ( flag );
		return m[S]-cnt;
	}
	void go() throws Exception {
		int i,j,k,t,l;
		while ( (n = scan.nextInt()) != 0 ) {
			System.out.print("Case "+(++cs)+": ");
			for ( i = 0; i < n; ++i ) {
				j = scan.nextInt(); k = scan.nextInt();
				p[i] = new Ponto(j,k,scan.nextInt());
			}
			id01 = scan.nextInt()-1;
			id02 = scan.nextInt()-1;
			R = scan.nextInt();
			for ( i = 0; i < n; ++i ) {
				if ( i == id01 || i == id02 || p[i].w == 0 ) continue ;
				if ( sign(p[id01],p[id02],p[i]) < 0 ) 
					p[i].flip();
			}
			for ( t = 0; t <= 1; m[t++] = 0 );
			for ( i = 0; i < n; ++i )
				if ( i != id01 && i != id02 && p[i].w > 0 ) {
					if ( p[i].flag ) v[S][m[S]++] = i;
					else v[T][m[T]++] = i;
				}
			for ( t = 0; t <= 1; ++t )
				for ( i = 0; i < m[t]; ++i )
					deg[t][i] = 0;
			if ( m[S] > m[T] ) { t = S; S = T; T = t; }
			for ( R *= R, i = 0; i < m[S]; ++i )
				for ( j = 0; j < m[T]; ++j )
					if ( p[v[S][i]].w > p[v[T][j]].w && p[v[S][i]].distTo(p[v[T][j]]) <= R ) {
						adj[S][i][deg[S][i]++] = j;
						adj[T][j][deg[T][j]++] = i;
					}
			for ( t = 0; t <= 1; ++t )
				for ( i = 0; i < m[t]; ++i )
					mate[t][i] = -1;
			System.out.println(bpm());
		}
	}
};

