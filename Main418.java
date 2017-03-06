/*
 * 418. Molecules
 * TOPIC: ad hoc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	String []c = new String[4];
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int []bts = new int[1<<4], h = new int[4], v = new int[4];
	void go() throws Exception {
		int i,j,k,u,l,t,x,y,w,e,r;
		for ( u = 0; u < 16; ++u ) bts[u] = bts[u>>1]+(u&1);
		for ( ;!(c[0] = scan.next()).equals("Q"); System.out.println(w) ) {
			for ( i = 1; i < 4; c[i++] = scan.next() );
			for ( w = 0, u = 0; u < 16; ++u )
				if ( bts[u] == 2 ) {
					for ( j = k = 0, i = 0; i < 4; ++i )
						if ( ((u>>i)&1) == 1 )
							h[k++] = i;
						else v[j++] = i;
					for ( t = 0; t <= 1; ++t )
						for ( l = 0; l <= 1; ++l )
							for ( i = 1; i+1 < c[h[t]].length(); ++i )
								for ( j = 1; j+1 < c[v[l]].length(); ++j )
									if ( c[h[t]].charAt(i) == c[v[l]].charAt(j) )
										for ( x = 1; x+1 < c[h[t^1]].length(); ++x )
											for ( y = 1; y+1 < c[v[l^1]].length(); ++y )
												if ( c[h[t^1]].charAt(x) == c[v[l^1]].charAt(y) ) 
													for ( e = i+2; e+1 < c[h[t]].length(); ++e )
														for ( r = 1; r+2 <= y; ++r )
															if ( c[h[t]].charAt(e) == c[v[l^1]].charAt(r) ) 
					if ( j+y-r >= 1 && j+y-r+1 < c[v[l]].length() && x-e+i >= 1 && x-e+i+1 < c[h[t^1]].length() && c[v[l]].charAt(j+y-r) == c[h[t^1]].charAt(x-e+i) )
																	w = Math.max(w,(e-i-1)*(y-r-1));
				}
		}
	}
};

