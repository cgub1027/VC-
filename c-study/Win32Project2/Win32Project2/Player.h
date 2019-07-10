#pragma once
#include<DxLib.h>
#include"Map.h"

#define WALKTIME 15

class Player {
public:
	int gh[12];
	int width, height;
	int walkVec;//���������B2,4,6,8�Ńe���L�[�ɑΉ�
	int animCount;//�}�C�t���[��1�����₷�A�A�j���[�V�����̂��߂̃J�E���^
	bool walkFlag;//�����Ă��邩�����~�܂��Ă��邩�̔���
	int x, y;//�O���t�B�b�N��`�悷����W
	int targetX, targetY;//�v���C���[�����Ɍ������ׂ����W�B���݈ʒu�ׂ̗̃}�X�̂ǂꂩ
	int speed;
	Player() {
		LoadDivGraph("Chara.png", 12, 3, 4, 20, 28, gh);
		GetGraphSize(gh[0], &width, &height);
		walkVec = 2;
		walkFlag = false;
		animCount = 0;
		x = 0;
		y = 0;
		speed = 1;
		targetX = 0;
		targetY = 0;
	}

	void AnimationView(int animState, int firstNum) {
		if (animState == 0)DrawExtendGraph(x, y - 2 * (height - width), x + CELL_WIDTH, y + CELL_HEIGHT, gh[firstNum], TRUE);
		if (animState == 1)DrawExtendGraph(x, y - 2 * (height - width), x + CELL_WIDTH, y + CELL_HEIGHT, gh[firstNum + 1], TRUE);
		if (animState == 2)DrawExtendGraph(x, y - 2 * (height - width), x + CELL_WIDTH, y + CELL_HEIGHT, gh[firstNum + 2], TRUE);
		if (animState == 3)DrawExtendGraph(x, y - 2 * (height - width), x + CELL_WIDTH, y + CELL_HEIGHT, gh[firstNum + 1], TRUE);
	}

	void Move(Map* map) {
		walkFlag = false;//��{��false�A�����Ă��鎞�����ύX����

		if (targetX == x && targetY == y) {//�ړ����łȂ����
			if (CheckHitKey(KEY_INPUT_DOWN)) {
				walkFlag = true;
				walkVec = 2;
				//if (map[0]->cell[x / CELL_WIDTH][y / CELL_HEIGHT + 1].canwalk &&
				//	map[1]->cell[x / CELL_WIDTH][y / CELL_HEIGHT + 1].canwalk &&
				//	map[2]->cell[x / CELL_WIDTH][y / CELL_HEIGHT + 1].canwalk)
					if(map->cell[x/CELL_WIDTH][y/CELL_HEIGHT + 1].canwalk)targetY += CELL_HEIGHT;//targetY��1�}�X���ړ�
			}
			else if (CheckHitKey(KEY_INPUT_LEFT)) {
				walkFlag = true;
				walkVec = 4;
				//if (map[0]->cell[x / CELL_WIDTH - 1][y / CELL_HEIGHT].canwalk &&
				//	map[1]->cell[x / CELL_WIDTH - 1][y / CELL_HEIGHT].canwalk &&
				//	map[2]->cell[x / CELL_WIDTH - 1][y / CELL_HEIGHT].canwalk)
				if (map->cell[x / CELL_WIDTH - 1][y / CELL_HEIGHT].canwalk)targetX -= CELL_WIDTH;
			}
			else if (CheckHitKey(KEY_INPUT_RIGHT)) {
				walkFlag = true;
				walkVec = 6;
				//if (map[0]->cell[x / CELL_WIDTH + 1][y / CELL_HEIGHT].canwalk &&
				//	map[1]->cell[x / CELL_WIDTH + 1][y / CELL_HEIGHT].canwalk &&
				//	map[2]->cell[x / CELL_WIDTH + 1][y / CELL_HEIGHT].canwalk)
				if (map->cell[x / CELL_WIDTH + 1][y / CELL_HEIGHT].canwalk)targetX += CELL_WIDTH;
			}
			else if (CheckHitKey(KEY_INPUT_UP)) {
				walkFlag = true;
				walkVec = 8;
				//if (map[0]->cell[x / CELL_WIDTH][y / CELL_HEIGHT - 1].canwalk &&
				//	map[1]->cell[x / CELL_WIDTH][y / CELL_HEIGHT - 1].canwalk &&
				//	map[2]->cell[x / CELL_WIDTH][y / CELL_HEIGHT - 1].canwalk)
				if (map->cell[x / CELL_WIDTH][y / CELL_HEIGHT - 1].canwalk)targetY -= CELL_HEIGHT;
			}
			else {
				animCount = 0;//�L�[��������Ă��炸�A�ړ����������Ă����animCount�����Z�b�g
			}
		}
		else {
			walkFlag = true;
		}

		if (y < targetY)y += speed;
		if (x > targetX)x -= speed;
		if (x < targetX)x += speed;
		if (y > targetY)y -= speed;
	}

	void View() {

		int animState = animCount / WALKTIME;//animCount��WALKTIME�̌��{���ɂȂ邽�т�animState��1������

		if (animState == 4) {//animState��4�ɂȂ����烊�Z�b�g
			animCount = 0;
			animState = 0;
		}

		if (walkFlag) {
			if (walkVec == 2)AnimationView(animState, 0);
			if (walkVec == 4)AnimationView(animState, 3);
			if (walkVec == 6)AnimationView(animState, 6);
			if (walkVec == 8)AnimationView(animState, 9);
			animCount++;
		}
		else {
			if (walkVec == 2)DrawExtendGraph(x, y - 2 * (height - width), x + CELL_WIDTH, y + CELL_HEIGHT, gh[1], TRUE);
			if (walkVec == 4)DrawExtendGraph(x, y - 2 * (height - width), x + CELL_WIDTH, y + CELL_HEIGHT, gh[4], TRUE);
			if (walkVec == 6)DrawExtendGraph(x, y - 2 * (height - width), x + CELL_WIDTH, y + CELL_HEIGHT, gh[7], TRUE);
			if (walkVec == 8)DrawExtendGraph(x, y - 2 * (height - width), x + CELL_WIDTH, y + CELL_HEIGHT, gh[10], TRUE);
		}

		/*comment*/
		
	}

	void All(Map* map) {
		Move(map);
		View();
	}
};
