#ifndef PENDING_STALL_SELECTION_H
#define PENDING_STALL_SELECTION_H

#include <fstream>

struct PendingStallSelection
{
    int vendorID;
    int eventID;
    int stallID;

    PendingStallSelection() : vendorID(0), eventID(0), stallID(0) {}
    PendingStallSelection(int v, int e, int s) : vendorID(v), eventID(e), stallID(s) {}

    void writeToFile(std::ofstream& out) const
    {
        out << vendorID << "," << eventID << "," << stallID << "\n";
    }
    bool readFromFile(std::ifstream& in)
    {
        char line[100];
        if (!in.getline(line, 100))
            return false;

        int field = 0, i = 0, bufIdx = 0;
        char buffer[50];
        int vID = 0, eID = 0, sID = 0;
        while (line[i] != '\0')
        {
            if (line[i] != ',' && line[i] != '\n')
            {
                buffer[bufIdx++] = line[i];
            }
            else
            {
                buffer[bufIdx] = '\0';
                if (field == 0) vID = atoi(buffer);
                else if (field == 1) eID = atoi(buffer);
                else if (field == 2) sID = atoi(buffer);
                field++;
                bufIdx = 0;
            }
            i++;
        }
        if (bufIdx > 0 && field == 2)
        {
            buffer[bufIdx] = '\0';
            sID = atoi(buffer);
        }
        vendorID = vID;
        eventID = eID;
        stallID = sID;
        return true;
    }
};

#endif
