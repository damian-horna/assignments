import java.util.ArrayList;
import java.util.Collections;


public class Generator
{
	public static int[] generateUniqueRandomArray(int length)
	{

		int[] a = new int[length];
		ArrayList<Integer> al = new ArrayList<Integer>();

		for (int i = 1; i <= length; i++)
			al.add(i);

		Collections.shuffle(al);

		for (int i = 0; i < length; i++)
			a[i] = (int) al.get(i);

		return a;
	}
}
