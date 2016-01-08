// Constructor, create empty sparse matrix with (row, col)
template <class type>
Matrix<type>::Matrix(int row, int col) 
{
	headnode = new MatrixNodeType(true, 0);
	nRow = row;
	nCol = col;
	nElem = 0;
	int p = (nRow < nCol) ? nCol : nRow;
	if(!p) {headnode->right = headnode; } else 
	{
		MatrixNodeType **head = new MatrixNodeType *[p];
		for(int i=0; i<p; i++) head[i] = new MatrixNodeType(true, 0);
	}
}
			
// Constructor from istream
template <class type>
Matrix<type>::Matrix(std::ifstream& is) 
{
	is >> nRow >> nCol >> nElem;
	int p = (nRow < nCol) ? nCol : nRow;
	std::cout << "Row : " << nRow << ", Col : " << nCol << ", nElem : " << nElem << std::endl;
	headnode = new MatrixNodeType(true, 0);
	if(!p) {headnode->right = headnode;} else
	{
		MatrixNodeType **head = new MatrixNodeType *[p];
		for(int i=0; i<p; i++) head[i] = new MatrixNodeType(true, 0);
		int currentRow = 0;
		int MatrixNodeType *last = head[0];
		for(int i=0; i<nElem; i++)
		{
			TripleType t;
			is >> t.row >> t.col >> t.value;
			if(t.row > currentRow)
			{
				last->right = head[currentRow];
				currentRow = t.row;
				last = head[currrentRow];
			}
			last = last->right = new MatrixNodeType(false, &t);
			head[t.col]->next = head[t.col]->next->down = last;
		}
		last->right = head[currentRow];
		for(int i=0; i<nCol; i++) head[i]->next->down = head[i];
		for(int i=0; i<p-1; i++) head[i]->next = head[i+1];
		head[p-1]->next = headnode;
		headnode->right = head[0];
		delete [] head;
		return is;
	}
}

// Copy constructor
template <class type>
Matrix<type>::Matrix(const Matrix& a)
{
	this->headnote = new MatrixNodeType(true, 0);
	this->nRow = a.nRow;
	this->nCol = a.nCol;
	this->nElem = a.nElem;
	int p = (nRow < nCol) ? nCol : nRow;
	if(!p) this->headnode->right = this->headnode; else
	{
		MatrixNodeType **head = new MatrixNodeType *[p];
		for(int i=0; i<p; i++) head[i] = new MatrixNodeType(true, 0);
		int currentRow = 0;
		int MatrixNodeType *last = head[0];
		MatrixNodeType *curr = a.headnode->next;
		while(curr != a.headnode)
		{
			MatrixNodeType *row = curr->right;
			while(row != curr)
			{
				TripleType t;
				t.row = (row->triple).row;
				t.col = (row->triple).col;
				t.value = (row->triple).value;
				if(t.row > currentRow)
				{
					last->right = head[currentRow];
					currentRow = t.row;
					last = head[currentRow];
				}
				last = last->right = new MatrixNodeType(false, &t);
				head[t.col]->next = head[t.col]->next->down = last;
				row = row->right;
			}
		}
		last->right = head[currentRow];
		for(int i=0; i<a.nCol; i++) head[i]->next->down = head[i];
		for(int i=0; i<p-1; i++) head[i]->next = head[i];
		head[p-1]->next = this->headnode;
		this->headnode->right = head[0];
		delete [] head;
	}
	return;
}
											
// Assignment operator
template <class type>
Matrix<type>& 
Matrix<type>::operator=(const Matrix& a)
{
	// ToDo
	this->headnote = new MatrixNodeType(true, 0);
	this->nRow = a.nRow;
	this->nCol = a.nCol;
	this->nElem = a.nElem;
	int p = (nRow < nCol) ? nCol : nRow;
	if(!p) this->headnode->right = this->headnode; else
	{
		MatrixNodeType **head = new MatrixNodeType *[p];
		for(int i=0; i<p; i++) head[i] = new MatrixNodeType(true, 0);
		int currentRow = 0;
		int MatrixNodeType *last = head[0];
		MatrixNodeType *curr = a.headnode->next;
		while(curr != a.headnode)
		{
			MatrixNodeType *row = curr->right;
			while(row != curr)
			{
				TripleType t;
				t.row = (row->triple).row;
				t.col = (row->triple).col;
				t.value = (row->triple).value;
				if(t.row > currentRow)
				{
					last->right = head[currentRow];
					currentRow = t.row;
					last = head[currentRow];
				}
				last = last->right = new MatrixNodeType(false, &t);
				head[t.col]->next = head[t.col]->next->down = last;
				row = row->right;
			}
		}
		last->right = head[currentRow];
		for(int i=0; i<a.nCol; i++) head[i]->next->down = head[i];
		for(int i=0; i<p-1; i++) head[i]->next = head[i];
		head[p-1]->next = this->headnode;
		this->headnode->right = head[0];
		delete [] head;	
	}	
	return *this;
}
															
