/*
 * 449. Majoring in Scales
 * TOPIC: Accepted
 * status: WA
 */

/**
 * Created by sj on 29/01/17.
 */

import java.io.*;
import java.util.*;
import java.util.regex.*;

public class Main {

    enum Note {
        C("C","B#"),CS("C#","Db"),D("D","D"),DS("D#","Eb"),E("E","Fb"),F("F","E#"),FS("F#","Gb"),G("G","G"),GS("G#","Ab"),A("A","A"),AS("A#","Bb"),B("B","Cb");
        public String a = "", b = "";
        public static final int []d = {2,2,1,2,2,2,1};
        Note( String a, String b ) {
            this.a = a;
            this.b = b;
        }
        public static Note find( String a ) {
            for ( Note x: values() )
                if ( a.equals(x.a) || a.equals(x.b) )
                    return x;
            return null;
        }
        List<Note> construct() {
            List<Note> lst = new ArrayList<>();
            lst.add(this);
            for ( int j = this.ordinal(), i = 0; i < d.length-1; ++i ) {
                j = (j+d[i])%values().length;
                lst.add(values()[j]);
            }
            lst = lst;
            return lst;
        }
        static boolean cross( String a, String b ) {
            return a.indexOf("#") != -1 && b.indexOf("b") != -1 || a.indexOf("b") != -1 && b.indexOf("#") != -1;
        }
        static boolean getAvailableNames( int cur, int idx, List<Note> lst, List<String> names, String acc ) {
            if ( cur == 7 )
                return names.size() == 7;
            if ( acc.indexOf(lst.get(idx).a.charAt(0)) == -1 && !cross(acc,lst.get(idx).a) ) {
                names.add(lst.get(idx).a);
                if ( getAvailableNames(cur+1,idx+1,lst,names,acc+lst.get(idx).a) )
                    return true ;
                names.remove(lst.get(idx).a);
            }
            if ( acc.indexOf(lst.get(idx).b.charAt(0)) == -1 && !cross(acc,lst.get(idx).b) ) {
                names.add(lst.get(idx).b);
                if ( getAvailableNames(cur+1,idx+1,lst,names,acc+lst.get(idx).b) )
                    return true ;
                names.remove(lst.get(idx).b);
            }
            return false ;
        }
        public String toString( List<String> availableNames ) {
            if ( availableNames.contains(a) )
                return a;
            if ( availableNames.contains(b) )
                return b;
            int trap = 1/0;
            return null;
        }
    }

    int n;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/449/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/449/src/out02.txt")));
        new Main().go();
    }

    void go() throws Exception {
        int i,j,k,offset;
        Note key,start;
        List<Note> e;
        for ( String s,t; (s = br.readLine()) != null; bw.write("\n") ) {
            bw.write("Key of "+s+"\n");
            key = Note.find(t=s);
            assert key != null;
            e = key.construct();
            List<String> availableNames = new ArrayList<>();
            availableNames.add(t);
            if ( !Note.getAvailableNames(1,1,e,availableNames,""+t) ) {
                int trap = 1/0;
            }
            String acc = "";
            for ( String y: availableNames )
                acc += "|"+y+"|";
            for ( j = 0; j < 16; e.add(e.get(j++)) );
            s = br.readLine();
            String []b = s.split("[\\s;]+");
            n = b.length;
            assert n%3 == 0;
            for ( i = 0; i < n/3; ++i ) {
                String note = b[i*3], direction = b[i*3+1], interval = b[3*i+2];
                switch ( interval ) {
                    case "SECOND": offset = 1; break ;
                    case "THIRD": offset = 2; break ;
                    case "FOURTH": offset = 3; break ;
                    case "FIFTH": offset = 4; break ;
                    case "SIXTH": offset = 5; break ;
                    case "SEVENTH": offset = 6; break ;
                    default: offset = 7; break ;
                }
                bw.write(note+":");
                start = Note.find(note);
                if ( !e.contains(start) || acc.indexOf("|"+note+"|") == -1 ) {
                    bw.write(" invalid note for this key\n");
                    continue ;
                }
                bw.write(" "+direction+" "+interval+" > ");
                switch ( direction ) {
                    case "UP":  for ( j = e.indexOf(start); offset-->0; ++j );
                                break ;
                    case "DOWN":for ( j = e.lastIndexOf(start); offset-->0; --j );
                                break ;
                    default: j = 0; assert false;
                }
                bw.write(e.get(j).toString(availableNames)+"\n");
            }
        }
        bw.flush();
    }
}

