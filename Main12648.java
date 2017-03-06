/*
 * 12648. Boss
 * TOPIC: graph traversal, permutations, dag
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 512, M = (1<<17), oo = 0x400;
	String tmp;
	Scanner scan = new Scanner(System.in);
	int E,m,n,qr;
	int[] age = new int[N], last = new int[N], _to = new int[M+M], next = new int[M+M], adr = new int[N], z = new int[N], who = new int[N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int f( int x ) {
		int i,y;
		if ( z[x] < +oo )
			return z[x];
		if ( last[x] == -1 )
			return +oo;
		for ( i=last[x]; i>=0 && (y=_to[i]) >= 0; i=next[i] ) 
			z[x]=Math.min(Math.min(z[x],f(y)),age[who[y]]);
		return z[x];
	}
	void go() throws Exception {
		int i,j,k,x,y;
		while ( scan.hasNext() ) {
			n = scan.nextInt();
			m = scan.nextInt();
			qr = scan.nextInt();
			for ( i = 0; i < n; ++i ) { age[i]=scan.nextInt(); last[adr[i]=i]=-1; who[i]=i; }
			for ( E = 0, k = 0; k < m; ++k ) {
				// i = E++;
				j = E++;
				x = scan.nextInt()-1; y = scan.nextInt()-1;
				// _to[i]=y; next[i] = last[x]; last[x] = i;
				_to[j]=x; next[j] = last[y]; last[y] = j;
			}
			while ( qr-- > 0 ) {
				tmp = scan.next();
				if ( tmp.equals("T") ) {
					x = scan.nextInt()-1;
					y = scan.nextInt()-1;
					k = adr[x]; adr[x] = adr[y]; adr[y] = k;
					k = who[adr[x]]; who[adr[x]] = who[adr[y]]; who[adr[y]] = k;
				}
				else {
					assert tmp.equals("P");
					x = scan.nextInt()-1;
					for ( i = 0; i < n; ++i ) z[i] = +oo;
					if ( f(adr[x]) < +oo )
						System.out.println(f(adr[x]));
					else System.out.println("*");
				}
			}
		}
	}
};


