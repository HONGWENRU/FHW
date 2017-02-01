package search;

import java.io.*;
import java.util.*;

/**
 * This class encapsulates an occurrence of a keyword in a document. It stores the
 * document name, and the frequency of occurrence in that document. Occurrences are
 * associated with keywords in an index hash table.
 * 
 * @author Sesh Venugopal
 * 
 */
class Occurrence {
	/**
	 * Document in which a keyword occurs.
	 */
	String document;
	
	/**
	 * The frequency (number of times) the keyword occurs in the above document.
	 */
	int frequency;
	
	/**
	 * Initializes this occurrence with the given document,frequency pair.
	 * 
	 * @param doc Document name
	 * @param freq Frequency
	 */
	public Occurrence(String doc, int freq) {
		document = doc;
		frequency = freq;
	}
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		return "(" + document + "," + frequency + ")";
	}
}

/**
 * This class builds an index of keywords. Each keyword maps to a set of documents in
 * which it occurs, with frequency of occurrence in each document. Once the index is built,
 * the documents can searched on for keywords.
 *
 */
public class LittleSearchEngine {
	
	/**
	 * This is a hash table of all keywords. The key is the actual keyword, and the associated value is
	 * an array list of all occurrences of the keyword in documents. The array list is maintained in descending
	 * order of occurrence frequencies.
	 */
	HashMap<String,ArrayList<Occurrence>> keywordsIndex;
	
	/**
	 * The hash table of all noise words - mapping is from word to itself.
	 */
	HashMap<String,String> noiseWords;
	
	/**
	 * Creates the keyWordsIndex and noiseWords hash tables.
	 */
	public LittleSearchEngine() {
		keywordsIndex = new HashMap<String,ArrayList<Occurrence>>(1000,2.0f);
		noiseWords = new HashMap<String,String>(100,2.0f);
	}
	
	/**
	 * This method indexes all keywords found in all the input documents. When this
	 * method is done, the keywordsIndex hash table will be filled with all keywords,
	 * each of which is associated with an array list of Occurrence objects, arranged
	 * in decreasing frequencies of occurrence.
	 * 
	 * @param docsFile Name of file that has a list of all the document file names, one name per line
	 * @param noiseWordsFile Name of file that has a list of noise words, one noise word per line
	 * @throws FileNotFoundException If there is a problem locating any of the input files on disk
	 */
	public void makeIndex(String docsFile, String noiseWordsFile) 
	throws FileNotFoundException {
		// load noise words to hash table
		Scanner sc = new Scanner(new File(noiseWordsFile));
		while (sc.hasNext()) {
			String word = sc.next();
			noiseWords.put(word,word);
		}
		
		// index all keywords
		sc = new Scanner(new File(docsFile));
		while (sc.hasNext()) {
			String docFile = sc.next();
			HashMap<String,Occurrence> kws = loadKeyWords(docFile);
			mergeKeyWords(kws);
		}
		
	}

	/**
	 * Scans a document, and loads all keywords found into a hash table of keyword occurrences
	 * in the document. Uses the getKeyWord method to separate keywords from other words.
	 * 
	 * @param docFile Name of the document file to be scanned and loaded
	 * @return Hash table of keywords in the given document, each associated with an Occurrence object
	 * @throws FileNotFoundException If the document file is not found on disk
	 */
	public HashMap<String,Occurrence> loadKeyWords(String docFile) 
	throws FileNotFoundException {
		// COMPLETE THIS METHOD
		// THE FOLLOWING LINE HAS BEEN ADDED TO MAKE THE METHOD COMPILE
		HashMap<String, Occurrence> ret= new HashMap<String, Occurrence>();
		Scanner sc = new Scanner(new File(docFile));
		while (sc.hasNext()){
			String raw=sc.next();
			raw=getKeyWord(raw);
			if(raw==null){ continue;}
			if(ret.containsKey(raw)){
			   ret.get(raw).frequency++;
				continue;
			}
			else if (!ret.containsKey(raw)){
				Occurrence temp=new Occurrence(docFile, 1);
				ret.put(raw, temp);
				continue;
				
			}
			}
		sc.close();
		
		
		
		
		return ret;
	}
	
