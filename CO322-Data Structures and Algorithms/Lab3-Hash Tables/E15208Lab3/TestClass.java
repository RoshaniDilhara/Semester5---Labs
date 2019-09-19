import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileReader;
import java.util.Scanner;
import java.io.InputStreamReader;
import java.lang.String;
import java.lang.NumberFormatException;
import java.util.Arrays;
// import java.lang.NullPointerException;

public class TestClass extends HashTableImp
{

	//constructor
	public TestClass(int initBuckets)
	{
		super(initBuckets);
	}

	public static void main(String[]args) throws FileNotFoundException,IOException
	{
		String line="";
		int hashTableSize=0;
		TestClass hashTbl = null;

		//check whether the number of arguments are correct
		if(args.length != 2){
				System.out.println("Use the format: java TestClass <filename> <key>");
				System.exit(1);
		}

		try{
				//getting the hashtablesize(number of buckets)
				hashTableSize = Integer.parseInt(args[1]);
		}
		catch(NumberFormatException nfe){
				System.out.println("The second argument must be an integer.");
				System.exit(1);
		}

			hashTbl = new TestClass(hashTableSize);


				//Reading from Text Files
				String fileName = args[0];

				try(BufferedReader br = new BufferedReader(new FileReader(fileName)))
				{
					 //read file line by line
					while((line = br.readLine())!=null)
					{
						//Converting allcharacters except alphabets and numbers, to whitespace
						String text = line.replaceAll("[^a-zA-Z0-9]"," ");

						//split by whitespaces
						String tokens[] = text.split("\\s+");
						// System.out.println(Arrays.toString(tokens));

						for(String word:tokens)
						{
							//insert words to hash table
							hashTbl.insert(word);
						}
					}


				//give all information of hash table
				hashTbl.getBucketSize(hashTableSize);
				System.out.println();

				try(Scanner ip = new Scanner(System.in))
				{
					String key = "";

					//return when key gets the string "z".
					// until, user is asked to enter a key
					while(!key.equals("z")){

						//get a key to search from the hash table
						System.out.println("Enter a key to search: ");
						key = ip.nextLine();
						//print the number of times the key has entered in the hash table
						System.out.println("Value: "+hashTbl.search(key));
					}

				}


			}

	}//end main

}//end class
