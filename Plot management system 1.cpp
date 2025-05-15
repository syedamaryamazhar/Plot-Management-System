#include <iostream>
#include<vector>
#include<string>
#include <fstream>
#include <sstream>

using namespace std;


int AdminLogin();
void Adminpanel(vector<vector<string>> &plots);
void Userpanel(const vector<vector<string>> &plots);
void Booking(vector<vector<string>> &plots);
void PlotStatus(const vector<vector<string>> &plots);
void Editing(vector<vector<string>> &plots);
void Fullpayment(vector<vector<string>> &plots, int plotnum);
void Installments(vector<vector<string>> &plots, int plotnum);
void loadFile(vector<vector<string>> &plots, const string &file);
void saveFile(const vector<vector<string>> &plots, const string &file);



int main()
{
	
	string file = "plotdata.txt";
	vector<vector<string>> plots(100, vector<string>(9, "Available"));
	loadFile(plots, file);
	
	int adminORuser;
	while(true)
	{
		cout<<"WELCOME! \n1. Press 1 for Admin \n2. Press 2 for User \n3. Press 0 to Exit\n";
		cin>>adminORuser;
		
		if(adminORuser ==1){
			Adminpanel(plots);
		}
		else if(adminORuser == 2){
			Userpanel(plots);
		}
		else if(adminORuser == 0){
			cout<<"Goodbye!";
			saveFile(plots, file);
			break;
		}
	}
}
//function for admin login
int AdminLogin()
{
	string password = "bscs1";
	string admpass;
	cout<<"Enter password: ";
	cin>>admpass;
	if(admpass == password){
		return 1;
	}
	else{
		return 0;
	}
}

//function for admin panel
void Adminpanel(vector<vector<string>> &plots)
{
	int admin;
	if(AdminLogin() == 1){
		cout<<"Logged in successfully!";
		cout<<"\nPress 1 for Booking \nPress 2 for Plot Status \nPress 3 for Editing\n";
		cin>>admin;
		
		if(admin==1){
			Booking(plots);
		}
		else if(admin==2){
			PlotStatus(plots);
		}
		else if(admin==3){
			Editing(plots);
		}
	}
	else{
		cout<<"Wrong Password\n";
	}
}

//funcion for user panel
void Userpanel(const vector<vector<string>> &plots)
{
	PlotStatus(plots);
}

//function for booking plot
void Booking(vector<vector<string>> &plots)
{
	int plotnum;
	cout<<"Enter plotnum for booking: ";
	cin>>plotnum;
	
	if(plotnum>=0 && plotnum<100){
		if(plots[plotnum][0]=="Available"){
			for(int i=0; i<9; i++){
				plots[plotnum][i]="empty";
			}
			
			cout<<"Enter the owner's name: ";
			cin>>plots[plotnum][1];
			
			cout<<"Enter mobile number: ";
			cin>>plots[plotnum][2];
			
			cout<<"Enter payment method: \n1. Press 1 for Full Payment \n2. Press 2 for Installments\n";   
			int paymenttype;
			cin>>paymenttype;
			
			if(paymenttype==1){
				plots[plotnum][3]="Full payment";
				Fullpayment(plots, plotnum);
				plots[plotnum][0]="Booked";
				cout<<"Plot number "<<plotnum<<" booked!\n";
			}
			else if(paymenttype==2){
				plots[plotnum][3]="Installments";
				Installments(plots, plotnum);
				plots[plotnum][0]="Booked";
				cout<<"Plot number "<<plotnum<<" booked!\n";
			}
			else{
				cout<<"Enter correct number";
				plots[plotnum][0]=="Available";
			}
		
		}
		else{
			cout<<"Plot is already booked.\n";		
		}
	}
	else{
		cout<<"Invalid plot number. Please enter a number between 0 to 99\n";
	}
}
// function for full payment	
void Fullpayment(vector<vector<string>> &plots,int plotnum)
{
	string pay;
	cout<<"Enter 1 if the payment is paid and 0 if not paid\n";
	cin>>pay;
	
	if(pay=="1"){
		plots[plotnum][4]="Payment Status: Paid";
	}
	else if (pay=="0"){
		plots[plotnum][4]="Payment Status: Not Paid";
	}
	else{
		cout<<"Please enter correct  number.";
	}
}

