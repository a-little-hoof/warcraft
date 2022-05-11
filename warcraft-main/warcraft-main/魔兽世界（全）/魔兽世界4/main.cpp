#include<fstream>
#include<iostream>
#include<cstring>
#include<stdio.h>
using namespace std;


class headquarter;
class warrior;
class city;
class weapon;
#define warrior_num 5
#define weapon_num 3
city * pcity[25];
int m,n,r,k,T;
bool endofgame=0;


class weapon{
public:
    int type;
    weapon(int _type):type(_type){};
};
class sword:public weapon{
public:
    int force;
    sword(int _force):force(_force),weapon(0){};
};

class bomb:public weapon{
public:
    bomb():weapon(1){};
};
class arrow:public weapon{
public:
    int R;
    int used_count;
    arrow():weapon(2),R(r),used_count(0){};
};

class headquarter{
    int totalvalue;
    int order[5];
    bool color;
    int cur;
    int totalwa;
    warrior * pw[1000];
    city * phcity;
    int take_the_other;
public:
    headquarter(int _totalvalue,bool _color);
    void produce(int time);
    void printproduced(int time);
    friend class warrior;
    friend class dragon;
    friend class ninja;
    friend class iceman;
    friend class lion;
    friend class wolf;
    friend class timeline;
};
class city{
    warrior * pcityw[2];
    int flag_color;
    int number;
    int element;
    bool jb;
    bool jr;
public:
    city(int _number){
        number=_number;
        flag_color=0;
        memset(pcityw,0,sizeof(pcityw));
        element=0;
        jb=0;
        jr=0;
    }
    void battle(int time);
    friend class headquarter;
    friend class timeline;
    friend class warrior;
    friend class dragon;
    friend class ninja;
    friend class iceman;
    friend class lion;
    friend class wolf;
};

class warrior{
protected:
    int totalNo;
    headquarter * pheadquarter;
    int element;
    int ATK;
    city * plocation;
    bool gone;
    int type;
    weapon * wp0,*wp1,*wp2;
public:
    static int warrior_life_value[warrior_num];
    static int warrior_ATK[warrior_num];
    static char names[warrior_num][10];
    warrior(int _totalNo,headquarter * _pheadquarter,int _type);
    virtual void march(int time){};
    void arrow_attack(warrior* pattacked,int time);
    void print_weapon(int time);
    void attack(warrior * pattacked);
    void fight_back(warrior * pattacked);
    friend class timeline;
    friend class city;
};
class dragon:public warrior{
    double courage;
public:
    void march(int time);
    dragon(headquarter * ppheadquarter,int totalwarr):warrior(totalwarr,ppheadquarter,0){
        courage=(double)(pheadquarter->totalvalue)/warrior_life_value[0];
        ATK=warrior_ATK[0];
        element=warrior_life_value[0];
        int tmp=totalNo%3;
        switch(tmp){
            case 0:
            wp0=new sword(ATK/5);break;
            case 1:
            wp1=new bomb();break;
            case 2:
            wp2=new arrow();break;
        }
        if(ATK/5==0)
            wp0=NULL;
    };
    friend class city;
    friend class timeline;
};
class ninja:public warrior{
public:
    void march(int time);
    ninja(headquarter * ppheadquarter,int totalwarr):warrior(totalwarr,ppheadquarter,1){
        ATK=warrior_ATK[1];
        element=warrior_life_value[1];
        int tmp=totalNo%3;
        switch(tmp){
            case 0:
            wp0=new sword(ATK/5);wp1=new bomb();break;
            case 1:
            wp1=new bomb();wp2=new arrow();break;
            case 2:
            wp2=new arrow();wp0=new sword(ATK/5);break;
        }
        if(ATK/5==0)
            wp0=NULL;
    };
    
};
class iceman:public warrior{
    bool even_move;
public:
    void march(int time);
    iceman(headquarter * ppheadquarter,int totalwarr):warrior(totalwarr,ppheadquarter,2){
        ATK=warrior_ATK[2];
        even_move=0;
        element=warrior_life_value[2];
        int tmp=totalNo%3;
        switch(tmp){
            case 0:
            wp0=new sword(ATK/5);break;
            case 1:
            wp1=new bomb();break;
            case 2:
            wp2=new arrow();break;
        }
        if(ATK/5==0)
            wp0=NULL;
    };
};
class lion:public warrior{
    int loyalty;
public:
    void march(int time);
    lion(headquarter * ppheadquarter,int totalwarr):warrior(totalwarr,ppheadquarter,3){
        ATK=warrior_ATK[3];
        element=warrior_life_value[3];
        loyalty=pheadquarter->totalvalue;
    }
    friend class timeline;
    friend class city;
        
};
class wolf:public warrior{
public:
    void march(int time);
    wolf(headquarter * ppheadquarter,int totalwarr):warrior(totalwarr,ppheadquarter,4){
        ATK=warrior_ATK[4];
        element=warrior_life_value[4];
    }
};

