#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

const string ClientDataFile = "Clients Data.txt";



enum enOpsions { Nothing, Show, Add, Delete, Update, Find, Exit };

struct strClientData
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool ClientMark = false;
};

// Declarations .
void _PrintHeaderInOrder(enOpsions Opstion);
void _PrintClientCard(strClientData Client);

string ReadString(string Messege)
{
    cout << Messege;
    string x;
    getline(cin, x);

    return x;
}

strClientData FillClientData()
{
    strClientData Data;


    cout << "\nPlease enter Account number: ";
    getline(cin >> ws, Data.AccountNumber);

    Data.PinCode = ReadString("\nPlease enter Pin code: ");

    Data.Name = ReadString("\nPlease enter Name: ");

    Data.Phone = ReadString("\nPlease enter Phone: ");

    cout << "\nPlease enter Account balance : ";
    cin >> Data.AccountBalance;

    return Data;
}

vector <string> SplitString(string str, string Delim)
{
    vector <string> vWords;
    string Word = "";

    short Pos = 0;

    while ((Pos = str.find(Delim)) != std::string::npos)
    {
        Word = str.substr(0, Pos);

        if (Word != "")
        {
            vWords.push_back(Word);
        }

        str.erase(0, Pos + Delim.length());
    }

    if (str != "")
    {
        vWords.push_back(str);
    }

    return vWords;
}

string ConvertClientRecordToLine(strClientData ClientData, string Delim)
{
    string RecordLine;
    RecordLine += ClientData.AccountNumber + Delim;
    RecordLine += ClientData.PinCode + Delim;
    RecordLine += ClientData.Name + Delim;
    RecordLine += ClientData.Phone + Delim;
    RecordLine += to_string(ClientData.AccountBalance);


    return RecordLine;

}

strClientData FillStructWithRecordLine(string str, string Delim = "#//#")
{
    vector <string> vSplitedString = SplitString(str, Delim);

    strClientData ClientData;

    ClientData.AccountNumber = vSplitedString[0];
    ClientData.PinCode = vSplitedString[1];
    ClientData.Name = vSplitedString[2];
    ClientData.Phone = vSplitedString[3];
    ClientData.AccountBalance = stod(vSplitedString[4]);

    return ClientData;
}

vector <strClientData> LoadClientDataFromFile(string FileName)
{
    fstream File;
    vector <strClientData> vClients;

    File.open(FileName, ios::in);

    string Line;

    if (File.is_open())
    {
        strClientData Client;

        while (getline(File, Line))
        {
            Client = FillStructWithRecordLine(Line);

            vClients.push_back(Client);
        }
        File.close();
    }

    return vClients;
}


//Add Clients .
void AddClientToFile(string FileName, const string DataLine)
{
    fstream File;

    File.open(FileName, ios::out | ios::app);

    if (File.is_open())
    {
        File << DataLine << endl;

        File.close();
    }
}

void AddClient()
{
    strClientData Client;

    Client = FillClientData();
    AddClientToFile(ClientDataFile, ConvertClientRecordToLine(Client, "#//#"));
}

void AddClients(vector <strClientData>& vClients)
{

    char Add = 'y';
    while (toupper(Add) == 'Y')
    {
        _PrintHeaderInOrder(enOpsions::Add);

        cout << "Adding new client :\n\n";

        AddClient();
        vClients = LoadClientDataFromFile(ClientDataFile);


        cout << "\nClient added succisfully, Do you want add a new client Y/N : ";
        cin >> Add;

    }

}


//Find And Delete Clients .
bool FindClientByAccountNumber(string AccountNumber, vector <strClientData> vClients, strClientData& Client)
{


    for (strClientData& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;

            return true;
        }
    }

    return false;
}

void MarkClientToDelete(string AccountNumber, vector <strClientData>& vClients)
{
    for (strClientData& c : vClients)
    {
        if (c.AccountNumber == AccountNumber)
        {
            c.ClientMark = true;
        }
    }
}

void SaveClientToFile(string FileName, vector <strClientData> vClients)
{
    fstream File;

    File.open(FileName, ios::out);

    if (File.is_open())
    {
        string Line = "";

        for (strClientData& c : vClients)
        {
            if (c.ClientMark == false)
            {
                Line = ConvertClientRecordToLine(c, "#//#");

                File << Line << endl;
            }
        }

        File.close();
    }
}

void DeleteClientFromFile(string AccountNumber, vector <strClientData>& vClients)
{

    strClientData Client;
    char Answer = 'y';


    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        _PrintHeaderInOrder(enOpsions::Delete);

        _PrintClientCard(Client);

        cout << "\n\n Are you sure you want to delete this client Y/N ?? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientToDelete(AccountNumber, vClients);
            SaveClientToFile(ClientDataFile, vClients);

            //Refresh vector with last changes .
            vClients = LoadClientDataFromFile(ClientDataFile);

            cout << "\n\nClient Deleted Succfully.\n";

        }
    }
    else
    {
        cout << "\n\nSorry client is not found .\n\n";
    }


}

