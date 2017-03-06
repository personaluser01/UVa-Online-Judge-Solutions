/*
 * 12060. All-Integer Average
 * TOPIC: pretty-printing
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.lang.Math.*;
import java.math.BigInteger;

class Main {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	public static void main( String [] args ) throws Exception { new Main().go(); }

		long gcd( long x, long y ) {
			if ( y == 0 )
				return x;
			return gcd(y,x%y);
		}


	void go() throws Exception {
		int n,i,j,k,cs = 0;
		StringTokenizer st;
		
		while ( (n=Integer.parseInt((st = new StringTokenizer(br.readLine())).nextToken())) != 0 ) {
			long a,s = 0,rem,q,d;
			int sign,len,L;
			for ( i = 0; i < n; ++i )
				s += Long.parseLong(st.nextToken());
			System.out.println("Case "+(++cs)+":");
			if ( (s%n) == 0 ) {
				if ( s < 0 ) {
					s = Math.abs(s);
					System.out.print("- ");
				}
				System.out.println(s/n);
				continue ;
			}
			d = gcd(Math.abs(s),(long)n);
			s /= d; n /= d;
			sign = 1;
			len = 0;
			if ( Math.abs(s) > n ) {
				if ( s < 0 ) {
					sign = -1;
					s = -s; len += 2;
				}
				rem = s%n; q = s/n;
				len += (Long.toString(q)).length();
				len += (Integer.toString(n)).length();
				L = len;
				System.out.println(String.format("%"+len+"d",(int)rem));
				if ( sign == -1 ) { System.out.print("- "); len -= 2; }
				System.out.print(q); len -= (Long.toString(q)).length();
				for ( i = 0; i < len; ++i )
					System.out.print("-");
				System.out.println("");
				System.out.println(String.format("%"+L+"d",(int)n));
			}
			else {
				if ( s < 0 ) {
					sign = -1;
					s = -s; len += 2;
				}
				rem = s%n;
				len += (Integer.toString(n)).length();
				L = len;
				System.out.println(String.format("%"+len+"d",(int)rem));
				if ( sign == -1 ) { System.out.print("- "); len -= 2; }
				for ( i = 0; i < len; ++i )
					System.out.print("-");
				System.out.println("");
				System.out.println(String.format("%"+L+"d",(int)n));
			}
		}
	}
};

