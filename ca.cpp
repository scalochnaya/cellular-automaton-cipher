#include <iostream>
#include <bitset>
#include <fstream>

using namespace std;


class NullInputFile : public exception
{
public:
    void print()
    {
        cout << "Please select file to cipher\n";
    }
};

class InvalidCommandLineParameter : public exception
{
private:
    char* invalidArg;

public:
    InvalidCommandLineParameter(char* arg) { invalidArg = arg; }

    void print()
    {
        cout << "Invalid arguement - '" << invalidArg << "'. Use -d to decipher, -c to cipher\n";
    }
};

class FailedToOpenFile : public exception
{
private:
    char* pathToFile;

public:
    FailedToOpenFile(char* p) { pathToFile = p; }

    void print()
    {
        cout << "Failed to open file '" << *pathToFile << "'\n";
    }
};

int activeRule = 228;
void setRule(int r)
{
    activeRule = r;
}


class Cube
{
private:
    bitset<8> b;

public:
    Cube(char convert) { bitset<8> a(convert); b = a; }

    bitset<1> operator[](int index) { return b.test(index); }

    //void printCube() { cout << b; }
};

void createField()//в аргументе файл
{
    // создает первичный слой кубов 
    // читает побайтово и преобразует в кубы
}



int cipher()
{
    return 0;
}

int decipher()
{
    return 0;
}




int main(int argc, char* argv[]) // в мейн поступает путь к файлу
{
    try
    {
        //если программа вызвана без аргументов
        if (argc == 1) throw NullInputFile();

        // иначе открываем директорию, указанную argv
        ifstream inputFile(argv[2], ios::in | ios::binary);
        if (!inputFile)
            throw FailedToOpenFile(argv[2]);
        //cout << "Successfully opened file\n";

        //проверка на то, меняется ли правило с дефолтного на пользовательское
        if (argc > 3)
        {
            if (argv[3][0] == '-' && argv[3][1] == 'r')
            {
                // + проверка на дурака
                setRule(atoi(argv[4]));
                //cout << "New rule is set\n";
            }
            else
                throw InvalidCommandLineParameter(argv[3]);
        }
        //что делаем с файлом
        if (argv[1][0] == '-')
        {
            switch (argv[1][1]) // свич по приколу
            {
            case 'd':
                //cout << "is -d\n";
                decipher();
                break;
            case 'c':
                //cout << "is -c\n";
                cipher();
                break;
            default:
                throw InvalidCommandLineParameter(argv[1]);
                break;
            }
        }
        else
            throw InvalidCommandLineParameter(argv[1]);


        inputFile.close();

        //создает новый файл в той же директории

    }
    catch (NullInputFile e) { e.print(); }
    catch (FailedToOpenFile e) { e.print(); }
    catch (InvalidCommandLineParameter e) { e.print(); }
    catch (...) { cout << "Smthng went wrong...\n"; }

    return 0;
}