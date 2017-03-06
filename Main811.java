/*
 * 811. Fortified Forest
 * TOPIC: convex hull, gift wrapping, computational geometry
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 16;
	int n,cs = 0;
	final double oo = (double)(1<<29), tol = 1e-9;
	int []x = new int[N],y = new int[N],vl = new int[N],l = new int[N],len = new int[1<<N],val = new int[1<<N];
	char []which = new char[1<<N], bts = new char[1<<N];
	Scanner scan = new Scanner(System.in);
	public static void main( String [] args ) throws Exception { new Main().go(); }
	int L( int u )   { return u&((~u)+1); }
	int who( int u ) { assert 0 == (u&(u-1)); return (int)which[u];   }
	double area( double a, double b, double c, double d, double p, double q ) {
		double u = c-a, v = d-b, x = p-a, y = q-b;
		return u*y-x*v;
	}
	boolean ccw( double a, double b, double c, double d, double p, double q ) {
		return area(a,b,c,d,p,q) > 0;
	}
	double scalar_product( double a, double b, double c, double d, double p, double q ) {
		double u = c-a, v = d-b, x = p-a, y = q-b;
		return u*x+v*y;
	}
	double A( double x ) { return x*x; }
	double convex_hull( int u ) {
		if ( bts[u] <= 1 ) return 0.00;
		double []a = new double[bts[u]+1], b = new double[bts[u]+1];
		double s = 0,lx,ly;
		int i,j,k,t,m = 0,idx = -1;
		int []next = new int[bts[u]+1];
		boolean []used = new boolean[bts[u]+1];
		for ( i = 0; i < n; ++i )
			if ( 1 == ((u>>i)&1) ) { a[m] = x[i]; b[m++] = y[i]; }
		// if ( bts[u] == 2 ) { return 2*Math.sqrt(A(a[1]-a[0])+A(b[1]-b[0])); }
		for ( lx=ly=+oo, i=0; i<m; ++i )
			if ( a[i]<lx || Math.abs(lx-a[i])<tol && ly>b[i] ) { lx = a[i]; ly = b[i]; idx = i; }
		for ( i = 0; i < m; ++i ) { next[i] = -1; used[i] = false; }
		for ( i=idx;;used[i=next[i]]=true ) {
			for ( next[i]=(i+1)%m, j=0; j<m; ++j ) {
				if ( used[j]||ccw(a[i],b[i],a[next[i]],b[next[i]],a[j],b[j]) ) continue ;
				if ( Math.abs(area(a[i],b[i],a[next[i]],b[next[i]],a[j],b[j]))<tol ) {
					assert scalar_product(a[i],b[i],a[next[i]],b[next[i]],a[j],b[j]) >= 0;
					if ( A(a[next[i]]-a[i])+A(b[next[i]]-b[i])<A(a[j]-a[i])+A(b[j]-b[i]) )
						next[i] = j;
				}
				else next[i] = j;
			}
			if ( i!=idx ) {
				if ( ccw(a[i],b[i],a[next[i]],b[next[i]],a[idx],b[idx]) ) continue ;
				if ( Math.abs(area(a[i],b[i],a[next[i]],b[next[i]],a[j],b[j]))<tol ) {
					assert scalar_product(a[i],b[i],a[next[i]],b[next[i]],a[idx],b[idx]) >= 0;
					if ( A(a[next[i]]-a[i])+A(b[next[i]]-b[i])<A(a[idx]-a[i])+A(b[idx]-b[i]) )
						next[i] = idx;
				}
				else next[i] = idx;
			}
			if ( next[i] == idx ) break ;
		}
		for(i=idx;;i=next[i]) {
			s+=Math.sqrt(A(a[next[i]]-a[i])+A(b[next[i]]-b[i]));
			if ( next[i]==idx ) break ;
		}
		return s;
	}
	void go() throws Exception {
		int i,j,k,u,v,w,U;
		for ( k = 0; k < N; ++k ) which[1<<k] = (char)k;
		for ( u = 0; u < (1<<N); ++u ) bts[u]=(char)(bts[u>>1]+((char)(u&1)));
		while((n=scan.nextInt())!=0){
			if ( cs >= 1 ) System.out.println("");
			for ( i = 0; i < n; ++i ) {
				x[i]  = scan.nextInt();
				y[i]  = scan.nextInt();
				vl[i] = scan.nextInt();
				l[i]  = scan.nextInt();
			}
			System.out.println("Forest "+(++cs));
			len[0] = val[0] = 0;
			for ( u = 1; u < (1<<n); ++u ) {
				len[u] = len[u&~L(u)]+l[who(L(u))];
				val[u] = val[u&~L(u)]+vl[who(L(u))];
			}
			w = (1<<29); U = (1<<N)-1;
			for ( u = 0; u < (1<<n); ++u ) 
				if ( convex_hull(v=(~u)&((1<<n)-1)) <= (double)len[u] ) 
					if ( val[u]<w || (val[u]==w && bts[u]<bts[U]) ) w = val[U = u]; 
			System.out.print("Cut these trees:");
			for ( i = 0; i < n; ++i )
				if ( 1==((U>>i)&1) )
					System.out.print(" "+(i+1));
			System.out.print("\nExtra wood: ");
			System.out.printf("%.2f\n",len[U]-convex_hull((~U)&((1<<n)-1)));
			//if ( n >= 6 ) System.out.println(val[(((1<<n)-1)&(~((1<<1)|(1<<3)|(1<<4))))]);
			//if ( n >= 6 ) System.out.println(val[(((1<<n)-1)&(~((1<<0)|(1<<2)|(1<<3))))]);
		}
	}
};