//function for installments
void Installments(vector<vector<string>> &plots,int plotnum)
{
	int plan;
	cout<<"Select the Installment Plan: \n1. Press 1 for 2 installment plan \n2. Press 2 for 3 installment plan\n";
	cin>>plan;
	
	if(plan==1){
		plots[plotnum][5]="2 Installment Plan";
		cout<<"Press 1 if first installment is paid and 0 if not paid "; int first;
		cin>>first;
		
		if(first==0){
			plots[plotnum][6]="First Installment: NOT Paid";
			plots[plotnum][7]="Second Installment: NOT Paid";
		}
		else if(first==1){
			plots[plotnum][6]="First Installment: Paid";
			cout<<"Press 1 if second installment is paid and 0 if not paid "; int second;
			cin>>second;
			
			if(second==1){
				plots[plotnum][7]="Second Installment: Paid";
			}
			else if(second==0){
				plots[plotnum][7]="Second Installment: NOT Paid";
			}
		}
	}
	else if(plan== 2){
		plots[plotnum][5]="3 Installment Plan";
		cout<<"Press 1 if first installment is paid and 0 if not paid "; int first;
		cin>>first;
		
		if(first==0){
			plots[plotnum][6]="First Installment: NOT Paid";
			plots[plotnum][7]="Second Installment: NOT Paid";
			plots[plotnum][8]="Third Installment: NOT Paid";
		}
		else if(first==1){
			plots[plotnum][6]="First Installment: Paid";
			cout<<"Press 1 if second installment is paid and 0 if not paid ";  int second;
			cin>>second;
			
			if(second==0){
				plots[plotnum][7]="Second Installment: NOT Paid";
				plots[plotnum][8]="Third Installment: NOT Paid";
			}
			else if(second==1){
				plots[plotnum][7]="Second Installment: Paid";
				cout<<"Press 1 if third installment is paid and 0 if not paid ";  int third;
				cin>>third;
				
				if(third==1){
					plots[plotnum][8]="Third Installment: Paid";
				}
				else if(third ==0){
					plots[plotnum][8]="Third Installment: NOT Paid";
				}
			}
			
		}
	}
}
	
//funtion for plot status
void PlotStatus(const vector<vector<string>> &plots)
{
	int plotnum;
	cout<<"Enter plot number for details (0-99)";
	cin>>plotnum;
	
	if(plots[plotnum][0]=="Booked"){
		cout<<"Plot number "<<plotnum<<" details:\n";
		for(int i=0; i<9; i++){
			if(i==0){
				cout<<"Plot Status: "<<plots[plotnum][i]<<endl;
			}
			else if(i==1){
				cout<<"Owner's name: "<<plots[plotnum][i]<<endl;
			}
			else if(i==2){
				cout<<"Mobile number: "<<plots[plotnum][i]<<endl;
			}
			else if(i==3){
				cout<<"Payment type: "<<plots[plotnum][i]<<endl;
			}
			else if(i==4){
				if(plots[plotnum][i]=="empty"){
					if(plots[plotnum][8]=="Third Installment: NOT Paid"){
						plots[plotnum][4] =="Payment Status: NOT Paid";
						cout<<plots[plotnum][4]<<endl;
					}
					else if(plots[plotnum][8]=="Third Installment: Paid"){
						plots[plotnum][4] =="Payment Status: Paid";
						cout<<plots[plotnum][4]<<endl;
					}
					else{
						cout<<plots[plotnum][4]<<endl;
					}
				}
				else if(plots[plotnum][i]!="empty"){
					if(plots[plotnum][8]=="Third Installment: NOT Paid"){
						plots[plotnum][4] =="Payment Status: NOT Paid";
						cout<<plots[plotnum][4]<<endl;
					}
					else if(plots[plotnum][8]=="Third Installment: Paid"){
						plots[plotnum][4] =="Payment Status: Paid";
						cout<<plots[plotnum][4]<<endl;
					}
					else{
						cout<<plots[plotnum][i]<<endl;
					}
				}
                            
			}
			else if(i==5){
				if(plots[plotnum][i]=="empty"){
					cout<<" ";
				}
				else {
					cout<<plots[plotnum][i]<<endl;
				}
			}
			else if(i==6){
				if(plots[plotnum][i]=="empty"){
					cout<<" ";
				}
				else {
					cout<<"Payment status: "<<plots[plotnum][i]<<endl;
				}
			}
			else if(i==7){
				if(plots[plotnum][i]=="empty"){
					cout<<" ";
				}
				else {
					cout<<"Payment status: "<<plots[plotnum][i]<<endl;
				}
			}
			else if(i==8){
				if(plots[plotnum][i]=="empty"){
					cout<<" ";
				}
				else {
					cout<<"Payment status: "<<plots[plotnum][i]<<endl;
				}
			}
		}
	}
	else{
		cout<<"Plot is not booked.\n";
	}
}

