#include <iostream>
#include <string>
#include <fstream>
#include <random>

using namespace std;

struct Bulka
{
    string name;
    string tname;
    string fname;
    bool   gender;
    bool   fertil;
    int    chaild;
    int    arge;
    int    xp;
};

struct Stat
{
    int day;
    int burn;
    int death = 0;
    int Arg[1000];
    int Chil[1000];
};

//массив с булочками
Bulka nas[100]{
    {"Fin", "Tik", "Fer", false, true, 0, 1, 3}, {"Tit", "Tou", "Fos", true, true, 0, 1, 3},
    {"Foc", "Tik", "Fer", false, true, 0, 1, 3}, {"Tos", "Tou", "Fos", true, true, 0, 1, 3}
};

Stat Itigo;

string name[]{ "ari", "otu", "ery", "ood", "ute", "ite", "eur", "opu", "ujo", "asu" };
int live = 4; //число живых булочек
int day; //счёт дней жизни цивилизации
int god = 0; //для божественных решений
int tlive = live;

void Burn() {

}

int main()
{
    //случайные числа
    random_device rd;
    mt19937 gen(rd());

    //основной цикл
    for (day = 1; day > 0; day++)
    {
        system("cls");
        cout << "dau " << day << "\n";
        Itigo.day = day;

        //пересчёт булочек
        cout << "\n In live:\n";
        for (int i = 0; i < live; i++)
        {
            cout << i + 1 << ". " << nas[i].name << " " << nas[i].tname << " " << nas[i].fname << "\n"
                 << "Gender: " << nas[i].gender << " Arge: " << nas[i].arge << " Chaild: " << nas[i].chaild << "\n\n";
        }

        //размножение
        cout << "\n Burn:\n";
        tlive = live;
        int fail = 0;

        for (int rod = 0; rod < live / 2; rod = rod)
        {
            //на случай зацикливания
            if (fail > 10) break;

            //подбор пары
            uniform_int_distribution<> RandPart(0, live - 1);
            int n = RandPart(gen);
            int h = RandPart(gen);

            //проверка партнёров на совместимость
            //на разность пола
            if (n != h && nas[n].gender != nas[h].gender)
            {
                //на родство(если есть другие представители)
                if ((nas[n].fertil > 0 && nas[h].fertil > 0 &&
                    nas[n].name != nas[h].tname && nas[n].name != nas[h].fname &&
                    nas[h].name != nas[n].tname && nas[h].name != nas[n].fname &&
                    nas[n].tname != nas[h].tname && nas[n].fname != nas[h].fname) || fail > 5)
                {
                    //определение помёта
                    uniform_int_distribution<> RandChaild(1, 5);
                    int C = RandChaild(gen);
                    //определение характеристик помёта
                    uniform_int_distribution<> RandGend(0, 1);
                    int G = RandGend(gen);
                    uniform_int_distribution<> RandName(0, 6);
                    int N = RandName(gen);
                    //количество детей
                    if (C < 5)
                    {
                        //пол ребёнка
                        if (G < 1)
                        {
                            //если n - tru
                            if (nas[n].gender > 0) nas[tlive] = { "F" + name[N], nas[n].name, nas[h].name,
                                                                  false, false, 0, 0, 3 };
                            else nas[tlive] = { "F" + name[N], nas[h].name, nas[n].name,
                                                false, false, 0, 0, 3 };
                        }
                        else
                        {
                            if (nas[n].gender > 0) nas[tlive] = { "T" + name[N], nas[n].name, nas[h].name,
                                                                  true, false, 0, 0, 3 };
                            else nas[tlive] = { "T" + name[N], nas[h].name, nas[n].name,
                                                true, false, 0, 0, 3 };
                        }
                        cout << nas[n].name << " " << nas[n].tname << " " << nas[n].fname << "\n";
                        cout << "    &&\n";
                        cout << nas[h].name << " " << nas[h].tname << " " << nas[h].fname << "\n";
                        cout << "    ==\n";
                        cout << nas[tlive].name << " " << nas[tlive].tname << " " << nas[tlive].fname << "\n\n";
                        nas[n].chaild++;
                        nas[h].chaild++;
                        tlive++;
                    }
                    else
                    {
                        cout << nas[n].name << " " << nas[n].tname << " " << nas[n].fname << "\n";
                        cout << "    &&\n";
                        cout << nas[h].name << " " << nas[h].tname << " " << nas[h].fname << "\n";
                        cout << "    ==\n";
                        int ch = tlive;
                        if (nas[n].gender > 0)
                        {
                            nas[ch] = { "F" + name[N], nas[n].name, nas[h].name,
                                        false, false, 0, 0, 3 };
                            cout << nas[ch].name << " " << nas[ch].tname << " " << nas[ch].fname << "\n";
                            ch++;
                            nas[ch] = { "T" + name[N], nas[n].name, nas[h].name,
                                           true, false, 0, 0, 3 };
                            cout << nas[ch].name << " " << nas[ch].tname << " " << nas[ch].fname << "\n\n";
                            ch++;
                        }
                        else
                        {
                            nas[ch] = { "F" + name[N], nas[h].name, nas[n].name,
                                        false, false, 0, 0, 3 };
                            cout << nas[ch].name << " " << nas[ch].tname << " " << nas[ch].fname << "\n";
                            ch++;
                            nas[ch] = { "T" + name[N], nas[h].name, nas[n].name,
                                        true, false, 0, 0, 3 };
                            cout << nas[ch].name << " " << nas[ch].tname << " " << nas[ch].fname << "\n\n";
                            ch++;
                        }
                        tlive = ch;
                        nas[n].chaild = nas[n].chaild + 2;
                        nas[h].chaild = nas[h].chaild + 2;
                    }
                    rod++;
                    Itigo.burn++;
                }
            }
            else fail++;
        }

        live = tlive;

        //смерть
        cout << "\n Death:\n";
        tlive = live;
        for (int i = 0; i < live; i++)
        {
            uniform_int_distribution<> RandDmg(2, 5);//продолжительность жизни
            int deat = RandDmg(gen);
            //если прожил сверх - -хр
            if (nas[i].arge >= deat)
            {
                nas[i].xp--;
                if (nas[i].xp < 1)
                {
                    cout << i + 1 << ". " << nas[i].name << " " << nas[i].tname << " " << nas[i].fname << "\n"
                         << "Gender: " << nas[i].gender << " Arge: " << nas[i].arge << " Chaild: " << nas[i].chaild << "\n\n";
                    Itigo.Arg[Itigo.death] = nas[i].arge;
                    tlive--;
                    Itigo.death++;

                    nas[live] = nas[i];
                    nas[i] = nas[live - 1];
                    nas[live - 1] = nas[live];
                }
            }
        }
        live = tlive;

        //окончание в случае вымирания
        if (live < 1)
        {
            cout << "Death live.\n"; //если все булочки умерли
            cout << "Day: " << Itigo.day << "\n";
            cout << "Burn: " << Itigo.burn << "\n";
            cout << "Deat: " << Itigo.death << "\n";
            int s = 0;
            for (int i = 0; i < Itigo.death; i++)
            {
                s = s + Itigo.Arg[i];
                cout << " " << Itigo.Arg[i];
            }
            cout << "\n Sr. arge: " << s / Itigo.death;

            break;
        }
        else
            if (god < 2)
            {
                cin >> god;
                switch (god)
                {
                case 1:
                    return 0;
                default:
                    //обновление возраста и фертильности
                    for (int i = 0; i < live; i++)
                    {
                        nas[i].arge++;
                        nas[i].fertil = true;
                    }
                    break;

                }
            }
            else
            {
                //обновление возраста и фертильности
                for (int i = 0; i < live; i++)
                {
                    nas[i].arge++;
                    nas[i].fertil = true;
                }
            }
    }
}
