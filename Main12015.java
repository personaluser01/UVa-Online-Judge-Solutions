/*
 * TOPIC: regex, trivial
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
    public static void main( String [] args ) throws Exception {
        new Main().go();
    }
    void go() throws Exception {
        int i,j,k,ts,cs = 0;
        Pattern p = Pattern.compile("([a-zA-Z\\.]+)\\s+(\\d+)");
        Matcher m;
        String []s = new String[10];
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int [] r = new int[10];
        for ( ts = Integer.parseInt(new StringTokenizer(br.readLine()).nextToken()); ts-- > 0; ) {
            for ( k = i = 0; i < 10; ++i ) {
                m = p.matcher(br.readLine());
                m.find();
                s[i] = m.group(1);
                r[i] = Integer.parseInt(m.group(2));
                if ( r[i] > k ) k = r[i];
            }
            System.out.println("Case #"+(++cs)+":");
            for ( i = 0; i < 10; ++i )
                if ( k == r[i] )
                    System.out.println(s[i]);
        }
    }
};

