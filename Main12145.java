/*
 * 12145. Bases
 * TOPIC: number bases
 * status: in progress
 * 8 777 26 4444
 */
import java.io.*;
import java.util.*;

class Main {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	public static void main( String [] args ) throws Exception { new Main().go(); }
	final int N = (1<<12);
	final double tol = 1e-9, oo = (1e31);

	class Poly {
		long []c;
		int n;
		Poly( int n ) { c = new long[this.n = N]; };
		Poly() { c = new long[this.n = N]; };
		Poly add( Poly other ) {
			if ( other == null ) return this;
			Poly p = new Poly(Math.max(this.n,other.n));
			for ( int i = 0; i < N; ++i )
				p.c[i] = c[i]+other.c[i];
			return p;
		};
		Poly sub( Poly other ) {
			if ( other == null ) return this;
			Poly p = new Poly(Math.max(this.n,other.n));
			for ( int i = 0; i < N; ++i )
				p.c[i] = c[i]-other.c[i];
			return p;
		};
		Poly mul( Poly other ) {
			if ( other == null ) return this;
			Poly p = new Poly(this.n+other.n+4);
			int i,j,k;
			for ( i = 0; i < N; ++i )
				for ( j = 0; j+i < N; ++j ) 
					p.c[i+j] += this.c[i]*other.c[j];
			return p;
		};
		double valueAt( double t ) {
			double s = 0;
			int m = this.getDeg();
			if ( Math.abs(t-oo) < tol ) {
				if ( 1 == (m&1) ) {
					if ( c[m] < 0 ) return -oo;
					return +oo;
				}
				else {
					if ( c[m] < 0 ) return -oo;
					return +oo;
				}
			}
			if ( Math.abs(t+oo) < tol ) {
				if ( 1 == (m&1) ) {
					if ( c[m] < 0 ) return +oo;
					return -oo;
				}
				else {
					if ( c[m] < 0 ) return -oo;
					return +oo;
				}
			}
			for ( int i = m; i >= 0; s *= t, s += this.c[i--] );
			return s;
		};
		Poly diff() {
			Poly p = new Poly();
			for ( int i = 1; i < N; ++i )
				p.c[i-1] = i*this.c[i];
			return p;
		};
		Poly( long x ) {
			int i = 0,j,k;
			this.c = new long[this.n=N];
			do {
				this.c[i++] = (x%10);
			} while ( (x/=10) > 0 );
		};
		boolean isZero() {
			int i;
			for ( i = N-1; i >= 0 && c[i] == 0; --i );
			return i<0;
		};
		int getDeg() {
			int k;
			for ( k = N-1; k >= 0 && c[k] == 0; --k );
			return Math.max(k,0);
		};
		double getRootAt( double l, double r ) {
			double L = this.valueAt(l), R = this.valueAt(r), low = -1, high = -1, mid;
			if ( Math.abs(L) < tol )
				return l;
			if ( Math.abs(R) < tol )
				return r;
			if ( L > 0 && R > 0 || L < 0 && R < 0 ) return +oo;
			if ( L < 0 ) {
				/* R > 0 */
				for ( low = l, high = r; Math.abs(high-low) >= tol; )
					if ( this.valueAt(mid=(low+high)/2)<0 )
						low=mid;
					else high=mid;
			}
			else {
				/* L > 0, R < 0 */
				for ( low = l, high = r; Math.abs(high-low) >= tol; )
					if ( this.valueAt(mid=(low+high)/2)>0 )
						low=mid;
					else high=mid;
			}
			return high;
		};
		double []findRoots() {
			int m = this.getDeg();
			double low,high,z;
			/*assert m >= 1;*/
			if ( m == 1 ) {
				double []res = new double[1];
				res[0] = (-c[0]+0.00)/c[1];
				return res;
			};
			double []ld = this.diff().findRoots();
			if ( ld == null || ld.length == 0 ) return null;
			int k = ld.length;
			low = -oo; high = ld[0];
			List<Double> res = new LinkedList<Double>();
			if ( (z = getRootAt(low,high)) < +oo )
				res.add(z);
			for ( int i = 0; i < k-1; ++i ) {
				low = ld[i]; high = ld[i+1];
				if ( (z = getRootAt(low,high)) < +oo )
					res.add(z);
			}
			low = ld[k-1]; high = +oo;
			if ( (z = getRootAt(low,high)) < +oo )
				res.add(z);
			double []e = new double[res.size()];
			for ( int l = 0; l < res.size(); ++l )
				e[l] = res.get(l);
			return e;
		};
	};

