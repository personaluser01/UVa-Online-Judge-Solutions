/*
 * 618. doing Windows
 * TOPIC: ad hoc, gcd, maths, neat backtracking, very neat, elegant, felix_halim
 * status: Accepted
 */

/**
 * Created by sj on 13/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private static int []who = new int[1<<10];
    static int L( int x ) {
        return ((~x)+1)&(x);
    }
    static {
        for ( int i = 0; i < 10; who[1<<i] = i, ++i );
    }
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    Scanner scan = new Scanner(System.in);

    long []x = new long[5], y = new long[5], s = new long[5];

    static long gcd( long x, long y ) {
        if ( y == 0 ) return x ;
        return gcd(y,x%y);
    }

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/618/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/618/src/out02.txt")));
        new Main().go();
    }

    boolean perfectSquare( long x ) {
        long sqr = (long)(Math.sqrt((double)x)+1e-9);
        return sqr*sqr == x;
    }

    boolean canBeCovered() {
        long []k = new long[5], w = new long[5];
        for ( k[1] = 1; (w[1] = k[1]*k[1]*s[1]) <= s[0]; ++k[1] )
            for ( k[2] = 1; (w[2] = k[2]*k[2]*s[2]) <= s[0]-w[1]; ++k[2] )
                for ( k[3] = 1; (w[3] = k[3]*k[3]*s[3]) <= s[0]-w[1]-w[2]; ++k[3] ) {
                    long t = s[0]-w[1]-w[2]-w[3];
                    if ( 0 != (t%s[4]) ) continue ;
                    if ( perfectSquare(t/s[4]) )
                        return true ;
                }
        return false ;
    }

    boolean rec( int used, long R, long C ) {
        int i;
        if ( R < 0 || C < 0 ) return false ;
        if ( R == 0 || C == 0 )
            return used == 0xf;
        for ( int a = ((~used)&0xf); a > 0 && (i = who[L(a)]+1) >= 1; a &= ~L(a) ) {
            if ( 0 == (C%y[i]) ) {
                if ( rec(used|(1<<(i-1)), R-C/y[i]*x[i],C) )
                    return true ;
            }
            if ( 0 == (R%x[i]) ) {
                if ( rec(used|(1<<(i-1)), R,C-R/x[i]*y[i]) )
                    return true ;
            }
        }
        if ( used == 0 ) {
            for ( long k = 1; k*x[1] <= R && k*y[1] <= C; ++k ) {
                for ( int j = 2; j <= 4; ++j ) {
                    if ( ((k*x[1])%x[j]) == 0 && (k*x[1]/x[j])*y[j]+k*y[1] == C ) {
                        if ( rec(used|(1<<0)|(1<<(j-1)), R-k*x[1],C) )
                            return true ;
                    }
                    if ( ((k*y[1])%y[j]) == 0 && (k*y[1]/y[j])*x[j]+k*x[1] == R ) {
                        if ( rec(used|(1<<0)|(1<<(j-1)), R, C-k*y[1]) )
                            return true ;
                    }
                }
            }
        }
        return false ;
    }

    void go() throws Exception {
        int i,cs = 0;
        for (;;) {
            x[0] = scan.nextLong();
            y[0] = scan.nextLong();
            if ( x[0] == 0 && y[0] == 0 ) break ;
            for ( i = 1; i <= 4; ++i ) {
                x[i] = scan.nextLong();
                y[i] = scan.nextLong();
                long g = gcd(x[i],y[i]);
                x[i] /= g;
                y[i] /= g;
            }
            for ( i = 0; i <= 4; ++i ) s[i] = x[i]*y[i];
            bw.write("Set "+(++cs)+": ");
            if ( !canBeCovered() ) {
                bw.write("No\n");
                continue ;
            }
            if ( !rec(0,x[0],y[0]) )
                bw.write("No\n");
            else bw.write("Yes\n");
        }
        bw.flush();
    }
}

