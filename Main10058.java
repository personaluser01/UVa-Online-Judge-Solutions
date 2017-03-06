/*
 * 10058. Jimmy's Riddles
 * status: Accepted
 * TOPIC: Regular Expressions, regex
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {

    Pattern VERB = Pattern.compile("\\s+(hates*|loves*|knows*|likes*)\\s+");
    Pattern NARTICLE = Pattern.compile("^((a|the)\\s+)?(tom|jerry|goofy|mickey|jimmy|dog|cat|mouse)$");

    public static void main( String [] args ) throws Exception { new Main().go(); }
    boolean isActor( String s ) {
        Matcher m = NARTICLE.matcher(s);
        return m.find();
    }
    boolean isActiveList( String s ) {
        String []w = s.split("\\s+and\\s+");
        for ( int i = 0; i < w.length; ++i ) 
            if ( !isActor(w[i]) )
                return false;
        return true;
    }
    boolean isAction( String s ) {
        String []w = VERB.split(s);
        return w.length == 2 && isActiveList(w[0]) && isActiveList(w[1]);
    }
    boolean isStatement( String s ) {
        String []w = s.split("\\s*,\\s*");
        for ( int i = 0; i < w.length; ++i )
            if ( !isAction(w[i]) )
                return false;
        return true;
    }
    void go() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String s;
        while ( (s = br.readLine()) != null ) 
            if ( isStatement(s) )
                System.out.println("YES I WILL");
            else
                System.out.println("NO I WON\'T");
    }
};

