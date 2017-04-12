#include "cpu.hpp"

Cpu::Cpu()
{
    nProcessor = sysconf(_SC_NPROCESSORS_ONLN);
}

int Cpu::parseFile(int totalJiffies[MAX_PROCESSORS], int workJiffies[MAX_PROCESSORS])
{
    std::ifstream procStat("/proc/stat");

    std::string cpuInfo[MAX_PROCESSORS];

    for(int i{0}; i <= nProcessor; i++)
    {
        getline(procStat, cpuInfo[i]);
    }

    int nSpaces{0};
    int data{0};

    std::string cpuName[MAX_PROCESSORS];
    std::string user[MAX_PROCESSORS];
    std::string nice[MAX_PROCESSORS];
    std::string system[MAX_PROCESSORS];
    std::string idle[MAX_PROCESSORS];
    std::string iowait[MAX_PROCESSORS];
    std::string irq[MAX_PROCESSORS];
    std::string softirq[MAX_PROCESSORS];


    for(int j{0}; j <= nProcessor; j++)
    {
        for(int k{0}; k <= cpuInfo[j].length(); k++)
        {
            if(data == 0)
            {
                cpuName[j] += cpuInfo[j][k-1];  //k - 1 To not include the space
            }

            else if(data == 1)
            {
                user[j] += cpuInfo[j][k-1];     //k - 1 To not include the space
            }

            else if(data == 2)
            {
                nice[j] += cpuInfo[j][k-1];     //k - 1 To not include the space
            }

            else if(data == 3)
            {
                system[j] += cpuInfo[j][k-1];   //k - 1 To not include the space
            }

            else if(data == 4)
            {
                idle[j] += cpuInfo[j][k-1];     //k - 1 To not include the space
            }

            else if(data == 5)
            {
                iowait[j] += cpuInfo[j][k-1];   //k - 1 To not include the space
            }

            else if(data == 6)
            {
                irq[j] += cpuInfo[j][k-1];      //k - 1 To not include the space
            }

            else if(data == 7)
            {
                softirq[j] += cpuInfo[j][k-1];  //k - 1 To not include the space
            }

            if(cpuInfo[j][k] == ' ' && j == 0 && nSpaces == 0)
            {
                k++;
                k++;
                nSpaces++;
                data++;
            }

            else if(cpuInfo[j][k] == ' ' && nSpaces != 0)
            {
                k++;
                nSpaces++;
                data++;
            }
        }
        data = 0;
    }

    int iuser[MAX_PROCESSORS];
    int inice[MAX_PROCESSORS];
    int isystem[MAX_PROCESSORS];
    int iidle[MAX_PROCESSORS];
    int iiowait[MAX_PROCESSORS];
    int iirq[MAX_PROCESSORS];
    int isoftirq[MAX_PROCESSORS];

    for(int n{0}; n <= nProcessor; n++)
    {
        iuser[n] = std::stoi(user[n]);
        inice[n] = std::stoi(nice[n]);
        isystem[n] = std::stoi(system[n]);
        iidle[n] = std::stoi(idle[n]);
        iiowait[n] = std::stoi(iowait[n]);
        iirq[n] = std::stoi(irq[n]);
        isoftirq[n] = std::stoi(softirq[n]);

        totalJiffies[n] = (iuser[n] + inice[n] + isystem[n] + iidle[n] + iiowait[n] + iirq[n] + isoftirq[n]);
        workJiffies[n] = (iuser[n] + inice[n] + isystem[n]);
    }
}

int Cpu::cpuUsageCalc()
{
    float workOverPeriod[MAX_PROCESSORS];
    float totalOverPeriod[MAX_PROCESSORS];

    parseFile(totalJiffies1, workJiffies1);

    usleep(1050000);

    parseFile(totalJiffies2, workJiffies2);

    for(int i{0}; i <= nProcessor; i++)
    {
    	workOverPeriod[i] = (workJiffies2[i] - workJiffies1[i]);
    	totalOverPeriod[i] = (totalJiffies2[i] - totalJiffies1[i]);
    	cpuUsagePercentage[i] = (workOverPeriod[i] / totalOverPeriod[i] * 100);
    }
}
