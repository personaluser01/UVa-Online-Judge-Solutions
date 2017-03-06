/*
 * 11339. Sonnet Rhyme Checker
 * TOPIC: encodings, regex, good interview question
 * status: Accepted
 */

/**
 * Created by sj on 15/02/17.
 */

import java.io.*;
import java.util.*;
import java.util.regex.Pattern;

public class Main {

    private final static String []str = {"ABBAABBACDECDE","ABBAABBACDEDCE","ABBAABBACDCDCD"};
    // private static final String ENC = "ISO-8859-1";
    private static final String ENC = "UTF-8";

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/11339/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/11339/src/out02.txt")));
        new Main().go();
    }

    boolean isEmptyLine( String s ) {
        for ( Character ch: s.toCharArray() )
            if ( ch != ' ' )
                return false ;
        return true ;
    }

    private final static Pattern punct = Pattern.compile("[ ¡!,:;¿?\\-.]+",Pattern.UNICODE_CHARACTER_CLASS);
    Map<String,String> m = new TreeMap<>();

    String g( String s ) {
        return s.replaceAll("\\s*$","");
    }

    String strip( String s ) {
        String t = s.replaceAll("[¡!,:;¿?\\-.]+\\s*$","");
        if ( t.endsWith("s") )
            return g(t.substring(0,t.length()-1));
        return g(t);
    }

    String f( String s ) {
        for ( Map.Entry<String,String> entry: m.entrySet() )
            if ( s.endsWith(entry.getKey()) )
                return entry.getValue();
        return "X";
    }

    void go() throws Exception {
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out, ENC));
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in, ENC));
        String s,title;
        int i,j,k;
        List<String> lst = new ArrayList<>();
        while ( (s=br.readLine()) != null ) {
            String []suff = s.replaceFirst("^\\s+","").split("\\s+");
            title = br.readLine();
            for ( m.clear(), i = 0; i < suff.length; ++i )
                m.put(suff[i],Character.valueOf((char)(i+'A'))+"");
            for ( lst.clear(); (s=br.readLine()) != null && !isEmptyLine(s); lst.add(strip(s)) );
            bw.write(title+":");
            if ( lst.size() != 14 ) {
                bw.write(" Not a chance!\n");
                continue ;
            }
            StringBuilder sb = new StringBuilder();
            for ( String t: lst )
                sb.append(f(t));
            String sbstr = sb.toString();
            sbstr = sbstr;
            boolean flag = false ;
            for ( String t: str )
                if ( sbstr.equals(t) ) {
                    bw.write(" "+t+"\n");
                    flag = true ;
                    break ;
                }
            if ( !flag )
                bw.write(" Not a chance!\n");
        }
        bw.flush();
    }
}
