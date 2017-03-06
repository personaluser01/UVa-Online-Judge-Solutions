/*
 * 373. Romulan Spelling
 * TOPIC: change-while-it-changes, update-while-flag, do-while-flag
 * status: Accepted
 */

/**
 * Created by sj on 09/01/17.
 */

import com.sun.org.apache.regexp.internal.CharacterArrayCharacterIterator;

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/373/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/373/src/out02.txt")));
        new Main().go();
    }

    static char H( char []s, int i ) {
        return Character.toLowerCase(s[i]);
    }

    void xchg( char []s, int x, int y ) {
        char ch = s[x]; s[x] = s[y]; s[y] = ch;
    }

    String f( char []s ) {
        boolean flag;
        int i,j,k,n = s.length;
        do {
            flag = false ;
            for ( i = 0; i < n; ++i )
                if ( H(s,i) == 'p' && i+1 < n && H(s,i+1) == 'g' ) {
                    if (!(i-1>=0 && H(s, i-1)=='e' || i+3 < n && H(s, i + 2) == 'u' && H(s, i + 3) == 'k')) {
                        xchg(s,i,i+1);
                        flag = true;
                    }
                }
                else if ( H(s,i)=='g' && i+1<n && H(s,i+1)=='p' ) {
                    if ( i+3<n && H(s,i+2)=='u' && H(s,i+3)=='k' ) {
                        xchg(s,i,i+1);
                        flag = true ;
                    }
                    else if ( i-1>=0 && H(s,i-1) == 'e' ) {
                        xchg(s,i,i+1);
                        flag = true ;
                    }
                }
        } while ( flag );
        return new String(s);
    }

    void go() throws Exception {
        for ( String s; (s=br.readLine())!=null; bw.write("\n") )
            for ( int i = 0; i < s.length(); ) {
                while ( i < s.length() && Character.isSpaceChar(s.charAt(i)) )
                    bw.write(s.charAt(i++));
                StringBuilder sb = new StringBuilder();
                while ( i < s.length() && !Character.isSpaceChar(s.charAt(i)) )
                    sb.append(s.charAt(i++));
                if ( sb.toString().length() >= 1 )
                    bw.write(f(sb.toString().toCharArray()));
            }
        bw.flush();
    }
}
