import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;

public class Main {
	public static void main(String[] args) {
		
		long div = 1000000000;
		
		PrintWriter writer = null;
		try
		{
			writer = new PrintWriter("bfsy6.txt", "UTF-8");
		} catch (FileNotFoundException | UnsupportedEncodingException error)
		{
			error.printStackTrace();
		}
		
		writer.println("n\tAMG\tALG\tEAG");
		
		for(int n=500;n<=5000;n+=500){
		 // number of vertices
		int m = (n * (n - 1)) / 4; // density of a graph
		int[][] aM = DAGGenerator.generateDAG(n, m);

		AdjacencyMatrixGraph AMG = new AdjacencyMatrixGraph(aM, n);
		AdjacencyListsGraph ALG = new AdjacencyListsGraph(aM, n);
		EdgeArrayGraph EAG = new EdgeArrayGraph(aM, n, m);
		
		long start = System.nanoTime();
		AMG.toposortBFS();
		long stop = System.nanoTime();
		double wynik1 = (double) (stop - start) / div;
		 
		start = System.nanoTime();
		ALG.toposortBFS();
		stop = System.nanoTime();
		double wynik2 = (double) (stop - start) / div;
		
		start = System.nanoTime();
		EAG.toposortBFS();
		stop = System.nanoTime();
		double wynik3 = (double) (stop - start) / div;
		
		writer.println(n+"\t"+wynik1 + "\t" + wynik2 + "\t" + wynik3);

		aM=null;
		AMG=null;
		ALG=null;
		EAG=null;
		}
		
		writer.close();
		
		
	}
}
