#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <cstddef>
#include <bits/stdc++.h>





using namespace std;

template <typename T>
std::string to_string(T value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

class U{
private:
    string username;
    string password;

public:
    U(string username, string password) {
        this->username = username;
        this->password = password;
    }

    bool authenticate(string username, string password) {
        return (this->username == username && this->password == password);
    }

    bool save_to_file(string username, string password) {
        ofstream outfile("users.txt", ios::app);
        if (!outfile) {
            cout << "Error opening file for writing!" << endl;
            return false;
        }
        outfile << username << "," << password << endl;
        outfile.close();
        return true;
    }

    string get_username() {
        return username;
    }

    void set_username(string username) {
        this->username = username;
    }

    string get_password() {
        return password;
    }

    void set_password(string password) {
        this->password = password;
    }

    static bool check_credentials(string username, string password, string filename) {
        ifstream infile(filename.c_str());
        if (!infile) {
            cout << "Error opening file for reading!" << endl;
            return false;
        }
        string line;
        while (getline(infile, line)) {
            size_t pos = line.find(",");
            string file_username = line.substr(0, pos);
            string file_password = line.substr(pos + 1);
            if (file_username == username && file_password == password) {
                infile.close();
                return true;
            }
        }
        infile.close();
        return false;
    }
};





class Student {
    private:
        std::string name;
        std::string rollNumber;
        std::string roomNumber;
        std::string phoneNumber;
        std::string parentphone;

    public:
    	Student(){}
        Student(std::string r, std::string n, std::string rm, std::string p, std::string pp) {
            name = n;
            rollNumber = r;
            roomNumber = rm;
            phoneNumber = p;
            parentphone= pp;
        }

        void saveToDatabase() {
            std::ofstream outfile;
            outfile.open("student_database.txt", std::ios_base::app);  // Open file in append mode

            // Write data to file
            outfile <<  rollNumber << ","  <<name<< "," << roomNumber << "," << phoneNumber << "," << parentphone << std::endl;

            // Close file
            outfile.close();
        }
        
        void getinformation(string rollno){
        	cout << "\n\n   Student name     : "<< name<<endl;
        	cout << "   Roll no          : "<<rollno<<endl;
        	cout << "   Allocated room   : "<<roomNumber<<endl;
        	cout << "   Phone no.        : "<<phoneNumber<<endl;
        	cout << "   Parent phone no. : "<<parentphone<<"\n\n"<<endl;
		}
		
		bool loadFromDatabase(const std::string& rollNo) {
        std::ifstream infile("student_database.txt");
        if (infile) {
            std::string line;
            while (getline(infile, line)) {
                std::stringstream ss(line);
                std::string field;
                getline(ss, field, ','); // Roll number is first field in the file
                if (field == rollNo) {
                    // Found the student, extract and set their fields
                    getline(ss, name, ',');
                    getline(ss, roomNumber, ',');
                    getline(ss, phoneNumber, ',');
                    getline(ss, parentphone, ',');
                    return true;
                }
            }
            infile.close();
        }
        // Student not found
        return false;
    }
};









class FLOOR{
	private:
		int floorno;
		string hname;
		int roomperfloor;
	public :
		FLOOR(string hname ,int floorno,int roomperfloor ){
		this -> floorno = floorno;
		this -> hname = hname;
		this -> roomperfloor =  roomperfloor;
		}
};




class HOSTEL{
	private:
		string hname;
		int floor;
		int roomperfloor;
	public:
		HOSTEL(string hname,int floor, int roomperfloor);
		bool searchstudent(string rollno);
		void vacancy();
		void allocate(string rollno);
		void deallocate(string rollno);
		
		string getname(){
			return hname;
		}

		
};


bool HOSTEL::searchstudent(string rollno){
    for(int i = 1; i <= floor; i++){
        string filename = hname + "_floor_" + to_string(i) + ".txt";
        ifstream infile(filename.c_str());
        string line;
        while (getline(infile, line)) {
            stringstream ss(line); // split the line into separate values using comma delimiter
            string value1,value2, value3, value4;
            if (getline(ss, value1, ',') && getline(ss, value2, ',') && getline(ss, value3, ',') && getline(ss, value4, ',')) { // read the values from the line
                if (value2 == rollno) {
                	Student s2;
                	if(s2.loadFromDatabase(rollno)){
                		s2.getinformation(rollno);
					}
                	
                	

                    infile.close();
                    return true;
                }
            }
        }
        infile.close();
    }
    cout << "Student " << rollno << " not found." << endl;
    return false;
}

HOSTEL::HOSTEL(string hname, int floor, int roomperfloor){
    this->hname = hname;
    this->floor = floor;
    this->roomperfloor = roomperfloor;
    
    for(int i=1; i<=floor; i++){
        string filename = hname + "_floor_" + to_string(i) + ".txt";
        ifstream infile(filename.c_str());
        if(!infile.good()){
            infile.close();
            ofstream outfile(filename.c_str());
            for(int j=1; j<=roomperfloor; j++){
                string roomno = to_string(i*100 + j);
                outfile << roomno << ",0,0,vacant" << endl;
            }
            outfile.close();
        }
    }
}




void HOSTEL::vacancy(){
	
	for(int i = 1; i <= floor; i++){
			    string filename = hname + "_floor_" + to_string(i) + ".txt";
				ifstream infile(filename.c_str());
			    string line;
			    cout << "\n\n  Floor "<< i<<"\n"<<endl;
    			while (getline(infile, line)) {
    				stringstream ss(line); // split the line into separate values using comma delimiter
    				string value1 , value2, value3, value4;
    				if (getline(ss, value1, ',') && getline(ss, value2, ',') && getline(ss, value3, ',') && getline(ss, value4, ',')) { // read the values from the line
        			if (value2 == "0") {
        				cout << "ROOM - "<< value1 << endl;
    				}
    				else{
    					continue;
					}
					}
				}
				infile.close();

			}
}



void HOSTEL::allocate(string rollno){
	
			if(searchstudent(rollno)){
				cout << "\nStudent "<<rollno << " has already been allocated a room \n\n";
				return;
			}
	
			vacancy();
			string roomno ;
			string sname = "Not provided";
			string pphone = "Not provided";
			string phone="Not provided";
		
			
			cout << "\n      ENTER ROOM CHOICE           : ";
			cin >> roomno;			
			cout << "\n      ENTER YOUR NAME             : ";
			cin >>	sname;
			cout << "\n      ENTER YOUR PHONE NO.        : ";
			cin >> phone;
			cout << "\n      ENTER YOUR PARENT PHONE NO. : ";
			cin >> pphone;
			Student student(rollno,sname,roomno, phone, pphone);

   			 // Save student data to file
    		student.saveToDatabase();
int floorno;
stringstream ss(roomno);
ss >> floorno;
floorno /= 100;
			
    string filename = hname + "_floor_"+to_string(floorno) + ".txt"; // input file name
    string tempfilename = "temp.txt"; // temporary output file name
    string line_to_update = roomno + ",0,0,vacant"; // line to update
    string updated_line = roomno +","+rollno +","+  sname +",occupied" ; // updated line

    // open the input file in read mode and the temporary output file in write mode
    ifstream infile(filename.c_str());
    ofstream tempfile(tempfilename.c_str());

    string line;
    while (getline(infile, line)) {
        if (line == line_to_update) { // if the line needs to be updated
            tempfile << updated_line << endl; // write the updated line to the temporary output file
        } else {
            tempfile << line << endl; // write the line to the temporary output file as it is
        }
    }
    cout << "             .---." << endl;
    cout << "            /     |\\__________________" << endl;
    cout << "            | ()  | _______   ___   ___)" << endl;
    cout << "            \\      |/       | |   | |" << endl;
    cout << "             `---'         \"-\"   |_|" << endl;
    cout << "\nRoom no "<<roomno<< " has been allocated to "<< sname <<" "<< rollno << " successfully\n"<<endl;


    infile.close();
    tempfile.close();

    // delete the input file and rename the temporary output file to the original file name
    remove(filename.c_str());
    rename(tempfilename.c_str(), filename.c_str());			
			
		
}

void HOSTEL::deallocate(string rollno){
    bool is_allocated = false;
    for(int i = 1; i <= floor; i++){
        string filename = hname + "_floor_" + to_string(i) + ".txt";
        ifstream infile(filename.c_str());
        ofstream tempfile("temp.txt");
        string line;
        while (getline(infile, line)) {
            stringstream ss(line);
            string roomno, occupant_rollno, occupant_name, status;
            getline(ss, roomno, ',');
            getline(ss, occupant_rollno, ',');
            getline(ss, occupant_name, ',');
            getline(ss, status, ',');
            if (occupant_rollno == rollno && status == "occupied") { // if the room is occupied by the given student
                tempfile << roomno << ",0,0,vacant" << endl; // change the status to vacant and write the line to the temporary output file
                cout << "Room no " << roomno << " has been deallocated from " << rollno << " successfully\n";
                is_allocated = true;
            } else {
                tempfile << line << endl; // write the line to the temporary output file as it is
            }
        }
        infile.close();
        tempfile.close();
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
    if (!is_allocated) {
        cout << "Student " << rollno << " is not allocated to any room." << endl;
    }	
}



void hosteloptions(HOSTEL &H){
	int choice;
	do{
		string hname = H.getname();
	cout << "\n\n    -------------------\n";
	cout << "      << "<< hname<<" >>  \n";
	cout << "    *******************\n";
		

	cout << "\n   1. SEARCH STUDENT IN HOSTEL \n";
	cout << "   2. SHOW ROOM VACANCY \n";
	cout << "   3. ALLLOCATE ROOM \n";
	cout << "   4. DEALLOCATE ROOM\n";
	cout << "   0. EXIT\n\n";
    cout << "   ENTER YOUR CHOICE : ";

	
	cin >> choice;
	string rollno;
switch (choice) {
    case 1:
        cout << "   \nENTER ROLL NO  : ";
        cin >> rollno;
        H.searchstudent(rollno);
        break;
    case 3:
        cout << "   \nENTER ROLL NO : ";
        cin >> rollno;
        H.allocate(rollno);
    	break;
    case 2:
cout << "                                _________" << endl;
cout << "                               |__$_$_$__|" << endl;
cout << "                          +------------------+" << endl;
cout << "                          ||\\                |" << endl;
cout << "                          || \\               |" << endl;
cout << "                          ||  \\              |" << endl;
cout << "                          ||   \\             |" << endl;
cout << "                          ||    \\            |" << endl;
cout << "                          ||     |           |" << endl;
cout << "                          ||     |           |" << endl;
cout << "                          ||     |           |" << endl;
cout << "                          ||    @|           |" << endl;
cout << "                          ||     |           |" << endl;
cout << "                          ||     |           |" << endl;
cout << "                          ||     |           |" << endl;
cout << "                          ||     /           |" << endl;
cout << "                          ||    /            |" << endl;
cout << "                          ||   /             |" << endl;
cout << "THE VACANT ROOMS ARE :    ||  /              |" << endl;
cout << "                          ||_/_______________|" << endl;
    	
    	H.vacancy();

    	break;
    case 4:
    	cout << "   ENTER ROLL NO TO DEALLOCATE : ";
    	cin >> rollno;
    	H.deallocate(rollno);
    	break;
      //  H.vacancy();
      //  break;
   // default:
     //   cout << "Invalid choice!";
       // break;
	}
}while(choice);
}

void createHostel() {
    string hname;
    int floors, roomsPerFloor;

    // get input from user for new hostel
    cout << "\n  Enter the name of the new hostel: ";
    cin >> hname;
    cout << "  Enter the number of floors in the hostel: ";
    cin >> floors;
    cout << "  aEnter the number of rooms on each floor: ";
    cin >> roomsPerFloor;

    // open the file in append mode and write the details of the new hostel to the end of the file
    ofstream outfile("hostels.txt", ios::app);
    outfile << hname << "," << floors << "," << roomsPerFloor << endl;
    outfile.close();

    // print confirmation message
    cout << "\n\nNew hostel '" << hname << "' has been created with " << floors << " floors and " << roomsPerFloor << " rooms per floor.\n\n" << endl;
}



void createHostelObjectsFromFile(string filename, vector<HOSTEL>& hostels) {
    ifstream infile(filename.c_str());
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string hname;
        int floor_count, room_count;
        if (getline(ss, hname, ',') && ss >> floor_count && ss >> room_count) {
            HOSTEL hostel(hname, floor_count, room_count);
            hostels.push_back(hostel);
        }
    }
    infile.close();
}


HOSTEL chooseHostel() {
    // open the file of hostels
    ifstream infile("hostels.txt");

    // read each line from the file and store the details in a vector of Hostel objects
    vector<HOSTEL> hostels;
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string hname;
        int floors, roomsPerFloor;
        if (getline(ss, hname, ',') && ss >> floors && ss.ignore() && ss >> roomsPerFloor) {
            hostels.push_back(HOSTEL(hname, floors, roomsPerFloor));
        }
    }
    int chh;
        int ch4;

    do{
    	chh = 0;

    // print the list of hostels and allow the user to choose one
    for (int i = 0; i < hostels.size(); i++) {
        cout <<"      "<< i+1 << ". " << hostels[i].getname() << endl;
    }
    cout << "\n   ENTER HOSTEL NUMBER : ";
    cin >> ch4;
    if ( ch4 <1||ch4 > hostels.size()) {
        cout << "\n\n   Invalid choice !!!!" << endl;
        chh = 1;
        
    }
}while(chh);

    // call the main program with the chosen hostel object
    return hostels[ch4-1];
}






