/*
 * 10876. Factory Robot
 * TOPIC: binary search, disjoint set union
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.text.*;

class Main {
	final static int N = 0x200, MAXSIZE = (1<<15);
	final static double tol = 1e-9;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	int n;
	int []x,y,r,p = new int[N],rank = new int[N],father = new int[N];
	double [][]d;
	double S( double x ) { return x*x; }
	public static void main(String...args) throws Exception {
		new Main().go();
	}
	int find( int x ) {
		return p[x] = (p[x]==x?x:find(p[x]));
	}
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
	void pr( double x ) throws Exception {
		NumberFormat nf = NumberFormat.getInstance();
		nf.setMaximumFractionDigits(3);
		nf.setMinimumFractionDigits(3);
		bw.write(nf.format(x)+"\n");
	}
	void go() throws Exception {
		int i,j,k,ts = Integer.parseInt(br.readLine());
		double good,bad,mid = 0;
		for ( ;ts--> 0; pr(mid/2)	) {
			n = Integer.parseInt(br.readLine());
			x = new int[n];
			y = new int[n];
			r = new int[n];
			d = new double[n][n];
			for ( i = 0; i < n; ++i ) {
				Scanner sc = new Scanner(br.readLine());
				x[i] = sc.nextInt();
				y[i] = sc.nextInt();
				r[i] = sc.nextInt();
			}
			for ( i = 0; i < n; ++i )
				for ( j = i+1; j < n; ++j )
					d[i][j] = d[j][i] = Math.sqrt(S(x[i]-x[j])+S(y[i]-y[j]));
			for ( bad = MAXSIZE, good = 0; Math.abs(bad-good) >= tol; ) {
				mid =(good+bad)/2;
				for ( i = 0; i < n+4; ++i )
					rank[p[i] = i] = 0;
				for ( i = 0; i < n; ++i )
					for ( j = i+1; j < n; ++j )
						if ( d[i][j] <= r[i]+r[j] || d[i][j]-r[i]-r[j] < mid )
							if ( find(i) != find(j) )
								merge(i,j);
				for ( i = 0; i < n; ++i ) {
					if ( y[i]-r[i] < mid && find(i) != find(n) )
						merge(i,n);
					if ( 1000-y[i]-r[i] < mid && find(i) != find(n+1) )
						merge(i,n+1);
					if ( x[i]-r[i] < mid && find(i) != find(n+2) )
						merge(i,n+2);
					if ( 1000-x[i]-r[i] < mid && find(i) != find(n+3) )
						merge(i,n+3);
				}
				for ( i = 0; i < n+4; ++i ) father[i] = find(i);
				boolean ok = true ;
				for ( i = n; i < n+4; ++i )
					for ( j = i+1; j < n+4; ++j )
						if ( father[i] == father[j] ) ok = false;
				if ( ok ) good = mid; else bad = mid;
			}
		}
		bw.flush();
	}
}

