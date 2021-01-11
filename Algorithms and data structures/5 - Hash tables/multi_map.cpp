#include <iostream>
#include <string>
#include <vector>
using namespace std;

const long M = 111111;

class Map {
	const int A = 73;
	const long P = 4998787;

public:
	vector<pair<string, string>>* arr;

	Map() {
		arr = new vector<pair<string, string>>[M];
	}

	void put(string key, string value) {
		long hash = hashFunction(key);
		long size = arr[hash].size();
		for (long i = 0; i < size; i++) {
			if (arr[hash][i].first == key && arr[hash][i].second == value) {
				return;
			}
		}
		arr[hash].push_back(make_pair(key, value));
	}

	vector<string> get(string key) {
		long hash = hashFunction(key);
		long size = arr[hash].size();
		vector<string> answer;
		for (int i = 0; i < size; i++) {
			if (arr[hash][i].first == key)
				answer.push_back(arr[hash][i].second);
		}
		return answer;
	}

	void del(string key, string value) {
		long hash = hashFunction(key);
		long size = arr[hash].size();
		for (long i = 0; i < size; i++) {
			if (arr[hash][i].first == key && arr[hash][i].second == value) {
				arr[hash].erase(arr[hash].begin() + i);
				break;
			}
		}
	}

	void delAll(string key) {
		long hash = hashFunction(key);
		int i = 0;
		while (arr[hash].size() > 0) {
			if (arr[hash][i].first == key)
				arr[hash].erase(arr[hash].begin() + i);
			else
				i++;
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
	vector<string> a;
	while (cin >> operation) {
		if (operation == "put") {
			cin >> key >> value;
			map.put(key, value);
		}
		else if (operation == "get") {
			cin >> key;
			a = map.get(key);
			cout << a.size() << " ";
			for (int i = 0; i < a.size(); i++)
				cout << a[i] << " ";
			cout << '\n';
		}
		else if (operation == "delete") {
			cin >> key >> value;
			map.del(key, value);
		}
		else if (operation == "deleteall") {
			cin >> key;
			map.delAll(key);
		}
	}
}