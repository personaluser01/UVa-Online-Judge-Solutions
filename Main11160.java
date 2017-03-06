/*
 * 11160. Going Together
 * TOPIC: bfs
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int SH = 4, N = 11, oo = (1<<29);
	Scanner scan = new Scanner(System.in);
	int m,n;
	char [][]g = new char[N][N];

	int BIT( int k )  { return (1<<k); }
	int MASK( int k ) { return BIT(k)-1; }
	boolean vc( int x, int y ) { return 0<=x && x<m && 0<=y && y<n; }
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int enc( int x, int y ) { return (x|(y<<SH)); }
	int []dx = {-1,0,1,0}, dy = {0,1,0,-1};

	class Foo implements Comparable<Foo> {
		int u;
		Foo( int []x, int []y ) {
			int []c = new int[3];
			for ( int i = 0; i < 3; ++i )
				c[i] = enc(x[i],y[i]);
			Arrays.sort(c);
			this.u = 0;
			for ( int i = 0; i < 3; ++i )
				this.u |= (c[i] << (i*(SH+SH)));
		}
		public int compareTo( Foo other ) { return this.u-other.u; }
		Foo dvigai( int t ) {
			int []x = new int[3], y = new int[3], nx = new int[3], ny = new int[3];
			int i,j,k;
			for ( i = 0; i < 3; ++i ) {
				nx[i] = (x[i]=(this.u>>((SH+SH)*i))&MASK(SH))   +dx[t];
				ny[i] = (y[i]=(this.u>>((SH+SH)*i+SH))&MASK(SH))+dy[t];
				if ( !vc(nx[i],ny[i]) || g[nx[i]][ny[i]] == '#' ) {
					nx[i] = x[i]; ny[i] = y[i];
					continue ;
				}
			}
			for ( boolean flag = true; flag; )
			for ( flag = false, i = 0; i < 3; ++i )
				for ( j = 0; j < 3; ++j )
					if ( i != j && nx[i] == nx[j] && ny[i] == ny[j] ) {
						assert !(x[i]==x[j] && y[i]==y[j]);
						nx[i] = x[i]; ny[i] = y[i];
						nx[j] = x[j]; ny[j] = y[j];
						assert !(nx[i]==nx[j] && ny[i]==ny[j]);
						flag = true;
					}
			return new Foo(nx,ny);
		}
	}

	Map<Foo,Integer> h = new TreeMap<Foo,Integer>();
	Queue<Foo> q = new LinkedList<Foo>();

	int bfs( Foo src, Foo dst ) {
		int i,d;
		Foo x,y;
		h.clear();
		for(;q.size()>0;q.poll());
		for ( h.put(src,0), q.add(src); q.size() > 0 && !h.containsKey(dst); ) 
			for ( d = h.get(x=q.poll()), i = 0; i < 4; ++i )
				if ( (y=x.dvigai(i)) != null )
					if ( !h.containsKey(y) ) {
						h.put(y,d+1); q.add(y);
					}
		return h.containsKey(dst)?h.get(dst):+oo;
	}

	void go() throws Exception {
		int i,j,k,l,w,cs = 0;
		int[]sx = new int[3], sy = new int[3], tx = new int[3], ty = new int[3];
		Foo Target,src;

		for ( int ts = scan.nextInt(); ts-- > 0; ) {
			m = n = scan.nextInt();
			for ( k = l = i = 0; i < m; ++i ) {
				String tmp = scan.next();
				for ( j = 0; j < n; ++j )
					if ( (g[i][j] = tmp.charAt(j)) == 'X' ) {
						tx[k] = i; ty[k++] = j;
					}
					else if ( 'A' <= g[i][j] && g[i][j] <= 'C' ) {
						sx[l] = i; sy[l++] = j;
					}
			}
			assert k == 3;
			assert l == 3;
			Target = new Foo(tx,ty);
			src = new Foo(sx,sy);
			System.out.println("Case "+(++cs)+": "+((w=bfs(src,Target))<+oo?w:"trapped"));
		}
	}
};


