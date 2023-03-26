#include "../Header/character.h"
#include "../Header/object.h"
#include "../../../Library/gameutil.h"

Character::Character() {
	jumpDuration = 300;
	timeJumped = 0;
	standTexture.LoadBitmapByString({ "" }, RGB(255, 255, 255));
	fireTexture.LoadBitmapByString({ "" }, RGB(255, 255, 255));
	slashTexture.LoadBitmapByString({ "" }, RGB(255, 255, 255));
	jumpUpTexture.LoadBitmapByString({ "" }, RGB(255, 255, 255));
	landTexture.LoadBitmapByString({ "" }, RGB(255, 255, 255));
	texture = standTexture;
}

void Character::jumpUpward() {
	//if (isCollide(ceiling)) {

	//}
	else if (timeJumped * 2 <= jumpDuration) {
		texture = jumpUpTexture;
		setTopLeft(getLeftX(), getTopY() + 30);
		timeJumped++;
	}
	else if (timeJumped <= jumpDuration) {
		setTopLeft(getLeftX(), getTopY() - 30);
		timeJumped++;
	}
	else {
		timeJumped = 0;
	}
}

void Character::moveLeft() {
	setTopLeft(getLeftX() - 30, getTopY());
}

void Character::moveRight() {
	setTopLeft(getLeftX() + 30, getTopY());
}

void Character::fireWeapon() {
	activeBullets.push_back(Bullet(facing));
}

void Character::slashNearby() {
	slashTexture
}

bool Character::isReadyToLand() {

}
