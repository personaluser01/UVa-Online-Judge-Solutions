/*
 * 1595. Symmetry
 * TOPIC: counting, good interview question, symmetry
 * status: Accepted
 */

/**
 * Created by sj on 26/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    final static int N = 0x400;
    int n;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/1595/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/1595/src/out02.txt")));
        new Main().go();
    }

    int []x = new int[N], y = new int[N];
    Map<Integer,Integer> mp,cnt;

    class Pair implements Comparable<Pair> {
        final int x,y;
        Pair( int x, int y ) {
            this.x = x;
            this.y = y;
        }
        @Override
        public int compareTo( Pair other ) {
            if ( this.x == other.x )
                return this.y-other.y;
            return this.x-other.x;
        }
    }

    Set<Pair> s = new TreeSet<>();

    void go() throws Exception {
        int i,j,k;
        int mid;
        for ( int ts = scan.nextInt(); ts-->0; ) {
            s.clear();
            n = scan.nextInt();
            cnt = new HashMap<>();
            for ( i = 0; i < n; ++i ) {
                x[i] = scan.nextInt()*2;
                y[i] = scan.nextInt();
                s.add(new Pair(x[i],y[i]));
            }
            n = 0;
            for ( Pair p: s ) {
                x[n] = p.x;
                y[n++] = p.y;
            }
            for ( i = 0; i < n; ++i ) {
                if (cnt.containsKey(x[i])) {
                    k = cnt.get(x[i]);
                    cnt.put(x[i], k + 1);
                }
                else cnt.put(x[i], 1);
            }
            mp = new HashMap<>();
            for ( i = 0; i < n; ++i )
                for ( j = i+1; j < n; ++j )
                    if ( y[i] == y[j] ) {
                        if ( x[i] == x[j] ) {
                            // int trap = 1/0;
                        }
                        if (mp.containsKey(mid = (x[i] + x[j]) / 2)) {
                            k = mp.get(mid);
                            mp.put(mid, k + 2);
                        }
                        else
                            mp.put(mid, 2);
                    }
            for ( Map.Entry<Integer,Integer> entry: cnt.entrySet() )
                if ( mp.containsKey(entry.getKey()) ) {
                    k = mp.get(entry.getKey());
                    mp.put(entry.getKey(), k + entry.getValue());
                }
                else mp.put(entry.getKey(),entry.getValue());
            boolean ok = false ;
            for ( Map.Entry<Integer,Integer> entry: mp.entrySet() )
                if ( entry.getValue() == n ) {
                    ok = true ;
                    break ;
                }
            bw.write(ok?"YES\n":"NO\n");
        }
        bw.flush();
    }
}
