/*
 * 11132. Dice From Pennies
 * TOPIC: probability, encoding, sliding window, binary
 * status: Accepted
 */

/**
 * Created by sj on 09/02/17.
 */

import java.io.*;
import java.util.*;
import java.util.regex.*;

public class Main {
    private final static Pattern p = Pattern.compile("(\\d+)D(\\d+)");
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/11132/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/11132/src/out02.txt")));
        new Main().go();
    }

    int m,n,len,K;
    char []c;
    int []a;

    void go() throws Exception {
        String s;
        int i,j,k,l;
        long res;
        for (;(s = br.readLine()) != null && !s.equals("0D0"); ) {
            Matcher matcher = p.matcher(s);
            matcher.find();
            m = Integer.parseInt(matcher.group(1));
            n = Integer.parseInt(matcher.group(2));
            len = (c = br.readLine().toCharArray()).length;
            a = new int[len];
            for ( i = 0; i < len; a[i] = c[i]=='H'?0:1, ++i );
            for ( K = 0; (1<<K) < n; ++K ) ;
            List<Long> lst = new ArrayList<>();
            for ( i = 0; i < len && lst.size() < m; i = k+1 ) {
                for ( res = 0, j = i, l = i; (k = j+K-1) < len && l <= k; ++l ) {
                    res <<= 1;
                    res += a[l];
                }
                if ( l == k+1 && res < n )
                    lst.add(res+1);
            }
            if ( lst.size() == m ) {
                for ( res = 0, i = 0; i < lst.size(); ++i )
                    res += lst.get(i);
            }
            else res = -1;
            bw.write(res+"\n");
        }
        bw.flush();
    }
}
