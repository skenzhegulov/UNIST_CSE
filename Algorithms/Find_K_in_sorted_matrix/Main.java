	/* Name: Saken Kenzhegulov
	   ID: 20132027
	   E-mail: s.kenzhegulov@mail.ru
		     
	Brief Explanation: Search starts from the rightmost upper part of the matrix (0,m-1).
			   If the current element is greater than 'num' we move along the row from the right to the left.
			   If the current element is less than 'num' we go to the next row, since elements on the left side will be less or equeal to it.
			   And when we jump to the next row, we don't need to start searching from column number m-1. 
			   Since our array is sorted and before on that positions were elements greater than 'num', on the right side of current cell will
			   be elements equal to or greater than those elements.
			   When we find the element equal to 'num', we print its position and check left neighbors since they also can be equal to 'num'.
			   Then we jump to the next row, and repeat these steps again until we will not reach left or bottom boundaries of our matrix.
	
	Reference and/or Collaborations: I discussed this problem with my friend Madi Khamitbekov. However, I write the code my own.
	*/
			   
import java.util.*;
import java.lang.*;
import java.io.*;
import java.util.Arrays;
import java.math.*;
import java.util.Random;
			   
/* Name of the class has to be "Main" only if the class is public. */
public class Main // MatrixSearch
{
	private int [][] mat;
	
	public void select(int[][] mat_in, int n, int m, int num) {
		if ( num < 0 || num > 100 ) {
			return;
		}

		mat = mat_in.clone();
				
		matrixsearch(n, m, num);	
	}
		
	private void matrixsearch(int n, int m, int num) {
		int i = 0, j = m-1;
		while(i<n && j>=0)
			if(mat[i][j] == num) {
				int k = j;
				while(k>=0 && mat[i][k]==num) {
					System.out.println("Element num="+num+" is found at location ("+i+","+k+").");
					k--;
				}
				i++;
			} else if(mat[i][j] > num) j--; else i++;
	}
																												

	private static int max( int x, int y ) { if ( x < y ) { return y; } else { return x; } }
																				
	private static void generatesortedmatrix(int [][] test, int n, int m) {
		Random randomGenerator = new Random();
		test[0][0] = 1;
		for( int j=1; j<m; j++ ) test[0][j] = test[0][j-1] + randomGenerator.nextInt(2) + 1;
		
		for( int i=1; i<n; i++ ) {
			test[i][0] = test[i-1][0] + randomGenerator.nextInt(2) + 1; 
			for( int j=1; j<m; j++ ) test[i][j] = max( test[i-1][j], test[i][j-1] ) + randomGenerator.nextInt(2) + 1;				
		}
	
		for( int i=0; i<n; i++ ) System.out.println( Arrays.toString(test[i]) );	
	}
		
	public static void main (String[] args) throws java.lang.Exception {
		Main selecter = new Main();
		Random randomGenerator = new Random();
		
		int n, m, num;
		
		// Following three lines are for your testing and debugging
		n = randomGenerator.nextInt( 50 ); 
		m = randomGenerator.nextInt ( 50 );
		num = randomGenerator.nextInt( 100 );  					
		
		/* Actual input will be the following format
		7 7 <- number of rows and columns
		10 <- number to be chosen (an integer between 1 and 100)
		*/
		
		// Use the following lines for your final testing and submission
		/*
		Scanner in = new Scanner(System.in);
		n = in.nextInt();
		m = in.nextInt();
		num = in.nextInt();
		*/
		
		int [][]test = new int[n][m];
		generatesortedmatrix( test, n, m );

		selecter.select( test, n, m, num );

		/* For your testing (when you want to verify that the orders generated are correct 
		for( int i=1; i<=test.length; i++ ) {
			int[] tmp_test = test.clone();
			selecter.select( tmp_test, i );
			System.out.println( Integer.toString(i) + ":" + Integer.toString( value ) );
		}
		*/	
	}
}
