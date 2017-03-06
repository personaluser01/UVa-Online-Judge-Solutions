/*
 * 11300. Spreading The Wealth
 * TOPIC: median, sorting
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.BigInteger;

class Main {
	public static void main ( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		Scanner scan = new Scanner(System.in);
		int n,i,j,k;
		long []c,s;
		long T,q;
		while ( scan.hasNext() ) {
			n = scan.nextInt();
			c = new long[n];
			for ( T = i = 0; i < n; T+=(c[i++]=scan.nextInt()) );
			q = T/n;
			s = new long[n];
			for ( i = 1; i < n; ++i ) 
				s[i] = s[i-1]+(c[i-1]-q);
			Arrays.sort(s);
			BigInteger res = new BigInteger("0"),med;
			if ( 0 == (n&1) )
				med = BigInteger.valueOf(s[n/2]);
			else
				med = BigInteger.valueOf((s[n/2]+s[n/2+1])/2);
			for ( i = 0; i < n; ++i )
				res = res.add((med.subtract(BigInteger.valueOf(s[i]))).abs());
			System.out.println(res.toString());
		}
	}
}
