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
    cout << "********欢迎参加演讲比赛********" << endl;
    cout << "********1.开始演讲比赛**********" << endl;
    cout << "********2.查看往届记录**********" << endl;
    cout << "********3.清空比赛记录**********" << endl;
    cout << "********0.退出比赛程序**********" << endl;
    cout << "******************************" << endl;
};

void SpeechManager::exit_sm() {
    cout << "欢迎下次使用" << endl;
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
        string name = "选手";
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
    printf("第%d轮比赛选手正在抽签", this->num);
    cout << "结果如下:" << endl;
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
//    第一轮比赛
//    抽签
    speech_draw();
//    比赛
    speech_contest();
//    显示结果
    show_score();
//    第二轮比赛
    num++;
//    抽签
    speech_draw();
//    比赛
    speech_contest();
//    显示比赛
    show_score();
//    保存信息
    save_record();
    init_sm();
    make_specker();
};

void SpeechManager::speech_contest() {
    printf("--------------第%d轮比赛正式开始-------------\n", num);
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
            printf("第%d个小组的比赛名次\n", people_num / 6);
            for (auto pp: mm) {
//                printf("编号：%d  姓名：%s 成绩：%d",pp.second,m[pp.second].name,pp.first);
                cout << "编号：" << pp.second << "姓名：" << m[pp.second].name << "成绩：" << pp.first << endl;
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
    printf("第%d轮比赛晋级情况如下\n", num);
    vector<int> vv;
    if (num == 1)vv = v2;
    else vv = v3;
    for (auto p: vv) {
        cout << "编号：" << p << "姓名：" << m[p].name << "成绩：" << m[p].score[num - 1] << endl;
    }
    cout << endl;
}

void SpeechManager::save_record() {
    fstream f;
    f.open("test.txt", ios::out | ios::app);
    for (auto p: v3) {
        f << "编号：" << p << "姓名：" << m[p].name << "成绩：" << m[p].score[1] << endl;
    }
    f.close();
}

void SpeechManager::show_record() {
    fstream f;
    f.open("test.txt", ios::in);
    if (!f.is_open()) {
        cout << "文件打开失败" << endl;
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