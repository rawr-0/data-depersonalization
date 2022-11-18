#include "fstream"
#include "iostream"
#include "vector"
#include "string"
#include "anonimyzation.cpp"

struct line{
    string from;
    string to;
    string date_out;
    string date_in;
    string run_number;
    string carriage_seat;
    string price;
    string card;
    int num;
    int choice;
    line(string a, string b, string c,string d, string e, string f, string g, string h, int choice){
        from = a; to = b; date_out = c; date_in = d; run_number = e;
        carriage_seat = f; price = g; card = h; num = 0;
        this-> choice = choice;
    }

    line(int choice){num = 0;this->choice = choice;}

    string to_string(){
        if(choice == 0)
            return from+" "+to+" "+date_out+" "+date_in+" "+run_number+" "+carriage_seat+
            " "+price+" "+card;
        if(choice == 1)
            return from;
        if(choice == 2)
            return to;
        if(choice == 3)
            return date_out;
        if(choice == 4)
            return date_in;
        if(choice == 5)
            return run_number;
        if(choice == 6)
            return carriage_seat;
        if(choice == 7)
            return price;
        if(choice == 8)
            return card;
        return "ERR";
    }

    bool is_equal(line l){
        string str1 = l.to_string();
        string str2 = to_string();
        if(str1.size() != str2.size())
            return false;
        for(int i = 0;i<=str1.size();i++)
            if(str1[i] != str2[i])
                return false;
        return true;
    }
};

bool in_vec(vector<line>& v,line l){
    for(int i = 0;i<v.size();i++){
        if(v[i].is_equal(l)) {
            v[i].num++;
            return true;
        }
    }
    return false;
}

void calculation(){
    ifstream in("../table_out.csv");
    string mem;
    int choice;
    cout<<"Выбрать quasi идентификатор:"<<endl<<"0 - для всех"<<endl<<"1 - для города отправления"
    <<endl<<"2 - для города прибытия"<<endl<<"3 - для даты отправления"<<endl<<"4 - для даты прибытия"
    <<endl<<"5 - для номера рейса"<<endl<<"6 - для места и вагона"<<endl<<"7 - для цены билета"<<endl<<"8 - для карты"<<endl;
    cin>>choice;
    getline(in,mem);
    vector<line> lines;
    int num = 0;
    while(!in.eof()){
        num++;
        getline(in,mem);
        if(!mem.empty()) {
            vector<string> s = split(mem);
            line l(s[4],s[5],s[6],s[7],s[8],s[9],s[10],s[11],choice);
            if(!in_vec(lines,l))
                lines.push_back(l);
        }
    }
    line line1(choice),line2(choice),line3(choice),line4(choice),line5(choice);
    cout<<"уникальные строки vvv"<<endl;
    for(int i = 0;i<lines.size();i++){
        if(lines[i].num == 0)
            cout<<lines[i].to_string()<<endl;
        if(line1.num <= lines[i].num)
            line5 = line4, line4 = line3, line3 = line2, line2 = line1, line1 = lines[i];
        else
            if(line2.num <= lines[i].num)
                line5 = line4, line4 = line3, line3 = line2, line2 = lines[i];
            else
                if(line3.num <= lines[i].num)
                    line5 = line4, line4 = line3, line3 = lines[i];
                else
                if(line4.num <= lines[i].num)
                    line5 = line4, line4 = lines[i];
                else
                if(line5.num <= lines[i].num)
                    line5 = lines[i];
    }
    cout<<"конец уникальных строк ^^^"<<endl<<endl;

    cout<<line1.num+1<<" -k  "<<double(line1.num+1)/num<<" - % "<<line1.to_string()<<endl
            <<line2.num+1<<" -k  "<<double(line2.num+1)/num<<" - % "<<line2.to_string()<<endl
            <<line3.num+1<<" -k  "<<double(line3.num+1)/num<<" - % "<<line3.to_string()<<endl
            <<line4.num+1<<" -k  "<<double(line4.num+1)/num<<" - % "<<line4.to_string()<<endl
            <<line5.num+1<<" -k  "<<double(line5.num+1)/num<<" - % "<<line5.to_string()<<endl;
}