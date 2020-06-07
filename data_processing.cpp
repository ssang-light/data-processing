/**********************************************************************************************************
Parsing code related to the gps information of the Vehicle.
-Parse the data to individual objects in DATA format
-DATA format is consists of 8 components 
-After parsing , various functions generate meaningful ata according to the DATA mainly related to speed

-Product of org SSanglight 
**********************************************************************************************************/




#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>
#include <time.h>


#define OV_SP_LIMIT 16.6 //  기준 = m/s
#define RAPID_ACC 3.79 //급가속 기준 = 변화량이 8.5mph =  13.67km.h = 3.79 m/s
#define RAPID_BRK 0.02 //급감속 기준 = 변화량이 6.5mph = 10.4km/h = 2.88 m/s



using namespace std;


struct DATA
{
	string accuracy;
	string altitude;
	string altitudeAccuracy;
	string heading;
	string latitude;
	string longtitude;
	string speed;
	string timestamp;
};

double is_avg_speed(vector<DATA> vec) {
	
	int sum = 0;
	int total_index = vec.size();
	double d = 0.0;
	
	for (int i = 0; i < vec.size(); i++) {
		stringstream ssDouble(vec[i].speed);
		ssDouble >> d;
		sum += d;
	}
	return sum / total_index;
}


double is_total_time(vector<DATA> vec) {//total time spent on driving
	double d_start, d_end = 0.0;
	int size = vec.size()-1;
	stringstream sDouble(vec[0].timestamp);
	sDouble >> d_start;
	stringstream saDouble(vec[size].timestamp);
	saDouble >> d_end;
	
	return d_end - d_start;
}
int is_over_speed(vector<DATA> vec) {//time of the overspeed according to the local speed limit
	int over_speed_time =0;
	double speed = 0.0;
	for (int i = 0; i < vec.size(); i++) {
		stringstream speedDouble(vec[i].speed);
		speedDouble >> speed;
		if (speed> OV_SP_LIMIT) {
			over_speed_time++;
		}
	}
	return over_speed_time;
}

pair<int,int> rapid_speed_change(vector<DATA> vec) {//time of the rapid acc or brk according to the international standard
	double rapid_speed = 0.0;
	double speed_later = 0.0;
	double speed_before = 0.0;
	pair<int, int>warning; //warning <rapid_acc,rapid_break>

	for (int i = 0; i < vec.size()-1; i++) {
		stringstream beforeDouble(vec[i].speed);
		stringstream laterDouble(vec[i+1].speed);
		beforeDouble >> speed_before;
		laterDouble >> speed_later;
		rapid_speed = speed_later - speed_before;
		if (rapid_speed > 0 && rapid_speed >= RAPID_ACC) {
			warning.first++;
		}
		if (rapid_speed < 0 && abs(rapid_speed) >= RAPID_BRK) {
			warning.second++;
			cout << "vector number rapid break = " << i << endl;
		}
	}
	return warning;
}


