/*
 * 1079. A Careful Approach
 * TOPIC: binary search, permutations
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 8, oo = (1<<29);
	final double tol = 1e-9;
	double ans;
	int n,mask,cs;
	double []x = new double[N], y = new double[N], t = new double[N];
	int L( int k ) { return k & (~k + 1); }
	int B( int k ) { return 1 << k; }
	int MASK( int k ) { return B(k)-1; }
	int []which = new int[1<<N], c = new int[N];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	boolean canBeArranged( double gap ) {
		int i;
		for ( t[0] = x[c[0]], i = 1; i < n; ++i ) 
			if ( (t[i]=Math.max(t[i-1]+gap,x[c[i]]))>y[c[i]] )
				return false ;
		return true ;
	}
	void f() {
		if ( !canBeArranged(0) ) return ;
		for(double good=0,bad=+oo,mid;Math.abs(bad-good)>tol;ans=Math.max(ans,good))
			if ( canBeArranged(mid=(good+bad)/2) )
				good=mid;
			else bad=mid;
	}
	int r( double s ) {
		int dx = (int)Math.floor(s), ux = (int)Math.ceil(s);
		return s-dx<ux-s?dx:ux;
	}
	void rec( int k ) {
		if ( k == n ) { f(); return ; }
		for ( int u=(~mask&MASK(n)),i; u>0 && (i=which[L(u)])>=0; mask|=B(i), c[k]=i, rec(k+1), mask&=~B(i), u&=~L(u) );
	}
	void go() throws Exception {
		for ( int k = 0; k < N; which[B(k)] = k, ++k );
		for (;(n=scan.nextInt())!=0; ans=0,rec(0),System.out.printf("Case %d: %d:%02d\n",++cs,((int)ans)/60,r(ans-60*((int)(ans/60)))) ) 
			for ( int k = 0; k < n; x[k] = scan.nextInt()*60, y[k] = scan.nextInt()*60, ++k );
	}
};

