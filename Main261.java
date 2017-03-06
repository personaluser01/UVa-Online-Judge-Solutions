/*
 * 261. The Window Property
 * TOPIC: hashing, rolling hash, modular inverse
 * status: Accepted
 */

/**
 * Created by sj on 20/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    String s;
    int n;
    static long a,b,d;
    private final static int MOD = (int)((1L<<31)-1L), P = 10007, Q = inv(P,MOD);

    static void extendedEuclid( long x, long y ) {
        long na,nb;
        if ( y == 0 ) {
            d = x; a = 1; b = 0;
            return ;
        }
        extendedEuclid(y,x%y);
        na = a; nb = b;
        a = nb; b = na-a*(x/y);
    }

    static int inv( long x, long y ) {
        extendedEuclid(x,y);
        while ( a < 0 ) a += y;
        return (int)(a%y);
    }

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/261/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/261/src/out02.txt")));
        new Main().go();
    }

    class Window {
        final int i,j,h;
        Window( int i, int j, int hash ) {
            assert hash >= 0;
            this.i = i;
            this.j = j;
            this.h = hash;
        }
        public String getS() {
            return s.substring(i,j);
        }
        @Override
        public int hashCode() {
            return h;
        }
        @Override
        public boolean equals( Object obj ) {
            if ( !(obj instanceof Window) )
                return false ;
            Window w = (Window)obj;
            return getS().equals(w.getS());
        }
    }

    int mypow( long x, int n ) {
        long ax = 1L;
        while ( n > 0 ) {
            if ( 1 == (n&1) ) {
                ax *= x;
                ax %= MOD;
                while ( ax < 0 ) ax += MOD;
            }
            x *= x;
            x %= MOD;
            while ( x < 0 ) x += MOD;
            n >>= 1;
        }
        while ( ax < 0 ) ax += MOD;
        return (int)(ax%MOD);
    }

    int offendingSymbol;
    Set<Window> bag = new HashSet<>();

    int hash( int i, int j ) {
        int h = 0;
        for ( int t = j; t >= i; --t ) {
            h = MULT(h,P);
            h = ADD(h,(int)s.charAt(t));
        }
        return h;
    }

    int ADD( int x, int y ) {
        long xx = x, yy = y;
        long res = ((xx+yy)%MOD);
        while ( res < 0 ) res += MOD;
        return (int)res;
    }

    int MULT( int x, int y ) {
        long xx = x, yy = y;
        long res = ((xx*yy)%MOD);
        while ( res < 0 ) res += MOD;
        return (int)res;
    }

    int SUB( int x, int y ) {
        long xx = x, yy = y;
        long res = (xx-yy)%MOD;
        while ( res < 0 ) res += MOD;
        return (int)res;
    }

    boolean check( final int k ) {
        int deg = mypow(P,k-1), h = hash(0,k-1);
        bag.clear();
        bag.add(new Window(0,k-1,h));
        for ( int i=1,j; (j=i+k-1) < n; ++i ) {
            h = ADD(MULT(SUB(h,(int)s.charAt(i-1)),Q),MULT(deg,((int)s.charAt(j))));
            bag.add(new Window(i,j,h));
            if ( bag.size() > k+1 ) {
                offendingSymbol = Math.min(j,offendingSymbol);
                return false ;
            }
        }
        return true ;
    }

    void go() throws Exception {
        int i,j,k;
        boolean ok;
        while ( (s = br.readLine()) != null ) {
            n = s.length(); offendingSymbol = n+1;
            for ( ok = true, k = 1; k <= n; ++k )
                ok &= check(k);
            if ( ok )
                bw.write("YES\n");
            else bw.write("NO:"+(++offendingSymbol)+"\n");
        }
        bw.flush();
    }
}

