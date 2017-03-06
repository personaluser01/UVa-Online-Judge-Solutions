/*
 * 10961. Chasing After Don Giovanni
 * TOPIC: simulation, medium interview question
 * status: Accepted
 */

/**
 * Created by sj on 13/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private static final int N = 0x80, MAXW = (1000001);
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/10961/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/10961/src/out02.txt")));
        new Main().go();
    }

    int [][]x = new int[2][N], y = new int[2][N];
    int []m = new int[2], xx = new int[2], yy = new int[2], cur = new int[2], cx = new int[2], cy = new int[2];

    void move( int t ) {
        int fx = x[t][cur[t]+1]-cx[t], fy = y[t][cur[t]+1]-cy[t];
        assert fx == 0 || fy == 0;
        if ( fx > 0 )
            ++cx[t];
        else if ( fx < 0 )
            --cx[t];
        else if ( fy > 0 )
            ++cy[t];
        else --cy[t];
        if ( cx[t] == x[t][cur[t]+1] && cy[t] == y[t][cur[t]+1] )
            ++cur[t];
    }

    void go() throws Exception {
        int i,j,k,ts = scan.nextInt(),cs = 0;
        while ( ts-- > 0 ) {
            if ( ++cs > 1 ) bw.write("\n");
            for ( i = 0; i < 2; ++i ) {
                xx[i] = scan.nextInt();
                yy[i] = scan.nextInt();
            }
            for ( i = 0; i < 2; ++i ) {
                m[i] = scan.nextInt();
                cx[i] = x[i][0] = xx[i^1];
                cy[i] = y[i][0] = yy[i^1];
                for ( ++m[i], j = 1; j < m[i]; ++j ) {
                    x[i][j] = scan.nextInt();
                    y[i][j] = scan.nextInt();
                }
            }
            boolean safe = true ;
            for ( cur[0] = cur[1] = 0; cur[0] < m[0] && cur[1] < m[1]; ) {
                move(0);
                move(1);
                if ( cx[0] == cx[1] && cy[0] == cy[1] && !(cx[0] == x[0][m[0]-1] && cy[0] == y[0][m[0]-1]) ) {
                    safe = false ;
                    break ;
                }
                if ( cx[0] == x[0][m[0]-1] && cy[0] == y[0][m[0]-1] ) break ;
                if ( cx[1] == x[1][m[1]-1] && cy[1] == y[1][m[1]-1] ) break ;
            }
            bw.write(safe?"Yes\n":"No\n");
        }
        bw.flush();
    }
}

