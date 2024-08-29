#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 100

int size = 0;
int heap[MAX_SIZE];

bool is_min_level(int index) {
    int level = 0;
    while (index > 0) {
        index = (index - 1) / 2;
        level++;
    }
    return (level % 2 == 0);
}

void swap(int *heap, int i, int j) {
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void percolate_up_min(int *heap, int index) {
    int grandparent = (index - 3) / 4;
    if (grandparent >= 0 && (heap[index] < heap[grandparent])) {
        swap(heap, index, grandparent);
        percolate_up_min(heap, grandparent);
    }
}

void percolate_up_max(int *heap, int index) {
    int grandparent = (index - 3) / 4;
    if (grandparent >= 0 && (heap[index] > heap[grandparent])) {
        swap(heap, index, grandparent);
        percolate_up_max(heap, grandparent);
    }
}

void percolate_up(int *heap, int index) {
    if (index == 0) {
        return;
    }
    int parent = (index - 1) / 2;

    if (is_min_level(index)) {
        if (heap[index] > heap[parent]) {
            swap(heap, index, parent);
            percolate_up_max(heap, parent);
        } else {
            percolate_up_min(heap, index);
        }
    } else {
        if (heap[index] < heap[parent]) {
            swap(heap, index, parent);
            percolate_up_min(heap, parent);
        } else {
            percolate_up_max(heap, index);
        }
    }
}

void percolate_down_min(int *heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int minChild = index;

    if (left < size && heap[left] < heap[minChild]) {
        minChild = left;
    }

    if (right < size && heap[right] < heap[minChild]) {
        minChild = right;
    }

    if (minChild != index) {
        swap(heap, index, minChild);
        percolate_down_min(heap, minChild);
    }
}

void percolate_down_max(int *heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int maxChild = index;

    if (left < size && heap[left] > heap[maxChild]) {
        maxChild = left;
    }

    if (right < size && heap[right] > heap[maxChild]) {
        maxChild = right;
    }

    if (maxChild != index) {
        swap(heap, index, maxChild);
        percolate_down_max(heap, maxChild);
    }
}

void percolate_down(int *heap, int index) {
    if (index == 0) {
        percolate_down_min(heap, index);
    } else if (is_min_level(index)) {
        percolate_down_max(heap, index);
    } else {
        percolate_down_min(heap, index);
    }
}

void insert(int value) {
    if (size >= MAX_SIZE) {
        printf("Heap overflow!\n");
        return;
    }

    heap[size] = value;
    size++;
    percolate_up(heap, size - 1);
}

void delete_min() {
    if (size == 0) {
        printf("Heap is empty!\n");
        return;
    }

    // Replace the root with the last element
    heap[0] = heap[size - 1];
    size--;

    // Percolate down from the root to restore heap properties
    percolate_down(heap, 0);
}

void delete_max() {
    if (size == 0) {
        printf("Heap is empty!\n");
        return;
    }

    // Find the index of the maximum element
    int max_index = 0;
    for (int i = 1; i < size; i++) {
        if (!is_min_level(i) && heap[i] > heap[max_index]) {
            max_index = i;
        }
    }

    // Replace the max element with the last element
    heap[max_index] = heap[size - 1];
    size--;

    // Percolate down from the max_index to restore heap properties
    percolate_down(heap, max_index);
}

void print_heap(int heap[]) {
    printf("Min-Max Heap: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int main() {
    // Example of filling the heap with some values
    // heap[0] = 2;
    // heap[1] = 17;
    // heap[2] = 19;
    // heap[3] = 5;
    // heap[4] = 7;
    // heap[5] = 11;
    // heap[6] = 3;

    heap[0] = 5;
    heap[1] = 42;
    heap[2] = 47;
    heap[3] = 12;
    heap[4] = 17;
    heap[5] = 27;
    heap[6] = 7;


    size = 7;

    // Print the heap before deletion
    printf("Heap before deletions:\n");
    print_heap(heap);

    // Insert a new value
    insert(1);
    printf("Heap after insertion:\n");
    print_heap(heap);

    // Delete the minimum element
    delete_min();
    printf("Heap after deletion of min:\n");
    print_heap(heap);

    // Delete the maximum element
    delete_max();
    printf("Heap after deletion of max:\n");
    print_heap(heap);

    return 0;
}
