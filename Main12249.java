/*
 * 12249. Overlapping Scenes
 * TOPIC: ad hoc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x10;
	String []s = new String[N];
	int n,mask,w;
	int []which = new int[1<<N], c = new int[N];
	int L( int k ) { return (k&((~(k))+1)); }
	int who ( int u ) { return which[L(u)]; }
	int BIT( int k ) { return (1<<k); }
	public static void main( String []args ) throws Exception { new Main().go(); }
	String merge( String a, String b ) {
		int i,j,k;
		for ( i = 0; i < a.length(); ++i ) {
			for ( j = 0, k = i; k < a.length() && j < b.length() && a.charAt(k) == b.charAt(j); ++j, ++k );
			if ( j == b.length() && k < a.length() ) continue ;
			if ( j < b.length() && k < a.length() ) continue ;
			return a+b.substring(j);
		}
		return a+b;
	}
	int MASK( int k ) { return BIT(k)-1; }
	void f( int k ) {
		String t;
		int i,u;
		if ( k == n ) {
			for ( t = s[c[0]], i = 1; i < n; t = merge(t,s[c[i++]]) );
			w = Math.min(w,t.length());
			return ;
		}
		for(u=(~mask)&MASK(n);u>0&&(i=who(u))>=0;mask|=BIT(i),c[k]=i,f(k+1),mask&=~BIT(i),u&=~L(u));
	}
	void go() throws Exception {
		int i,j,k,l,t,ts,cs = 0;
		for ( i = 0; i < N; ++i )
			which[1<<i] = i;
		for ( ts = scan.nextInt(); ts-- > 0; ) {
			n = scan.nextInt();
			for ( i = 0; i < n; s[i++] = scan.next() );
			w = (1<<29); mask = 0; f(0);
			System.out.println("Case "+(++cs)+": "+w);
		}
	}
};

