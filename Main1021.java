/*
 * 1021. Eurodiffusion
 * TOPIC: ad hoc, simulation
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x30, Q = 0x20, S = 0x10;
	int n,cs,w;
	Scanner scan = new Scanner(System.in);
	int MASK( int k ) { return B(k)-1; }
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Country implements Comparable<Country> {
		int t;
		String name;
		Country( String s, int t ) { this.name = s; this.t = t; }
		public int compareTo( Country other ) {
			if ( this.t == other.t ) return this.name.compareTo(other.name);
			return this.t<other.t?-1:1;
		}
	}
	String []name = new String[N];
	int [][]id = new int[Q][Q];
	int []xl = new int[Q], yl = new int[Q], xh = new int[Q], yh = new int[Q], T = new int[N];
	int [][][][]c = new int[2][N][Q][Q];
	int [][][]u = new int[2][Q][Q];
	int [][]v = new int[2][N];
	int B( int k ) { return 1<<k; }
	int []dx = {-1,0,1,0}, dy = {0,1,0,-1};
	boolean vc( int x, int y ) { return  0 <= x && x < S && 0 <= y && y < S && id[x][y] != -1; }
	Country []e;
	void go() throws Exception {
		int i,j,k,l,t,ni,nj,days;
		boolean flag;
		int []r = new int[N];
		while ( scan.hasNext() && (n=scan.nextInt()) != 0 ) {
			System.out.println("Case Number "+(++cs));
			for ( i = 0; i < Q; ++i ) for ( j = 0; j < Q; id[i][j++] = -1 );
			for ( t = 0, i = 0; i < n; T[i++] = -1 ) {
				name[i] = scan.next(); v[t][i] = B(i);
				xl[i] = scan.nextInt()-1; yl[i] = scan.nextInt()-1; xh[i] = scan.nextInt()-1; yh[i] = scan.nextInt()-1;
				for ( k = xl[i]; k <= xh[i]; ++k )
					for ( l = yl[i]; l <= yh[i]; ++l ) {
						for ( u[t][k][l] = B(i), id[k][l] = i, j = 0; j < n; c[t][j++][k][l] = 0 );
						c[t][i][k][l] = 1000000;
					}
			}
			if ( n == 1 ) {
				System.out.println("   "+name[0]+"   "+"0");
				continue ;
			}
			for ( e = new Country[n], t = 0, days = 1, w = 0; w != MASK(n); ++days ) {
				for ( t ^= 1, i = 0; i < S; ++i ) for ( j = 0; j < S; ++j ) for ( u[t][i][j] = 0, k = 0; k < n; c[t][k++][i][j] = 0 );
				for ( i = 0; i < S; ++i ) for ( j = 0; j < S; ++j ) if ( id[i][j] != -1 ) {
					for ( k = 0; k < n; r[k] = c[t^1][k][i][j]/1000, ++k );
					for ( l = 0; l < 4; ++l ) if ( vc(ni=i+dx[l],nj=j+dy[l]) ) 
						for ( k = 0; k < n; ++k ) if ( r[k] > 0 ) {
							if ( (c[t][k][ni][nj]+=r[k]) > 0 ) u[t][ni][nj] |= B(k);
							if ( 0 == (c[t^1][k][i][j]-=r[k]) ) {
								u[t^1][i][j] &= ~B(k);
								// assert r[k] == 0 || 0 == 1;
							}
						}
				}
				for ( i = 0; i < S; ++i ) for ( j = 0; j < S; ++j ) for ( k = 0; k < n; ++k )
					if ( (c[t][k][i][j]+=c[t^1][k][i][j]) > 0 ) u[t][i][j] |= B(k);
				for ( w = MASK(n), k = 0; k < n; ++k ) if ( T[k] == -1 ) {
					for ( v[t][k] = MASK(n), i = xl[k]; i <= xh[k]; ++i ) for ( j = yl[k]; j <= yh[k]; v[t][k] &= u[t][i][j++] );
					if ( v[t][k] == MASK(n) ) { e[k] = new Country(name[k],T[k]=days); /*System.out.println(name[k]+" has reached maturity on "+days);*/ }
					w &= v[t][k];
				}
			}
			for ( Arrays.sort(e), i = 0; i < n; System.out.println("   "+e[i].name+"   "+e[i].t), ++i );
		}
	}
};

