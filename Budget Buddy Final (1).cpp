#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <conio.h> // Include conio.h for _getch() function
using namespace std;

int g = 100;
int h = 0;
float tba;
bool wrongp;
extern float temp[6];

class User
{
	protected:
	    int user_id;
	    string username, email;
	    char password[30];
	public:
	    void registration();
	    void login();
	    int getUserId() const 
		{ 
			return user_id; 
		}
	    const string& getUsername() const 
		{ 
			return username; 
		}
	    int logout();
	    void maskPassword(string &password);
};

void User::registration()
{
	cout<<"\n\n---------------REGISTRATION---------------\n";
	
	//USER_ID
	
	int lastUserID=100;
	ofstream loginfile("login.txt",ios::app);
	ifstream indexfile("login.txt");		//login is the file having registered users' details
	string line;
	if(indexfile.is_open())
	{
		while(getline(indexfile,line))
		{
			lastUserID++;
        }
        indexfile.close();
    }
	user_id=++lastUserID;
	
	//USERNAME
	
	cout<<"Enter Username:"<<endl;
	cin>>username;
	
	//EMAIL
	
	cout<<"Enter Email:"<<endl<<"(Format: xyz123@gmail.com)"<<endl;
	cin>>email;
	string str1="@";
	int f=email.find(str1);								//find finds the index of @
	while((f==-1)||(email.compare(f,10,"@gmail.com")!=0))
	{
		cout<<"Email is invalid"<<endl;
		cout<<"Re-enter email:"<<endl;
		cin>>email;
		f=email.find(str1);	
	}
	
	//PASSWORD	
	
	int length=0,c=0,n=0;
	int ch[10],i=0;
	cout<<"Enter password:"<<endl<<"(Password must contain a digit and a capital letter with exactly 8 characters)"<<endl;
	cin>>password;
	length=strlen(password);
	for(int i=0;i<length;i++)
	{
		ch[i]=(int)password[i];
		if((ch[i]>=65)&&(ch[i]<=90))
			(c)++;
		if((ch[i]>=48)&&(ch[i]<=57))
			(n)++;
	}
	while(length!=8||c==0||n==0)
	{
		length=0;
		cout<<"Password format invalid!\nRe-enter password-"<<endl;
		cin>>password;
		length=strlen(password);
		for(int i=0;i<length;i++)
		{
			ch[i]=(int)password[i];
			if((ch[i]>=65)&&(ch[i]<=90))
				(c)++;
			if((ch[i]>=48)&&(ch[i]<=57))
				(n)++;
		}	
	}
	
	cout<<"Registration Successful"<<endl;
	
	//Saving all this data of a user into the file "login.txt"
	loginfile<<user_id<<setw(30)<<username<<setw(30)<<email<<setw(30)<<password<<endl;
	loginfile.close();
}

void User::maskPassword(string &password) 
{
    char ch;
    cout<<"Enter password: ";
    while((ch = _getch()) != '\r') // Read characters until Enter (ASCII code 13) is pressed
	{ 
	 	
        if(ch == '\b') 	// Handle backspace character
		{  
		
            if(!password.empty()) 
			{
                cout << "\b \b";  // Move cursor back, overwrite with space, move cursor back again
                password.erase(password.size() - 1);  // Remove last character from password string
            }
        } 
		else 
		{
            cout<<'*';  // Print asterisk for each character entered
            password+=ch;  // Append character to password string
        }
    }
    cout<<endl;  // Print newline after password input
}

