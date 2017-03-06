/*
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int i,j,k,ts = Integer.parseInt(br.readLine());
		String s,t;
		while ( ts-- > 0 ) {
			s = new StringTokenizer(br.readLine()).nextToken();
			t = new StringTokenizer(br.readLine()).nextToken();
			BigInteger x = new BigInteger(t);
			System.out.println(x.mod(new BigInteger(s)).toString());
		}
	}
};