class YEAR{
	
	public:
		string year;

		YEAR(string year){
			this->year = year;
    		ofstream outfile((year + "_semesters.txt").c_str(),ios ::app);
            outfile.close();
		}		
		
		void availablesemesters(){
			vector<string > semesters;
			ifstream infile((year + "_semesters.txt").c_str());
        	if (infile) {
            	string line;
            	while (getline(infile, line)) {
                	semesters.push_back(line);
            	}
            infile.close();
        	}
        	cout << "   The Available Semesters are : \n";
			for (int i = 0; i < semesters.size(); i++) {
    			cout <<"      "<< semesters[i] << endl;			
			}		
		}
		
		
		
		
		
		void createsem(string semname);
		
		
		void createsemster(){
			availablesemesters();
		int makesem =0;
		cout <<"\n\n   To create new semester Enter 1 : ";
		cin >> makesem;
		if(makesem == 1){
			string seme,sems;
			cout << "\n   Enter semester start month : ";
			cin >> sems;
			cout << "   Enter semester end month : ";
			cin >> seme;
	        string semname = sems + "_" + seme;

			createsem(semname);
		}
	}
		
		
};
	
		
class payment : public YEAR{
	public:
		string semester;
		payment(string year,string semester) : YEAR(year){
			semester = semester;
		}
		
