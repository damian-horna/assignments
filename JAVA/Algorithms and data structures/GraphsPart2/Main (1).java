


public class Main {
	public static void main(String[] args) {
		
		for(int n=2;n<19;n+=1){
		
		long start, stop;
		long div = 1000000000;
		double timeE=0;
		
		Graph graph = new Graph();
		graph.createGraph(n, 50);
		start = System.nanoTime();
		graph.wszystkiecykle(1,n);
	    stop = System.nanoTime();
	    timeE = (double)(stop - start)/div;
	    System.out.println(n);
	    System.out.println(timeE);
		
	}

	}
	}	

