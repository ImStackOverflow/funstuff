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
        Scanner in = new Scanner(new File("theGoodGood.txt"));
        //while (in.hasNext())
        for (int i = 0; i < 10; i++)
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
            if (input[i].toUpperCase().equals(input[i])||input[i].equals(" ")) //throws space and uppercase words
            {
                continue;
            }
            else
            {
                System.out.println("node stores " + input[i]);
                hash.store(input[i]);
            }
        }
    }


    //parses input string, removes puncutation and splits on spaces and dashes
    //input: string to be parsed
    //output: parsed string array or null
    public String[] parseLine(String input)
    {
        String[] parsed = input.replaceAll("[^a-zA-Z -]", "").split("\\s|-");
        return parsed;
    }



    public static void main(String args[]) throws IOException
    {
        HashAdo hash = new HashAdo();
        try
        {
            Tempest(hash);
            Scanner command = new Scanner(System.in);
            System.out.println("gimmie the key value");
            int in = command.nextInt();
            System.out.println("the value is: " + hash.getValue(in)+" and the freq is "+hash.getFreq(in));

        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }

    }
}