#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<conio.h>
#include<fstream>
#include"function.h"
// library used

using namespace std;

int currentCurrency(int, string[][4]);                                  //function for original currency
int currencyChange(int, string[][4]);                                   //function that change currency
float currentValue();                                                   //function that get amount of money
float changeValue(int,float,int,float [6]);                             //function for currency conversion
void menuDisp();                                                        //extern function for menu
double placeChange(int, string[][4]);                                   //function to choose place
int buy_sell();                                                         //function to select buy/sell
void receipt(int ,int ,int ,float ,float ,double , string[6]);          //function that process receipt
int opt();                                                              //option function
void admin(int *, string[][4],double [10]);                             //special menu for admin only

int main()
{
	string data[10][4],rateName[6] = {"USD","SGD","JPY","MYR","EUR","CNY"};  //initialize currency name
	float rate[6] = {4.1775,3.0189,3.7244/100,1.0,4.7479,0.6002};            //initialize currency value
	int current=0,currency=0,buysell=0,opti,user,user_num=0;
	float value,change;
	char decide,option;
	double commission = 0.0;
	double datanum[10];

	do{
        system("cls");
        cout << "\n\t\t\t---Currency Converter---\n\n\n";
        cout << "Choose user type  \n\n 1. Admin\n 2. Customer\n 3. Exit \n\nYour option : ";
        cin >> user;
        system("cls");

        if(user == 1)
        {
            admin(&user_num, data,datanum);     //prompt admin menu
        }

        if(user == 2)                          //prompt customer menu
        {
            cout << "\n\nEnter your name : ";
            cin >> data[user_num][0];
            system("cls");

            do{
                do{
                    menuDisp();
                    cout << "\n\nYour option : ";
                    cin >> option;
                    while(option<'1' || option>'4')
                    {
                        cout << "Please re-enter : ";
                        cin >> option;
                    }

                    system("cls");

                    if(option=='1') //this option allows user to convert currency from different countries
                    {
                        current = currentCurrency(user_num,data);
                        currency = currencyChange(user_num,data);
                        value = currentValue();
                        change = changeValue(current,value,currency,rate);

                        cout << fixed << setprecision(2) << endl
                             << "  " << value << " " << *(rateName + current - 1)
                             << "  =  " << change << " " << *(rateName + currency - 1) << "\n\n";
                    }

                    if(option=='2') //this option allows user to buy or sell currency
                    {
                        buysell = buy_sell();

                        if(buysell == 1) //buy currency (foreign to RM)
                        {
                            data[user_num][1] = "BUY";
                            current = currentCurrency(user_num,data);
                            value = currentValue();
                            currency = 4;
                            change = changeValue(current,value,currency,rate);
                            cout << fixed << setprecision(2) << endl << "You buy : "
                                 << "  " << value << " " << *(rateName + current - 1) << "\n\n";

                            data[user_num][3] = *(rateName + current - 1);
                            datanum[user_num] = value;

                        }

                        else if(buysell == 2) //sell currency (RM to foreign)
                        {
                            data[user_num][1] = "SELL";
                            currency = currencyChange(user_num,data);
                            value = currentValue();
                            current = 4;
                            change = changeValue(current,value,currency,rate);
                            cout << fixed << setprecision(2) << endl << "You sell : "
                                 << "  " << value << " " << "MYR \n\n";
                            data[user_num][3] = "MYR";
                            datanum[user_num] = value;
                        }

                        else
                            cout << "\n\nWrong Input!\n\n";


                        cout << "  " << value << " " << *(rateName + current - 1) << "  =  "
                             << change << " " << *(rateName + currency - 1) << "\n\n"; //summary of conversion

                        cout << " Press ENTER to continue.";
                        getch();
                        system("cls");

                        commission = placeChange(user_num,data); //choose place to change money currency

                    }

                    if(option=='3')
                    {
                        receipt(buysell,current,currency,value,change,commission,rateName); //displays receipt after conversion
                    }

                    if(option=='4') // exit to main menu
                    {
                        user_num++;
                        break;
                    }

                    getch();
                    system("cls");

                  }while(option!='4');


               }while(option=='1'||option=='2'||option=='3');

	//keep data in file
            ofstream file;
            file.open("customer_data.txt");
            for(int i=0;i<user_num;i++)
            {
                for(int j=0;j<4;j++)
                {
                    file << " " << data[i][j];
                }

                file << " " << datanum[i] << endl;
            }
            file.close();
        }

        if(user==3)
        {
            break;
        }


    }while(user==1||user==2);


    cout << "\n\n\t\t~~THANK YOU FOR USING CURRENCY CONVERTER~~\n\n";
    getch();

	return 0;
}

