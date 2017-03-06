/*
 * 11140. Little Ali's Little Brother
 * TOPIC: bitmasks, bitwise xor, excellent interview question
 * status: Accepted
 */

/**
 * Created by sj on 13/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/11140/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/11140/src/out02.txt")));
        new Main().go();
    }

    int m,n,s,mm,nn;
    int []len;
    long []board,g;

    boolean canBePlaced( int x, int y ) {
        int i = x, k = 0;
        assert len[mm-1] >= 1;
        for ( ;k < mm && g[k] == 0; ++k );
        if ( k == mm ) return true ;
        for ( i = x; i < m && k < mm; ++i, ++k ) {
            if ( y+len[k] > n ) return false ;
            if ( g[k] == 0 ) continue ;
            if ( (((board[i]>>y)^g[k])&g[k]) != g[k] )
                return false ;
        }
        return k == mm;
    }

    static int []which = new int[1<<20];
    static long LSB( long k ) { return k & ((~k)+1); }
    static {
        for ( int k = 0; k < 20; ++k )
            which[1<<k] = k;
    }
    static int who( long k ) {
        if ( k < (1<<20) )
            return which[(int)k];
        if ( k < (1L<<40) )
            return 20+which[(int)(k>>20)];
        if ( k < (1L<<60) )
            return 40+which[(int)(k>>40)];
        return 60+which[(int)(k>>60)];
    }

    boolean fit() {
        int i,j,k;
        len = new int[mm];
        for ( i = 0; i < mm; ++i ) {
            for ( len[i] = nn-1; len[i] >= 0 && 0 == (g[i]&(1L<<len[i])); --len[i] );
            ++len[i];
        }
        for ( ;mm >= 1 && len[mm-1] == 0; --mm );
        if ( mm == 0 ) return true ;
        k = 1<<29;
        for ( i = 0; i < mm; ++i ) {
            if ( g[i] == 0 ) continue ;
            k = Math.min(k,who(LSB(g[i])));
        }
        for ( i = 0; i < mm; ++i ) {
            if ( g[i] == 0 ) continue ;
            g[i] >>= k;
            len[i] -= k;
        }
        for ( i = 0; i < m; ++i )
            for ( j = 0; j < n; ++j )
                if ( canBePlaced(i,j) )
                    return true ;
        return false ;
    }

    void go() throws Exception {
        int i,j,ts = scan.nextInt();
        String t;
        for ( ;ts-->0; bw.write("\n") ) {
            m = scan.nextInt();
            n = scan.nextInt();
            s = scan.nextInt();
            board = new long[m];
            for ( i = 0; i < m; ++i )
                for ( t = scan.next(), j = 0; j < n; ++j )
                    if ( t.charAt(j) == '.' )
                        board[i] |= (1L<<j);
            for ( int l = 0; l < s; ++l ) {
                mm = scan.nextInt();
                nn = scan.nextInt();
                g = new long[mm];
                for ( i = 0; i < mm; ++i )
                    for ( t = scan.next(), j = 0; j < nn; ++j )
                        if ( t.charAt(j) == '*' )
                            g[i] |= (1L<<j);
                bw.write(fit()?"Yes\n":"No\n");
            }
        }
        bw.flush();
    }
}
