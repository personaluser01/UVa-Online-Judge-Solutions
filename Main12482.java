/*
 * 12482. Short Story Competition
 * TOPIC: greedy, prefix sums, binary search
 * status: Accepted
 */

/**
 * Created by sj on 01/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private final static int N = 0x400;
    int n,L,C;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    String []s;
    int []pref;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12482/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12482/src/out02.txt")));
        new Main().go();
    }

    int getNext( int idx ) {
        int good,bad,mid;
        idx = idx;
        if ( pref[n]-pref[idx-1]+(n-idx) <= C )
            return n;
        assert pref[idx]-pref[idx-1] <= C;
        for ( bad = n, good = idx; good+1<bad; ) {
            mid = (good+bad)/2;
            if ( pref[mid]-pref[idx-1]+(mid-idx) <= C )
                good = mid;
            else bad = mid;
        }
        good = good;
        int kk = pref[good]-pref[idx-1]+(good-idx);
        kk = kk;
        return good;
    }

    void go() throws Exception {
        int i,j,k,t;
        for ( String buff; (buff = br.readLine()) != null; ) {
            Scanner scan = new Scanner(buff);
            n = scan.nextInt();
            L = scan.nextInt();
            C = scan.nextInt();
            s = (br.readLine()).replaceFirst("^\\s+","").split("\\s+");
            assert s.length == n;
            pref = new int[n+1];
            for ( i = 0; i < n; ++i )
                pref[i+1] = pref[i]+s[i].length();
            for ( t = 0, k = 0, i = 1; k < n; j = getNext(i), k += (j-i+1), i = j+1, ++t ) ;
            bw.write( ((int)Math.ceil((t+0.0)/L))+"\n");
        }
        bw.flush();
    }
}
