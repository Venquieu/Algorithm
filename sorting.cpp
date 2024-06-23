#include <vector>

namespace sorting {
    template<typename T>
    int Partition(std::vector<T>* arr, const int left, const int right) {
        T pivot = arr->at(right);
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (arr->at(j) < pivot) {
                i++;  // now i points to the first element greater than pivot
                std::swap(arr->at(i), arr->at(j));
            }
        }
        std::swap(arr->at(i + 1), arr->at(right));
        return i + 1;
    }

    template<typename T>
    void QuickSort(std::vector<T>* arr, const int left, const int right) {
        if (left < right) {
            int pivot = Partition(arr, left, right);
            QuickSort(arr, left, pivot - 1);
            QuickSort(arr, pivot + 1, right);
        }
    }
}