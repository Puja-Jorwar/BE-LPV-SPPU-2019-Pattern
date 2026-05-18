#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Merge function
void merge(vector<int>& arr, int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {

        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Sequential Merge Sort
void sequentialMergeSort(vector<int>& arr, int left, int right) {

    if (left < right) {

        int mid = (left + right) / 2;

        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int left, int right) {

    if (left < right) {

        int mid = (left + right) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, left, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);
    }
}

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n), arr2(n);

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++) {

        cin >> arr[i];
        arr2[i] = arr[i];
    }

    // Sequential Merge Sort
    double start1 = omp_get_wtime();

    sequentialMergeSort(arr, 0, n - 1);

    double end1 = omp_get_wtime();

    // Parallel Merge Sort
    double start2 = omp_get_wtime();

    parallelMergeSort(arr2, 0, n - 1);

    double end2 = omp_get_wtime();

    cout << "\nSequential Merge Sort:\n";

    for (int x : arr)
        cout << x << " ";

    cout << "\nTime Taken: "
         << end1 - start1 << " seconds\n";

    cout << "\nParallel Merge Sort:\n";

    for (int x : arr2)
        cout << x << " ";

    cout << "\nTime Taken: "
         << end2 - start2 << " seconds\n";

    return 0;
}

// Sample Input:
// Enter number of elements: 6
// Enter elements:
// 38 27 43 3 9 82
//
// Sample Output:
//
// Sequential Merge Sort:
// 3 9 27 38 43 82
// Time Taken: 0.000002 seconds
//
// Parallel Merge Sort:
// 3 9 27 38 43 82
// Time Taken: 0.000145 seconds




// To Enable OpenMP in Dev-C++
//
// 1. Go to:
//    Tools -> Compiler Options
//
// 2. In "General" tab,
//    tick:
//    "Add the following commands when calling compiler"
//
// 3. Write:
//    -fopenmp
//
// 4. Click OK
