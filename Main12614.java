/*
 * 12614. Earn For Future
 * status: Accepted
 * TOPIC: bitwise operations, bits, greedy
 */
import java.io.*;
import java.util.*;

class Main {
	public static void main( String [] args ) throws Exception {
		new Main().doIt();
	}
	int rec( int[] c, int n, int pos ) {
		int []a = new int[n];
		int i,j,k,m = 0;
		if ( pos < 0 ) 
			return 0;
		for ( i = 0; i < n; ++i )
			if ( ((1<<pos)&c[i]) > 0 )
				a[m++] = c[i];
		if ( m == 0 )
			return rec(c,n,pos-1);
		return rec(a,m,pos-1)|(1<<pos);
	}
	void doIt() throws Exception {
		int i,j,k,ts,n,cs = 0;
		int []c = new int[0x40];
		String s;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		ts = Integer.parseInt(br.readLine());
		while ( ts-- > 0 ) {
			n = Integer.parseInt(br.readLine());
			st = new StringTokenizer(br.readLine());
			for ( i = 0; i < n; ++i ) 
				c[i] = Integer.parseInt(st.nextToken());
			System.out.printf("Case %d: %d\n",++cs,rec(c,n,30));
		}
	}
};

