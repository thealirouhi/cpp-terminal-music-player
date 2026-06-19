/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef NOWPLAYINGSCREEN_H
#define NOWPLAYINGSCREEN_H

#include "Screen.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include "Player.h"
#include <string>
using namespace std;

class NowPlayingScreen : public Screen
{
public:
    NowPlayingScreen(UIRenderer& renderer, InputHandler& input,
                     Player& player);

    void render() override;
    void handleInput() override;

private:
    UIRenderer& renderer_;
    InputHandler& input_;
    Player& player_;

    string stateLabel() const;
    string modeLabel() const;
};

#endif
