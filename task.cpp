#pragma once
#include <iostream>
#include <vector>
#include <random>

using namespace std;


template<typename K, typename T>
class HashTable {
private:
	const size_t _min_size = 10;
	vector <Node<K, T>> _data;
	size_t _count;
	enum state = { empty, filled, deleted };
	struct Node {
		K* key;
		T* value;
		state status;
		Node() : key(nullptr), value(nullptr), status(empty) {};
		void print() {
			cout << key << ":" << value << endl;
		}
		void del() {
			key = nullptr;
			value = nullptr;
			status = deleted;
		}
	};
	size_t h(K key) {

	};
public:

	HashTable() { 
		_data.resize(_min_size);
		_count = 0;
	}

	HashTable(size_t size) {
		_data.resize(size);
		_count = 0;
	}

	HashTable(HashTable <K, T>& other) {
		_data = other._data;
		_count = other._count;
	}
	~HashTable() = default;

	HashTable<K, T>& operator=(HashTable<K, T>& other) {
		if (this == &other) {
			return *this;
		}
		_data = other._data;
		_count = other._count;
	}

	void print() {
		for (auto& i : _data) {
			i.print();
		}
	}

	bool contains(T value) {
		for (auto& i : _data) {
			if (i.value == value) {
				return true;
			}
		}
		return false;
	}
};