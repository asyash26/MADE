#include <iostream>
#include <string>

using namespace std;

int main() {
    string targetString;
    cin >> targetString;
    int left = 0, right = 0, stringSize = targetString.size();
    int z[stringSize];
    for (int i = 1; i < stringSize; i++) {
        z[i] = max(0, min(right - i, z[i - left]));
        while ((i + z[i] < stringSize) && (targetString[z[i]] == targetString[i + z[i]]))
            z[i]++;
        if (i + z[i] > right) {
            left = i;
            right = i + z[i];
        }
    }
    for (int i = 1; i < stringSize; i++) {
        cout << z[i] << " ";
    }
    return 0;
}
