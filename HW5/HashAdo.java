import java.util.*;

class HashAdo
{
    private HashMap<Integer, Node>  map = new HashMap<Integer, Node>();

    public HashAdo()
    {
    }

    //stores node value into hash map
    //input: Node
    //output: none
    public void store(String word)
    {
        int hash = word.hashCode();
        System.out.println("the hash code is: " + hash);
        Node value = map.get(hash);
        if (value != null)
        {
            if (word.equals(value.getWord())) //if value word is same as word trying to add
            {
                map.replace(hash, value.addOne());
            }
            else
            {//collition detection
                System.out.println("the word " + word+ " has the same hash as " + value.getWord());
                System.out.println("eg. "+hash+" and "+value.getWord().hashCode());
                System.exit(0);
            }
        }
        else
        {
            Node node = new Node(word);
            map.put(hash, node);

        }
    }


    public int getFreq(int key){
        if(map.containsKey(key)){
            Node value = map.get(key);
            return value.getFreq();
        }
        else {
            return 0;
        }

    }
    //finds value given key
    //input: key int
    //output: string word value
    public String getValue(int key)
    {
        if(map.containsKey(key))
        {
            Node balls = map.get(key);
            return balls.getWord();
        }
        else
        {
            String balls = "that key aint got no value bitch";
            return balls;
        }
    }
}