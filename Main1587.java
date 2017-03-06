/*
 * 1587. Box
 * TOPIC: ad hoc, backtracking, nice
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	int [][]w = new int[2][6];
	int []who = new int[6],which = new int[1<<10];
	int L( int k ) { return (k&((~k)+1)); }
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int BIT( int k ) { return (1<<k); }
	int mask;
	boolean f( int k ) {
		int l,u,i,j,t;
		if ( k == 6 ) return true;		
		// System.out.println("k = "+k);
		for ( u=((~mask)&63); u>0 && (l=which[L(u)])>=0; u&=~L(u) ) 
			switch ( k ) {
				case 1: for ( t = 0; t <= 1; ++t )
							if ( w[(who[k-1]&1)^1][who[k-1]>>1] == w[t][l] ) {
								mask |= BIT(l);
								who[k] = (t^1)|(l<<1);
								if ( f(k+1) ) return true;
								mask &= ~BIT(l);
							}
						break ;
				case 2: for ( t = 0; t <= 1; ++t )
						if ( w[(who[k-1]&1)^1][who[k-1]>>1] == w[t][l] && w[t^1][l] == w[who[k-2]&1][who[k-2]>>1] ) {
								mask |= BIT(l);
								who[k] = (t^1)|(l<<1);
								if ( f(k+1) ) return true;
								mask &= ~BIT(l);
							}
						break ;
				case 3: for ( t = 0; t <= 1; ++t )
							if ( w[(who[k-1]&1)^1][who[k-1]>>1] == w[t][l] )
								if ( w[who[0]^1][who[0]>>1] == w[t][l] && w[t^1][l] == w[who[1]&1][who[1]>>1] ) {
									mask |= BIT(l);
									who[k] = (t^1)|(l<<1);
									if ( f(k+1) ) return true;
									mask &= ~BIT(l);
							}
						break ;
				default: for ( t = 0; t <= 1; ++t )
							if ( w[(who[0]&1)][who[0]>>1] == w[t][l] )
								if ( w[(who[1]&1)][who[1]>>1] == w[t^1][l] ) {
									mask |= BIT(l);
									who[k] = (t^1)|(l<<1);
									if ( f(k+1) ) return true ;
									mask &= ~BIT(l);
								}
						 break ;
			}
		return false ;
	}
	void go() throws Exception {
		int i,j,k,t,l;
		for ( i = 0; i < 10; ++i )
			which[BIT(i)] = i;
		for (;scan.hasNext();) {
			for ( i = 0; i < 6; ++i ) 
				for ( t = 0; t <= 1; w[t++][i] = scan.nextInt() );
			mask = BIT(0); who[0] = 0;
			if ( f(1) ) System.out.println("POSSIBLE");
			else System.out.println("IMPOSSIBLE");
		}
	}
};

