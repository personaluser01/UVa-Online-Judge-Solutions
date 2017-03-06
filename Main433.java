/*
 * 433. Bank (Not Quite O.C.R.)
 * TOPIC: backtracking
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	char [][]c = new char[3][32];
	int []d = new int[11], r = new int[11], can_be = new int[11], b = new int[1<<20];
	String ans;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	int m=3,n=9,solns;
	boolean []isValid = new boolean[256];
	char []g = new char[11];
	int BIT( int k ) { return (1<<k); }
	int MASK( int k ) { return BIT(k)-1; }
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int which( int i, int j, char c ) {
		if ( i == 0 ) {
			if ( (j%3) == 0 )
				return isValid[(int)c]?7:8;
			if ( (j%3) == 1 )
				return c=='_'?0:(isValid[(int)c]?7:8);
			if ( (j%3) == 2 )
				return isValid[(int)c]?7:8;
		}
		else if ( i == 1 ) {
			if ( (j%3) == 0 ) 
				return c=='|'?1:(isValid[(int)c]?7:8);
			if ( (j%3) == 1 ) 
				return c=='_'?6:(isValid[(int)c]?7:8);
			if ( (j%3) == 2 ) 
				return c=='|'?5:(isValid[(int)c]?7:8);
		}
		else {
			if ( (j%3) == 0 ) 
				return c=='|'?2:(isValid[(int)c]?7:8);
			if ( (j%3) == 1 ) 
				return c=='_'?3:(isValid[(int)c]?7:8);
			if ( (j%3) == 2 ) 
				return c=='|'?4:(isValid[(int)c]?7:8);
		}
		return 7;
	}

	int L( int k ) { return ((k)&((~(k))+1)); }

	boolean isGarbled( int k ) {
		for ( int t = 0; t <= 9; ++t )
			if ( (d[t]&r[k]) == r[k] )
				return false;
		return true;
	}

	boolean twoGarbled() {
		int s = 0;
		for ( int t = 0; t <= 9 && s <= 2; ++t )
			if ( isGarbled(t) ) ++s;
		return s >= 2;
	}

	boolean isCorrect( int k, int sum ) {
		int u,t,j;
		if ( k == n ) {
			if ( (sum%11) == 0 ) {
				solns = 1;
				ans = "";
				for ( j = 0; j < 9; ++j )
					ans += Character.toString(g[j]);
				return true;
			}
			return false;
		}
		/*
		for ( u = can_be[k]; u > 0; u &= ~L(u) ) {
			g[k] = (char)((t=b[L(u)])+'0');
			if ( d[t] == r[k] && isCorrect(k+1,(sum+(n-k)*t)%11) )
				return true;
		}
		*/
		for ( t = 0; t <= 9; ++t )
			if ( r[k]==d[t] ) {
				g[k]=(char)((t)+'0');
				if ( isCorrect(k+1,(sum+(n-k)*t)%11) )
					return true;
			}
		return false;
	}

	void f( int cost, int k, int sum ) {
		int u,i,j,t;
		if ( solns >= 2 )
			return ;
		if ( cost >= 2 )
			return ;
		if ( k == n ) {
			if ( (sum%11) == 0 ) {
				if ( (++solns)>=2 )
					return ;
				ans = "";
				for ( j = 0; j < 9; ++j )
					ans += Character.toString(g[j]);
				return ;
			}
			return ;
		}
		for ( t = 0; t <= 9; ++t )
			if ( (r[k]&d[t]) == r[k] ) {
				g[k] = (char)(t+'0');
				f(cost+(d[t]==r[k]?0:1),k+1,(sum+(n-k)*t)%11);
				if ( solns >= 2 ) return ;
			}
		/*
		for ( u = can_be[k]; u > 0; u &= ~L(u) ) {
			t = b[L(u)]; g[k] = (char)(t+'0');
			if ( cost+(d[t]==r[k]?0:1)<=1 ) f(cost+(d[t]==r[k]?0:1),k+1,(sum+(n-k)*t)%11);
			if ( solns >= 2 ) return ;
		}
		*/
	}

	void go() throws Exception {
		int ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken()),i,j,k,t;
		boolean ok;
		for ( i = 0; i < 20; ++i ) b[BIT(i)] = i;
		isValid[' '] = true;
		d[0] = MASK(7)&(~BIT(6));
		d[1] = BIT(5)|BIT(4);
		d[2] = BIT(0)|BIT(5)|BIT(6)|BIT(2)|BIT(3);
		d[3] = MASK(7)&(~BIT(1))&(~BIT(2));
		d[4] = MASK(7)&(~BIT(0))&(~BIT(2))&(~BIT(3));
		d[5] = MASK(7)&(~BIT(5))&(~BIT(2));
		d[6] = MASK(7)&(~BIT(5));
		d[7] = BIT(0)|BIT(4)|BIT(5);
		d[8] = MASK(7);
		d[9] = MASK(7)&(~BIT(2));
		for ( i = 0; i <= 9; ++i )
			d[i] &= MASK(7);
		String s;
		for (;ts-->0;) {
			for ( solns = i = 0; i < m; ++i ) {
				s = br.readLine();
				for ( j = 0; j < 3*n; ++j )
					c[i][j] = ' ';
				for ( j = 0; j < 3*n && j < s.length(); ++j )
					c[i][j] = s.charAt(j);
			}
			for ( k = 0; k < n; ++k ) 
				for ( r[k] = i = 0; i < m; ++i )
					for ( j = 3*k; j < 3*k+3; ++j )
						if ( (t=which(i,j,c[i][j])) < 7 )
							r[k] |= BIT(t);
			for ( ok = true, k = 0; k < n; ok &= (can_be[k++] != 0) )
				for ( can_be[k] = i = 0; i <= 9; ++i )
					if ( (r[k]&d[i]) == r[k] ) {
						can_be[k] |= BIT(i);
						// System.out.println((k+1)+" can be "+i+","+r[k]+" "+d[i]);
					}
			if ( twoGarbled() ) { System.out.println("failure"); continue ; }
			if ( isCorrect(0,0) ) {
				System.out.println(ans);
				continue ;
			}
			f(0,0,0);
			if ( solns == 0 ) 
				System.out.println("failure");
			else if ( solns >= 2 ) 
				System.out.println("ambiguous");
			else System.out.println(ans);
		}
	}
};

