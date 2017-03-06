/*
 * 1339. Ancient Cipher
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int i,j,k,ts;
		int [] ee = new int[26];
		int [] dd = new int[26];
		String s,e,d;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while ( (e = br.readLine()) != null ) {
			d = br.readLine();
			Set<Character> E,D;
			E = new HashSet<Character>();
			D = new HashSet<Character>();
			for ( char c: e.toCharArray() ) E.add(c);
			for ( char c: d.toCharArray() ) D.add(c);
			if ( E.size() != D.size() )
				System.out.println("NO");
			else {
				boolean ok = true;
				for ( i = 0; i < 26; ++i ) { ee[i] = 0; dd[i] = 0; }
				for ( i = 0; i < (int)e.length(); ++i ) ++ee[e.charAt(i)-'A'];
				for ( i = 0; i < (int)d.length(); ++i ) ++dd[d.charAt(i)-'A'];
				Arrays.sort(ee);
				Arrays.sort(dd);
				for ( i = 0; i < 26 && ok; ++i )
					if ( ee[i] != dd[i] )
						ok = false;
				if ( !ok )
					System.out.println("NO");
				else
					System.out.println("YES");
			}
		}
	}
};

