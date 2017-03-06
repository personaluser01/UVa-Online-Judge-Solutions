/*
 * 10214. Critical Wave
 * TOPIC: LIS, dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x400, oo = (1<<29), UP = 0, DOWN = 1;
	int n;
	Foo []c;
	int [][]z = new int[2][N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Foo implements Comparable<Foo> {
		int x,y;
		Foo ( int x, int y ) { this.x = x; this.y = y; }
		public int compareTo( Foo other ) {
			if ( this.x == other.x ) {
				if ( this.y == other.y ) 
					return 0;
				return this.y<other.y?-1:1;
			}
			return this.x<other.x?-1:1;
		}
	}
	void go() throws Exception {
		int i,j,k,t,l,w;
		for (;scan.hasNext();System.out.println(w)) {
			c=new Foo[n=scan.nextInt()];
			for ( i = 0; i < n; ++i ) {
				j = scan.nextInt();
				k = scan.nextInt();
				c[i] = new Foo(j,k);
			}
			for ( Arrays.sort(c), t = UP; t <= DOWN; ++t )
				for ( i = 0; i <= n; z[t][i++] = 1 );
			for ( i = 0; i < n; ++i ) 
				for ( j = 0; j < i; ++j ) {
					if ( c[j].x < c[i].x && c[j].y-c[i].y == 2 )
						z[DOWN][i+1] = Math.max(z[DOWN][i+1],z[UP][j+1]+1);
					if ( c[j].x < c[i].x && c[j].y-c[i].y == -2 )
						z[UP][i+1] = Math.max(z[UP][i+1],z[DOWN][j+1]+1);
				}
			for ( w = 0, i = 1; i <= n; ++i )
				for ( t = UP; t <= DOWN; ++t )
					w = Math.max(w,z[t][i]);
		}
	}
};

