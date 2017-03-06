/*
 * 10357. Points!!!
 * TOPIC: ad hoc
 * status: Accepred
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	Pattern pat = Pattern.compile("\\w+=(\\d+)");
	final double tol = 1e-9;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	StringTokenizer st;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Foo {
		int x,y,v;
		Foo( int x, int y, int v ) { this.x = x; this.y = y; this.v = v; }
	}
	Foo []p;
	int S( int x ) { return x*x; }
	int a,b,c,d,e,f,g,T;
	int calcZ( int t ) {
		return a*t*t + b*t + c;
	}
	int calcX( int t ) {
		return d*t + e;
	}
	int calcY( int t ) {
		return f*t + g;
	}
	void go() throws Exception {
		int i,j,k,l,t,n,m;
		String s;
		boolean ok;
		while ( (s=br.readLine()) != null ) {
			Matcher mat = pat.matcher(s);
			mat.find();
			p = new Foo[n = Integer.parseInt(mat.group(1))];
			for ( i = 0; i < n; ++i ) {
				st = new StringTokenizer(s = br.readLine());
				j = Integer.parseInt(st.nextToken());
				k = Integer.parseInt(st.nextToken());
				t = Integer.parseInt(st.nextToken());
				p[i] = new Foo(j,k,t);
			}
			mat = pat.matcher(br.readLine());
			mat.find();
			for ( m = Integer.parseInt(mat.group(1)), i = 1; i <= m; ++i ) {
				st = new StringTokenizer(br.readLine());
				a = Integer.parseInt(st.nextToken());
				b = Integer.parseInt(st.nextToken());
				c = Integer.parseInt(st.nextToken());
				double x2,det = b*b-4*a*c;
				d = Integer.parseInt(st.nextToken());
				e = Integer.parseInt(st.nextToken());
				f = Integer.parseInt(st.nextToken());
				g = Integer.parseInt(st.nextToken());
				for ( T = 1; calcZ(T) > 0; ++T );
				System.out.print("Ball "+i+" was ");
				int xx = calcX(T), yy = calcY(T);
				if ( xx < 0 || yy < 0 ) {
					System.out.println("foul at ("+xx+","+yy+")");
					continue ;
				}
				for ( ok = false, j = 0; j < n && !ok; ++j ) {
					int dis = S(xx-p[j].x)+S(yy-p[j].y);
					if ( dis <= T*T*p[j].v*p[j].v ) 
						ok = true ;
				}
				if ( ok )
					System.out.println("caught at ("+xx+","+yy+")");
				else 
					System.out.println("safe at ("+xx+","+yy+")");
			}
		}
	}
};

