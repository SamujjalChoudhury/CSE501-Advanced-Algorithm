# Define constants
MAX_SIZE = 100

# Initialize global variables
heap = []
size = 0

def is_min_level(index):
    """Determine if the level of the node at `index` is a Min level."""
    level = 0
    while index > 0:
        index = (index - 1) // 2
        level += 1
    return level % 2 == 0

def swap(heap, i, j):
    """Swap elements at index i and j in the heap."""
    heap[i], heap[j] = heap[j], heap[i]

def percolate_up_min(heap, index):
    """Percolate up from Min level to maintain heap property."""
    grandparent = (index - 3) // 4
    if grandparent >= 0 and heap[index] < heap[grandparent]:
        swap(heap, index, grandparent)
        percolate_up_min(heap, grandparent)

def percolate_up_max(heap, index):
    """Percolate up from Max level to maintain heap property."""
    grandparent = (index - 3) // 4
    if grandparent >= 0 and heap[index] > heap[grandparent]:
        swap(heap, index, grandparent)
        percolate_up_max(heap, grandparent)

def percolate_up(heap, index):
    """Percolate up to maintain Min-Max Heap properties."""
    if index == 0:
        return
    parent = (index - 1) // 2
    
    if is_min_level(index):
        if heap[index] > heap[parent]:
            swap(heap, index, parent)
            percolate_up_max(heap, parent)
        else:
            percolate_up_min(heap, index)
    else:
        if heap[index] < heap[parent]:
            swap(heap, index, parent)
            percolate_up_min(heap, parent)
        else:
            percolate_up_max(heap, index)

def insert(heap, value):
    """Insert a new value into the Min-Max Heap."""
    global size
    if size >= MAX_SIZE:
        print("Heap overflow!")
        return
    
    heap.append(value)
    size += 1
    percolate_up(heap, size - 1)

def print_heap(heap):
    """Print the heap."""
    print("Min-Max Heap:", heap)

def main():
    global size
    elements = [5.0, 7.5, 12.5, 17.5, 25.0, 27.5, 42.5, 47.5]
    
    for element in elements:
        insert(heap, element)
    
    print_heap(heap)

if __name__ == "__main__":
    main()
