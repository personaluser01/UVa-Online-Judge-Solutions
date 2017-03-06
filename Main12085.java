/*
 * 12085. Mobile Casanova
 * TOPIC: ad hoc, easy interview question
 * status: Accepted
 */

/**
 * Created by sj on 01/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private final static int N = (1<<17);
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    int n;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12085/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12085/src/out02.txt")));
        new Main().go();
    }

    int lcp( int x, int y ) {
        String a = Integer.toString(x), b = Integer.toString(y);
        for ( int i = 0; i < a.length(); ++i )
            if ( a.charAt(i) != b.charAt(i) )
                return i+1;
        return a.length();
    }
    String f( int i, int j ) {
        assert i <= j ;
        if ( i == j )
            return "0"+i+"";
        else return String.format("0%d-%s",i,Integer.toString(j).substring(lcp(i,j)-1));
    }

    void go() throws Exception {
        int i,j,k,left = 0,right = -2,cs = 0;
        String s;
        while ( (n = Integer.parseInt(br.readLine())) != 0 ) {
            bw.write("Case "+(++cs)+":\n");
            for ( left = 0, right = -1, i = 0; i < n; ++i ) {
                k = Integer.parseInt(br.readLine());
                if ( right+1 < k ) {
                    if ( left <= right )
                        bw.write(f(left,right)+"\n");
                    left = right = k;
                }
                else if ( right+1 == k ) ++right;
                else {
                    int trap = 1/0;
                }
            }
            if ( left <= right ) bw.write(f(left,right)+"\n");
            bw.write("\n");
        }
        bw.flush();
    }
}
