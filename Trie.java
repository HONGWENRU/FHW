package structures;


import java.util.ArrayList;


/**
 * This class implements a compressed trie. Each node of the tree is a CompressedTrieNode, with fields for
 * indexes, first child and sibling.
 * 
 * @author Sesh Venugopal
 *
 */
public class Trie {
	
	
	/**
	 * Words indexed by this trie.
	 */
	ArrayList<String> words;
	
	/**
	 * Root node of this trie.
	 */
	TrieNode root;
	
	/**
	 * Initializes a compressed trie with words to be indexed, and root node set to
	 * null fields.
	 * 
//	 * @param words
	 */
	public Trie() {
		root = new TrieNode(null, null, null);
		words = new ArrayList<String>();
	}
	
	/**
	 * Inserts a word into this trie. Converts to lower case before adding.
	 * The word is first added to the words array list, then inserted into the trie.
	 * 
	 * @param word Word to be inserted.
	 */
	public void insertWord(String word) {
		/** COMPLETE THIS METHOD **/
	
	word=word.toLowerCase();
	words.add(word);
		Indexes target=new Indexes(words.indexOf(word),(short)0,(short)(word.length()-1));
		TrieNode targerN=new TrieNode(target,null,null);
	if(this.root.firstChild==null){
		int index=0;short startindex=0;short endindex=(short)(word.length()-1);
		Indexes need=new Indexes(index, startindex, endindex);
	 TrieNode child=new TrieNode(need, null,null);
	   this.root=new TrieNode(null, child, null);
	}
	else{
	TrieNode checksparent=this.root;
	TrieNode check=this.root.firstChild;
	while(true)	{
//		if(contain(getsubst(targerN), getsubst(check))&&check.firstChild==null){
//		    int a=findtheprindex(getsubst(targerN),getsubst(check));
//			Indexes tempi=new Indexes(check.substr.wordIndex,(short)0,(short)(a-1));
//			check.substr.endIndex=(short)(words.get(check.substr.wordIndex).length()-1);check.substr.startIndex+=(short)a;
//			targerN.substr.endIndex=(short)(words.get(targerN.substr.wordIndex).length()-1);targerN.substr.startIndex+=(short)a;
//			TrieNode temp=new TrieNode(tempi,null,null);
//			temp.sibling=check.sibling;
//			checksparent.firstChild=temp;temp.firstChild=check;check.sibling=targerN;break;
//			}
//			else
			while(true) {
				while (getsubst(targerN).contains(getsubst(check)) && check.firstChild != null) {
					targerN.substr.startIndex += (short) (findtheprindex(getsubst(targerN), getsubst(check)));
					checksparent = check;
					check = check.firstChild;
					continue;
				}
				while (check != null && !contain(getsubst(targerN), getsubst(check)) ) {
					check = check.sibling;
				}

				if (check!=null&&check.firstChild != null && getsubst(targerN).contains(getsubst(check))) {
				
					continue;
					
				}
				else if(check!=null && contain(getsubst(check), getsubst(targerN))){
					break;
				}
				if(check==null){
					break;
				}
		
			}
			if (check == null) {
				TrieNode temp = checksparent.firstChild;
				while (temp.sibling != null) {
					temp = temp.sibling;
				}

				temp.sibling = targerN;
				break;
			}
			if(check!=null){
				if(check==checksparent.firstChild&&check.firstChild==null){
					int c = findtheprindex(getsubst(check), getsubst(targerN));
					Indexes what = new Indexes(check.substr.wordIndex, check.substr.startIndex, (short) (check.substr.startIndex + c - 1));
					TrieNode what2 = new TrieNode(what, null, null);
					check.substr.endIndex = (short) (words.get(check.substr.wordIndex).length() - 1);
					check.substr.startIndex = (short) (check.substr.startIndex + c);
					targerN.substr.endIndex = (short) (words.get(targerN.substr.wordIndex).length() - 1);
					targerN.substr.startIndex = check.substr.startIndex;
					what2.sibling=checksparent.firstChild.sibling;
					checksparent.firstChild=what2;
					what2.firstChild=check;
					check.sibling=targerN;
					break;
				}
				else if(check==checksparent.firstChild&&check.firstChild!=null){
					
					int c = findtheprindex(getsubst(check), getsubst(targerN));
					Indexes what = new Indexes(check.substr.wordIndex, check.substr.startIndex, (short) (c-1));
					TrieNode what2 = new TrieNode(what, null, null);
		            check.substr.startIndex = (short) (what2.substr.endIndex+1);
					targerN.substr.endIndex = (short) (words.get(targerN.substr.wordIndex).length() - 1);
					targerN.substr.startIndex = check.substr.startIndex;
				    check.sibling=targerN;
				    what2.firstChild=check;
				    checksparent.firstChild=what2;
					break;
					}
				else {
					TrieNode temp = checksparent.firstChild;
					while (temp.sibling != check) {
						temp = temp.sibling;
					}
					int c = findtheprindex(getsubst(check), getsubst(targerN));
					Indexes what = new Indexes(check.substr.wordIndex, check.substr.startIndex, (short) (check.substr.startIndex + c - 1));
					TrieNode what2 = new TrieNode(what, null, null);
					check.substr.endIndex = (short) (words.get(check.substr.wordIndex).length() - 1);
					check.substr.startIndex = (short) (check.substr.startIndex + c);
					targerN.substr.endIndex = (short) (words.get(targerN.substr.wordIndex).length() - 1);
					targerN.substr.startIndex = check.substr.startIndex;
					what2.sibling = temp.sibling.sibling;
					temp.sibling = what2;
					what2.firstChild = check;
					check.sibling = targerN;
					break;
				}
			}

//	    else if(check.sibling!=null&&check.sibling.firstChild!=null){
//		checksparent=check.sibling;check=check.sibling.firstChild;continue;
//		}
//
//	    else if(check.sibling!=null&&check.sibling.firstChild==null){
//
//	    	Indexes shit=new Indexes(words.indexOf(getsubst(check.sibling)),check.sibling.substr.startIndex, (short)findtheprindex(word, getsubst(check.sibling)));
//	    	check.sibling.substr.startIndex=(short)findtheprindex(word, getsubst(check.sibling));
//	    	check.sibling.substr.endIndex=(short)(getsubst(check.sibling).length()-1);
//	    	Indexes ok=new Indexes(words.indexOf(word), (short)findtheprindex(word, getsubst(check.sibling)), (short)(word.length()-1));
//	    	TrieNode ok1=new TrieNode(ok, null, null);
//	    	TrieNode shit1=new TrieNode(shit,check.sibling, check.sibling.sibling);
//	    	check.sibling=shit1;shit1.firstChild.sibling=ok1;
//	    	break;
//
//	    }

	}
	
}
	
	
	}
	/**
	 * Given a string prefix, returns its "completion list", i.e. all the words in the trie
	 * that start with this prefix. For instance, if the tree had the words bear, bull, stock, and bell,
	 * the completion list for prefix "b" would be bear, bull, and bell; for prefix "be" would be
	 * bear and bell; and for prefix "bell" would be bell. (The last example shows that a prefix can be
	 * an entire word.) The order of returned words DOES NOT MATTER. So, if the list contains bear and
	 * bell, the returned list can be either [bear,bell] or [bell,bear]
	 * 
	 * @param prefix Prefix to be completed with words in trie
	 * @return List of all words in tree that start with the prefix, order of words in list does not matter.
	 *         If there is no word in the tree that has this prefix, null is returned.
	 */
	public ArrayList<String> completionList(String prefix) {
		/** COMPLETE THIS METHOD **/
		ArrayList<String> result=new ArrayList<String>();
		TrieNode temp=new TrieNode(null, null, null);
		temp=root.firstChild;
//		words.add(prefix);
//		Indexes prifixs=new Indexes(words.indexOf(prefix), (short)0, (short)(prefix.length()-1));
//		TrieNode prifixa=new TrieNode(prifixs, null, null);	
		trackthenode( temp, result,prefix);	
		return result;
	}
	
	
	public void print() {
		print(root, 1, words);
	}
	
