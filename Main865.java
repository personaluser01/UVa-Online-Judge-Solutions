/*
 * 865. Substitution Cipher
 * status: Accepted
 * TOPIC: simulation, easy
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	public static void main( String [] args ) throws Exception {
		Main m = new Main();
		m.doIt();
	}
	void doIt() {
		String s,t,plain,subs;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int i,j,k,ts;

		try {
			ts = Integer.parseInt(br.readLine());
			br.readLine();
			while ( ts-->0 ) {
				plain = br.readLine();
				subs = br.readLine();
				Map<Character,Character> m = new HashMap<Character,Character>();
				System.out.println(subs+"\n"+plain);
				for ( i = 0; i < (int)plain.length(); ++i )
					m.put(plain.charAt(i),subs.charAt(i));
				while ( (t=br.readLine()) != null && !t.equals("") ) {
					// System.out.println(t);
					s = new String();
					for ( char c: t.toCharArray() ) {
						if ( !m.containsKey(c) ) {
							s += c;
							continue ;
						}
						s += m.get(c);
					}
					System.out.println(s);
				}
				if ( ts > 0 ) System.out.println("");
			}
		}
		catch ( IOException e ) {
			System.out.println(e.toString());
		}
	}
};