	void add_payment();
		
	
	
};





void payment::add_payment() {
    std::string student_id, utr_no, date;
    double amount_paid;

    // Get user input
    
vector<string > semesters;
			ifstream infile((year + "_semesters.txt").c_str());
        	if (infile) {
            	string line;
            	while (getline(infile, line)) {
                	semesters.push_back(line);
            	}
            infile.close();
        	}    std::cout << "   Choose a semester:" << std::endl;
    for (int i = 0; i < semesters.size(); i++) {
        std::cout <<"   "<< i+1 << ". " << semesters[i] << std::endl;
    }
    int semester_choice;
    std::cin >> semester_choice;
    std::string semester = semesters[semester_choice-1];
    std::cout << "      Enter student ID        : ";
    std::cin >> student_id;

    std::cout << "      Enter amount paid       : ";
    std::cin >> amount_paid;

    std::cout << "      Enter UTR number        : ";
    std::cin >> utr_no;


    std::cout << "      Enter date (YYYY-MM-DD) : ";
    std::cin >> date;

    // Write to file
    std::ofstream outfile((year +"_"+ semester + ".txt").c_str(), std::ios::app);
    if(outfile){
        outfile << student_id << "," << amount_paid << "," << utr_no << "," << date << "\n";
        outfile.close();
    }
    else{
        cout << "      Semester not found !!!";
    }

    std::cout << "\n      Payment record added to file " << semester << ".txt\n";
}




