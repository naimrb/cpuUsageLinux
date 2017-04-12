#include <ncurses.h>
#include <iostream>
#include "cpu.hpp"

int main()
{
    Cpu cpu;
    initscr();
    while(1)
    {
        cpu.cpuUsageCalc();
        for(int i{0}; i <= cpu.nProcessor; i++)
        {
            if(i == 0)
            {
                move(i, 0);
                printw("Total cpu: %f", cpu.cpuUsagePercentage[i]);
                i++;
            }

            move(i+1, 6);
            printw("cpu%i: %f", i, cpu.cpuUsagePercentage[i]);
        }
        refresh();
    }
    endwin();
}
