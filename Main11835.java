/*
 * 11835. Formula I
 * TOPIC: ad hoc, sorting, easy
 * status: Accepted
 */

/**
 * Created by sj on 30/01/17.
 */

import java.io.*;
import java.lang.reflect.Array;
import java.util.*;

public class Main {
    private final static int N = (1<<8);
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/11835/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/11835/src/out02.txt")));
        new Main().go();
    }

    int m,n;
    int [][]arr = new int[N][N];

    class Pilot implements Comparable<Pilot> {
        final int id;
        int score;
        Pilot( int id ) { this.id = id; score = 0; }
        @Override
        public int compareTo( Pilot other ) {
            if ( score == other.score )
                return id-other.id;
            return -score+other.score;
        }
        void addPoints( int ds ) {
            score += ds;
        }
    }

    Pilot []p;

    List<Integer> determine( Pilot []p, int []s ) {
        int k = s.length,i,j;
        for ( i = 0; i < m; ++i )
            for ( j = 0; j < n; ++j )
                if ( arr[i][j] < k )
                    p[j].addPoints(s[arr[i][j]]);
        Arrays.sort(p);
        List<Integer> res = new ArrayList<>();
        res.add(p[0].id);
        for ( i = 1; i < n && p[i].score == p[0].score; ++i )
            res.add(p[i].id);
        return res;
    }

    void go() throws Exception {
        int i,j,k;
        for ( ;scan.hasNext(); ) {
            m = scan.nextInt();
            n = scan.nextInt();
            if ( m == 0 && n == 0 ) break ;
            for ( i = 0; i < m; ++i )
                for ( j = 0; j < n; ++j )
                    arr[i][j] = scan.nextInt()-1;
            for ( int qr = scan.nextInt(); qr-->0; ) {
                k = scan.nextInt();
                p = new Pilot[n];
                for ( i = 0; i < n; ++i )
                    p[i] = new Pilot(i);
                int []s = new int[k];
                for ( i = 0; i < k; ++i )
                    s[i] = scan.nextInt();
                List<Integer> lst = determine(p,s);
                for ( i = 0; i < lst.size(); ++i ) {
                    if ( i > 0 ) bw.write(" ");
                    bw.write((lst.get(i)+1)+"");
                }
                bw.write("\n");

            }
        }
        bw.flush();
    }
}
