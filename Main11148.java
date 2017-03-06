/*
 * 11148. Moliu Fractions
 * TOPIC: parsing, regex
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	Pattern P = Pattern.compile("\\d[0-9/-]*"), p0 = Pattern.compile("(\\d+)"), p1 = Pattern.compile("(\\d+)/(\\d+)"), p2 = Pattern.compile("(\\d+)-(\\d+)/(\\d+)");
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String s;
	public static void main( String[] args ) throws Exception { new Main().go(); };
	long gcd( long x, long y ) { return y==0?x:gcd(y,x%y); };
	class Frac {
		long p,q;
		Frac() { p=0; q=1; };
		Frac( long P, long Q ) { this.p = P; this.q = Q; };
		Frac mult( Frac other ) {
			long d = gcd(this.p*other.p,this.q*other.q);
			return new Frac(this.p*other.p/d,this.q*other.q/d);
		};
		public String toString() {
			long d = gcd(this.p,this.q);
			this.p /= d; this.q /= d;
			long n = this.p/this.q;
			StringBuilder sb = new StringBuilder();
			if ( (this.p%this.q) == 0 ) {
				sb.append(n);
				return sb.toString();
			};
			if ( n > 0 ) {
				sb.append(n);
				sb.append("-");
			}
			sb.append(this.p%this.q);
			sb.append("/");
			sb.append(this.q);
			return sb.toString();
		};
	};
	void go() throws Exception {
		int ts = Integer.parseInt(br.readLine());
		for (;ts-->0;) {
			List<Frac> lst = new LinkedList<Frac>();
			s = br.readLine();
			Matcher m,M;
			for (;;) {
				M = P.matcher(s);
				if ( !M.find() ) break ;
				m = p2.matcher(M.group(0));
				if ( m.find() ) {
					Long a = Long.parseLong(m.group(1)), b = Long.parseLong(m.group(2)), c = Long.parseLong(m.group(3));
					lst.add(new Frac(a*c+b,c));
					s = s.substring(M.end());
					continue ;
				};
				m = p1.matcher(M.group(0));
				if ( m.find() ) {
					Long a = Long.parseLong(m.group(1)), b = Long.parseLong(m.group(2));
					lst.add(new Frac(a,b));
					s = s.substring(M.end());
					continue ;
				};
				m = p0.matcher(M.group(0));
				if ( m.find() ) {
					Long a = Long.parseLong(m.group(1));
					lst.add(new Frac(a,1L));
					s = s.substring(M.end());
					continue ;
				}
				else break ;
			};
			Frac ax = new Frac(1L,1L);
			for ( Frac f: lst ) 
				ax = ax.mult(f);
			System.out.println(ax);
		};
	};
};

