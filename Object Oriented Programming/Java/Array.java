import java.io.*;

public class Array
{
	public static void main(String[] args)
	{
		int[] a,b;

		a = new int[100];
		b = a;
		
		a[0] = 10;
		b[1] = 20;

		System.out.println(b[0]);
		System.out.println(a[1]);
	}
}
