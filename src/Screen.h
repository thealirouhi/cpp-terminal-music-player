/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
public:
    virtual void render() = 0;
    virtual void handleInput() = 0;
    virtual bool hasExited() const = 0;
    virtual void resetExit() = 0;
    virtual ~Screen() = default;
};

#endif
