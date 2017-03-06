/*
 * 12515. Movie Police
 * TOPIC: easy interview question, hamming distance, brute force, branch-and-bound
 * status: Accepted
 */

/**
 * Created by sj on 10/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private final static int oo = (1<<29);
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    Scanner scan = new Scanner(System.in);

    int n;
    char [][]g;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12515/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12515/src/out02.txt")));
        new Main().go();
    }

    int g( final char []c, int row, int est ) {
        int i,j,k,len = c.length,t,l,best = est;
        for ( i = 0; (j = i+len-1) < g[row].length; ++i ) {
            for ( t = 0, k = i; k <= j && t < best; ++k )
                t += (c[k-i] == g[row][k]?0:1);
            best = Math.min(best,t);
        }
        return best;
    }

    int f( final char []c ) {
        int ans = +oo, i,j,k,h,idx = -1;
        for ( i = 0; i < n; ++i ) {
            h = g(c,i,ans);
            if ( h < ans ) { idx = i; ans = h; }
        }
        return (idx+1);
    }

    void go() throws Exception {
        int i,j,k,qr;
        n = scan.nextInt();
        qr = scan.nextInt();
        g = new char[n][];
        for ( i = 0; i < n; ++i )
            g[i] = scan.next().toCharArray();
        for ( ;qr-->0; bw.write(f(scan.next().toCharArray())+"\n") );
        bw.flush();
    }
}
