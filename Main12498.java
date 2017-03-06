/*
 * 12498. Ant's Shopping Mall
 * TOPIC: iteration, easy interview question
 * status: Accepted
 */

/**
 * Created by sj on 10/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private final static int N = 0x40, oo = (1<<29);
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    Scanner scan = new Scanner(System.in);
    int m,n;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12498/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12498/src/out02.txt")));
        new Main().go();
    }

    char [][]g;

    int f( final int x, final int y ) {
        if ( g[x][y] == '0' ) return 0;
        int nx,ny, ansLeft = +oo, ansRight = +oo;
        for ( nx = x, ny = y-1; ny >= 0 && g[nx][ny] == '1'; --ny );
        if ( ny >= 0 ) ansLeft = (y-ny);
        for ( nx = x, ny = y+1; ny < n && g[nx][ny] == '1'; ++ny );
        if ( ny < n ) ansRight = (ny-y);
        return Math.min(ansLeft,ansRight);
    }

    int minMoves( final int col ) {
        int i,ans = 0, t;
        for ( i = 0; i < m; ans += t, ++i )
            if ( (t = f(i,col)) == +oo )
                return +oo;
        return ans;
    }

    void go() throws Exception {
        int i,j,k,cs = 0,ts = scan.nextInt(),ans;
        while ( ts--> 0 ) {
            m = scan.nextInt();
            n = scan.nextInt();
            g = new char[m][];
            for ( i = 0; i < m; ++i )
                g[i] = scan.next().toCharArray();
            for ( ans = +oo, j = 0; j < n; ++j )
                ans = Math.min(ans,minMoves(j));
            bw.write("Case "+(++cs)+": "+(ans<+oo?ans:-1)+"\n");
        }
        bw.flush();
    }
}
