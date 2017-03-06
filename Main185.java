/*
 * 185. Roman Numerals
 * TOPIC: roman numerals, simulation, medium interview question
 * status: Accepted
 */

/**
 * Created by sj on 31/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static Map<Character,Integer> m = new HashMap<>();
    String digs;
    static int []which = new int[1<<11], D = {0,1,2,3,4,5,6,7,8,9};
    static int L( int k ) { return k&((~k)+1); }

    static {
        for ( int i = 0; i < 11; which[1<<i] = i, ++i );
    }

    public static void main( String... args ) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/185/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/185/src/out02.txt")));
        m.put('I',1);
        m.put('X',10);
        m.put('C',100);
        m.put('M',1000);
        m.put('V',5);
        m.put('L',50);
        m.put('D',500);
        new Main().go();
    }

    int convert( String s, Map<Character,Integer> mp ) {
        int n = 0;
        for ( int i = 0; i < s.length(); n = 10*n+mp.get(s.charAt(i++)) );
        return n;
    }

    int f( String s ) {
        int n = 0,i,j = 0,k;
        for (;j < s.length(); ++j ) {
            for ( k = j; j+1 < s.length() && m.get(s.charAt(j+1)) <= m.get(s.charAt(j)); ++j) ;
            for ( i = k; i < j; n += m.get(s.charAt(i++))) ;
            if (j+1 < s.length()) {
                n -= m.get(s.charAt(j));
                n += m.get(s.charAt(++j));
            }
            else n += m.get(s.charAt(j));
        }
        return n;
    }

    String []T;
    int ans;
    Set<String> collection = new HashSet<>();

    void arabic( int used, int cur, Map<Character,Integer>  mp) {
        if ( cur == digs.length() ) {
            assert mp.size() == digs.length();
            for ( int i = 0; i < 3; ++i )
                if ( mp.get(T[i].charAt(0)) == 0 ) return;
            if ( convert(T[0],mp)+convert(T[1],mp) == convert(T[2],mp) ) {
                Map<Character,Integer> map = new TreeMap<>();
                for ( int i = 0; i < 3; ++i )
                    for ( int j = 0; j < T[i].length(); ++j )
                        map.put(T[i].charAt(j),mp.get(T[i].charAt(j)));
                StringBuilder sb = new StringBuilder();
                for ( Map.Entry<Character,Integer> entry: map.entrySet() )
                    sb.append(entry.getValue()+"");
                collection.add(sb.toString());
                if ( collection.size() >= 2 ) return ;
            }
            return ;
        }
        for ( int u = (~used)&1023; u>0 && collection.size() <= 1; u &= ~L(u) ) {
            mp.put(digs.charAt(cur),D[which[L(u)]]);
            arabic(used|L(u),cur+1,mp);
        }
    }

    void go() throws Exception {
        for ( String buff; (buff = br.readLine()) != null && !buff.equals("#"); ) {
            T = buff.replaceFirst("^\\s+","").split("[+=]");
            int a = f(T[0]), b = f(T[1]), c = f(T[2]);
            Set<Character> ss = new TreeSet<>();
            for ( int i = 0; i < 3; ++i )
                for ( int j = 0; j < T[i].length(); ++j )
                    ss.add(T[i].charAt(j));
            digs = "";
            for ( Character ch: ss )
                digs += ch;
            if ( a+b == c )
                bw.write("Correct ");
            else
                bw.write("Incorrect ");
            collection.clear();
            arabic(0,0,new HashMap<>());
            ans = collection.size();
            if ( ans == 0 )
                bw.write("impossible\n");
            else if ( ans == 1 )
                bw.write("valid\n");
            else bw.write("ambiguous\n");
        }
        bw.flush();
    }
}

