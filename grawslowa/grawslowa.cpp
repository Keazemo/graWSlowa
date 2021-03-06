// grawslowa.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <list>
#include <time.h>
using namespace std;
fstream bankSlow;
int dlugoscHasla;
list<string> zbiorOdpowiedzi;
list<char> znakiDoLosowania = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'w', 'x', 'y', 'z'}; // 15
list<char> juzWylosowane = {};
list<int> wylosowaneIndexy = {};
char letters[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'w', 'x', 'y', 'z' };
void setWords(unsigned int wordsLong);
void updateLista(string x);
string setChar(int position, char znak, string odpowiedzHandle);
//char losujZnak();
bool czyGra = false;
bool czyKoniec(string x);
int howMuchWords();
int lettersInZbiorOdpowiedzi[24] = { };
void getLetters();
int getMax();
int main()
{
	srand(time(NULL)); //fajnie że random musi mieć ziarno XD
	bankSlow.open("slowa.txt");
	cout << "Dlugosc mojego hasla wynosi ";
	cin >> dlugoscHasla; //pobranie długości hasła
	cout << "Pobieram liste hasel!" << endl;
	setWords(dlugoscHasla);//pobranie haseł ze względu na długość wyrazu
	string odpowiedz;
	for (int i = 1; i <= dlugoscHasla; i++) {
		odpowiedz.append("?"); //budowanie odpowiedzi - dodawanie '?'
	}
	char wylosowanyZnak, czyZawiera;
	int counter = 0;
	int ileRazyZnak;
	unsigned int ktoryZnak;
	do{
		getLetters();
		//cout << "Jest "<< howMuchWords()<< "takich słów"<<endl; //sprawdzenie ile słów 
		cout << odpowiedz << endl;
		for (int i = 1; i <= odpowiedz.length(); i++) {
			cout << i;
		}
		wylosowanyZnak = letters[getMax()]; // losowanie znaku do gry
		cout << "\nCzy twoje slowo zawiera litere " << wylosowanyZnak << "?\n";
		cin >> czyZawiera;
		if (czyZawiera == 't' || czyZawiera == 'y' || czyZawiera == 'tak') { //czy trafiono (użytkownik wpisał t/y/tak/yes
			cout << "Ile razy? ";
			cin >> ileRazyZnak; //ile razy jest danych liter
			for (int i = 1; i <= ileRazyZnak; i++) {
				cout << "W ktorym miejscu? ";
				cin >> ktoryZnak;
				odpowiedz = setChar(ktoryZnak, wylosowanyZnak, odpowiedz); //aktualizacja odpowiedzi przy trafieniu
			}
		}
		updateLista(odpowiedz); //aktualizacja listy możliwych haseł
		counter++; //licznik ruchów
		czyGra = czyKoniec(odpowiedz); //sprawdzenie czy gra ukończona (czy są '?')
	} while (!czyGra);
	cout << "Pokonalem cie w " << counter << " rundach!\n Twoje slowo to: " << odpowiedz << endl;
	bankSlow.close();
	system("pause");
	return 1;
}

//czy gra została skończona( nie ma żadnych znaków zapytania)
bool czyKoniec(string x) {
	for (char l : x) {
		if (l == '?') {
			return false;
		}
	}
	return true;
}

//wprowadzone hasło - wpisanie znaku zamiast '?'
string setChar(int position, char znak, string odpowiedzHandle) {
	odpowiedzHandle[position - 1] = znak;
	return odpowiedzHandle;
}

//losowanie znaku
	//sprawdzenie czy wylosowany znak nie był już używany
bool checkZnak(char x) {
	for (list<char>::iterator iter = juzWylosowane.begin(); iter != juzWylosowane.end(); iter++) {
		if (x == *iter) {
			return false;
		}
	}
	juzWylosowane.push_back(x);
	return true;
}
	//losowanie znaku (obecnie random)
/*
char losujZnak() {
	bool end = false;
	int index;
	char znak = NULL;
	do {
		index = rand()%24+1;
		int i = 1;
		for (list<char>::iterator iter = znakiDoLosowania.begin(); iter != znakiDoLosowania.end();iter++) {
			if (i == index) {
				znak = *iter;
				if (checkZnak(znak) == true) {
					end = true;

				}
				break;
			}
			i++;
		}
	} while (!end);
	return znak;
}
*/
bool checker(int i) {
	for (list<int>::iterator iter = wylosowaneIndexy.begin(); iter != wylosowaneIndexy.end(); iter++) {
		if (i == *iter) {
			return false;
		}
	}
	return true;
}
int getMax() {
	int maxObecne = -1;
	int id = 0;
	for (int i = 0; i < 24; i++) {
		if (lettersInZbiorOdpowiedzi[i] > maxObecne && checker(i)) {
			maxObecne = lettersInZbiorOdpowiedzi[i];
			id = i;
		}
	}
	wylosowaneIndexy.push_back(id);
	return id;
}
/*char losujZnak() {
	int temp = getMax();
	return letters[temp];
}*/

//lista możliwych haseł

//tworzenie listy
	//dodawanie możliwych odpowiedzi po długości znaków
void setWords(unsigned int wordsLong) {
	string tmp;
	while (!bankSlow.eof()) {
		getline(bankSlow, tmp);
		if (tmp.length() == wordsLong) {
			//cout << tmp << " " << tmp.length() << endl;
			zbiorOdpowiedzi.push_back(tmp);
		}
	}
}
//akutalizowanie listy możliwych haseł
	//funkcja sprawdzająca czy hasło należy usunąć
bool czyDoUsuniecia(string x, string y, int i) {
	if (x[i] != y[i]) {
		return true;
	}
	else {
		return false;
	}
}
	//funkcja aktualizująca listę
void updateLista(string x) {
	string temp;
	bool czyRemove;
	list<string>::iterator iter = zbiorOdpowiedzi.begin();
	for (int i = 0; i < x.length(); i++) {
		if (x[i] != '?') {
			while (iter != zbiorOdpowiedzi.end()) {
				temp = *iter;
					czyRemove = czyDoUsuniecia(x, *iter, i);
					if(czyRemove){
						iter = zbiorOdpowiedzi.erase(iter);
					}
					else {
						iter++;
					}
			}
		}
		}
	}

//countery
	//liczenie ile jest słów
int howMuchWords() {
	return zbiorOdpowiedzi.size();
}

void getLetters() {
	string znak;
	for (int i = 0; i < 24; i++) {
		lettersInZbiorOdpowiedzi[i] = 0;
	}
	char znaczek;
	auto start = zbiorOdpowiedzi.begin();
	while (start != zbiorOdpowiedzi.end()) {
		znak = *start;
		for (int i = 0; i < znak.length(); i++) {
			znaczek = znak[i];
			lettersInZbiorOdpowiedzi[znaczek - 'a']++;
		}
		start++;
	}
}
//lista znaków losujących
//list znaków wylosowanych
//funkcja losująca znak i sprawdzanie czy był
//pytanie o ten znak
//