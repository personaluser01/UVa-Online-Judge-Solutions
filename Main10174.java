/*
 * 10147.
 * TOPIC: divisibilty, modulo 8
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;
import java.lang.Math.*;

class Main {
	double tol = 1e-9;
	long oo = (1L<<40);
    public static void main( String [] args ) throws Exception { new Main().go(); }
    int f( long Q, boolean revOrder, String res ) {
		if ( Q == 0 ) {
			System.out.println("0 0");
			return 1;
		}
        long a,b,s = (long)(Math.sqrt(Q)+tol),B,i,j,c,d;
        // assert Q >= 0;
		for ( i = s; i >= 1; --i ) {
			if ( 0 != (Q%i) ) continue ;
			c = i; d = Q/i;
			if ( ((a=c+d)&1) != 0 || ((b=d-c)&1) != 0 )
				continue ;
			a >>= 1; b >>= 1;
			if ( a >= 0 && b >= 0 ) {
				// assert a*a - b*b == Q;
				if ( revOrder )
					System.out.println(b + " " + a);
				else
					System.out.println(a + " " + b);
				return 1;
			}
		}
        System.out.println(res);
		return 0;
    }
    void go() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        long m,n,rem,Q,a,b,k,u,v;
        StringTokenizer st;
        String s,res;
        while ( (s = br.readLine()) != null ) {
            st = new StringTokenizer(s);
            m = Long.parseLong(st.nextToken());
            n = +oo;
            if ( st.hasMoreTokens() )
                n = Long.parseLong(st.nextToken());
            if ( n == +oo ) {
                Q = m;
                if ( (Q&1) != 0 )
                    res = new String("Spinster Number.");
                else 
                    res = new String("Bachelor Number.");
                rem = (Math.abs(Q)%8);
                if ( rem == 2 || rem == 6 ) {
                    System.out.println(res);
                    continue ;
                }
                if ( Q < 0 ) 
                    f(-Q,true,res);
                else 
                    f(Q,false,res);
            }
            else {
				if ( m > n ) { k = m; m = n; n = k; }
				if ( ((m-2)%4) != 0 ) v = (m-2)/4+1;
				else v = (m-2)/4;
				u = (n-2)/4;
				k = (u-v+1);
				System.out.println(k);
            }
        }
    }
};

