/*
 * 11497. Set
 * TOPIC: ad hoc
 * status: WA
 */
import java.io.*;
import java.util.*;

class Main {

	static final int N = 30100, M = 27*27*27+8, oo = (1<<29);
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	int []c = new int[N], z = new int[M];
	int []bin = new int[9];
	int n;

	int readCard() throws Exception {
		String s = br.readLine();
		StringTokenizer st = new StringTokenizer(s);
		String a=st.nextToken(),b=st.nextToken();
		return num(a)*3+fig(b);
	}

	static int num( String s ) {
		switch ( s ) {
			case "um": return 0;
			case "dois": return 1;
			default: return 2;
		}
	}

	static int fig( String s ) {
		switch ( s.charAt(0) ) {
			case 'c': return 0;
			case 'q': return 1;
			default: return 2;
		}
	}

	public static void main( String ... args ) throws Exception { new Main().go(); }

	boolean isSet( int i, int j, int k ) {
		boolean x = (i/3 == j/3 && j/3 == k/3), y = (i%3 == j%3 && j%3 == k%3), a = (i/3 != j/3 && i/3 != k/3 && j/3 != k/3), b = (i%3 != j%3 && i%3 != k%3 && j%3 != k%3);
		return (x&&y)||(x&&b)||(a&&y)||(a&&b);
	}

	int pack( int [][]b ) {
		int u = 0,i,j;
		for ( i = 0; i < 3; ++i )
			for ( j = 0; j < 3; ++j )
				u = (u*3+b[i][j]);
		return u;
	}

	int calcZ( int u ) {
		int i,j,k,v = u;
		int [][]b = new int[3][3];
		if ( z[u] < +oo )
			return z[u];
		for ( i = 0; i < 3; ++i )
			for ( j = 0; j < 3; b[i][j] = (v%3), ++j, v /= 3 );
		for ( z[u] = 0, i = 0; i < 7; ++i )
			if ( b[i/3][i%3] > 0 )
				for ( j = i+1; j < 8; ++j )
					if ( b[j/3][j%3] > 0 )
						for ( k = j+1; k < 9; ++k )
							if ( b[k/3][k%3] > 0 )
								if ( isSet(i,j,k) ) {
									--b[i/3][i%3];
									--b[j/3][j%3];
									--b[k/3][k%3];
									z[u] = Math.max(z[u],1+calcZ(pack(b)));
									++b[i/3][i%3];
									++b[j/3][j%3];
									++b[k/3][k%3];
								}
		return z[u];
	}

	void go() throws Exception {
		int i,j,k;
		long ans;
		int [][]t = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6},{1,3,8},{2,3,7},{1,5,6},{0,5,7}};
		for ( i = 1; i < M; z[i++] = +oo );
		for ( String s; (s = br.readLine()) != null; ) {
			if ( (n = Integer.parseInt(s)) == 0 ) break ;
			for ( i = 0; i < n; c[i++] = readCard() );
			for ( i = 0; i < 9; bin[i++] = 0 );
			for ( i = 0; i < n; ++bin[c[i++]] );
			for ( ans = 0, i = 0; i < t.length; ++i ) {
				k = Math.min(bin[t[i][0]],Math.min(bin[t[i][1]],bin[t[i][2]]));
				if ( k == 0 ) continue ;
				ans += k;
				bin[t[i][0]] -= k;
				bin[t[i][1]] -= k;
				bin[t[i][2]] -= k;
			}
			for ( i = 0; i < 9; ++i )
				ans += bin[i]/3;
			System.out.println(ans);
		}
	}
}