void YEAR::createsem(string semname){
    string filename = semname ;
    
    // check if semester already exists
    ifstream infile((year + "_semesters.txt").c_str());
    string line;
    while (getline(infile, line)) {
        if (line == filename) {
            cout << "      Semester already exists !!!\n";
            infile.close();
            return;
        }
    }
    infile.close();
    
    // add semester to year_semesters file
    ofstream outfile((year + "_semesters.txt").c_str(), ios::app);
    outfile << filename << "\n";
    outfile.close();
    
    // create semester file
    ofstream out((year + "_" + semname + ".txt").c_str());
    if (out) {
        cout << "   Semester " << semname << " created in year " << year <<"\n\n"<< endl;
        out.close();
    } else {
        cout << "      Error creating semester file!" << endl;
    }
}



void check_payment(){
    string student_id;
    cout << "\n   Enter roll no of the student :";
    cin >> student_id;

    // Get current year
    time_t t = time(NULL);
    struct tm *now = localtime(&t);
    int current_year = now->tm_year + 1900;

    // Check records for last three years
    for (int i = 0; i < 3; i++) {
        int year_in = current_year - i;
        std::cout <<"   "<< "\nYear " << year_in << ":\n";
        std::stringstream year_stream;
        year_stream << year_in;
        std::string year = year_stream.str();

        // Check records for all semesters in this year
        ifstream infile((year + "_semesters.txt").c_str());
        if (infile) {
            string line;
            while (getline(infile, line)) {
                // Get semester name from filename
                std::cout <<"   "<< "\nsemester " << line << ":\n";

                // Check records for given student ID in this semester
                ifstream infile2((year +"_"+ line + ".txt").c_str());
                if (infile2) {
                    string record;
                    while (getline(infile2, record)) {
                        // Split record into fields
                        vector<string> fields;
                        stringstream ss(record);
                        string field;
                        while (getline(ss, field, ',')) {
                            fields.push_back(field);
                        }

                        // Check if record matches given student ID
                        if (fields[0] == student_id) {
                            std::cout << "      Payment record found:\n\n";
                            std::cout << "      Student ID    : " << fields[0] << std::endl;
                            std::cout << "      Amount paid   : " << fields[1] << std::endl;
                            std::cout << "      UTR number    : " << fields[2] << std::endl;
                            std::cout << "      Date          : " << fields[3] << std::endl;
                        }
                        
                    }
                    infile2.close();
                }
            }
            infile.close();
        } else {
            std::cout << "\n   No semesters this year " << year << std::endl;
        }
    }
}
















