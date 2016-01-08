import java.util.Comparator;

/**
 * Bubble sort algorithm.
 * 
 * @param <E> type of element to be sorted
 */
public class BubbleSort<E> implements Sort<E> {

	public void sort(Sequence<E> sequence, Comparator<E> comparator) {
		for(int i=0; i<sequence.size()-1; i++) 
			for(int j=i+1; j<sequence.size(); j++)
				if( comparator.compare(sequence.get(i), sequence.get(j))>0) sequence.swap(i,j);
	}
	
	public String toString() {
		return "Bubble Sort";
	}

}
