/*
 * 1219. Team Arrangement
 * TOPIC: string processing
 * status: Accepted
 */

import java.io.*;
import java.util.*;

/**
 * Created by sj on 08/01/17.
 */
public class Main1219 {
    enum Roles { G, D, M, S };
    private final static int N = 22;
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    public static void main( String ... args ) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/1219/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/1219/src/out02.txt")));
        new Main1219().go();
    }
    private class Player implements Comparable<Player> {
        Roles r;
        String name;
        int number, record;
        boolean isCap = false;
        Player( Scanner scan ) {
            number = scan.nextInt();
            name = scan.next();
            switch ( scan.next() ) {
                case "G": r = Roles.G; break ;
                case "D": r = Roles.D; break ;
                case "M": r = Roles.M; break ;
                case "S": r = Roles.S; break ;
                default: assert false ;
            }
            record = 0;
            while ( scan.hasNext() ) {
                String []t = scan.next().split("-");
                record += Integer.parseInt(t[1]) - Integer.parseInt(t[0])+1;
            }
        }
        @Override
        public int compareTo( Player other ) {
            if ( this.isCap ) return -1;
            if ( other.isCap ) return 1;
            if ( this.r == other.r )
                return this.number-other.number;
            return this.r.compareTo(other.r);
        }
    }
    class SelectCaptain implements Comparator<Player> {
        @Override
        public int compare( Player x, Player y ) {
            if ( x.record == y.record )
                return y.number-x.number;
            return y.record-x.record;
        }
    }
    Player[] p = new Player[N];
    List<Player> lst;
    void go() throws Exception {
        String s;
        String []formation;
        int i,j,k;
        while ( (s = br.readLine()) != null && !s.equals("0") ) {
            Scanner scan = new Scanner(s);
            i = 0;
            do {
                p[i++] = new Player(scan);
                if ( i < N )
                    scan = new Scanner(br.readLine());
            } while ( i < N );
            formation = ("1-"+br.readLine()).split("-");
            lst = new ArrayList<>();
            Map<Roles,Set<Player>> m = new TreeMap<>();
            for ( Roles r: Roles.values() ) {
                k = Integer.parseInt(formation[r.ordinal()]);
                m.put(r,new TreeSet<>());
                for ( i = 0; i < N; ++i )
                    if ( p[i].r == r )
                        m.get(r).add(p[i]);
                i = 0;
                for ( Iterator<Player> it =  m.get(r).iterator(); i < k && it.hasNext(); ++i )
                    lst.add(it.next());
            }
            if ( lst.size() < 11 ) {
                bw.write("IMPOSSIBLE TO ARRANGE\n\n");
                continue ;
            }
            Collections.sort(lst,new SelectCaptain());
            lst.get(0).isCap = true ;
            Collections.sort(lst);
            for ( i = 0; i < 11; ++i )
                bw.write(lst.get(i).number+" "+lst.get(i).name+" "+lst.get(i).r+"\n");
            bw.write("\n");
        }
        bw.flush();
    }
}

