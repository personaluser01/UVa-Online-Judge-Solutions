/*
 * 11083. Zeroes Revisited
 * TOPIC: number theory, neat, formula
 * status: Accepted
 */

/**
 * Created by sj on 06/02/17.
 */

import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class Main {
    private final static int MAXB = 10000;
    private final static double MAXL = Math.log(BigInteger.valueOf(1L<<62).multiply(BigInteger.valueOf(2).subtract(BigInteger.ONE)).doubleValue());
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);
    long n;
    int B;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/11083/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/11083/src/out02.txt")));
        new Main().go();
    }

    static boolean []isprime = new boolean[MAXB];
    static long []p;

    static {
        for ( int i = 3; i < MAXB; i += 2 )
            isprime[i] = true ;
        for ( int i = 3; i < MAXB; i += 2 )
            for ( int j = i+i; j < MAXB && isprime[i]; j += i )
                isprime[j] = false ;
        isprime[2] = true ;
        int k = 0;
        for ( int i = 0; i < MAXB; ++i )
            if ( isprime[i] ) ++k;
        p = new long[k];
        k = 0;
        for ( int i = 0; i < MAXB; ++i )
            if ( isprime[i] ) p[k++] = i;
    }

    void go() throws Exception {
        int i,j,k,limit;
        long P = 0, M, ans;
        double LM, LP;
        while ( scan.hasNext() ) {
            n = scan.nextLong();
            B = scan.nextInt();
            if ( n == 0 && B == 0 ) break ;
            for ( i = 0; i < p.length && p[i]*p[i] <= B; ++i )
                if ( 0 == (B%p[i]) ) {
                    for ( j = 0; 0 == (B%p[i]); ++j, B /= p[i] );
                    assert j == 1;
                    P = p[i];
                }
            if ( B > 1 ) P = B;
            limit = (int)(Math.log(n)/Math.log(P))+1;
            for ( ans = 0, LM = LP = Math.log(M = P), j = 1; j <= limit; ++j, M *= P, LM += LP ) {
                long a = (n/M), b = (M*(a-1)+2*(1+n%M));
                if ( (a%2) == 0 )
                    ans += (a/2)*b;
                else ans += a*(b/2);
                if ( LM+LP > MAXL ) break ;
            }
            bw.write(ans+"\n");
        }
        bw.flush();
    }
}
