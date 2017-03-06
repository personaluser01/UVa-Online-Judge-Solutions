/*
 * 1241. Jollybee Tournament
 * TOPIC: bit manipulations
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 11;
	int []c = new int[1<<N];
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int f( int []c, int m, int n ) {
		if ( m == 0 ) return 0;
		if ( n == 0 ) return 0;
		int ans=0,i,k = 0;
		int []b = new int[1<<n], d = new int[1<<(n-1)];
		for ( i = 0; i < (1<<n); ++i ) b[i] = 0;
		for ( i = 0; i < m; ++i ) b[c[i]] = 1;
		for ( i = 0; i < (1<<n); i += 2 )
			if ( (b[i]^b[i+1]) == 1 ) ++ans;
			else if ( (b[i]&b[i+1]) == 1 )
				d[k++] = (i>>1);
		return ans+f(d,k,n-1);
	}
	void go() throws Exception {
		int i,j,k,ts=scan.nextInt(),n,m;
		for(;ts-->0;){
			n = scan.nextInt();
			m = scan.nextInt();
			for ( i = 0; i < m; ++i ) 
				c[i] = scan.nextInt()-1;
			System.out.println(f(c,m,n));
		}
	}
};

