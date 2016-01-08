/* Name: Saken Kenzhegulov
   ID: 20132027
   E-mail: s.kenzhegulov@mail.ru
         
	Brief Explanation: Implementation of my algorithm is almost the same as that of Selection algorithm in the CSLR textbook.  
	                   
	Reference and/or Collaborations: CLRS, Selection in worst-case linear time, Introduction to Algorithm (CLRS book), 215-222 pages  
*/
		 
import java.util.*;
import java.lang.*;
import java.io.*;
import java.util.Arrays;
import java.math.*;
import java.util.Random;
		  
public class Main // LinearSelection
{
 	public int select(int[] values, int order) {
		if (values == null || values.length==0 ) { return -1; }
		int[] numbers;		
		numbers = values;
		return linearsearch(numbers, 0, values.length-1, order-1);
	}

	private int min( int x, int y ) { if ( x > y ) { return y; } else { return x; } }

	private int median_of_5( int[] numbers, int idx){
		if ( idx+5 > numbers.length ) return numbers[idx];
		int[] tmp_numbers = new int[5];
		
		for(int i=idx; i<idx+5; i++) {
			tmp_numbers[i-idx] = numbers[i];
		}
		
		for(int i=0; i < 3; i++) {
			for (int j=i+1; j < 5; j++ ) {
				if ( tmp_numbers[i] > tmp_numbers[j] ) {
					exchange( tmp_numbers, i, j );
				}
			}
		}
		return tmp_numbers[2];
	}

	private int median_of_median( int[] numbers, int low, int high) {
		//System.out.println("median_of_median" + Arrays.toString( Arrays.copyOfRange(numbers, low, high+1) ) );
		//System.out.println("low = "+low+"\nhigh = "+high);
		//new Scanner(System.in).nextLine();
		int length = high-low+1;
		if(length<5) return numbers[low];
		int j = 0;
		int[] num_medians = new int[length/5+1];
	 	for(int i=low; i<=high; i+=5){
			num_medians[j++] = median_of_5(numbers, i);
		}
		return linearsearch(num_medians, 0, j-1, j/2);
	}

	private int linearsearch(int[] numbers, int low, int high, int order) {
		if(low == high) return numbers[low];
		int i = low, j = high;
		int pivot = median_of_median(numbers, low, high);
		//System.out.println("Pivot = "+pivot);
		//new Scanner(System.in).nextLine();
		while ( i <= j ) {
			while ( numbers[i] < pivot) { i++; }
			while ( numbers[j] > pivot ) { j--; }
			if ( i <= j ) {
				exchange( numbers, i, j );						
				i++; j--;								
			}			
		}
		if ( order <  i ) {		
			return linearsearch( numbers, low, i-1, order);
		} else {
			return linearsearch( numbers, i, high, order );
		}
	}

	private void exchange(int[] numbers, int i, int j ) {
		int temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = temp;	
	}

	public static void main (String[] args) throws java.lang.Exception {
		Main selecter = new Main();
		Random randomGenerator = new Random();
		int order;
		int[] test;
		Scanner in = new Scanner(System.in);
		int len = in.nextInt();
		test = new int[len];
		for( int i=0; i < len; i++ ) {
			test[i] = in.nextInt();
			//test[i] = randomGenerator.nextInt();
			//if(test[i]<0) test[i] *= -1;
		}
		order = in.nextInt();
		//order = randomGenerator.nextInt( test.length );  
		System.out.println( Integer.toString( order ) + ":" + Integer.toString( selecter.select( test, order) ) );
	}
		
}
