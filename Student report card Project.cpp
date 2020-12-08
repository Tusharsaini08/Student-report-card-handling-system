#include<iostream>     //Header files used in the Project.
#include<fstream>
#include<iomanip>
#include<stdio.h>

using namespace std;

class student     //Class starts here.
{
    private:
        int rollno;
        int Class;
        char name[50];
        int s_marks, ss_marks, m_marks, e_marks, h_marks;
        double per;
        char grade;
        void calculate();     //Function to calculate grade.
    public:
	    void getdata();     //Function to accept data from user.
        void showdata() const;     //Function to show data on screen.
	    void show_tabular() const;     //Function to show data in tabular form.
	    int retrollno() const;
	    int retClass() const;
};     //class ends here.

void student::calculate()     //Function definition for calculating student grade.
{
	per=(s_marks+ss_marks+m_marks+e_marks+h_marks)/5.0;     //For calculating the Percentage.
	if(per>=90)
		{
		    grade='A';
		}
	else if(per>=80)
		{
		    grade='B';
		}
	else if(per>=70)
		{
		    grade='C';
		}
	else
		{
		    grade='D';
		}
}

void student::getdata()     //Function definition to accept data from user.
{
	cout<<"\nEnter The Roll Number of Student : ";
	cin>>rollno;
	cout<<"\nEnter The Class of Student : ";
	cin>>Class;
	cout<<"\nEnter The Name of Student : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The marks in Science out of 100 : ";
	cin>>s_marks;
	cout<<"\nEnter The marks in Social Science out of 100 : ";
	cin>>ss_marks;
	cout<<"\nEnter The marks in Maths out of 100 : ";
	cin>>m_marks;
	cout<<"\nEnter The marks in English out of 100 : ";
	cin>>e_marks;
	cout<<"\nEnter The marks in Hindi out of 100 : ";
	cin>>h_marks;
	calculate();     //Function calling to calculate grade.
}

void student::showdata() const     //Function definition to show data on screen.
{
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nClass of student : "<<Class;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in Science : "<<s_marks;
	cout<<"\nMarks in Social Science : "<<ss_marks;
	cout<<"\nMarks in Maths : "<<m_marks;
	cout<<"\nMarks in English : "<<e_marks;
	cout<<"\nMarks in Hindi : "<<h_marks;
	cout<<"\nPercentage of student is : "<<per;
	cout<<"\nGrade of student is : "<<grade;
}

void student::show_tabular()const     //Function definition to show data in tabular form.
{
	cout<<rollno<<setw(6)<<Class<<setw(6)<<" "<<name<<setw(10)<<s_marks<<setw(4)<<ss_marks<<setw(4)<<m_marks<<setw(4)
		<<e_marks<<setw(4)<<h_marks<<setw(8)<<per<<setw(6)<<grade<<endl;
}
int student::retrollno()const
{
    return rollno;
}
int student::retClass()const
{
    return Class;
}
void write_student();     //Function to Write the record in binary file.
void display_all();     //Function to Read all records from binary file.
void display_sp(int);     //Function to Accept Roll no and Read record from binary file.
void modify_student(int);     //Function to Accept Roll no and Update record of binary file.
void delete_student(int);     //Function to Accept Roll no and Delete selected records from binary file.
void class_result();     //Function to Display all records in tabular format from binary file.
void result();     //Function to Display result menu.
void intro();     //Function to Display welcome screen.
void entry_menu();     //Function to Display entry menu on screen.

int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2);     //Program outputs decimal number to two decimal places.
	intro();
	do
	{
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. RESULT MENU";
		cout<<"\n\n\t02. ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1/2/3) : ";
		cin>>ch;
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}

void write_student()     //Function definition to Write the record in binary file.
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    cout<<"\n\nStudent Record Has Been Created. Press Enter key. ";
	cin.ignore();
	cin.get();
}

void display_all()     //Function definition to Read all records from binary file.
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press Enter Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}

void display_sp(int n)     //Function definition to Accept Roll no and Read record from binary file.
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press Enter Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nRecord Not Exist. Press Enter key.";
	cin.ignore();
	cin.get();
}

void modify_student(int n)     //Function definition to Accept Roll no and Update record of binary file.
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press Enter Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    	cout<<"\n\n\t Record Updated.Press Enter key.";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found. Press Enter key";
	cin.ignore();
	cin.get();
}

void delete_student(int n)     //Function definition to Accept Roll no and Delete selected records from binary file.
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press Enter Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted.";
	cin.ignore();
	cin.get();
}

void class_result()     //Function definition to Display all records in tabular format from binary file.
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press Enter Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"=============================================================\n";
	cout<<"R.No  Class    Name       S   SS   M   E   H   %age    Grade"<<endl;
	cout<<"=============================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}

void result()     //Function definition to Display result menu.
{
	char ch;
	int rno;

	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3) : ";
	cin>>ch;
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display_sp(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}

void intro()     //Function definition to Display welcome screen.
{
	cout<<"\n\n\n\t\t  Welcome To Student Report card Handling System Project";
	cout<<"\n\n\n\tMADE BY : Tushar saini";
	cout<<"\n\tPress The Enter Key for Main Menu";
	cin.get();
}

void entry_menu()     //Function definition to Display entry menu on screen.

{
	char ch;
	int num;

	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1/2/3/4/5/6) : ";
	cin>>ch;

	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number : "; cin>>num;
			display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number : "; cin>>num;
			modify_student(num);break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number : "; cin>>num;
			delete_student(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}
