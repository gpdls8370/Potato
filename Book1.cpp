//도감 1페이지
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bangtal.h>

extern SceneID farm, book2, end;
extern SoundID button;
SceneID book1;
ObjectID bookCell1[3];
ObjectID goRightButton1, goFarmButton1, goBackButton;

extern bool findPotato[8];
extern const char* bookImageList_no[8];

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);

void mouseCallbackBook1(ObjectID object, int x, int y, MouseAction action) {

	if (object == goFarmButton1) {
		playSound(button);
		enterScene(farm);
	}

	else if (object == goRightButton1) {
		playSound(button);
		enterScene(book2);
	}

	else if (object == goBackButton) {
		playSound(button);
		enterScene(end);
	}
}

void mainBook1() {

	book1 = createScene("감자 도감 - 1페이지", "Images/book.png");

	//0,1,2
	for (int i = 0; i < 3; i++)
		bookCell1[i] = createObject(bookImageList_no[i], book1, 87 + 373 * i, 35, true, 0.7f);

	goFarmButton1 = createObject("Images/버튼/농장으로.png", book1, 30, 40, true, 1.5f);
	goBackButton = createObject("Images/버튼/뒤로.png", book1, 30, 40, false, 1.5f);
	goRightButton1 = createObject("Images/도감/화살표_오.png", book1, 1160, 15, true, 0.8f);

}