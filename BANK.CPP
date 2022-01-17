#include<fstream.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<ctype.h>
class account
{
private:
long acno;
char name[50],fname[50],mname[50],bdate[15],odate[15],ddate[15],wdate[15],address[100];
char type,atm,check;
public:
long amnt;
int add_accnt();
void withdraw();
void deposit();
void balance();
void disp_all();
void display();
void close_acnt();
void modify();
void trans();
long racno();
}B;

int account::add_accnt()				//add_accnt
{
clrscr();
account a;
ifstream fin("bank.txt",ios::app|ios::binary);
cout<<"\n\n Enter The account No.: ";
	cin>>acno;
	while(fin.read((char*)&a,sizeof(a)))
	{	if(acno==a.racno())
		{
			cout<<"\n An Account already exist with the same no.!!";
			getch();
			return 0;
		}
	}
cout<<"\n Enter The Name of The account Holder: ";
	gets(name);
cout<<"\n Enter Father's Name: ";
	gets(fname);
cout<<"\n Enter Mother's Name: ";
	gets(mname);
cout<<"\n Enter Birth Date (dd-mm-yyyy): ";
	gets(bdate);
cout<<"\n Enter Address: ";
	gets(address);
cout<<"\n Enter Type of The account (C/S): ";
	cin>>type;
	type=toupper(type);
cout<<"\n Enter The Initial amount \n (500 or more for saving and 1000 or more for current): ";
	cin>>amnt;
cout<<"\n Enter The date on which account is Opened: ";
	gets(odate);
strcpy(ddate,odate);
strcpy(wdate,"---");
cout<<"\n Do You Want to Make ATM Card: ";
	cin>>atm;
	atm=toupper(atm);
cout<<"\n Do You Want a check book: ";
	cin>>check;
	check=toupper(check);
fin.close();
return 1;
}


void account::deposit()                             	//deposit
{
clrscr();
int count=0;
long tamnt,tacno;
account a;
ifstream fin("bank.txt",ios::app|ios::binary);
ofstream fout("temp.txt",ios::app|ios::binary);
cout<<"\n\n Enter account no. in which you want to deposit: ";
	cin>>tacno;
	while(fin.read((char*)&a,sizeof(a)))
	{
		if(tacno==a.racno())
		{
			count=1;
			cout<<"\n Enter the amount you want to deposit: ";
				cin>>tamnt;
			a.amnt+=tamnt;
			cout<<"\n Enter the Date of Deposit (dd-mm-yyyy): ";
				gets(a.ddate);
			cout<<"\n\n\n\t\t\t\t Amount deposited \n ";
		}
		fout.write((char*)&a,sizeof(a));
	}
	if(count==0)
		cout<<"\n Enter correct account no. \n ";
getch();
fin.close();
fout.close();
remove("bank.txt");
rename("temp.txt","bank.txt");
}


void account::withdraw()                               	//withdraw
{
clrscr();
int count=0;
long tamnt,tacno;
account a;
ifstream fin("bank.txt",ios::app|ios::binary);
ofstream fout("temp.txt",ios::app|ios::binary);
cout<<"\n\n Enter account no. from which you want to withdraw: ";
	cin>>tacno;
	while(fin.read((char*)&a,sizeof(a)))
	{
		if(tacno==a.racno())
		{
			count=1;
			cout<<"\n Enter the amount you want to withdraw: ";
				cin>>tamnt;
			if(tamnt<a.amnt)
			{
				a.amnt-=tamnt;
				cout<<"\n Enter the Date of Withdraw (dd-mm-yyyy): ";
					gets(a.wdate);
				cout<<"\n\n\n\t\t\t\t Amount withdrawn \n ";
			}
			else
				cout<<"\n Not enough amount in your account \n ";
		}
		fout.write((char*)&a,sizeof(a));
	}
	if(count==0)
		cout<<"\n Enter correct account no. \n ";
getch();
fin.close();
fout.close();
remove("bank.txt");
rename("temp.txt","bank.txt");
}


