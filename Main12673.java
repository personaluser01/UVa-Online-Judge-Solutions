/*
 * 12673. Football
 * TOPIC: greedy, sorting, excellent interview question
 * status: Accepted
 */

/**
 * Created by sj on 01/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    Scanner scan = new Scanner(System.in);
    int n,g,m;
    int []d;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12673/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12673/src/out02.txt")));
        new Main().go();
    }

    void go() throws Exception {
        int i,j,k,score;
        while ( scan.hasNext() ) {
            m = n = scan.nextInt();
            g = scan.nextInt();
            d = new int[n];
            for ( i = 0; i < n; ++i ) {
                j = scan.nextInt();
                k = scan.nextInt();
                d[i] = j-k;
            }
            Arrays.sort(d);
            for ( score = 0; n >= 1 && d[n-1] > 0; --n, score += 3 );
            if ( n == 0 ) {
                bw.write(score+"\n");
                continue ;
            }
            assert n >= 1 && d[n-1] <= 0;
            for ( k = g, i = n-1; i >= 0 && k >= 0; --i )
                if ( -d[i]+1 <= k ) {
                    k -= (-d[i]+1);
                    score += 3;
                }
                else if ( -d[i] <= k ) {
                    k -= (-d[i]);
                    score += 1;
                }
            bw.write(score+"\n");
        }
        bw.flush();
    }
}
