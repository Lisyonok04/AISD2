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
	template<typename T>
	size_t h(T key, size_t size) {
		return static_cast<int>(fmod((1.0 * 435769 * int(key) / (2 << 16)), 1) * int(size));
	}
	template<>
	size_t h<string>(string key, size_t size) {
		unsigned int hash = 0;
		for (char c : key) {
			hash = (hash * 435769 + c) % size;
		}
		return hash;
	}
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

	bool insert(K key, T value) {
		size_t position = h(key);
		if (_data[position].status != filled) {
			_data[position].key = key;
			_data[position].value = value;
			_data[position].status = filled;
			_count ++;
			return true;
		}
		else {
			int i = 1;
			while (true) {
				position = (position + i) % _data.size();
				if (_data[position].status != filled) {
					_data[position].key = key;
					_data[position].value = value;
					_data[position].status = filled;
					_count++;
					break;
				}
				i++;
			}
			return true;
		}
	}

	void insert_or_assign(K key, T value) {
		size_t position = h(key);
		_data[position].key = key;
		_data[position].value = value;
		if (_data[position].status != filled) {
			_data[position].status = fiiled;
			count++;
		}
		return true;
	}

	T* search(K key) {

	}

	bool erase(K key) {

	}

	int count(K key) {

	}
};