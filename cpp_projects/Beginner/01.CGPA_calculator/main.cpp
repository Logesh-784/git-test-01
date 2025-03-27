#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<fstream>
#include<ranges>


using namespace std;

struct points {
	int credit;
	float gp;
	struct points * nxt = nullptr;
};


class sem {

private:	
	points * start[5] = { (points *) malloc (sizeof(points)) } ;
	points * current[5] = { nullptr } ;
	points * temp;
	float gp;
	int i, j;
	float gp_score, tot_credits;

	void insert(int credit){
		if (current[credit]!=nullptr){
			current[credit]->nxt = (points *) malloc (sizeof(points));
			current[credit] = current[credit]->nxt;
		}
		else
			current[credit] = start[credit];
		current[credit]->credit = credit;
		current[credit]->gp = gp;
	}



public:
	float gpa;
	vector<vector<string>> course;

	sem(){
		course.resize(5,vector<string>(4, ""));
	}

	void GPA(){
		for (i=4;i>=0;i++){
			temp=start[i];
			while(temp->nxt!=nullptr){
				gp_score += temp->credit * temp->gp;
				tot_credits += temp->credit;
				temp=temp->nxt;
			}
		}
		gpa = gp_score / tot_credits ;
	}

	void input(){
		cout<< left << setw(40) << "COURSE" << "GRADE POINTS";
		for (i=4;i>=0;i++)
			for (j=0;course[i][j].empty()!=1;j++){
				cout<< left << setw(40) << course[i][j];
				cout<< string(5, ' ');
				cin >> gp;
				insert (i);
			}
	}
};

//semester object declaration
sem sem[6];

float CGPA_calc(int tot_sem){
	if (tot_sem == 0)
		return 0;
	else
		return ( (sem[tot_sem -1].gpa + CGPA_calc(tot_sem - 1)) / tot_sem );
}

void assign_subj(){
	vector<string> semfiles{"sem_01.txt","sem_02.txt","sem_03.txt","sem_04.txt","sem_05.txt","sem_06.txt"};
	int sem_no=0;
	for (auto semfile : semfiles){
		ifstream file_in(semfile);
		if (file_in.is_open())
			for(int i=0;i<5;i++)
				for(int j=0;j<4;j++)
					getline(file_in, sem[sem_no].course[i][j]);
		else{
			cerr<<"Sem subject list files error or not found"<<endl;
			exit(5);
		}
		sem_no++;
	}
}


int main(){
	int tot_sem,sem_no,choice ;
	float cgpa;
	system("clear");
start:	cout<<"\n\n1. Calculate GPA\n2. Calculate CGPA" << endl;
	cin>>choice;
	switch(choice){
		case 1:
			cout<<"\nEnter the semester number: ";
			cout<<choice;
			cin>>sem_no;
			cout<<sem_no;
			sem[sem_no].input();
			sem[sem_no].GPA();
			cout<< "Your Semester "<< sem_no <<" GPA is "<<sem[sem_no].gpa <<endl;
			break;

		case 2:
			cout<<"\nEnter the number of Semesters ended : ";
			cin>>tot_sem;
			for(sem_no=0;sem_no<tot_sem;sem_no++){
				sem[sem_no].input();
				sem[sem_no].GPA();
			}
			cgpa = CGPA_calc(tot_sem);
			cout<<"Your current CGPA is "<<cgpa<<endl;
			break;

		default:
			cout<<"\n\n\nYou have entered an invalid option!!" <<endl;
			goto start;
	}
	return 0;
}
