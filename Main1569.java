/*
 * 1569. Multiple
 * TOPIC: neat bfs
 * status: Accepted
 */

/**
 * Created by sj on 04/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private final static int N = 5010;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);
    int []parent = new int[N], move = new int[N];

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/1569/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/1569/src/out02.txt")));
        new Main().go();
    }

    void dump( int x ) throws Exception {
        if ( parent[x] != -1 )
            dump(parent[x]);
        bw.write(move[x]+"");
    }

    void go() throws Exception {
        int i,j,k,n,m;
        Set<Integer> digs = new HashSet<>();
        for ( ;scan.hasNextInt(); ) {
            n = scan.nextInt();
            m = scan.nextInt();
            for ( digs.clear(), i = 0; i < m; ++i )
                digs.add(scan.nextInt());
            if ( n == 0 ) {
                bw.write("0\n");
                continue ;
            }
            Integer[]d = new Integer[digs.size()];
            digs.toArray(d);
            Queue<Integer> q = new LinkedList<>();
            boolean []seen = new boolean[n+1];
            for ( i = 0; i < d.length; ++i )
                if ( d[i] != 0 && !seen[k = d[i]%n] ) {
                    move[k] = d[i];
                    parent[k] = -1;
                    q.add(k);
                    seen[k] = true ;
                }
            while ( !q.isEmpty() )
                for ( i = q.poll(), k = 0; k < d.length; ++k )
                    if ( !seen[j = (10*i+d[k])%n] ) {
                        seen[j] = true ;
                        parent[j] = i;
                        move[j] = d[k];
                        q.add(j);
                    }
            if ( !seen[0] ) {
                bw.write("0\n");
                continue ;
            }
            dump(0);
            bw.write("\n");
        }
        bw.flush();
    }
}