void account::balance()       			    	//balance
{
clrscr();
int count=0;
long tacno;
account a;
ifstream fin("bank.txt",ios::app|ios::binary);
cout<<"\n Enter account no.: ";
	cin>>tacno;
	while(fin.read((char*)&a,sizeof(a)))
	{
		if(tacno==a.racno())
		{
			count=1;
			a.display();
		}
	}
	if(count==0)
		cout<<"\n Enter correct account no. \n ";
fin.close();
getch();
}


void account::disp_all()                     	       	//disp_all
{
clrscr();
account a;
ifstream fin("bank.txt",ios::app|ios::binary);
	while(fin.read((char*)&a,sizeof(a)))
	{
		a.display();
		getch();
	}
cout<<"\n\n\t\t\t\t No more accounts \n ";
getch();
fin.close();
}


void account::display()                                	//display
{
clrscr();
cout<<"\n\n The information about account is: \n\n";
	cout<<"\n Account no.  : "<<acno;
	cout<<"\n Name         : ";puts(name);
	cout<<" Father's Name: ";puts(fname);
	cout<<" Mother's Name: ";puts(mname);
	cout<<" Date Of Birth: ";puts(bdate);
	cout<<" Address      : ";puts(address);
	cout<<" Account Type : "<<type;
	cout<<"\n Ammount      : "<<amnt;
	cout<<"\n Opening Date : ";puts(odate);
	cout<<" Last Deposit : ";puts(ddate);
	cout<<" Last Withdraw: ";puts(wdate);
	cout<<" ATM Card     : "<<atm;
cout<<"\n\n\n Press any key to continue.... \n ";
}


void account::close_acnt()      		       	//close_acnt
{
clrscr();
char ch;
int count=0;
long tacno;
account a;
ifstream fin("bank.txt",ios::app|ios::binary);
ofstream fout("temp.txt",ios::app|ios::binary);
cout<<"\n Enter the account no that you want to close: ";
	cin>>tacno;
	while(fin.read((char*)&a,sizeof(a)))
	{
		if(tacno==a.racno())
		{
			count=1;
			a.display();
			getch();
			cout<<"\n Are you sure you want to close this account: ";
				cin>>ch;
			cout<<" ";
			if(ch=='N'||ch=='n')
				fout.write((char*)&a,sizeof(a));
			else
				cout<<"\n\t\t\t\t Account closed \n ";
		}
		else
			fout.write((char*)&a,sizeof(a));
	}
	if(count==0)
		cout<<"\n Enter correct choice \n ";
getch();
fin.close();
fout.close();
remove("bank.txt");
rename("temp.txt","bank.txt");
}


void account::modify()    				//modify
{
clrscr();
char ans;
int count=0;
long tacno;
account a,h1;
ifstream fin("bank.txt",ios::app|ios::binary);
ofstream fout("temp.txt",ios::app|ios::binary);
cout<<"\n\n Enter account no. that you want to modify: ";
	cin>>tacno;
	while(fin.read((char*)&a,sizeof(a)))
	{
		if(a.racno()==tacno)
		{
			count=1;
			clrscr();
			a.display();
			getch();
			clrscr();
			h1.acno=a.acno;
			cout<<"\n\n Enter New Details....\n ";
			cout<<"\n Enter The Name of The account Holder: ";
				gets(h1.name);
			cout<<"\n Enter Father's Name: ";
				gets(h1.fname);
			cout<<"\n Enter Mother's Name: ";
				gets(h1.mname);
			cout<<"\n Enter Birth Date (dd-mm-yyyy): ";
				gets(h1.bdate);
			cout<<"\n Enter Address: ";
				gets(h1.address);
			cout<<"\n Enter Type of The account (C/S): ";
				cin>>h1.type;
				h1.type=toupper(h1.type);
			cout<<"\n Do You Want to Edit Amount: ";
				cin>>ans;
			if(ans=='y'||ans=='Y')
			{
				cout<<"\n Enter The Initial amount \n (500 or more for saving and 1000 or more for current): ";
					cin>>h1.amnt;
			}
			else
				h1.amnt=a.amnt;
			cout<<"\n Enter The date on which account is Opened: ";
				gets(h1.odate);
			strcpy(h1.ddate,h1.odate);
			strcpy(h1.wdate,"---");
			cout<<"\n Do You Want to Make ATM Card: ";
				cin>>h1.atm;
				h1.atm=toupper(h1.atm);
			cout<<"\n Do You Want a check book: ";
				cin>>h1.check;
				h1.check=toupper(h1.check);
			fout.write((char*)&h1,sizeof(h1));
			cout<<"\n\t\t\t\t Account Modified \n ";
			getch();

		}
		else
			fout.write((char*)&a,sizeof(a));
	}
	if(count==0)
	{
		cout<<"\n Sorry!! Account Not Found!!";
		getch();
	}
fin.close();
fout.close();
remove("bank.txt");
rename("temp.txt","bank.txt");
}


