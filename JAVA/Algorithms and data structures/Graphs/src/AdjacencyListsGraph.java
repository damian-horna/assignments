import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Stack;

public class AdjacencyListsGraph {

	private int v;
	private LinkedList<Integer>[] adjacencyLists; // array of LinkedLists

	public AdjacencyListsGraph(int[][] tab, int n) {
		v = n;
		adjacencyLists = new LinkedList[v];// v - number of LinkedLists in the
											// adjacencyLists array
		for (int i = 0; i < v; i++)
			adjacencyLists[i] = new LinkedList<Integer>();
		for (int i = 0; i < v; i++)
			for (int j = 0; j < v; j++)
				if (tab[i][j] == 1) adjacencyLists[i].add(j);
	}

	public ArrayList<Integer> toposortBFS() {

		PriorityQueue<Integer> q = new PriorityQueue<Integer>();
		ArrayList<Integer> result = new ArrayList<Integer>();

		int[] inDegree = new int[v];
		boolean[] visited = new boolean[v];
		Integer iter;

		// creates table of in-degrees for all vertices
		for (int i = 0; i < v; i++) {
			Iterator<Integer> it = adjacencyLists[i].iterator();
			while (it.hasNext()) {
				iter = it.next();
				inDegree[iter]++;
			}
		}

		// adds vertices with 0 in-degree to the queue
		for (int i = 0; i < v; i++)
			if (inDegree[i] == 0) {
				q.add(i);
				visited[i] = true;
			}

		// bfs - taking the first element with 0 in-degree in queue and deleting
		// the arcs
		while (q.size() > 0) {

			int vertex = q.poll();
			result.add(vertex);

			Iterator<Integer> it = adjacencyLists[vertex].iterator();
			while (it.hasNext()) {
				iter = it.next();
				if (visited[iter] == false) {
					inDegree[iter]--;
					if (inDegree[iter] == 0) {
						q.add(iter);
						visited[iter] = true;
					}
				}
			}

		}
		// System.out.println(result);
		return result;
	}

	// A recursive function used by toposortDFS
	public void toposortDFSRec(int v, boolean visited[], Stack stack) {

		visited[v] = true;
		Integer i;

		// Recur for all the vertices adjacent to current vertex
		Iterator<Integer> it = adjacencyLists[v].iterator();
		while (it.hasNext()) {
			i = it.next();
			if (visited[i] == false) toposortDFSRec(i, visited, stack);
		}

		// push vertices with no way out as first - here the recursion stops
		stack.push(new Integer(v));
	}

	public void toposortDFS() {
		Stack stack = new Stack();
		boolean visited[] = new boolean[v]; // false by default

		// Calls toposortDFSRec from all vertices one by one if they're not
		// visited yet
		for (int i = 0; i < v; i++)
			if (visited[i] == false) toposortDFSRec(i, visited, stack);

//		 while (stack.empty() == false)
//		 System.out.print(stack.pop() + " ");
	}
}
