#ifndef STALL_MAP_GUI_H
#define STALL_MAP_GUI_H

#include <iostream>
#include <raylib.h>

int showStallMapGUI(const bool* bookedStalls)
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Select Your Stall");

    if (!IsWindowReady())
    {
        std::cout << "\n[ASCII Stall Map Interface]\n";
        std::cout << "+-----------+\n";
        std::cout << "| ";
        std::cout << (bookedStalls && bookedStalls[1] ? " - " : "[1]");
        std::cout << "   ";
        std::cout << (bookedStalls && bookedStalls[2] ? " - " : "[2]");
        std::cout << " |\n";
        std::cout << "|           |\n";
        std::cout << "| ";
        std::cout << (bookedStalls && bookedStalls[3] ? " - " : "[3]");
        std::cout << "   ";
        std::cout << (bookedStalls && bookedStalls[4] ? " - " : "[4]");
        std::cout << " |\n";
        std::cout << "|           |\n";
        std::cout << "| ";
        std::cout << (bookedStalls && bookedStalls[5] ? " - " : "[5]");
        std::cout << "   ";
        std::cout << (bookedStalls && bookedStalls[6] ? " - " : "[6]");
        std::cout << "   |\n";
        std::cout << "+-----------+\n";
        std::cout << "Select a stall ID (1-6): ";

        int stallID;
        std::cin >> stallID;
        return stallID;
    }
    SetTargetFPS(60);

    Rectangle stalls[6];
    for (int i = 0; i < 6; ++i)
    {
        int row = i / 2;
        int col = i % 2;
        stalls[i].x = 100 + col * 300;
        stalls[i].y = 100 + row * 200;
        stalls[i].width = 200;
        stalls[i].height = 120;
    }

    int selected = -1;

    while (!WindowShouldClose() && selected < 0)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < 6; ++i)
        {
            bool isBooked = bookedStalls && bookedStalls[i + 1];
            Color fillCol = isBooked ? LIGHTGRAY : SKYBLUE;

            DrawRectangleRec(stalls[i], fillCol);
            DrawRectangleLines((int)stalls[i].x,
                (int)stalls[i].y,
                (int)stalls[i].width,
                (int)stalls[i].height,
                BLACK);

            DrawText(TextFormat("%d", i + 1),
                (int)(stalls[i].x + stalls[i].width / 2) - 10,
                (int)(stalls[i].y + stalls[i].height / 2) - 10,
                24,
                BLACK);

            if (!isBooked && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 m = GetMousePosition();
                if (CheckCollisionPointRec(m, stalls[i]))
                    selected = i + 1;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return selected;
}

#endif
