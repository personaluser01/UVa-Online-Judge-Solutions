/*
 * 12563. Jin Ge Jin Qu hao
 * TOPIC: dp, knapsack, binary search
 * status: Accepted
 */

/**
 * Created by sj on 16/02/17.
 */

import java.io.*;
import java.util.*;

import static java.lang.Long.bitCount;
import static java.lang.Long.max;
import static java.lang.Long.sum;

public class Main {
    private final static long oo = (1L<<62);
    private final static int MAXN = 50, MAXS = MAXN*3*60;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);
    int n,t,m;
    int []c,pref;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12563/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12563/src/out02.txt")));
        new Main().go();
    }

    boolean canFit( int k ) {
        if ( k == 0 ) return t > 0;
        assert k >= 1;
        return pref[k-1] < t;
    }

    long [][]z;

    long calcZ( int i, int k ) {

        if ( z[i][k] < +oo )
            return z[i][k];
        if ( k == 0 )
            return z[i][k] = 0;
        assert k >= 1;
        if ( i == 0 )
            return z[i][k] = +oo;
        if ( pref[i-1] < k )
            return z[i][k] = +oo;
        if ( pref[i-1] == k )
            return z[i][k] = i;

        assert k >= 1 ;
        assert pref[i-1] > k;
        if ( calcZ(i-1,k) < +oo )
            z[i][k] = calcZ(i-1,k);
        if ( c[i-1] <= k && calcZ(i-1,k-c[i-1]) < +oo )
            if ( z[i][k] == +oo || 1+calcZ(i-1,k-c[i-1]) > z[i][k] )
                z[i][k] = 1+calcZ(i-1,k-c[i-1]);
        return z[i][k];
    }

    void go() throws Exception {
        int i,j,k, cs = 0, ts = scan.nextInt(),T,good,bad,mid,sumOfT;
        for (;ts-->0;) {
            c = new int[n = scan.nextInt()];
            pref = new int[n+1];
            t = scan.nextInt();
            bw.write("Case "+(++cs)+": ");
            for ( sumOfT = 0, i = 0; i < n; sumOfT += (c[i++] = scan.nextInt()) );
            Arrays.sort(c);
            for ( i = 0; i < n; ++i )
                pref[i] = (i==0?c[i]:pref[i-1]+c[i]);
            pref[n] = pref[n-1]+678;
            for ( good = 0, bad = n+1; good+1<bad; )
                if ( canFit(mid = (good+bad)/2) )
                    good = mid;
                else bad = mid;
            m = good;
            sumOfT = Math.min(t-1,sumOfT);
            z = new long[n+1][sumOfT+1];
            for ( i = 0; i <= n; ++i )
                for ( k = 0; k <= sumOfT; ++k )
                    z[i][k] = +oo;
            for ( k = sumOfT; k >= 0 && (calcZ(n,k) == +oo || calcZ(n,k) < (long)m); --k ) ;
            z[n][sumOfT] = z[n][sumOfT];
            bw.write((m+1)+" "+(k+678)+"\n");
        }
        bw.flush();
    }
}

