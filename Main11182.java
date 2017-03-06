/*
 * 11182. Zeroes III
 * TOPIC: factorials, primes, maths, neat, number bases, best-so-far
 * status: Accepted
 */

/**
 * Created by sj on 06/02/17.
 */

import javax.swing.*;
import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class Main {
    private final static int MAXB = 10000;
    private final static double L = Math.log(BigInteger.valueOf(1L<<62).multiply(BigInteger.valueOf(2)).subtract(BigInteger.ONE).doubleValue());
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/11182/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/11182/src/out02.txt")));
        new Main().go();
    }

    static boolean []isprime = new boolean[MAXB];
    static long []p;

    static {
        int i,j,k;
        for ( isprime[2] = true, i = 3; i < MAXB; isprime[i] = true, i += 2 );
        for ( i = 3; i < MAXB; i += 2 )
            for ( j = i+i; j < MAXB && isprime[i]; isprime[j] = false, j += i );
        for ( k = 0, i = 0; i < MAXB; ++i )
            if ( isprime[i] ) ++k;
        p = new long[k];
        for ( k = 0, i = 0; i < MAXB; ++i )
            if ( isprime[i] )
                p[k++] = i;
    }

    long n,B,P,PPOW;
    double LM, LP;

    long SQ( long L ) {
        BigInteger a = BigInteger.valueOf(L), b = BigInteger.valueOf(L+1), c = BigInteger.valueOf(2*L+1);
        return a.multiply(b).multiply(c).divide(BigInteger.valueOf(6)).longValue();
    }

    long F( long x ) {
        long y = x+1;
        if ( 0 == (x%2) )
            return (x/2)*y;
        return (y/2)*x;
    }

    BigInteger bigSQ( long L ) {
        BigInteger a = BigInteger.valueOf(L), b = BigInteger.valueOf(L+1), c = BigInteger.valueOf(2*L+1);
        return a.multiply(b).multiply(c).divide(BigInteger.valueOf(6));
    }

    class Pair {
        long prime;
        int power;
        Pair( long x, int p ) {
            prime = x;
            power = p;
        }
    }

    List<Pair> lst = new ArrayList<>();

    void go() throws Exception {
        int i,j,k,limit,deg;
        long ax,M,ans;
        while ( scan.hasNext() ) {
            n = scan.nextLong();
            B = scan.nextLong();
            if ( n == 0 && B == 0 )
                break ;
            for ( lst.clear(), P = 1L, deg = -1, PPOW = 0, i = 0; i < p.length && p[i]*p[i] <= B; ++i )
                if ( 0 == (B%p[i]) ) {
                    for ( ax = 1L, j = 0; 0 == (B%p[i]); ++j, B /= p[i], ax *= p[i] ) ;
                    lst.add(new Pair(p[i],j));
                }
            if ( B > 1 )
                lst.add(new Pair(B,1));
            BigInteger res = null;
            for ( Pair w: lst ) {
                P = w.prime;
                deg = w.power;
                limit = (int) (Math.log(n) / Math.log(P)) + 1;
                BigInteger acc = BigInteger.valueOf(0);
                for (ans = 0, LM = LP = Math.log(M = P), j = 1; j <= limit; ++j, LM += LP, M *= P) {
                    long q = n / M, r = (n % M);
                    BigInteger BM = BigInteger.valueOf(M);
                    acc = acc.add(BigInteger.valueOf(F(q - 1)).multiply(BM).multiply(BigInteger.valueOf(2 * n + 3 - M)).divide(BigInteger.valueOf(2)));
                    acc = acc.subtract(BM.multiply(BM).multiply(bigSQ(q - 1)));
                    acc = acc.add(BigInteger.valueOf(F(r + 1)).multiply(BigInteger.valueOf(q)));
                    ans += M * F(q - 1) * (2 * n + 3 - M) / 2 - M * M * SQ(q - 1) + q * F(r + 1);
                    //if ( LM+LP > L ) break ;
                }
                acc = acc.divide(BigInteger.valueOf(deg));
                ans /= deg;
                if ( res == null || res.compareTo(acc) > 0 ) res = acc;
            }
            //bw.write(ans+"\n");
            bw.write(res+"\n");
        }
        bw.flush();
    }
}

