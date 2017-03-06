/*
 * 10528. Major Scales
 * TOPIC: ad hoc, enumset, Java technique, good interview question
 * status: Accepted
 */

/**
 * Created by sj on 29/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static int []d = {2,2,1,2,2,2,1};
    static EnumMap<FullScale,EnumSet<FullScale>> m = new EnumMap<>(FullScale.class);
    static Map<String,FullScale> nm = new HashMap<>();

    enum FullScale {
        C("C"),CS("C#"),D("D"),DS("D#"),E("E"),F("F"),FS("F#"),G("G"),GS("G#"),A("A"),AS("A#"),B("B");
        final String name;
        FullScale( String s ) {
            name = s;
        }
        @Override
        public String toString() { return name; }
    }

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/10528/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/10528/src/out02.txt")));
        for ( int j,l, k = 0, i = 0; i < FullScale.values().length; ++i, k = 0 ) {
            FullScale []fs = new FullScale[d.length+1];
            for ( fs[k++] = FullScale.values()[j=i], l = 0; l < d.length; ++l ) {
                j = (j+d[l])%FullScale.values().length;
                fs[k++] = FullScale.values()[j];
            }
            m.put(fs[0],EnumSet.of(fs[0],fs));
        }
        for ( FullScale f: FullScale.values() )
            nm.put(f.toString(),f);
        new Main().go();
    }

    boolean contains( FullScale key, Set<FullScale> s ) {
        return m.get(key).containsAll(s);
    }

    void go() throws Exception {
        for ( String s; (s = br.readLine()) != null && !s.equals("END"); ) {
            Scanner scan = new Scanner(s);
            Set<FullScale> q = new HashSet<>(), ans = new TreeSet<>();
            for ( ;scan.hasNext(); q.add(nm.get(scan.next())) );
            for ( FullScale f: FullScale.values() )
                if ( contains(f,q) )
                    ans.add(f);
            int k = 0;
            for ( FullScale f: ans ) {
                if ( ++k > 1 ) bw.write(" ");
                bw.write("" + f);
            }
            bw.write("\n");
        }
        bw.flush();
    }
}