	/**
	 * Merges the keywords for a single document into the master keywordsIndex
	 * hash table. For each keyword, its Occurrence in the current document
	 * must be inserted in the correct place (according to descending order of
	 * frequency) in the same keyword's Occurrence list in the master hash table. 
	 * This is done by calling the insertLastOccurrence method.
	 * 
	 * @param kws Keywords hash table for a document
	 */
	public void mergeKeyWords(HashMap<String,Occurrence> kws) {
		// COMPLETE THIS METHOD
      Set<String> keys=kws.keySet();
		for(String key:keys){
			if(keywordsIndex.containsKey(key)){
			keywordsIndex.get(key).add(kws.get(key));
			insertLastOccurrence(keywordsIndex.get(key));
			continue;}
			else if(!keywordsIndex.containsKey(key)){
				ArrayList<Occurrence> temp= new ArrayList<Occurrence>();
				temp.add(kws.get(key));
				keywordsIndex.put(key, temp);
				continue;
				}
		}
		}
	
	/**
	 * Given a word, returns it as a keyword if it passes the keyword test,
	 * otherwise returns null. A keyword is any word that, after being stripped of any
	 * TRAILING punctuation, consists only of alphabetic letters, and is not
	 * a noise word. All words are treated in a case-INsensitive manner.
	 * 
	 * Punctuation characters are the following: '.', ',', '?', ':', ';' and '!'
	 * 
	 * @param word Candidate word
	 * @return Keyword (word without trailing punctuation, LOWER CASE)
	 */
	public String getKeyWord(String word) {
		// COMPLETE THIS METHOD
		// THE FOLLOWING LINE HAS BEEN ADDED TO MAKE THE METHOD COMPILE
		if(word.contains(" ")){return null;}
		if(!containletter(word)){return null;}
		for(int i=0;i<=(word.length()-1);i++){
			if(!Character.isAlphabetic(word.charAt(i))&&!ispunnction(word.charAt(i))){
				return null;}
		}
		if(containpun(word)&&Character.isAlphabetic(word.charAt(word.length()-1))){
			return null;
		}
		String ret=word.replaceAll("[^a-zA-Z]+", "");
		ret=ret.toLowerCase();
		if(noiseWords.containsKey(ret)){
			return null;}
		return ret;
	}
	
	/**
	 * Inserts the last occurrence in the parameter list in the correct position in the
	 * same list, based on ordering occurrences on descending frequencies. The elements
	 * 0..n-2 in the list are already in the correct order. Insertion of the last element
	 * (the one at index n-1) is done by first finding the correct spot using binary search, 
	 * then inserting at that spot.
	 * 
	 * @param occs List of Occurrences
	 * @return Sequence of mid point indexes in the input list checked by the binary search process,
	 *         null if the size of the input list is 1. This returned array list is only used to test
	 *         your code - it is not used elsewhere in the program.
	 */
	public ArrayList<Integer> insertLastOccurrence(ArrayList<Occurrence> occs) {
		// COMPLETE THIS METHOD
		// THE FOLLOWING LINE HAS BEEN ADDED TO MAKE THE METHOD COMPILE
		if(occs==null){return null;}
		int insertfre=occs.get(occs.size()-1).frequency;
		ArrayList<Integer> ret=new ArrayList<Integer>(); 
		 int low = 0;
		 int high = occs.size() - 2;
		 int middle=0;
		           while(high >= low) {
		               middle = (low + high) / 2;
		              ret.add(middle);
		              if(occs.get(middle).frequency == insertfre) {
		                  break;
		              }
		              if(occs.get(middle).frequency > insertfre) {
		                  low = middle + 1;continue;
		              }
		              if(occs.get(middle).frequency < insertfre) {
		                  high = middle - 1;continue;}
		           }
		           
		          if(high>=low){occs.add(middle,occs.get(occs.size()-1));}
		       if (high<low){occs.add(low,occs.get(occs.size()-1));}
		       occs.remove((occs.size()-1));
		        
		    return ret;
	}
         private boolean ispunnction(char i){
		if(i=='.'||i==','||i=='?'||i==':'||i==';'||i=='!'){
			
		return true;
		}
		else return false;
			
	}
         private boolean containpun(String e){
        	 for(int b=0; b<=(e.length()-1);b++){
        		     char i=e.charAt(b);
        		if(i=='.'||i==','||i=='?'||i==':'||i==';'||i=='!'){
        			return true;
        		}
        		 
        		 
        	 }
        	 
        	 
        	 
        	 return false;
        	 
         }
         private boolean containletter(String e){
        	 for(int i=0;i<=(e.length()-1);i++){
        		 if(Character.isLetter(e.charAt(i))){
        			 
        			 return true;
        		 }
        		 
        		 
        	 }
        	 
        	 return false;
        	 
         }
	
