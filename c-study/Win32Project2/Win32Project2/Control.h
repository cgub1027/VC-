#pragma once
#include<DxLib.h>
#include"Map.h"
#include"Player.h"

class Control {
public:
	Player* pl;
	Map* map;
	//Map* map[4];

	Control() {
		pl = new Player();
		map = new Map("Map007.png");
		//map[0] = new Map("flame.csv");
		//map[1] = new Map("flame1.csv");
		//map[2] = new Map("flame2.csv");
		pl->x = pl->targetX = CELL_WIDTH;
		pl->y = pl->targetY = CELL_HEIGHT;
	}

	~Control() {
		delete pl;
		delete[] map;
	}


	void All() {
		//for (int i = 0; i < 3; i++)map[i]->BackView();
		map->view();
		pl->All(map);
		//for (int i = 0; i < 3; i++)map[i]->FrontView();
		//DrawFormatString(pl->x + CELL_WIDTH, pl->y - CELL_HEIGHT, BLACKNESS, "‚¤‚ñ‚±‚à‚ê‚»‚¤");
	}
};