//Upadate Client .
strClientData ChangeClient(string AccountNumber)
{
    strClientData c;

    c.AccountNumber = AccountNumber;

    cout << "\nPlease enter Pin Code : ";
    getline(cin >> ws, c.PinCode);
    c.Name = ReadString("\nPlease enter Name : ");
    c.Phone = ReadString("\nPlease enter Phone : ");
    c.AccountBalance = stod(ReadString("\nPlease enter Account Balance : "));

    return c;
}
bool UpdateClient(string AccountNumber, vector <strClientData>& vClients)
{
    strClientData Client;
    char Answer = 'y';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        _PrintHeaderInOrder(enOpsions::Update);

        _PrintClientCard(Client);

        cout << "\n Are you sure you want to update this client informations Y/N ?? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            for (strClientData& c : vClients)
            {
                if (c.AccountNumber == AccountNumber)
                {
                    c = ChangeClient(AccountNumber);
                    break;
                }
            }


            SaveClientToFile(ClientDataFile, vClients);


            cout << "\nCLient updated succfully .";
            return 1;
        }
    }
    else
    {
        cout << "\nClient not found !!";

        return 0;
    }

}


//Show CLients Data .
void _PrintClientCard(strClientData Client)
{
    cout << "\nClient Card\n";
    cout << "-----------------------\n";
    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "Pin Code       : " << Client.PinCode << endl;
    cout << "Client Name    : " << Client.Name << endl;
    cout << "Phone          : " << Client.Phone << endl;
    cout << "Balance        : " << Client.AccountBalance << endl;
    cout << "-----------------------\n";
    cout << endl;

}

void _PrintClientRecord(strClientData Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}

void _PrintAllClientsData(vector <strClientData> vClients)
{
    cout << "\n\t\t\t\t\tClients List  (" << vClients.size() << ") Client(s) \n";
    cout << "----------------------------------------------------------------------------------------------------\n\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n\n----------------------------------------------------------------------------------------------------\n";

    for (strClientData& Client : vClients)
    {
        _PrintClientRecord(Client);
        cout << endl;
    }

    cout << "\n----------------------------------------------------------------------------------------------------\n";

}

void _PrintHeaderInOrder(enOpsions Opstion)
{
    switch (Opstion)
    {
    case Add:
        cout << "=============================================================================\n";
        cout << "                                  Add Client Secreen                         \n";
        cout << "=============================================================================\n\n";

        break;

    case Update:
        cout << "================================================================================\n";
        cout << "                                  Update Client Secreen                         \n";
        cout << "================================================================================\n\n";

        break;

    case Delete:
        cout << "================================================================================\n";
        cout << "                                  Delete Client Secreen                         \n";
        cout << "================================================================================\n\n";

        break;

    case Find:
        cout << "==============================================================================\n";
        cout << "                                  Find Client Secreen                         \n";
        cout << "==============================================================================\n\n";

        break;

    default:
        cout << ".";

    }

}

void _PrintMainMenu()
{
    system("cls");

    cout << "=========================================\n";
    cout << "           Main Menu Screen              \n";
    cout << "=========================================\n\n";

    cout << "[1] Show Client List.\n";
    cout << "[2] Add New Client.\n";
    cout << "[3] Delete Client.\n";
    cout << "[4] Update Client Info.\n";
    cout << "[5] Find Client.\n";
    cout << "[6] Exit.\n";

    cout << "=========================================\n";

}




void ActivateTheOption(enOpsions Chosen, vector <strClientData>& vClients)
{
    switch (Chosen)
    {
    case Show:
    {
        system("cls");
        _PrintAllClientsData(vClients);
        cout << "\n";
        system("Pause");
        break;
    }

    case Add:
    {
        system("cls");

        AddClients(vClients);

        cout << "\n";
        system("Pause");
        break;
    }

    case Delete:
    {
        system("cls");

        string AccountNumber = ReadString("Enter account number to update : ");
        DeleteClientFromFile(AccountNumber, vClients);

        cout << "\n";
        system("Pause");
        break;
    }

    case Update:
    {
        system("cls");


        string AccountNumber = ReadString("Enter account number to update : ");
        UpdateClient(AccountNumber, vClients);

        cout << "\n";
        system("Pause");
        break;
    }

    case Find:
    {
        system("cls");

        string AccountNumber = ReadString("Enter account number to find : ");
        strClientData Client;

        if (FindClientByAccountNumber(AccountNumber, vClients, Client))
            _PrintClientCard(Client);
        else
            cout << "\nClient not found!\n\n";

        cout << "\n";
        system("Pause");
        break;
    }


    case Exit:
    {
        system("cls");

        cout << "\n";
        system("Pause");
        break;
    }

    default:
    {
        system("cls");
        cout << "\nWrong option.\n";

        system("Pause");
        break;
    }
    }
}
enOpsions ReadAnOpstion(string Messege)
{
    int num;
    cout << Messege;
    cin >> num;

    return (enOpsions)num;
}



void RunBankSystem()
{

    enOpsions Opstion = enOpsions::Nothing;
    vector <strClientData> vClients = LoadClientDataFromFile(ClientDataFile);


    while (Opstion != enOpsions::Exit)
    {

        _PrintMainMenu();
        Opstion = ReadAnOpstion("Choose what do you want to do? [1 to 6]? ");

        ActivateTheOption(Opstion, vClients);
    }
}

int main()
{
    RunBankSystem();

    return 0;
}


