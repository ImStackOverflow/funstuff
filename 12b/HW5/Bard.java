import java.util.*;
import java.io.*;

class Bard
{
    public static Bard Romeo = new Bard();



    //hashes shakespeare works
    //input hash interface
    //no output
    public static void Tempest(HashAdo hash) throws IOException
    {
        String[] shit = new String[200];
        Scanner in = new Scanner(new File("shakespeare.txt"));
        while (in.hasNext())
        {
            shit = Romeo.parseLine(in.nextLine());
            Romeo.putInMap(hash, shit);
        }
        in.close();
    }




    //stores array of strings into hash map
    //input hashmap and input string
    public void putInMap(HashAdo hash, String[] input)
    {
        for (int i = 0; i < input.length; i++)
        {
            if (input[i].toUpperCase().equals(input[i]) || input[i].equals(" ")) //throws space and uppercase words
            {
                continue;
            }
            else
            {
                //System.out.println("node stores " + input[i]);
                input[i].replaceAll(" ","");
                hash.store(input[i].toLowerCase());
            }
        }
    }


    //parses input string, removes puncutation and splits on spaces and dashes
    //input: string to be parsed
    //output: parsed string array or null
    public String[] parseLine(String input)
    {
        String[] parsed = input.replaceAll("[^a-zA-Z - ']", "").split("\\s");
        return parsed;
    }

    /*
    public String treeWord(HashAdo hash, TreeMap tree, int length){
    	int[][] key = tree.get(length);
    	String balls = hash.getWord(key[0][1]);
    	return balls;
    }
    */

    public static void doInput(HashAdo hash, BinaryTree tree)
    {
        try
        {
            PrintWriter out = new PrintWriter(new File("analysis.txt"));
            Scanner input = new Scanner(new File("input.txt"));
            while (input.hasNext())
            {
                String[] line = input.nextLine().split(" ");
                if(line[0].matches("\\d+"))//if number
                {
                    if(tree.containsLength(Integer.parseInt(line[0])))
                    {
                        int[] words = tree.getWords(Integer.parseInt(line[0]), Integer.parseInt(line[1]));
                        for (int i = 0; i < words.length; i++)
                        {
                            out.print(hash.getWord(words[i]) + " ");
                        }
                        out.println(" ");

                    }
                    else out.println("no words of that length exist");

                }
                else//otherwise word
                {
                    out.println(hash.getFreq(line[0]));
                }
            }
            input.close();
            out.close();
        }

        catch (NumberFormatException e)
        {
            System.out.println("All arguments must be integers"); // throw error incase parsing integer fails
        }
        catch (IndexOutOfBoundsException e)
        {
            System.out.println("Array index is out of bounds"); // throw error when inserting elements into arrays fail
        }
        catch (Exception e)
        {
            System.out.println("Exception occurred trying to read file"); // throw a generic exception if failure to read occurs
        }
    }



    public static void main(String args[])
    {
        HashAdo hash = new HashAdo();
        BinaryTree tree = new BinaryTree();
        try
        {
            Tempest(hash); //partition shakespeare text and make hash table
            tree.makeTree(hash.getArray()); //make binary tree
            Romeo.doInput(hash, tree); //do input operations
            //System.out.println(hash.getWord(3481)+" "+hash.getFreq("o'"));
        }
        catch (Exception e)
        {
            System.out.println("there was an error it was " + e.getMessage());
        }
    }
}