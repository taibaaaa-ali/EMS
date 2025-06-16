#ifndef STALL_MAP_GUI_H
#define STALL_MAP_GUI_H

#include <iostream>

int showStallMapGUI(const bool* bookedStalls)
{
    std::cout << "\n[Graphics not available, using ASCII interface]\n";
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

#endif
