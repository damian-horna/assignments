
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;
import java.util.ArrayList;

//eulerian and hamiltonian at the same time, undirected
public class Graph {
	ArrayList<Integer> eulerianCycle = new ArrayList<Integer>();
	private int[][] adjacencyMatrix;
	private int n, m;
	private int hamCycle[] ;
	private boolean hamVisited[];
	ArrayList<ArrayList> answer=new ArrayList<ArrayList>();
	ArrayList<Integer> V = new ArrayList<Integer>();
	

	public int[][] createGraph(int n, int density) {
		adjacencyMatrix = new int[n][n];
		this.n = n;
		this.m = n * (n - 1) * density / 200;

		makeItHamiltonian();
		makeItEulerian();
		
		return adjacencyMatrix;
	}

	private void makeItEulerian() {
		Random random = new Random();
		int ver1, ver2, ver3;
		while (m > 0) {

			ver1 = random.nextInt(n);
			ver2 = random.nextInt(n);
			ver3 = random.nextInt(n);

			if (areOkay(ver1, ver2, ver3)) {
				connect(ver1, ver2, ver3);
				m-=3;
			} else continue;

		}
	}

	private void connect(int ver1, int ver2, int ver3) {
		adjacencyMatrix[ver1][ver2] = 1;
		adjacencyMatrix[ver2][ver1] = 1;
		adjacencyMatrix[ver1][ver3] = 1;
		adjacencyMatrix[ver3][ver1] = 1;
		adjacencyMatrix[ver2][ver3] = 1;
		adjacencyMatrix[ver3][ver2] = 1;
	}

	private boolean areOkay(int ver1, int ver2, int ver3) {

		// three different vertices
		if (ver1 == ver2 || ver2 == ver3 || ver1 == ver3) return false;

		// no connection between them yet
		if (adjacencyMatrix[ver1][ver2] == 1 || adjacencyMatrix[ver1][ver3] == 1 || adjacencyMatrix[ver2][ver3] == 1)
			return false;

		return true;
	}

	private void makeItHamiltonian() {

		int[] permutation = new int[n];
		
		for (int i = 0; i < n; i++)
			permutation[i] = i;
		
		shuffleArray(permutation);

		for (int i = 0; i < n - 1; i++) {
			adjacencyMatrix[permutation[i]][permutation[i + 1]] = 1;
			adjacencyMatrix[permutation[i + 1]][permutation[i]] = 1;
		}
		adjacencyMatrix[permutation[0]][permutation[n - 1]] = 1;
		adjacencyMatrix[permutation[n - 1]][permutation[0]] = 1;
		
		m -= n;

	}

	// Implementing Fisher–Yates shuffle
	public void shuffleArray(int[] ar) {
		Random rnd = ThreadLocalRandom.current();
		for (int i = ar.length - 1; i > 0; i--) {
			int index = rnd.nextInt(i + 1);
			// Simple swap
			int a = ar[index];
			ar[index] = ar[i];
			ar[i] = a;
		}
	}

	public void printTheMatrix(int n) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				System.out.print(adjacencyMatrix[i][j] + " ");
			System.out.println();
		}
	}
	
	public void cyklEulera(int b,int n) {
		

		for(int i=0;i<n;i++){
			if(adjacencyMatrix[b][i]==1 ){
				adjacencyMatrix[b][i]=0;
				adjacencyMatrix[i][b]=0;
				cyklEulera(i,n);
			}
		
		}
		eulerianCycle.add(b);
	}
	public void cyklE(int b,int n){
		
		cyklEulera(b,n);
		for(int i = 0; i < eulerianCycle.size(); i++) eulerianCycle.set(i, eulerianCycle.get(i)+1);
		//System.out.println(eulerianCycle);
		eulerianCycle.clear();
	}
	
	public int cyklH (long start,int pos,int n){
		if(pos==n){
			if(adjacencyMatrix[hamCycle[pos-1]][hamCycle[0]]==1)
				return 1;
			else
				return 0;
		}
		for (int v = 1; v < n; v++){
			if(!hamVisited[v] && adjacencyMatrix[hamCycle[pos - 1]][v] == 1){
				hamCycle[pos] = v;
				hamVisited[v] = true;
				if((double)(System.nanoTime()-start)/1000000000 > 300) return -1;
				if(cyklH(start,pos + 1,n) == 1)
					return 1;
				
				hamCycle[pos] = -1;
				hamVisited[v] = false;
			}
		}
		return 0;
	}
	
	public void cykleHamiltona(long start,int n){
		hamCycle = new int[n];
		for(int j = 0; j < n; j++){
			hamCycle[j] = -1;
	  }
	hamVisited = new boolean[n];
	for(int j = 0; j < n; j++){
		hamVisited[j] = false;
	}
		hamVisited[0] = true;
		hamCycle[0] = 0;
		cyklH(start,1 ,n);
	
  }
	

	public void wszystkiecykle(int v,int n){
		V.add(v);
		for(int i=0;i<adjacencyMatrix[v].length;i++)
		{
			if(adjacencyMatrix[v][i]==0||V.contains(i)){continue;}
			wszystkiecykle(i,n);
		}
			if(V.size()==n && adjacencyMatrix[V.get(0)][v]==1){answer.add(new ArrayList<Integer>(V));V.remove(V.indexOf(v));}
			else{V.remove(V.indexOf(v));}
	}
	public void wszystkie(int v,int n){
		wszystkiecykle(v,n);
		for(ArrayList<Integer> array:answer){
			for(int i = 0; i < n; i++) array.set(i, array.get(i)+1);
		}
//		System.out.println(answer);
		answer.clear();
		V.clear();
	}
	
	public void hamilton(int v,int n){
		V.add(v);
		for(int i=0; i<adjacencyMatrix[v].length; i++)
		{
			if(adjacencyMatrix[v][i]==0 || V.contains(i))continue;
			hamilton(i,n);
		}
		if(V.size()==adjacencyMatrix[v].length && adjacencyMatrix[V.get(0)][V.get(V.size()-1)]==1){return;}
		else{V.remove(V.indexOf(v));}
	}
	
}