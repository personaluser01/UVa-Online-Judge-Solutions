/*
 * 824. Coast Tracker
 * TOPIC: ad hoc, moving directions
 * status: status
 */
import java.io.*;
import java.util.*;

class Main {
	int []dx = {0,-1,-1,-1,0,1,1,1};
	int []dy = {1,1,0,-1,-1,-1,0,1};
	int whichDirection( int sx, int sy, int tx, int ty ) {
		for ( int i = 0; i < 8; ++i )
			if ( dx[i] == tx-sx && dy[i] == ty-sy )
				return i;
		return -1;
	}
	Scanner scan = new Scanner(System.in);
	public static void main ( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int []xx = new int[8];
		int []yy = new int[8];
		int []s = new int[8];
		int i,j,k,d,x,y,nx,ny;
		while ( (x=scan.nextInt()) != -1 ) {
			y=scan.nextInt();
			d=scan.nextInt();
			for ( i = 0; i < 8; ++i ) {
				nx = scan.nextInt();
				ny = scan.nextInt();
				j = whichDirection(x,y,nx,ny);
				xx[j] = nx;
				yy[j] = ny;
				s[j] = scan.nextInt();
			}
			for ( j = ((d+6)&7), i = 0; i < 8; ++i, j += 1, j &= 7 ) 
				if ( 1 == s[j] ) break ;
			System.out.printf("%d\n",j);
		}
	}
};


