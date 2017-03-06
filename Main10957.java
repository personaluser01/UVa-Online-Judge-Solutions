/*
 * 10957. SuDoku Checker
 * TOPIC: backtracking, bitmasks, pruning
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {

	int n = 9,yes = 0,m,ans;
	int [][]c = new int[n+1][n+1], s = new int[n+1][n+1];
	int []seen = new int[n+4],a = new int[n+1],b = new int[n+1], x = new int[n*n+2], y = new int[n*n+2];
	int []which = new int[1 << (n+1)];

	int L( int u ) { return (u)&((~u)+1); }

	public static void main( String [] args ) throws Exception { new Main().go(); }

	boolean row( int i ) {
		++yes;
		for ( int j = 0; j < n; ++j ) {
			if ( c[i][j] != 0 && seen[c[i][j]] == yes )
				return false;
			seen[c[i][j]] = yes;
		}
		return true;
	}
	boolean col( int j ) {
		++yes;
		for ( int i = 0; i < n; ++i ) {
			if ( c[i][j] != 0 && seen[c[i][j]] == yes )
				return false;
			seen[c[i][j]] = yes;
		}
		return true;
	}
	boolean isValid() {
		int i,j,k,l,t;
		for ( i = 0; i < n; ++i ) {
			if ( !row(i) ) return false;
			if ( !col(i) ) return false;
		}
		for ( i = 0; i < 3; ++i )
			for ( j = 0; j < 3; ++j ) {
				++yes;
				for ( k = i*3; k < (i+1)*3; ++k )
					for ( l = j*3; l < (j+1)*3; ++l ) {
						if ( c[k][l] != 0 && seen[c[k][l]] == yes ) return false;
						seen[c[k][l]] = yes;
					}
			}
		return true;
	}
	void solve( int cur ) {
		int u,i,j,k;
		if ( cur == m ) {
			if ( (++ans) >= 2 )
				return ;
			return ;
		}
		i = x[cur]; j = y[cur];
		for ( u = (a[i]&b[j]&s[i/3][j/3]); u > 0; u -= L(u) ) {
			k = which[L(u)];
			a[i] &= ~(1<<k);
			b[j] &= ~(1<<k);
			s[i/3][j/3] &= ~(1<<k);
			solve(cur+1);
			if ( ans >= 2 ) return ;
			a[i] |= (1<<k);
			b[j] |= (1<<k);
			s[i/3][j/3] |= (1<<k);
		}
	}

	void go() throws Exception {
		Scanner scan = new Scanner(System.in);
		int ts = 0,i,j,k,l;
		for ( i = 0; i < (n+1); ++i ) which[1 << i] = i;
		while ( scan.hasNext() ) {
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					c[i][j] = scan.nextInt();
			System.out.print("Case "+(++ts)+": ");
			if ( !isValid() ) {
				System.out.println("Illegal.");
				continue ;
			}
			for ( i = 0; i < n; ++i ) {
				a[i] = 0;
				for ( j = 0; j < n; ++j )
					if ( c[i][j] != 0 )
						a[i] |= (1<<(c[i][j]-1));
				a[i] = (~a[i])&511;
			}
			for ( j = 0; j < n; ++j ) {
				b[j] = 0;
				for ( i = 0; i < n; ++i )
					if ( c[i][j] != 0 )
						b[j] |= (1<<(c[i][j]-1));
				b[j] = (~b[j])&511;
			}
			for ( i = 0; i < 3; ++i )
				for ( j = 0; j < 3; ++j ) {
					s[i][j] = 0;
					for ( k = i*3; k < (i+1)*3; ++k )
						for ( l = j*3; l < (j+1)*3; ++l )
							if ( c[k][l] != 0 )
								s[i][j] |= (1<<(c[k][l]-1));
					s[i][j] = (~s[i][j])&511;
				}
			for ( ans = i = m = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					if ( c[i][j] == 0 ) {
						x[m] = i; 
						y[m++] = j;
					}
			solve(0);
			if ( ans == 1 ) {
				System.out.println("Unique.");
				continue ;
			}
			if ( ans == 0 ) {
				System.out.println("Impossible.");
				continue ;
			}
			if ( ans == 2 ) {
				System.out.println("Ambiguous.");
			}
		}
	}
};

