#include "FastLED.h"
#include <Button.h>
#include <Coord.h>
#include <GameController.h>
#include <DisplayController.h>


#define leftBtnPin 3
#define rightBtnPin 4
#define shootBtnPin 6

Button leftBtn(leftBtnPin);
Button rightBtn(rightBtnPin);
Button shootBtn(shootBtnPin);
GameController game({15, 15}, {0, 0}, 150);
DisplayController display;

void setup()
{
  Serial.begin(9600);
  display.init();
  game.init();
}

void buttonsHandler()
{
  if (leftBtn.isPressed())
    game.moveUserLeft();

  if (rightBtn.isPressed())
    game.moveUserRight();

  if (shootBtn.isPressed())
    game.shoot();
}

void loop()
{
  buttonsHandler();
  game.play();
  display.renderGame(game.getUserPos(), game.getShootPos(), game.get_enemy_matrix());
}
