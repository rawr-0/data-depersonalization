#include <fstream>
#include "string"
#include "vector"

using namespace std;

vector<string> split(string line){
    vector<string> spliter;
    string s;
    if(!line.empty()) {
        for (int i = 0; i < line.size(); i++) {
            if (line[i] != ';')
                s += line[i];
            else
                spliter.push_back(s), s.clear();
        }
        spliter.push_back(s);
    }
    return spliter;
}

string datec(string date){
    string s;
    int q = 0;
    int u = 0;
    for(int i = date.size()-1;date[i] != 'T';i--,q++){}
    for(int i = 0;i<date.size();i++){
        if(u>1 and i < date.size()-q)
            s+=date[i];
        if(date[i] == '.' and u <= 1)
            u++;
    }
    return "*"+s;
}

void anonymization(){
    ifstream in("../table.csv");
    ofstream out("../table_out.csv");
    string s;
    getline(in,s);
    vector<string> line;
    line = split(s);
    out<<line[0]<<";"<<line[1]<<";"<<line[2]<<";"<<line[3]<<";"<<line[4]<<";"<<line[5]
    <<";"<<line[6]<<";"<<line[7]<<";"<<line[8]<<";"<<line[9]<<";"<<line[10]<<";"<<line[11]<<endl;
    while(!in.eof()){
        getline(in,s);
        if(!s.empty()) {
            line = split(s);
            if(!line[0].empty())
            out << "*****;" << "*****;" << "*****;" << "РФ"<<";"<< line[4] << ";" << line[5] << ";" << datec(line[6]) << ";"
                << datec(line[7]) << ";" << "*" << ";" << "*" <<";" << ((stoi(line[10]) > 3000) ? ">2000" : (stoi(line[10]) > 2000) ? ">2000"
                : (stoi(line[10]) > 1000) ? "1000-2000" : (stoi(line[10]) > 0) ? "0-1000" : "er")<<";"<< line[11][0] <<"*********"<<endl;
        }
    }
}