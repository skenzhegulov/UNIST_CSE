
import java.util.Comparator;

/**
 * Insertion sort algorithm.
 *
 * @param <E> type of element to be sorted
 */
public class InsertionSort<E> implements Sort<E> {

	public void sort(Sequence<E> sequence, Comparator<E> comparator) {
		for(int i=1; i<sequence.size(); i++) {
			int prevKey = i-1;
			while(prevKey>=0 && comparator.compare(sequence.get(prevKey), sequence.get(prevKey+1))>0) {
				sequence.swap(prevKey, prevKey+1);
				prevKey--;
			}
		}
	}

	public String toString() {
		return "Insertion Sort";
	}
	
}
