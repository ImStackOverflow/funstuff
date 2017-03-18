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
        for (int i = 0; i < 5; i++)
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
                hash.store(input[i]);
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

    public static void readFromInputFile()
    {
        try
        {
            BufferedReader reader = new BufferedReader(new FileReader("input.txt"));
            String line;
            while ((line = reader.readLine()) != null)
            {
                String[] args = line.split(":"); // Reader assumes that the input format is as given in the instruction
                // If the line is 2i, then I know that it is a configuration of a ChessBoard
                // so create a new ChessBoard here, parse board size and insert
                // given chesspieces into the linked list
                //System.out.println("line is: "+line+" args[0]: "+args[0]);
                level = Integer.parseInt(args[0]);
                args = line.split(" ");
                c = new ChessBoard();

                for(int i = 1; i < args.length; i += 3)
                {
                    //System.out.print(args[i]+" ");
                    head = ListOperations.insert(head, new Node(args[i].charAt(0), Integer.parseInt(args[i + 2]), Integer.parseInt(args[i + 1])));
                }
                //Utilities.printList(head);
                System.out.println(" at board number: " + lineCtr);
                board_no = lineCtr;
                //Utilities.printList(head);
                performOperations(c, level);
                lineCtr++; // move to the next line
            }

            reader.close();
        }
        catch (NumberFormatException e)
        {
            Utilities.errExit("All arguments must be integers"); // throw error incase parsing integer fails
        }
        catch (IndexOutOfBoundsException e)
        {
            Utilities.errExit("Array index is out of bounds"); // throw error when inserting elements into arrays fail
        }
        catch (Exception e)
        {
            Utilities.errExit("Exception occurred trying to read file"); // throw a generic exception if failure to read occurs
        }
    }



    public static void main(String args[]) throws IOException
    {
        HashAdo hash = new HashAdo();
        BinaryTree tree = new BinaryTree();

        try
        {
            Tempest(hash); //partition shakespeare text
            Scanner command = new Scanner(System.in);
            int[][] table = hash.getArray();
            tree.makeTree(table);
            int[] words = tree.getWords(6, 2);
            //System.out.println("gimmie the length to probe: ");
            //int in = command.nextInt();
            System.out.println("the word of length 6 is: ");
            for (int i = 0; i < words.length; i++)
            {
                System.out.println(words[i] + " ");
                System.out.println("that equals: " + hash.getWord(words[i]));
            }


        }
        catch (Exception e)
        {
            System.out.println("there was an error it was " + e.getMessage());
        }

    }
}