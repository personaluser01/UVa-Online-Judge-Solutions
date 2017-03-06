/*
 * 857. Quantiser
 * TOPIC: ad hoc, simulation, good interview question, Java technique
 * status: Accepted
 */

/**
 * Created by sj on 28/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private static final int oo = (1<<29);
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);
    int n;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/857/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/857/src/out02.txt")));
        new Main().go();
    }

    enum StampField {
        TICK(480), BEAT(4), MEASURE(+oo);
        public final int MAXVAL;
        private StampField( int MAXVAL ) {
            this.MAXVAL = MAXVAL;
        }
    }

    class Stamp implements Comparable<Stamp>, Cloneable {
        int measure, beat, tick;
        final boolean on;
        final int pianoKey;
        boolean toRemove;
        int id;
        Stamp closingEvent = null, openingEvent = null;
        Stamp( Scanner scan, int id ) {
            this.id = id;
            on = scan.nextInt()==1;
            pianoKey = scan.nextInt();
            measure = scan.nextInt();
            beat = scan.nextInt();
            tick = scan.nextInt();
        }
        void roll( int x, StampField f ) {
            switch ( f ) {
                case TICK: if ( (tick += x) >= f.MAXVAL ) {
                                beat += (tick/f.MAXVAL);
                                tick %= f.MAXVAL;
                                if ( beat >= StampField.BEAT.MAXVAL+1 ) {
                                    measure += beat/StampField.BEAT.MAXVAL;
                                    beat %= StampField.BEAT.MAXVAL;
                                }
                           }
                           break ;
                case BEAT: if ( (beat += x) >= f.MAXVAL+1 ) {
                                measure += beat/f.MAXVAL;
                                beat %= f.MAXVAL;
                           }
                           break ;
                default: measure += x;
            }
        }
        @Override
        public int compareTo( Stamp other ) {
            if ( this.measure == other.measure ) {
                if ( this.beat == other.beat ) {
                    if ( this.tick == other.tick ) {
                        if ( this.id == other.id ) {
                            if ( on == other.on ) return 0;
                            return on?-1:1;
                        }
                        return id-other.id;
                    }
                    return tick-other.tick;
                }
                return beat-other.beat;
            }
            return measure-other.measure;
        }
        public int value() {
            return measure*StampField.BEAT.MAXVAL*StampField.TICK.MAXVAL+beat*StampField.TICK.MAXVAL+tick;
        }
        public int diff( Stamp other ) {
            return value()-other.value();
        }
        void quantise() throws Exception {
            Stamp s = (Stamp)this.clone(), q = (Stamp)this.clone();
            List<Stamp> lst = new ArrayList<>();
            q.tick = 0;
            for ( int i = 0; i <= 10; ++i ) {
                lst.add((Stamp)q.clone());
                q.roll(60,StampField.TICK);
            }
            for ( int i = 0; i < lst.size()-1; ++i )
                if ( s.compareTo(lst.get(i)) >= 0 && lst.get(i+1).compareTo(s) > 0 ) {
                    int down = s.diff(lst.get(i)), up = lst.get(i+1).diff(s);
                    if ( down >= up ) s = (Stamp)lst.get(i+1).clone();
                    else s = (Stamp)lst.get(i).clone();
                    break ;
                }
            this.measure = s.measure;
            this.beat = s.beat;
            this.tick = s.tick;
        }
        public String toString() {
            return String.format("%d %d %d %d %d\n",on?1:0,pianoKey,measure,beat,tick);
        }
    }

    class Comp implements Comparator<Stamp> {
        @Override
        public int compare( Stamp x, Stamp y ) {
            return x.pianoKey-y.pianoKey;
        }
    }

    Stamp []s;
    Map<Stamp,Deque<Stamp>> q = new TreeMap<>(new Comp());
    List<Stamp> lst = new ArrayList<>();

    void go() throws Exception {
        int i,j,k;
        for ( ;scan.hasNext() && (n = scan.nextInt()) != -1; ) {
            s = new Stamp[n];
            for ( i = 0; i < n; ++i )
                s[i] = new Stamp(scan,i);
            q.clear();
            for ( i = 0; i < n; ++i ) {
                if (!q.containsKey(s[i]))
                    q.put(s[i], new LinkedList<>());
                if ( s[i].on )
                    q.get(s[i]).addLast(s[i]);
                else {
                    Stamp top = q.get(s[i]).pollLast();
                    top.closingEvent = s[i];
                    s[i].openingEvent = top;
                }
            }
            for ( i = 0; i < n; s[i++].quantise() );
            for ( i = 0; i < n; ++i )
                if ( s[i].closingEvent != null && s[i].on && s[i].diff(s[i].closingEvent) == 0 )
                    s[i].toRemove = s[i].closingEvent.toRemove = true ;
            for ( lst.clear(), i = 0; i < n; ++i )
                if ( !s[i].toRemove )
                    lst.add(s[i]);
            bw.write(lst.size()+"\n");
            for ( Stamp r: lst )
                bw.write(""+r);
        }
        bw.write("-1\n");
        bw.flush();
    }
}