//function for editing
void Editing(vector<vector<string>> &plots)
{
	
	int plotnum;
	string status, change;
	cout<<"Enter plot number for editing (0-99): ";
	cin>>plotnum;
	
	if(plotnum>=0 && plotnum<100){
		if(plots[plotnum][0]=="Booked"){
			cout<<"What do you want to change: \n1. Press 1 for Name \n2. Press 2 for Mobile number \n3. Press 3 for Payment status \n4. Press 4 for First Installment plan \n5. Press 5 for Second Installment plan \n6. Press 6 for Third Installment Plan \n";
			cin>>change;
			
			if(change=="1"){
				cout<<"Enter new name: ";
				cin>>plots[plotnum][1];
			}
			else if(change =="2"){
				cout<<"Enter new mobile number: ";
				cin>>plots[plotnum][2];
			}
			else if(change =="3"){
				cout<<"Type payment status: Paid or Not Paid\n";
				cin>>status;
				if(status == "Paid"){
					plots[plotnum][4]="Payment Status: Paid";
				}
				else if(status =="Not Paid"){
					plots[plotnum][4]="Payment Status: Not Paid";
				}
				else{
					cout<<"Incorrect Status!\n";
				}
			}
			else if(change =="4"){
				if(plots[plotnum][6]=="empty"){
					cout<<" ";
				}
				else{
					cout<<"Type First Installment Status: Paid or Not Paid\n";
				cin>>status;
					if(status == "Paid"){
						plots[plotnum][6]="First Installment: Paid";
					}
					else if(status =="Not Paid"){
						plots[plotnum][6]="First Installment: Not Paid";
					}
					else{
						cout<<"Incorrect Status!\n";
					}
				}
			}
			else if(change =="5"){
				if(plots[plotnum][7]=="empty"){
					cout<<" ";
				}
				else{
					cout<<"Type Second Installment Status: Paid or Not Paid\n";
				cin>>status;
					if(status == "Paid"){
						plots[plotnum][7]="Second Installment: Paid";
					}
					else if(status =="Not Paid"){
						plots[plotnum][7]="Second Installment: Not Paid";
					}
					else{
						cout<<"Incorrect Status!\n";
					}
				}
			}
			else if(change =="6"){
				if(plots[plotnum][8]=="empty"){
					cout<<" ";
				}
				else{
					cout<<"Type Third Installment Status: Paid or Not Paid\n";
				cin>>status;
					if(status == "Paid"){
						plots[plotnum][8]="Third Installment: Paid";
					}
					else if(status =="Not Paid"){
						plots[plotnum][8]="Third Installment: Not Paid";
					}
					else{
						cout<<"Incorrect Status!\n";
					}
				}
			}
			else{
				cout<<"invalid number";
			}
		}
		else{
			cout<<"This plot is not booked";
		}
	}
	else{
		cout<<"Invalid plot number. Please enter a plot number between 0 to 99\n";
	}
}

//function to save data in a file
void saveFile(const vector<vector<string>> &plots, const string &file) 
{
    ofstream out(file);

    if (out.is_open()) {

        for (int i = 0; i < plots.size(); i++) {
            for (int j = 0; j < plots[i].size(); j++) {
                out << plots[i][j] << ",";
            }
            out << "\n";
        }
        out.close();
        cout << "\nData saved to file successfully!\n";
    } else {
        cout << "File cannot be opened\n";
    }
}


//function to load data from file
void loadFile(vector<vector<string>> &plots, const string &file)
{
	ifstream in(file);
	
	
	if(in.is_open()){
		for(int i=0; i<plots.size(); i++){
			string line;
			getline(in, line);
			
			stringstream ss(line);         //making the whole line string
			string data;
			
			for(int j=0; j<plots[i].size(); j++){
				getline(ss, data, ',');
				plots[i][j] = data;
			}
		}
		in.close();
		cout<<"Data loaded from file successfully\n";
	}
	else{
		cout<<"File cannot be opened\n";
	}
}