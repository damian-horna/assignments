
public class Node
{
	int data;
	Node left;
	Node right;

	public Node()
	{
		this(0);
	}
	
	public Node(int data)
	{
		this.data = data;
		left = null;
		right = null;
	}
}
