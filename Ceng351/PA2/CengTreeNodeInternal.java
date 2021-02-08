import java.util.ArrayList;

public class CengTreeNodeInternal extends CengTreeNode
{
    private ArrayList<Integer> keys;
    private ArrayList<CengTreeNode> children;

    public CengTreeNodeInternal(CengTreeNode parent)
    {
        super(parent);

        // TODO: Extra initializations, if necessary.
        keys = new ArrayList<Integer>();
        children = new ArrayList<CengTreeNode>();
        this.type = CengNodeType.Internal;
    }

    // GUI Methods - Do not modify
    public ArrayList<CengTreeNode> getAllChildren()
    {
        return this.children;
    }
    public Integer keyCount()
    {
        return this.keys.size();
    }
    public Integer keyAtIndex(Integer index)
    {
        if(index >= this.keyCount() || index < 0)
        {
            return -1;
        }
        else
        {
            return this.keys.get(index);
        }
    }

    // Extra Functions
    public Integer findPosition(Integer key){
        Integer position = 0;
        while(position < this.keys.size() && key >= this.keys.get(position))
            position += 1;

        return position;
    }

    public Integer findIndexofChild(CengTreeNode src){
        return this.children.indexOf(src);
    }

    public CengTreeNode findPath(Integer key){
        return this.children.get(findPosition(key));
    }

    public CengTreeNode getChild(Integer position){
        return this.children.get(position);
    }

    public void insertKey(Integer position, Integer key){
        this.keys.add(position, key);
    }

    public void insertChild(Integer position, CengTreeNode child){
        this.children.add(position, child);
    }

    public void updateChild(Integer position, CengTreeNode child){
        this.children.set(position, child);
    }

}
