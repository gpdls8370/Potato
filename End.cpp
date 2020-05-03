//도감 1페이지
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bangtal.h>

extern SceneID book1;
extern SoundID button;
SceneID end;
ObjectID endButton2, goBookButton2, titleImage2;

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);

void mouseCallbackEnd(ObjectID object, int x, int y, MouseAction action) {

	if (object == endButton2) {
		playSound(button);
		endGame();
	}

	else if (object == goBookButton2) {
		playSound(button);
		enterScene(book1);
	}
}

void mainEnd() {

	end = createScene("농사 끝", "Images/farm.png");

	titleImage2 = createObject("Images/감자캐기.png", end, 240, 370, true, 0.7f);
	endButton2 = createObject("Images/버튼/나가기.png", end, 700, 120, true, 2.0f);
	goBookButton2 = createObject("Images/버튼/도감보기.png", end, 400, 120, true, 2.0f);
}