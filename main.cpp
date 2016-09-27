#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Data
{
public:
    ~Data()
    {
        delete[] numA;
        delete[] numB;
        //cout << "memory released." << endl;
    }
    int Calculate(void);
    int Divide(void);
    int InputErrorInformation(void);
    int Minus(void);
    int Multiply(void);
    int NumAWrite(char*, int);
    int NumBWrite(char*, int);
    int OperaterWrite(char*);
    int Plus(void);
    int SetNumAJudge(bool);
    int SetNumBJudge(bool);

private:
    int* numA = NULL;
    int numASign = 0;// '0' means plus, '1' means minus
    int numALength = 0;
    bool numAJudge = false;// 'true' means input legal, 'false' means input illegal

    int* numB = NULL;
    int numBSign = 0;
    int numBLength = 0;
    bool numBJudge = false;

    int operater = 0;
    bool operaterJudge = false;
};

void DataTypeRefresh(int &);

int main()
{
    int dataType = 1;
    int dataLength = 0;
    int dataGroupNum = 0;

    char* inputData = new char[100000];
    Data* calculateData = new Data;

    cout << "Test stared." << endl;
    cout << endl << "Group no." << dataGroupNum << endl;
    while(gets(inputData) != NULL)
    {
        dataLength = strlen(inputData);
        switch(dataType)
        {
            case 1 : calculateData->NumAWrite(inputData, dataLength);
            break;
            case 2 : calculateData->NumBWrite(inputData, dataLength);
            break;
            case 3 : calculateData->OperaterWrite(inputData);
            calculateData->Calculate();
            calculateData->~Data();
            calculateData = new Data;
            dataGroupNum++;
            cout << endl << endl << "Group no." << dataGroupNum << endl;
            break;
            default : cout << "Unknown error in main" << endl;
            exit (1);
        }

        DataTypeRefresh(dataType);
        delete[] inputData;
        inputData = new char[100000];
    }

}

int Data::NumAWrite(char* inputData, int dataLength)
{
    bool recordBeginFlag = false;
    int recordBeginPosition = -1;
    numAJudge = true;

    numASign = 0;
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
    else if((inputData[0] < '0' || inputData[0] > '9') || inputData[0] == '\0')
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
                return 0;
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

    if(recordBeginFlag == false)
    {
        recordBeginPosition = dataLength;
        numALength = 1;
        numA = new int[numALength];
        numA[0] = 0;
    }
    /*cout << "numA inputed" << endl;
    cout << "numA = " << numASign << ' ';
    for(int i = 0; i < numALength; i++)
    {
        cout << numA[i];
    }
    cout <<endl;*/

    return 0;
}

int Data::NumBWrite(char* inputData, int dataLength)
{
    bool recordBeginFlag = false;
    int recordBeginPosition = -1;
    numBJudge = true;

    numBSign = 0;
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
    else if((inputData[0] < '0' || inputData[0] > '9') || inputData[0] == '\0')
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

    if(recordBeginFlag == false)
    {
        recordBeginPosition = dataLength;
        numBLength = 1;
        numB = new int[numBLength];
        numB[0] = 0;
    }
    /*cout << "numB inputed" << endl;
    cout << "numB = " << numBSign << ' ';
    for(int i = 0; i < numBLength; i++)
    {
        cout << numB[i];
    }
    cout <<endl;*/
}

int Data::OperaterWrite(char* inputData)
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
        if(numASign == 1)
        {
            SetNumAJudge(false);
        }
        else if(numBSign == 1)
        {
            SetNumBJudge(false);
        }
        if(numBLength == 1 && numB[0] == 0)
        {
            SetNumBJudge(false);
        }
        break;
        default : operater = -1;
        operaterJudge = false;
        break;
    }

    if(inputData[1] != '\0')
    {
        operaterJudge = false;
    }

    //cout << "operater = " << operater << endl;
    return 0;
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

int Data::SetNumAJudge(bool judge)
{
    numAJudge = judge;
}

int Data::SetNumBJudge(bool judge)
{
    numBJudge = judge;
}

int Data::Calculate(void)
{
    if (InputErrorInformation() == 1)
    {
        return 0;
    }

    switch(operater)
    {
        case 1 : Plus();
        break;
        case 2 : Minus();
        break;
        case 3 : Multiply();
        break;
        case 4 : Divide();
        break;
        default : cout << "Unknown error in Data::Calculate" << endl;
        break;
    }
    return 0;
}

