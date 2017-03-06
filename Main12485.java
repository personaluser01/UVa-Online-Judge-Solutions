/*
 * 12485. Perfect Choir
 * TOPIC: sorting, bricks problem, greedy
 * status: Accepted
 */

/**
 * Created by sj on 12/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private static final int N = (10100);
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);
    int n;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12485/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12485/src/out02.txt")));
        new Main().go();
    }

    long total,T;
    int []c = new int[N];

    void go() throws Exception {
        int i,j,k,low,high,mid;
        long rounds;
        for ( ;scan.hasNext(); ) {
            c = new int[n = scan.nextInt()];
            for ( total = 0, i = 0; i < n; ++i )
                total += (c[i] = scan.nextInt());
            if ( 0 != (total%n) ) {
                bw.write("-1\n");
                continue ;
            }
            T = total/n;
            Arrays.sort(c);
            if ( c[n-1] == T ) {
                bw.write("1\n");
                continue ;
            }
            for ( low = 0, high = n-1; low+1<high; ) {
                mid = (low+high)/2;
                if ( c[mid] > T )
                    high = mid;
                else low = mid;
            }
            for ( rounds = 0, k = high; k < n; ++k )
                rounds += c[k]-T;
            bw.write(++rounds+"\n");
        }
        bw.flush();
    }
}
