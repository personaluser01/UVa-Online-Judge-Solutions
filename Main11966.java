/*
 * 11966. Galactic Bonding
 * TOPIC: dfs
 * status: Accepted
 */
import java.io.*;
import java.util.*;

/**
 * Created by sj on 06/01/17.
 */
public class Main11966 {

    private final static int N = 0x400;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);
    int n;
    double []x,y;
    double [][]d = new double[N][N];
    double D;
    boolean []seen;

    public static void main( String ... args ) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/11966/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/11966/src/out02.txt")));
        new Main11966().go();
    }
    static double dist( double a, double b, double c, double d ) {
        return Math.sqrt((a-c)*(a-c)+(b-d)*(b-d));
    }
    void dfs( int x ) {
        if ( seen[x] ) return ;
        seen[x] = true ;
        for ( int y = 0; y < n; ++y )
            if ( d[x][y] <= D )
                dfs(y);
    }
    void go() throws Exception {
        int ts = scan.nextInt(),i,j,k,cs = 0;
        for (;ts-->0; ) {
            n = scan.nextInt();
            D = scan.nextDouble();
            x = new double[n];
            y = new double[n];
            for ( i = 0; i < n; ++i ) {
                x[i] = scan.nextDouble();
                y[i] = scan.nextDouble();
            }
            for ( i = 0; i < n; ++i )
                for ( j = i+1; j < n; ++j )
                    d[j][i] = d[i][j] = dist(x[i],y[i],x[j],y[j]);
            seen = new boolean[n];
            for ( k = 0, i = 0; i < n; ++i )
                if ( !seen[i] ) {
                    dfs(i);
                    ++k;
                }
            bw.write("Case "+(++cs)+": "+k+"\n");
        }
        bw.flush();
    }
}

