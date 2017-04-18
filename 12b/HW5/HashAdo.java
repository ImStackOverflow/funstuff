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
        if(word.equals("o'")){
            hash++;
        }
        //System.out.println("the hash code is: " + hash);
        Node value = map.get(hash);

        if (value != null)
        {
            if (word.equals(value.getWord())) //if value word is same as word trying to add
            {
                map.put(hash, value.addOne());
            }
            else
            {
                //collition detection
                //System.out.println("the word " + word + " has the same hash as " + value.getWord());
                //System.out.println("eg. " + hash + " and " + value.getWord().hashCode());
                //System.exit(0);
            }
        }
        else
        {
            Node node = new Node(word);
            map.put(hash, node);

        }
    }


    //gets frequency of word
    //input: word
    //output: int of frequency
    public int getFreq(String word)
    {

        int key = word.hashCode();
        if(word.equals("o' ")) key++;
        if(map.containsKey(key))
        {
            Node value = map.get(key);
            return value.getFreq();
        }
        else
        {
            return 0;
        }

    }


    //returns 2d array with length as 0th element, freq as 1st, and hashvalue as 2nd
    public int[][] getArray()
    {
        int[][] array = new int[map.size()][3];
        Node value;
        int i = 0;
        Set<Integer> set = map.keySet();
        for (int key : set)
        {
            value = map.get(key);
            array[i][0] = value.getLength();
            array[i][1] = value.getFreq();
            array[i][2] = key;
            i++;
        }
        return array;

    }

    //finds value given key
    //input: key int
    //output: string word value

    public String getWord(int key)
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