#include <iostream>
#include <algorithm>
#include "SpeechManager.h"
#include <map>
#include <deque>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>
//#include <random>
using namespace std;

SpeechManager::SpeechManager() {
    this->init_sm();
    this->make_specker();
};

SpeechManager::~SpeechManager() {

};

void SpeechManager::show_menu() {
    cout << "******************************" << endl;
    cout << "********��ӭ�μ��ݽ�����********" << endl;
    cout << "********1.��ʼ�ݽ�����**********" << endl;
    cout << "********2.�鿴�����¼**********" << endl;
    cout << "********3.��ձ�����¼**********" << endl;
    cout << "********0.�˳���������**********" << endl;
    cout << "******************************" << endl;
};

void SpeechManager::exit_sm() {
    cout << "��ӭ�´�ʹ��" << endl;
    exit(0);
}

void SpeechManager::init_sm() {
    v1.clear();
    v2.clear();
    v3.clear();
    m.clear();
    num = 1;
}

void SpeechManager::make_specker() {
    string s = "ABCDEFGHIJKL";
    for (int i = 0; i < s.size(); i++) {
        string name = "ѡ��";
        name += s[i];

        Specker s;
        s.name = name;
        for (int j = 0; j < 2; j++) {
            s.score[j] = 0;
        }
        m.insert(pair<int, Specker>(i + 1, s));
        v1.push_back(i + 1);
    }
}

void SpeechManager::speech_draw() {
    printf("��%d�ֱ���ѡ�����ڳ�ǩ", this->num);
    cout << "�������:" << endl;
    if (num == 1) {
        random_shuffle(v1.begin(), v1.end());
        for (auto p: v1) {
            cout << p << " ";
        }
        cout << endl;

    } else {
        random_shuffle(v2.begin(), v2.end());
        for (auto p: v2) {
            cout << p << " ";
        }
        cout << endl;
    }

}

void SpeechManager::start_speech() {
//    ��һ�ֱ���
//    ��ǩ
    speech_draw();
//    ����
    speech_contest();
//    ��ʾ���
    show_score();
//    �ڶ��ֱ���
    num++;
//    ��ǩ
    speech_draw();
//    ����
    speech_contest();
//    ��ʾ����
    show_score();
//    ������Ϣ
    save_record();
    init_sm();
    make_specker();
};

void SpeechManager::speech_contest() {
    printf("--------------��%d�ֱ�����ʽ��ʼ-------------\n", num);
    map<double, int, greater<>> mm;
    vector<int> vv;
    if (num == 1)vv = v1;
    else vv = v2;
    int people_num = 0;
    for (auto p: vv) {
        people_num++;
        double score = 0;
        deque<double> d;
        for (int i = 0; i < 10; i++) {
            score = rand() % 100 * 100;
            d.push_back(score);
        }
        sort(d.begin(), d.end());
        d.pop_back();
        d.pop_front();
        score = accumulate(d.begin(), d.end(), 0) / d.size();
        mm.insert(make_pair(score, p));
        this->m[p].score[num - 1] = score;
        if (people_num % 6 == 0) {
            printf("��%d��С��ı�������\n", people_num / 6);
            for (auto pp: mm) {
//                printf("��ţ�%d  ������%s �ɼ���%d",pp.second,m[pp.second].name,pp.first);
                cout << "��ţ�" << pp.second << "������" << m[pp.second].name << "�ɼ���" << pp.first << endl;
            }
            int i = 0;
            for (auto pp = mm.begin(); i < 3; i++, pp++) {
                if (num == 1) {
                    v2.push_back((*pp).second);
                } else {
                    v3.push_back((*pp).second);
                }
            }
            mm.clear();
            cout << endl;
        }
    }
}

void SpeechManager::show_score() {
    printf("��%d�ֱ��������������\n", num);
    vector<int> vv;
    if (num == 1)vv = v2;
    else vv = v3;
    for (auto p: vv) {
        cout << "��ţ�" << p << "������" << m[p].name << "�ɼ���" << m[p].score[num - 1] << endl;
    }
    cout << endl;
}

void SpeechManager::save_record() {
    fstream f;
    f.open("test.txt", ios::out | ios::app);
    for (auto p: v3) {
        f << "��ţ�" << p << "������" << m[p].name << "�ɼ���" << m[p].score[1] << endl;
    }
    f.close();
}

void SpeechManager::show_record() {
    fstream f;
    f.open("test.txt", ios::in);
    if (!f.is_open()) {
        cout << "�ļ���ʧ��" << endl;
        exit_sm();
    }
    string s;
    while (getline(f, s)) {
        cout << s << endl;
    }
    f.close();
}

void SpeechManager::clear_record() {
    ofstream f("test.txt", ios::trunc);
    f.close();
}