void account::trans()
{
clrscr();
int count1=0,count2=0;
long tacno1,tacno2;
long tamnt;
account a1,a2;
ifstream fin("bank.txt",ios::app|ios::binary);
ofstream fout("temp.txt",ios::app|ios::binary);
cout<<"\n\n Enter The No. of Account From Which You Want to Transfer Money: ";
	cin>>tacno1;
cout<<"\n Enter The No. of Account to Which You Want to Transfer Money: ";
	cin>>tacno2;
	while(fin.read((char*)&a1,sizeof(a1)))
	{
		if(a1.racno()==tacno1)
			count1=1;
		if(a2.racno()==tacno2)
			count2=1;
	}
	if(count1==0||count2==0)
		cout<<"\n One or Both The Accounts Are Not Found!!\n\n Enter Correct Account No. \n ";
	else
	{
		fin.seekg(0);
		cout<<fin.tellg();
		while(fin.read((char*)&a1,sizeof(a1)))
		{
			if(a1.racno()==tacno1||a2.racno()==tacno2)
			{
				while(fin.read((char*)&a2,sizeof(a2)))
				{
					if(a2.racno()==tacno2)
					{
						cout<<"\n Enter The Amount: ";
							cin>>tamnt;
						if(a1.amnt>=tamnt)
						{
							a1.amnt-=tamnt;
							a2.amnt+=tamnt;
							cout<<"\n Amount Transfered \n ";
						}
						else
							cout<<"\n Not Enough Amount \n ";
					}
					fout.write((char*)&a1,sizeof(a1));
					fout.write((char*)&a2,sizeof(a2));
				}
			}
			else
				fout.write((char*)&a1,sizeof(a1));
		}
	}
fin.close();
fout.close();
remove("bank.txt");
rename("temp.txt","bank.txt");
getch();
}


long account::racno()                                  	//racno
{ return acno; }                                        //Functions of class over



void add()						//Function to add a new accnt
{
account a;
ofstream fout("bank.txt",ios::app|ios::binary);
if(a.add_accnt()==1)
	fout.write((char*)&a,sizeof(a));
cout<<"\n\t\t\t\t Account Created ";
getch();
fout.close();
}


void main()       					//main
{
clrscr();
char ch='1';
	while(ch!='9')
	{
		clrscr();
		cout<<"\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. TRANSFER";
		cout<<"\n\n\t09. EXIT";
		cout<<"\n\n\n\tSelect Your Option \n\t";
		cin>>ch;
		switch(ch)
		{
			case'1':
				add();
				break;
			case'2':
				B.deposit();
				break;
			case'3':
				B.withdraw();
				break;
			case'4':
				B.balance();
				break;
			case'5':
				B.disp_all();
				break;
			case'6':
				B.close_acnt();
				break;
			case'7':
				B.modify();
				break;
			case'8':
				B.trans();
				break;
			case'9':
				exit(0);
				break;
			default:
				cout<<"\n Enter correct choice \n";
				getch();
		}
	}
}