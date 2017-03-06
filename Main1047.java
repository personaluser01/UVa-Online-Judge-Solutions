/*
 * 1047. Zones
 */
import java.io.*;
import java.util.*;
import java.math.*;

class Main {
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	void go() throws Exception {
		int n,m,i,j,k,l,common,cs = 0;
		int []c,u;
		String s;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while ( (s=br.readLine())!=null ) {
			st = new StringTokenizer(s);
			n = Integer.parseInt(st.nextToken());
			m = Integer.parseInt(st.nextToken());
			if ( n == 0 && m == 0 ) break ;
			c = new int[n];
			for ( i = 0; i < n; ++i ) 
				c[i] = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
			common = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken());
			u = new int[common];
			for ( i = 0; i < common; ++i ) {
				st = new StringTokenizer(br.readLine());
				for ( l = Integer.parseInt(st.nextToken()); l-- > 0; ) {
					j = Integer.parseInt(st.nextToken());
					u[i] |= (1<<(j-1));
				}
			}
			System.out.printf("Case Number  %d \n",++cs);
			System.out.println("");
		}
	}
};

