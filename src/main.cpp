/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : lower_snake_case
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include "Application.h"

int main()
{
    Application app;

    if (!app.init()) {
        return 1;
    }

    app.run();

    return 0;
}
