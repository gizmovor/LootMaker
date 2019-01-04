#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;


class Stat{
public:
        string name;
        int weight;
        int value;

};
vector<Stat> stats;
vector<Stat> item;
vector<Stat> resistances;
Stat s;
int nb_stat = 0;
int tiers = 0;
bool cont = true;
bool res_here;
bool armor_here;
bool crit_here;
string res;
int mini;
int maxi;
int modulo;
int contexte;
int moyenne_res;
int first_res;
int nb_res;
int nb_res_min;
void fill_modulo(int i){
    contexte = maxi;
    modulo = 0;
    if(item[i].name == "Armure"){


        /*if(crit_here){
            contexte += 20 + ((nb_stat - 2) * 10);
        }
        else{
            contexte += (nb_stat - 1) * 10;
        }

            modulo = tiers + 5 + contexte/10;*/
        if(tiers == 1){
            modulo = (tiers + 1) + (tiers + 1) -1;
        }
        else{
            modulo = tiers + tiers -1;
        }



    }
    else if(item[i].name == "Critique"){
        if(armor_here){
            contexte += 50 + ((nb_stat - 2) * 15);
        }
        else{
            contexte += (nb_stat - 1) * 15;
        }
        modulo = 11 + contexte/2;
    }
    else{
        if(armor_here == true and crit_here == false){
            contexte += 50 + ((nb_stat - 2) * 15);
        }
        else if(armor_here == true and crit_here == true){
            contexte += 70 + ((nb_stat - 3) * 15);
        }
        else if(armor_here == false and crit_here == true){
            contexte += 20 + ((nb_stat - 2) * 15);
        }
        else{
            contexte += (nb_stat - 1) * 15;
        }
        modulo = 4 + contexte/5;
    }


};

void random_stats(){
    int somme = -1000;
    while(somme < mini or somme > maxi){
        somme = -1000;
        for(int i=0;i<item.size();i++){
            fill_modulo(i);
            if(item[i].name == "Armure"){
                if(tiers == 1){
                    item[i].value = (rand() % modulo) - (tiers + 1) + 1;
                }
                else{
                    item[i].value = (rand() % modulo) - tiers + 1;
                }

            }
            else if(item[i].name == "Critique"){
                item[i].value = (rand() % modulo) - 10;

            }
            else{
                item[i].value = (rand() % modulo) - 3;
                item[i].value = item[i].value * 5;

            }
            if(i==0){
                somme = item[i].value * item[i].weight;
            }
            else{
                somme += item[i].value * item[i].weight;
            }


            //cout << item[i].name <<  " / somme = " << somme << " / modulo = " << modulo << " / contexte = " << contexte <<  endl;
        }
    }


};

void random_resistances(){
    int moyenne = -1000;
    while(moyenne != moyenne_res * resistances.size()){
        moyenne = -1000;
        for(int i=first_res;i<item.size();i++){
            contexte = abs(moyenne_res * resistances.size());
            contexte += (nb_res) * 30;
            modulo = 3 + contexte/5;
            item[i].value = (rand() % modulo) - 6;
            item[i].value = item[i].value * 5;
            //item[i].value = (rand() % ((moyenne_res)+51)) - 10;
            //item[i].value = item[i].value * 5;

            if(i == first_res){
                moyenne = item[i].value;
            }
            else{
                moyenne += item[i].value;
            }



        }
        //cout << " moyenne 1 : " << moyenne << endl;
        //moyenne = int(moyenne / resistances.size());
        //cout << " moyenne 2 : " << moyenne << endl;

    }



};

void affiche_item(){

        cout << "//////////////////////////////////////////////////////////////////" << endl;
        cout << "Tiers : " << tiers << endl;
        cout << "Nombre de stats : " << nb_stat << endl;
        cout << "//////////////////////////////////////////////////////////////////" << endl;
        for(int i=0;i<item.size();i++){
            cout << item[i].name << " " << item[i].value << endl;
        }
        cout << "//////////////////////////////////////////////////////////////////" << endl;


};

