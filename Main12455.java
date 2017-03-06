/*
 * 12455. Bars
 * status: Accepted
 * TOPIC: bitmasks, dp, subset sum
 */
import java.io.*;
import java.util.*;

class Main {
	static int B( int k ) { return (k&(~(k)+1)); }
	static int []A;
	public static void main( String [] args ) throws Exception { 
		A = new int[1 << 21];
		for ( int i = 0; i < 21; ++i ) A[1 << i] = i;
		new Main().doIt();
	}
	void doIt() throws Exception {
		int L,n,i,j,k,ts;
		int []c;
		int []len;
		boolean ok;
		String s;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
		while ( ts-- > 0 ) {
			L = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
			n = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
			st = new StringTokenizer(br.readLine());
			c  = new int[n];
			len = new int[1 << n];
			for ( i = 0; i < n; ++i ) 
				c[i] = Integer.parseInt(st.nextToken());
			ok = (L==0);
			for ( len[0] = 0, k = 1; k < (1 << n) && !ok; ++k ) 
				ok |= ((len[k]=len[k-B(k)]+c[Main.A[B(k)]])==L);
			System.out.println(ok?"YES":"NO");
		}
	}
};