class InOutStudent : public Student {
public:
	void viewOutStudents() {
    std::ifstream infile("student_out.txt");
    if (infile) {
        std::vector<std::string> student_lines;
        cout << "\n\n   Out Students:" << std::endl;
        cout << "^^^^^^^^^^^^^^^^^^^\n"<<endl;
        std::string line;
        int student_num = 1;
        while (getline(infile, line)) {
            std::stringstream ss(line);
            std::string roll, time;
            getline(ss, roll, ',');
            getline(ss, time);
            std::cout << student_num << ". " << roll <<"     "<< " (" << time << ")" << std::endl;
            student_lines.push_back(line);
            student_num++;
        }
        infile.close();
        
        std::cout << "\n\nEnter student number to view details :\n";
        cout << "<<< Enter 0 to exit : ";
        int choice;
        std::cin >> choice;
        if (choice > 0 && choice <= student_lines.size()) {
            std::stringstream ss(student_lines[choice - 1]);
            std::string roll, time;
            getline(ss, roll, ',');
            getline(ss, time);
            Student sout ;
            sout.loadFromDatabase(roll);
            sout.getinformation(roll);
        }
    } else {
        std::cout << "Error: student_out.txt not found." << std::endl;
    }
}


    void checkOutStudent() {
        std::string rollNumber;
        std::cout << "\n   Enter roll number of student checking out: ";
        std::cin >> rollNumber;

        
        time_t t = time(NULL);
        struct tm* now = localtime(&t);
        std::stringstream ss;
        ss << (now->tm_year + 1900) << "-" << (now->tm_mon + 1) << "-" << now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
        std::string currentTime = ss.str();

        std::ofstream outfile;
        outfile.open("student_out.txt", std::ios_base::app);
        outfile << rollNumber << "," << currentTime << std::endl;
        outfile.close();

        std::cout << "Student with roll number " << rollNumber << " has been checked out of the hostel." << std::endl;
    }
    void checkInStudent() {
    std::string rollNumber;
    std::cout << "Enter roll number of student checking in: ";
    std::cin >> rollNumber;

    // Get current time
    time_t t = time(NULL);
    struct tm* now = localtime(&t);
    std::stringstream ss;
    ss << (now->tm_year + 1900) << "-" << (now->tm_mon + 1) << "-" << now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
    std::string currentTime = ss.str();

    std::ifstream infile("student_out.txt");
    std::vector<std::string> lines;
    if (infile) {
        std::string line;
        while (getline(infile, line)) {
            std::stringstream ss(line);
            std::string roll;
            getline(ss, roll, ',');
            if (roll != rollNumber) {
                lines.push_back(line);
            }
        }
        infile.close();
    }

    std::ofstream outfile;
    outfile.open("student_out.txt", std::ofstream::out | std::ofstream::trunc);
    outfile.close();

    outfile.open("student_out.txt", std::ios_base::app);
for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
    std::string line = *it;
    // rest of the code here

        outfile << line << std::endl;
    }
    outfile.close();

    std::cout << "Student with roll number " << rollNumber << " has been checked into the hostel." << std::endl;
}
};











