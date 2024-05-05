#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>

using namespace std;

struct DATA
{
	char NAME[42];
	char ADDRESS[62];
	char EMAIL[42];
	char RENT_PURPOSE[255];
	char DATE[21];
	char TIME[21];
	char DURATION[255];
	char TRANSACTION[21];
	float COST;
	char CONTACT[12];
};

struct CONNECTION
{
    const char *SERVER = "localhost";
    const char *USER = "root";
    const char *PASSWORD = "pass123";
    const char *DATABASE = "karaoke";
};

MYSQL *connection_to_database(CONNECTION connection)
{
    MYSQL *newConnection = mysql_init(NULL);
    if (!newConnection)
    {
        cout << "Failed to create an object" << endl;
        cout << mysql_error(newConnection) << endl;
        exit(0);
    }
    if (!mysql_real_connect(newConnection, connection.SERVER, connection.USER,
                            connection.PASSWORD, connection.DATABASE, 3306, NULL, 0))
    {
        cout << "Failed to connect to database:" << endl;
        cout << mysql_error(newConnection) << endl;
        exit(0);
    }
    return newConnection;
}

MYSQL_RES *execute_query(MYSQL *connection, char* query)
{
    if (mysql_query(connection, query))
    {
        cout << "ERROR: "<<mysql_error(connection) <<endl;
					rewind(stdin);
					getchar();
    }
    cout << "Info Added"<<endl;
    return mysql_store_result(connection);
}

