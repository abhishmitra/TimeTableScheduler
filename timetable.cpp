#include<iostream.h>
#include<fstream.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*
To do next:
make constants for array size,etc (i can do this if you want)						   add write to file, read from file for each class -static function (for entire array)
*/

/*
Abhishek's comments
 Static ints may need to be read from a file. So that any changes are saved permanently.
 So put them in a class with one object. That way all changes can be made with one read/ write call.
 I also added a basic schema for Table printing. We'll use this later.
 Changes made at LINES:
 1.) 137 -162
 2.) 278 - 299
 3.) 306 - 350

*/



/*
To do later:
use pointers
use data structures
robustness
add comments, menus
capatilization/grammar
*/

/*
stuff to check before running:
i and j are not interchanged
only paramenterized constructor and read from file functions should increment no_labs,no_subjs,etc
make sure constants are used where ever reqd
make sure all counters are used where ever reqd
*/

/*
future improvements / bonus features / features which we may not be able to include
diff batches -commerce,comp,bio
paired subjs -comp/bio
special allocation of class teacher periods, and extra curriculars before lunch
rejection of table based on standard deviation
*/

using namespace std;


class Constant
{
	public:
	int no_labs;
	int no_subjs;
	int no_grades;
	int no_teachers;	
	
	void Constant()
	{
		no_labs = 0;
		no_subjs = 0;
		no_grades = 0;
       	no_teachers = 0;
}
}c;

void WriteC()
{
/*
	Use this after every single change is made to any of the values.
*/
	fstream file(“CONSTANTS.dat”, ios::in|ios::app|ios::binary);
	file.write((char *)&c, sizeof(c));					
}

void ReadC()
{
/*
Use this at the very beginning of the program run. So as to initialize all the lengths.
*/
	fstream file(“CONSTANTS.dat”, ios::in|ios::app|ios::binary);
	file.read((char *)&c, sizeof(c));						
}



class lab
{	
	public:
		static int no_labs;
		
		char name[20];
		int capacity, day[6][10];	
}labs[5];

	void lab::newlab()
	{
		no_labs++;
		
		cout<<"Enter:\n";
		cout<<"Name of Infrastructure: ";
		gets(name);
		cout<<"Capacity: ";
		cin>>capacity;
	}

class subject
{
	public:
		static int no_subjs;
		
		char name[20];
		
		int type, no_doubles, pairing_id;	
		int class_list[15], no_classes;
		int infra_reqd[5];

	
}subjs[50];



int subjext::no_subjs=0;

	void subject::newsubject()
	{
		no_sub += 1; 
		int i=0,temp;
		char ch;
		
		no_subjs++;
		
		cout<<"Enter:\n";
		cout<<"Name of subject: ";
		cin>>name;
		cout<<"Type of subject:\n";
		cout<<"1.Academic\n2.Extra-curricular\n";
		cin>>type;
		cout<<"List of classes\n(continue entering, when done enter 0)\n";
			for(i=0;i<15;i++)
			{
				cin>>temp;
				if(temp==0)
				break;
				class_list[i]=temp;
			}
			no_classes=i;
			
		cout<<"Infra structure required? (y/n)\n"
			for(i=0;i<lab::no_labs;i++)
			{
				cout<<labs[i].name;//based on existing labs
				cin>>ch;
				ch=tolower(ch);
				if(ch=='y')
				infra_reqd[i]=1;
				else
				infra_reqd[i]=0;				
			}
		cout<<"No of double periods per week: ";
		cin>>no_doubles;
		cout<<"Pairing ID:\n(enter 0 if not required)\n";
		cin>>pairing_id;
	}

	void WriteSub(subject s)
	{
		/* Must be used after newsubject() is called. The argument MUST be the object for which 
		   newsubject function is called. As newsub() function is for one object at a time
		  I kept the write function as "one object at a time" too.
		 */
		fstream file1 ("SUBJECTS.dat", ios::app|ios::binary);				
		file1.write((char *)&s, sizeof(s));									
	}


	void ReadSub()
	{

		/* no_sub is a constant that is declared at the beginning of the program
		   before using this function. The constant no_sub must be read from 
		  a file. Otherwise it is 0.
		*/
		fstream file1 ("SUBJECTS.dat", ios::in|ios::binary);
		for (int i = 0; i<no_sub; i++)										
		{																	
			 file1.read((char *)&subjs[i], sizeof(subjs[i]));				
		}																	
																			// a file otherwise it is 0.

	}






	
class grade
{
	public:
		static int no_grades;
		
		int number,no_sections, day[6][10];
		