// Destructor
template <class type>
Matrix<type>::~Matrix()
{
	// ToDo
	if (!headnode) return;
	MatrixNodeType *x = headnode->right, av = 0;
	headnode->right = av;
	av = headnode;
	while(x != headnode) {
		MatrixNodeType *y = x->right;
		x->right = av;
		av = y;
		x = x->next;
	}
	headnode = 0;
}

// Add Matrix b to *this
template <class type>
Matrix<type>
Matrix<type>::operator+(const Matrix& b)
{
	Matrix<type> m(*this);
	// ToDo
	int p = (m.nRow < m.nCol) ? m.nCol : m.nRow;
	if(!p) m = b; else
	{
		MatrixNodeType **head = new MatrixNodeType *[p];
		for(int i=0; i<p; i++) head[i] = new MatrixNodeType(true, 0);
		int currentRow = 0;
		int MatrixNodeType *last = head[0];
		MatrixNodeType *curr = m.headnode->next;
		while(curr != m.headnode)
		{
			MatrixNodeType *row = curr->right;
			while(row != curr)
			{
				TripleType t;
				t.row = (row->triple).row;
				t.col = (row->triple).col;
				t.value = (row->triple).value;
				if(t.row > currentRow)
				{
					last->right = head[currentRow];
					currentRow = t.row;
					last = head[currentRow];
				}
				last = last->right = new MatrixNodeType(false, &t);
				head[t.col]->next = head[t.col]->next->down = last;
				row = row->right;
			}
		}
		last->right = head[currentRow];
		for(int i=0; i<a.nCol; i++) head[i]->next->down = head[i];
		for(int i=0; i<p-1; i++) head[i]->next = head[i];
		head[p-1]->next = head[0];
		int currentRow = 0;
		int MatrixNodeType *last, *Last;
		MatrixNodeType *curr = b.headnode->next;
		while(curr != b.headnode)
		{
			MatrixNodeType *row = curr->right;
			while(row != curr)
			{
				TripleType t;
				t.row = (row->triple).row;
				t.col = (row->triple).col;
				t.value = (row->triple).value;
				last = head[t.row];
				Last = head[t.col];
				while(last->right != head[t.row] && (last->right).col<t.col) last = last->right;
				while(Last->down != head[t.col] && (Last->down).row<t.row) Last = Last->down;
				if ((last->right).col == t.col && (Last->down).row == t.row && last->right == Last->down) (last->right).value += t.value; else 
				{	
					temp = new MatrixNodeType(false, &t);
					temp->right = last.right;
					temp->down = Last->down;
					last->right = temp;
					Last->down = temp;
				}
				row = row->right;
			}
		}
		head[p-1]->next = m.headnode;
		m.headnode->right = head[0];
		delete [] head;	
	}	
	return m;
}
																				
// Subtract Matrix b to *this
template <class type>
Matrix<type>
Matrix<type>::operator-(const Matrix& b)
{
	Matrix<type> m(*this);
	// ToDo	
	int p = (m.nRow < m.nCol) ? m.nCol : m.nRow;
	if(!p) m = b; else
	{
		MatrixNodeType **head = new MatrixNodeType *[p];
		for(int i=0; i<p; i++) head[i] = new MatrixNodeType(true, 0);
		int currentRow = 0;
		int MatrixNodeType *last = head[0];
		MatrixNodeType *curr = m.headnode->next;
		while(curr != m.headnode)
		{
			MatrixNodeType *row = curr->right;
			while(row != curr)
			{
				TripleType t;
				t.row = (row->triple).row;
				t.col = (row->triple).col;
				t.value = (row->triple).value;
				if(t.row > currentRow)
				{
					last->right = head[currentRow];
					currentRow = t.row;
					last = head[currentRow];
				}
				last = last->right = new MatrixNodeType(false, &t);
				head[t.col]->next = head[t.col]->next->down = last;
				row = row->right;
			}
		}
		last->right = head[currentRow];
		for(int i=0; i<a.nCol; i++) head[i]->next->down = head[i];
		for(int i=0; i<p-1; i++) head[i]->next = head[i];
		head[p-1]->next = head[0];
		int MatrixNodeType *last, *Last;
		MatrixNodeType *curr = b.headnode->next;
		while(curr != b.headnode)
		{
			MatrixNodeType *row = curr->right;
			while(row != curr)
			{
				TripleType t;
				t.row = (row->triple).row;
				t.col = (row->triple).col;
				t.value = -(row->triple).value;
				last = head[t.row];
				Last = head[t.col];
				while(last->right != head[t.row] && (last->right).col<t.col) last = last->right;
				while(Last->down != head[t.col] && (Last->down).row<t.row) Last = Last->down;
				if ((last->right).col == t.col && (Last->down).row == t.row && last->right == Last->down) (last->right).value += t.value; else 
				{	
					temp = new MatrixNodeType(false, &t);
					temp->right = last.right;
					temp->down = Last->down;
					last->right = temp;
					Last->down = temp;
				}
				row = row->right;
			}
		}
		head[p-1]->next = m.headnode;
		m.headnode->right = head[0];
		delete [] head;	
	}	
	return m;
}
																			
