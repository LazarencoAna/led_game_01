#include "FastLED.h"
#include <Coord.h>
#include <GameController.h>
#include <DisplayController.h>
#include <JoyStick.h>

#define shootBtnPin 6
#define xPin A0
#define yPin A1

GameController game(0,{15, 15}, {0, 0}, 150);
DisplayController display;
JoyStick joyStick(xPin,yPin,shootBtnPin);

void setup()
{
  Serial.begin(9600);
  display.init();
  game.init();
}

void buttonsHandler()
{
  if (joyStick.isLeft())
    game.moveUserLeft();

  if (joyStick.isRight())
    game.moveUserRight();

  if (joyStick.isPressed())
    game.shoot();
}

void loop()
{
  buttonsHandler();
  game.play();
  display.renderGame(game.getUserPos(), game.getShootPos(), game.get_enemy_matri());
 // display.Display(game.get_enemy_matrix());
  joyStick.lisen();
}
