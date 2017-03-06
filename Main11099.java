/*
 * 11099. Next Same-Factored
 * TOPIC: prime factorization, sieve, constructive algorithms, brute force
 * status: Accepted
 */

/**
 * Created by sj on 06/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private final static int N = (1000000), M = (10000);
    int n;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);

    static boolean []isprime = new boolean[M];
    static long []p;
    static {
        for ( int i = 3; i < M; i +=2 )
            isprime[i] = true ;
        isprime[2] = true ;
        for ( int i = 3; i < M; i += 2 )
            for ( int j = i+i; j < M && isprime[i]; j += i )
                isprime[j] = false ;
        int k = 0;
        for ( int i = 0; i < M; ++i )
            if ( isprime[i] ) ++k;
        p = new long[k];
        k = 0;
        for ( int i = 0; i < M; ++i )
            if ( isprime[i] )
                p[k++] = i;
    }

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/11099/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/11099/src/out02.txt")));
        new Main().go();
    }

    long MASK( long k ) {
        return (1L<<k)-1L;
    }

    long []c = new long[N];
    int m;
    int []t, best;
    double []logs = new double[0x400];
    double minSum,limit;
    boolean []noExist = new boolean[N];

    void generate( int cur, double sum ) {
        if ( cur == m ) {
            if ( sum > 0 && (best == null || sum < minSum) && sum <= limit+1e-9 ) {
                minSum = sum;
                best = t.clone();
            }
            return ;
        }
        for ( t[cur] = (int)(1-(c[cur]>>30)); t[cur] <= (c[cur]>>30)+8; ++t[cur] )
            generate(cur+1,sum+logs[cur]*t[cur]);
    }

    long myPow( long x, long n ) {
        long ax = 1L;
        for (;n>0; n >>= 1, x *= x )
            if ( 1 == (n&1L) )
                ax *= x;
        return ax;
    }

    long []ans = new long[1000001];

    void go() throws Exception {
        int i,j,k;
        long ax;
        for ( ;scan.hasNextInt(); ) {
            n = scan.nextInt();
            if ( ans[n] != 0 ) {
                bw.write(ans[n]+"\n");
                continue ;
            }
            if ( noExist[n] ) {
                bw.write("Not Exist!\n");
                continue ;
            }
            for ( m = 0, k = n, i = 0; i < p.length && p[i]*p[i] <= k; ++i )
                if ( 0 == (k%p[i]) ) {
                    for ( j = 0; 0 == (k%p[i]); ++j, k /= p[i] ) ;
                    c[m++] = p[i]|(((long)j)<<30);
                    p[i] = p[i];
                }
            if ( k > 1 ) c[m++] = k|(1L<<30);
            for ( i = 0; i < m; ++i )
                logs[i] = Math.log(c[i]&MASK(30));
            best = null;
            t = new int[m];
            limit = Math.log(2000000.0)-Math.log(n);
            generate(0,0);
            if ( best != null ) {
                for (ax = 1L, i = 0; i < m; ++i)
                    ax *= myPow(c[i] & MASK(30), (c[i] >> 30) + best[i]);
                if ( ax < 2000000 )
                    ans[n] = ax;
                else {
                    best = null;
                    noExist[n] = true ;
                }
            }
            bw.write(best==null?"Not Exist!\n":ans[n]+"\n");
        }
        bw.flush();
    }
}

