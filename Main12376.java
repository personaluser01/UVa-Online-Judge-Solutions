/*
 * 12376.
 * TOPIC: trivial
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
    int m,n,yes;
    int []v = new int[100];
    int [][]g = new int[100][100];
    public static void main( String [] args ) throws Exception {
        new Main().go();
    }
    void go() throws Exception {
        int i,j,k,x,y,ts,cs = 0,w;
        Scanner scan = new Scanner(System.in);
        for ( ts = scan.nextInt(); ts-- > 0; ) {
            n = scan.nextInt();
            m = scan.nextInt();
            for ( i = 0; i < n; ++i )
                v[i] = scan.nextInt();
            ++yes;
            for ( k = 0; k < m; ++k ) {
                i = scan.nextInt();
                j = scan.nextInt();
                g[i][j] = yes;
            }
            for ( k = x = 0; ; x = j ) {
                k += v[x]; w = -1;
                for ( j = y = 0; y < n; ++y )
                    if ( g[x][y] == yes )
                        if ( v[y]> w ) {
                            w = v[y];
                            j = y;
                        }
                if ( w == -1 ) break ;
            }
            System.out.println("Case "+(++cs)+": "+k+" "+x);
        }
    }
};

