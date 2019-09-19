/*********************************************
 * CO322: Data structures and algorithms
 * Implementation of the hashTable
 *********************************************/


 import java.io.BufferedReader;
 import java.io.IOException;
 import java.io.InputStreamReader;
 import java.lang.String;
 import java.lang.RuntimeException;


public class HashTableImp implements HashTable
{

  //making the linked list
   private static class LinkedListNode
   {
      String key;
      int value=0;
      LinkedListNode next; //points to the next node

      //Constructor
      LinkedListNode(String key)
      {
        this.key = key;
        this.next = null;
      }
   }

   public LinkedListNode[] table;  //Hash table
   private int count;  //Number of (key,value) pairs in the hash table
   private int TABLE_SIZE;

   // create a open hash table with given number of buckets
   public HashTableImp(int initBuckets)
   {
     TABLE_SIZE = initBuckets;
     table = new LinkedListNode[TABLE_SIZE];
   }

   public void insert(String key)
   {
     //Receive bucket number by calculating the hashcode for a given key
      int bucketNum = hash(key);
      LinkedListNode bucket = table[bucketNum];

      while (bucket != null)
      {
         //check if the key already exists
         if (bucket.key.equals(key))
            break;
         bucket = bucket.next;
      }

      if (bucket != null)
      {
         //key is found
         //so then Update the value
         bucket.value++;
      }
      else
      {
         LinkedListNode newNode = new LinkedListNode(key);
         newNode.value++;
         newNode.next = table[bucketNum];
         table[bucketNum] = newNode;
         count++;  //Count the newly added key.
      }
   }

   //search the value for a given key
   public int search(String key)
   {
      int bucketNum = hash(key); //compute the bucket number using the hashcode
      LinkedListNode bucket = table[bucketNum]; //make a bucket for the bucket number
      while (bucket != null)
      {
         if (bucket.key.equals(key))
            return bucket.value;
         bucket = bucket.next;
      }

      return 0;
   }

   //check whether the specified key is already in the table.
   public boolean containsKey(String key)
   {
      int bucketNum = hash(key);
      LinkedListNode bucket = table[bucketNum];

      while (bucket != null)
      {
         //return true if the key if found
         if (bucket.key.equals(key))
            return true;
         bucket = bucket.next;
      }

      return false;
   }

   //to get the number of (key,value) pairs in the table.
   public int getSize()
   {
      return count;
   }

   //Compute a hash code for the key
   private int hash(String key)
   {
	   int hashcode = 0;
	   for (int i = 0; i < key.length(); i++)
	   {

		   hashcode = (23* hashcode + key.charAt(i))%table.length;
	   }
	   return (hashcode%table.length);
   }


   //Returns the number of nodes in the specified bucket
   public void getBucketSize(int length)
   {
	   int x2=0;
	   int sum = 0;
     float lengthF = (float)length;
     int k = 0;

     while(k<length)
	   {
    		   int counter=0;
    		   LinkedListNode bucket = table[k];
    		   while(bucket != null)
    		   {
    			   bucket = bucket.next;
    			   counter++;
    		   }
    		   sum += counter;
    		   x2 = x2 + (int) Math.pow(counter,2);
    		   System.out.println((k+1)+":"+counter);
           k++;
	     }

	   float avg = (float)(sum/lengthF);
	   float var = (float)(x2/lengthF) - (float)(Math.pow(avg, 2));

	   System.out.println("Total:"+ sum);
	   System.out.println("Average:"+ avg);
	   System.out.println("Deviation:"+Math.sqrt(var));
   }

}// end HashTableImp
