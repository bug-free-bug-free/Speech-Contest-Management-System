#ifndef UNTITLED2_SPEECHMANAGER_H
#define UNTITLED2_SPEECHMANAGER_H
#include <iostream>
#include "Specker.h"
#include <vector>
#include <map>
using namespace std;
class SpeechManager{
public:
    SpeechManager();
    ~SpeechManager();
    void show_menu();
    void exit_sm();
    void init_sm();
    void make_specker();
    void start_speech();
    void speech_draw();//抽签
    void speech_contest();//比赛
    void show_score();//展示成绩
    void save_record();//保存成绩
    void show_record();//展示成绩
    void clear_record();//清空记录
public:
    vector<int> v1;//第一轮比赛的人
    vector<int> v2;//第二轮比赛的人
    vector<int> v3;//最终胜出的人
    map<int,Specker> m;
    int num;//此时的比赛轮数
};


#endif