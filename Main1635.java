/*
 * 1635. Irrelevant elements
 * TOPIC: binomial theorem, kummer theorem, number bases
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final long N = (1L<<21);
	long []p;
	long m,n;
	int L;
	boolean []isprime = new boolean[(int)N];
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	class Pair {
		int deg;
		long val;
		Pair() {};
		Pair( long val, int deg ) { this.val = val; this.deg = deg; };
	};
	void signature( long m, List<Pair> e ) {
		for ( int k,i = 0; i < L && p[i]*p[i] <= m; ++i ) {
			for ( k = 0; 0 == (m%p[i]); ++k, m/=p[i] );
			if ( k > 0 ) e.add(new Pair(p[i],k));
		}
		if ( m > 1 ) e.add(new Pair(m,1));
	}
	void writeInBase( long n, long B, List<Integer> e ) {
		do e.add((int)(n%B)); while ( (n/=B) > 0 );
	}
	boolean f( long n, long i, List<Pair> e ) {
		for ( Iterator<Pair> it = e.iterator(); it.hasNext(); ) {
			Pair r = it.next();
			long P = r.val,carries,tmp;
			int l;
			List<Integer> a = new LinkedList<Integer>(), b = new LinkedList<Integer>();
			writeInBase(n-i,P,a);
			writeInBase(i,P,b);
			for ( carries=0, tmp=0, l=0; l<a.size() && l<b.size(); carries+=(tmp=(tmp+a.get(l)+b.get(l))/P),++l );
			for (;l<a.size();carries+=(tmp=(tmp+a.get(l++))/P) );
			for (;l<b.size();carries+=(tmp=(tmp+b.get(l++))/P) );
			if ( carries < r.deg ) return false ;
		}
		return true ;
	}
	void go() throws Exception {
		int i,j,k,l,t,top;
		for ( isprime[2] = true, i = 3; i < N; isprime[i] = true, i += 2 );
		for ( i = 3; i < N; i += 2 )
			for ( j = i+i; j < N && isprime[j]; isprime[j] = false, j += i );
		for ( k = 0, i = 0; i < N; ++i )
			if ( isprime[i] ) ++k;
		p = new long[k];
		for ( L = 0, i = 0; i < N; ++i )
			if ( isprime[i] ) p[L++] = i;
		assert L == k;
		for (;scan.hasNext();System.out.println()) {
			n = scan.nextLong();
			m = scan.nextLong();
			if ( m == 0 && n == 0 ) break ;
			List<Pair> e = new LinkedList<Pair>();
			List<Integer> st = new LinkedList<Integer>();
			for ( signature(m,e), top = 0, k = 0, i = 1; i <= n-2; ++i )
				if ( f(n-1,(long)i,e) ) st.add(i+1);
			System.out.println(st.size());
			i = 0;
			for ( Iterator<Integer> it = st.iterator(); it.hasNext(); ) {
				if ( ++i > 1 ) System.out.print(" ");
				System.out.print(it.next());
			}
		}
	}
};

