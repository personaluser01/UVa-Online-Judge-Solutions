/*
 * 250. Pattern Matching Prelims
 * TOPIC: ad hoc
 * status: Accepted
 * NOTES: hmm, I thought x<=y is x+tol<=y for floating points, but it turns out it is x-tol<=y... interesting...
 */

/**
 * Created by sj on 20/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {

    final static int N = 32;
    final static double tol = 1e-11, oo = (1<<29);
    int m,n;
    double [][]g = new double[N][N], w = new double[N][N];
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    //BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    Scanner scan = new Scanner(System.in);

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/250/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/250/src/out02.txt")));
        new Main().go();
    }

    double sum( int i, int j, int k, int t ) {
        return w[k][t]-w[i-1][t]-w[k][j-1]+w[i-1][j-1];
    }

    void go() throws Exception {
        int i,j,k,cs = 0,ii = -1, jj = -1;
        double left,right,up,down,a,b,A,B;
        while ( true ) {
            m = scan.nextInt();
            n = scan.nextInt();
            if ( m == 0 && n == 0 ) break ;
            for ( i = 1; i <= m; ++i )
                for ( j = 1; j <= n; ++j )
                    g[i][j] = scan.nextDouble();
            for ( i = 1; i <= m; ++i )
                for ( j = 1; j <= n; ++j )
                    w[i][j] = w[i-1][j]+w[i][j-1]-w[i-1][j-1]+g[i][j];
            A = B = +oo;
            for ( i = m; i >= 1; --i )
                for ( j = n; j >= 1; --j ) {
                    left = sum(1,1,m,j-1);
                    right = sum(1,j+1,m,n);
                    up = sum(1,1,i-1,n);
                    down = sum(i+1,1,m,n);
                    a = Math.abs(up-down);
                    b = Math.abs(left-right);
                    if ( Math.abs(a-A) < tol && Math.abs(b-B) < tol ) continue ;
                    if ( a-tol <= A && b-tol <= B ) {
                        ii = i;
                        jj = j;
                        A = a;
                        B = b;
                    }
                }
            bw.write(String.format("Case %d: center at (%d, %d)\n",++cs,ii,jj));
        }
        bw.flush();
    }
}

