/*
 * 10021. Cube in the Labyrinth
 * TOPIC: bfs
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 10,PERMS = 24,oo = (1<<29);
	int m,n,sx,sy,tx,ty;
	int []dx = {-1,0,1,0}, dy = {0,-1,0,1};
	char [][]p = {{4,1,5,3,2,0},{0,4,2,5,3,1},{5,1,4,3,0,2},{0,5,2,4,1,3}};
	int [][]multiplication_table = new int[PERMS][4];
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st;
	String s;
	boolean [][][][]isWall = new boolean[N][N][N][N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	boolean validCell( int x, int y ) { return 0<=x&&x<=m-1&&0<=y&&y<=n-1; }
	class Perm implements Comparable<Perm> {
		char []c;
		Perm( char []c ) {
			this.c = new char[6];
			for ( int i = 0; i < 6; ++i ) 
				this.c[i] = c[i];
		}
		Perm() {
			this.c = new char[6];
			for ( int i = 0; i < 6; ++i )
				this.c[i] = (char)i;
		}
		Perm multiply( Perm other ) {
			char []a = new char[6];
			for ( int i = 0; i < 6; ++i ) 
				a[i] = this.c[(int)other.c[i]];
			return new Perm(a);
		}
		public int compareTo( Perm other ) {
			for ( int i = 0; i < 6; ++i ) 
				if ( this.c[i] != other.c[i] ) 
					return this.c[i]<other.c[i]?-1:1;
			return 0;
		}
		String toStr() {
			String r = "";
			for ( int i = 0; i < 6; ++i )
				r += Integer.toString(((int)this.c[i]))+" ";
			return r;
		}
	}
	Perm []e = {new Perm(p[0]),new Perm(p[1]),new Perm(p[2]),new Perm(p[3])};
	class Cube implements Comparable<Cube> {
		int x,y,t;
		Cube( int x, int y, int t ) { this.x = x; this.y = y; this.t = t; }
		Cube rollOver( int k ) {
			int nx=this.x+dx[k],ny=this.y+dy[k];
			if ( (!validCell(nx,ny)) || isWall[this.x][this.y][nx][ny] )
				return null;
			return new Cube(nx,ny,multiplication_table[this.t][k]);
		}
		public int compareTo( Cube other ) {
			if ( this.x == other.x ) {
				if ( this.y == other.y ) 
					return this.t-other.t;
				return this.y<other.y?-1:1;
	 		}
			return this.x<other.x?-1:1;
		}
	}

	TreeMap<Perm,Integer> T = new TreeMap<Perm,Integer>();
	Queue<Perm> q = new LinkedList<Perm>();
	Queue<Cube> Q = new LinkedList<Cube>();
	int [][][]d = new int[N][N][PERMS];

	void go() throws Exception {
		int ts,i,j,k,t,x,y,mm = 0,w;
		boolean []isGood = new boolean[PERMS];
		Perm u = new Perm(),v;
		for ( i = 0; i < PERMS; ++i ) isGood[i] = false;

		T.clear(); T.put(u,mm++);
		for ( q.add(u); q.size() > 0; ) 
			for ( u=q.poll(), i = 0; i < 4; ++i ) 
				if ( !T.containsKey(v=u.multiply(e[i])) ) { T.put(v,mm++); q.add(v); }

		for ( Map.Entry<Perm,Integer> entry: T.entrySet() ) {
			u = entry.getKey(); i = entry.getValue();
			isGood[i] = (((int)u.c[5])==5);
			for ( j = 0; j < 4; ++j ) {
				v = u.multiply(e[j]);
				k = T.get(v);
				multiplication_table[i][j] = k;
			}
		}

		// System.out.println((new Perm()).multiply(e[0]).toStr());

		st = new StringTokenizer(br.readLine());
		ts = Integer.parseInt(st.nextToken());

		for ( br.readLine(); ts-- > 0; ) {
			st = new StringTokenizer(br.readLine());
			m = Integer.parseInt(st.nextToken());
			n = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(br.readLine());
			sx = Integer.parseInt(st.nextToken())-1;
			sy = Integer.parseInt(st.nextToken())-1;
			st = new StringTokenizer(br.readLine());
			tx = Integer.parseInt(st.nextToken())-1;
			ty = Integer.parseInt(st.nextToken())-1;
			for ( i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j )
					for ( k = 0; k < m; ++k )
						for ( t = 0; t < n; ++t )
							isWall[i][j][k][t] = false;
			for ( k = 0; (s=br.readLine()) != null && !s.equals(""); ) {
				if ( s.equals("v") ) { k = 2; continue ; }
				if ( s.equals("h") ) { k = 3; continue ; }
				st = new StringTokenizer(s);
				x = Integer.parseInt(st.nextToken())-1;
				y = Integer.parseInt(st.nextToken())-1;
				assert validCell(x+dx[k],y+dy[k]);
				isWall[x][y][x+dx[k]][y+dy[k]] = isWall[x+dx[k]][y+dy[k]][x][y] = true;
			}
			for ( i = 0; i < m; ++i )
				for ( j = 0; j < n; ++j ) 
					for ( k = 0; k < PERMS; ++k )
						d[i][j][k] = +oo;
			Q.add(new Cube(sx,sy,0)); d[sx][sy][0] = 0; w = +oo;
			while ( Q.size() > 0 ) {
				Cube box = Q.poll(),nbox;
				if ( box.x == tx && box.y == ty ) 
					if ( isGood[box.t] && w > d[box.x][box.y][box.t] )
						w = d[box.x][box.y][box.t];
				if ( w <= d[box.x][box.y][box.t] ) continue ;
				for ( i = 0; i < 4; ++i ) {
					if ( (nbox = box.rollOver(i)) == null )
						continue ;
					if ( d[nbox.x][nbox.y][nbox.t] > d[box.x][box.y][box.t]+1 ) {
						 d[nbox.x][nbox.y][nbox.t] = d[box.x][box.y][box.t]+1;
						 Q.add(nbox);
					}
				}
			}
			System.out.println(w<+oo?w:"No solution");
			if ( ts > 0 ) System.out.println("");
		}
	}
};


