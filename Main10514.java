/*
 * 10514. River Crossing
 * TOPIC: geometry, ternary search, apsp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x80, L = 0, R = 1, oo = (1<<29);
	final double tol = 1e-11;
	Scanner scan = new Scanner(System.in);
	int []n = new int[2],m = new int[N];
	double [][]x = new double[N][N], y = new double[N][N], X = new double[2][N], Y = new double[2][N];
	int polygons,V,src,sink;
	public static void main( String []args ) throws Exception { new Main().go(); }
	class Point {
		double x,y;
		Point( double x, double y ) { this.x = x; this.y = y; }
		double sqDistTo( Point other ) { return (this.x-other.x)*(this.x-other.x)+(this.y-other.y)*(this.y-other.y); }
		Point( Point a, Point b, double t ) {
			this.x = a.x+(b.x-a.x)*t;
			this.y = a.y+(b.y-a.y)*t;
		}
		double sqDistTo( Foo f ) {
			double a,b,na,nb;
			for ( a = 0.00, b = 1.00; Math.abs(b-a) > tol; ) {
				na = (2.00*a+b)/3.00;
				nb = (a+2.00*b)/3.00;
				Point A = new Point(f.p,f.q,na), B = new Point(f.p,f.q,nb);
				if ( this.sqDistTo(A) < this.sqDistTo(B) ) b = nb;
				else a = na;
			}
			return this.sqDistTo(new Point(f.p,f.q,(a+b)/2.00));
		}
	}
	class Foo {
		Point p,q;
		Foo( Point p, Point q ) { this.p = p; this.q = q; }
		double sqDistTo( Foo other ) {
			double x = Math.min(this.p.sqDistTo(other),this.q.sqDistTo(other));
			double y = Math.min(other.p.sqDistTo(this),other.q.sqDistTo(this));
			return Math.min(x,y);
		}
	}
	Foo [][]q = new Foo[N][N], p = new Foo[2][N];
	int []len = new int[N];
	double [][]islands = new double[N][N], w = new double[2][N], g = new double[N][N];
	double []d = new double[2];
	void go() throws Exception {
		int i,j,k,l,t,ts = scan.nextInt();
		for (;ts-->0;) {
			for ( t = L; t <= R; n[t++] = scan.nextInt() );
			polygons = scan.nextInt();
			for ( t = L; t <= R; ++t ) {
				for ( i = 0; i < n[t]; ++i ) {
					X[t][i] = scan.nextDouble();
					Y[t][i] = scan.nextDouble();
				}
				for ( i = 0; i < n[t]-1; ++i ) 
					p[t][i] = new Foo(new Point(X[t][i],Y[t][i]),new Point(X[t][i+1],Y[t][i+1]));
			}
			for ( i = 0; i < polygons; ++i ) 
				for ( m[i] = scan.nextInt(), j = 0; j < m[i]; ++j ) 
				{ x[i][j] = scan.nextDouble(); y[i][j] = scan.nextDouble(); }
			for ( i = 0; i < polygons; ++i ) 
				for ( len[i] = 0, j = 0; j < m[i]; ++j ) {
					k = (j+1)%m[i];
					q[i][len[i]++] = new Foo(new Point(x[i][j],y[i][j]),new Point(x[i][k],y[i][k]));
				}
			for ( i = 0; i < polygons; ++i ) 
				for ( j = i+1; j < polygons; islands[j][i] = islands[i][j], ++j ) 
					for ( islands[i][j] = +oo, l = 0; l < len[i]; ++l )
						for ( k = 0; k < len[j]; ++k )
							islands[i][j] = Math.min(islands[i][j],q[i][l].sqDistTo(q[j][k]));
			for ( i = 0; i < polygons; ++i )
				for ( j = 0; j < polygons; ++j )
					islands[i][j] = Math.sqrt(islands[i][j]);
			for ( k = 0; k < polygons; ++k )
				for ( i = 0; i < polygons; ++i )
					for ( j = 0; j < polygons; ++j )
						islands[i][j] = Math.min(islands[i][k]+islands[k][j],islands[i][j]);
			for ( t = L; t <= R; ++t )
				for ( j = 0; j < polygons; w[t][j] = Math.sqrt(w[t][j]), ++j )
					for ( w[t][j] = +oo, i = 0; i < n[t]-1; ++i )
						for ( k = 0; k < len[j]; ++k )
							w[t][j] = Math.min(w[t][j],p[t][i].sqDistTo(q[j][k]));
			for ( t = L; t <= R; d[t] = Math.sqrt(d[t]), ++t )
				for ( d[t] = +oo, i = 0; i < n[t]-1; ++i )
					for ( j = 0; j < n[t^1]-1; ++j )
						d[t] = Math.min(d[t],p[t][i].sqDistTo(p[t^1][j]));
			src = polygons; sink = polygons+1; V = sink+1;
			for ( i = 0; i < polygons; ++i )
				for ( j = 0; j < polygons; ++j )
					g[i][j] = islands[i][j];
			for ( i = 0; i < polygons; ++i )
				g[src][i] = g[i][src] = w[L][i];
			for ( j = 0; j < polygons; ++j )
				g[sink][j] = g[j][sink] = w[R][j];
			g[src][sink] = d[L]; g[sink][src] = d[R];
			for ( k = 0; k < V; ++k )
				for ( i = 0; i < V; ++i )
					for ( j = 0; j < V; ++j )
						g[i][j] = Math.min(g[i][j],g[i][k]+g[k][j]);
			System.out.printf("%.3f\n",g[src][sink]);
			// System.out.printf("%f\n",(g[3][2]));
		}
		// System.out.printf("%f\n",Math.sqrt(new Point(0,0).sqDistTo(new Foo(new Point(1,0),new Point(0,1)))));
	}
};


