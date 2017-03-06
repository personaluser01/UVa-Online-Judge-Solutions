/*
 * 804. Petri Net Simulation
 * TOPIC: simulation
 * status: Accepted
 */

/**
 * Created by sj on 11/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    enum EventType {
        ENABLED, DISABLED;
    }
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    Scanner scan = new Scanner(System.in);
    int firings;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/804/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/804/src/out02.txt")));
        new Main().go();
    }

    class PetriNet {
        int np,nt = 0;
        Map<Integer,Set<Integer>> in = new HashMap<>(), out = new HashMap<>();
        Map<Integer,Integer> tokens = new HashMap<>();
        int [][]ink = new int[0x80][0x80], outk = new int[0x80][0x80];
        void addInput( int t, int p ) {
            if ( !in.containsKey(t) )
                in.put(t,new HashSet());
            in.get(t).add(p);
            ++ink[t][p];
        }
        void addOutput( int t, int p ) {
            if ( !out.containsKey(t) )
                out.put(t,new HashSet());
            out.get(t).add(p);
            ++outk[t][p];
        }
        PetriNet() {
            np = scan.nextInt();
            if ( np == 0 ) return ;
            for ( int i = 0; i < np; ++i )
                tokens.put(i,scan.nextInt());
            nt = scan.nextInt();
            for ( int i = 0; i < nt; ++i )
                for ( int j; (j = scan.nextInt()) != 0; )
                    if ( j < 0 ) addInput(i,-j-1);
                    else addOutput(i,j-1);
            firings = scan.nextInt();
        }
        boolean isEnabled( int t ) {
            for ( Integer inp: in.get(t) )
                if ( tokens.get(inp) < ink[t][inp] )
                    return false ;
            return true ;
        }
        boolean fire( int t ) {
            boolean remainsEnabled = true;
            for ( Integer inp: in.get(t) ) {
                assert tokens.get(inp) >= ink[t][inp];
                tokens.put(inp, tokens.get(inp)-ink[t][inp]);
                remainsEnabled &= tokens.get(inp)>=ink[t][inp];
            }
            for ( Integer outp: out.get(t) )
                tokens.put(outp,tokens.get(outp)+outk[t][outp]);
            return remainsEnabled;
        }
        int getFirstEnabled() {
            for ( int i = 0; i < nt; ++i )
                if ( isEnabled(i) )
                    return i;
            return -1;
        }
    }

    PriorityQueue<Integer> pq = new PriorityQueue<>();

    void go() throws Exception {
        int i,j,k,cs = 0,time,completed,t;
        for ( PetriNet p; (p = new PetriNet()) != null && p.np != 0; ) {
            assert( p.nt != 0 );
            pq.clear();
            if ( (i = p.getFirstEnabled()) != -1 )
                pq.add(i);
            for ( completed = 0; !pq.isEmpty(); ) {
                t = pq.poll();
                if ( p.fire(t) ) {
                    if ( ++completed == firings ) break ;
                    if ( !pq.isEmpty() ) continue ;
                    pq.add(t);
                }
                else {
                    if ( ++completed == firings ) break ;
                    if ( !pq.isEmpty() ) continue ;
                    if ( (t = p.getFirstEnabled()) != -1 )
                        pq.add(t);
                }
            }
            bw.write("Case "+(++cs)+": ");
            if ( completed < firings )
                bw.write("dead after "+completed+" transitions\n");
            else bw.write("still live after "+completed+" transitions\n");
            bw.write("Places with tokens:");
            for ( i = 0; i < p.np; ++i )
                if ( (k=p.tokens.get(i)) > 0 )
                    bw.write(String.format(" %d (%d)",i+1,k));
            bw.write("\n\n");
        }
        bw.flush();
    }
}

