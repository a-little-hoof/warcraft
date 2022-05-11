#include <iostream>
#include<cstring>
using namespace std;

class headquarter;
class warrior;
#define warrior_num 5
#define weapon_num 3

class weapon{
    int type;
    public:
        static char weapon_name[weapon_num][10];
        weapon(int i=0):type(i){};
        weapon & operator=(int i){
            type=i;
            return *this;
        }
        operator int(){
            return type;
        }
};

class warrior{
    protected:
        int totalNo;
        int No;
        headquarter * pheadquarter;
    public:
        static char names[warrior_num][10];
        static int warrior_life_value[warrior_num];
        warrior(headquarter * p,int totalw,int w_kind);
    virtual ~warrior(){}
    virtual void print_result()=0;
    friend class headquarter;
};
class dragon:public warrior{
    weapon wp;
    double courage;
    public:
        void print_result(){
            printf("It has a %s,and it's morale is %.2lf\n",weapon::weapon_name[wp],courage);
        }
        dragon(headquarter * p,int totalw,int w_kind);
};
class ninja:public warrior{
    weapon wp[2];
    public:
        void print_result(){
            printf("It has a %s and a %s\n",weapon::weapon_name[wp[0]],weapon::weapon_name[wp[1]]);
        }
        ninja(headquarter * p,int totalw,int w_kind):warrior(p,totalw,w_kind){
            wp[0]=totalw%3;
            wp[1]=(totalw+1)%3;
        }
};
class iceman:public warrior{
    weapon wp;
    public:
        void print_result(){
            printf("It has a %s\n",weapon::weapon_name[wp]);
        }
        iceman(headquarter * p,int totalw,int w_kind):warrior(p,totalw,w_kind),wp(totalw%3){}
};
class lion:public warrior{
    int loyalty;
    public:
        void print_result(){
            printf("It's loyalty is %d\n",loyalty);
        };
        lion(headquarter * p,int totalw,int w_kind);
};
class wolf:public warrior{
    public:
        void print_result(){};
        wolf(headquarter * p,int totalw,int w_kind):warrior(p,totalw,w_kind){}
};
char warrior::names[warrior_num][10]={"dragon","ninja","iceman","lion","wolf"};
int warrior::warrior_life_value[warrior_num]={0};
char weapon::weapon_name[weapon_num][10]={"sword","bomb","arrow"};
warrior::warrior(headquarter * p,int totalw,int w_kind):pheadquarter(p),totalNo(totalw),No(w_kind){};

class headquarter{
    private:
        int totalvalue;
        int order[5];
        bool color;
        bool enough_value;
        int cur;
        int totalw;
        int w_kind[warrior_num];
        warrior * pw[1000];//定义了一个对象指针数组，要注意每次清理
    public:
        headquarter(int m,bool color_);
        ~headquarter();
        bool produce(int time);
        bool canproduce();
        void print(int time);
        int get_total_value(){
            return totalvalue;
        }
};
headquarter::headquarter(int m,bool color_):color(color_),totalvalue(m){
    color=color_;
    if(color==1)
    {
        memset(order,0,sizeof(order));
        int tmp[5]={2,3,4,1,0};
        memcpy(order,tmp,sizeof(tmp));
    }
    else
    {
        memset(order,0,sizeof(order));
        int tmp[5]={3,0,1,2,4};
        memcpy(order,tmp,sizeof(tmp));
    }
    totalvalue=m;
    enough_value=1;
    cur=0;
    totalw=0;
    memset(pw,0,sizeof(pw));
    memset(w_kind,0,sizeof(w_kind));
}

headquarter::~headquarter(){
    for(int i=1;i<=totalw;i++)
        delete pw[i];
}
bool headquarter::canproduce(){
    for(int i=0;i<5;i++)
        if(totalvalue-warrior::warrior_life_value[i]>=0)
            return 1;
    return 0;
}
bool headquarter::produce(int time){
    if(enough_value==0)
        return 0;
    if(canproduce()==0)
    {
        enough_value=0;
        if(color==1)
            printf("%03d red headquarter stops making warriors\n",time);
        else
            printf("%03d blue headquarter stops making warriors\n",time);
        return 1;
    }
    while(totalvalue<warrior::warrior_life_value[order[cur]])
    {
        cur++;
        if(cur==5)
            cur=0;
    }
    totalvalue-=warrior::warrior_life_value[order[cur]];
    totalw++;
    w_kind[order[cur]]+=1;
    switch(order[cur]){
        case 0:
            pw[totalw]=new dragon(this,totalw,w_kind[order[cur]]);
            break;
        case 1:
            pw[totalw]=new ninja(this,totalw,w_kind[order[cur]]);
            break;
        case 2:
            pw[totalw]=new iceman(this,totalw,w_kind[order[cur]]);
            break;
        case 3:
            pw[totalw]=new lion(this,totalw,w_kind[order[cur]]);
            break;
        case 4:
            pw[totalw]=new wolf(this,totalw,w_kind[order[cur]]);
            break;//switch怎么能忘加break，废物点心
    }
    print(time);
    cur++;
    if(cur==5)
        cur=0;
    return 1;
}
void headquarter::print(int time){
    if(color)
    {
        printf("%03d red %s %d born with strength %d,%d %s in red headquarter\n",time,warrior::names[order[cur]],totalw,warrior::warrior_life_value[order[cur]],w_kind[order[cur]],warrior::names[order[cur]]);
        pw[totalw]->print_result();
    }
    else
    {
        printf("%03d blue %s %d born with strength %d,%d %s in blue headquarter\n",time,warrior::names[order[cur]],totalw,warrior::warrior_life_value[order[cur]],w_kind[order[cur]],warrior::names[order[cur]]);
        pw[totalw]->print_result();
    }
}
lion::lion(headquarter * p,int totalw,int w_kind):warrior(p,totalw,w_kind){
            loyalty=pheadquarter->get_total_value();
        }
dragon::dragon(headquarter * p,int totalw,int w_kind):warrior(p,totalw,w_kind),wp(totalw%3){
            courage=(double)pheadquarter->get_total_value()/warrior_life_value[0];
        }
int main()
{
    int m;
    int CaseNo;
    int t;
    cin>>t;
    for(int o=1;o<=t;o++)
    {
        CaseNo=o;
        printf("Case:%d\n",CaseNo);
        cin>>m;
        headquarter red(m,1);
        headquarter blue(m,0);
        for(int i=0;i<5;i++)
            cin>>warrior::warrior_life_value[i];
        int time=0;
        while(1)
        {
            int tmp1=red.produce(time);
            int tmp2=blue.produce(time);
            if(tmp1==0&&tmp2==0)
                break;
            time++;
        }
    }
    return 0;
}