int Data::Plus(void)
{
    int minDataLength = 0;
    int maxDataLength = 0;
    char largerNum = ' ';
    int *answer = nullptr;
    int answerSign = 0;
    char calculateType = ' ';
    bool equalLengthFlag = false;
    bool changeOutputFlag = false;

    if(numALength < numBLength)
    {
        largerNum = 'B';
        //cout << "largerNum = B" << endl;
        minDataLength = numALength;
        maxDataLength = numBLength;
    }
    else if(numALength > numBLength)
    {
        largerNum = 'A';
        //cout << "largerNum = A" << endl;
        minDataLength = numBLength;
        maxDataLength = numALength;
    }
    else
    {
        equalLengthFlag = true;
        largerNum = '?';
        //cout << "largerNum = ?" << endl;
        minDataLength = numALength;
        maxDataLength = numALength;
    }

    answer = new int[maxDataLength + 1];

    if(numASign == numBSign)
    {
        calculateType = '+';
        //cout << "calculateType = +" << endl;
        answerSign = numASign;
    }
    else
    {
        calculateType = '-';
        //cout << "calculateType = -" << endl;
        if(largerNum == 'A')
        {
            answerSign = numASign;
        }
        else if(largerNum == 'B')
        {
            answerSign = numBSign;
        }
        else if(largerNum == '?')
        {
            answerSign = numASign;
        }
        else
        {
            cout << "Unknown error in Data::Plus 01" << endl;
            return 1;
        }
    }

    int answerTemp = 0;
    int carryTemp = 0;
    int borrowTemp = 0;
    int dataNum = 0;

    if(calculateType == '+')
    {
        for(dataNum = 0; dataNum < minDataLength; dataNum++)
        {
            answerTemp = numA[numALength - dataNum - 1] + numB[numBLength - dataNum - 1] + carryTemp;
            carryTemp = answerTemp / 10;
            answer[dataNum] = answerTemp % 10;
        }

        if(largerNum == 'A')
        {
            for(dataNum = minDataLength; dataNum < maxDataLength; dataNum++)
            {
                answerTemp = numA[numALength - dataNum - 1] + carryTemp;
                carryTemp = answerTemp / 10;
                answer[dataNum] = answerTemp %10;
            }
        }
        else
        {
            for(dataNum = minDataLength; dataNum < maxDataLength; dataNum++)
            {
                answerTemp = numB[numBLength - dataNum - 1] + carryTemp;
                carryTemp = answerTemp / 10;
                answer[dataNum] = answerTemp %10;
            }
        }

        if(carryTemp != 0)
        {
            answer[maxDataLength] = carryTemp;
        }
        else
        {
            answer[maxDataLength] = 0;
        }
    }
    else if(calculateType == '-')
    {
        if(largerNum == 'A')
        {
            answerSign = numASign;
            for(dataNum = 0; dataNum < minDataLength; dataNum++)
            {
                answerTemp = numA[numALength - dataNum - 1] - numB[numBLength - dataNum - 1] - borrowTemp;
                if(answerTemp < 0)
                {
                    borrowTemp = 1;
                    answer[dataNum] = answerTemp + 10;
                }
                else if(answerTemp >= 0)
                {
                    borrowTemp = 0;
                    answer[dataNum] = answerTemp;
                }
            }
            for(dataNum = minDataLength; dataNum < maxDataLength - 1; dataNum++)
            {
                answerTemp = numA[numALength - dataNum - 1] - borrowTemp;
                if(answerTemp < 0)
                {
                    borrowTemp = 1;
                    answer[dataNum] = answerTemp + 10;
                }
                else if(answerTemp >= 0)
                {
                    borrowTemp = 0;
                    answer[dataNum] = answerTemp;
                }
            }
            if(borrowTemp != 0)
            {
                answer[dataNum] = numA[numALength - dataNum - 1] - borrowTemp;
                answer[dataNum + 1] = 0;
            }
            else if(borrowTemp == 0)
            {
                answer[dataNum] = numA[numALength - dataNum - 1];
                answer[dataNum + 1] = 0;
            }
        }
        else if(largerNum == 'B')
        {
            answerSign = numBSign;
            for(dataNum = 0; dataNum < minDataLength; dataNum++)
            {
                answerTemp = numB[numBLength - dataNum - 1] - numA[numALength - dataNum - 1] - borrowTemp;
                if(answerTemp < 0)
                {
                    borrowTemp = 1;
                    answer[dataNum] = answerTemp + 10;
                }
                else if(answerTemp >= 0)
                {
                    borrowTemp = 0;
                    answer[dataNum] = answerTemp;
                }
            }
            for(dataNum = minDataLength; dataNum < maxDataLength - 1; dataNum++)
            {
                answerTemp = numB[numBLength - dataNum - 1] - borrowTemp;
                if(answerTemp < 0)
                {
                    borrowTemp = 1;
                    answer[dataNum] = answerTemp + 10;
                }
                else if(answerTemp >= 0)
                {
                    borrowTemp = 0;
                    answer[dataNum] = answerTemp;
                }
            }
            if(borrowTemp != 0)
            {
                answer[dataNum] = numB[numBLength - dataNum - 1] - borrowTemp;
                answer[dataNum + 1] = 0;
            }
            else if(borrowTemp == 0)
            {
                answer[dataNum] = numB[numBLength - dataNum - 1];
                answer[dataNum + 1] = 0;
            }
        }
        else if(largerNum == '?')
        {
            answerSign = numASign;
            for(dataNum = 0; dataNum < maxDataLength - 1; dataNum++)
            {
                answerTemp = numA[numALength - dataNum - 1] - numB[numBLength - dataNum - 1] - borrowTemp;
                if(answerTemp < 0)
                {
                    borrowTemp = 1;
                    answer[dataNum] = answerTemp + 10;
                }
                else if(answerTemp >= 0)
                {
                    borrowTemp = 0;
                    answer[dataNum] = answerTemp;
                }
            }
            answerTemp = numA[numALength - dataNum - 1] - numB[numBLength - dataNum - 1] - borrowTemp;
            if(answerTemp >= 0)
            {
                changeOutputFlag = false;
                answer[dataNum] = answerTemp;
                answer[dataNum + 1] = 0;
            }
            else if(answerTemp < 0)
            {
                changeOutputFlag = true;
                answer[dataNum] = answerTemp + 10;
                answer[dataNum + 1] = 0;
            }
        }
    }
    else
    {
        cout << "Unknown error in Data::Plus" << endl;
        return 1;
    }

    if(changeOutputFlag == true)
    {
        if(answerSign == 0)
        {
            answerSign = 1;
        }
        else if(answerSign == 1)
        {
            answerSign = 0;
        }

        answer[0] = 10 - answer[0];
        for(dataNum = 1; dataNum < maxDataLength; dataNum++)
        {
            answer[dataNum] = 9 - answer[dataNum];
        }
    }

    int outputStartPosition = 0;
    cout << "answer: ";
    if(answerSign == 1)
    {
        cout << '-';
    }

    dataNum = maxDataLength;
    while((answer[dataNum] == 0) && (dataNum >= 0))
    {
        dataNum--;
    }

    if(dataNum == -1)
    {
        cout << 0;
    }
    else if(dataNum > 0)
    {
        while(dataNum >= 0)
        {
            cout << answer[dataNum];
            dataNum--;
        }
    }
    //////
    delete[] answer;
    return 0;
}