int main() {
	
	ifstream file;
	file.open("data.txt");

	if (file.fail()) {
		return (cout << "no such file" << endl) && 0;
	}

	vector<DATA> vec;
	DATA data;
	int count = 0;
	int index = 0;
	while (file.good()) {
		char str[100] = { '/0' };
		file.getline(str,100);
		//cout << str << " "<< "line finished"<<endl<<endl;
		int key = 1;
		for (int i = 0; i < 100; i++) {
			
			if (str[i] == '"') {
				
				int ending_point = 0;
				if (key == 1) {
					//cout << endl<<endl<<"new line starting here" << endl << endl;
					//cout << "open " << str[i]<<str[i+1]<<str[i+2]<<str[i+3]<<str[i+4]<< endl;
					//cout << str << endl;
				}
				
				if(key==-1) {
					ending_point = i;
				}
				key = key * -1;
			}
			
			if (str[i] == ':'&& count ==0) {
				cout << "================================================" << endl;
				cout << "count value " << count << endl;

				count++;
			}
			//each of line is pared by the existence of the sign ":"
			else if (str[i] == ':' && count ==1) {
				//accuracy
				cout << "count>>" << count << " " << str[i + 2] << endl;
				string single_line = str;
				int found = single_line.find(",");
				string target = single_line.substr(i + 2, found - (i + 2));
				cout << "is this your target?? >>>>>>" << target << endl;

				data.accuracy = target;
				count++;
				
			}
			else if (str[i] == ':' && count == 2) {
				//altitude
				cout << "count>>" << count << " " << str[i + 2] << endl;
				string single_line = str;
				int found = single_line.find(",");
				string target = single_line.substr(i + 2, found - (i + 2));
				cout << "is this your target?? >>>>>>" << target << endl;

				data.altitude = target;
				count++;
				
			}
			else if (str[i] == ':' && count == 3) {
				//altitudeAccuracy
				cout << "count>>" << count << " " << str[i + 2] << endl;
				string single_line = str;
				int found = single_line.find(",");
				string target = single_line.substr(i + 2, found - (i + 2));
				cout << "is this your target?? >>>>>>" << target << endl;

				data.altitudeAccuracy = target;
				count++;
				
			}
			else if (str[i] == ':' && count == 4) {
				//heading
				cout << "count>>" << count << " " << str[i + 2] << endl;
				string single_line = str;
				int found = single_line.find(",");
				string target = single_line.substr(i + 2, found -(i + 2));
				cout << "is this your target?? >>>>>>" << target << endl;
				
				data.heading = target;
				count++;
				
			}
			else if (str[i] == ':' && count == 5) {
				//latitude
				cout << "count>>" << count << " " << str[i + 2] << endl;
				string single_line = str;
				int found = single_line.find(",");
				string target = single_line.substr(i + 2, found - (i + 2));
				cout << "is this your target?? >>>>>>" << target << endl;

				data.latitude = target;
				count++;
				
			}
			else if (str[i] == ':' && count == 6) {
				//longtitude
				cout << "count>>" << count << " " << str[i + 2] << endl;
				string single_line = str;
				int found = single_line.find(",");
				string target = single_line.substr(i + 2, found - (i + 2));
				cout << "is this your target?? >>>>>>" << target << endl;

				data.longtitude = target;
				count++;
				
			}
			else if (str[i] == ':' && count == 7) {
				//speed
				cout << "count>>" << count << " " << str[i + 2] << endl;
				string single_line = str;
				int found = single_line.find(",");
				string target = single_line.substr(i + 2, found - (i + 2));
				cout << "is this your target?? >>>>>>" << target << endl;

				data.speed = target;
				count++;

			}
			else if (str[i] == ':' && count == 8) {
				//speed
				cout << "count>>" << count << " " << str[i + 2] << endl;
				string single_line = str;
				int found = single_line.find(",");
				string target = single_line.substr(i + 2, found - (i + 2));
				cout << "is this your target?? >>>>>>" << target << endl << endl << endl;

				data.timestamp = target;
				count++;

			}
			else if (str[i] == ':' && count == 9) {
				//timestamp
				cout << "count>>" << count << endl << "got one package  " << endl;
				count = 1;
				vec.push_back(data);
				//count = 0;
				//input all the material to the vector
				//one single vector consists of components of DATA based on a single timestamp
				cout << "in vec "<<index <<" : " <<"accuracy  " <<vec[index].accuracy << endl << endl;
				cout << "in vec "<<index <<" : " <<"altitude  " <<vec[index].altitude << endl << endl;
				cout << "in vec "<< index << " : " <<"altitudeAccuracy  " <<vec[index].altitudeAccuracy << endl << endl;
				cout << "in vec "<< index << " : " <<"heading  "<<vec[index].heading << endl << endl;
				cout << "in vec "<< index << " : " << "latitude  "<<vec[index].latitude << endl << endl;
				cout << "in vec "<< index << " : " << "longtitude  "<<vec[index].longtitude << endl << endl;
				cout << "in vec "<< index << " : " << "speed  "<< vec[index].speed << endl << endl;
				cout << "in vec "<< index << " : " << "timestamp  "<< vec[index].timestamp << endl << endl;
				cout << "================================================" << endl;
				index++;
				//:를 기준으로 파싱했기 때문에 마지막 패키지 하나는 검사만 하고 담기지 않는다.
				//때문에 total vector size = 실제 들어온 패키지 -1
			}
		}
	}



	double avg_speed = is_avg_speed(vec);//평균 속도
	double total_time = is_total_time(vec);//전체 운전 시간
	int total_over_speed = is_over_speed(vec);//과속 횟수
	int rapid_acc = rapid_speed_change(vec).first;//급가속 횟수
	int rapid_brk = rapid_speed_change(vec).second;//급정거 횟수


	//급가속 기준 = 변화량이 8.5mph =  13.67km.h = 3.79 m/s
	//급감속 기준 = 변화량이 6.5mph = 10.4km/h = 2.88 m/s
	cout << "vector size = " << vec.size() << endl;
	cout << "avg speed = " << avg_speed << " total_time = " << total_time << endl;
	cout << "overspeed_time = " << total_over_speed << endl;
	cout << "rapid acceleration = " << rapid_acc << endl;
	cout << "rapid_brk" << rapid_brk << endl;


	return 0;
}