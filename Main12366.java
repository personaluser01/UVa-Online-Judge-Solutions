/*
 * 12366. King's Poker
 * TOPIC: ad hoc, greedy, IQ, case analysis
 * status: Accepted
 */

/**
 * Created by sj on 18/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {

    enum Ranks {
        ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING;
        static Ranks find( int k ) {
            assert 0 <= k && k <= values().length-1: k+"\n";
            for ( Ranks r: values() )
                if ( r.ordinal() == k )
                    return r;
            assert false;
            return null;
        }
    }

    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12366/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12366/src/out02.txt")));
        new Main().go();
    }

    class PokerHand implements Comparable<PokerHand> {
        Ranks []r = new Ranks[3];
        boolean isSet = false, isPair = false, noPair = true ;
        PokerHand( Ranks ... x ) {
            assert x.length == 3;
            r[0] = x[0];
            r[1] = x[1];
            r[2] = x[2];
            setType();
        }
        @Override
        public int compareTo( PokerHand hand ) {
            assert hand != null;
            if ( isSet && !hand.isSet )
                return 1;
            if ( !isSet && hand.isSet )
                return -1;
            if ( isSet && hand.isSet )
                return r[0].ordinal()-hand.r[0].ordinal();
            assert !isSet && !hand.isSet;
            if ( isPair && !hand.isPair )
                return 1;
            if ( !isPair && hand.isPair )
                return -1;
            if ( isPair && hand.isPair )
                return r[0].ordinal()==hand.r[0].ordinal()?r[2].ordinal()-hand.r[2].ordinal():r[0].ordinal()-hand.r[0].ordinal();
            assert !isPair && !hand.isPair;
            assert noPair && hand.noPair: hand.noPair+" "+noPair;
            return 0;
        }
        private void setType() {
            if ( r[0] == r[1] && r[1] == r[2] ) {
                isSet = true ;
                noPair = false ;
                return ;
            }
            Arrays.sort(r);
            if ( r[0] == r[1] || r[1] == r[2] ) {
                if ( r[1] == r[2] ) {
                    Ranks tmp = r[0];
                    r[0] = r[2];
                    r[2] = tmp;
                }
                isPair = true ;
                assert r[0] == r[1];
                noPair = false ;
                return ;
            }
            noPair = true ;
        }
        @Override
        public String toString() {
            Arrays.sort(r);
            StringBuilder sb = new StringBuilder();
            int k = 0;
            for ( Ranks x: r ) {
                if (++k > 1) sb.append(" ");
                sb.append((x.ordinal()+1)+"");
            }
            return sb.toString();
        }
    }

    void go() throws Exception {
        int i,j,k;
        PokerHand best;

        for ( String s; (s=br.readLine()) != null && !s.equals("0 0 0"); ) {
            Scanner scan = new Scanner(s);
            i = scan.nextInt()-1;
            j = scan.nextInt()-1;
            k = scan.nextInt()-1;
            PokerHand p = new PokerHand(Ranks.find(i),Ranks.find(j),Ranks.find(k)), hand;
            if ( p.noPair )
                best = new PokerHand(Ranks.ACE,Ranks.ACE,Ranks.TWO);
            else if (p.isPair ) {
                if ( p.r[2] != Ranks.KING ) {
                    best = new PokerHand(p.r[0], p.r[1], Ranks.find(p.r[2].ordinal() + 1));
                    hand = null;
                    if ( p.r[2] != Ranks.QUEEN )
                        hand = new PokerHand(p.r[0], p.r[1], Ranks.find(p.r[2].ordinal() + 2));
                    if ( hand != null && hand.compareTo(best) < 0 )
                        best = hand;
                }
                else
                    best = new PokerHand(Ranks.find(p.r[0].ordinal()+1),Ranks.find(p.r[1].ordinal()+1),Ranks.ACE);
                hand = new PokerHand(Ranks.ACE,Ranks.ACE,Ranks.ACE);
                if ( best.compareTo(hand) > 0 ) best = hand;
            }
            else {
                if ( p.r[0] == Ranks.KING )
                    best = null;
                else best = new PokerHand(Ranks.find(p.r[0].ordinal()+1),Ranks.find(p.r[1].ordinal()+1),Ranks.find(p.r[2].ordinal()+1));

            }
            bw.write(best==null?"*\n":best.toString()+"\n");
        }
        bw.flush();
    }
}
