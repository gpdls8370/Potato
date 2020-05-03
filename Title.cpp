//Ÿ��Ʋȭ��
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bangtal.h>

extern SceneID farm;
extern SoundID button, bgm;
SceneID title;
ObjectID titleImage, startButton, endButton;

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);

void mouseCallbackTitle(ObjectID object, int x, int y, MouseAction action) {

	if (object == startButton) {
		playSound(button);
		showMessage("������ ��縦 ��� ���� ������ �� ä������!");
		enterScene(farm);
		playSound(bgm, true);
	}

	else if (object == endButton)
		endGame();
}


void mainTitle() {

	title = createScene("���� ĳ��", "Images/farm.png");

	titleImage = createObject("Images/����ĳ��.png", title, 240, 370, true, 0.7f);

	endButton = createObject("Images/��ư/������.png", title, 700, 120, true, 2.0f);
	startButton = createObject("Images/��ư/������.png", title, 400, 120, true, 2.0f);
}