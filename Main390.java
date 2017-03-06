/*
 * 390. Letter Sequence Analysis
 * TOPIC: ad hoc, output formatting
 * status: Accepted
 */

/**
 * Created by sj on 10/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {

    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    Map<Integer,Map<String,Integer>> m = new TreeMap<>();
    Map<Integer,Map<Integer,Set<String>>> q = new TreeMap<>();

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/390/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/390/src/out02.txt")));
        new Main().go();
    }

    void ins( char []c ) {
        int n = c.length;
        for ( int i = 0; i < n; ++i )
            if ( !Character.isAlphabetic(c[i]) )
                return ;
        String s = new String(c).toUpperCase();
        if ( !m.containsKey(n) )
            m.put(n,new TreeMap<>());
        if ( m.get(n).containsKey(s) )
            m.get(n).put(s,m.get(n).get(s)+1);
        else m.get(n).put(s,1);
    }

    void process( String s ) {
        char []c = s.toCharArray();
        int i,j,ws,n = s.length();
        for ( ws = 1; ws <= 5; ++ws )
            for ( i = 0; (j=i+ws-1) < n; ++i )
                ins(Arrays.copyOfRange(c,i,j+1));
    }

    void go() throws Exception {
        int ts = 0,i,j,k,freq;
        for ( String s,t; (s = br.readLine()) != null; )
            for ( Scanner scan = new Scanner(s); scan.hasNext(); process(scan.next()) );
        for ( k = 1; k <= 5; ++k )
            q.put(k,new TreeMap<>(Collections.reverseOrder()));
        for ( Map.Entry<Integer,Map<String,Integer>> entry: m.entrySet() ) {
            k = entry.getKey();
            for ( Map.Entry<String,Integer> e: entry.getValue().entrySet() ) {
                freq = e.getValue();
                if ( q.get(k).containsKey(freq) )
                    q.get(k).get(freq).add(e.getKey());
                else {
                    q.get(k).put(freq,new TreeSet<>());
                    q.get(k).get(freq).add(e.getKey());
                }
            }
        }
        for ( Map.Entry<Integer,Map<Integer,Set<String>>> entry: q.entrySet() ) {
            k = entry.getKey();
            if ( ++ts > 1 ) bw.write("\n");
            bw.write("Analysis for Letter Sequences of Length "+k+"\n");
            bw.write("-----------------------------------------\n");
            i = 0;
            for ( Map.Entry<Integer,Set<String>> e: entry.getValue().entrySet() ) {
                bw.write("Frequency = "+e.getKey()+", Sequence(s) = (");
                j = 0;
                for ( String x: e.getValue() )
                    bw.write(((++j>1)?",":"")+x);
                bw.write(")\n");
                if ( ++i == 5 ) break ;
            }
        }
        bw.flush();
    }
}
