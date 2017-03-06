/*
 * 268. Double Trouble
 * TOPIC: ad hoc, maths, bases, neat for interview
 * status: Accepted
 */

/**
 * Created by sj on 19/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    static Integer []generator( final int B, int lastDig ) {
        int d,carry = 0,x;
        Deque<Integer> q = new LinkedList<>();
        for ( q.add(d=lastDig), x=(2*d)%B, carry=(2*d)/B; !(x==lastDig&&carry==0); q.addFirst(x), d=(2*x+carry)%B, carry=(2*x+carry)/B, x=d );
        Integer[]res = new Integer[q.size()];
        ((LinkedList<Integer>)q).toArray(res);
        return res;
    }

    static class Comp implements Comparator<Integer[]> {
        @Override
        public int compare( Integer[] a, Integer []b ) {
            if ( a.length == b.length )
                for ( int i = 0; i < a.length; ++i )
                    if ( a[i].compareTo(b[i]) != 0 )
                        return a[i].compareTo(b[i]);
            return a.length<b.length?-1:1;
        }
    }

    Map<Integer,Integer[]> m = new TreeMap<>();

    public static void main(String... args) throws Exception {
        //System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/268/src/input.txt")));
        //System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/268/src/out02.txt")));
        new Main().go();
    }

    void display( Integer[] a )  throws Exception {
        int i,j = 0;
        for ( i = 0; i < a.length; ++i ) {
            //if ( ++j > 1 ) bw.write(" ");
            bw.write(a[i].toString()+" ");
        }
    }

    void go() throws Exception {
        Comp c = new Comp();
        for ( int B = 2; B < 200; ++B ) {
            Integer[] res = null, cand;
            for ( int d = 1; d <= B-1; ++d ) {
                cand = generator(B,d);
                if ( res == null || c.compare(res,cand) > 0 )
                    res = cand;
            }
            assert res != null;
            m.put(B,res);
        }
        for ( String s; (s = br.readLine()) != null; ) {
            int n = Integer.parseInt(s);
            bw.write(String.format("For base %d the double-trouble number is\n",n));
            display(m.get(n));
            bw.write("\n");
        }
        bw.flush();
    }
}
