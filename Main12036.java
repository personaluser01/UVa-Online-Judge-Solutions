/*
 * 12036. Stable Grid
 * TOPIC: ad hoc, medium, invariant
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
    int N = 0x80,n;
    int []cnt = new int[N];
    int [][]c = new int[N][N];
    public static void main ( String [] args ) throws Exception {
        new Main().go();
    }
    boolean cntTest() {
        for ( int i = 0; i < N; ++i )
            if ( cnt[i] > n )
                return false;
        return true;
    }
    void go() throws Exception {
        int i,j,k,ts,cs = 0;
        Scanner scan = new Scanner(System.in);
        for ( ts = scan.nextInt(); ts-- > 0 && (n = scan.nextInt()) > 0; ) {
            for ( i = 0; i < N; cnt[i++] = 0 );
            for ( i = 0; i < n; ++i )
                for ( j = 0; j < n; ++j )
                    ++cnt[c[i][j] = scan.nextInt()];
            System.out.print("Case "+(++cs)+": ");
            if ( !cntTest() ) {
                System.out.println("no");
                continue ;
            }
            System.out.println("yes");
        }
    }
};

