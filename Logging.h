#ifndef LOGGING_H
#define LOGGING_H

#include "raylib.h"
#include "myString.h"
#include <iostream>

inline void log_message(const myString& level,
    const myString& msg)
{
    SetTraceLogLevel(LOG_NONE);

    const int winW = 400;
    const int winH = 200;
    const double displaySeconds = 2.0; 

    InitWindow(winW, winH, "Log Message");
    if (!IsWindowReady())
    {
        std::cout << "[";
        level.print();
        std::cout << "] ";
        msg.print();
        std::cout << std::endl;
        return;
    }

    double startTime = GetTime();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        int l = level.length();
        char* bufL = new char[l + 1];
        for (int i = 0; i < l; ++i) bufL[i] = level.charAt(i);
        bufL[l] = '\0';
        DrawText(bufL, 10, 10, 20, GREEN);
        delete[] bufL;
        int m = msg.length();
        char* bufM = new char[m + 1];
        for (int i = 0; i < m; ++i) bufM[i] = msg.charAt(i);
        bufM[m] = '\0';
        DrawText(bufM, 10, 50, 20, WHITE);
        delete[] bufM;

        EndDrawing();
        if (GetTime() - startTime >= displaySeconds)
            break;
    }

    CloseWindow();
}

#endif