	class Parser {
		char []buff;
		int cur;
		Cell root;
		Parser( String s ) { 
			int len = s.length();
			buff = new char[len+3];
			buff[len] = '$'; cur = 0;
			for ( int i = 0; i < len; ++i )
				buff[i] = s.charAt(i);
			root = expr();
			/*assert buff[cur] == '$';*/
		};
		class Cell {
			char op;
			long B;
			Cell left,right;
			Cell() { op='$'; left=right=null; };
			Cell( char ch ) { this.op=ch; left=right=null; };
		};
		Cell f00() {
			if ( '0' <= buff[cur] && buff[cur] <= '9' ) {
				long res = 0;
				for (;'0' <= buff[cur] && buff[cur] <= '9'; res *= 10, res += (long)(buff[cur++]-'0') );
				Cell c = new Cell();
				c.B = res;
				return c;
			}
			return null;
		};
		Cell f01( Cell left ) {
			if ( buff[cur] == '*' ) {
				Cell c = new Cell(buff[cur++]);
				c.left = left; c.right = f00();
				return f01(c);
			}
			return left;
		};
		Cell f02( Cell left ) {
			if ( buff[cur] == '+' ) {
				Cell c = new Cell(buff[cur++]);
				c.left = left; c.right = f01(f00());
				return f02(c);
			}
			return left;
		};
		Cell expr() { return f02(f01(f00())); };
		Poly convert( Cell c ) {
			if ( c == null ) return null;
			if ( c.op == '+' ) 
				return convert(c.left).add(convert(c.right));
			if ( c.op == '*' )
				return convert(c.left).mul(convert(c.right));
			/*assert c.op == '$';*/
			return new Poly(c.B);
		};
	};

	void go() throws Exception {
		String s,sleft,sright;
		int i,j,k,m,n;
		char LargestDigit;
		for(;(s=br.readLine())!=null&&!s.equals("=");) {
			for ( j = 0; s.charAt(j) != '='; ++j );
			sleft = s.substring(0,j); sright = s.substring(j+1);
			Parser parseLeft = new Parser(sleft), parseRight = new Parser(sright);
			Poly polyLeft = parseLeft.convert(parseLeft.root), polyRight = parseRight.convert(parseRight.root);
			Poly z = polyLeft.sub(polyRight);
			LargestDigit = '1';
			for ( char x: sleft.toCharArray() )
				if ( '0' <= x && x <= '9' )
					if ( x > LargestDigit ) LargestDigit = x;
			for ( char x: sright.toCharArray() )
				if ( '0' <= x && x <= '9' )
					if ( x > LargestDigit ) LargestDigit = x;
			if ( z.isZero() ) {
				int xx = LargestDigit-'0';
				System.out.println((++xx)+"+");
				continue ;
			}
			if ( z.getDeg() == 0 ) {
				System.out.println("*");
				continue ;
			}
			double []roots = z.findRoots();
			if ( roots == null || roots.length == 0 ) {
				System.out.println("*");
				continue ;
			}
			StringBuilder sb = new StringBuilder();
			boolean ok = false;
			for ( i = 0; i < roots.length; ++i ) {
				if ( Math.abs(roots[i]-((int)(roots[i]+tol)))<tol) {
					if ( ok ) sb.append(" ");
					ok = true ;
					sb.append(Integer.toString((int)(roots[i]+tol)));
				}
				// System.out.println("root = "+roots[i]);
			}
			if ( !ok ) System.out.println("*");
			else System.out.println(sb.toString());
		}
	}
};

