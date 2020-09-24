#include <iostream>
using namespace std;
 
int k;
 
inline bool inRange(int cur, int bound1, int bound2) {
    return bound1 <= cur && bound2 >= cur;
}
 
void find(int* a, int low, int high) {
    int i = low;
    int j = high;
    int x = a[low + (high - low) / 2];
    do {
        while (a[i] < x) ++i;
        while (a[j] > x) --j;
        if (i <= j) {
            swap(a[i], a[j]);
            i++; j--;
        }
    } while (i <= j);
    if (low < j && inRange(k, low, j)) {
        find(a, low, j);
    }
    if (i < high && inRange(k, i, high)) {
        find(a, i, high);
    }
}
 
int main() {
    int i, l, r, n, m;
    cin >> n;
    int* array = new int[n];
    for (i = 0; i < n; i++)
        cin >> array[i];
    cin >> m;
    for (i = 0; i < m; i++) {
        cin >> l >> r >> k;
        l--; r--; k--;
        int* subArray = new int[r - l + 1];
        memcpy(subArray, array + l, sizeof(int) * (r - l + 1));
        find(subArray, 0, r - l);
        cout << subArray[k] << endl;
        delete[] subArray;
    }
}