		Subject subj_list[15];
		int no_per_week[15];
int curr[15][5];	
float prob[15];
}grades[20];

int grade::no_grades=0;

	void grade::newgrade()
	{
		int i,j,k=0,status;
		
		no_grades++;
		
		cout<<"Enter:\n";
		cout<<"Class number: ";
		cin>>number;
		cout<<"Number of sections required: ";
		cin>>no_sections;
		cout<<"No of period per week:\n";
			for(i=0;i<subject::no_subjs;i++)
			{
				for(j=0;j<subjs[i].no_classes;j++)
				{
					if(subjs[i].class_list[j]==number)//based on existing subjects
					{
						cout<<subjs[i].name<<": ";
						subj_list[k]=subjs[i];//add to list
						cin>>no_per_week[k];
					}
				}							
			}
	}
	
class teacher
{
	public:
		static int no_teachers;
		
		char name[20];
		int no_periods_per_week, day[6][10];
		grade myclass;
		
		grade class_list[15];
		subject subj_list[15];

} Teachers[100];

int teacher::no_teachers=0;

	void teacher::newteacher()
	{
			int i, j, k=0, temp;
			char ch;
			
			no_teachers++;
			
			cout<<"Enter:\n";
			cout<<"Name of teacher: ";
			gets(name);
			cout<<"class teacher's class number: ";//need to rephrase  
			cin>>temp;
				for(i=0;i<grade::no_grades;i++)
				{
					if(grades[i].number==temp)
					myclass=grades[i];
				}
			cout<<"No of periods per day: ";
			cin>>no_periods_per_week;
			cout<<"Subjects to be taught? (y,n):\n";
				for(i=0;i<subject::no_subjs;i++)//based on existing subject
				{
					cout<<subjs[i].name<<": ";
					cin>>ch;
					ch=tolower(ch);
					if(ch=='n')
					continue;
					
					cout<<"Classes to be taught? (y/n)";
					for(j=0;j<subjs[i].no_classes;j++)//grades of chosen subject
					{
						cout<<subjs[i].class_list[j]<<": ";
						cin>>ch;
						ch=tolower(ch);
						if(ch=='y')//add to list
						{
							subj_list[k]=subjs[i];
							class_list[k]=subjs[i].class_list[j];
						}
					}					
				}			
	}




/*
		Read And Write functions for teachers. 
		Same stuff as students. See student-io comments
*/


void WriteTeach(teacher T)
{

 fstream file ("TEACHERS.dat", ios::app|ios::binary); 
 file.write((char *)&T, sizeof(T));		 
}



void ReadTeach()
{


 fstream file ("TEACHERS.dat", ios::in|ios::binary);
 int i = 0;
 for (int i = 0; i<no_teachers; i++)
	{
		 file.read((char *)&Teachers[i], sizeof(Teachers[i]));
		 //i+=1;
	}

}





/*
void PrintTable( TABLE)
{
		cout<<"__________________________________________\n";
		for (int i = 0; i<7; i++)
		{			
			for (int j = 0; j< periods_per_day - 1; j++)
			{
				cout<<"|"<<Class[i][j].Class<<"|";
			}
			cout<<"\n";
		}
}





void Process()
{
int i,j,k,l,curr	
for(i=0;i<no_grades;i++)//choose class
{
for(j=0;j<grade[i].max_subjs;j++)//choose period
{	
	 	for (k=0; k<5;k++)//choose day
		{
        		if(curr[j][k]/9.0>no_per_week[j]/45.0)  					    
				grade[i].prob[j]=0;
	  		else
				grade[i].prob[j]=(9-curr[j][k])/9;
			int period = RandomDraw();
			Class[day][period] = subj_list[period];
}
}
}
/*
void RandomDraw()
{
	int cf[];
      int o = 0;
srand (time(NULL));
	for (int j =0;j<maxsub;j++)
	{
		o += grade[i].prob[j];
		cf[i] = o;
}	

int rand = rand() % cf[maxsub];         //Limit is from 0 till cf[i]
int sum = 0; 
int k =0;
while (sum < rand)
{
	sum = cf[k];
k+=1;
}
return k;
}		
*/		
	


for class
	   //for section
	      for period
		       define fixed average per day

		       next allocation
			  choose subject
				  define current average

				  if current average > fixed average
				      P(Sub) = 0
				  else
						 periods of Sub to allocate
					P(Sub) = ---------------------------
						 total periods to allocate

		       Randomly select
		   }

	

}

*/
class allocate
{

ReadC();
/*
call functions for input
make the time table
print according to teacher
print according to class +section 
call functions for file management
*/
};

