/*
 * 405. Message Routing
 * TOPIC: simulation, bfs, hard interview question
 * status: Accepted
 */

/**
 * Created by sj on 02/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);
    int n;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/405/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/405/src/out02.txt")));
        new Main().go();
    }

    static boolean M( String x, String y ) {
        return x.equals("*") || y.equals("*") || x.equals(y);
    }

    class MTA {
        String name, country, admd, prmd, oname;
        MTA() {};
        MTA( Scanner scan ) {
            name = scan.next();
            country = scan.next();
            admd = scan.next();
            prmd = scan.next();
            oname = scan.next();
        }
        public boolean matches( MTA other ) {
            return M(country,other.country) && M(admd,other.admd) && M(prmd,other.prmd) && M(oname,other.oname);
        }
    }

    MTA combine( MTA x, MTA y ) throws Exception {
        MTA z = new MTA();
        z.name = y.name;
        z.country = x.country;
        z.admd = x.admd;
        z.prmd = x.prmd;
        z.oname = x.oname;
        return z;
    }

    class RoutingTable {
        final String name;
        List<MTA> lst = new ArrayList<>();
        RoutingTable( Scanner scan ) throws Exception {
            m.put(name = scan.next(),this);
            for ( int k = scan.nextInt(); k-->0; )
                lst.add(new MTA(scan));
        }
        @Override
        public boolean equals( Object other ) {
            if ( !(other instanceof RoutingTable) )
                return false ;
            RoutingTable r = (RoutingTable)other;
            return name.equals(r.name);
        }
        @Override
        public int hashCode() {
            return name.hashCode();
        }
    }

    RoutingTable []r;
    Map<String,RoutingTable> m = new HashMap<>();
    Queue<MTA> q = new LinkedList<>();
    Set<MTA> seen = new HashSet<>();

    void go() throws Exception {
        int i,j,k,cs = 0;
        boolean unabletoRoute, circular, ok;
        for ( ;scan.hasNext(); bw.write("\n") ) {
            r = new RoutingTable[n = scan.nextInt()];
            for ( m.clear(), i = 0; i < n; ++i )
                r[i] = new RoutingTable(scan);
            bw.write("Scenario # "+(++cs)+"\n");
            for ( i = 1, k = scan.nextInt(); k-->0; ++i ) {
                MTA x = new MTA(scan), y;
                for ( q.clear(), seen.clear(), bw.write(i+" -- "), ok = circular = unabletoRoute = false, seen.add(x), q.add(x); !q.isEmpty(); ) {
                    if ( !m.containsKey((x = q.poll()).name) ) {
                        unabletoRoute = true ;
                        break ;
                    }
                    RoutingTable t = m.get(x.name);
                    y = null;
                    for ( MTA z: t.lst )
                        if ( z.matches(x) ) {
                            y = z;
                            break ;
                        }
                    if ( y == null ) {
                        unabletoRoute = true ;
                        break ;
                    }
                    if ( y.name.equals(x.name) ) {
                        ok = true ;
                        break ;
                    }
                    if ( seen.contains(y) ) {
                        circular = true ;
                        break ;
                    }
                    q.add(combine(x,y));
                    seen.add(y);
                }
                ok = ok || (q.isEmpty() && !unabletoRoute && !circular);
                if ( ok ) bw.write("delivered to "+x.name+"\n");
                else if ( unabletoRoute ) bw.write("unable to route at "+x.name+"\n");
                else bw.write("circular routing detected by "+x.name+"\n");
            }
        }
        bw.flush();
    }
}
