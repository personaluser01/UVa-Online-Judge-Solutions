/*
 * 1368. DNA Consensus String
 * TOPIC: greedy, trivial, dna
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	String []s = new String[64];
	char[]t = new char[0x400];
	public static void main ( String [] args ) throws Exception {
		new Main().go();
	}
	int code( char ch ) {
		switch ( ch ) {
				case 'A': return 0;
				case 'C': return 1;
				case 'G': return 2;
				default: return 3;
		}
	}
	void go() throws Exception {
		int i,j,k,ts,m,n,len,mx,idx,dist;
		int []cnt = new int[4];
		String y = new String("ACGT");
		Scanner scan = new Scanner(System.in);
		for ( ts = scan.nextInt(); ts-- > 0; ) {
			m = scan.nextInt(); n = scan.nextInt();
			for ( dist = i = 0; i < m; s[i++] = scan.next() );
			for ( len = j = 0; j < n; t[j++] = y.charAt(idx) ) {
				for ( i = 0; i < 4; ++i ) cnt[i] = 0;
				for ( i = 0; i < m; ++i )
					++cnt[code(s[i].charAt(j))];
				for ( idx = mx = i = 0; i < 4; ++i )
					if ( cnt[i] > mx )
						mx = cnt[idx=i];
				for ( i = 0; i < m; ++i )
					if ( code(s[i].charAt(j)) != idx )
						++dist;
			}
			System.out.println(new String(t,0,n));
			System.out.println(dist);
		}
	}
};


