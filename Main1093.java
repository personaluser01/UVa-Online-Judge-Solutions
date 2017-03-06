/*
 * 1093. Castles
 * TOPIC: recursion, dp, hard, euler tour, tree
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x80;
	class Foo implements Comparable<Foo> {
		int a,g;
		Foo( int a, int g ) { this.a = a; this.g = g; }
		public int compareTo( Foo other ) {
			if ( this.a == other.a ) 
				return this.g<other.g?-1:1;
			return this.a>other.a?-1:1;
		}
	}
	Foo []c;
	int []deg = new int[N], seen = new int[N];
	int [][]adj = new int[N][N];
	int n,yes;
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	boolean isLess( Foo x, Foo y ) {
		if ( x.a==y.a ) 
			return x.g<y.g;
		return x.a<y.a;
	}
	Foo f( int x ) {
		int i,y,l=0,k = 0,aa,bb;
		for ( i = 0; i < deg[x]; ++i )
			if ( seen[adj[x][i]] != yes ) ++l;
		Foo []B = new Foo[l];
		for ( seen[x] = yes, i = 0; i < deg[x] && (y=adj[x][i]) >= 0; ++i )
			if ( seen[y] != yes ) B[k++] = f(y);
		for ( Arrays.sort(B), aa = c[x].a, bb = c[x].g, i = 0; i < k; ++i ) {
			aa = Math.max(aa,bb+B[i].a);
			bb += B[i].g;
		}
		return new Foo(Math.max(aa,bb),bb);
	}
	void go() throws Exception {
		int i,j,k,l,t,cs = 0;
		Foo ans,e;
		for(;(n=scan.nextInt())!=0; ) {
			c = new Foo[n];
			for ( i = 0; i < n; deg[i++] = 0 ) {
				j = scan.nextInt();
				k = scan.nextInt()+scan.nextInt();
				c[i] = new Foo(Math.max(j,k),k);
			}
			for ( k = 0; k < n-1; ++k ) {
				i = scan.nextInt()-1;
				j = scan.nextInt()-1;
				adj[i][deg[i]++] = j;
				adj[j][deg[j]++] = i;
			}
			for ( ans = new Foo(1<<29,1<<29), i = 0; i < n; ++i ) {
				++yes; e = f(i);
				if ( isLess(e,ans) ) ans = e;
			}
			System.out.printf("Case %d: %d\n",++cs,ans.a);
		}
	}
};

