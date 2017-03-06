/*
 * 12662. Good Teacher
 * TOPIC: trivial dp, easy interview question
 * status: Accepted
 */

/**
 * Created by sj on 18/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private final static int N = (0x400);
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);
    String []c = new String[N];
    int []left = new int[N], right = new int[N];
    int n;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12662/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12662/src/out02.txt")));
        new Main().go();
    }

    void go() throws Exception {
        int i,j,k;
        for ( n = scan.nextInt(), i = 0; i < n; ++i )
            c[i] = scan.next();
        int oo = (1<<29);
        for (i = 0; i < n; ++i ) {
            if ( !c[i].equals("?") ) {
                left[i] = right[i] = i;
                continue ;
            }
            left[i] = (i>0?left[i-1]:-oo);
        }
        for ( i = n-1; i >= 0; --i ) {
            if ( !c[i].equals("?") )
                continue ;
            right[i] = (i+1<n?right[i+1]:+oo);
        }
        for ( int qr = scan.nextInt(); qr-->0; ) {
            k = scan.nextInt()-1;
            if ( left[k] == k ) {
                bw.write(c[k]+"\n") ;
                continue ;
            }
            if ( k-left[k] < right[k]-k ) {
                bw.write(f(left[k],k)+"\n");
                continue ;
            }
            if ( k-left[k] > right[k]-k ) {
                bw.write(g(k,right[k])+"\n");
                continue ;
            }
            bw.write(String.format("middle of %s and %s\n",c[left[k]],c[right[k]]));
        }
        bw.flush();
    }

    private String g(int k, int i ) {
        StringBuilder sb = new StringBuilder();
        for ( int t = i-k; t-->0; )
            sb.append("left of ");
        sb.append(c[i]);
        return sb.toString();
    }
    private String f(int i, int k ) {
        StringBuilder sb = new StringBuilder();
        for ( int t = k-i; t-->0; )
            sb.append("right of ");
        sb.append(c[i]);
        return sb.toString();
    }
}

