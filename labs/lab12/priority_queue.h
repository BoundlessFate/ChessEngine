#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
	private:
		std::vector<T> m_heap;

	public:
		priority_queue() {}

		priority_queue( std::vector<T> const& values )
		{
			m_heap = values;
			for (int i = (m_heap.size() - 1) /2; i>=0; i--)
				percolate_down();
		}

		const T& top() const 
		{
			assert( !m_heap.empty() );
			return m_heap[0]; 
		}

		void push( const T& entry )
		{
			m_heap.push_back(entry);
			percolate_up();
		}

		void percolate_up() {
			int index = m_heap.size() - 1;
			while (index > 0) {
				int parent = (index - 1) / 2;
				if (m_heap[index] < m_heap[parent]) {
					std::swap(m_heap[index], m_heap[parent]);
					index = parent;
				} else
					break;
			}
		}
		void percolate_down() {
			int index = 0;
			while (index * 2 + 1 < m_heap.size()) {
				int first = index * 2 + 1;
				int second = index * 2 + 2;
				int smaller = m_heap.size();
				if (first >= m_heap.size())
					smaller = second;
				else if (second >= m_heap.size())
					smaller = first;
				else if (second <= m_heap.size() && m_heap[first] > m_heap[second])
					smaller = second;
				else
					smaller = first;
				if (m_heap[index] > m_heap[smaller]) {
					std::swap(m_heap[index], m_heap[smaller]);
					index = smaller;
				} else
					break;
			}
		}

		void pop() 
		{
			assert(!m_heap.empty());
			m_heap[0] = m_heap[m_heap.size() - 1];
			m_heap.erase(m_heap.begin() + m_heap.size() - 1);
			percolate_down();
		}

		int size() { return m_heap.size(); }
		bool empty() { return m_heap.empty(); }


		//  The following three functions are used for debugging.

		//  Check to see that internally the heap property is realized.
		bool check_heap( )
		{
			return this->check_heap( this->m_heap );
		}

		//  Check an external vector to see that the heap property is realized.
		bool check_heap( const std::vector<T>& heap )
		{
			const unsigned int size = heap.size();
			for (unsigned int i=0; i<size; i++) {
				unsigned int left = i * 2 + 1;
				unsigned int right = i* 2 + 2;
				if ((left < size && heap[i] > heap[left]) || (right < size && heap[i] > heap[right]))
					return false;
			}
			return true;
		}

		//  A utility to print the contents of the heap.  Use it for debugging.
		void print_heap( std::ostream & ostr )
		{
			for ( unsigned int i=0; i<m_heap.size(); ++i )
				ostr << i << ": " << m_heap[i] << std::endl;
		}

};


	template <class T>
void heap_sort( std::vector<T> & v )
{
	priority_queue<T> queue(v);
	for (unsigned int i=0; i<v.size(); i++) {
		v[i] = queue.top();
		queue.pop();
	}
}

#endif