void User::login()
{
	cout<<"\n\n---------------LOGIN---------------\n";
	cout<<"Enter email id: ";
	cin>>email;
	int flag=0;
	string e;
	ifstream loginfile("login.txt");			//open file
	if(loginfile.is_open())
	{
    	string line;
    	
    	string token;
        while (getline(loginfile, line)) 
		{
		 	// Read each line from the file
            stringstream ss(line);
            int count = 0;
            string tempEmail;
            while (ss>>token) 
			{
                if(count==2)
				{
                    tempEmail=token; // Store email
                }
                if(count==0) 
				{
                    user_id=stoi(token); // Convert string to integer and store user_id
                } 
				else if(count==1) 
				{
                    username=token; // Store username
                }
                count++;
            }
            if(tempEmail == email) 
			{ // Check if email matches
				
                flag=1;
                break;
            }
        }
        if(flag!=1)		//Email not found in the file 
        {
           	cout<<"User not registered!"<<endl;
           	cout<<"Do you want to register? (Yes/No)"<<endl;
           	string choice;
          	cin>>choice;
           	if(choice=="yes"||choice=="Yes"||choice=="YES")
           	{
           		registration();
			}
			else
				return;
		}
		loginfile.close();
	}
	else
       cout<<"Unable to open file"<<endl;
	
	
   	string line;	
    // Email found
    if(flag==1) 
	{
        string p;
        maskPassword(p);
        bool found=false;
        ifstream loginfile("login.txt");           // Open file again
        if(loginfile.is_open()) 
		{
            while(getline(loginfile, line)) 
			{
                stringstream ss(line);
                string token;
                if(ss>>token) 
				{ 
					// Extract user_id
                    if(user_id==stoi(token)) 
					{ 
						// Check if user_id matches
                        if(ss>>token) 
						{ 	
							// Extract username
                            if(ss>>token) 
							{ 	
								// Extract email
                                if(ss>>token) 
								{ 	
									// Extract password
                                    if(p==token) 
									{ 
										// Check if password matches
                                        found=true;
                                        break;
                                    } 
									else 
									{
                                        cout<<"Password doesn't match!"<<endl;
                                        wrongp=true;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            loginfile.close();
        } 
		else 
            cout<<"Unable to open file"<<endl;

        if(found) 
        {
        	cout<<"LOGIN SUCCESSFUL"<<endl;
        	wrongp=false;
		}
            
            
        else 
            cout<<"Unable to login. Please try again."<<endl;

    }
}
int User::logout()
{
	int ch;
	cout<<"Are you sure?";
	cout<<"\n1. Yes\t2. No"<<endl;
	cin>>ch;
	if(ch==1)
	{			
		cout<<"LOGOUT SUCCESSFUL"<<endl;
		return 1;
	}
	else
		return 0;
}


class Budget
{
	protected:
		string budget_catname[10],start_date,end_date;
		float total_budgetamt,catbudget[10];
	public:
		void set_bamt();
		void view_bsummary();
		//float get_total_budgetamt();
		friend class Balance;		
};

void Budget::set_bamt()
{
	cout<<"Enter total budget amount:";
	cin>>total_budgetamt;
	tba=total_budgetamt;
	cout<<endl<<"Enter the start date of budget: ";
	cin>>start_date;
	cout<<"Enter the end date of budget: ";
	cin>>end_date;
	cout<<endl<<"Categories:"<<endl;
	cout<<"1.Food\n2.Stationery\n3.Daily_Uses\n4.Clothes\n5.Savings\n6.Others\n";
	budget_catname[1]="Food";
	budget_catname[2]="Stationery";
	budget_catname[3]="Daily_Uses";
	budget_catname[4]="Clothes";
	budget_catname[5]="Savings";
	budget_catname[6]="Others";
	cout<<endl<<"Enter budget for each category:"<<endl<<endl;
	for(int i=1;i<7;i++)
	{
		cout<<budget_catname[i]<<" : \t";
		cin>>catbudget[i];
		temp[i-1]=catbudget[i];
		
	}
	float t=0;
	for(int i=1;i<7;i++)
	{
		t=t+catbudget[i];
	}
	
	if(t<total_budgetamt)
			catbudget[5]+=(total_budgetamt-t);
	else if(t>total_budgetamt)
			cout<<"WARNING:Sum of budgets for categories exceed total budget amount!!!!!"<<endl;
			
}

void Budget::view_bsummary()
{
	cout<<endl<<"\nTotal budget amount: "<<total_budgetamt<<endl<<endl;
	cout<<"Start Date:"<<start_date<<endl;
	cout<<"End Date:"<<end_date<<endl;
	cout<<endl<<"\n---------BUDGET SUMMARY---------"<<endl;
	cout<<setw(10)<<"CATEGORY"<<setw(20)<<"BUDGET"<<endl;
	cout<<"------------------------------------"<<endl;
	for(int i=1;i<7;i++)
	{
		cout<<setw(10)<<budget_catname[i]<<setw(20)<<catbudget[i]<<endl;
	}
}

//void Budget::track_bprog();
class UserBudget:public User, public Budget
{
	protected:
		int id;
		string name;
	public:
		void display();
};

void UserBudget::display()
{
	id=getUserId();
	name=getUsername();

    cout<<endl<<"-----------USER DETAILS-----------"<<endl;
    cout << "ID: " << id << setw(20) << "Username: " << name << endl << endl;
    cout<<endl<<"-----------BUDGET DETAILS-----------"<<endl;
    cout << "Start date: " << start_date << setw(20) << "End date: " << end_date << endl;
    cout << "Total Budget Amount: " << total_budgetamt << endl << endl;
    cout << setw(10) << "CATEGORY" << setw(20) << "BUDGET" << endl;
    cout << "------------------------------------" << endl;
    for(int i=1;i<7;i++)
    {
        cout<<setw(10)<<budget_catname[i]<<setw(20)<<catbudget[i]<<endl;
    }
}
class Transaction:public UserBudget
{
	protected:
		int tr_id;
		float tr_amt;
		string tr_date,expense_cat;
		
	public:
		void add_transaction(int user_id);
		//void edit_transaction();
		void delete_transaction(int user_id);
		friend class Balance;
};


void Transaction::add_transaction(int user_id)
{
	h=0;
	string filename="transactions_" + to_string(user_id) + ".txt";
	ofstream file(filename,ios::app);
	string choice;
	cout<<"Enter the date of transaction:";
	cin>>tr_date;
	file<<tr_date<<endl;
	do
	{
		tr_id=++h;
		cout<<"Enter the category of expense:";
		cin.ignore();								//clears anything previously present in the buffer
		getline(cin,expense_cat);	
		cout<<"Enter the transaction amount:";
		cin>>tr_amt;
		file<<tr_id<<"\t"<<expense_cat<<"\t"<<tr_amt<<endl;
		cout<<"Add another Transaction for this date?"<<endl<<"(Yes/No)"<<endl;
		cin>>choice;
	}
	while(choice=="Yes"||choice=="yes"||choice=="YES");
	file.close();
}

void Transaction::delete_transaction(int user_id) 
{
	
	//Display all the transactions of that user from the corresponding file
	string filename= "transactions_" + to_string(user_id) + ".txt";
	// Open the file
    ifstream file(filename);
    
    // Check if the file is open
    if(!file.is_open()) 
	{
        cout<<"Unable to open file!"<<endl;
        return;
    }
    cout<<"\n\n-----------YOUR TRANSACTIONS-----------\n";
    // Read and display each line of the file
    string line;
    while(getline(file, line)) 
	{
        cout<<line<<endl; 	// Output the line to the console
    }
    // Close the file
    file.close();
	
	cout<<endl<< "------------------------------------"<<endl;
    string del_date, transaction;
    cout<<endl<<endl<< "Enter the date of transaction to be deleted: ";
    cin>>del_date;

    cout<<"Enter the transaction to be deleted: ";
    cout<<endl<<"(Press tab between id,category and amount)"<<endl;
    cin.ignore(); // Ignore any leftover newline character in the input buffer
    getline(cin, transaction);
	
    ifstream infile(filename);
    if(!infile) 
	{
        cout<<"Error: Unable to open file"<<endl;
        return;
    }

    ofstream outfile("temp.txt");
    if(!outfile) 
	{
        cout<<"Error: Unable to create temporary file"<<endl;
        infile.close();
        return;
    }

    //string line;
    bool dateFound=false;
    bool transactionFound=false;

    while(getline(infile, line)) 
	{
        if(line.find(del_date)!=string::npos) //find return npos (invalid) when anything is not found in file
		{
            dateFound=true;
            outfile<<line<<endl; // Write date line
            while(getline(infile,line) && !line.empty() && line.find_first_not_of(' ') != string::npos) 
            												//finds first non-space character from the line and checks if it is not at an invalid(npos) position
			{
                if(line.find(transaction)!= string::npos) 
				{
                    transactionFound=true;
                } 
				else 
				{
                    outfile<<line<<endl; // Write transaction if not to be deleted
                }
            }
        } 
		else
            outfile<<line<<endl; // Write non-date line
    }

    infile.close();
    outfile.close();

    if(!dateFound) 
	{
        cout<<"Error: Date not found in file"<<endl;
        remove("temp.txt");
        return;
    }

    if(!transactionFound) 
	{
        cout<<"Error: Transaction not found"<<endl;
        remove("temp.txt");
        return;
    }

    filename="transactions_" + to_string(user_id) + ".txt";
    if(remove(filename.c_str()) != 0) 		//converting filename into c-style string, remove returns 0 if file is removed
	{
        cout<<"Error: Unable to remove original file"<<endl;
        return;
    }

    if(rename("temp.txt",filename.c_str())!=0) //rename also returns 0 if file is renamed
	{
        cout<<"Error: Unable to rename temporary file"<<endl;
        return;
    }

    cout<<"Transaction deleted successfully"<<endl;
}

class Balance
{
	protected:
		float total_bal;
	public:
		void calc_totalbal(UserBudget B, Transaction T,int user_id); 	//B, T are passed because Balance is friend to UserBudget & Transaction
																		//user_id is passed because of multi-user
		void cat_bal(UserBudget B,Transaction T,int user_id);
};
float temp[6] = {0};	//Initialized with 0, to avoid undesired values initially 

void Balance::calc_totalbal(UserBudget B,Transaction T,int user_id)
{
	string filename = "transactions_" + to_string(user_id) + ".txt";
	ifstream file(filename);
    string line;
    float totalAmount = 0; 		//total expense amount of a particular user

    if(file.is_open())
	{
        while(getline(file, line)) 
		{
            istringstream iss(line);		//creates an input string stream from 'line' to extract data(date,category,amount)
            string date, category;
            float amount;

            if(iss>>date>>category>>amount) 
			{
                totalAmount+=amount;
            }
        }
        file.close();
        cout<<"Total transaction amount: "<<totalAmount<<endl;
    } 
	else 
	{
        cout<<"Unable to open file."<<endl;
    }
	
	cout<<"Total Budget Amount: "<<tba<<endl<<endl;
	total_bal=tba-totalAmount;
	cout<<"-----------BALANCE------------\n";
	
	cout<<"\nTotal remaining balance is "<<total_bal<<endl;
	cout<<"------------------------------\n\n";
		
}

void Balance::cat_bal(UserBudget B,Transaction T,int user_id)
{
	const int NUM_CATEGORIES =6;
	string filename = "transactions_" + to_string(user_id) + ".txt";
	ifstream file(filename); // Open the file
    string line;
    float categorySums[NUM_CATEGORIES] = {0}; // Array to store sums for each category

    if(file.is_open()) 
	{
        while(getline(file, line)) 
		{
            istringstream iss(line);
            string date, category;
            float amount;

            // Extract date, category, and amount
            getline(iss, date, '\t');
            getline(iss, category, '\t');
            iss>>amount;

            // Determine the index of the category in the array
            int index;
            if(category=="Food") 
                index=0;
            else if(category=="Stationery") 
                index=1;
            else if(category=="Daily_Uses") 
                index=2;
            else if(category=="Clothes") 
                index=3;
            else if(category=="Savings")
                index=4;
            else if(category=="Others")
                index=5;
            else
                continue;

            
            categorySums[index] += amount;					// Sum the amounts for each category
        }
        file.close(); // Close the file

        // Print the total transaction amount for each category
        cout<<setw(10)<<"CATEGORY"<<setw(20)<<"AMOUNT"<<endl;
		cout<<"-----------------------------------------------------\n";
		string budget_catname[NUM_CATEGORIES] = {"Food", "Stationery", "Daily_Uses", "Clothes", "Savings", "Others"};
        for(int i=0;i< NUM_CATEGORIES;++i) 
            cout<<setw(10)<<budget_catname[i]<<setw(20)<<(temp[i]-categorySums[i])<<endl;
          
		for(int i=0;i<NUM_CATEGORIES;++i)
		{	
			if(categorySums[i]>temp[i])
			{
				cout<<endl<<"WARNING : Transaction amount for "<<budget_catname[i]<<" exceeds its budget!!!!"<<endl;
			}
		}  
    }
	else 
        cout<<"Unable to open file."<<endl;
}

class Report : public Transaction
{
	protected:
		int report_id;
	public:
		void generate_report();
		void view_report();	
};

int main()
{
	Transaction T;
	Balance A;
	UserBudget B; 
	cout<<"--------WELCOME TO BUDGET BUDDY--------\n"<<endl;
	do
	{
		cout<<endl<<"---------------------------------------"<<endl;
		cout<<"1. Register\t2.Login\t\t3.Exit"<<endl;
		int ch,ch2,ch3,flag;
		cin>>ch;
		switch(ch)
		{
			case 1:
				T.registration();
				T.login();
				if(wrongp!=true) 		//if password is correct
				{
					cout<<endl<<"1.Create Budget\t2.Logout"<<endl;
					cin>>ch2;
					switch(ch2)
					{
						case 1:
							T.set_bamt();
							do
							{
								cout<<endl<<"-----------OPTIONS-----------"<<endl;
								cout<<"1.View Budget Summary\n2.Add a transaction\n3.Delete transaction\n4.Check total balance\n5.Check category balance\n6.Logout\n7.Exit\n";
								cout<<"---------------------------------------"<<endl;
								cin>>ch3;
							
								switch(ch3)
								{
									case 1:
										T.display();
										break;
									case 2:
										T.add_transaction(T.getUserId());
										break;
									case 3:
										T.delete_transaction(T.getUserId());
										break;
									case 4:
										A.calc_totalbal(B,T,T.getUserId());
										break;
									case 5:
										A.cat_bal(B,T,T.getUserId());
										break;
									case 6:
										flag=T.logout();				//logout returns 1 if logout is successful
										if(flag==1)
										{
											cout<<endl<<"-----------THANK YOU!-----------"<<endl;
											exit(0);
										}
										else
											break;
									case 7:
										exit(0);
									default:
										cout<<"Invalid input"<<endl;		
								}
							}
							while(1);
							break;
						case 2:
							flag=T.logout();
							if(flag==1)
							{
								cout<<endl<<"-----------THANK YOU!-----------"<<endl;
								exit(0);
							}
							else
							{
								do
								{
									cout<<endl<<"-----------OPTIONS-----------"<<endl;
									cout<<"1.View Budget Summary\n2.Add a transaction\n3.Delete transaction\n4.Check total balance\n5.Check category balance\n6.Logout\n7.Exit\n";
									cout<<"---------------------------------------"<<endl;
									cin>>ch3;
								
									switch(ch3)
									{
										case 1:
											T.display();
											break;
										case 2:
											T.add_transaction(T.getUserId());
											break;
										case 3:
											T.delete_transaction(T.getUserId());
											break;
										case 4:
											A.calc_totalbal(B,T,T.getUserId());
											break;
										case 5:
											A.cat_bal(B,T,T.getUserId());
											break;
										case 6:
											flag=T.logout();
											if(flag==1)
											{
												cout<<endl<<"-----------THANK YOU!-----------"<<endl;
												exit(0);
											}
											else
												break;
										case 7:
											exit(0);
										default:
											cout<<"Invalid input"<<endl;		
									}
								}
								while(1);
							}
						default:
							cout<<"Invalid input"<<endl;
					}
				}
				break;
			case 2:
				T.login();
				if(wrongp!=true) 		//if password is correct
				{	
					/*cout<<endl<<"1.Create Budget\t2.Logout"<<endl;
					cin>>ch2;
					switch(ch2)
					{
						case 1:
							T.set_bamt();
						*/
							do
							{
								cout<<endl<<"-----------OPTIONS-----------"<<endl;
								cout<<"1.Create Budget \n2.View Budget Summary\n3.Add a transaction\n4.Delete transaction\n5.Check total balance\n6.Check category balance\n7.Logout\n8.Exit\n";
								cout<<"---------------------------------------"<<endl;
								cin>>ch3;
							
								switch(ch3)
								{
									case 1:
										T.set_bamt();
										break;
									case 2:
										T.display();
										break;
									case 3:
										T.add_transaction(T.getUserId());
										flag=1;
										break;
									case 4:
										/*if(flag==0)
											cout<<"No Transaction added!"<<endl;
										else*/
											T.delete_transaction(T.getUserId());
										break;
									case 5:
										A.calc_totalbal(B,T,T.getUserId());
										break;
									case 6:
										A.cat_bal(B,T,T.getUserId());
										break;
									case 7:
										flag=T.logout(); //logout returns 1 if logout successful
										if(flag==1)
										{
											cout<<endl<<"-----------THANK YOU!-----------"<<endl;
											exit(0);
										}
										else
											break;
									
									case 8:
										exit(0);
									default:
										cout<<"Invalid input"<<endl;		
								}
							}
							while(1);
				}
				break;
			case 3:
				exit(0);
			default:
				cout<<"Invalid input"<<endl;
		}
	}
		while(1);
	
}