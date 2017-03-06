/*
 * 554. Caesar Cypher
 * TOPIC: ad hoc, output formatting careful
 * status: Accepted
 */

/**
 * Created by sj on 21/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    String A = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    private final static int N = 0x80;
    int n;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    Set<String> words = new HashSet<>();
    char []e;
    String soln;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/554/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/554/src/out02.txt")));
        new Main().go();
    }

    char f( char ch, int k ) {
        switch ( ch ) {
            case ' ': return A.charAt((0+k)%27);
            default: return A.charAt(((ch-'A')+1+k)%27);
        }
    }

    int numOfMatches( final int k ) {
        int i,score = 0;
        StringBuilder sb = new StringBuilder();
        for ( i = 0; i < n; ++i )
            sb.append(f(e[i],k));
        Scanner scan = new Scanner(soln = sb.toString());
        while ( scan.hasNext() )
            if ( words.contains(scan.next()) ) ++score;
        return score ;
    }

    void go() throws Exception {
        int i,j = -1,k,maxSoFar = -1;
        String s;
        for (;(s = br.readLine()) != null && !s.equals("#"); words.add(s) );
        e = (s = br.readLine()).toCharArray();
        n = s.length();
        for ( k = 26; k >= 1; --k )
            if ( (i = numOfMatches(k)) > maxSoFar ) {
                maxSoFar = i;
                j = k;
            }
        numOfMatches(j);
        String []str = soln.split("\\b");
        for ( i = 0; i < str.length; i = j ) {
            if ( str[i].indexOf(' ') != -1 )
                if ( ++i >= str.length ) break ;
            for ( j = i+1, k = str[i].length(), bw.write(str[i]); j < str.length && k+str[j].length() <= 60; ) {
                k += str[j++].length();
                if ( (j < str.length && k+str[j].length() > 60 || j == str.length) && str[j-1].indexOf(' ') != -1 ) break ;
                bw.write(str[j-1]);
            }
            bw.write("\n");
        }
        bw.flush();
    }
}

