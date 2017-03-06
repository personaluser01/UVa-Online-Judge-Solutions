/*
 * 11860. Document Analyzer
 * TOPIC: regex, text analyzing, good interview question, intervals, rolling
 * status: Accepted
 */

/**
 * Created by sj on 15/02/17.
 */

import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    private final static Pattern p = Pattern.compile("(^?|[^a-z]*)([a-z]+)($?|[^a-z])");
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/11860/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/11860/src/out02.txt")));
        new Main().go();
    }

    String []w = new String[100100];
    int []x = new int[100100];
    int n,sz,left,right;
    Map<String,Integer> m = new HashMap<>();

    void extract( String s ) {
        for ( Matcher m = p.matcher(s); m.find(); w[n++] = m.group(2) );
    }

    void go() throws Exception {
        int i,j,k,cs = 0,ts = Integer.parseInt(br.readLine());
        for ( String s; ts-- > 0; ) {
            bw.write("Document "+(++cs)+": ");
            for ( n = 0; (s = br.readLine()) != null && !s.equals("END"); extract(s) ) ;
            for ( m.clear(), i = 0; i < n; x[i] = m.get(w[i]), ++i )
                if (!m.containsKey(w[i]))
                    m.put(w[i], i);

            Map<Integer,Integer> cnt = new HashMap<>();
            for ( sz = m.size(), left = -n-1, right = n+1, i = j = 0, cnt.put(x[i],1); !(i==n || j==n); )
                if ( i <= j && cnt.size() == sz ) {
                    if (j - i < right - left || j - i == right - left && i < left) {
                        left = i;
                        right = j;
                    }
                    if ( cnt.get(x[i]) == 1 ) cnt.remove(x[i]);
                    else cnt.put(x[i],cnt.get(x[i])-1);
                    ++i;
                }
                else {
                    ++j;
                    if ( j == n ) continue ;
                    assert j < n;
                    if ( !cnt.containsKey(x[j]) )
                        cnt.put(x[j],1);
                    else cnt.put(x[j],cnt.get(x[j])+1);
                }
            bw.write((++left)+" "+(++right)+"\n");
        }
        bw.flush();
    }
}

