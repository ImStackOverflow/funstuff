import java.util.*;

class BinaryTree
{
    private TreeMap<Integer, int[][]> tree = new TreeMap<Integer, int[][]>();

    public BinaryTree()
    {

    }
    //merge sorts an array given the value to sory by
    //input arry to sort and value of array to sort by
    //output sorted array
    public int[][] mergesort(int[][] array, int sortVlaue)
    {
        /*
        System.out.println("the array is: ");
        for (int i = 0; i < array.length; i++)
        {
            System.out.print(array[i][0] + " ");
        }
        System.out.println(" ");
        */
        if(array.length == 1) return array;


        //System.out.println("at mergesort array length is: " + array.length);
        int[][] half1 = new int[(array.length / 2) ][array[0].length];
        //System.out.println("the half1 length is " + half1.length);
        for (int i = 0; i < array.length / 2; i++)
        {
            for (int j = 0; j < array[0].length; j++)
            {
                half1[i][j] = array[i][j];
            }
        }
        int[][] half2 = new int[(array.length / 2) + array.length % 2][array[0].length];

        for (int i = (array.length / 2), k = 0; i < array.length; i++, k++)
        {
            for (int j = 0; j < array[0].length; j++)
            {
                half2[k][j] = array[i][j];
            }
        }
        half1 = mergesort(half1, sortVlaue);
        half2 = mergesort(half2, sortVlaue);


        return merge(half1, half2, sortVlaue);

    }


    //does the merging
    //input: the 2 halves and which array value to sort by
    //output: the merger of the 2 arrays
    public int[][] merge(int[][] half1, int[][] half2, int sortVlaue)
    {
        /*System.out.println("merging");
        System.out.println("the merge array input is: ");
        for (int i = 0; i < half1.length; i++)
        {
            System.out.print(half1[i][0] + " ");
        }
        System.out.println(" ");
        for (int i = 0; i < half2.length; i++)
        {
            System.out.print(half2[i][0] + " ");
        }
        System.out.println(" ");
        //System.out.println("the half1 length is " + half1.length);
        //System.out.println("the half2 length is " + half2.length);
        */
        int [][] merged = new int[half1.length + half2.length][half1[0].length];
        //System.out.println("the merged length is " + merged.length);
        int a = 0, b = 0, c = 0;
        while (a < half1.length && b < half2.length)
        {

            if(half1[a][sortVlaue] <= half2[b][sortVlaue])
            {
                for (int i = 0; i < half1[0].length; i++)
                {
                    merged[c][i] = half1[a][i];
                }
                a++;
            }
            else
            {
                for (int i = 0; i < half1[0].length; i++)
                {
                    merged[c][i] = half2[b][i];
                }
                b++;
            }
            c++;
            //System.out.println("a = "+a+" b = "+b+" c = "+c);
        }
        if (a < half1.length)
        {
            for (; a < half1.length; a++, c++)
            {
                for (int i = 0; i < half1[0].length; i++)
                {
                    merged[c][i] = half1[a][i];
                }
            }
        }
        else
        {
            for (; b < half2.length; b++, c++)
            {
                for (int i = 0; i < half1[0].length; i++)
                {
                    merged[c][i] = half2[b][i];
                }
            }
        }

        /*System.out.println("the merge array is: ");
        for (int i = 0; i < merged.length; i++)
        {
            System.out.print(merged[i][0] + " ");
        }
        System.out.println(" ");
        */

        return merged;
    }


    //makes binary tree labeled with word length
    //input tree and data to imput
    //output none
    public void makeTree(int[][] beta)
    {
        int[][] data = mergesort(beta, 0); //sorts data based on length
        for (int i = 0; i < data.length;)
        {
            int j = 1;
            //System.out.println("the freq for length " + data[i][0]);
            while(i + j < data.length && data[i][0] == data[i + j][0])
            {
                //System.out.println(data[i + j][1] + " ");
                j++;
            }
            //System.out.println("the range is: " + j + "and the start is: " + i);
            int[][] whoop = partitionArray(data, i, j);
            /*System.out.println("the data is: ");
            for (int k = 0; k < whoop.length; k++)
            {
                System.out.print(whoop[k][0]);
            }
            System.out.println(" ");
            */
            tree.put(data[i][0], whoop);
            i += j;
        }
        data = tree.get(6);
        //System.out.println("the words of length 6 are: ");
        /*for (int i = 0; i < data.length; i++)
        {
            System.out.print(" " + data[i][0]);
        }*/
        //System.out.println("getting out of the tree");
    }

    //stores section of input into seperate array defined by range and start indicie
    //input data array, start location, and range
    //output 2d array of
    public int[][] partitionArray(int data[][], int start, int range)
    {
        int[][] store = new int[range][2];
        for (int k = 0; k < range; k++)
        {
            for (int l = 1; l < 3; l++)
            {
                store[k][l - 1] = data[k + start][l];
            }
        }
        store = mergesort(store, 0);//sort based on frequency
        return store;
    }



    public boolean containsLength(int k)
    {
        return tree.containsKey(k);
    }

    //returns k most frequent word hash values of l length
    //input number of words k of length l
    //output array of length k
    public int[] getWords(int l, int k)
    {
        int[] words = new int[k];//array to store hash values
        int[][] values = tree.get(l);//values from tree
        if (values.length >= k)
        {
            for (int i = 0; i < k; i++)
            {
                words[i] = values[i][1];
            }
        }

        return words;
    }
}