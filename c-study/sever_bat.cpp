#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <Windows.h>
#include <direct.h>
#include <shlwapi.h>
#pragma comment( lib, "shell32.lib" )
#pragma comment( lib, "shlwapi.lib" )
#define CHARBUFF 124


using namespace std;

/*----playerクラス-------*/
class player
{
private:
	string name;
	string adress = "k_games/player/";
	string def_adress = "k_games/player/default/";
public:
	void create(string name);
	void createComment();
	void createCoordinate();
	void createStage();
	void createLooks();
	string getN();
	/*
	~player() {
		string Adress = "k_games/player/" + name;
		remove((Adress + "coordinate/x.txt").c_str());
		remove((Adress + "coordinate/y.txt").c_str());
		_rmdir((Adress + "coordinate").c_str());
		remove((Adress + "stage").c_str());
		remove((Adress + "comment").c_str());

		_rmdir(Adress.c_str());
		fstream fs("k_games/player/name.txt");
		if (!fs) {
			cout << "error" << endl;
		}
		string list;
		while (1) {
			string n;
			getline(fs, n);
			if (EOF) break;
			if(n.find(name) == string::npos) {
				list += n + "\n";
			}
		}
		fs.clear();
		fs.seekp(ios::beg);
		fs << list;
	}
	*/
};
void player::create(string name) {
	this->name = name;
	adress += name;
	if (_mkdir(adress.c_str()) != 0) {
		cout << "作成できませんでした" << endl;
		cin.get();
	}
	else {
		cout << "作成しました" << endl;
		cin.get();
	}
	
}
void player::createComment() {
	string Adress, def_Adress;
	Adress = adress + "/comment.txt";
	def_Adress = def_adress + "/comment.txt";
	CopyFile(def_Adress.c_str(), Adress.c_str(), true);
}
void player::createCoordinate() {
	string Adress, def_Adress;
	Adress = adress + "/coordinate";
	if (_mkdir(Adress.c_str()) != 0) {
		cout << "作成できませんでした" << endl;
		cin.get();
	}
	Adress = adress + "/coordinate/x.txt";
	def_Adress = def_adress + "coordinate/x.txt";
	CopyFile(def_Adress.c_str(), Adress.c_str(), true);
	Adress = adress + "/coordinate/y.txt";
	def_Adress = def_adress + "coordinate/y.txt";
	CopyFile(def_Adress.c_str(), Adress.c_str(), true);
}
void player::createStage() {
	string Adress, def_Adress;
	Adress = adress + "/stage.txt";
	def_Adress = def_adress + "stage.txt";
	CopyFile(def_Adress.c_str(), Adress.c_str(), true);
}
void player::createLooks() {
	string Adress, def_Adress;
	Adress = adress + "/looks.txt";
	def_Adress = def_adress + "looks.txt";
	CopyFile(def_Adress.c_str(), Adress.c_str(), true);
}
string player::getN() {
	return name;
}
/*-----server-------*/
void getCurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

//commentを書き込む
void write_c(string adress, string name, string comment)
{
	string Adress = adress + name + "/comment.txt";
	ofstream outputfile(Adress);
	outputfile << comment;
	outputfile.close();
}
//commentに読み込む
void read_c(string adress, string name, string* comment)
{
	string Adress = adress + name + "/comment.txt";
	fstream fs(Adress);
	if (!fs)
	{
		cout << "ファイルが開けませんでした" << endl;
		cin.get();
	}
	string c;
	fs >> c;
	*comment = c;
}


int main() {
	//ShellExecute(NULL, "open", "git-cmd.exe", "login_doshisha.bat", "", SW_HIDE);
	ShellExecute(NULL, "open", "git-cmd.exe", "login.bat", "", SW_HIDE);
	if (!PathFileExists("k_games")) {
		ShellExecute(NULL, "open", "git-cmd.exe", "clone.bat", "", SW_HIDE);
		cout << "clone作成" << endl;
		cin.get();
	}
	else {
		ShellExecute(NULL, "open", "git-cmd.exe", "pull.bat", "", SW_HIDE);
	}
	ShellExecute(NULL, "open", "git-cmd.exe", "push.bat", "", SW_HIDE);

	player p1;
	string name;
	cout << "名前を入れてね:" << endl;
	cin >> name;
	cin.get();
	p1.create(name);
	string Adress = "k_games/player/name.txt";
	ofstream outputfile(Adress, ios::app);
	outputfile << name << endl;
	outputfile.close();
	p1.createComment();
	p1.createCoordinate();
	p1.createLooks();
	p1.createStage();
		string save_comment;
		string comment;
		cout << "commentを入れてね！" << endl;
		cin >> comment;
		write_c("k_games/player/", p1.getN(), comment);
		ShellExecute(NULL, "open", "git-cmd.exe", "push.bat", "", SW_HIDE);
		ShellExecute(NULL, "open", "git-cmd.exe", "pull.bat", "", SW_HIDE);
		read_c("k_games/player/", p1.getN(), &comment);
		if (comment != save_comment) {
			cout << comment << endl;
			save_comment = comment;
		}
		
	
	delete &p1;
	cin.get();
	cout << "delete";
	
	while(1);
	return 0;
}
