#include "main.h"
#include "AutoBedLeveling.h"
#include "Test.h"

#define MAX_LENGTH 255

void Test1();
void Test2();
void Test3();
void Test4();

int main(void) {
    const char filename[] = "bottom_contour.nc";
    FILE* fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    char buffer[MAX_LENGTH];
    char printBuffer[MAX_LENGTH];
    ABL_LoadLinePointer(buffer);
    int16_t lineCounter = 0;
    Coordinates_t pos = { 0.0, 0.0, 0.0 };
    while (fgets(buffer, MAX_LENGTH, fp)) {
        double value = 0;
        char temp[MAX_LENGTH];
        printBuffer[0] = '\0';

        if (true == ABL_ParseNumber('G', &value)) {
            sprintf(temp, "G%02d", (int) value);
            strcat(printBuffer, temp);
            if (true == ABL_ParseNumber('F', &value)) {
                sprintf(temp, " F%d", (int) value);
                strcat(printBuffer, temp);
            }
            if (true == ABL_ParseNumber('X', &pos.x)) {
                sprintf(temp, " X%.2f", pos.x);
                strcat(printBuffer, temp);
            }
            if (true == ABL_ParseNumber('Y', &pos.y)) {
                sprintf(temp, " Y%.2f", pos.y);
                strcat(printBuffer, temp);
            }
            if (true == ABL_ParseNumber('Z', &pos.z)) {
                sprintf(temp, " Z%.2f", pos.z);
                strcat(printBuffer, temp);
            }
            //printf("%0.2f, %0.2f, %0.2f\n", pos.x,pos.y,pos.z);
        }
        else if (true == ABL_ParseNumber('M', &value)) {
            sprintf(temp, "M%02d", (int) value);
            strcat(printBuffer, temp);

            if (true == ABL_ParseNumber('S', &value)) {
                sprintf(temp, " S%d", (int) value);
                strcat(printBuffer, temp);
            }
        }
#ifndef DEBUG
        if (strlen(printBuffer)) {
            //printf("%-30s",testData[lineCounter]);
            printf("%-30s", printBuffer);
            if (strcmp(printBuffer, testData[lineCounter])) {
                printf(" - NOK\n");
            }
            else {
                printf(" - OK\n");
            }
            lineCounter++;
        }
#endif
    }

    // close the file
    fclose(fp);

    Test1();
    Test2();
    Test3();
    return 0;
}

void Test1(){
    printf("line();\n");
    line(0, 0);
    line(7, 28);
    line(2, 7);
    line(28, 2);
    line(0, 0);
}
void Test2(){
    printf("ComputeLine();\n");
    while (!ComputeLine(0, 0));
    while (!ComputeLine(7, 28));
    while (!ComputeLine(2, 7));
    while (!ComputeLine(28, 2));
    while (!ComputeLine(0, 0));
}
void Test3(){
    while(Available()){
        string temp = ReadStringUntil('\r');
        std::cout << temp;
    }
}
