//타이틀화면
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
		showMessage("열심히 농사를 지어서 감자 도감을 다 채워보자!");
		enterScene(farm);
		playSound(bgm, true);
	}

	else if (object == endButton)
		endGame();
}


void mainTitle() {

	title = createScene("감자 캐기", "Images/farm.png");

	titleImage = createObject("Images/감자캐기.png", title, 240, 370, true, 0.7f);

	endButton = createObject("Images/버튼/나가기.png", title, 700, 120, true, 2.0f);
	startButton = createObject("Images/버튼/농사시작.png", title, 400, 120, true, 2.0f);
}