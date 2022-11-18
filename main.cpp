#include <iostream>
#include "k-calculation.cpp"
using namespace std;

int main() {
    cout<<"выбрать метод"<<endl<<"1 - обезличивание"<<endl<<"2 - вычисление K"<<endl;
    int c;
    cin>>c;
    if(c == 1)
        anonymization();
    if(c == 2)
        calculation();
    return 0;
}
