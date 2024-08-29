#include<stdio.h>
#include <math.h>

#define N 10
int heap[100], n=0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


bool is_min_level(int index) {
    int level = 0;
    while (index > 0) {
        index = (index - 1) / 2;
        level++;
    }
    return (level % 2 == 0);
}


void grand_parent_level(int ind)
{	
	if((ind == 0) || (ind == 1) || (ind == 2)){
		return;
	}
	int g_p_ind = (((ind - 1) / 2) - 1) / 2;

	if(is_min_level(ind)){
		if(heap[ind] < heap[g_p_ind]){

			swap(&heap[ind], &heap[g_p_ind]);
			grand_parent_level(g_p_ind);
		}
	}
	else{
		if(heap[ind] > heap[g_p_ind]){
			swap(&heap[ind], &heap[g_p_ind]);
			grand_parent_level(g_p_ind);
		}
	}
}



void parent_level(int val)
{
	int parent_ind = ((n-1) / 2);

	if(is_min_level(n)){
		if(heap[parent_ind] > val){
			heap[n] = val;
			grand_parent_level(n);
			n++;

		}
		else{
			heap[n] = val;
			swap(&heap[parent_ind], &heap[n++]);
			grand_parent_level(parent_ind);
		}
	}

	else{
		if(heap[parent_ind] < val){
			heap[n] = val;
			grand_parent_level(n);
			n++;

		}
		else{
			heap[n] = val;
			swap(&heap[parent_ind], &heap[n++]);
			grand_parent_level(parent_ind);
		}	
	}
}

void insert(int val){
	if(n == 0){
			heap[n++] = val;
			return;}
	else if((n==1) || (n==2)){
		if(heap[0] < val)
			heap[n++] = val;
		else{
			heap[n] = val;
			swap(&heap[0], &heap[n++]);
		}
		return;
	}
	else{
		parent_level(val);
	}
}

void heapify(int *arr){
	for (int i = 0; i < N; i++)
	{
		insert(arr[i]);
	}
}

// int minimun(int ind){
// 	int child1 = (2*ind) + 1;
// 	int child2 = (2*ind) + 2;
// 	if heap[child1] < heap[ind]{
// 		swap(&heap[child1],&heap[ind]);
// 		return child1;
// 	}
// 	else if heap[child2] < heap[ind]{
// 		swap(&heap[child2],&heap[ind]);
// 		return child2;
// 	}
// 	return ind;
// }

// int deleteMin(int ind){
// 	int min = heap[ind];
// 	int grand_child = (2 * ((2 * ind) + 1)) + 1;
// 	int level = (int)log2(grand_child + 1);
// 	int num_grand_child = pow(2, level);

// 	// Not having grand child
// 	if(grand_child >= n){
// 		child_ind = ((2*ind)+1);
// 		//Not having child
// 		if(child_ind>=n){
			
// 		}
// 		//Having child
// 		else{

// 		}
// 	}
// 	// Having grand child
// 	else{
// 		int new_min_ind = grand_child;
// 		for (int i=grand_child+1;i<grand_child + num_grand_child;++i)
// 		{
// 			if(heap[new_min_ind] > heap[i]){
// 				new_min_ind = i;
// 			}
// 		}
// 		deleteMin(new_min_ind);
// 	}
// }

int deleteMin(int arr[]){
	int min = heap[0];
	for(int i=1;i<N;i++){
		arr[i-1] = heap[i];
	}
	n=0;
	for(int i=0;i<N-1;i++){
		insert(arr[i]);
	}
	return min;

}

int deleteMax(int arr[]){
	int max, max_ele;
	if(heap[1] > heap[2])	max = 1;
	else	max = 2;
	max_ele = heap[max];
	int j=0;

	for(int i=0;i<N;i++){
		if(i == max)	continue;
		arr[j++] = heap[i];
	}
	n=0;
	for(int i=0;i<N-1;i++){
		insert(arr[i]);
	}
	return max_ele;

}


int main()
{
	int arr[] = {2, 7, 3, 9, 10, 6, 4, 1, 0, 12};
	heapify(arr);
	int min = deleteMin(arr);
	int max = deleteMax(arr);
	// insert(103);
	
	printf("\n");
	for(int i=0;i<n-1;i++)
		printf("%d ", heap[i]);

	printf("\n%d  %d\n", min, max);

	return 0;
}