// wordle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
#include <algorithm>
#include <fstream>
using namespace std;
string arrayOfWords[10] = {
		"лошадь",
		"правда",
		"судьбоносный",
		"поддубный",
		"код",
		"horse",
		"queue",
		"presentation",
		"delete",
		"git"
};
string newWord() {
	srand(time(0));
	int len = arrayOfWords->length();
	return arrayOfWords[rand() % len];
}
void infile(int Ball) {
	cout << "Введите имя:";
	string name;
	cin >> name;
	ifstream fs;
	fs.open("Records.txt");
	vector<pair<int, string>> records;
	string msg;
	string val;
	string nick;
	while (getline(fs,msg)) {
		if (msg != "") {
			for (int i = 0; i < msg.size(); i++) {
				if (msg[i]>=48 && msg[i]<=57) {
					val += msg[i];
				}
				else if (msg[i] != 58) {
					nick += msg[i];
				}
			}
			records.push_back(pair<int, string>(stoi(val), nick));
			val = "";
			nick = "";
		}
	}
	fs.close();
	ofstream of;
	of.open("Records.txt", std::ios::in);
	bool bl = true;
	if (records.empty()) {
		records.push_back(pair<int, string>(Ball, name));
	}
	else {
		for (int i = 0; i < records.size(); i++) {
			if (records[i].second == name) {
				if (records[i].first < Ball) {
					records[i].first = Ball;
				}
				bl = false;
				break;
			}
		}
		if (bl) {
			records.push_back(pair<int, string>(Ball, name));
		}
		std::sort(records.rbegin(),records.rend());
	}
	for (int i = 0; i < records.size(); i++) {
		of << records[i].first << ":" << records[i].second<<endl;
	}
	of.close();
}
void fromfile() {
	string msg;
	ifstream fs;
	fs.open("Records.txt");
	cout << "Топ 3 игрока:" << endl;
	for (int i = 0; i < 3; i++) {
		if (getline(fs, msg)) {
			cout << msg << endl;
		}
	}
	fs.close();
}
string checkWor(string word, string player) {

	string correct(word.size(), '_');
	vector<char> cor;
	for (int i = 0; i < player.size(); i++) {
		if (word[i] == player[i]) {
			correct[i] = word[i];
			cor.push_back(word[i]);
			word.replace(i, 1, "!");
			player.replace(i, 1, "?");
		}
	}
	for (int i = 0; i < player.size(); i++) {
		if (player[i] == char("?")) {
			break;
		}
		for (int j = 0; j < word.size(); j++) {
			if (word[j] == player[i]) {
				cor.push_back(word[j]);
				word.replace(j, 1, "!");
				break;
			}
		}
	}
	cout << "Отгаданные буквы:";
	for (int i = 0; i < cor.size(); i++) {
		cout << cor[i] << ",";
	}
	cout << endl;
	cout << "Слово:" << correct << endl;
	return correct;
}
void game(int play, int n, int Ball) {
	while (play == 1) {
		string Word = newWord();
		cout << "Длина слова:" << Word.length() << endl;
		int Sum;
		for (int i = 0; i < n; i++) {
			string player;
			cout << "Клиент:" << endl;
			cin >> player;
			string Word1 = checkWor(Word, player.substr(0, Word.length()));
			if (Word1 == Word) {
				switch (i)
				{
				case(0):
					Sum = 5;
					break;
				case(1):
					Sum = 4;
					break;
				case(2):
					Sum = 3;
					break;
				case(3):
					Sum = 2;
					break;
				default:
					Sum = 1;
					break;
				}
				break;
			}
			else if (i == n - 1) {
				Sum = 0;
			}
		}
		if (Sum == 0) {
			cout << "Попытки закончились! Ваши баллы:" << Ball << endl;
			break;
		}
		Ball += Sum;
		cout << "Вы заработали " << Ball << " баллов. Хотите продолжить? (y/n)" << endl;
		string res;
		cin >> res;
		while (true) {
			if (res == "n") {
				play = 0;
				cout << "Вы заработали " << Ball << " баллов." << endl;
				infile(Ball);
				break;
			}
			else if (res == "y") {
				play = 1;
				break;
			}
			else {
				cout << "Wrong answer!" << endl;;
			}
			cin >> res;
		}
	}
	fromfile();
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n = 5;
	int play = 1;
	int Ball = 0;
	game(play, n, Ball);
	return 0;

}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
