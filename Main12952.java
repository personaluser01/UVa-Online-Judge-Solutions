/*
 * 12952. Tri-du
 * TOPIC: probability, combinatorics, neat, easy
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	int []cnt = new int[53];
	static long [][]c = new long[20][20];

	public static void main( String ... args ) throws Exception {
		int i,j,k;
		for ( i = 0; i < 20; ++i )
			c[i][0] = 1L;
		for ( i = 1; i < 20; ++i )
			for ( j = 1; j <= i; ++j )
				c[i][j] = c[i-1][j]+c[i-1][j-1];
		new Main().go();
	}

	long getDenom() {
		return 47*48*49/6;
	}

	long P( int x, int y ) {
		return y<x ? c[x-2][1]*c[4][2]*45+c[3][2]*46 : c[x-1][1]*c[4][2]*45;
	}

	long winningProb( int x, int y, int z ) {
		int r,other;
		if ( x == y && y == z ) { //three of a kind
			r = x;
			return c[12][1]*c[4][2]*45 + 4*(r-1);
		}
		if ( x == y && y != z ) {
			r = x; other = z;
			return P(r,other);
		}
		if ( x == z && x != y ) {
			r = x; other = y;
			return P(r,other);
		}
		if ( y == z && y != x ) {
			r = z; other = x;
			return P(r,other);
		}
		return 0;
	}

	void go() throws Exception {
		StringTokenizer st;
		String s;
		long w;
		int x,y,z = 0,i;
		for ( ;(s = br.readLine()) != null && !s.equals("#"); ) {
			st = new StringTokenizer(s);
			for ( i = 1; i <= 13; ++i )
				cnt[i] = 4;
			x = Integer.parseInt(st.nextToken());
			y = Integer.parseInt(st.nextToken());
			--cnt[x]; --cnt[y]; w = -1;
			for ( i = 1; i <= 13; ++i ) {
				if ( 0 == cnt[i] ) continue ;
				--cnt[i];
				if ( winningProb(x,y,i) > w ) 
					w = winningProb(x,y,z = i);
				++cnt[i];
			}
			bw.write(z+"\n");
		}
		bw.flush();
	}
};


