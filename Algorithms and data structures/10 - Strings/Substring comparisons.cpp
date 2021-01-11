#include <iostream>
#include <string>

using namespace std;

int M = 1000001501;
int P = 101;

void init(string targetString, long long hash[], long long pow[]) {
    hash[0] = targetString[0];
    pow[0] = 1;
    for (long i = 1; i < targetString.size(); i++) {
        hash[i] = (hash[i -1] * P + targetString[i]) % M;
        pow[i] = (pow[i - 1] * P) % M;
    }
}

long getHash(long left, long right, long long hash[], long long pow[]) {
    if (left == 0)
        return hash[right];
    return (hash[right] - (hash[left - 1] * pow[right - left + 1] % M) + M) % M;

}

int main() {
    string targetString;
    long queriesCount, a, b, c, d;
    cin >> targetString;
    long long hash[targetString.size()];
    long long pow[targetString.size()];
    init(targetString, hash, pow);
    cin >> queriesCount;
    for (long i = 0; i < queriesCount; i++) {
        cin >> a >> b >> c >> d;
        if (getHash(a - 1, b - 1, hash, pow) == getHash(c - 1, d - 1, hash, pow))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
