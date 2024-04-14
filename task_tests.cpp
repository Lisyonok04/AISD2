#include "task.cpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>

TEST(create, test) {
	HashTable<char, int> table1(12);
	table1.insert('a', 12);
	table1.insert('b', 16);
	table1.insert('c', 21);
	table1.insert('d', 90);
	table1.print();
	cout << *table1.search('d') << endl;
	table1.erase('b');
	table1.insert('a', 13);
	table1.print();
	cout << table1.count('a') << endl;
	cout << table1.count('c') << endl;
	cout << table1.count('d') << endl;
}

TEST(roman, test) {
	HashTable<char, int> table1(10);
	roman_num(table1);
	string roman_num = "MIVV";
	cout << roman_num << " --> " << roman_to_arabic(roman_num, table1) << endl;
	roman_num = "XIV";
	cout << roman_num << " --> " << roman_to_arabic(roman_num, table1) << endl;
}