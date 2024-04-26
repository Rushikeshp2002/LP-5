#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

struct Result {
    int min;
    int max;
    int sum;
    double average;
};

Result parallel_reduction(const vector<int>& data) {
    int num_elements = data.size();
    int min_val = data[0];
    int max_val = data[0];
    int sum = 0;

    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum)
    for (int i = 0; i < num_elements; ++i) {
        int value = data[i];
        sum += value;

        if (value < min_val) {
            min_val = value;
        }

        if (value > max_val) {
            max_val = value;
        }
    }

    double average = static_cast<double>(sum) / num_elements;

    return { min_val, max_val, sum, average };
}

int main() {
    int num_elements;
    cout << "Enter the number of elements: ";
    cin >> num_elements;

    vector<int> data(num_elements);
    cout << "Enter " << num_elements << " elements:\n";
    for (int i = 0; i < num_elements; ++i) {
        cin >> data[i];
    }

    Result result = parallel_reduction(data);

    cout << "Min: " << result.min << endl;
    cout << "Max: " << result.max << endl;
    cout << "Sum: " << result.sum << endl;
    cout << "Average: " << result.average << endl;

    return 0;
}
