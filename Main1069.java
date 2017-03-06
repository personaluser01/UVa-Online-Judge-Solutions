/*
 * 1069. Always an Integer
 * TOPIC: maths, polynomials, divisibility, regex
 * status: Accepted
 */
import java.util.regex.*;
import java.io.*;
import java.util.*;

class Main {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	Pattern outer = Pattern.compile("\\s*[(](.*)[)]\\s*/\\s*(\\d+)"), monomial = Pattern.compile("^([-+]?)(\\d+)n[\\^](\\d+)");
	Pattern mon1 = Pattern.compile("^([-+]?)n[\\^](\\d+)"), mon2 = Pattern.compile("^([-+]?)n"), cons = Pattern.compile("^([-+]?)(\\d+)");
	Pattern mon3 = Pattern.compile("^([-+]?)n[\\^](\\d+)"), mon4 = Pattern.compile("^([-+]?)(\\d+)n");
	StringTokenizer st;
	final int MAXDEG = 0x80;
	int cs = 0,idx;
	long D;
	public static void main( String [] args ) throws Exception { new Main().go(); };
	long Pow( long x, long n ) {
		long ax = (1L%D);
		for (;n>0; x *= x, x %= D, n >>= 1 ) 
			if ( (n&1) == 1 ) {
				ax *= x;
				ax %= D;
			}
		return ax;
	};
	class Monomial {
		long C,E;
		boolean hasVar;
		Monomial() { E = 0; hasVar = false; };
		Monomial( long C, long E, boolean f ) { this.C = (C%D); this.E = E; this.hasVar = f; };
		long eval( long t ) {
			if ( hasVar )
				return C*Pow(t,E);
			return C;
		};
		public String toString() {
			StringBuilder sb = new StringBuilder();
			sb.append(Long.toString(C));
			if ( hasVar ) sb.append("n");
			if ( E > 0 ) sb.append(Long.toString(E));
			return sb.toString();
		};
	};
	Monomial next( String p ) {
		String s = p.substring(idx);
		Matcher m = monomial.matcher(s);
		// Pattern outer = Pattern.compile("\\s*[(](.*)[)]\\s*/\\s*(\\d+)"), monomial = Pattern.compile("^([-+]?)(\\d+)n[^](\\d+)");
		// Pattern mon1 = Pattern.compile("^([-+]?)n[^](\\d+)"), mon2 = Pattern.compile("^([-+]?)n"), cons = Pattern.compile("^([-+]?)(\\d+)");
		// Pattern mon4 = Pattern.compile("^([-+]?)(\\d+)n");
		if ( m.find() ) {
			idx += m.end();
			if ( m.group(1).length() == 0 || m.group(1).equals("+") ) 
				return new Monomial(Long.parseLong(m.group(2)),Long.parseLong(m.group(3)),true);
			return new Monomial(-Long.parseLong(m.group(2)),Long.parseLong(m.group(3)),true);
		}
		else {
			m = mon1.matcher(s);
			if ( m.find() ) {
				idx += m.end();
				if ( m.group(1).length() == 0 || m.group(1).equals("+") ) 
					return new Monomial(1L,Long.parseLong(m.group(2)),true);
				return new Monomial(-1L,Long.parseLong(m.group(2)),true);
			}
			else {
				m = mon4.matcher(s);
				if ( m.find() ) {
					idx += m.end();
					if ( m.group(1).length() == 0 || m.group(1).equals("+") )
						return new Monomial(Long.parseLong(m.group(2)),1L,true);
					return new Monomial(-Long.parseLong(m.group(2)),1L,true);
				}
				else {
					m = mon2.matcher(s);
					if ( m.find() ) {
						idx += m.end();
						if ( m.group(1).length() == 0 || m.group(1).equals("+") )
							return new Monomial(1L,1L,true);
						return new Monomial(-1L,1L,true);
					}
					else {
						m = cons.matcher(s);
						if ( !m.find() ) return null;
						idx += m.end();
						if ( m.group(1).length() == 0 || m.group(1).equals("+") )
							return new Monomial(Long.parseLong(m.group(2)),0,false);
						return new Monomial(-Long.parseLong(m.group(2)),0,false);
					}
				}
			}
		}
	};
	long Eval( Monomial []a, long t ) {
		long res = 0;
		for ( int i = 0; a[i] != null; ++i ) {
			res += a[i].eval(t);
			res %= D;
		};
		return res;
	};
	void go() throws Exception {
		String s,p;
		int i,j,k,n;
		Monomial []a = new Monomial[MAXDEG];
		while ( (s=br.readLine())!=null && !s.equals(".") ) {
			Matcher m = outer.matcher(s);
			m.find();
			p = m.group(1); idx = 0;
			D = Long.parseLong(m.group(2));
			for ( n = 0; (a[n] = next(p)) != null; ++n );
			for ( i = n; i < MAXDEG; a[i++] = null );
			boolean ok = true;
			for ( i = 1; i <= n+1 && ok; ++i ) 
				if ( 0 != Eval(a,i) ) ok = false;
			System.out.println("Case "+(++cs)+": "+(ok?"Always an integer":"Not always an integer"));
		};
	};
};

