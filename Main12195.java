/*
 * 12195. Jingle Composition
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k;
		String s;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Map<Character,Integer> m = new HashMap<Character,Integer>();
		m.put('W',64); m.put('H',32); m.put('Q',16); m.put('E',8); 
		m.put('S',4);  m.put('T',2);  m.put('X',1);
		while ( !(s = br.readLine()).equals("*") ) {
			st = new StringTokenizer(s,"/"); i = 0;
			while ( st.hasMoreTokens() ) {
				s = st.nextToken();
				k = 0;
				for ( char c: s.toCharArray() ) {
					if ( !('A' <= c && c <= 'Z') ) continue ;
					k += m.get(c);
				}
				if ( k == 64 ) ++i;
			}
			System.out.println(i);
		}
	}
};

