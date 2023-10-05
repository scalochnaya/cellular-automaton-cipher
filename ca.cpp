#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

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
        cout << "Invalid argument - '" << invalidArg << "'. Use -d to decipher, -c to cipher\n";
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

class InvalidRule : public exception
{
private:
    char* invalidArg;

public:
    InvalidRule(char* arg) { invalidArg = arg; }

    void print()
    {
        cout << "Invalid argument - '" << invalidArg << "'. Use integer num to set a new rule\n";
    }
};

class ArgumentLoss : public exception
{
public:
    void print()
    {
        cout << "Argument loss\n";
    }
};

int activeRule = 228;
void setRule(int r)
{
    activeRule = r;
}


class Cube
{
protected:
    bitset<8> b;

public:
    Cube(char convert) { bitset<8> a(convert); b = a; }

    bitset<1> operator[](int index) { return b.test(index); } // правило индексации пусть как в дискре будет

    char getSymbol() { return (char)b.to_ulong(); }
};

class Text
{
protected:
    vector<Cube> field;

public:
    Text()
    {
        // конструктор принимает файл и считывает хексдамп в кубы
    }

};



int cipher()
{
    return 0;
}

int decipher()
{
    return 0;
}




int main(int argc, char* argv[])
{
    try
    {
        if (argc == 1)
            throw NullInputFile();

        if (!argv[2])
            throw ArgumentLoss();

        ifstream inputFile(argv[2], ios::binary);
        
        if (!inputFile)
            throw FailedToOpenFile(argv[2]);
        cout << "* Successfully opened file *\n";

        inputFile.seekg(0, ios::end);
        int sizeOfFile = inputFile.tellg();
        inputFile.seekg(0, ios::beg);
        cout << "* File size: " << sizeOfFile << " *\n";

        if (argc > 3)
        {
            if (argv[3][0] == '-' && argv[3][1] == 'r')
            {
                if (!argv[4])
                {
                    inputFile.close();
                    throw ArgumentLoss();
                }

                if (atoi(argv[4]))
                {
                    setRule(atoi(argv[4]));
                    cout << "* New rule is set *\n";
                }
                else
                {
                    inputFile.close();
                    throw InvalidRule(argv[4]);
                }
            }
            else
            {
                inputFile.close();
                throw InvalidCommandLineParameter(argv[3]);
            }
        }

        if (argv[1][0] == '-')
        {
            if (argv[1][1] == 'd')
            {
                cout << "* is -d *\n";
                decipher();
            }
            else if (argv[1][1] == 'c')
            {
                cout << "* is -c *\n";
                cipher();
            }
            else
            {
                inputFile.close();
                throw InvalidCommandLineParameter(argv[1]);
            }
        }
        else
        {
            inputFile.close();
            throw InvalidCommandLineParameter(argv[1]);
        }



        ofstream outputFile("result", ios::binary);
        if (outputFile)
        {
            //пока просто копирование в файл без расширения
            Cube c('a');
            for (int i = 0; i < sizeOfFile; i++)
            {
                c = inputFile.get();
                outputFile << c.getSymbol();
            }

            outputFile.close();
        }

        inputFile.close();
    }
    catch (NullInputFile e) { e.print(); }
    catch (FailedToOpenFile e) { e.print(); }
    catch (InvalidCommandLineParameter e) { e.print(); }
    catch (InvalidRule e) { e.print(); }
    catch (ArgumentLoss e) { e.print(); }
    catch (...) { cout << "Smthng went wrong...\n"; }

    return 0;
}
