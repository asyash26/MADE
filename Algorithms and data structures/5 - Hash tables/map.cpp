#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
const long M = 100001;
 
class Map {
	const int A = 101;
	const int P = 9584017;
 
public:
	vector<pair<string, string>>* arr;
 
	Map() {
		arr = new vector<pair<string, string>>[M];
	}
 
	void put(string key, string value) {
		long hash = hashFunction(key);
		int size = arr[hash].size();
		for (int i = 0; i < size; i++) {
			if (arr[hash][i].first == key) {
				arr[hash][i].second = value;
				return;
			}
		}
		arr[hash].push_back(make_pair(key, value));
	}
 
	string get(string key) {
		long hash = hashFunction(key);
		long size = arr[hash].size();
		for (int i = 0; i < size; i++) {
			if (arr[hash][i].first == key)
				return arr[hash][i].second;
		}
		return "none";
	}
 
	void del(string key) {
		long hash = hashFunction(key);
		long size = arr[hash].size();
		for (long i = 0; i < size; i++) {
			if (arr[hash][i].first == key) {
				arr[hash].erase(arr[hash].begin() + i);
				break;
			}
		}
	}
 
	long hashFunction(string str) {
		long hash = 0;
		int aPow = A;
		for (int i = 0; str[i]; i++) {
			hash = ((str[i] * aPow) % P + hash) % P;
			aPow = aPow * A % P;
		}
		return hash % M;
	}
 
};
 
void main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string operation, key, value;
	Map map;
	while (cin >> operation) {
		if (operation == "put") {
			cin >> key >> value;
			map.put(key, value);
		}
		else if (operation == "get") {
			cin >> key;
			cout << map.get(key) << '\n';
		}
		else if (operation == "delete") {
			cin >> key;
			map.del(key);
		}
	}
}