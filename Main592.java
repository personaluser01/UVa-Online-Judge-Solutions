/*
 * 592. Island of Logic
 * TOPIC:
 * status: RTE
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;

class Main {
	BufferedReader br;
	Pattern pa = Pattern.compile("\\(A=(\\d)\\)");
	Pattern pb = Pattern.compile("\\(B=(\\d)\\)");
	Pattern pc = Pattern.compile("\\(C=(\\d)\\)");
	Pattern pd = Pattern.compile("\\(D=(\\d)\\)");
	Pattern pe = Pattern.compile("\\(E=(\\d)\\)");
	Pattern pf = Pattern.compile("\\(F=(\\d)\\)");
	static final String KONST_OR = "||", KONST_AND = "&&";
	int []Lower = new int[5], Upper = new int[5];

	final int DIVINE=0,EVIL=1,HUMAN=2,LYING=3,NOT_LYING=4,NOT_HUMAN=5,NOT_EVIL=6,NOT_DIVINE=7,DAY=0,NIGHT=1, A = 0, BE = 0, CE = 0, DE = 0, E = 0, TAIM = 5;
	int n,pos,cnt;
	int []var = new int[0x40];
	String BRACKETS( String t ) { 
		StringBuilder sb = new StringBuilder("(");
		sb.append(t);
		sb.append(")");
		return sb.toString();
	}
	String T;
	char []txt;

	Map<Integer,String> mp;

	String factory( int var_name, int val ) {
		int x = var_name|(val<<15);
		if ( mp.containsKey(x) )
			return mp.get(x);
		StringBuilder sb = new StringBuilder((char)(var_name+'A')+"=");
		sb.append(""+val);
		mp.put(x,BRACKETS(sb.toString()));
		return mp.get(x);
	}

	int getCode( String s ) {
		if ( s.equalsIgnoreCase("divine") ) return DIVINE;
		if ( s.equalsIgnoreCase("evil") ) return EVIL;
		if ( s.equalsIgnoreCase("human") ) return HUMAN;
		if ( s.equalsIgnoreCase("lying") ) return LYING;
		if ( s.equalsIgnoreCase("day") ) return DAY;
		return NIGHT;
	}

	String conj( String a, String b ) { 
		StringBuilder sb = new StringBuilder(a);
		sb.append(KONST_AND);
		sb.append(b);
		return sb.toString();
	}

	String disj( String a, String b ) { 
		StringBuilder sb = new StringBuilder(a);
		sb.append(KONST_OR);
		sb.append(b);
		return BRACKETS(sb.toString());
	}

	String TRUTHFUL( int k ) { 
		StringBuilder sb = new StringBuilder(factory(k,DIVINE));
		sb.append(KONST_OR);
		sb.append(conj(factory(k,HUMAN),factory(TAIM,DAY)));
		return BRACKETS(sb.toString());
	}

	String LIE( int k ) { 
		StringBuilder sb = new StringBuilder(factory(k,EVIL));
		sb.append(KONST_OR);
		sb.append(conj(factory(k,HUMAN),factory(TAIM,NIGHT)));
		return BRACKETS(sb.toString());
	}

	String ANYTHING_BUT( int k, int val ) {
		if ( k == TAIM )
			return factory(k,val^1);
		if ( val == DIVINE )
			return disj(factory(k,HUMAN),factory(k,EVIL));
		if ( val == HUMAN )
			return disj(factory(k,EVIL),factory(k,DIVINE));
		if ( val == EVIL )
			return disj(factory(k,HUMAN),factory(k,DIVINE));
		return "";
	}

	String replaceOll( String s, int a, int b, int c, int d, int e, int f ) {
		Matcher m;
		String t = s;
		TreeMap<String,String> h = new TreeMap<String,String>();
		Set set;
		Iterator it;

		h.clear();
		m = pa.matcher(s);
		while ( m.find() ) 
			if ( Integer.parseInt(m.group(1)) != a )
				h.put(m.group(0),"0");
			else 
				h.put(m.group(0),"1");
		set = h.entrySet();
		it = set.iterator();
		while ( it.hasNext() ) {
			Map.Entry me = (Map.Entry)it.next();
			// System.out.println("Replacing "+(String)me.getKey()+" with "+(String)me.getValue());
			s = s.replaceAll((String)me.getKey(),(String)me.getValue());
		}

		h.clear();
		m = pb.matcher(s);
		while ( m.find() ) {
			if ( Integer.parseInt(m.group(1)) != b )
				h.put(m.group(0),"0");
			else 
				h.put(m.group(0),"1");
		}
		set = h.entrySet();
		it = set.iterator();
		while ( it.hasNext() ) {
			Map.Entry me = (Map.Entry)it.next();
			s = s.replaceAll((String)me.getKey(),(String)me.getValue());
		}

		h.clear();
		m = pc.matcher(s);
		while ( m.find() ) {
			if ( Integer.parseInt(m.group(1)) != c )
				h.put(m.group(0),"0");
			else 
				h.put(m.group(0),"1");
		}
		set = h.entrySet();
		it = set.iterator();
		while ( it.hasNext() ) {
			Map.Entry me = (Map.Entry)it.next();
			s = s.replaceAll((String)me.getKey(),(String)me.getValue());
		}

		h.clear();
		m = pd.matcher(s);
		while ( m.find() ) {
			if ( Integer.parseInt(m.group(1)) != d )
				h.put(m.group(0),"0");
			else 
				h.put(m.group(0),"1");
		}
		set = h.entrySet();
		it = set.iterator();
		while ( it.hasNext() ) {
			Map.Entry me = (Map.Entry)it.next();
			s = s.replaceAll((String)me.getKey(),(String)me.getValue());
		}

		h.clear();
		m = pe.matcher(s);
		while ( m.find() ) {
			if ( Integer.parseInt(m.group(1)) != e )
				h.put(m.group(0),"0");
			else 
				h.put(m.group(0),"1");
		}
		set = h.entrySet();
		it = set.iterator();
		while ( it.hasNext() ) {
			Map.Entry me = (Map.Entry)it.next();
			s = s.replaceAll((String)me.getKey(),(String)me.getValue());
		}

		h.clear();
		m = pf.matcher(s);
		while ( m.find() ) {
			if ( Integer.parseInt(m.group(1)) != f )
				h.put(m.group(0),"0");
			else 
				h.put(m.group(0),"1");
		}
		set = h.entrySet();
		it = set.iterator();
		while ( it.hasNext() ) {
			Map.Entry me = (Map.Entry)it.next();
			s = s.replaceAll((String)me.getKey(),(String)me.getValue());
		}
		return "1"+s;
	}

	public static void main( String [] args ) throws Exception { new Main().go(); }

	String G( TreeSet<Integer> t ) {
		Iterator<Integer> it = t.iterator();
		switch ( it.next() ) {
			case 0:   return "divine";
			case 1:   return "evil";
			case 2:   return "human";
			default:  return "";
		}
	}

	String H( TreeSet<Integer> t ) {
		Iterator<Integer> it = t.iterator();
		switch ( it.next() ) {
			case 0:   return "day";
			case 1:   return "night";
			default:  return "";
		}
	}

	boolean []present = new boolean[0x40];
	int U( int k ) {
		if ( k == 5 ) {
			if ( present[k] )
				return NIGHT;
			return DAY;
		}
		if ( present[k] )
			return HUMAN;
		return DIVINE;
	}

	String Triple( String a, String b, String c ) {
		StringBuilder sb = new StringBuilder();
		sb.append(a);
		sb.append(b);
		sb.append(c);
		return sb.toString();
	}

	void go() throws Exception {
		int i,j,k,val,cs = 0,e = 0,l;
		boolean ok;
		String nn;
		mp = new TreeMap<Integer,String>();
		if ( br == null )
			br = new BufferedReader(new InputStreamReader(System.in,"ISO-8859-1"));
		Pattern p1 = Pattern.compile("i\\s+am\\s+(not )?\\s*(divine|human|evil|lying)");
		Pattern p2 = Pattern.compile("([a-z])\\s+is\\s+(not )?\\s*(divine|human|evil|lying)");
		Pattern p3 = Pattern.compile("it\\s+is\\s+(day|night)");
		Pattern p4 = Pattern.compile("([a-z])");
		for ( int vr = 0; vr < 5; Lower[vr] = DIVINE, Upper[vr++] = HUMAN );
		while ( (nn=br.readLine())!=null && (n=Integer.parseInt(new StringTokenizer(nn).nextToken()))!=0 ) {
			StringBuilder sb = new StringBuilder();
			System.out.println("Conversation #"+(++cs));
			ok = true;
			for ( i = 0; i <= 5; ++i ) present[i] = false;
			for ( i = 0; i < n; ++i ) {
				String t = br.readLine();
				t = t.toLowerCase();
				if ( !ok ) { T = ""; continue ; }
				if ( t.indexOf("it") != -1 )
					present[5] = true;
				for ( char c: t.toCharArray() )
					if ( 'a' <= c && c <= 'z' )
						present[c-'a'] = true;
				Matcher m1 = p1.matcher(t.substring(t.indexOf(":")));
				Matcher m2 = p2.matcher(t.substring(t.indexOf(":")));
				Matcher m3 = p3.matcher(t.substring(t.indexOf(":")));
				Matcher m4 = p4.matcher(t);
				m4.find();
				k = m4.group(1).charAt(0)-'a';
				if ( k >= 5 ) continue ;
				if ( m1.find() ) {
					e = getCode(m1.group(2));
					if ( m1.group(1) != null ) {
						// m1.group(1).equals("not");
						if ( e == LYING ) {
							sb.append(KONST_AND+BRACKETS(Triple(TRUTHFUL(k),KONST_OR,factory(k,EVIL))));
						}
						else if ( e == DIVINE ) {
							sb.append(KONST_AND+conj(factory(TAIM,DAY),factory(k,HUMAN)));
						}
						else if ( e == HUMAN ) {
							sb.append(KONST_AND+BRACKETS(Triple(factory(k,DIVINE),KONST_OR,conj(factory(TAIM,NIGHT),factory(k,HUMAN)))));
						}
						else {
							sb.append(KONST_AND+BRACKETS(Triple(factory(k,DIVINE),KONST_OR,conj(factory(TAIM,DAY),factory(k,HUMAN)))+factory(k,EVIL)));
						}
					}
					else {
						if ( e == LYING ) {
							ok = false;
						}
						else if ( e == DIVINE ) {
							sb.append(KONST_AND+BRACKETS(Triple(factory(k,DIVINE),KONST_OR,LIE(k))));
						}
						else if ( e == HUMAN ) {
							sb.append(KONST_AND+BRACKETS(conj(factory(k,HUMAN),Triple(factory(TAIM,DAY),KONST_OR,factory(k,EVIL)))));
						}
						else {
							sb.append(KONST_AND+conj(factory(k,HUMAN),factory(TAIM,NIGHT)));
							Lower[k] = HUMAN;
						}
					}
				}
				else if ( m2.find() ) {
					j = m2.group(1).charAt(0)-'a';
					if ( j >= 5 ) continue ;
					e = getCode(m2.group(3));
					if ( m2.group(2) != null ) {
						// m2.group(2).equals("not");
						if ( e == LYING ) sb.append(KONST_AND+BRACKETS(Triple(BRACKETS(Triple(TRUTHFUL(k),KONST_AND,TRUTHFUL(j))),KONST_OR,BRACKETS(Triple(LIE(k),KONST_AND,LIE(j))))));
						else if ( e == DIVINE ) 
							sb.append(KONST_AND+
								BRACKETS(
												BRACKETS(
														Triple(Triple(LIE(k),KONST_AND,factory(j,DIVINE)),KONST_OR,BRACKETS(Triple(TRUTHFUL(k),KONST_AND,ANYTHING_BUT(j,DIVINE))))
														)
										)
								);
						else if ( e == HUMAN ) 
							sb.append(KONST_AND+BRACKETS(Triple(BRACKETS(Triple(LIE(k),KONST_AND,factory(j,HUMAN))),KONST_OR,BRACKETS(Triple(TRUTHFUL(k),KONST_AND,ANYTHING_BUT(j,HUMAN))))));
						else
							sb.append(KONST_AND+
											BRACKETS(
															Triple(BRACKETS(Triple(LIE(k),KONST_AND,factory(j,EVIL))),KONST_OR,BRACKETS(Triple(TRUTHFUL(k),KONST_AND,ANYTHING_BUT(j,EVIL))))
													)
											);
					}
					else {
						if ( e == LYING ) sb.append(KONST_AND+BRACKETS(Triple(BRACKETS(Triple(TRUTHFUL(k),KONST_AND,LIE(j))),KONST_OR,BRACKETS(Triple(LIE(k),KONST_AND,TRUTHFUL(j))))));
						else if ( e == DIVINE )
							sb.append(KONST_AND+BRACKETS(Triple(BRACKETS(Triple(TRUTHFUL(k),KONST_AND,factory(j,DIVINE))),KONST_OR,BRACKETS(Triple(LIE(k),KONST_AND,ANYTHING_BUT(j,DIVINE))))));
						else if ( e == HUMAN )
							sb.append(KONST_AND+BRACKETS(Triple(BRACKETS(Triple(TRUTHFUL(k),KONST_AND,factory(j,HUMAN))),KONST_OR,BRACKETS(Triple(LIE(k),KONST_AND,ANYTHING_BUT(j,HUMAN))))));
						else 
							sb.append(KONST_AND+BRACKETS(Triple(BRACKETS(Triple(TRUTHFUL(k),KONST_AND,factory(j,EVIL))),KONST_OR,BRACKETS(Triple(LIE(k),KONST_AND,ANYTHING_BUT(j,EVIL))))));
					}
				}
				else if ( m3.find() ) {
					val = getCode(m3.group(1));
					sb.append(KONST_AND+BRACKETS(Triple(BRACKETS(Triple(TRUTHFUL(k),KONST_AND,factory(TAIM,val))),KONST_OR,BRACKETS(Triple(LIE(k),KONST_AND,factory(TAIM,val^1))))));
				}
			}
			T = sb.toString();
			if ( !ok || T==null || T.equals("") ) {
				System.out.println("This is impossible.\n");
				continue ;
			}
			// System.out.println(T);
			TreeSet<Integer> ma = new TreeSet<Integer>();
			TreeSet<Integer> mb = new TreeSet<Integer>();
			TreeSet<Integer> mc = new TreeSet<Integer>();
			TreeSet<Integer> md = new TreeSet<Integer>();
			TreeSet<Integer> me = new TreeSet<Integer>();
			TreeSet<Integer> mf = new TreeSet<Integer>();
			ma.clear();
			mb.clear();
			mc.clear();
			md.clear();
			me.clear();
			mf.clear();
			for ( int vr = 0; vr < 5; ++vr )
				if ( !present[vr] )
					Lower[vr] = Upper[vr] = HUMAN;
			for ( i = Lower[A]; i <= Upper[A]; ++i )
			for ( j = Lower[BE]; j <= Upper[BE]; ++j )
			for ( k = Lower[CE]; k <= Upper[CE]; ++k )
			for ( l = Lower[DE]; l <= Upper[DE]; ++l )
			for ( e = Lower[E]; e <= Upper[E]; ++e )
				for ( val = DAY; val <= NIGHT; ++val ) {
					String S = replaceOll(T,i,j,k,l,e,val);
					// System.out.println(S);
					ScriptEngineManager sem = new ScriptEngineManager();
					ScriptEngine se = sem.getEngineByName("JavaScript");
					if ( ((int)se.eval(S)) == 1 ) {
						// System.out.println(T+" "+S);
						ma.add(i);
						mb.add(j);
						mc.add(k);
						md.add(l);
						me.add(e);
						mf.add(val);
					}
					// System.out.println(S);
				}
			if ( ma.size() == 0 && mb.size() == 0 && mc.size() == 0 && md.size() == 0 && me.size() == 0 && mf.size() == 0 ) {
				System.out.println("This is impossible.\n");
				continue ;
			}
			cnt = 0;
			if ( ma.size() == 1 && present[0] ) {
				System.out.println("A is "+G(ma)+".");
				++cnt;
			}
			if ( mb.size() == 1 && present[1] ) {
				System.out.println("B is "+G(mb)+".");
				++cnt;
			}
			if ( mc.size() == 1 && present[2] ) {
				System.out.println("C is "+G(mc)+".");
				++cnt;
			}
			if ( md.size() == 1 && present[3] ) {
				System.out.println("D is "+G(md)+".");
				++cnt;
			}
			if ( me.size() == 1 && present[4] ) {
				System.out.println("E is "+G(me)+".");
				++cnt;
			}
			if ( mf.size() == 1 ) {
				System.out.println("It is "+H(mf)+".");
				++cnt;
			}
			if ( cnt == 0 )
				System.out.println("No facts are deducible.");
			System.out.println("");
		}
	}
};

