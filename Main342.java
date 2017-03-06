/*
 * 342. HTML Syntax Checking
 * TOPIC: ad hoc, formatting, text processing
 * status: Accepted
 */

/**
 * Created by sj on 10/01/17.
 */

import java.io.*;
import java.util.*;
import java.util.regex.*;

public class Main {

    private final static Pattern openingTag = Pattern.compile("<[A-Z]{1,10}>");
    private final static Pattern closingTag = Pattern.compile("</[A-Z]{1,10}>");
    String s;
    int cur,cs;

    String getNextTag() {
        StringBuilder sb = new StringBuilder();
        while ( cur < s.length() && s.charAt(cur) != '<' ) ++cur;
        if ( cur == s.length() ) return null ;
        sb.append(s.charAt(cur++));
        while ( cur < s.length() && !Character.isSpaceChar(s.charAt(cur)) && s.charAt(cur) != '/' && s.charAt(cur) != '>' )
            sb.append(s.charAt(cur++));
        if ( cur < s.length() ) {
            if ( s.charAt(cur) == '/' ) {
                sb.append(s.charAt(cur++));
                while ( cur < s.length() && s.charAt(cur) != '>' )
                    sb.append(s.charAt(cur++));
                if ( cur < s.length() )
                    sb.append(s.charAt(cur++));
                return sb.toString();
            }
            else if ( s.charAt(cur) == '>' ) {
                sb.append(s.charAt(cur++));
                return sb.toString();
            }
            else {
                assert Character.isSpaceChar(s.charAt(cur));
                return sb.toString();
            }
        }
        return sb.toString();
    }

    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/NetBeansProjects/342/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/NetBeansProjects/342/src/out02.txt")));
        new Main().go();
    }

    Deque<String> tagStack;

    String getClosing( String s ) {
        return s.replace("<","</");
    }

    boolean tagMatch( String o, String c ) {
        return getClosing(o).equals(c);
    }

    boolean badCharacter( String t ) {
        if ( t == null || t.length() == 0 )
            return false ;
        Pattern p = Pattern.compile("^[A-Z]+");
        Matcher m = p.matcher(t);
        if ( !m.find() ) return true ;
        if ( m.group().length() > 10 ) return false ;
        return !(m.group().length() == t.length());
    }

    boolean processLine( int lineNo ) throws Exception {
        int k;
        String r,t;
        for ( cur = 0; (t = getNextTag()) != null; ) {
            k = t.length();
            if ( t.charAt(0) != '<' || t.charAt(k-1) != '>' ) {
                bw.write("line "+(lineNo)+": bad character in tag name.\n");
                return false ;
            }
            Matcher m = openingTag.matcher(t);
            if ( !m.find() ) {
                m = closingTag.matcher(t);
                if ( !m.find() ) {
                    if ( badCharacter(t.substring(1,k-1)) ) {
                        bw.write("line "+(lineNo)+": bad character in tag name.\n");
                        return false ;
                    }
                    else {
                        bw.write("line "+(lineNo)+": too many/few characters in tag name.\n");
                        return false ;
                    }
                }
                else {
                    assert m.group().equals(t);
                    if ( tagStack.isEmpty() ) {
                        bw.write("line "+(lineNo)+": no matching begin tag.\n");
                        return false ;
                    }
                    if ( !tagMatch(r = tagStack.pollFirst(),t) ) {
                        bw.write("line "+(lineNo)+": expected "+getClosing(r)+"\n");
                        return false ;
                    }
                }
            }
            else {
                assert m.group().equals(t);
                tagStack.addFirst(t);
            }
        }
        return true ;
    }

    void go() throws Exception {
        int i,lines;
        Scanner scan;
        boolean ok;
        for (;(s=br.readLine())!=null;) {
            scan = new Scanner(s);
            if ( (lines = scan.nextInt()) == 0 ) break ;
            bw.write("Test Case "+(++cs)+"\n");
            tagStack = new ArrayDeque<>();
            for ( ok = true, i = 0; i < lines && (s = br.readLine()) != null && (ok &= processLine(++i)); );
            for ( ;i++ < lines; br.readLine() );
            if ( ok && !tagStack.isEmpty() ) {
                bw.write("line "+lines+": expected "+getClosing(tagStack.getFirst())+"\n");
                ok = false ;
            }
            if ( ok ) bw.write("OK\n");
        }
        bw.flush();
    }
}

