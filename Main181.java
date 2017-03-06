/*
 * 181. Hearts
 * TOPIC: java enums, card games, simulation
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	
	static boolean DBG = false;

	enum Suits {
		CLUBS ("C"),
		DIAMONDS ("D"), 
		HEARTS ("H"), 
		SPADES ("S");
		private final String str;
		private Suits( String t ) {
			this.str = t;
		}
		public String getStr() {
			return this.str;
		}
		static Suits getInstance( String t ) {
			for ( Suits s: values() ) 
				if ( s.str.equals(t) ) return s;
			return null;
		}
		int getRank() {
			for ( int i = 0; i < values().length; ++i )
				if ( values()[i] == this )
					return i;
			return -1;
		}
	};

	enum Values {
		TWO ("2",2),
		THREE ("3",3),
		FOUR ("4",4),
		FIVE ("5",5),
		SIX ("6",6),
		SEVEN ("7",7),
		EIGHT ("8",8),
		NINE ("9",9),
		TEN ("T",10),
		JACK ("J",11),
		QUEEN ("Q",12),
		KING ("K",13),
		ACE ("A",14);
		final String str;
		final int val;
		private Values( String str, int val ) {
			this.str = str;
			this.val = val;
		}
		static Values getInstance( String t ) {
			for ( Values v: values() ) 
				if ( v.str.equals(t) )
					return v;
			return null;
		}
	};

	class Card {
		Suits s;
		Values v;
		Card( Suits s, Values v ) {
			this.s = s; 
			this.v = v;
		};
		Card( String t ) {
			this(Suits.getInstance(t.charAt(1)+""),Values.getInstance(t.charAt(0)+""));
		}
		public String toString() {
			return this.v.str+this.s.str;
		}
		public boolean equals( Object obj ) {
			if ( obj instanceof Card ) 
				return this.s == ((Card)obj).s && this.v == ((Card)obj).v;
			return false ;
		}
	};

	final int A = 52;
	Scanner scan = new Scanner(System.in);
	Card []c = new Card[A];
	Map<Integer,List<Card>> h;
	List<Card> dealt;
	Suits trumpSuit,leadSuit;
	int []score = new int[5];

	public static void main( String [] args ) throws Exception {
		new Main().go();
	}

	Suits decideTrump( Card a, Card b ) {
		if ( a.v.val > b.v.val )
			return a.s;
		if ( a.v.val < b.v.val )
			return b.s;
		assert a.v.val == b.v.val;
		return a.s.getRank()<b.s.getRank()?b.s:a.s;
	}

	Card firstMove( int idx ) {
		int i,j,k,highestVal = -1;
		List<Card> lst = new ArrayList<>();
		if ( DBG ) {
			System.out.print("Leader "+idx+" cards: ");
			for ( Card c: h.get(idx) ) {
				System.out.print(c+" ");
			}
			System.out.println();
		}
		for ( i = 0; i < h.get(idx).size(); ++i ) {
			assert h.get(idx) != null;
			assert h.get(idx).get(i).v != null;
			if ( h.get(idx).get(i).v.val > highestVal ) {
				highestVal = h.get(idx).get(i).v.val;
				lst.clear();
				lst.add(h.get(idx).get(i));
			}
			else if ( highestVal == h.get(idx).get(i).v.val ) 
				lst.add(h.get(idx).get(i));
		}
		if ( lst.size() == 1 )
			return lst.get(0);
		for ( i = 0; i < lst.size(); ++i ) 
			if ( lst.get(i).s == trumpSuit ) 
				return lst.get(i);
		Card best = lst.get(0);
		for ( i = 1; i < lst.size(); ++i )
			if ( lst.get(i).s.getRank() > best.s.getRank() )
				best = lst.get(i);
		return best;
	}

	Card nextMove( Card lastPlayed, int idx ) {
		int i,j,k,highestVal = -1;
		Card bestCard = null;

		for ( i = 0; i < h.get(idx).size(); ++i ) 
			if ( leadSuit == h.get(idx).get(i).s && h.get(idx).get(i).v.val > highestVal ) 
				highestVal = (bestCard = h.get(idx).get(i)).v.val;
		if ( highestVal != -1 ) 
			return bestCard;

		for ( i = 0; i < h.get(idx).size(); ++i )
			if ( h.get(idx).get(i).s == trumpSuit && h.get(idx).get(i).v.val > highestVal ) {
				highestVal = (bestCard = h.get(idx).get(i)).v.val;
			}
		if ( highestVal != -1 )
			return bestCard;
		/* choose a card to discard */
		if ( lastPlayed.s == trumpSuit ) {
			for ( i = 0; i < h.get(idx).size(); ++i ) {
				assert h.get(idx).get(i).s != trumpSuit;
				if ( h.get(idx).get(i).v.val > highestVal || h.get(idx).get(i).v.val == highestVal && h.get(idx).get(i).s.getRank() > bestCard.s.getRank() ) 
					highestVal = (bestCard = h.get(idx).get(i)).v.val;
			}
			return bestCard;
		}

		assert highestVal == -1;
		for ( i = 0; i < h.get(idx).size(); ++i )
			if ( h.get(idx).get(i).s == trumpSuit ) 
				if ( h.get(idx).get(i).v.val > highestVal )
					highestVal = (bestCard = h.get(idx).get(i)).v.val;

		if ( highestVal != -1 )
			return bestCard;

		for ( i = 0; i < h.get(idx).size(); ++i )
			if ( h.get(idx).get(i).v.val > highestVal || h.get(idx).get(i).v.val == highestVal && h.get(idx).get(i).s.getRank() > bestCard.s.getRank() ) 
				highestVal = (bestCard = h.get(idx).get(i)).v.val;
		return bestCard;
	}

	int oneRoundWinner( int lead ) {
		int winner = -1,i,j,k,highestVal = -1,who[] = new int[5];
		Card lastPlayed = null, bestCard = null;
		Card []x = new Card[5];
		Suits s = null;
		boolean isTrumped = false;

		dealt = new ArrayList<Card>();

		for ( i = 0; i < 5; dealt.add(x[k]=lastPlayed), ++i ) {
			k = (lead+i)%5;
			if ( i == 0 ) {
				lastPlayed = firstMove(lead);
				leadSuit = s = lastPlayed.s;
				h.get(lead).remove(lastPlayed);
			}
			else {
				lastPlayed = nextMove(lastPlayed,k);
				h.get(k).remove(lastPlayed);
			}
		}
		for ( i = 0; i < 5 & !isTrumped; isTrumped|=(x[i++].s==trumpSuit) );
		if ( isTrumped ) {
			for ( i = 0; i < 5; ++i )
				if ( x[i].s == trumpSuit && x[i].v.val > highestVal ) {
					highestVal = x[i].v.val;
					bestCard = x[i];
					winner = i;
				}
		}
		else {
			assert highestVal == -1;
			for ( i = 0; i < 5; ++i )
				if ( x[i].s == s && x[i].v.val > highestVal ) {
					highestVal = x[i].v.val;
					bestCard = x[i];
					winner = i;
				}
		}
		if ( DBG ) {
			for ( i = 0; i < 5; ++i )
				if ( bestCard == x[i] )
					System.out.print(x[i]+"("+i+")"+"*"+" ");
				else System.out.print(x[i]+"("+i+")"+" ");
			System.out.println("\nWinner is "+winner+", with "+x[winner]);
		}
		assert winner != -1;
		return winner;
	}

	void countScore( int idx ) {
		for ( Card c: dealt )
			if ( c.s == Suits.HEARTS )
				score[idx] += c.v.val;
	}

	void go() throws Exception {
		int i,j,k,lead;
		String s;
		while ( scan.hasNext() && !(s=scan.next()).equals("#") ) {
			h = new TreeMap<Integer,List<Card>>();
			for ( i = 0, c[i++] = new Card(s); i < A; c[i++] = new Card(scan.next()) );
			assert i == A;
			for ( k = 0; k < 5; score[k] = 0, h.put(k++,new ArrayList<Card>()) );
			for ( i = 0; i < A-2; )
				for ( k = 0; k < 5; h.get(k++).add(c[i++]) );
			assert i == A-2;
			trumpSuit = decideTrump(c[i],c[i+1]);
			for ( lead = 0, k = 0; k < 10; ++k ) {
				countScore(lead = oneRoundWinner(lead));
			}
			for ( j = 4, i = 0; i < 5; ++i, ++j )
				System.out.printf("%3d",score[(j)%5]);
			System.out.println();
		}
	}
}



