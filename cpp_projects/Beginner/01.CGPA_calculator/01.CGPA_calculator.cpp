#include<iostream>
#include<string>

using namespace std;

struct points {
	int credit;
	float gp;
	struct points * nxt = nullptr;
};


class sem {

private:	
	points * start[5] = (points *) malloc (sizeof(points));
	points * current[5] = nullptr;
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
	vector<vector<string>> course (5, vector<string> (4, string()));

	void GPA(){
		for (i=4;i>=0;i++){
			temp=start[i];
			while(temp->nxt!=nullptr){
				gp_score += temp->credit * temp->gp;
				tot_credits += temp->credit;
				temp=temp->nxt;
			}
		}
		gpa = gp_score / total_gp ;
	}

	void input(){
		cout<< left << setw(35) << "COURSE" << "GRADE POINTS";
		for (i=4;i>=0;i++)
			for (j=0;course[i][j].empty()!=1;j++){
				cout<< left << setw(35) << course[i][j];
				cout<< string(5, " ");
				cin >> gp;
				insert (i);
			}
	}
};

//semester object declaration
sem sem[6];

float CGPA(int tot_sem){
	if (tot_sem == 0)
		return 0;
	else
		return ( (sem[tot_sem -1].gpa + CGPA(tot_sem - 1)) / tot_sem );
}

int main(){
	int tot_sem;
	sem[
