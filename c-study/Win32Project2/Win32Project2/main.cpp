#include"DxLib.h"
#include "Control.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)return -1;
	SetWindowSize(WINDOW_X, WINDOW_Y);
	SetDrawScreen(DX_SCREEN_BACK);

	Control* cont = new Control();

	while (ProcessMessage() != -1 && !ScreenFlip() && !ClearDrawScreen()) {
		int startTime = GetNowCount();

		cont->All();
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;
		int endTime = GetNowCount();
		WaitTimer((1000 / 60) - (endTime - startTime));
	}

	delete cont;
	DxLib_End();

	return 0;
}