int main()
{



    s.value = 0;
    s.name = "Armure";
    s.weight = 10;
    stats.push_back(s);
    s.name = "Critique";
    s.weight = 2;
    stats.push_back(s);
    s.name = "Toucher";
    s.weight = 1;
    stats.push_back(s);
    s.name = "Esquive";
    s.weight = 1;
    stats.push_back(s);
    s.name = "Resistances";
    s.weight = 1;
    stats.push_back(s);

    //vector resistances
    s.name = "Resistance Bleed";
    s.weight = 1;
    resistances.push_back(s);
    s.name = "Resistance Blight";
    s.weight = 1;
    resistances.push_back(s);
    s.name = "Resistance Poison";
    s.weight = 1;
    resistances.push_back(s);
    s.name = "Resistance Stun";
    s.weight = 1;
    resistances.push_back(s);
    s.name = "Resistance Move";
    s.weight = 1;
    resistances.push_back(s);
    s.name = "Resistance Maladie";
    s.weight = 1;
    resistances.push_back(s);
    nb_res = 0;

    srand(time(NULL));
    cout << "tiers de l'item ?" << endl;
    cout << "0:random / 1: mediocre / 2: commun / 3:rare / 4:epique / 5:legendaire  / any : quitter" << endl;
    cin >> res;cin.ignore();
    if(res == "0"){
        tiers = 0;
    }
    else if(res == "1"){
        tiers = 1;
    }
    else if(res == "2"){
        tiers = 2;
    }
    else if(res == "3"){
        tiers = 3;
    }
    else if(res == "4"){
        tiers = 4;
    }
    else if(res == "5"){
        tiers = 5;
    }
    else{
        cont = false;
    }

    while(cont == true){
        item.clear();
        res_here = false;
        armor_here = false;
        crit_here = false;
        moyenne_res = 0;


        cout << " nombre de stats ? entre 0 et 5 , 0 etant random " << endl;
        cin >> nb_stat;cin.ignore();

        if(tiers == 0){
            tiers = rand()%5 +1;

        }
        if(nb_stat == 0){
            nb_stat = rand()%5 +1;
        }
        if(nb_stat == 5){
            for(int i=0;i<5;i++){
                item.push_back(stats[i]);
            }
            res_here = true;
            armor_here = true;
            crit_here = true;
        }
        else{
            while(item.size() < nb_stat){
                int i = rand() %5;
                bool exist = false;
                for(int j=0;j<item.size();j++){
                    if(item[j].name == stats[i].name){
                        exist = true;
                    }
                }
                if(exist == false){
                    item.push_back(stats[i]);
                    if(stats[i].name == "Armure"){
                        armor_here = true;
                    }
                    else if(stats[i].name == "Critique"){
                        crit_here = true;

                    }
                    else if(stats[i].name == "Resistances"){
                        res_here = true;
                    }
                }
            }
        }
        switch(tiers){
        case 1:
            mini = -5;
            maxi = 5;
            break;

        case 2:
            mini = 5;
            maxi = 10;
            break;
        case 3:
            mini = 10;
            maxi = 20;
            break;
        case 4:
            mini = 20;
            maxi = 30;
            break;

        case 5:
            mini = 30;
            maxi = 40;
            break;
        }

        random_stats();
        affiche_item();
        if(res_here == true){

            int found;
            for(int i=0;i<item.size();i++){
                if(item[i].name == "Resistances"){
                    moyenne_res = item[i].value;
                    found = i;
                }
            }

            item.erase(item.begin()+found);
            first_res = item.size();

            cout << "res unique("  << int(moyenne_res * resistances.size()) <<")  / reroll les res?" << endl;
            cout << " 0 : random , 1 ,2 ,3 ,4 ,5 ,6  , any : non " << endl;
            cin >> res;cin.ignore();
            nb_res_min = ceil(int(moyenne_res * resistances.size()) / -30);
            if(res == "0"){
                nb_res = rand()%6 +1;
            }
            else if(res == "1"){
                nb_res = 1;
                res = "o";
            }
            else if(res == "2"){
                nb_res = 2;
                res = "o";
            }
            else if(res == "3"){
                nb_res = 3;
                res = "o";
            }
            else if(res == "4"){
                nb_res = 4;
                res = "o";
            }
            else if(res == "5"){
                nb_res = 5;
                res = "o";
            }
            else if(res == "6"){
                nb_res = 6;
                res = "o";
            }
            else{
                res = "n";
            }
            if(nb_res < nb_res_min and res == "o"){
                nb_res = nb_res_min;
                cout << "le nombre de res est trop bas, il a ete change au minimum requis : " << nb_res << endl;
            }
            while(res == "o" or res == "O" or res == "0"){

                if(nb_res == 6){
                    for(int i=0;i<6;i++){
                        item.push_back(resistances[i]);
                    }
                }
                else{
                    while(item.size() < nb_stat -1 + nb_res){
                        int i = rand() %6;
                        bool exist = false;
                        for(int j=first_res;j<item.size();j++){
                            if(item[j].name == resistances[i].name){
                                exist = true;
                            }
                        }
                        if(exist == false){
                            item.push_back(resistances[i]);
                        }
                    }
                }
                random_resistances();

                affiche_item();
                cout << "reroll les res a nouveau? O/N" << endl;
                cin >> res;cin.ignore();
                item.erase(item.begin()+first_res, item.end());
            }


        }
        cout << "tiers de l'item ?" << endl;
        cout << "0:random / 1: mediocre / 2: commun / 3:rare / 4:epique / 5:legendaire  / any : quitter" << endl;
        cin >> res;cin.ignore();
        if(res == "0"){
            tiers = 0;
        }
        else if(res == "1"){
            tiers = 1;
        }
        else if(res == "2"){
            tiers = 2;
        }
        else if(res == "3"){
            tiers = 3;
        }
        else if(res == "4"){
            tiers = 4;
        }
        else if(res == "5"){
            tiers = 5;
        }
        else{
            cont = false;
        }
    }



    return 0;
}
