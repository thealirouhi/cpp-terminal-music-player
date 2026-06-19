/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include "Screen.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include "Player.h"
#include <string>
using namespace std;

class SettingsScreen : public Screen
{
public:
    SettingsScreen(UIRenderer& renderer, InputHandler& input,
                   Player& player);

    void render() override;
    void handleInput() override;
    bool hasExited() const override;
    void resetExit() override;

private:
    UIRenderer& renderer_;
    InputHandler& input_;
    Player& player_;
    bool exited_;

    string modeDescription(Player::PlaybackMode mode) const;
};

#endif
