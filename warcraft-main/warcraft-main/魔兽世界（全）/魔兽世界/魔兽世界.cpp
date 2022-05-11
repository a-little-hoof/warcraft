#include <iostream>
#include<cstring>
using namespace std;

class headquarter;
class warrior;
const int warrior_num=5;

class warrior{
    private:
        int totalNo;
        int No;
        headquarter * pheadquarter;
    public:
        static char names[warrior_num][10];
        static int warrior_life_value[warrior_num];
        warrior(headquarter * p,int totalw,int w_kind);
    friend class headquarter;
};
char warrior::names[warrior_num][10]={"dragon","ninja","iceman","lion","wolf"};
int warrior::warrior_life_value[warrior_num]={0};
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
    pw[totalw]=new warrior(this,totalw,w_kind[order[cur]]);//这里一开始加了warrior，是脑残吗...
    print(time);
    cur++;
    if(cur==5)
        cur=0;
    return 1;
}
void headquarter::print(int time){
    if(color)
        printf("%03d red %s %d born with strength %d,%d %s in red headquarter\n",time,warrior::names[order[cur]],totalw,warrior::warrior_life_value[order[cur]],w_kind[order[cur]],warrior::names[order[cur]]);
    else
        printf("%03d blue %s %d born with strength %d,%d %s in blue headquarter\n",time,warrior::names[order[cur]],totalw,warrior::warrior_life_value[order[cur]],w_kind[order[cur]],warrior::names[order[cur]]);
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