// Multiply Matrix b to *this
template <class type>
Matrix<type>
Matrix<type>:operator*(const Matrix& b)
{
	Matrix<type> m(*this);
	// ToDo	
	int p = (m.nRow < m.nCol) ? m.nCol : m.nRow;
	if(!p) m = b; else
	{
		MatrixNodeType **head = new MatrixNodeType *[p];
		for(int i=0; i<p; i++) head[i] = new MatrixNodeType(true, 0);
		int currentRow = 0;
		int MatrixNodeType *last = head[0];
		MatrixNodeType *currm = m.headnode->next;
		while(currm != m.headnode)
		{
			MatrixNodeType *rowm = currm->right;
			while(rowm != currm)
			{
				TripleType t;
				t.row = (rowm->triple).row;
				t.col = (rowm->triple).col;
				t.value = (rowm->triple).value;
				MatrixNodeType *currb = b.headnode->next;
				while(curr != b.headnode)
				{
					MatrixNodeType *rowb = currb->right;
					while(rowb != currb)
					{
						TripleType s;
						s.row = (rowb->triple).row;
						s.col = (rowb->triple).col;
						s.value = (rowb->triple).value;
						if(s.row == t.row && s.col == t.col) {
							s.value *= t.value;
							if(s.row > currentRow)
							{
								last->right = head[currentRow];
								currentRow = t.row;
								last = head[currentRow];
							}
							last = last->right = new MatrixNodeType(false, &s);
							head[t.col]->next = head[t.col]->next->down = last;
						}
						rowb = rowb->right;
					}
					currb = currb->next;
				}
				rowm = rowm->right;
			}
			currm = currm->next;
		}
		last->right = head[currentRow];
		for(int i=0; i<a.nCol; i++) head[i]->next->down = head[i];
		for(int i=0; i<p-1; i++) head[i]->next = head[i];
		head[p-1]->next = m.headnode;
		m.headnode->right = head[0];
		delete [] head;	
	}	
	return m;
}
																			
// Swap i-th row with j-th row
template <class type>
Matrix<type>& 
Matrix<type>::SwapRow(int i, int j)
{
	// ToDo
	MatrixNodeType *si, *fi, *sj, *fj, *curr = this->headnode->next;
	while(curr != headnode)
	{
		if((curr->right).row == i) 
		{
			si = curr;
			fi = curr->next;
		}
		if((curr->right).row == j)
		{
			sj = curr;
			fj = curr->next;
		}
		curr = curr->next;
	}
	curr = this->headnode->next;
	while(curr != headnode)
	{
		if((curr->right).row == i) 
		{
			curr = sj;
			curr->next = fj;
		}
		if((curr->right).row == j)
		{
			curr = si;
			curr->next = fj;
		}
		curr = curr->next;
	}
	return *this;
}																				

// Swap i-th col with j-th col
template <class type>
Matrix<type>& 
Matrix<type>::SwapCol(int i, int j)
{
	// ToDo
	MatrixNodeType *si, *fi, *sj, *fj, *curr = this->headnode->next;
	while(curr != headnode)
	{
		if((curr->down).col == i) 
		{
			si = curr;
			fi = curr->next;
		}
		if((curr->down).col == j)
		{
			sj = curr;
			fj = curr->next;
		}
		curr = curr->next;
	}
	curr = this->headnode->next;
	while(curr != headnode)
	{
		if((curr->down).col == i) 
		{
			curr = sj;
			curr->next = fj;
		}
		if((curr->down).col == j)
		{
			curr = si;
			curr->next = fj;
		}
		curr = curr->next;
	}
	return *this;
}

// Create single element in the matrix
template <class type>
Matrix<type>& 
Matrix<type>::CreateElement(int i, int j, type val)
{
	// ToDo
	
	return *this;
}

// Transpose matrix
template <class type>
Matrix<type>& 
Matrix<type>::Transpose()
{
	// ToDo

	return *this;
}

