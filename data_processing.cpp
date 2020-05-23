#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;


struct DATA
{
	int accuracy;
	int altitude;
	int altitudeAccuracy;
	float heading;
	float latitude;
	float longtitude;
	float speed;
	unsigned int timestamp;
};
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
		cout << str << " "<< "line finished"<<endl<<endl;
		int key = 1;
		for (int i = 0; i < 100; i++) {
			
			if (str[i] == '"') {
				
				int ending_point = 0;
				if (key == 1) {
					cout << endl<<endl<<"new line starting here" << endl << endl;
					cout << "open " << str[i]<<str[i+1]<<str[i+2]<<str[i+3]<<str[i+4]<< endl;
					cout << str << endl;
				}
				
				if(key==-1) {
					cout << "close" << str[i] << endl;
					ending_point = i;
				}
				key = key * -1;
			}
			///////////////
			if (str[i] == ':'&& count ==0) {
				cout << "count value " << count << endl;
				count++;
			}
			//////////////
			else if (str[i] == ':' && count ==1) {
				//accuracy
				cout << "count>>" << count << " " << str[i + 2] << endl << endl;
				data.accuracy = str[i + 2] - '0';
				count++;
				
			}
			else if (str[i] == ':' && count == 2) {
				//altitude
				cout << "count>>" << count << " " << str[i + 2] << endl << endl;
				data.altitude = str[i + 2] - '0';
				count++;
				
			}
			else if (str[i] == ':' && count == 3) {
				//altitudeAccuracy
				cout << "count>>" << count << " " << str[i + 2] << endl << endl;
				data.altitudeAccuracy = str[i + 2] - '0';
				count++;
				
			}
			else if (str[i] == ':' && count == 4) {
				//heading
				cout << "count>>" << count << " " << str[i + 2] << endl << endl;
				data.heading = str[i + 2] - '0';
				count++;
				
			}
			else if (str[i] == ':' && count == 5) {
				//latitude
				cout << "count>>" << count << " " << str[i + 2] << endl << endl;
				data.latitude = str[i + 2] - '0';
				count++;
				
			}
			else if (str[i] == ':' && count == 6) {
				//longtitude
				cout << "count>>" << count << " " << str[i + 2] << endl << endl;
				data.longtitude = str[i + 2] - '0';
				count++;
				
			}
			else if (str[i] == ':' && count == 7) {
				//speed
				cout << "count>>" << count << " " << str[i + 2] << endl << endl;
				data.speed = str[i + 2] - '0';
				count++;

			}
			else if (str[i] == ':' && count == 8) {
				//timestamp
				cout << "count>>" << count << " " << str[i + 2] << endl << endl;
				data.timestamp = str[i + 2] - '0';
				vec.push_back(data);
				//count = 0;
				cout << "in vec "<<index <<" : " << vec[index].accuracy << endl << endl;
				cout << "in vec "<<index <<" : " << vec[index].altitude << endl << endl;
				cout << "in vec "<< index << " : " <<vec[index].altitudeAccuracy << endl << endl;
				cout << "in vec "<< index << " : " << vec[index].heading << endl << endl;
				cout << "in vec "<< index << " : " << vec[index].latitude << endl << endl;
				cout << "in vec "<< index << " : " << vec[index].longtitude << endl << endl;
				cout << "in vec "<< index << " : " << vec[index].speed << endl << endl;
				cout << "in vec "<< index << " : " << vec[index].timestamp << endl << endl;
				index++;
			}
		}
	}
	return 0;
}