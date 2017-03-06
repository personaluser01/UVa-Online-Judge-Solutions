/*
 * 1572. Self-Assembly
 * TOPIC: graphs, cycles, world finals, neat state
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int MAXV = (1|(26<<1))+1, MAXE = (1<<20);
	Scanner scan = new Scanner(System.in);
	Set<Integer> s;
	int n,E,V,yes = 0;
	int []to = new int[MAXE], last = new int[MAXV], next = new int[MAXE], p = new int[MAXV], seen = new int[1<<20];
	public static void main( String [] args ) throws Exception { new Main().go(); };
	int toVx( String a ) {
		int k;
		if ( 'A' <= a.charAt(0) && a.charAt(0) <= 'Z' ) {
			char ch = a.charAt(1);
			if ( ch == '-' ) k = 0; else k = 1;
			return (k)|(((int)(a.charAt(0)-'A'))<<1);
		}
		return 0|(26<<1);
	}
	void addArcs( int x, int y ) {
		int i = E++, j = E++;
		to[i] = y; next[i] = last[x]; last[x] = i;
		to[j] = x; next[j] = last[y]; last[y] = j;
	}
	int e( int x, boolean f ) {
		if ( f ) return x|(1<<7);
		return x;
	}
	boolean visit( int src, int x, boolean cameViaBridge, int len ) {
		int i,y;
		if ( !s.contains(x) ) return false ;
		if ( x == src && len > 0 && cameViaBridge ) {
			// System.out.printf("%c %c\n",(char)((x>>1)+'A'),(x&1)==0?'-':'+');
			return true ;
		}
		if ( seen[e(x,cameViaBridge)] == yes ) return false ;
		seen[e(x,cameViaBridge)] = yes;
		if ( cameViaBridge ) {
			for ( i = last[x]; i >= 0; i = next[i] ) {
				y = to[i];
				if ( visit(src,y,false,len+1) )
					return true ;
			}
		}
		else {
			y = x^1;
			if ( visit(src,y,true,len+1) )
				return true ;
		}
		return false ;
	};
	void go() throws Exception {
		int i,j,k,x,y;
		int []v = new int[4];
		for(;scan.hasNext();) {
			n = scan.nextInt();
			if ( n == 0 ) break ;
			s = new TreeSet<Integer>();
			for ( E = 0, i = 0; i < MAXV; last[i++] = -1 );
			for ( i = 0; i < n; ++i ) {
				String tmp = scan.next();
				for ( j = 0; j < 4; ++j ) 
					s.add(v[j] = toVx(tmp.substring(2*j,2*j+2)));
				for ( j = 0; j < 4; ++j )
					if ( !tmp.substring(2*j,2*j+2).equals("00") )
						for ( k = j+1; k < 4; ++k ) 
							if ( 2*k+2 <= 8 && !tmp.substring(2*k,2*k+2).equals("00") )
								addArcs(v[j],v[k]);
			}
			boolean ok = true ;
			for ( int t: s ) {
				++yes;
				if ( visit(t,t,true,0) ) {
					ok = false ;
					break ;
				};
			};
			System.out.println(ok?"bounded":"unbounded");
		};
	};
};

