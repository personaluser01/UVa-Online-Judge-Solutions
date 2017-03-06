/*
 * 11839. Optical Reader
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
		int i,j,k,n;
		int []c = new int[5];
		String s;
		String m = "ABCDE";
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Queue<Integer> q = new LinkedList<Integer>();
		try {
			while ( (s = br.readLine()) != null ) {
				st = new StringTokenizer(s);
				n = Integer.parseInt(st.nextToken());
				if ( n == 0 ) break ;
				assert( q.size() == 0 );
				for ( i = 0; i < n; ++i ) {
					st = new StringTokenizer(s = br.readLine());
					for ( j = 0; j < 5; ++j ) {
						c[j] = Integer.parseInt(st.nextToken());
						try {
							if ( c[j] <= 127 )
								q.add(j);
						}
						catch ( IllegalStateException g ) {
							System.out.println(g.toString());
						}
					}
					if ( q.size() == 1 ) 
						System.out.println(m.charAt(q.element()));
					else System.out.println("*");
					while ( q.size() >= 1 ) q.remove();
					assert( q.size() == 0 );
				}
			}	
		}
		catch ( IOException e ) {
			System.out.println(e.toString());
		}
	}
};

