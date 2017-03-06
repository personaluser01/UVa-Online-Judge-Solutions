/*
 * 11074. Draw Grid
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		String str;
		int i,j,k,s,t,e,n,m,g,row,col,l,cs = 0,baseline,basecol;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while ( (str=br.readLine())!=null ) {
			st = new StringTokenizer(str);
			s = Integer.parseInt(st.nextToken());
			t = Integer.parseInt(st.nextToken());
			g = Integer.parseInt(st.nextToken());
			if ( s == 0 && t == 0 && g == 0 )
				break ;
			m = s*g+t*g+t; n = m;
			byte [][]c = new byte[m][];
			for ( i = 0; i < m; ++i )
				c[i] = new byte[n];
			baseline = 0;
			for ( row = 0; row < g; ++row ) {
				for ( l = 0; l < t; ++l ) 
					for ( j = 0; j < n; ++j )
						c[baseline+l][j] = '*';
				basecol = 0;
				for ( col = 0; col < g; ++col ) {
					for ( e = 0; e < t; ++e )
						for ( j = 0; j < s; ++j )
							c[baseline+t+j][basecol+e] = '*';
					for ( e = 0; e < s; ++e )
						for ( j = 0; j < s; ++j )
							c[baseline+t+j][basecol+t+e] = '.';
					basecol += (t+s);
				}
				for ( e = 0; e < t; ++e )
					for ( j = 0; j < s; ++j )
						c[baseline+t+j][basecol+e] = '*';
				baseline += (t+s);
			}
			for ( l = 0; l < t; ++l ) 
				for ( j = 0; j < n; ++j )
					c[baseline+l][j] = '*';
			System.out.println("Case "+(++cs)+":");
			for ( i = 0; i < m; ++i ) 
				System.out.println(new String(c[i],0,n));
			System.out.println("");
		}
	}
};

