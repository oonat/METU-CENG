import java.util.ArrayList;

public class CengTree
{
    public CengTreeNode root;
    // Any extra attributes...

    public CengTree(Integer order)
    {
        CengTreeNode.order = order;
        // TODO: Initialize the class
        root = new CengTreeNodeLeaf(null);

    }

    public void addVideo(CengVideo video)
    {
        // TODO: Insert Video to Tree
        CengTreeNodeLeaf targetLeaf = ((CengTreeNodeLeaf) findLeaftoAdd(video));
        CengTreeNodeInternal parent_node;
        targetLeaf.addVideo(video);

        if(targetLeaf.videoCount() > 2*CengTreeNode.order){
            parent_node = copyup(targetLeaf);
            while(parent_node.keyCount() > 2*CengTreeNode.order) {
                parent_node = pushup(parent_node);
            }
            if(parent_node.getParent() == null)
                root = parent_node;
        }

    }

    public ArrayList<CengTreeNode> searchVideo(Integer key)
    {
        // TODO: Search within whole Tree, return visited nodes.
        // Return null if not found.
        ArrayList<CengTreeNode> node_array = new ArrayList<CengTreeNode>();
        CengTreeNode tmp = root;
        while(tmp.getType() != CengNodeType.Leaf){
            node_array.add(tmp);
            tmp = ((CengTreeNodeInternal) tmp).findPath(key);
        }

        Integer pos = ((CengTreeNodeLeaf) tmp).findVideo(key);
        if(pos.equals(-1)) {
            System.out.println("Could not find " + key + ".");
            return null;
        }

        String indent_string;
        CengTreeNodeInternal tmp_node;
        Integer tmp_keys_size;

        for(int i = 0; i < node_array.size(); i++){
            tmp_node = (CengTreeNodeInternal) node_array.get(i);
            tmp_keys_size = tmp_node.keyCount();

            indent_string = "\t".repeat(i);

            System.out.println(indent_string + "<index>");

            for(int j = 0; j < tmp_keys_size; j++)
                System.out.println(indent_string + tmp_node.keyAtIndex(j));

            System.out.println(indent_string + "</index>");
        }

        CengVideo target_video = ((CengTreeNodeLeaf) tmp).getVideo(pos);
        indent_string = "\t".repeat(node_array.size());
        System.out.println(indent_string + "<record>" + target_video.fullName() + "</record>");

        return node_array;
    }

    public void printTree()
    {
        // TODO: Print the whole tree to console
        traverse(root, 0);

    }


    // Any extra functions...
    private CengTreeNode findLeaftoAdd(CengVideo video){
        CengTreeNode tmp = root;
        while(tmp.getType() != CengNodeType.Leaf){
            tmp = ((CengTreeNodeInternal) tmp).findPath(video.getKey());
        }

        return tmp;
    }

    private CengTreeNodeInternal copyup(CengTreeNodeLeaf target){
        Integer mid_position =  target.videoCount()/2;
        Integer mid_key = target.videoKeyAtIndex(mid_position);
        CengTreeNodeInternal parent_node = (CengTreeNodeInternal) target.getParent();

        // create left node
        CengTreeNodeLeaf left_node = new CengTreeNodeLeaf(parent_node);

        for(int i = 0; i < mid_position; i++) {
            left_node.insertVideo(i, target.getVideo(i));
        }

        // create right node
        CengTreeNodeLeaf right_node = new CengTreeNodeLeaf(parent_node);

        for(int i = mid_position; i < target.videoCount(); i++) {
            right_node.insertVideo(i - mid_position, target.getVideo(i));
        }

        // If leaf node is root
        if(parent_node == null){
            parent_node = new CengTreeNodeInternal(null);
            left_node.setParent(parent_node);
            right_node.setParent(parent_node);

            parent_node.insertKey(0, mid_key);
            parent_node.insertChild(0, left_node);
            parent_node.insertChild(1, right_node);
        }else {
            Integer key_position = parent_node.findIndexofChild(target);
            parent_node.insertKey(key_position, mid_key);
            parent_node.updateChild(key_position, left_node);
            parent_node.insertChild(key_position + 1, right_node);
        }

        return parent_node;
    }

    private CengTreeNodeInternal pushup(CengTreeNodeInternal target){
        Integer mid_position =  target.keyCount()/2;
        Integer mid_key = target.keyAtIndex(mid_position);
        CengTreeNodeInternal parent_node = (CengTreeNodeInternal) target.getParent();


        CengTreeNode tmp;
        Integer tmp_key;

        // create left node
        CengTreeNodeInternal left_node = new CengTreeNodeInternal(parent_node);

        for(int i = 0; i < mid_position; i++) {
            tmp = target.getChild(i);
            tmp.setParent(left_node);
            left_node.insertChild(i, tmp);

            tmp_key = target.keyAtIndex(i);
            left_node.insertKey(i, tmp_key);
        }

        // create right node
        CengTreeNodeInternal right_node = new CengTreeNodeInternal(parent_node);

        for(int i = mid_position + 1; i < target.keyCount(); i++) {
            tmp = target.getChild(i);
            tmp.setParent(right_node);
            right_node.insertChild(i - mid_position - 1, tmp);

            tmp_key = target.keyAtIndex(i);
            right_node.insertKey(i - mid_position - 1, tmp_key);
        }

        // Special cases
        tmp = target.getChild(mid_position);
        tmp.setParent(left_node);
        left_node.insertChild(mid_position, tmp);

        tmp = target.getChild(target.keyCount());
        tmp.setParent(right_node);
        right_node.insertChild(target.keyCount() - mid_position -1, tmp);

        // If Internal node is root
        if(parent_node == null){
            parent_node = new CengTreeNodeInternal(null);
            left_node.setParent(parent_node);
            right_node.setParent(parent_node);

            parent_node.insertKey(0, mid_key);
            parent_node.insertChild(0, left_node);
            parent_node.insertChild(1, right_node);
        }else {
            Integer key_position = parent_node.findIndexofChild(target);
            parent_node.insertKey(key_position, mid_key);
            parent_node.updateChild(key_position, left_node);
            parent_node.insertChild(key_position + 1, right_node);
        }

        return parent_node;
    }

    private void traverse(CengTreeNode start_node, Integer node_level){
        String indent_string = "\t".repeat(node_level);

        if(start_node.getType() == CengNodeType.Leaf){

            CengTreeNodeLeaf tmp = ((CengTreeNodeLeaf) start_node);
            System.out.println(indent_string + "<data>");

            for(int i = 0; i < tmp.videoCount(); i++) {
                System.out.println(indent_string + "<record>" + tmp.getVideo(i).fullName() + "</record>");
            }

            System.out.println(indent_string + "</data>");

        }else{
            CengTreeNodeInternal tmp = ((CengTreeNodeInternal) start_node);
            Integer key_count = tmp.keyCount();

            System.out.println(indent_string + "<index>");
            for(int i = 0; i < key_count; i++)
                System.out.println(indent_string + tmp.keyAtIndex(i));
            System.out.println(indent_string + "</index>");

            for(int i = 0; i <= key_count; i++) {
                traverse(tmp.getChild(i), node_level+1);
            }

        }
    }

}
