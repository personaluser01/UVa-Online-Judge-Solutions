/*
 * 12151. Higgs Boson
 * TOPIC: maths, fractions
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	long []A = new long[2], B = new long[2], C = new long[2], D = new long[2];
	Set<Frac> s;
	public static void main( String [] args ) throws Exception { new Main().go(); };
	long gcd( long x, long y ) { if ( y == 0 ) return x; else return gcd(y,x%y); };
	class Frac implements Comparable<Frac> {
		long m,n;
		Frac() { m = 0; n = 1; };
		void normalize() {
			long g = gcd(m,n);
			m /= g; n /= g;
			if ( m == 0 ) { n = 1; };
			if ( n < 0 ) { m = -m; n = -n; };
		};
		Frac( long M, long N ) { this.m = M; this.n = N; normalize(); };
		Frac add( Frac other ) {
			return new Frac(this.m*other.n+this.n*other.m,this.n*other.n);
		};
		Frac sub( Frac other ) {
			return new Frac(this.m*other.n-this.n*other.m,this.n*other.n);
		};
		Frac mul( Frac other ) {
			return new Frac(this.m*other.m,this.n*other.n);
		};
		boolean isNonnegative() { return this.m >= 0; };
		public int compareTo( Frac other ) {
			if ( other.m == (1L<<59) ) return -1;
			long t = this.m*other.n-this.n*other.m;
			if ( t == 0 ) return 0;
			return t<0?-1:1;
		};
	};

	boolean solution_theta() {
		/*
		 * A[0] == A[1], B[0] == B[1]
		 */
		Frac r;
		for ( int i = 0; i <= 1; ++i )
			if ( D[i] < 0 )
				D[i]=D[i]+360*(long)(Math.ceil(D[i]/-360.00));
			else D[i]%=360;
		if ( C[0]==C[1] ) {
			if ( D[0]!=D[1] ) 
				return false ;
			r=new Frac(0,1);
		}
		else if ( D[0]==D[1] ) 
			r=new Frac(0,1);
		else {
			long d = D[0]-D[1];
			if ( d < 0 ) d = d+360*(long)(Math.ceil(d/-360.0));
			else d %= 360;
			r=new Frac(d,Math.abs(C[1]-C[0]));
		}
		s.add(r);
		return true ;
	}
	
	boolean scenario01() {
		long k;
		Frac r,t;

		if ( A[0] == A[1] && B[0] != B[1] ) return false ;

		if ( A[0] == A[1] && B[0] == B[1] )
			return solution_theta();

		r = new Frac(B[0]-B[1],A[1]-A[0]);
		if ( A[0]*r.m+B[0]*r.n == 0 ) {
			s.add(r);
			return true ;
		}

		assert A[0] != A[1];

		Frac []theta = new Frac[2];
		theta[0] = new Frac(C[0],1L).mul(r).add(new Frac(D[0],1L));
		theta[1] = new Frac(C[1],1L).mul(r).add(new Frac(D[1],1L));
		Frac diff = theta[0].sub(theta[1]);
		if ( diff.n != 1 || 0 != (diff.m%360) )
			return false ;
		s.add(r);		
		return true ;
	};

	long num,den;

	boolean f1() {
		for ( int i = 0; i <= 1; ++i )
			if ( D[i] < 0 )
				D[i] = D[i]+360*(long)(Math.ceil(D[i]/-360.0));
			else D[i] %= 360;
		num = D[1]-D[0]; den = C[0]-C[1];
		if ( den < 0 ) { den *= -1; num *= -1; };
		if ( num < 0 ) num = num+360*(long)(Math.ceil(num/-360.0));
		if ( den == 0 ) {
			if ( num == 0 ) den = 1;
			else return false ;
		}
		else if ( num == 0 ) den = 1;
		else {
			long g = gcd(num,den);
			num /= g; den /= g;
		}
		s.add(new Frac(num,den));
		return true ;
	}

	boolean f0() {
		boolean ok = true ;
		num = B[1]-B[0]; den = A[0]-A[1];
		if ( den == 0 ) {
			if ( num == 0 ) 
				ok = f1();
			else ok = false ;
		}
		else if ( den*num >= 0 ) {
			if ( num == 0 ) den = 1;
			else {
				num = Math.abs(num);
				den = Math.abs(den);
				long g = gcd(num,den);
				num /= g; den /= g;
			}
			if ( ok ) {
				long th0 = C[0]*num+D[0]*den, th1 = C[1]*num+D[1]*den;
				ok = (A[0]*num+B[0]*den==0)||((th0-th1)%(360*den)==0);
			}
		}
		else ok = false ;
		if ( ok ) s.add(new Frac(num,den));
		return ok;
	}

	void go() throws Exception {
		int i,j,k;
		Frac t,w = new Frac(1L<<59,1L);
		for (;;) {
			for ( i = 0; i <= 1; ++i ) {
				A[i] = scan.nextLong();
				B[i] = scan.nextLong();
				C[i] = scan.nextLong();
				D[i] = scan.nextLong();
			}
			if ( 0 == A[0] && 0 == A[1] && 0 == B[0] && 0 == B[1] && 0 == C[0] && 0 == C[1] && 0 == D[0] && 0 == D[1] )
				break ;
			s = new TreeSet<Frac>();
			w = new Frac((1L<<59),1L);
			f0();
			A[1] = -A[1]; B[1] = -B[1]; D[1] += 180;
			f0();
			for ( Iterator<Frac> it = s.iterator(); it.hasNext(); ) 
				if ( (t=it.next()).isNonnegative() && t.compareTo(w) == -1 )
				// if ( (t=it.next()).compareTo(w) == -1 )
					w = t;
			if ( w.m != (1L<<59) )
				System.out.println(w.m+" "+w.n);
			else System.out.println("0 0");
		};
	};
};

