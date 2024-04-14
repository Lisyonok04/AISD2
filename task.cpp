#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <string>

using namespace std;

char get_roman_num() {
	string mass = "IVXLCDM";
	int randomIndex = rand() % mass.size();
	char result = mass[randomIndex];
	return result;
}

template<typename K, typename T>
class HashTable {
private:
	const size_t _min_size = 10;
	size_t _count;
	enum State { empty, filled, deleted };
	template<typename K, typename T>
	struct Node {
		K key;
		T value;
		State status;
		Node() : key(NAN), value(NAN), status(empty) {};
		void print() {
			if (status == filled) {
				cout << key << ":" << value << endl;
			}
		}
		void del() {
			key = nullptr;
			value = nullptr;
			status = deleted;
		}
	};
	vector <Node<K, T>> _data;
	template<typename T>
	size_t h(T key) {
		return static_cast<int>(fmod((1.0 * 435769 * int(key) / (2 << 16)), 1) * _data.size());
	}
	template<>
	size_t h<string>(string key) {
		unsigned int hash = 0;
		for (char c : key) {
			hash = (hash * 435769 + c) % _data.size();
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

	/*HashTable(size_t len, size_t count) {
		for (int i = 0, i < count, i++) {
			
		}
	}*/

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
		if (search(key))
			return false;
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
		if (search(key))
			return false;
		size_t position = h(key);
		_data[position].key = key;
		_data[position].value = value;
		if (_data[position].status != filled) {
			_data[position].status = filled;
			count++;
		}
		return true;
	}

	T* search(K key) {
		size_t position = h(key);
		if (_data[position].key == key) {
			return &_data[position].value;
		}
		else {
			int i = 1;
			while (true) {
				position = (position + i) % _data.size();
				if ((position == h(key)) || (_data[position].status == empty)) {
					return nullptr;
				}
				if (_data[position].key == key) {
					return &_data[position].value;
				}
				i++;
			}
		}
	}

	bool erase(K key) {
		size_t position = h(key);
		if (_data[position].key == key) {
			_data[position].key = NAN;
			_data[position].value = NAN;
			_data[position].status = deleted;
			_count--;
			return true;
		}
		else {
			int i = 1;
			while (true) {
				position = (position + i) % _data.size();
				if (_data[position].key == key) {
					_data[position].key = NAN;
					_data[position].value = NAN;
					_data[position].status = deleted;
					_count--;
					return true;
				}
				i++;
			}
		}
	}

	int count(K key) {
		int count = 0;
		for (auto& i : _data) {
			if (h(i.key) == h(key)) {
				count++;
			}
		}
		return count;
	}
};

void roman_num(HashTable<char, int>& table) {
	table.insert('I', 1);
	table.insert('V', 5);
	table.insert('X', 10);
	table.insert('L', 50);
	table.insert('C', 100);
	table.insert('D', 500);
	table.insert('M', 1000);
}
int roman_to_arabic(string roman_num, HashTable<char, int>& table) {
	int result = 0;
	int prevValue = 0;
	for (int i = roman_num.length() - 1; i >= 0; i--) {
		int value = *table.search(roman_num[i]);
		if (value < prevValue)
			result -= value;
		else
			result += value;
		prevValue = value;
	}
	return result;

}