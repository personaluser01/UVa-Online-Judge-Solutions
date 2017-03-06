/*
 * 947. Mastermind Hints
 * TOPIC: ad hoc, greedy
 * status: Accepted
 */

/**
 * Created by sj on 28/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    int N = 5, n;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);
    int []c,code;
    int ans;
    int B( int k ) { return 1<<k; }
    int MASK( int k ) { return B(k)-1; }
    int L( int k ) { return k&((~k)+1); }

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/947/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/947/src/out02.txt")));
        new Main().go();
    }

    boolean consistent( final int k, final int m, int []code ) {
        int kk = 0, mm = 0, i,j;
        int []u = new int[9], v = new int[9];
        for ( i = 0; i < n; ++i )
            if ( code[i] == c[i] ) {
                if (++kk > k) return false;
            }
            else {
                ++u[code[i]];
                ++v[c[i]];
            }
        for ( i = 0; i < 9; ++i )
            mm += Math.min(u[i],v[i]);
        return kk == k && mm == m;
    }

    void generate( final int k, final int m, int cur, int kSoFar ) {
        if ( cur == n ) {
            if ( consistent(k,m,code) )
                ++ans ;
            return ;
        }
        for ( int i = 0; i < 9; ++i ) {
            code[cur] = i;
            if ( c[cur] == code[cur] && 1+kSoFar > k ) continue ;
            generate(k,m,cur+1,kSoFar+(c[cur]==code[cur]?1:0));
        }
    }

    void go() throws Exception {
        int i,j,k,ts = scan.nextInt();
        String s;
        while ( ts-->0 ) {
            s = scan.next();
            n = s.length();
            c = new int[n];
            code = new int[n];
            for ( i = 0; i < n; ++i ) c[i] = s.charAt(i)-'1';
            i = scan.nextInt();
            j = scan.nextInt();
            ans = 0; generate(i,j,0,0);
            bw.write(ans+"\n");
        }
        bw.flush();
    }
}

