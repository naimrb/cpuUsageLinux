#include <unistd.h>
#include <fstream>
#include <string>
#include <iostream>

#define MAX_PROCESSORS 64

class Cpu
{
    private:
        int totalJiffies1[MAX_PROCESSORS];
        int totalJiffies2[MAX_PROCESSORS];
        int workJiffies1[MAX_PROCESSORS];
        int workJiffies2[MAX_PROCESSORS];

    public:
        float cpuUsagePercentage[MAX_PROCESSORS];
        int nProcessor;

        Cpu();
        int parseFile(int totalJiffies[MAX_PROCESSORS], int workJiffies[MAX_PROCESSORS]);
        int cpuUsageCalc();
};
