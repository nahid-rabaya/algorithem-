
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// ---------- Sorting Algorithms ----------

// Bubble Sort (Stable, Simple)
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// Merge Sort (Stable, O(n log n))
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0, j = 0, k = left;
    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort (Not stable, Fast average case)
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ---------- Helper Functions ----------

vector<int> generateData(int size, string type) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i)
        arr[i] = rand() % 100000;

    if (type == "sorted") {
        sort(arr.begin(), arr.end());
    } else if (type == "reversed") {
        sort(arr.begin(), arr.end(), greater<int>());
    }
    return arr;
}

template<typename SortFunc>
long long measure(SortFunc sortFunc, vector<int> data) {
    auto start = high_resolution_clock::now();
    sortFunc(data);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

void runAllSorts(vector<int> base, int size, const string& label) {
    cout << "\n--- Input Type: " << label << ", Size: " << size << " ---" << endl;

    auto b1 = base;
    auto b2 = base;
    auto b3 = base;

    auto bubbleTime = measure([](vector<int> v) { bubbleSort(v); }, b1);
    cout << "Bubble Sort: " << bubbleTime << " µs" << endl;

    auto mergeTime = measure([&](vector<int> v) { mergeSort(v, 0, v.size() - 1); }, b2);
    cout << "Merge Sort:  " << mergeTime << " µs" << endl;

    auto quickTime = measure([&](vector<int> v) { quickSort(v, 0, v.size() - 1); }, b3);
    cout << "Quick Sort:  " << quickTime << " µs" << endl;
}

// ---------- Main ----------

int main() {
    srand(time(0));
    vector<int> sizes = {100, 200, 1000, 5000, 10000}; // تمّت إضافة 200 و10000
    vector<string> types = {"random", "sorted", "reversed"};

    for (int size : sizes) {
        for (const string& type : types) {
            vector<int> dataset = generateData(size, type);
            runAllSorts(dataset, size, type);
        }
    }

    return 0;
}
