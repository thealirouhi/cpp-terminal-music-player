/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "Screen.h"
#include "UIRenderer.h"
#include "InputHandler.h"
#include <string>
using namespace std;

class MainMenu : public Screen
{
public:
    MainMenu(UIRenderer& renderer, InputHandler& input,
             const string& lastPlayed);

    void render() override;
    void handleInput() override;
    bool hasExited() const override;
    void resetExit() override;

    int getSelectedOption() const;

private:
    UIRenderer& renderer_;
    InputHandler& input_;
    string lastPlayed_;
    int selectedOption_;
    bool exited_;
};

#endif
