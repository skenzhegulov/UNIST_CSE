
import java.util.Comparator;

/**
 * Quick sort algorithm.
 *
 * @param <E> type of element to be sorted
 */
public class QuickSort<E> implements Sort<E> {

	public void sort(Sequence<E> sequence, Comparator<E> comparator) {
		QS(0, sequence.size()-1, sequence, comparator);
	}

	private void QS(int l, int r, Sequence<E> seq, Comparator<E> comp){
		int i = l, j = r;
		int num = l+(r-l)/2;
		while(i <= j){
			while(comp.compare(seq.get(num), seq.get(i))>0) i++;
			while(comp.compare(seq.get(j), seq.get(num))>0) j--;
			if(i<=j) {
				seq.swap(i,j);
				if (i==num) num=j; else
				if (j==num) num=i;
				i++; j--;
			}
		}
		if(l<j) QS(l,j, seq, comp);
		if(i<r) QS(i,r, seq, comp);
	}

	public String toString() {
		return "Quick Sort";
	}
}
