// Logging.h

#ifndef LOGGING_H
#define LOGGING_H

#include "raylib.h"
#include <string>

inline void log_message(const char* msg)
{
    // Open a tiny window just to show this one message
    const int width = 400;
    const int height = 200;
    InitWindow(width, height, "Log Message");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(msg, 10, 10, 20, GREEN);
        DrawText("Press [ENTER] to continue", 10, height - 30, 14, LIGHTGRAY);
        EndDrawing();

        if (IsKeyPressed(KEY_ENTER))
            break;
    }

    CloseWindow();
}

#endif