int Data::Minus(void)
{
    if(numBSign == 0)
    {
        numBSign = 1;
    }
    else if(numBSign == 1)
    {
        numBSign = 0;
    }
    Plus();
    return 0;
}

int Data::Multiply(void)
{
    int *answer = nullptr;
    int *largerNumPtr = nullptr;
    int *shorterNumptr = nullptr;
    int answerTemp = 0;
    int answerSign = 0;
    int carryTemp = 0;
    int answerLength = numALength + numBLength;
    int answerNum = 0;
    int scanNum = 0;
    int maxDataLength = 0;
    int minDataLength = 0;

    if(numALength <= 1 && numBLength <= 1)
    {
        cout << "answer: " << numA[0] * numB[0] << endl;
        return 0;
    }

    answer = new int[answerLength];
    if(numALength < numBLength)
    {
        largerNumPtr = numB;
        shorterNumptr = numA;
        maxDataLength = numBLength;
        minDataLength = numALength;
    }
    else if(numALength >= numBLength)
    {
        largerNumPtr = numA;
        shorterNumptr = numB;
        maxDataLength = numALength;
        minDataLength = numBLength;
    }
    else
    {
        cout << "Error in Data::Multiply" << endl;
    }


    if(numASign == numBSign)
    {
        answerSign = 0;
    }
    else if(numASign != numBSign)
    {
        answerSign = 1;
    }
    else
    {
        cout << "Error in Data::Multiply" << endl;
    }

    //Lattice multiply
    answerTemp = 0;
    carryTemp = 0;
    for(answerNum = 0; answerNum < minDataLength; answerNum++)
    {
        answerTemp = 0;
        for(scanNum = 0; scanNum <= answerNum; scanNum++)
        {
            answerTemp += (largerNumPtr[maxDataLength - 1 - scanNum] * shorterNumptr[minDataLength -1 - answerNum + scanNum]) % 10;
        }
        for(scanNum = 0; scanNum <answerNum; scanNum++)
        {
            answerTemp += (largerNumPtr[maxDataLength - 1 - scanNum] * shorterNumptr[minDataLength - answerNum + scanNum]) / 10;
        }
        answerTemp += carryTemp;
        carryTemp = answerTemp / 10;
        answer[answerNum] = answerTemp - 10 * carryTemp;
    }
    for(answerNum = minDataLength; answerNum < maxDataLength; answerNum++)
    {
        answerTemp = 0;
        for(scanNum = 0; scanNum < minDataLength; scanNum++)
        {
            answerTemp += (largerNumPtr[maxDataLength - 1 - (answerNum - minDataLength) -scanNum] * shorterNumptr[scanNum]) / 10;
            answerTemp += (largerNumPtr[maxDataLength - 2 - (answerNum - minDataLength) -scanNum] * shorterNumptr[scanNum]) % 10;
        }
        answerTemp += carryTemp;
        carryTemp = answerTemp / 10;
        answer[answerNum] = answerTemp - 10 * carryTemp;
    }
    for(answerNum = maxDataLength; answerNum < answerLength; answerNum++)
    {
        answerTemp = 0;
        for(scanNum = 0; scanNum < minDataLength - (answerNum - maxDataLength); scanNum++)
        {
            answerTemp += (largerNumPtr[minDataLength - (answerNum - maxDataLength) - 1 - scanNum] * shorterNumptr[scanNum]) / 10;
        }
        for(scanNum = 0; scanNum < minDataLength - (answerNum - maxDataLength) - 1; scanNum++)
        {
            answerTemp += (largerNumPtr[minDataLength - (answerNum - maxDataLength) - 2 - scanNum] * shorterNumptr[scanNum]) % 10;
        }
        answerTemp += carryTemp;
        carryTemp = answerTemp / 10;
        answer[answerNum] =  answerTemp - 10 * carryTemp;
    }

    int outputStartPosition = 0;
    int dataNum = 0;
    cout << "answer: ";
    if(answerSign == 1)
    {
        cout << '-';
    }

    dataNum = answerLength - 1;
    while((answer[dataNum] == 0) && (dataNum >= 0))
    {
        dataNum--;
    }

    if(dataNum == -1)
    {
        cout << 0;
    }
    else if(dataNum > 0)
    {
        while(dataNum >= 0)
        {
            cout << answer[dataNum];
            dataNum--;
        }
    }

    delete[] answer;
    return 0;
}

int Data::Divide(void)
{
    int *answer = nullptr;
    int dividentTemp = 0;
    int quotientTemp = 0;
    int remainderTemp = 0;

    if(numALength < numBLength)
    {
        cout << "quotient: 0" << endl;
        cout << "remainder: ";
        for(int dataNum = 0; dataNum < numBLength; dataNum++)
        {
            cout << numB[dataNum];
        }
        cout << endl;
        return 0;
    }


    return 0;
}

int Data::InputErrorInformation(void)
{
    bool errorExistFlag = false;

    if(numAJudge == false)
    {
        errorExistFlag = true;
        cout << "Error occurred in numA input" << endl;
    }
    if(numBJudge == false)
    {
        errorExistFlag = true;
        cout << "Error occurred in numB input" << endl;
    }
    if(operaterJudge == false)
    {
        errorExistFlag = true;
        cout << "Error occurred in operater input" << endl;
    }

    if(errorExistFlag == true)
    {
        return 1;
    }
    else if(errorExistFlag == false)
    {
        return 0;
    }
}
