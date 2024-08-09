#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

struct stClientData
{
    string AccountNumber;
    string PinCode;
    string ClientName;
    string Phone;
    double Balance;
    bool MarkClientForDeletion = false;
};

const string FileNameClient = "Clients.txt";
const string delim = "#//#";

enum enATMMenuChoices
{
    QuickWithdraw=1, NormalWithdraw=2, Deposit = 3, CheckBalance = 4, LogOut = 5
};

enum enQuickDraw
{
    twenty=1, fifty=2, hundred=3, twoHundred=4, fourHundred=5,
    sixHundred=6, eightHundred=7, oneThousand=8, exitQuickDraw=9
};

void ShowATMMainMenu();
short GetMenuChoice();
vector <string> SplitString(string Line, string delim);
stClientData ConvertLineToRecord(string Line, string delim);
void ExecuteMenuChoice(enATMMenuChoices MenuChoice);
void ReturnToMainMenu();
void AddDataLineToFile(string FileName, string stDataLine);
string GetAccNumToSearch();
vector <stClientData> LoadClientsDataFromFile(string FileName);
stClientData ConvertLineToRecord(string Line, string delim);
string ConvertRecordToLine(stClientData Client, string delim);
vector <stClientData> SaveClientsDataToFile(string FileName, vector <stClientData> vClients);
void DepositMoneyScreen();
void WithdrawMoneyScreen();
void LoginScreen();
bool CheckClientLogin(string UserName, string Password, stClientData& CurrentClient);
void StartProgram();
void CheckBalanceScreen();
void ShowClientBalance();
void QuickWithdrawScreen();
short GetQuickDrawChoice();
bool ATMWithdrawMoney(int Withdraw);
void ExecuteQuickDrawChoice(enQuickDraw Choice);
void RefreshClientBalance(stClientData& CurrentClient, stClientData ClientNewBalance);
void ExecuteNormalWithdraw();
void NormalWithdrawScreen();
bool ATMDepositMoney();
