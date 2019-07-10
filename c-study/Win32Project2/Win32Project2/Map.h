#pragma once

#include<DxLib.h>
#include <iostream>
#include <string>

#define CELL_WIDTH 16
#define CELL_HEIGHT 12
#define CELL_NUM_X 40
#define CELL_NUM_Y 40
#define WINDOW_Y 640
#define WINDOW_X 640

struct Cell {
	int gh;
	bool canwalk;
	int drawMode;//0:プレイヤーより奥 1:プレイヤーより手前
};

class Map {
public:
	Cell cell[CELL_NUM_X][CELL_NUM_Y];
	int gh[40 * 40];
	int Wgh[1 * 6];
	Map(const char* add) {
		LoadDivGraph(add, 40 * 40, 40, 40, 24, 24, gh);
		LoadDivGraph("Map001.png", 1 * 6, 6, 1, 24, 24, Wgh);

		for (int i = 0; i < CELL_NUM_X * CELL_NUM_Y; i++) {
			int x = i % CELL_NUM_X;
			int y = i / CELL_NUM_X;
			for (int j = 0; j < 6; j++) {
				if (gh[i] == Wgh[j]) cell[x][y].canwalk = 0;
				else cell[x][y].canwalk = 1;
			}
			cell[x][y].gh = gh[i];
		}
		/*
		FILE* fp;//ファイルのポインタを宣言
		fopen_s(&fp, add, "r");//fpを読み取り形式で開く
		if (fp == NULL) {
			DebugBreak();
		}
		int c;//文字を格納する
		int retu = 0;
		int gyou = 0;
		char buf[10];//文字列を格納する
		memset(buf, 0, sizeof(buf));
		bool eofFlag = false;
		while (1) {
			while (1) {
				c = fgetc(fp);
				if (c == EOF) {
					eofFlag = true;
					break;
				}
				if (c != ';') {//「,」が出てくるまで読み進める
					strcat_s(buf, (const char*)& c);
				}
				else {
					int num = atoi(buf);
					cell[retu][gyou].gh = chipgh[num];
					memset(buf, 0, sizeof(buf));
					break;
				}
			}
			if (eofFlag)break;
			while (1) {
				c = fgetc(fp);
				if (c != ';') {
					strcat_s(buf, (const char*)& c);
				}
				else {
					int num = atoi(buf);
					cell[retu][gyou].canwalk = num;
					memset(buf, 0, sizeof(buf));
					break;
				}
			}
			while (1) {
				c = fgetc(fp);
				if (c != ',' && c != '\n') {
					strcat_s(buf, (const char*)& c);
				}
				else {
					int num = atoi(buf);
					cell[retu][gyou].drawMode = num;
					memset(buf, 0, sizeof(buf));
					break;
				}
			}
			//1セル分のループを抜けたら
			if (c == ',') {
				retu++;
			}
			if (c == '\n') {//改行だったら行を増やす
				gyou++;
				retu = 0;
			}
		}
		fclose(fp);
		*/
	}
/*
	void FrontView() {
		for (int i = 0; i < CELL_NUM_X; i++) {
			for (int j = 0; j < CELL_NUM_Y; j++) {
				if (cell[i][j].drawMode == 1)DrawExtendGraph(i * CELL_WIDTH, j * CELL_HEIGHT, (i + 1) * CELL_WIDTH, (j + 1) * CELL_HEIGHT, cell[i][j].gh, TRUE);
			}
		}
	}
	
	void BackView() {
		for (int i = 0; i < CELL_NUM_X; i++) {
			for (int j = 0; j < CELL_NUM_Y; j++) {
				if (cell[i][j].drawMode == 0)DrawExtendGraph(i * CELL_WIDTH, j * CELL_HEIGHT, (i + 1) * CELL_WIDTH, (j + 1) * CELL_HEIGHT, cell[i][j].gh, TRUE);
			}
		}
	}
	*/

	void view() {
		for (int x = 0; x < CELL_NUM_X; x++) {
			for (int y = 0; y < CELL_NUM_Y; y++) {
				DrawExtendGraph(x * CELL_WIDTH, y * CELL_HEIGHT, (x + 1) * CELL_WIDTH, (y + 1) * CELL_HEIGHT, cell[x][y].gh, TRUE);
				//DrawFormatString(x * CELL_WIDTH, y * CELL_HEIGHT, BLACKNESS, std::to_string(i).c_str());

			}
		}
	}
	void All() {

	}
};