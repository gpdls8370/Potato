//도감 1페이지
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bangtal.h>

extern SceneID book2;
extern SoundID button;
SceneID book3;
ObjectID bookCell3[2];
ObjectID goLeftButton3;

extern bool findPotato[8];
extern const char* bookImageList_no[8];

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);

void mouseCallbackBook3(ObjectID object, int x, int y, MouseAction action) {

	if (object == goLeftButton3) {
		playSound(button);
		enterScene(book2);
	}
}

void mainBook3() {

	book3 = createScene("감자 도감 - 3페이지", "Images/book.png");

	//6,7
	for (int i = 0; i < 2; i++)
		bookCell3[i] = createObject(bookImageList_no[i + 6], book3, 83 + 560 * i, 35, true, 0.7f);


	goLeftButton3 = createObject("Images/도감/화살표_왼.png", book3, 10, 15, true, 0.8f);

}