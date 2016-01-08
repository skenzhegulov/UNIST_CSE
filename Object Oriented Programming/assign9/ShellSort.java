
import java.util.Comparator;

/**
 * Shell sort algorithm.
 * 
 * @param <E> type of element to be sorted
 */
public class ShellSort<E> implements Sort<E> {

	public void sort(Sequence<E> sequence, Comparator<E> comparator) {
		for(int gap = sequence.size()/2; gap>0; gap = gap == 2 ? 1 : (int) (gap/2.2) )
			for(int i = gap; i<sequence.size(); i++) {
					for(int j=i; j>=gap && comparator.compare(sequence.get(j-gap), sequence.get(j))>0; j-=gap) sequence.swap(j, j-gap);
			}
	}
	
	public String toString() {
		return "Shell Sort";
	}
}
