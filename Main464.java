/*
 * 464. Sentence/Phrase Generator
 * TOPIC: ad hoc
 * status: Accepted
 * <sentence> ::= <trans-sentence> | <sentence> ::= <intrans-sentence>
 * <trans-sentence> ::= <subject> <verb-phrase> <object> <prep-phrase>
 * <intrans-sentence> ::= <subject> <intrans-verb-phrase> <prep-phrase>
 * <subject> ::= <noun-phrase>
 * <object> ::= <noun-phrase>
 * <noun-phrase> ::= <article> <modified-noun>
 * <modified-noun> ::= <noun> | <modifier> <noun>
 * <modifier> ::= <adjective> | <adverb> <adjective>
 * <verb-phrase> ::= <trans-verb> | <adverb> <trans-verb>
 * <intrans-verb-phrase> ::= <intrans-verb> | <adverb> <intrans-verb>
 * <prep-phrase> ::= <preposition> <noun-phrase> | <empty>
 * <noun> ::= man | dog | fish | computer | waves
 * <trans-verb> ::= struck | saw | bit | took
 * <intrans-verb> ::= slept | jumped | walked | swam
 * <article> ::= the | a
 * <adjective> ::= green | small | rabid | quick
 * <adverb> ::= nearly | suddenly | restlessly
 * <preposition> ::= on | over | through
 * <empty> ::= "":
 */
import java.io.*;
import java.util.*;


class Main {
	int k;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String []prep = {"on","over","through"};
 	String []adverb = {"nearly","suddenly","restlessly"};
 	String []article = {"the","a"};
 	String []intrans_verb = {"slept","jumped","walked","swam"};
 	String []trans_verb = {"struck","saw","bit","took"};
 	String []noun = {"man","dog","fish","computer","waves"};
	String []adj = {"green","small","rabid","quick"};
	String getPreposition() { return prep[(++k)%3]; }
	String getAdverb() { return adverb[(++k)%3]; }
	String getArticle() { return article[(++k)%2]; }
	String getIntransVerb() { return intrans_verb[(++k)%4]; }
	String getTransVerb() { return trans_verb[(++k)%4]; }
	String getNoun() { return noun[(++k)%5]; }
	String getAdjective() { return adj[(++k)%4]; }
	/*
 	 * <noun-phrase> ::= <article> <modified-noun>
 	 * <intrans-sentence> ::= <subject> <intrans-verb-phrase> <prep-phrase>
 	 * <trans-sentence> ::= <subject> <verb-phrase> <object> <prep-phrase>
 	 * <sentence> ::= <trans-sentence> | <sentence> ::= <intrans-sentence>
	 */
	String getSent() {
		if ( ((++k)&1) == 0 )
			return getTransSent();
		return getIntransSent();
	}
	String getTransSent() { 
		String s = getSubject()+" "+getVerbPhrase()+" "+getObject();
		String t = getPrepPhrase(); 
		if ( !t.equals("") )
			return s+" "+t;
		return s;
	}
	String getIntransSent() {
		String s = getSubject()+" "+getIntransVerbPhrase();
		String t = getPrepPhrase();
		if ( !t.equals("") )
			return s+" "+t;
		return s;
	}
	String getObject() { return getNounPhrase(); }
	String getSubject() { return getNounPhrase(); }
	String empty() { return ""; }
	String getNounPhrase( ) {
		return getArticle()+" "+getModifiedNoun();
	}
	/*
 	 * <prep-phrase> ::= <preposition> <noun-phrase> | <empty>
 	 * <intrans-verb-phrase> ::= <intrans-verb> | <adverb> <intrans-verb>
 	 * <verb-phrase> ::= <trans-verb> | <adverb> <trans-verb>
 	 * <modifier> ::= <adjective> | <adverb> <adjective>
 	 * <modified-noun> ::= <noun> | <modifier> <noun>
	 */
	String getModifiedNoun() {
		if ( ((++k)&1) == 0 )
			return getNoun();
		return getModifier()+" "+getNoun();
	}
	String getModifier() {
		if ( ((++k)&1) == 0 )
			return getAdjective();
		return getAdverb()+" "+getAdjective();
	}
	String getVerbPhrase() {
		if ( ((++k)%2) == 0 )
			return getTransVerb();
		return getAdverb()+" "+getTransVerb();
	}
	String getIntransVerbPhrase() {
		if ( ((++k)%2) == 0 ) 
			return getIntransVerb();
		return getAdverb()+" "+getIntransVerb();
	}
	String getPrepPhrase() {
		if ( ((++k)%2) == 0 )
			return getPreposition()+" "+getNounPhrase();
		return empty(); 
	}
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	String f( String s ) {
		if ( s.equalsIgnoreCase("sentence") )
			return getSent();
		if ( s.equalsIgnoreCase("trans-sentence") )
			return getTransSent();
		if ( s.equalsIgnoreCase("intrans-sentence") )
			return getIntransSent();
		if ( s.equalsIgnoreCase("subject") )
			return getSubject();
		if ( s.equalsIgnoreCase("object") )
			return getObject();
		if ( s.equalsIgnoreCase("noun-phrase") )
			return getNounPhrase();
		if ( s.equalsIgnoreCase("modified-noun") )
			return getModifiedNoun();
		if ( s.equalsIgnoreCase("modifier") )
			return getModifier();
		if ( s.equalsIgnoreCase("verb-phrase") )
			return getVerbPhrase();
		if ( s.equalsIgnoreCase("intrans-verb-phrase") )
			return getIntransVerbPhrase();
		if ( s.equalsIgnoreCase("prep-phrase") )
			return getPrepPhrase();
		if ( s.equalsIgnoreCase("noun") )
			return getNoun();
		if ( s.equalsIgnoreCase("trans-verb") )
			return getTransVerb();
		if ( s.equalsIgnoreCase("article") )
			return getArticle();
		if ( s.equalsIgnoreCase("adjective") )
			return getAdjective();
		if ( s.equalsIgnoreCase("intrans-verb") )
			return getIntransVerb();
		if ( s.equalsIgnoreCase("adverb") )
			return getAdverb();
		if ( s.equalsIgnoreCase("preposition") )
			return getPreposition();
		return empty();
	}
	void go() throws Exception {
		String s;
		while ( (s=br.readLine()) != null ) {
			StringTokenizer st = new StringTokenizer(s);
			System.out.println(f(st.nextToken()));
		}
	}
};

