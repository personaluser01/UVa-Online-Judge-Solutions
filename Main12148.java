/*
 * 12148. Electricity
 * TOPIC: time, simulation, java.time.*, built-in libraries
 * status: Accepted
 */

/**
 * Created by sj on 03/02/17.
 */

import java.io.*;
import java.time.temporal.TemporalUnit;
import java.util.*;
import java.time.*;
import java.util.concurrent.TimeUnit;

public class Main {
    private final static int N = 0x400;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);
    int n;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12148/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12148/src/out02.txt")));
        new Main().go();
    }

    class Reading implements Comparable<Reading> {
        LocalDate d,next;
        int w;
        Reading() {};
        Reading( Scanner scan ) {
            int day = scan.nextInt(), month = scan.nextInt(), year = scan.nextInt();
            d = LocalDate.of(year,month,day);
            w = scan.nextInt();
            next = d.plusDays(1);
        }
        public boolean isConsecutive( Reading r ) {
            return next.equals(r.d);
        }
        @Override
        public int compareTo( Reading other ) {
            return d.compareTo(other.d);
        }
    }

    Reading []r;

    void go() throws Exception {
        int i,j,k,days;
        long weight;
        for ( ;scan.hasNext() && (n = scan.nextInt()) != 0; ) {
            for ( r = new Reading[n], i = 0; i < n; r[i++] = new Reading(scan) );
            Arrays.sort(r);
            for ( weight = 0, days = 0, i = 0; i < n; days += (j-i-1), i = j )
                for ( j = i+1; j < n && r[j-1].isConsecutive(r[j]); weight += r[j].w-r[j-1].w, ++j );
            bw.write(days+" "+weight+"\n");
        }
        bw.flush();
    }
}

