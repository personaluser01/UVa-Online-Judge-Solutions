/*
 * 12346. Water Gate Management
 * TOPIC: bitmasks, enumeration, brute force, smallest-set-bit, good interview question
 * status: Accepted
 */

/**
 * Created by sj on 12/02/17.
 */

import java.io.*;
import java.lang.reflect.Array;
import java.util.*;

public class Main {
    private final static int N = 20;
    private final static double tol = 1e-9;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Reader r = new InputStreamReader(System.in);

    int rd() throws Exception {
        int n = 0,ch;
        for (;(ch = r.read()) != -1 && !('0'<=(char)ch && (char)ch<='9'); );
        for ( n = ch-'0'; (ch = r.read()) != -1 && ('0'<=(char)ch && (char)ch<='9'); n = 10*n+ch-'0' );
        return n;
    }

    int []F = new int[N], C = new int[N];
    int n;
    long []sumOfCost = new long[1<<N], sumOfFlow = new long[1<<N];

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12346/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12346/src/out02.txt")));
        for ( int k = 0; k < N; ++k )
            which[1<<k] = k;
        new Main().go();
    }

    static int L( int k ) { return k&((~k)+1); }
    static int []which = new int[1<<N];

    class Pair implements Comparable<Pair> {
        final long cost, flow;
        final double kpd;
        Pair( long cost, long flow ) {
            this.cost = cost;
            this.flow = flow;
            this.kpd = ((flow+0.00)/cost);
        }
        @Override
        public int compareTo( Pair other ) {
            if ( Math.abs(kpd-other.kpd) < tol )
                return 0;
            return kpd>other.kpd?-1:1;
        }
    }

    Pair []p;
    long []pref,pc;

    void go() throws Exception {
        int i,j,k,qr,cs = 0,vol,t,good,bad,mid;
        long ans;
        for ( p = new Pair[n = rd()], i = 0; i < n; ++i ) {
            F[i] = rd();
            C[i] = rd();
        }
        for ( k = 1; k < (1<<n); ++k ) {
            sumOfCost[k] = sumOfCost[k&~L(k)]+C[which[L(k)]];
            sumOfFlow[k] = sumOfFlow[k&~L(k)]+F[which[L(k)]];
        }
        for ( qr = rd(); qr-->0; ) {
            vol = rd();
            t = rd();
            bw.write(String.format("Case %d: ",++cs));
            ans = (1L<<62);
            for ( k = 1; k < (1<<n); ++k )
                if ( sumOfFlow[k]*t >= vol )
                    ans = Math.min(ans, sumOfCost[k]);
            bw.write(ans==(1L<<62)?"IMPOSSIBLE\n":ans+"\n");
        }
        bw.flush();
    }
}

