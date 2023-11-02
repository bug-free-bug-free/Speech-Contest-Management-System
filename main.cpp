#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include "SpeechManager.h"
#include "Specker.h"
using namespace std;


int main(){
    SpeechManager sm;
    int choice;
    while(true){
        sm.show_menu();
        cout<<"ÇëÊäÈëÄãµÄÑ¡Ôñ"<<endl;
        cin>>choice;
        switch (choice) {
            case 1:{
                sm.start_speech();
                break;
            }
            case 2:{
                sm.show_record();
                break;
            }
            case 3:{
                sm.clear_record();
                break;
            }
            case 0:{
                sm.exit_sm();
            }
        }
    }

    return 0;
}