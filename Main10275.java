/*
 * 10275. Guess The Number!
 * TOPIC: big decimal, big integer, logarithms. binary search, estimates, maths
 * status: Accepted
 */

/**
 * Created by sj on 14/02/17.
 */

import java.io.*;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.*;
import static java.lang.Math.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/10275/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/10275/src/out02.txt")));
        new Main().go();
    }

    int dist( String x, String y ) {
        int k = 0;
        if ( x.length() != y.length() )
            return 2;
        for ( int i = 0; i < x.length() && i < y.length(); ++i )
            if ( x.charAt(i) != y.charAt(i) ) {
                if ( ++k >= 2 ) return k;
            }
        return k;
    }

    String find( String s, long h ) {
        int logS = s.length()-1,ans = 0,d;
        String res = "-1";
        List<Long> exact = new ArrayList<>(), approx = new ArrayList<>();
        for ( ;h*log10(h) < logS+1; ++h ) {
            BigInteger b = BigInteger.valueOf(h).pow((int)h);
            String t = b.toString();
            if ( (d = dist(s,t)) <= 1 ) {
                if ( d == 0 && ++ans > 1 ) return "-1";
                if ( d == 0 ) {
                    exact.add(h);
                    res = Long.toString(h);
                }
                if ( d == 1 ) approx.add(h);
            }
        }
        if ( exact.size() == 1 ) return res;
        return "-1";
    }

    void go() throws Exception {
        int i,j,k,ts = Integer.parseInt(br.readLine()),n;
        long low,high,mid;
        String s;
        for (;ts-->0; ) {
            n = (s = br.readLine()).length()-1;
            if ( n == 0 ) {
                bw.write(find(s,1)+"\n");
                continue ;
            }
            for ( low = 0, high = n+1; low+1<high; ) {
                mid = (low+high)/2;
                if ( mid*log10(mid) < n )
                    low = mid;
                else high = mid;
            }
            bw.write(find(s,high)+"\n");
        }
        bw.flush();
    }
}

