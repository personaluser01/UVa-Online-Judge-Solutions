/*
 *
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k,ts,n,m,ans,cs = 0;
		int []last_seen = new int[26];
		String s;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
		while ( ts-- > 0 ) {
			st = new StringTokenizer(br.readLine());
			n = Integer.parseInt(st.nextToken());
			m = Integer.parseInt(st.nextToken());
			s = st.nextToken();
			for ( i = 0; i < 26; ++i ) last_seen[i] = -1;
			ans = s.length();
			i = 0;
			for ( char c: s.toCharArray() ) {
				k = (int)(c-'A');
				if ( last_seen[k] == -1 || i-last_seen[k] > m )
					--ans;
				last_seen[k] = i++;
			}
			System.out.println("Case "+(++cs)+": "+ans);
		}
	}
};

