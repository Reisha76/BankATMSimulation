#include "ATM.h"
stClientData CurrentClient;

vector <string> SplitString(string Line, string delim)
{
    short pos = 0;
    string CurrentWord = "";
    vector <string> vStrings;

    while ((pos = Line.find(delim)) != string::npos)
    {
        CurrentWord = Line.substr(0, pos);

        if (CurrentWord != "")
        {
            vStrings.push_back(CurrentWord);
        }

        Line.erase(0, pos + delim.length());

    }

    if (Line != "")
    {
        vStrings.push_back(Line);
    }

    return vStrings;
}

void ShowATMMainMenu()
{
    system("cls");
    cout << "====================================================" << endl;
    cout << "\t\tATM Main Menu Screen" << endl;
    cout << "====================================================" << endl;
    cout << "\t[1] Quick Withdraw" << endl;
    cout << "\t[2] Normal Withdraw" << endl;
    cout << "\t[3] Deposit" << endl;
    cout << "\t[4] Check Balance" << endl;
    cout << "\t[5] Log out" << endl;
    cout << "====================================================" << endl;
    ExecuteMenuChoice((enATMMenuChoices)GetMenuChoice());
}

short GetMenuChoice()
{
    short MenuNumber = 0;
    cout << "Choose what do you want to do? [1 to 5]?\n";
    cin >> MenuNumber;

    return MenuNumber;
}

void ExecuteMenuChoice(enATMMenuChoices MenuChoice)
{
    switch (MenuChoice)
    {
    case enATMMenuChoices::QuickWithdraw:

        QuickWithdrawScreen();

        break;

    case enATMMenuChoices::NormalWithdraw:
        NormalWithdrawScreen();
        ExecuteNormalWithdraw();
        ReturnToMainMenu();
        break;

    case enATMMenuChoices::Deposit:

        DepositMoneyScreen();
        ATMDepositMoney();
        ReturnToMainMenu();
        break;

    case enATMMenuChoices::CheckBalance:
        
        system("cls");

        CheckBalanceScreen();
        ShowClientBalance();
        ReturnToMainMenu();
        break;

    case enATMMenuChoices::LogOut:

        StartProgram();
        break;
    }
}

void ReturnToMainMenu()
{
    cout << "\n\nPress any key to return to main menu...";
    system("pause>0");
    ShowATMMainMenu();
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

string GetAccNumToSearch()
{
    string AccNumber = "";
    cout << "Enter account number: ";
    cin >> AccNumber;

    return AccNumber;
}

vector <stClientData> LoadClientsDataFromFile(string FileName)
{
    fstream MyFile;
    vector <stClientData> vClients;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClientData Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line, delim);

            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

stClientData ConvertLineToRecord(string Line, string delim)
{
    stClientData Client;
    vector <string> vClientData;
    vClientData = SplitString(Line, delim);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.ClientName = vClientData[2];
    Client.Phone = vClientData[3];
    Client.Balance = stod(vClientData[4]);

    return Client;
}

string ConvertRecordToLine(stClientData Client, string Separator)
{
    string ClientRecord = "";

    ClientRecord += Client.AccountNumber + Separator;
    ClientRecord += Client.PinCode + Separator;
    ClientRecord += Client.ClientName + Separator;
    ClientRecord += Client.Phone + Separator;
    ClientRecord += to_string(Client.Balance);

    return ClientRecord;
}

vector <stClientData> SaveClientsDataToFile(string FileName, vector <stClientData> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (stClientData C : vClients)
        {
            if (C.MarkClientForDeletion == false)
            {
                DataLine = ConvertRecordToLine(C, delim);//omly write records that are NOT marked for deletion
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }

    return vClients;
}

void DepositMoneyScreen()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\t Deposit money screen " << endl;
    cout << "----------------------------------------\n" << endl;
}

void WithdrawMoneyScreen()
{
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\t Withdraw money screen " << endl;
    cout << "----------------------------------------\n" << endl;
}

void LoginScreen()
{

    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "\tLogin Screen " << endl;
    cout << "----------------------------------------" << endl;

}

void StartProgram()
{
    bool IsValidUser = true;

    do
    {
        string AccountNumber, PinCode;
        LoginScreen();

        if (!IsValidUser)
            cout << "\nInvalid Account Number/Pincode!";

        cout << "\nEnter Username:";
        cin >> AccountNumber;

        cout << "\nEnter Password:";
        cin >> PinCode;

        IsValidUser = CheckClientLogin(AccountNumber, PinCode, CurrentClient);

    } while (!IsValidUser);

    ShowATMMainMenu();
}

bool CheckClientLogin(string AccountNumber, string PinCode, stClientData& CurrentClient)
{
    vector <stClientData> vClientData;
    vClientData = LoadClientsDataFromFile(FileNameClient);

    for (stClientData& FileClient : vClientData)
    {
        if (AccountNumber == FileClient.AccountNumber && PinCode == FileClient.PinCode)
        {
            CurrentClient = FileClient;
            return true;
        }
    }
    return false;
}

void CheckBalanceScreen()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "\t Check Balance screen " << endl;
    cout << "========================================" << endl;
}