int main()
{
	CONNECTION id;
    MYSQL* connection = connection_to_database(id);
    
    DATA data;
	string customerName, purpose, contactDetails, address, email, karaokeDetails, payment,note = "  Thank you for renting at RENT A' OKE!";
    double totalCost = 0.0;
    int karaokeHours, karaokeMinutes, karaokeType;
    int hourDuration = 0, minutesDuration = 0, count = 0;
    string listOfKaraoke;
    char retry, agreeTerms;

    do {
        cout << "-================= >> --- << ~ + ~ >> --- << ==================-" << endl;
        cout << "\t\t     WELCOME TO RENT A' OKE\t\t  " << endl;
        cout << "\t        Most Convenient Karaoke Rentals! " << endl;
        cout << "-==============================================================-" << endl;
        cout << "\t           Types and rates of Karaoke " << endl;
        cout << "\t     [1] Classic Karaoke = $50 per hour    " << endl;
        cout << "\t     [2] Retro Karaoke = $100 per hour           " << endl;
        cout << "\t     [3] Premium Karaoke = $150 per hour     " << endl;
        cout << "-=============================================================-" << endl;
        cout << " Note: Every exceeding time will cost you an additional fee" << endl;
        cout << "\t\t [ $10 every 15 minutes ]" << endl;
        cout << "-=============================================================-" << endl; 

        // Terms and conditions agreement
        cout << "\n------------------------------------------------------------------------" << endl;
        cout << "  You need to agree with Terms and Condition to continue your Rental" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << "1. You must be at least 18 years old to rent." << endl;
        cout << "2. By proceeding, you agree to the terms and conditions." << endl;
        cout << "\t\tDo you agree? (y/n): ";
        cin >> agreeTerms;
        if (agreeTerms != 'y' && agreeTerms != 'Y') {
            cout << "You must agree to the terms and conditions to proceed." << endl;
            cout << "Sorry, you cannot proceed with renting without agreeing to the terms and conditions." << endl;
            return 0;
        }

        // Renter Information fill up
        cout << "\n---------------------------------------------------------------" << endl;
        cout << "\t\t      Renter's Information" << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "| Enter your name: ";
        cin.ignore(); 
        getline(cin, customerName);
        cout << "| Enter address: ";
        getline(cin, address);
        cout << "| Enter email: ";
        getline(cin, email);
        cout << "| Enter contact details: ";
        getline(cin, contactDetails);
        cout << "| Enter the purpose of renting: ";
        getline(cin, purpose);

        // Input renting date and time
        int rentedYear, rentedMonth, rentedDay, rentedHour, rentedMinute;
        string rentedMonths, am_pm = "AM";
        cout << "| Enter the rental date (YYYY MM DD): ";
        cin >> rentedYear >> rentedMonth >> rentedDay;
        cout << "| Enter the rental time (HH MM AM/PM): ";
        cin >> rentedHour >> rentedMinute >> am_pm;

        // Karaoke Information Section
        char addMoreKaraoke;
        string temp_list_karaoke;
        do {
        	
            cout << "-----------------------------------------" << endl;
            cout << "|\t  Types of Karaoke\t\t|\n";
            cout << "-----------------------------------------" << endl;
            cout << "| [1] Classic Karaoke = $50\n";
            cout << "| [2] Retro Karaoke = $100 \n";
            cout << "| [3] Premium Karaoke = $150\n";
            cout << "| Type of karaoke (1-3 only): ";
            cin >> karaokeType;

            if (karaokeType >= 1 && karaokeType <= 3) {
                cout << "| Enter the rental duration for karaoke type " << karaokeType << " (HH:MM): ";
                char colon;
                cin >> karaokeHours >> colon >> karaokeMinutes;

                hourDuration += karaokeHours;
                minutesDuration += karaokeMinutes;

                int karaokeCostPerHour;
                switch (karaokeType) {
                    case 1:
                        karaokeCostPerHour = 50;
                        break;
                    case 2:
                        karaokeCostPerHour = 100;
                        break;
                    case 3:
                        karaokeCostPerHour = 150;
                        break;
                    default:
                        karaokeType = 1;
                        karaokeCostPerHour = 50;
                }

                double totalHours = karaokeHours + static_cast<double>(karaokeMinutes) / 60.0;
                totalCost += totalHours * karaokeCostPerHour;
				
                listOfKaraoke += "| Type: " + to_string(karaokeType) + " - Cost: $" + to_string(karaokeCostPerHour) + " per hour\n";
                listOfKaraoke += "| Karaoke Duration: " + to_string(karaokeHours) + " hours and " + to_string(karaokeMinutes) + " minutes\n";
                temp_list_karaoke += "Type: " + to_string(karaokeType) + " - Cost: $" + to_string(karaokeCostPerHour) + " per hour\n";
                temp_list_karaoke += "Karaoke Duration: " + to_string(karaokeHours) + " hours and " + to_string(karaokeMinutes) + " minutes\n";
            } else {
                cout << "Invalid karaoke type. Please choose between 1 and 3." << endl;
            }
			
            cout << "| Add more karaoke types? (y/n): ";
            cin >> addMoreKaraoke;
			
        } while (addMoreKaraoke == 'y' || addMoreKaraoke == 'Y');
		//This will put data type karaoke
		strcpy(data.DURATION, temp_list_karaoke.c_str());
		
        // Payment method selection
        char paymentOption;
        
        
        
        cout << "| How would you like to pay? (O for Online / S for Store):";
   
        	cin >> paymentOption;
       	 	cout << "\n-==============================================================-" << endl;
  		 	cout << "|Please transfer the total amount to the following account" << endl;
  		    cout << "-==============================================================-\n" << endl;
            cout << "-----------------------------------------" << endl;
            cout << "| for Bank Payment" << endl;
            cout << "| bank Account: RENT A' OKE" << endl;
            cout << "| Account Number: 1234567890\n" << endl;
            cout << "-----------------------------------------" << endl;
            cout << "| for E-Wallet Payment" << endl;
            cout << "| Gcash: RENT A' OKE" << endl;
            cout << "| Gcash Number: 1234567890" << endl;
            cout << "-----------------------------------------" << endl;
        string transactionStatus = "Pending";

        if (paymentOption == 'O' || paymentOption == 'o') {
            char paymentMethod;
            cout << "-==============================================================-" << endl;
            cout << "| Choose your payment method (B for Bank Transfer / E for E-Wallets): ";
            cin >> paymentMethod;
            cout << "-==============================================================-" << endl;
            if (paymentMethod == 'B' || paymentMethod == 'b') {
                string accountName, accountNumber, transactionID;
                cout << "-----------------------------------------" << endl;
                  cout << "\t BANK TRANSFER\n" << endl;
                cout << "\n| Enter account name: ";
                cin.ignore();
                getline(cin, accountName);
                cout << "| Enter account number: ";
                getline(cin, accountNumber);
                cout << "| Enter transaction ID: ";
                getline(cin, transactionID);
                cout << "\n-==============================================================-" << endl;
                cout << "| Once the transfer is complete, your rental will be confirmed." << endl;
                cout << "-==============================================================-" << endl;
           
                transactionStatus = "Paid";
            } else if (paymentMethod == 'E' || paymentMethod == 'e') {
                string accountName, accountNumber, transactionID;
                cout << "\n-----------------------------------------" << endl;
                  cout << "\t E-Wallet PAYMENT\n" << endl;
                cout << "| Enter account name: ";
                cin.ignore();
                getline(cin, accountName);
                cout << "| Enter account number: ";
                getline(cin, accountNumber);
                cout << "| Enter transaction ID: ";
                getline(cin, transactionID);
                
                cout << "\n-==============================================================-" << endl;
                cout << "| Once the transfer is complete, your rental will be confirmed." << endl;
                cout << "-==============================================================-\n" << endl;
                transactionStatus = "Paid";
            }
        } else {
            cout << "| Please pay at the store. Your rental will be confirmed upon payment." << endl;
        }
		
        // Display receipt
        cout << "\n--------------------------------------------------------------" << endl;
        cout << " \t\t\t   RECEIPT\t\t\t\t  " << endl;
        cout << "--------------------------------------------------------------" << endl;
        cout << "| Renter's Name: " << customerName << endl;
        cout << "| Address: " << address << endl;
        cout << "| Email: " << email << endl;
        cout << "| Contact Details: " << contactDetails << endl;
        cout << "| Purpose of Renting: " << purpose << endl;
        cout << "| Renting Date: " << rentedYear << "-" << rentedMonth << "-" << rentedDay << " ";
        cout << rentedHour << ":" << (rentedMinute < 10 ? "0" : "") << rentedMinute << " " << am_pm << endl;
        cout << "| Karaoke Details:" << endl;
        cout << listOfKaraoke;
        if (paymentOption == 'O' || paymentOption == 'o') {
        	payment = "Online";
            cout << "| Payment method: "<< payment<<" ";
        } else {
        	payment = "Store";
            cout << "| Payment method: "<< payment<<" ";
        }
        cout << "| Transaction Status: " << transactionStatus << endl;
        cout << "| Total Cost: $" << fixed << totalCost << endl;
        cout << "-=============================================================-" << endl;
        cout << "\t   " << note << endl;
        cout << "-=============================================================-" << endl;
        cout << "  Do you want to retry/edit (r) or print your receipt (p)? :";
        cin >> retry;

        if (retry == 'p' || retry == 'P') {
        	
            cout << "\t     -------------------------------------" << endl;
            cout << "\t     |   Receipt printed successfully!   |" << endl;
            cout << "\t     -------------------------------------" << endl;
            
        //This will put into databases
        string temp_Date = to_string(rentedYear) + "-" + std::to_string(rentedMonth) + "-" + to_string(rentedDay);

		string temp_Time = to_string(rentedHour) + ":" + (rentedMinute < 10 ? "0" : "") + to_string(rentedMinute) + " " + am_pm;
		string temp_transaction = ""+payment+" "+transactionStatus;
		
        strcpy(data.NAME, customerName.c_str());
        strcpy(data.ADDRESS, address.c_str());
        strcpy(data.CONTACT, contactDetails.c_str());
        strcpy(data.EMAIL, email.c_str());
        strcpy(data.RENT_PURPOSE, purpose.c_str());
        strcpy(data.DATE, temp_Date.c_str());
        strcpy(data.TIME, temp_Time.c_str());
        strcpy(data.TRANSACTION, temp_transaction.c_str());
        data.COST = totalCost;
        
        char* collect;
		char* sentence;
		string sentence_aux;
		sentence_aux = "INSERT INTO clients(Name, Address, Contact, Email, Rent_Purpose, Rent_Date, Rent_Time, Karaoke_duration, Transaction, Total_Cost) VALUES('%s', '%s','%d', '%s', '%s','%s', '%s','%s','%s','%f')";
		sentence = new char[sentence_aux.length() + 1];
		strcpy(sentence, sentence_aux.c_str());
				
		collect = new char[strlen(sentence)+strlen(data.NAME)+strlen(data.ADDRESS)+strlen(data.CONTACT)+strlen(data.EMAIL)+strlen(data.RENT_PURPOSE)+strlen(data.DATE)+strlen(data.TIME)+strlen(data.DURATION)+strlen(data.TRANSACTION)+sizeof(float)];
		sprintf(collect, sentence, data.NAME, data.ADDRESS, data.CONTACT, data.EMAIL, data.RENT_PURPOSE, data.DATE, data.TIME, data.DURATION, data.TRANSACTION, data.COST);

		if(mysql_ping(connection)){
			cout << "ERROR: Impossible to connect." << endl;
			cout << mysql_error(connection) << endl;
			}

		MYSQL_RES* res = execute_query(connection, collect);
            
            
            break;
            
        }
        s
        cin.clear(); 
        cin.ignore(10000, '\n');

    } while (true);
    

    return 0;
}