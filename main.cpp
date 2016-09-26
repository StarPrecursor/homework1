#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Data
{
private:
    int* numA = NULL;
    int numASign = 0;// '0' means plus, '1' means minus
    int numALength = 0;
    int* numB = NULL;
    int numBSign = 0;
    int numBLength = 0;
    int operater = 0;
    bool numAJudge = false;// 'true' means input legal, 'false' means input illegal
    bool numBJudge = false;
    bool operaterJudge = false;

public:
    int numAWrite(char*, int);
    int numBWrite(char*, int);
    int operaterWrite(char*);
};

void DataTypeRefresh(int &);

int main()
{
    int dataType = 1;
    int dataLength = 0;

    char* inputData = new char[100000];
    Data* calculateData = new Data;

    while(gets(inputData) != NULL)
    {
        dataLength = strlen(inputData);
        switch(dataType)
        {
            case 1 : calculateData->numAWrite(inputData, dataLength);
                break;
            case 2 : calculateData->numBWrite(inputData, dataLength);
                break;
            case 3 : calculateData->operaterWrite(inputData);
                break;
            default : cout << "Unknown error in main" << endl;
                exit (1);
        }

        DataTypeRefresh(dataType);
        delete[] inputData;
        inputData = new char[100000];
    }

}

int Data::numAWrite(char* inputData, int dataLength)
{
    bool recordBeginFlag = false;
    int recordBeginPosition = -1;
    numAJudge = true;

    if(inputData[0] == '+')
    {
        numASign = 0;
    }
    else if(inputData[0] == '-')
    {
        numASign = 1;
    }
    else if(inputData[0] == '0')
    {
        recordBeginFlag = false;
    }
    else if(inputData[0] < '0' && inputData[0] > '9')
    {
        numAJudge = false;
        return 0;
    }
    else
    {
        recordBeginFlag = true;
        recordBeginPosition = 0;
        numALength = dataLength - recordBeginPosition;
        numA = new int[numALength];
        numA[0] = inputData[0] - '0';
    }

    for(int dataNum = 1; dataNum < dataLength; dataNum++)
    {
        if(recordBeginFlag == false)
        {
            if(inputData[dataNum] == '0')
            {
                continue;
            }
            else if(inputData[dataNum] < '0' || inputData[dataNum] > '9')
            {
                numAJudge = false;
                break;
            }
            else
            {
                recordBeginFlag = true;
                recordBeginPosition = dataNum;
                numALength = dataLength - recordBeginPosition;
                numA = new int[numALength];
                numA[0] = inputData[dataNum] - '0';
            }
        }
        else if(recordBeginFlag == true)
        {
            if(inputData[dataNum] < '0' || inputData[dataNum] > '9')
            {
                numAJudge = false;
                break;
            }
            else
            {
                numA[dataNum - recordBeginPosition] = inputData[dataNum] - '0';
            }
        }
    }
}

int Data::numBWrite(char* inputData, int dataLength)
{
    bool recordBeginFlag = false;
    int recordBeginPosition = -1;
    numBJudge = true;

    if(inputData[0] == '+')
    {
        numBSign = 0;
    }
    else if(inputData[0] == '-')
    {
        numBSign = 1;
    }
    else if(inputData[0] == '0')
    {
        recordBeginFlag = false;
    }
    else if(inputData[0] < '0' && inputData[0] > '9')
    {
        numBJudge = false;
        return 0;
    }
    else
    {
        recordBeginFlag = true;
        recordBeginPosition = 0;
        numBLength = dataLength - recordBeginPosition;
        numB = new int[numBLength];
        numB[0] = inputData[0] - '0';
    }

    for(int dataNum = 1; dataNum < dataLength; dataNum++)
    {
        if(recordBeginFlag == false)
        {
            if(inputData[dataNum] == '0')
            {
                continue;
            }
            else if(inputData[dataNum] < '0' || inputData[dataNum] > '9')
            {
                numBJudge = false;
                break;
            }
            else
            {
                recordBeginFlag = true;
                recordBeginPosition = dataNum;
                numBLength = dataLength - recordBeginPosition;
                numB = new int[numBLength];
                numB[0] = inputData[dataNum] - '0';
            }
        }
        else if(recordBeginFlag == true)
        {
            if(inputData[dataNum] < '0' || inputData[dataNum] > '9')
            {
                numBJudge = false;
                break;
            }
            else
            {
                numB[dataNum - recordBeginPosition] = inputData[dataNum] - '0';
            }
        }
    }
}

int Data::operaterWrite(char* inputData)
{
    operaterJudge = true;
    switch(inputData[0])
    {
        case '+' : operater = 1;
            break;
        case '-' : operater = 2;
            break;
        case '*' : operater = 3;
            break;
        case '/' : operater = 4;
            break;
        default : operater = -1;
            operaterJudge = false;
            break;
    }

    if(inputData[1] != '\0')
    {
        operaterJudge = false;
    }
}

void DataTypeRefresh(int &dataType)
{
    switch(dataType)
    {
        case 1 : dataType++;
            break;
        case 2 : dataType++;
            break;
        case 3 : dataType = 1;
            break;
        default : cout << "Unknown Problem in DataTypeRefresh(int &dataType)" << endl;
            exit(1);
    }
}