void admin(int *user_pt,string data[][4], double datanum[10])
{
        bool grant=0;
        string pass,name;
        int loc,optionad,user_num=*user_pt;

        cout << "\n\n Enter password : ";
        cin >> pass;
        system("cls");

        if(pass == "1234")
        {
            cout << "\n\n Choose your transaction \n\n 1. Search customer's name\n 2. All transaction history\n 3. Back\n\n Your option : ";
            cin >> optionad;
            system("cls");

            if(optionad==1)
            {
                cout << "\n\n Enter customer's name : ";
                cin >> name;

                for(int k=0;k<10;k++) //start searching for customer's name
                {
                    if(data[k][0]== name)
                    {
                        grant = 1;
                        loc=k;
                    }
                }

                if(grant)
                {

                    cout << "\n\n Transaction history for " << name << "\n\n";
                    cout << left << setw(11) << "Name" << setw(13) << "Transaction"
                         << setw(11) << "Place" << setw(11) << "Currency" << setw(11) << "Amount\n\n";

                    for(int l=0;l<4;l++)
                    {
                        cout << left << setw(11) << data[loc][l];
                    }
                    cout << left << setw(11) << datanum[loc] << endl;
                }

                else
                {
                    cout << "\n\n No customer found \n";
                }

            }

            if(optionad==2)
            {
                cout << "\n\n Transaction history \n\n ";
                cout << left << setw(11) << "Name" << setw(13) << "Transaction"
                     << setw(11) << "Place" << setw(11) << "Currency" << setw(11) << "Amount\n\n";
                for(int i=0;i<user_num;i++)
                {
                    for(int j =0;j<4;j++)
                        cout << setw(11) << data[i][j];

                    cout << setw(11) << datanum[i] << endl;
                }
            }

            else
                ;

        }

        else
            cout << "\n\n Incorrect password!";

        getch();
        system("cls");
}


int currentCurrency(int user_num, string data[][4])
{
	int current;

    //list of currencies
	cout << "\n\n\n\t\t\t"
		 << "CURRENCY EXCHANGE\n\n"
		 << "  1. United State Dollar (USD)\n"
		 << "  2. Singaporean Dollar (SGD) \n"
		 << "  3. Japanese Yen (JPY)\n"
		 << "  4. Malaysian Ringgit (MYR)\n"
		 << "  5. Euro (EUR)\n"
		 << "  6. Chinese Yuan (CNY)\n"
		 << "\n\n  Please choose current currency to be changed: ";
	do
	{
		cin >> current;
		if(current<1||current>6)
		cout << "Invalid Input!! Please Re-enter: ";
	}while(current<1||current>6);

	system("cls");

	return current;
}
int currencyChange(int user_num, string data[][4])
{
	int currency;

	//list of currencies
	cout << "\n\n\n\t\t\t"
		 << "CURRENCY EXCHANGE\n\n"
		 << "  1. United State Dollar (USD)\n"
		 << "  2. Singaporean Dollar (SGD) \n"
		 << "  3. Japanese Yen (JPY)\n"
		 << "  4. Malaysian Ringgit (MYR)\n"
		 << "  5. Euro (EUR)\n"
		 << "  6. Chinese Yuan (CNY)\n"
		 << "\n\n  Please choose currency that want to be exchanged to: ";
	do
	{
		cin >> currency;
		if(currency<1||currency>6)
		cout << "Invalid Input!! Please Re-enter: ";
	}while(currency<1||currency>6);

	system("cls");
	return currency;
}
float currentValue()
{
	float value;

	cout << "\n\n  Please enter value that want to be changed: ";
	cin >> value;

	return value;
}
float changeValue(int current,float value, int currency,float rate[6])
{
	float change;

    //calculation for conversion
	value *= rate[current-1];
	change = value/ *(rate + currency - 1);

	return change;
}



double placeChange(int user_num, string data[][4])
{
    int place;
    double commission;

    //display places
    cout << "\n\n\n\t"
         << "Choose place you want to do money changing (COMMISION RATE)\n\n"
         << " 1. Maybank (RM 4.50) \n"
         << " 2. Bank Islam (RM 4.00) \n"
         << " 3. Bank Muamalat (RM 4.30) \n"
         << " 4. Melawati Mall (RM 5.00) \n"
         << " 5. KLIA (RM 5.50) \n";

    cout << "\nYour Option : ";
    cin >> place;

    switch (place)
    {
        case 1 : commission = 4.50;data[user_num][2]="MAYBANK";break;
        case 2 : commission = 4.00;data[user_num][2]="BANK ISLAM";break;
        case 3 : commission = 4.30;data[user_num][2]="BANK MUAMALAT";break;
        case 4 : commission = 5.00;data[user_num][2]="MELAWATI MALL";break;
        case 5 : commission = 5.50;data[user_num][2]="KLIA";break;
        default : cout << "\nPlease choose your desired place\n";break;
    }

    if(place!=6)
        cout << "\nTotal commission = " << commission << endl;

    return commission;
}

int buy_sell()
{
    int choice;

    system("cls");
    cout << "\n\n1. Buy (Foreign to MYR)\n2. Sell (MYR to Foreign)\n\nChoice : ";
    cin >> choice;
    system("cls");

    return choice;

}

void receipt(int buysell,int current,int currency,float value,float change,double commission, string rateName[6]) //summary of transaction
{
    system("cls");
    cout << "\n\t\t\tSummary and Receipt\n\n";

    if(buysell == 1)
    {
        cout << fixed << setprecision(2) << endl << "You buy : "
             << "  " << value << " " << *(rateName + current - 1) << "\n\n";
        cout << "  " << value << " " << *(rateName + current - 1) << "  =  " << change << " " << *(rateName + currency - 1) << "\n\n";
        cout << "Commission = " << commission << " MYR "<< endl;
        cout << "Total paid = " << value << " " << *(rateName + current - 1) << endl;
        cout << "Total received = " << change - commission << " MYR " << endl;
    }

    else
    {
        cout << fixed << setprecision(2) << endl << "You sell : "
             << "  " << value << " " << "MYR \n\n";
        cout << "  " << value << " " << *(rateName + current - 1) << "  =  " << change << " " << *(rateName + currency - 1) << "\n\n";
        cout << "Commission = RM " << commission << endl;
        cout << "Total paid = " << commission + value << " MYR \n"
             << "Total received =  " << change << " " << *(rateName + currency - 1) << endl;
    }

}

