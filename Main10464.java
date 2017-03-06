/*
 * 10646. Big Big Real Numbers
 * TOPIC: big decimal
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.BigDecimal;

class Main {
	public static void main ( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken()),i,j,k,n;
		StringTokenizer st;
		BigDecimal a,b,c;
		while ( ts-- > 0 ) {
			st = new StringTokenizer(br.readLine());
			a = new BigDecimal(st.nextToken());
			b = new BigDecimal(st.nextToken());
			c = a.add(b);
			String s = c.toPlainString();
			n = s.length();
			for ( i = n-1; i >= 0 && s.charAt(i) == '0' && s.charAt(i) != '.'; --i );
			if ( i < 0 ) {
				System.out.println("0.0");
				continue ;
			}
			if ( s.charAt(i) == '.' ) {
				System.out.println(s.substring(0,i+1)+"0");
				continue ;
			}
			if ( s.indexOf('.') == -1 ) {
				System.out.println(s+".0");
				continue ;
			}
			System.out.println(s.substring(0,i+1));
		}
	}
};

