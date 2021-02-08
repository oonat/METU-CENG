import java.util.ArrayList;

public class CengTreeNodeLeaf extends CengTreeNode
{
    private ArrayList<CengVideo> videos;
    // TODO: Any extra attributes

    public CengTreeNodeLeaf(CengTreeNode parent)
    {
        super(parent);

        // TODO: Extra initializations
        videos = new ArrayList<CengVideo>();
        this.type = CengNodeType.Leaf;
    }

    // GUI Methods - Do not modify
    public int videoCount()
    {
        return videos.size();
    }
    public Integer videoKeyAtIndex(Integer index)
    {
        if(index >= this.videoCount()) {
            return -1;
        } else {
            CengVideo video = this.videos.get(index);

            return video.getKey();
        }
    }

    // Extra Functions
    public void addVideo(CengVideo video){
        Integer position = 0;
        Integer video_key = video.getKey();
        while(position < this.videos.size() && video_key > this.videos.get(position).getKey())
            position += 1;

        this.videos.add(position, video);
    }

    public Integer findVideo(Integer key){
        Integer position = 0;
        Integer videos_size = videos.size();
        while(position < videos_size && !(key.equals(this.videos.get(position).getKey())))
            position += 1;

        if(position.equals(videos_size))
            return -1;
        else
            return position;
    }

    public CengVideo getVideo(Integer position){
        return this.videos.get(position);
    }
    public void insertVideo(Integer position, CengVideo video){ this.videos.add(position, video) ;}
}