int main() {
    U A("admin", "admin");
    if(!A.check_credentials("admin", "admin", "users.txt"))
    	A.save_to_file("admin", "admin");
        string username, password;
        int check = 0;
do{ 
     cout << " ---------\n";
    cout << "| # # # # |         +----------------------------+\n";
    cout << "| # # # # |         |      DIGITAL CARETAKER     |\n";
    cout << "| # # # # |         +============================+\n";
    cout << "| # # # # |\n";
    cout << "| # # # ---------\n";
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |    Login :\n";
    cout << "| # # #| # # # # |    Enter username: ";
    cin >> username;
    cout << "| # # #| # # # # |    Enter password: ";

    cin >> password;
    if (!U::check_credentials(username, password, "users.txt")) {
        cout << "\nX Authentication failed  !!!!!!\n\n" << endl;
    }else{check = 1;
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |    successfull...\n";
    
	}
    }while(!check);
    
    
    
	int ch1;
    do{
    cout << " ---------\n";
    cout << "| # # # # |         +----------------------------+\n";
    cout << "| # # # # |         |      DIGITAL CARETAKER     |\n";
    cout << "| # # # # |         +============================+\n";
    cout << "| # # # # |\n";
    cout << "| # # # ---------\n";
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |       1. Choose Hostel \n";
    cout << "| # # #| # # # # |       2. Hostels Fee Related\n";
    cout << "| # # #| # # # # |       3. Students IN-OUT \n";
    cout << "| # # #| # # # # |       4. Extra Options \n";
    cout << "| # # #| # # # # |\n";
    cout << "| # # #| # # # # |       Enter your choice : ";
    cin >> ch1;
    cout << "\n\n";
    InOutStudent IO;
    switch(ch1){
    	case 1:{
                HOSTEL HH = chooseHostel();
                hosteloptions(HH);
                break;
            }
        case 2:
        	int fch;
        	do{
        	cout << "\n\n   1.Update students payment information :\n";
        	cout << "   2.Check student payment information :\n";
        	cout << "   << Enter 0 to exit \n\n";
        	cout << "   Enter your choice : ";
        	cin >> fch;
        	YEAR PY(" ");
        	payment PP("","");
        	string year_st;
        	int year;
        	tm* now;
        	time_t t;
        	string semname;
        	string py;


        	
        	switch(fch){
        		case 1:
        		    t = std::time(NULL);
    				now = std::localtime(&t);
    				year = now->tm_year + 1900;
    				year_st = to_string(year);
        			PY = YEAR(year_st);
        			PP = payment(year_st,"");
        			PP.add_payment();
        		break; 
				case 2:
					check_payment();
					break;
					       		   		        			     			
        	}
         	}while(fch);
		
			
		break;
		case 3:
			int ioch;
			do{
			cout << "\n      1. CHECK OUT :";
			cout << "\n      2. CHECK IN :";
			cout << "\n      3. VIEW OUT STUDENTS :";
			cout << "\n      << Enter 0 to exit :";
			cout << "\n\n      Enter choice : ";
			cin >> ioch;
			switch(ioch){
				case 1:
					IO.checkOutStudent();
					break;
				case 2:
					IO.checkInStudent();
					break;
				case 3:
					IO.viewOutStudents();
					break;
					
			}
			
			
			
			
			}while(ioch);
		break;
			
			

        	

    	case 4:
    		int ch2;
    		do{
    		cout << "  1. Add New Semester : \n";
    		cout << "  2. Add New Caretaker : \n";
			cout << "  3. Create New Hostel : \n";
    		cout << "  0. EXIT \n\n";
    		cout << "  ENTER YOUR CHOICE : ";
    		cin >> ch2;
    		string y;
			YEAR Y("");
    		switch (ch2){
    			case 3:
    				createHostel();
    			break;
    			case 1:
    				
    				cout << "\n   Enter year :";
    				cin >> y;
    				Y = YEAR(y);
    				Y.createsemster();
    				break;
    			case 2:
    				string usern, pass;
        			cout << "\n   Enter username for caretaker : ";
        			cin >> usern;
		        	cout << "   Enter password for you : ";
        			cin >> pass;
        			U B(usern,pass);
        			B.save_to_file(usern,pass);
		        	cout <<"\n   "<<usern << " added as a caretaker\n\n"<< endl;
				break;	
    				
    			
    			
				
			}		
			}while(ch2);
		break;
	}		
			
	}while(ch1);
    
    

	

    return 0;
}

