package apps;

import structures.*;
import java.util.ArrayList;

public class MST {
	
	/**
	 * Initializes the algorithm by building single-vertex partial trees
	 * 
	 * @param graph Graph for which the MST is to be found
	 * @return The initial partial tree list
	 */
	public static PartialTreeList initialize(Graph graph) {
	
		/* COMPLETE THIS METHOD */


		PartialTreeList ret=new PartialTreeList();
        for(int a=0 ;a<=(graph.vertices.length)-1;a++){
            Vertex temp=graph.vertices[a];
			Vertex.Neighbor wtf=graph.vertices[a].neighbors;
            PartialTree temp2=new PartialTree(temp);
            while(wtf!=null){
                PartialTree.Arc temp3=new PartialTree.Arc(temp,wtf.vertex,wtf.weight);
                temp2.getArcs().insert(temp3);
                wtf=wtf.next;
            }

            ret.append(temp2);

        }
        return ret;
	}

	/**
	 * Executes the algorithm on a graph, starting with the initial partial tree list
	 * 
	 * @param ptlist Initial partial tree list
	 * @return Array list of all arcs that are in the MST - sequence of arcs is irrelevant
	 */
	public static ArrayList<PartialTree.Arc> execute(PartialTreeList ptlist) {
  		ArrayList<PartialTree.Arc> ret=new ArrayList<PartialTree.Arc>();
		while(ptlist.size()!=1) {
			PartialTree w = ptlist.remove();
			while (gotp(w.getArcs().getMin().v2).equals(w.getRoot())) {
				w.getArcs().deleteMin();
			}
			ret.add(w.getArcs().getMin());
			w.merge(ptlist.removeTreeContaining(w.getArcs().getMin().v2));
			ptlist.append(w);
		}


		return ret;
	}
	private static Vertex gotp(Vertex e){

		while(true){
			if(e.equals(e.parent)){
				break;
			}
			e=e.parent;
		}
      return e;

	}


}
