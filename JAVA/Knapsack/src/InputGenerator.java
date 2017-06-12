import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Random;

public class InputGenerator {

	public void generateInput(String filename, int capacity, int numOfItems) {

		Random rand = new Random();
		int wt;
		int pr;
		
		PrintWriter writer = null;
		try
		{
			writer = new PrintWriter(filename, "UTF-8");
		} catch (FileNotFoundException | UnsupportedEncodingException error)
		{
			error.printStackTrace();
		}
		
		writer.println(capacity);
		writer.println(numOfItems);
		
		for(int i=0;i<numOfItems;i++){
			wt = rand.nextInt(capacity/10)+1;
			pr = rand.nextInt(capacity)+1;
			writer.println(pr + " " + wt);
		}
		
		writer.close();
	}

}
