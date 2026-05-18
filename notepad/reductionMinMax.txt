#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int minVal = arr[0];
    int maxVal = arr[0];
    int sum = 0;

    // Parallel reduction for sum
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    // Parallel reduction for minimum
    #pragma omp parallel for reduction(min:minVal)
    for (int i = 0; i < n; i++) {
        if (arr[i] < minVal)
            minVal = arr[i];
    }

    // Parallel reduction for maximum
    #pragma omp parallel for reduction(max:maxVal)
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    double average = (double)sum / n;

    cout << "\nMinimum Value = " << minVal;
    cout << "\nMaximum Value = " << maxVal;
    cout << "\nSum = " << sum;
    cout << "\nAverage = " << average;

    return 0;
}