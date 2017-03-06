/*
 * 13059. Tennis Championship
 * TOPIC: ad hoc, easy, recurrence
 * status: Accepted
 */

/**
 * Created by sj on 20/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/13059/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/13059/src/out02.txt")));
        new Main().go();
    }

    long f( long n ) {
        return n==1?0:(n>>1)+f((n>>1)+(n&1));
    }

    void go() throws Exception {
        long n;
        for ( String s; (s = br.readLine()) != null && (n = Long.parseLong(s)) >= 0; bw.write(f(n)+"\n") );
        bw.flush();
    }
}