	private static void print(TrieNode root, int indent, ArrayList<String> words) {
		if (root == null) {
			return;
		}
		for (int i=0; i < indent-1; i++) {
			System.out.print("    ");
		}
		
		if (root.substr != null) {
			System.out.println("      " + words.get(root.substr.wordIndex));
		}
		
		for (int i=0; i < indent-1; i++) {
			System.out.print("    ");
		}
		System.out.print(" ---");
		System.out.println("(" + root.substr + ")");
		
		for (TrieNode ptr=root.firstChild; ptr != null; ptr=ptr.sibling) {
			for (int i=0; i < indent-1; i++) {
				System.out.print("    ");
			}
			System.out.println("     |");
			print(ptr, indent+1, words);
		}
	}

private int findtheprindex(String a,String b){
	String s = a;
    String s2 = b;
    String small,large;
     if(s.length() > s2.length()) 
        {small = s2;large = s;}
      else
        {small = s;large = s2;}
    int index = 0;    
    for(char c: large.toCharArray())
    {
        if(index==small.length()) break;
        if(c != small.charAt(index)) break;
        index++;}
        return index;
    }
	
private boolean contain(String a,String b){
	if(a.charAt(0)==b.charAt(0)){
		return true;
	}
	return false;
}
private String getsubst(TrieNode a){
	String b;
	b=words.get(a.substr.wordIndex).substring((int)a.substr.startIndex,(int)(a.substr.endIndex+1));
	
	return b;
	
	
	
}

private void trackthenode(TrieNode temp, ArrayList<String> result,String prefix) {
	TrieNode T1=temp;
	while(T1!=null){

		if(T1.firstChild==null&&words.get(T1.substr.wordIndex).startsWith(prefix)){
		result.add(words.get(T1.substr.wordIndex));
		}
		else if (T1.firstChild!=null&&match(prefix, words.get(T1.substr.wordIndex).substring(0,T1.substr.endIndex+1))){
			trackthenode(T1.firstChild, result,prefix);
		}
		T1=T1.sibling;
	}

	return ;
	
	
	
	
//	while(temp!=null){
//		if(temp.firstChild!=null&&words.get(temp.substr.wordIndex).startsWith(prefix)){
//			trackthenode(prefix, temp, result);temp=temp.firstChild;continue;
//			}
//		else if(temp.firstChild!=null&&!words.get(temp.substr.wordIndex).startsWith(prefix)){
//		temp=temp.sibling;continue;}
//		else if(temp.firstChild==null&&words.get(temp.substr.wordIndex).startsWith(prefix)){
//			result.add(words.get(temp.substr.wordIndex));temp=temp.sibling;continue;
//			}
//		
//	}
	
}

private boolean match(String a, String b){
	int index=0;
	
	try{
	while(true){
		if(a.charAt(index)==b.charAt(index)){
			index++;continue;
		}else break;
		}
	}catch(IndexOutOfBoundsException e) {
		return true;
	}
	
	return false;
	
	
	
	
	
}
	
}

 

