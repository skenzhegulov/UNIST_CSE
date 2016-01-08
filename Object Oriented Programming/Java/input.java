import java.io.*;

public class input
{
	public static void main(String[] args)
			throws IOException
	{
		/*System.out.print("Please enter a string: ");
		BufferedReader bufIn = new BufferedReader(new InputStreamReader(System.in));
		String s = bufIn.readLine();
		System.out.println("You entered: " + s);*/
		PrintWriter outputFile = new PrintWriter("Names.txt");
		outputFile.println("Hello!");
		outputFile.println("How Are You?");
		outputFile.close();
	}
}