class timeline{
    public:
        int cur;
        static int echomoment[10];
        timeline(){
            cur=0;
        };
        void timeproduce(int time,headquarter * pred,headquarter * pblue){
            pred->produce(time);
            pblue->produce(time);
        }
        void reportlion(int time);
        void reportmarched(int time,headquarter * marchred,headquarter * marchblue);
        void produce_element(){
                for(int i=1;i<=n;i++)
                    pcity[i]->element+=10;
        }
        void take_element(int time);
        void release_arrow(int time);
        void reportelements(int time,headquarter * preportred,headquarter * preportblue);
        void reportweapon(int time);
        void usebomb(int time);
        void battle(int time);
};
int timeline::echomoment[10]={0,5,10,20,30,35,38,40,50,55};

int main(){
    //freopen("1.txt","w",stdout);
    int CaseNo;
    int t;
    scanf("%d",&t);
    for(int o=1;o<=t;o++)
    {
        memset(pcity,0,sizeof(pcity));
        CaseNo=o;
        endofgame=0;
        printf("Case %d:\n",CaseNo);
        scanf("%d%d%d%d%d",&m,&n,&r,&k,&T);
        for(int i=0;i<n+2;i++)
            pcity[i]=new city(i);
        headquarter red(m,1);
        headquarter blue(m,0);
        headquarter * pred=&red;
        headquarter * pblue=&blue;
        for(int i=0;i<5;i++)
            cin>>warrior::warrior_life_value[i];
        for(int i=0;i<5;i++)
            cin>>warrior::warrior_ATK[i];
        int time=0;
        timeline timeloop;
        while(1)
        {
            switch (timeline::echomoment[timeloop.cur]){
                case 0:timeloop.timeproduce(time,pred,pblue);break;
                case 5:timeloop.reportlion(time);break;
                case 10:timeloop.reportmarched(time,pred,pblue);break;
                case 20:timeloop.produce_element();break;
                case 30:timeloop.take_element(time);break;
                case 35:timeloop.release_arrow(time);break;
                case 38:timeloop.usebomb(time);break;
                case 40:timeloop.battle(time);break;
                case 50:timeloop.reportelements(time,pred,pblue);break;
                case 55:timeloop.reportweapon(time);break;
            }
            
            if(60*time+timeline::echomoment[timeloop.cur+1]>T)
                break;
            timeloop.cur++;
            if(timeloop.cur==10)
            {
                timeloop.cur=0;
                time++;
            }
            if(endofgame)
                break;
        }
    }
    //fclose(stdout);
    return 0;
}

headquarter::headquarter(int _totalvalue,bool _color):totalvalue(_totalvalue),color(_color){
        take_the_other=0;
        totalwa=0;
        cur=0;
        memset(pw,0,sizeof(pw));
        if(color){
            memset(order,0,sizeof(order));
            int tmp[5]={2,3,4,1,0};
            memcpy(order,tmp,sizeof(order));
            phcity=pcity[0];
        }
        else{
            memset(order,0,sizeof(order));
            int tmp[5]={3,0,1,2,4};
            memcpy(order,tmp,sizeof(order));
            phcity=pcity[n+1];
        }
    }
warrior::warrior(int _totalNo,headquarter * _pheadquarter,int _type):pheadquarter(_pheadquarter),totalNo(_totalNo),type(_type){
    ATK=0;
    element=0;
    plocation=pheadquarter->phcity;
    gone=0;
    wp0=NULL;
    wp1=NULL;
    wp2=NULL;
}

void headquarter::produce(int time){
    if(totalvalue<warrior::warrior_life_value[order[cur]])
        return;
    totalvalue-=warrior::warrior_life_value[order[cur]];
    totalwa++;
    switch(order[cur]){
        case 0:
            pw[totalwa]=new dragon(this,totalwa);
            break;
        case 1:
            pw[totalwa]=new ninja(this,totalwa);
            break;
        case 2:
            pw[totalwa]=new iceman(this,totalwa);
            break;
        case 3:
            pw[totalwa]=new lion(this,totalwa);
            break;
        case 4:
            pw[totalwa]=new wolf(this,totalwa);
            break;//switch怎么能忘加break，废物点心
    }
    if(color)
        phcity->pcityw[0]=pw[totalwa];
    else
        phcity->pcityw[1]=pw[totalwa];
    printproduced(time);
    cur++;
    if(cur==5)
        cur=0;
}
char warrior::names[warrior_num][10]={"dragon","ninja","iceman","lion","wolf"};
int warrior::warrior_life_value[warrior_num];
int warrior::warrior_ATK[warrior_num];

void headquarter::printproduced(int time){
    if(color)
    {
        printf("%03d:00 red %s %d born\n",time,warrior::names[order[cur]],totalwa);
        if(cur==1)
            printf("Its loyalty is %d\n",totalvalue);
        if(cur==4)
            printf("Its morale is %0.2f\n",(double)totalvalue/warrior::warrior_life_value[0]);
    }
    else
    {
        printf("%03d:00 blue %s %d born\n",time,warrior::names[order[cur]],totalwa);
        if(cur==0)
            printf("Its loyalty is %d\n",totalvalue);
        if(cur==1)
            printf("Its morale is %0.2f\n",(double)totalvalue/warrior::warrior_life_value[0]);
    }
}

