/*
 * 295. Fatman
 * TOPIC: binary search, geometry, dsu
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.text.*;

class Main {
	private static final int N = 0x80, leftX = -0x80, rightX = 2*0x80;
	private static final double tol = 1e-9;
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	InputStreamReader R = new InputStreamReader(System.in);
	int []x = new int[N],y = new int[N], rank = new int[N], p = new int[N], father = new int[N];
	double [][]d = new double[N][N];
	int n,L,W,cs = 0;

	double S( double x ) { return x*x; }

	void link( int x, int y ) {
		if ( rank[x] > rank[y] )
			p[y] = x;
		else {
			p[x] = y;
			if ( rank[x] == rank[y] )
				++rank[y];
		}
	}
	void merge( int x, int y ) {
		link(find(x),find(y));
	}
	int find( int x ) {
		return p[x] = (p[x]==x?x:find(p[x]));
	}

	public static void main( String ... args ) throws Exception {
		new Main().go();
	}

	void pr( double x ) throws Exception {
		NumberFormat nf = NumberFormat.getInstance();
		x = ((int)(10000*(x+0.00005)))/10000.00;
		nf.setMinimumFractionDigits(4);
		nf.setMaximumFractionDigits(4);
		bw.write("Maximum size in test case "+(++cs)+" is "+nf.format(x)+".\n");
	}

	int rd() throws Exception {
		int ch,n = 0;
		for ( ;(ch = R.read()) != -1 && !('0'<=(char)ch && (char)ch<='9'); );
		for ( n = ch-'0'; (ch = R.read()) != -1 && '0' <= (char)ch && (char)ch <= '9'; )
			n = 10*n+ch-'0';
		return n;
	}

	void go() throws Exception {
		int i,j,k,ts = rd();
		double good,bad,mid = 0;
		boolean ok;
		for (;ts-->0; pr(good) ) {
			L = rd();
			W = rd();
			n = rd();
			for ( i = 0; i < n; ++i ) {
				x[i] = rd();
				y[i] = rd();
			}
			for ( i = 0; i < n; ++i )
				for ( j = i+1; j < n; ++j )
					d[i][j] = d[j][i] = Math.sqrt(S(x[i]-x[j])+S(y[i]-y[j]));
			d[n][n+1] = d[n+1][n] = W;
			for ( i = 0; i < n; ++i ) {
				d[n][i] = d[i][n] = y[i];
				d[n+1][i] = d[i][n+1] = W-y[i];
				//d[n+2][i] = d[i][n+2] = x[i]-leftX;
				//d[n+3][i] = d[i][n+3] = rightX-x[i];
			}
			for ( good = 0, bad = 0x80+1; Math.abs(bad-good) >= tol; ) {
				mid = (good+bad)/2;
				for ( i = 0; i < n+2; rank[p[i] = i] = 0, ++i );
				for ( i = 0; i < n+2; ++i )
					for ( j = i+1; j < n+2; ++j )
						if ( d[i][j] < mid && find(i) != find(j) )
							merge(i,j);
				for ( i = 0; i < n+2; ++i ) father[i] = find(i);
				ok = (father[n] != father[n+1]);
				if ( ok ) good = mid;
				else bad = mid;
			}
		}
		bw.flush();
	}
}

