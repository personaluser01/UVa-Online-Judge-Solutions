/*
 * status: Accepted
 * TOPIC: regex
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
    public static void main ( String [] args ) throws Exception {
        new Main().go();
    }
    void go() throws Exception {
        StringTokenizer st;
        String s,ans = new String();
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        boolean done = false;
        Pattern p = Pattern.compile("([A-Za-z-]+)");
        int best_length = -1;

        while ( !done && (s = br.readLine()) != null ) {
            st = new StringTokenizer(s);
            while ( st.hasMoreTokens() ) {
                String t = st.nextToken();
                if ( t.equals("E-N-D") ) { done = true; break ; }
                Matcher m = p.matcher(t);
                while ( m.find() ) {
                    String h = m.group(1);
                    if ( h.length() > best_length ) {
                        best_length = h.length();
                        ans = h;
                    }
                }
            }
        }
        System.out.println(ans.toLowerCase());
    }
};