void timeline::reportlion(int time){
    for(int i=0;i<=n+1;i++)
    {
        if(pcity[i]->pcityw[0]!=NULL&&pcity[i]->pcityw[0]->type==3&&pcity[i]->pcityw[0]->gone==0)
        {
            lion * tmp=(lion *)pcity[i]->pcityw[0];
            int seek=tmp->loyalty;
            if(seek<=0)
            {
                printf("%03d:05 red lion %d ran away\n",time,pcity[i]->pcityw[0]->totalNo);
                pcity[i]->pcityw[0]->gone=1;
                pcity[i]->pcityw[0]=NULL;
            }
        }
        if(pcity[i]->pcityw[1]!=NULL&&pcity[i]->pcityw[1]->type==3&&pcity[i]->pcityw[1]->gone==0)
        {
            lion * tmp=(lion *)pcity[i]->pcityw[1];
            int seek=tmp->loyalty;
            if(seek<=0)
            {
                printf("%03d:05 blue lion %d ran away\n",time,pcity[i]->pcityw[1]->totalNo);
                pcity[i]->pcityw[1]->gone=1;
                pcity[i]->pcityw[1]=NULL;
            }
        }
    }
}

void dragon::march(int time){
    if(gone==0)
    {
        int place=plocation->number;
        if(pheadquarter->color)
        {
            place++;
            if(place==n+1)
            {
                printf("%03d:10 red dragon %d reached blue headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                pheadquarter->take_the_other++;
                if(pheadquarter->take_the_other==2)
                {
                    endofgame=1;
                    printf("%03d:10 blue headquarter was taken\n",time);
                }
            }
            else
                printf("%03d:10 red dragon %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            plocation=pcity[place];
            
        }
        else
        {
            place--;
            if(place==0)
            {
                printf("%03d:10 blue dragon %d reached red headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                pheadquarter->take_the_other++;
                if(pheadquarter->take_the_other==2)
                {
                    endofgame=1;
                    printf("%03d:10 red headquarter was taken\n",time);
                }
            }
            else
                printf("%03d:10 blue dragon %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            plocation=pcity[place];
            
        }
    }
}
void ninja::march(int time){
    if(gone==0)
    {
        int place=plocation->number;
        if(pheadquarter->color)
        {
            place++;
            if(place==n+1)
            {
                printf("%03d:10 red ninja %d reached blue headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                pheadquarter->take_the_other++;
                if(pheadquarter->take_the_other==2)
                {
                    endofgame=1;
                    printf("%03d:10 blue headquarter was taken\n",time);
                }
            }
            else
                printf("%03d:10 red ninja %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            plocation=pcity[place];
            
        }
        else
        {
            place--;
            if(place==0)
            {
                printf("%03d:10 blue ninja %d reached red headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                pheadquarter->take_the_other++;
                if(pheadquarter->take_the_other==2)
                {
                    endofgame=1;
                    printf("%03d:10 red headquarter was taken\n",time);
                }
            }
            else
                printf("%03d:10 blue ninja %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            plocation=pcity[place];
            
        }
    }
    
}
void iceman::march(int time){
    if(gone==0)
    {
        int place=plocation->number;
        even_move=(!even_move);
        if(!even_move){
            if(element>9)
                element-=9;
            else
                element=1;
            ATK+=20;
        }
        if(pheadquarter->color)
        {
            place++;
            if(place==n+1)
            {
                printf("%03d:10 red iceman %d reached blue headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                pheadquarter->take_the_other++;
                if(pheadquarter->take_the_other==2)
                {
                    endofgame=1;
                    printf("%03d:10 blue headquarter was taken\n",time);
                }
            }
            else
                printf("%03d:10 red iceman %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            plocation=pcity[place];
            
        }
        else
        {
            place--;
            if(place==0)
            {
                printf("%03d:10 blue iceman %d reached red headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                pheadquarter->take_the_other++;
                if(pheadquarter->take_the_other==2)
                {
                    endofgame=1;
                    printf("%03d:10 red headquarter was taken\n",time);
                }
            }
            else
                printf("%03d:10 blue iceman %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            plocation=pcity[place];
            
        }
    }
    
}
void lion::march(int time){
    if(gone==0)
    {
        int place=plocation->number;
        if(pheadquarter->color)
        {
            place++;
            if(place==n+1)
            {
                printf("%03d:10 red lion %d reached blue headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                pheadquarter->take_the_other++;
                if(pheadquarter->take_the_other==2)
                {
                    endofgame=1;
                    printf("%03d:10 blue headquarter was taken\n",time);
                }
            }
            else
                printf("%03d:10 red lion %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            plocation=pcity[place];
            
        }
        else
        {
            place--;
            if(place==0)
            {
                printf("%03d:10 blue lion %d reached red headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                pheadquarter->take_the_other++;
                if(pheadquarter->take_the_other==2)
                {
                    endofgame=1;
                    printf("%03d:10 red headquarter was taken\n",time);
                }
            }
            else
                printf("%03d:10 blue lion %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            plocation=pcity[place];
            
        }
    }
    
}
void wolf::march(int time){
    if(gone==0)
    {
        int place=plocation->number;
        if(pheadquarter->color)
        {
            place++;
            if(place==n+1)
            {
                printf("%03d:10 red wolf %d reached blue headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                pheadquarter->take_the_other++;
                if(pheadquarter->take_the_other==2)
                {
                    endofgame=1;
                    printf("%03d:10 blue headquarter was taken\n",time);
                }
            }
            else
                printf("%03d:10 red wolf %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            plocation=pcity[place];
            
        }
        else
        {
            place--;
            if(place==0)
            {
                printf("%03d:10 blue wolf %d reached red headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                pheadquarter->take_the_other++;
                if(pheadquarter->take_the_other==2)
                {
                    endofgame=1;
                    printf("%03d:10 red headquarter was taken\n",time);
                }
            }
            else
                printf("%03d:10 blue wolf %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            plocation=pcity[place];
            
        }
    }
    
}

void timeline::reportmarched(int time,headquarter * marchred,headquarter * marchblue){
    if(pcity[1]->pcityw[1])
        pcity[1]->pcityw[1]->march(time);
    for(int i=1;i<=n;i++)
    {
        if(pcity[i-1]->pcityw[0])
            pcity[i-1]->pcityw[0]->march(time);
        if(pcity[i+1]->pcityw[1])
            pcity[i+1]->pcityw[1]->march(time);
    }
    if(pcity[n]->pcityw[0])
        pcity[n]->pcityw[0]->march(time);
    for(int i=0;i<n+2;i++)
    {
        if(pcity[i]->pcityw[0])
            pcity[i]->pcityw[0]=NULL;
        if(pcity[i]->pcityw[1])
            pcity[i]->pcityw[1]=NULL;
    }
    int i=1;
    while(marchred->pw[i]||marchblue->pw[i])
    {
        if(marchred->pw[i]&&marchred->pw[i]->gone==0)
            marchred->pw[i]->plocation->pcityw[0]=marchred->pw[i];
        if(marchblue->pw[i]&&marchblue->pw[i]->gone==0)
            marchblue->pw[i]->plocation->pcityw[1]=marchblue->pw[i];
        i++;
    }
    pcity[0]->pcityw[0]=NULL;
    pcity[n+1]->pcityw[1]=NULL;
}

void timeline::take_element(int time){
    for(int i=1;i<=n;i++){
        if(pcity[i]->pcityw[0]!=NULL&&pcity[i]->pcityw[1]==NULL){
            pcity[i]->pcityw[0]->pheadquarter->totalvalue+=pcity[i]->element;
            printf("%03d:30 red %s %d earned %d elements for his headquarter\n",time,warrior::names[pcity[i]->pcityw[0]->type],pcity[i]->pcityw[0]->totalNo,pcity[i]->element);
            pcity[i]->element=0;
        }
        if(pcity[i]->pcityw[1]!=NULL&&pcity[i]->pcityw[0]==NULL){
            pcity[i]->pcityw[1]->pheadquarter->totalvalue+=pcity[i]->element;
            printf("%03d:30 blue %s %d earned %d elements for his headquarter\n",time,warrior::names[pcity[i]->pcityw[1]->type],pcity[i]->pcityw[1]->totalNo,pcity[i]->element);
            pcity[i]->element=0;
        }
    }
}

void timeline::release_arrow(int time){

    for(int i=1;i<n+1;i++){
        if(pcity[i]->pcityw[0]&&pcity[i+1]->pcityw[1]&&pcity[i]->pcityw[0]->wp2)
            pcity[i]->pcityw[0]->arrow_attack(pcity[i+1]->pcityw[1],time);
        if(pcity[i]->pcityw[1]&&pcity[i-1]->pcityw[0]&&pcity[i]->pcityw[1]->wp2)
            pcity[i]->pcityw[1]->arrow_attack(pcity[i-1]->pcityw[0],time);
    }

}

void warrior::arrow_attack(warrior* pattacked,int time){
    arrow * pa=(arrow*)wp2;
    pa->used_count++;
    if(pa->used_count==3)
        wp2=NULL;
    pattacked->element-=r;
    if(pattacked->element<=0){
        pattacked->gone=1;
        if(pheadquarter->color)
            printf("%03d:35 red %s %d shot and killed blue %s %d\n",time,warrior::names[type],totalNo,warrior::names[pattacked->type],pattacked->totalNo);
        else
            printf("%03d:35 blue %s %d shot and killed red %s %d\n",time,warrior::names[type],totalNo,warrior::names[pattacked->type],pattacked->totalNo);
    }
    else{
        if(pheadquarter->color)
            printf("%03d:35 red %s %d shot\n",time,warrior::names[type],totalNo);
        else
            printf("%03d:35 blue %s %d shot\n",time,warrior::names[type],totalNo);
    }
}

void timeline::reportelements(int time,headquarter * preportred,headquarter * preportblue){
    int tmpred=preportred->totalvalue;
    int tmpblue=preportblue->totalvalue;
    printf("%03d:50 %d elements in red headquarter\n",time,tmpred);
    printf("%03d:50 %d elements in blue headquarter\n",time,tmpblue);
}

void timeline::reportweapon(int time){
    for(int i=0;i<=n+1;i++)
    {
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[0]->gone==0)
        {
            pcity[i]->pcityw[0]->print_weapon(time);
        }
    }
    for(int i=0;i<=n+1;i++)
    {
        if(pcity[i]->pcityw[1]&&pcity[i]->pcityw[1]->gone==0)
        {
            pcity[i]->pcityw[1]->print_weapon(time);
        }
    }
}

void warrior::print_weapon(int time)
{
    printf("%03d:55",time);
    if(pheadquarter->color)
    printf(" red ");
    else
    printf(" blue ");
    printf("%s %d has ",names[type],totalNo);
    bool weap0=0,weap1=0,weap2=0;
    if(wp2)
    {
        if(weap0||weap1)
        printf(",");
        arrow *pa=(arrow*)wp2;
        printf("arrow(%d)",3-pa->used_count);
        weap2=1;
    }
    if(wp1)
    {
        if(weap2)
            printf(",");
        printf("bomb");
        weap1=1;
    }
    if(wp0)
    {
        if(weap1||weap2)
            printf(",");
        sword *ps=(sword*)wp0;
        printf("sword(%d)",ps->force);
        weap0=1;
    }
    if(weap0+weap1+weap2==0)
        printf("no weapon");
    printf("\n");
}

void timeline::usebomb(int time){
    for(int i=1;i<=n;i++){
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1]&&pcity[i]->pcityw[0]->gone==0&&pcity[i]->pcityw[1]->gone==0)
        {
            if((i%2&&pcity[i]->flag_color!=-2)||pcity[i]->flag_color==2)
            {
                if(pcity[i]->pcityw[0]->wp1)
                {
                    int tmp=pcity[i]->pcityw[1]->ATK/2;
                    if(pcity[i]->pcityw[1]->wp0)
                    {
                        sword * sw=(sword *)pcity[i]->pcityw[1]->wp0;
                        tmp+=sw->force;
                    }
                    if(pcity[i]->pcityw[1]->type==1)
                        tmp=0;
                    int att_tmp=pcity[i]->pcityw[0]->ATK;
                    if(pcity[i]->pcityw[0]->wp0)
                    {
                        sword * sw=(sword *)pcity[i]->pcityw[0]->wp0;
                        att_tmp+=sw->force;
                    }
                    if(att_tmp>=pcity[i]->pcityw[1]->element)
                        tmp=0;
                    if(pcity[i]->pcityw[0]->element<=tmp)
                    {
                        printf("%03d:38 red %s %d used a bomb and killed blue %s %d\n",time,warrior::names[pcity[i]->pcityw[0]->type],pcity[i]->pcityw[0]->totalNo,warrior::names[pcity[i]->pcityw[1]->type],pcity[i]->pcityw[1]->totalNo);
                        pcity[i]->pcityw[0]->gone=1;
                        pcity[i]->pcityw[1]->gone=1;
                    }
                }
                if(pcity[i]->pcityw[1]->wp1)
                {
                    int tmp=pcity[i]->pcityw[0]->ATK;
                    if(pcity[i]->pcityw[0]->wp0)
                    {
                        sword * sw=(sword *)pcity[i]->pcityw[0]->wp0;
                        tmp+=sw->force;
                    }
                    if(pcity[i]->pcityw[1]->element<=tmp)
                    {
                        printf("%03d:38 blue %s %d used a bomb and killed red %s %d\n",time,warrior::names[pcity[i]->pcityw[1]->type],pcity[i]->pcityw[1]->totalNo,warrior::names[pcity[i]->pcityw[0]->type],pcity[i]->pcityw[0]->totalNo);
                        pcity[i]->pcityw[0]->gone=1;
                        pcity[i]->pcityw[1]->gone=1;
                    }
                }
            }
            if((i%2==0&&pcity[i]->flag_color!=2)||pcity[i]->flag_color==-2)
            {
                if(pcity[i]->pcityw[0]->wp1)
                {
                    int tmp=pcity[i]->pcityw[1]->ATK;
                    if(pcity[i]->pcityw[1]->wp0)
                    {
                        sword * sw=(sword *)pcity[i]->pcityw[1]->wp0;
                        tmp+=sw->force;
                    }
                    if(pcity[i]->pcityw[0]->element<=tmp)
                    {
                        printf("%03d:38 red %s %d used a bomb and killed blue %s %d\n",time,warrior::names[pcity[i]->pcityw[0]->type],pcity[i]->pcityw[0]->totalNo,warrior::names[pcity[i]->pcityw[1]->type],pcity[i]->pcityw[1]->totalNo);
                        pcity[i]->pcityw[0]->gone=1;
                        pcity[i]->pcityw[1]->gone=1;
                    }
                }
                if(pcity[i]->pcityw[1]->wp1)
                {
                    int tmp=pcity[i]->pcityw[0]->ATK/2;
                    if(pcity[i]->pcityw[0]->wp0)
                    {
                        sword * sw=(sword *)pcity[i]->pcityw[0]->wp0;
                        tmp+=sw->force;
                    }
                    if(pcity[i]->pcityw[0]->type==1)
                        tmp=0;
                    int att_tmp=pcity[i]->pcityw[1]->ATK;
                    if(pcity[i]->pcityw[1]->wp0)
                    {
                        sword * sw=(sword *)pcity[i]->pcityw[1]->wp0;
                        att_tmp+=sw->force;
                    }
                    if(att_tmp>=pcity[i]->pcityw[0]->element)
                        tmp=0;
                    if(pcity[i]->pcityw[1]->element<=tmp)
                    {
                        printf("%03d:38 blue %s %d used a bomb and killed red %s %d\n",time,warrior::names[pcity[i]->pcityw[1]->type],pcity[i]->pcityw[1]->totalNo,warrior::names[pcity[i]->pcityw[0]->type],pcity[i]->pcityw[0]->totalNo);
                        pcity[i]->pcityw[0]->gone=1;
                        pcity[i]->pcityw[1]->gone=1;
                    }
                }
            }

        }
    }
}

void timeline::battle(int time){

    for(int i=1;i<=n;++i){
        int elementr=0,elementb=0;
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1])
        {
            elementr=pcity[i]->pcityw[0]->element;
            elementb=pcity[i]->pcityw[1]->element;
        }
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1]&&pcity[i]->pcityw[0]->gone&&pcity[i]->pcityw[1]->gone==0)
        {
            if(pcity[i]->pcityw[1]->type==0)
            {
                dragon * dr=(dragon*)pcity[i]->pcityw[1];
                if(((i%2==0&&pcity[i]->flag_color!=2)||pcity[i]->flag_color==-2)&&dr->courage>0.6){
                    printf("%03d:40 blue dragon %d yelled in city %d\n",time,pcity[i]->pcityw[1]->totalNo,i);
                }
            }
            printf("%03d:40 blue %s %d earned %d elements for his headquarter\n",time,warrior::names[pcity[i]->pcityw[1]->type],pcity[i]->pcityw[1]->totalNo,pcity[i]->element);
            
            if(pcity[i]->pcityw[0]->type==3)
                pcity[i]->pcityw[1]->element=pcity[i]->pcityw[1]->element-pcity[i]->pcityw[0]->element;
        }
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1]&&pcity[i]->pcityw[0]->gone==0&&pcity[i]->pcityw[1]->gone)
        {
            if(pcity[i]->pcityw[0]->type==0)
            {
                dragon * dr=(dragon*)pcity[i]->pcityw[0];
                if(((i%2&&pcity[i]->flag_color!=-2)||pcity[i]->flag_color==2)&&dr->courage>0.6){
                    printf("%03d:40 red dragon %d yelled in city %d\n",time,pcity[i]->pcityw[0]->totalNo,i);
                }
            }
            printf("%03d:40 red %s %d earned %d elements for his headquarter\n",time,warrior::names[pcity[i]->pcityw[0]->type],pcity[i]->pcityw[0]->totalNo,pcity[i]->element);
            if(pcity[i]->pcityw[1]->type==3)
                pcity[i]->pcityw[0]->element=pcity[i]->pcityw[0]->element-pcity[i]->pcityw[1]->element;
        }
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1]&&pcity[i]->pcityw[0]->gone==0&&pcity[i]->pcityw[1]->gone==0){
            pcity[i]->battle(time);
        }

        if (pcity[i]->pcityw[0]&&pcity[i]->pcityw[1]&&pcity[i]->pcityw[1]->gone&&pcity[i]->pcityw[0]->gone==0)
        {
            if(pcity[i]->pcityw[0]->type==4)
            {
                if(pcity[i]->pcityw[0]->wp0==NULL)
                {
                    pcity[i]->pcityw[0]->wp0=pcity[i]->pcityw[1]->wp0;
                    pcity[i]->pcityw[1]->wp0=NULL;
                }
                if(pcity[i]->pcityw[0]->wp1==NULL)
                {
                    pcity[i]->pcityw[0]->wp1=pcity[i]->pcityw[1]->wp1;
                    pcity[i]->pcityw[1]->wp1=NULL;
                }
                if(pcity[i]->pcityw[0]->wp2==NULL)
                {
                    pcity[i]->pcityw[0]->wp2=pcity[i]->pcityw[1]->wp2;
                    pcity[i]->pcityw[1]->wp2=NULL;
                }
            }
            if(pcity[i]->pcityw[0]->type==0)
            {
                dragon* dr=(dragon *)pcity[i]->pcityw[0];
                dr->courage+=0.2;
            }
            if(pcity[i]->pcityw[1]->type==3)
                pcity[i]->pcityw[0]->element+=elementb;
        }
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1]&&pcity[i]->pcityw[0]->gone&&pcity[i]->pcityw[1]->gone==0)
        {
            if(pcity[i]->pcityw[1]->type==4)
            {
                if(pcity[i]->pcityw[1]->wp0==NULL)
                {
                    pcity[i]->pcityw[1]->wp0=pcity[i]->pcityw[0]->wp0;
                    pcity[i]->pcityw[0]->wp0=NULL;
                }
                if(pcity[i]->pcityw[1]->wp1==NULL)
                {
                    pcity[i]->pcityw[1]->wp1=pcity[i]->pcityw[0]->wp1;
                    pcity[i]->pcityw[0]->wp1=NULL;
                }
                if(pcity[i]->pcityw[1]->wp2==NULL)
                {
                    pcity[i]->pcityw[1]->wp2=pcity[i]->pcityw[0]->wp2;
                    pcity[i]->pcityw[0]->wp2=NULL;
                }
            }
            if(pcity[i]->pcityw[1]->type==0)
            {
                dragon* dr=(dragon *)pcity[i]->pcityw[1];
                dr->courage+=0.2;
            }
            if(pcity[i]->pcityw[0]->type==3)
                pcity[i]->pcityw[1]->element+=elementr;

        }
        //升旗
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1])
        {
            int tmpflag=pcity[i]->flag_color;
            if(pcity[i]->pcityw[0]->gone==0&&pcity[i]->pcityw[1]->gone==0)
            {
                if(pcity[i]->flag_color!=2&&pcity[i]->flag_color!=-2)
                pcity[i]->flag_color=0;
                pcity[i]->jb=0;
                pcity[i]->jr=0;
            }
            if(pcity[i]->pcityw[0]->gone==0&&pcity[i]->pcityw[1]->gone)
            {
                pcity[i]->jb=0;
                if(pcity[i]->flag_color!=2&&pcity[i]->flag_color>=0)
                pcity[i]->flag_color++;
                if(pcity[i]->flag_color==-2)
                {
                    if(pcity[i]->jr)
                    {
                        pcity[i]->flag_color=2;
                        pcity[i]->jr=0;
                    }
                    else{
                        pcity[i]->jr=1;
                    }
                }
                if(pcity[i]->flag_color==-1)
                pcity[i]->flag_color=1;
                if(pcity[i]->flag_color==2&&tmpflag!=2)
                    printf("%03d:40 red flag raised in city %d\n",time,i);
            }
            if(pcity[i]->pcityw[0]->gone&&pcity[i]->pcityw[1]->gone==0)
            {
                pcity[i]->jr=0;
                if(pcity[i]->flag_color!=-2&&pcity[i]->flag_color<=0)
                pcity[i]->flag_color--;
                if(pcity[i]->flag_color==2)
                {
                    if(pcity[i]->jb)
                    {
                        pcity[i]->flag_color=-2;
                        pcity[i]->jb=0;
                    }
                    else{
                        pcity[i]->jb=1;
                    }
                }
                if(pcity[i]->flag_color==1)
                pcity[i]->flag_color=-1;
                if(pcity[i]->flag_color==-2&&tmpflag!=-2)
                    printf("%03d:40 blue flag raised in city %d\n",time,i);
            }
        }
    }


    //奖励
    for(int i=n;i>=1;--i){
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1]&&pcity[i]->pcityw[0]->gone==0&&pcity[i]->pcityw[1]->gone)
        {
            if(pcity[i]->pcityw[0]->pheadquarter->totalvalue>=8){
                pcity[i]->pcityw[0]->element+=8;
                pcity[i]->pcityw[0]->pheadquarter->totalvalue-=8;
            }
        }
    }
    for(int i=1;i<=n;++i){
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1]&&pcity[i]->pcityw[0]->gone&&pcity[i]->pcityw[1]->gone==0)
        {
            if(pcity[i]->pcityw[1]->pheadquarter->totalvalue>=8){
                pcity[i]->pcityw[1]->element+=8;
                pcity[i]->pcityw[1]->pheadquarter->totalvalue-=8;
            }
        }
    }
    //奖励完成

    //获得生命元
    for(int i=1;i<=n;i++)
    {
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1]&&pcity[i]->pcityw[0]->gone==0&&pcity[i]->pcityw[1]->gone)
        {
            pcity[i]->pcityw[0]->pheadquarter->totalvalue+=pcity[i]->element;
            pcity[i]->element=0;
        }
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1]&&pcity[i]->pcityw[0]->gone&&pcity[i]->pcityw[1]->gone==0)
        {
            pcity[i]->pcityw[1]->pheadquarter->totalvalue+=pcity[i]->element;
            pcity[i]->element=0;
        }
    }
    //生命元获取完成


}