void ShowClientBalance()
{
    cout << "Your current balance is: " << CurrentClient.Balance << endl;
}

void QuickWithdrawScreen()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "\t\tQuick Withdraw " << endl;
    cout << "========================================" << endl;
    cout << "\t[1] 20\t\t[2] 50" << endl;
    cout << "\t[3] 100\t\t[4] 200" << endl;
    cout << "\t[5] 400\t\t[6] 600" << endl;
    cout << "\t[7] 800\t\t[8] 1000" << endl;
    cout << "\t[9] Exit"<<endl;
    cout << "========================================" << endl;
    ShowClientBalance();
    ExecuteQuickDrawChoice((enQuickDraw)GetQuickDrawChoice());
}

short GetQuickDrawChoice()
{
    short Choice=0;
    while (Choice < 1 || Choice>9)
    {
        cout << "Choose how much to withdraw [1] to [9]? ";
        cin >> Choice;
    }

    return Choice;
}

void ExecuteQuickDrawChoice(enQuickDraw Choice)
{
    switch (Choice)
    {
    case enQuickDraw::twenty:

        ATMWithdrawMoney(20);

        ReturnToMainMenu();
        break;

    case enQuickDraw::fifty:

        ATMWithdrawMoney(50);
        ReturnToMainMenu();
        break;

    case enQuickDraw::hundred:

        ATMWithdrawMoney(100);
        ReturnToMainMenu();
        break;

    case enQuickDraw::twoHundred:

        ATMWithdrawMoney(200);
        ReturnToMainMenu();
        break;

    case enQuickDraw::fourHundred:

        ATMWithdrawMoney(400);
        ReturnToMainMenu();
        break;

    case enQuickDraw::sixHundred:

        ATMWithdrawMoney(600);
        ReturnToMainMenu();
        break;

    case enQuickDraw::eightHundred:

        ATMWithdrawMoney(800);
        ReturnToMainMenu();
        break;

    case enQuickDraw::oneThousand:

        ATMWithdrawMoney(1000);
        ReturnToMainMenu();
        break;

    case enQuickDraw::exitQuickDraw:
        ReturnToMainMenu();

    default:
        break;
    }

}

bool ATMWithdrawMoney(int Withdraw)
{
    vector<stClientData> vClients = LoadClientsDataFromFile(FileNameClient);
    stClientData Client;
    char ans;

        for (stClientData& C : vClients)
        {
            if (C.AccountNumber == CurrentClient.AccountNumber)
            {
                while (Withdraw > C.Balance)
                {
                    cout << "Withdraw amount exceeds balance, you can withdraw up to : " << C.Balance << endl;
                    ReturnToMainMenu();
                }
                cout << "\nAre you sure you want to perform this transaction? y/n: ";
                cin >> ans;
                if (toupper(ans) == 'Y')
                {
                    Withdraw *= -1;
                    C.Balance += Withdraw;
                    cout << "\nAmount has been withdrawed succesfully. ";
                    cout << "New client balance : " << C.Balance << endl;

                    SaveClientsDataToFile(FileNameClient, vClients);
                    RefreshClientBalance(CurrentClient,C);
                    return true;
                }
                else
                    return false;
            }
        }

    return false;
}

void RefreshClientBalance(stClientData &CurrentClient, stClientData ClientNewBalance)
{
    CurrentClient.Balance = ClientNewBalance.Balance;
}

void NormalWithdrawScreen()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "\tNormal Withdraw " << endl;
    cout << "========================================" << endl;
}

void ExecuteNormalWithdraw()
{
    int Withdraw;
    do
    {
       cout << "Enter an amount that is a multiple of 5 : ";
       cin >> Withdraw;

    } while ( (Withdraw%5)!=0 );

    ATMWithdrawMoney(Withdraw);
}

bool ATMDepositMoney()
{
    vector<stClientData> vClients = LoadClientsDataFromFile(FileNameClient);
    char ans;
    int Deposit;

    for (stClientData& C : vClients)
    {
        if (C.AccountNumber == CurrentClient.AccountNumber)
        {

            cout << "Enter deposit amount: ";
            cin >> Deposit;

            while (Deposit <= 0)
            {
                cout << "Enter deposit amount: ";
                cin >> Deposit;
            }

            cout << "\nAre you sure you want to perform this transaction? y/n: ";
            cin >> ans;
            if (toupper(ans) == 'Y')
            {
                C.Balance += Deposit;
                cout << "\nAmount has been deposited succesfully. ";
                cout << "New client balance : " << C.Balance << endl;

                SaveClientsDataToFile(FileNameClient, vClients);
                RefreshClientBalance(CurrentClient, C);
                return true;
            }
            else
                return false;
        }
    }

    return false;
}