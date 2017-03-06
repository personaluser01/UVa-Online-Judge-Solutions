/*
 * 346. Getting Chorded
 * TOPIC: ad hoc
 * status: Accepted
 */

/**
 * Created by sj on 30/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {

    enum Note {
        A("A","A"), AS("A#","BB"), B("B","Cb"), C("C","B#"), CS("C#","DB"), D("D","D"), DS("D#","EB"), E("E","Fb"), F("E#","F"), FS("F#","GB"), G("G","G"), GS("G#","AB");
        String a,b;
        Note( String a, String b ) {
            this.a = a;
            this.b = b;
        }
        static Note find( String s ) {
            s = s.toUpperCase();
            for ( Note x: values() )
                if ( x.a.equals(s) || x.b.equals(s) )
                    return x;
            return null ;
        }
        Note [] major() {
            int i,k;
            Note[] lst = {null,null,null};
            lst[0]=this;
            for ( i = this.ordinal(), k = 4; k-->0; ++i, i %= 12 );
            lst[1]=values()[i];
            for ( k = 3; k-->0; ++i, i %= 12 );
            lst[2]=values()[i];
            return lst;
        }
        Note [] minor() {
            int i,k;
            Note []lst = {null,null,null};
            lst[0]=this;
            for ( i = this.ordinal(), k = 3; k-->0; ++i, i %= 12 );
            lst[1]=values()[i];
            for ( k = 4; k-->0; ++i, i %= 12 );
            lst[2]=values()[i];
            return lst;
        }
        public String toString() {
            if ( a.length() == 1 )
                return a;
            if ( b.length() == 1 )
                return b;
            if ( a.indexOf("#") != -1 )
                return a;
            return b;
        }
    }

    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/346/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/346/src/out02.txt")));
        new Main().go();
    }

    void go() throws Exception {
        String s,buff,res = null;
        int j;
        String []t = {null,null,null};
        Note []a = {null,null,null};
        while ( (buff = br.readLine()) != null ) {
            Scanner scan = new Scanner(buff);
            for ( int i = 0; i < 3; ++i ) {
                s = scan.next();
                t[i] = new String(s);
                a[i] = Note.find(s);
            }
            Arrays.sort(a);
            boolean verdict = false;
            for ( int i = 0; i < 3 && !verdict; ++i ) {
                Note[] b = a[i].major(), c = a[i].minor();
                Arrays.sort(b);
                Arrays.sort(c);
                if (Arrays.equals(a, b)) {
                    for ( j = 0; j < 3; ++j )
                        if ( Note.find(t[j]) == a[i] )
                        { res = t[j]; break; }
                    bw.write(buff + " is a " + Note.find(res) + " Major chord.\n");
                    verdict = true ;
                } else if (Arrays.equals(a, c)) {
                    for ( j = 0; j < 3; ++j )
                        if ( Note.find(t[j]) == a[i] )
                        { res = t[j]; break; }
                    bw.write(buff + " is a " + Note.find(res) + " Minor chord.\n");
                    verdict = true ;
                }
            }
            if ( !verdict )
                bw.write(buff + " is unrecognized.\n");
        }
        bw.flush();
    }
}

