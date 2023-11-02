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
    void speech_draw();//��ǩ
    void speech_contest();//����
    void show_score();//չʾ�ɼ�
    void save_record();//����ɼ�
    void show_record();//չʾ�ɼ�
    void clear_record();//��ռ�¼
public:
    vector<int> v1;//��һ�ֱ�������
    vector<int> v2;//�ڶ��ֱ�������
    vector<int> v3;//����ʤ������
    map<int,Specker> m;
    int num;//��ʱ�ı�������
};


#endif