	/**
	 * Search result for "kw1 or kw2". A document is in the result set if kw1 or kw2 occurs in that
	 * document. Result set is arranged in descending order of occurrence frequencies. (Note that a
	 * matching document will only appear once in the result.) Ties in frequency values are broken
	 * in favor of the first keyword. (That is, if kw1 is in doc1 with frequency f1, and kw2 is in doc2
	 * also with the same frequency f1, then doc1 will appear before doc2 in the result. 
	 * The result set is limited to 5 entries. If there are no matching documents, the result is null.
	 * 
	 * @param kw1 First keyword
	 * @param kw1 Second keyword
	 * @return List of NAMES of documents in which either kw1 or kw2 occurs, arranged in descending order of
	 *         frequencies. The result size is limited to 5 documents. If there are no matching documents,
	 *         the result is null.
	 */
	public ArrayList<String> top5search(String kw1, String kw2) {
		// COMPLETE THIS METHOD
		// THE FOLLOWING LINE HAS BEEN ADDED TO MAKE THE METHOD COMPILE
		ArrayList<Occurrence> k1=keywordsIndex.get(kw1);
		ArrayList<Occurrence> k2=keywordsIndex.get(kw2);
		if(k1==null&&k2==null){return null;}
		ArrayList<String> ret=new ArrayList<String>();
		int k1index=0,k2index=0;
		if(k1!=null&&k2!=null){
		while((k1index<=(k1.size()-1)||k2index<=(k2.size()-1))&&ret.size()<5){
			if(k1index<=(k1.size()-1)&&k2index<=(k2.size()-1)){
			if(k1.get(k1index).frequency>k2.get(k2index).frequency){
			if(!ret.contains(k1.get(k1index).document)){
					ret.add(k1.get(k1index).document);
					k1index++;continue;}
				else if(ret.contains(k1.get(k1index).document)){
				k1index++;continue;}

			}
			if(k1.get(k1index).frequency<k2.get(k2index).frequency) {
				if (!ret.contains(k2.get(k2index).document)) {
					ret.add(k2.get(k2index).document);
					k2index++;
					continue;
				}
				else if(ret.contains(k2.get(k2index).document)){
					k2index++;continue;}

			}
			if(k1.get(k1index).frequency==k2.get(k2index).frequency){
					if(!ret.contains(k1.get(k1index).document)){
							ret.add(k1.get(k1index).document);k1index++;continue;}
					else if(!ret.contains(k2.get(k2index).document)){ ret.add(k2.get(k2index).document);k1index++;k2index++;continue;}
				    else {k1index++;k2index++;continue;}
					}
			}
			else if (k1index<=(k1.size()-1)&&k2index>(k2.size()-1)){
				if(!ret.contains(k1.get(k1index).document)){
					ret.add(k1.get(k1index).document);
					k1index++;continue;}
				else if(ret.contains(k1.get(k1index).document)){
					k1index++;continue;}

			}
			else if (k1index>(k1.size()-1)&&k2index<=(k2.size()-1)){
					if (!ret.contains(k2.get(k2index).document)) {
						ret.add(k2.get(k2index).document);
						k2index++;
						continue;
					}
					else if(ret.contains(k2.get(k2index).document)){
						k2index++;continue;}

			}
			}
			}
		
		
		if(k1==null&&k2!=null){
			while(ret.size()<5&&k2index<=(k2.size()-1)){
				if (!ret.contains(k2.get(k2index).document)) {
					ret.add(k2.get(k2index).document);
					k2index++;
					continue;
				}
				
			}
}
		if(k1!=null&&k2==null){
			while(ret.size()<5&&k1index<=(k1.size()-1)){
				if (!ret.contains(k1.get(k1index).document)) {
					ret.add(k1.get(k1index).document);
					k1index++;
					continue;
				}
				
			}
}		

		return ret;
	}
}
