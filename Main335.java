/*
 * 335. Processing MDX Records
 * TOPIC: simulation, strings
 * status: Accepted
 */

/**
 * Created by sj on 02/02/17.
 */

import java.io.*;
import java.util.*;
import java.util.regex.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/335/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/335/src/out02.txt")));
        new Main().go();
    }

    class Pair implements Comparable<Pair> {
        int p;
        String name;
        @Override
        public int compareTo( Pair other ) {
            if ( this.p == other.p )
                return name.compareTo(other.name);
            return p-other.p;
        }
        Pair( String n, int p ) {
            this.p = p;
            this.name = n;
        }
    }

    Map<String,Set<Pair>> m = new TreeMap<>();
    Set<String> machines = new HashSet<>(), suffixes = new HashSet<>();
    Set<String> up = new HashSet<>(), down = new HashSet<>();

    void addRecord( String x, Pair p ) {
        if ( p.name.charAt(0) == '*' )
            return ;
        if ( !m.containsKey(x) )
            m.put(x,new TreeSet<>());
        m.get(x).add(p);
    }

    String none( String x ) {
        return String.format("%s =>",x);
    }

    String processOrdinaryRequest( String x, String name ) {
        for ( Pair p: m.get(x) )
            if ( up.contains(p.name) )
                return String.format("%s => %s",name,p.name);
        return none(name);
    }

    String processRequest( String x ) {
        int k;
        if ( m.containsKey(x) )
            return processOrdinaryRequest(x,x);
        else {
            if ( x.indexOf(".") == -1 )
                return none(x);
            String y = x;
            for ( k = y.indexOf("."); k != -1 && (y = y.substring(k+1)) != null; k = y.indexOf(".") )
                if ( suffixes.contains(y) && up.contains(y) )
                    return processOrdinaryRequest("*." + y, x);
            return none(x);
        }
    }

    String getAns( String x ) {
        int k;
        Set<Pair> a = new TreeSet<>();
        if ( m.containsKey(x) )
            for ( Pair p: m.get(x) )
                if ( up.contains(p.name) )
                    a.add(p);
        String y = x;
        for ( k = y.indexOf("."); k != -1 && (y = y.substring(k+1)) != null; k = y.indexOf(".") ) {
            if ( suffixes.contains(y) )
                for ( Pair p: m.get("*."+y) )
                    if ( up.contains(p.name) )
                        a.add(p);
        }
        if ( a.isEmpty() ) return none(x);
        return String.format("%s => %s",x,a.iterator().next().name);
    }

    void go() throws Exception {
        int n;
        String s,prev = null;
        String []c;
        for ( n = Integer.parseInt(br.readLine()); n-->0; ) {
            c = br.readLine().replaceFirst("^\\s+","").split("\\s+");
            if ( c.length == 3 ) {
                addRecord(prev = c[0], new Pair(c[2], Integer.parseInt(c[1])));
                machines.add(c[0]);
                machines.add(c[2]);
                if ( c[0].charAt(0) == '*' ) {
                    if (c[0].length() >= 2)
                        suffixes.add(c[0].substring(2));
                    else suffixes.add("");
                }
            }
            else {
                assert c.length == 2;
                if ( prev == null ) continue ;
                addRecord(prev,new Pair(c[1],Integer.parseInt(c[0])));
                machines.add(c[1]);
            }
        }
        for ( up.addAll(machines); (s = br.readLine()) != null; ) {
            c = s.replaceFirst("^\\s+","").split("\\s+");
            if ( c.length <= 1  ) continue ;
            c[0] = c[0].toUpperCase();
            if ( c[0].equals("X") ) break ;
            switch ( c[0] ) {
                case "A": //bw.write(processRequest(c[1])+"\n");
                          bw.write(getAns(c[1])+"\n");
                          break ;
                case "D": if ( up.remove(c[1]) )
                            down.add(c[1]);
                          break ;
                case "U": if ( down.remove(c[1]) )
                            up.add(c[1]);
                          break ;
                default:  assert false ;
            }
            bw.flush();
        }
    }
}