void city::battle(int time){
    if((number%2&&pcity[number]->flag_color!=-2)||pcity[number]->flag_color==2)
    {
        pcityw[0]->attack(pcityw[1]);
        printf("%03d:40 red %s %d attacked blue %s %d in city %d with %d elements and force %d\n",time,warrior::names[pcityw[0]->type],pcityw[0]->totalNo,warrior::names[pcityw[1]->type],pcityw[1]->totalNo,number,pcityw[0]->element,pcityw[0]->ATK);
        if(pcityw[1]->element>0)
        {
            pcityw[1]->fight_back(pcityw[0]);
            if(pcityw[1]->type!=1)
            printf("%03d:40 blue %s %d fought back against red %s %d in city %d\n",time,warrior::names[pcityw[1]->type],pcityw[1]->totalNo,warrior::names[pcityw[0]->type],pcityw[0]->totalNo,number);
        }
    }
    if((number%2==0&&pcity[number]->flag_color!=2)||pcity[number]->flag_color==-2)
    {
        pcityw[1]->attack(pcityw[0]);
        printf("%03d:40 blue %s %d attacked red %s %d in city %d with %d elements and force %d\n",time,warrior::names[pcityw[1]->type],pcityw[1]->totalNo,warrior::names[pcityw[0]->type],pcityw[0]->totalNo,number,pcityw[1]->element,pcityw[1]->ATK);
        if(pcityw[0]->element>0)
        {
            pcityw[0]->fight_back(pcityw[1]);
            if(pcityw[0]->type!=1)
            printf("%03d:40 red %s %d fought back against blue %s %d in city %d\n",time,warrior::names[pcityw[0]->type],pcityw[0]->totalNo,warrior::names[pcityw[1]->type],pcityw[1]->totalNo,number);
        }
    }
    if(pcityw[0]->element<=0)
    pcityw[0]->gone=1;
    if(pcityw[1]->element<=0)
    pcityw[1]->gone=1;
    if(pcityw[0]->gone&&pcityw[1]->gone==0){
        printf("%03d:40 red %s %d was killed in city %d\n",time,warrior::names[pcityw[0]->type],pcityw[0]->totalNo,number);
        if(pcityw[1]->type==0&&pcityw[1]->gone==0)
        {
            dragon * dr=(dragon*)pcityw[1];
            if(((number%2==0&&flag_color!=2)||flag_color==-2)&&dr->courage>0.6){
                printf("%03d:40 blue dragon %d yelled in city %d\n",time,pcityw[1]->totalNo,number);
            }
        }
        printf("%03d:40 blue %s %d earned %d elements for his headquarter\n",time,warrior::names[pcityw[1]->type],pcityw[1]->totalNo,element);
    }
    if(pcityw[1]->gone&&pcityw[0]->gone==0){
        printf("%03d:40 blue %s %d was killed in city %d\n",time,warrior::names[pcityw[1]->type],pcityw[1]->totalNo,number);
        if(pcityw[0]->type==0&&pcityw[0]->gone==0)
        {
            dragon * dr=(dragon*)pcityw[0];
            if(((number%2&&flag_color!=-2)||flag_color==2)&&dr->courage>0.6){
                printf("%03d:40 red dragon %d yelled in city %d\n",time,pcityw[0]->totalNo,number);
            }
        }
        printf("%03d:40 red %s %d earned %d elements for his headquarter\n",time,warrior::names[pcityw[0]->type],pcityw[0]->totalNo,element);
    }
    if(pcityw[0]->gone==0&&pcityw[1]->gone==0){
        if(pcityw[0]->type==3)
        {
            lion * li=(lion*)pcityw[0];
            li->loyalty-=k;
        }
        if(pcityw[1]->type==3)
        {
            lion * li=(lion*)pcityw[1];
            li->loyalty-=k;
        }
        if(pcityw[0]->type==0)
        {
            dragon* dr=(dragon *)pcityw[0];
            dr->courage-=0.2;
        }
        if(pcityw[1]->type==0)
        {
            dragon* dr=(dragon *)pcityw[1];
            dr->courage-=0.2;
        }
        if(pcityw[1]->type==0&&pcityw[1]->gone==0)
        {
            dragon * dr=(dragon*)pcityw[1];
            if(((number%2==0&&flag_color!=2)||flag_color==-2)&&dr->courage>0.8){
                printf("%03d:40 blue dragon %d yelled in city %d\n",time,pcityw[1]->totalNo,number);
            }
        }
        if(pcityw[0]->type==0&&pcityw[0]->gone==0)
        {
            dragon * dr=(dragon*)pcityw[0];
            if(((number%2&&flag_color!=-2)||flag_color==2)&&dr->courage>0.6){
                printf("%03d:40 red dragon %d yelled in city %d\n",time,pcityw[0]->totalNo,number);
            }
        }
    }
}

void warrior::attack(warrior * pattacked){
    int tmp=ATK;
    if(wp0)
    {
        sword * sw=(sword *)wp0;
        tmp+=sw->force;
        sw->force=sw->force*0.8;
        if(sw->force==0)
        wp0=NULL;
    }
    pattacked->element-=tmp;
}
void warrior::fight_back(warrior * pattacked){
    if(type==1)
        return;
    int tmp=ATK/2;
    if(wp0)
    {
        sword * sw=(sword *)wp0;
        tmp+=sw->force;
        sw->force=sw->force*0.8;
        if(sw->force==0)
        wp0=NULL;
    }
    pattacked->element-=tmp;

}