
public class NodeAVL
{
	int data, height;
	NodeAVL left;
	NodeAVL right;

	public NodeAVL()
	{
		this(0);
	}
	
	public NodeAVL(int data)
	{
		this.data = data;
		left = null;
		right = null;
		height = 1;
	}
}
