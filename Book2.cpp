//도감 2페이지
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bangtal.h>

extern SceneID book1, book3;
extern SoundID button;
SceneID book2;
ObjectID bookCell2[3];
ObjectID goLeftButton2, goRightButton2;

extern bool findPotato[8];
extern const char* bookImageList_no[8];

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);

void mouseCallbackBook2(ObjectID object, int x, int y, MouseAction action) {

	if (object == goLeftButton2) {
		playSound(button);
		enterScene(book1);
	}

	else if (object == goRightButton2) {
		playSound(button);
		enterScene(book3);
	}
}

void mainBook2() {

	book2 = createScene("감자 도감 - 2페이지", "Images/book.png");

	//3,4,5
	for (int i = 0; i < 3; i++)
		bookCell2[i] = createObject(bookImageList_no[i + 3], book2, 87 + 373 * i, 35, true, 0.7f);

	goLeftButton2 = createObject("Images/도감/화살표_왼.png", book2, 10, 15, true, 0.8f);
	goRightButton2 = createObject("Images/도감/화살표_오.png", book2, 1160, 15, true, 0.8f);

}