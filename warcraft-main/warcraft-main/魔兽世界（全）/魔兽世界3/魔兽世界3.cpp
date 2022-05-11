#include<iostream>
#include<cstring>
using namespace std;

class headquarter;
class warrior;
class city;
class weapon;
#define warrior_num 5
#define weapon_num 3
city * pcity[25];
int k,m,n,T;
bool endofgame=0;
void sortp(warrior * sortpw);

class weapon{
    public:
        static char weapon_name[weapon_num][10];
        //静态成员变量记录武器名字
        weapon(int i=0):type(i),used(0){};
        //构造函数
        weapon & operator=(int i){
            type=i;
            used=0;
            return *this;
        }
        //重载赋值运算符
        operator int(){
            return type;
        }
        //强制转换为整数，方便查询是第几个武器
        bool used;
        int type;
        friend class warrior;
};
//武器类

class warrior{
    protected:
        int totalNo;
        //第几号武士
        int No;
        //第几号同类武士
        headquarter * pheadquarter;
        //每个武士有一个指针，表明自己是哪个阵营的
        int element;
        //生命值
        int ATK;
        int typeofw;
        city * location;
    public:
        static char names[warrior_num][10];
        //武士名
        static int warrior_life_value[warrior_num];
        //制作武士所需生命值
        warrior(headquarter * p,city * plocation,int totalw,int w_kind,int _element,int _ATK);
        //构造函数，指明哪个总部及编号及自己类编号
        virtual ~warrior(){}
        //虚析构函数，目前没有添加功能
        virtual void print_weapon(int time)=0;
        //虚函数，下面每个类都有一个print_weapon()
        void march(city * pmarch);
        virtual void attack(warrior * pattack,int x){};
        void hurted(int minuspower){
            element-=minuspower;
        }
        virtual void march(int time){};
        static int warrior_ATK[warrior_num];
        void countweapon();
        bool gone;
        weapon * wp[10];
        int get_typeofw(){
            return typeofw;
        }
        int get_totalNo(){
            return totalNo;
        }
        int get_element(){
            return element;
        }
        void tp(warrior * tpw);
        int weaponnum[3];
        friend class headquarter;
        //可访问总部的成员变量成员函数
        friend class timeline;
};
//武士做基类

class dragon:public warrior{
    double courage;
    //龙有勇气
    public:
        void print_weapon(int time);
        dragon(headquarter * p,city * pdragoncity,int totalw,int w_kind);
        //构造函数
        void attack(warrior * pattack,int x);
        void march(int time);

};
class ninja:public warrior{
    public:
        void print_weapon(int time);
        ninja(headquarter * p,city * pninjacity,int totalw,int w_kind):warrior(p,pninjacity,totalw,w_kind,warrior_life_value[1],warrior_ATK[1]){
            wp[0]=new weapon(totalw%3);
            wp[1]=new weapon((totalw+1)%3);
            typeofw=1;
        }
        //构造函数
        void attack(warrior * pattack,int x);
        void march(int time);

};
class iceman:public warrior{
    public:
        void print_weapon(int time);
        iceman(headquarter * p,city * picemancity,int totalw,int w_kind):warrior(p,picemancity,totalw,w_kind,warrior_life_value[2],warrior_ATK[2]){
            wp[0]=new weapon(totalw%3);
            typeofw=2;
        }
        //构造函数
        void attack(warrior * pattack,int x);
        void march(int time);

};
class lion:public warrior{
    int loyalty;
    //忠诚度
    public:
        void print_weapon(int time);
        lion(headquarter * p,city * plioncity,int totalw,int w_kind);
        //构造函数
        int get_loyalty(){
            return loyalty;
        }
        void attack(warrior * pattack,int x);
        void march(int time);
    friend class headquarter;
    friend class timeline;

};
class wolf:public warrior{
    public:
        void print_weapon(int time);
        wolf(headquarter * p,city * pwolfcity,int totalw,int w_kind):warrior(p,pwolfcity,totalw,w_kind,warrior_life_value[4],warrior_ATK[4]){
            typeofw=4;
        }
        //构造函数
        void attack(warrior * pattack,int x);
        void march(int time);
        void takeweapon(int time,warrior * takepw);

};
//五个武士类

char warrior::names[warrior_num][10]={"dragon","ninja","iceman","lion","wolf"};
//武士名
int warrior::warrior_life_value[warrior_num]={0};
//生命值
char weapon::weapon_name[weapon_num][10]={"sword","bomb","arrow"};
//武器名
//这三个是静态成员变量在此声明
int warrior::warrior_ATK[warrior_num]={0};

warrior::warrior(headquarter * p,city * plocation,int totalw,int w_kind,int _element,int _ATK):pheadquarter(p),location(plocation),totalNo(totalw),No(w_kind),element(_element),ATK(_ATK){
    memset(weaponnum,0,sizeof(weaponnum));
    memset(wp,0,sizeof(wp));
    gone=0;
    typeofw=0;
};
//武士构造函数

class headquarter{
    private:
        int totalvalue;
        //总生命元
        int order[5];
        //武士生产顺序
        bool color;
        //分辨红蓝总部
        int cur;
        //当前所在生产顺序中的位置
        int totalw;
        //武士总个数
        int w_kind[warrior_num];
        //记录着每类武士的个数
        warrior * pw[1000];
        //记录着总部生产出的所有武士的信息
        //定义了一个对象指针数组，要注意每次清理
        city * phcity;
    public:
        headquarter(int m,bool color_);
        ~headquarter();
        void produce(int time);
        void printproduced(int time);
        int get_total_value(){
            return totalvalue;
        }
        //龙制造武器时用
        void changephcity(city * pcphcity){
            phcity=pcphcity;
        }
        bool getcolor(){
            if(color)
                return 1;
            return 0;
        }
        bool take_the_other;
    friend class timeline;
    friend class warrior;
};
//总部类

class city{
    private:
        int number;
    public:
        warrior * pcityw[2];
        city(int i):number(i){
            memset(pcityw,0,sizeof(pcityw));
        }
        void battle(int time);
        ~city(){};
        int get_number(){
            return number;
        }
};

headquarter::headquarter(int m,bool color_):color(color_),totalvalue(m),take_the_other(0){
    color=color_;
    phcity=NULL;
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
    cur=0;
    totalw=0;
    memset(pw,0,sizeof(pw));
    memset(w_kind,0,sizeof(w_kind));
}
//构造函数

headquarter::~headquarter(){
    for(int i=1;i<=totalw;i++)
        delete pw[i];
}
//析构函数，武士都是new出来的

void headquarter::produce(int time){
    if(totalvalue<warrior::warrior_life_value[order[cur]])
        return;
    totalvalue-=warrior::warrior_life_value[order[cur]];
    totalw++;
    w_kind[order[cur]]+=1;
    switch(order[cur]){
        case 0:
            pw[totalw]=new dragon(this,phcity,totalw,w_kind[order[cur]]);
            break;
        case 1:
            pw[totalw]=new ninja(this,phcity,totalw,w_kind[order[cur]]);
            break;
        case 2:
            pw[totalw]=new iceman(this,phcity,totalw,w_kind[order[cur]]);
            break;
        case 3:
            pw[totalw]=new lion(this,phcity,totalw,w_kind[order[cur]]);
            break;
        case 4:
            pw[totalw]=new wolf(this,phcity,totalw,w_kind[order[cur]]);
            break;//switch怎么能忘加break，废物点心
    }
    if(getcolor())
        phcity->pcityw[0]=pw[totalw];
    else
        phcity->pcityw[1]=pw[totalw];
    printproduced(time);
    cur++;
    if(cur==5)
        cur=0;
}
//produce是一个布尔型函数，如果不能够制造并且已经输出了stopped那句话，则返回值为0
//在主函数的循环中，如果两个返回值都是0，那么此次战斗便结束了

void headquarter::printproduced(int time){
    if(color)
    {
        printf("%03d:00 red %s %d born\n",time,warrior::names[order[cur]],totalw);
        if(cur==1)
            printf("Its loyalty is %d\n",totalvalue);
    }
    else
    {
        printf("%03d:00 blue %s %d born\n",time,warrior::names[order[cur]],totalw);
        if(cur==0)
            printf("Its loyalty is %d\n",totalvalue);
    }
}
//打印结果函数，同时访问五个武士类中的打印结果函数

lion::lion(headquarter * p,city * plioncity,int totalw,int w_kind):warrior(p,plioncity,totalw,w_kind,warrior_life_value[3],warrior_ATK[3]){
            loyalty=pheadquarter->get_total_value();
            wp[0]=new weapon(totalw%3);
            typeofw=3;
        }
dragon::dragon(headquarter * p,city * pdragoncity,int totalw,int w_kind):warrior(p,pdragoncity,totalw,w_kind,warrior_life_value[0],warrior_ATK[0]){
            wp[0]=new weapon(totalw%3);
            courage=(double)pheadquarter->get_total_value()/warrior_life_value[0];
            typeofw=0;
        }
//在最后具体写出龙和狮子的构造函数。这是因为二者包含headquarter的指针，并且要访问其中变量，
//但由于dragon和lion的构建在headquarter之前，所以只能把具体函数体放到最后才不会报错

class timeline{
    public:
        int cur;
        static int echomoment[7];
        timeline(){
            cur=0;
        };
        void timeproduce(int time,headquarter * pred,headquarter * pblue);
        void reportelements(int time,headquarter * preportred,headquarter * preportblue);
        void reportweapon(int time);
        void reportlion(int time);
        void reportmarched(int time,headquarter * marchred,headquarter * marchblue);
        void tookweapon(int time);
        void reportbattle(int time);
};
int timeline::echomoment[7]={0,5,10,35,40,50,55};

void warrior::countweapon(){

    memset(weaponnum,0,sizeof(weaponnum));
    for(int i=0;i<10;i++)
    {
        if(wp[i]==NULL)
            break;
        weapon tmp=*wp[i];
        weaponnum[int(tmp)]++;
    }
}
void dragon::print_weapon(int time){
    if(pheadquarter->getcolor())
        printf("%03d:55 red dragon %d has %d sword %d bomb %d arrow and %d elements\n",time,totalNo,weaponnum[0],weaponnum[1],weaponnum[2],element);
    else
        printf("%03d:55 blue dragon %d has %d sword %d bomb %d arrow and %d elements\n",time,totalNo,weaponnum[0],weaponnum[1],weaponnum[2],element);
}
void ninja::print_weapon(int time){
    if(pheadquarter->getcolor())
        printf("%03d:55 red ninja %d has %d sword %d bomb %d arrow and %d elements\n",time,totalNo,weaponnum[0],weaponnum[1],weaponnum[2],element);
    else
        printf("%03d:55 blue ninja %d has %d sword %d bomb %d arrow and %d elements\n",time,totalNo,weaponnum[0],weaponnum[1],weaponnum[2],element);
}
void iceman::print_weapon(int time){
    if(pheadquarter->getcolor())
        printf("%03d:55 red iceman %d has %d sword %d bomb %d arrow and %d elements\n",time,totalNo,weaponnum[0],weaponnum[1],weaponnum[2],element);
    else
        printf("%03d:55 blue iceman %d has %d sword %d bomb %d arrow and %d elements\n",time,totalNo,weaponnum[0],weaponnum[1],weaponnum[2],element);
}
void lion::print_weapon(int time){
    if(pheadquarter->getcolor())
        printf("%03d:55 red lion %d has %d sword %d bomb %d arrow and %d elements\n",time,totalNo,weaponnum[0],weaponnum[1],weaponnum[2],element);
    else
        printf("%03d:55 blue lion %d has %d sword %d bomb %d arrow and %d elements\n",time,totalNo,weaponnum[0],weaponnum[1],weaponnum[2],element);
}
void wolf::print_weapon(int time){
    if(pheadquarter->getcolor())
        printf("%03d:55 red wolf %d has %d sword %d bomb %d arrow and %d elements\n",time,totalNo,weaponnum[0],weaponnum[1],weaponnum[2],element);
    else
        printf("%03d:55 blue wolf %d has %d sword %d bomb %d arrow and %d elements\n",time,totalNo,weaponnum[0],weaponnum[1],weaponnum[2],element);
}
void dragon::march(int time){
    if(gone==0)
    {
        int place=location->get_number();
        if(pheadquarter->getcolor())
        {
            place++;
            if(place==n+1)
            {
                printf("%03d:10 red dragon %d reached blue headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                printf("%03d:10 blue headquarter was taken\n",time);
                pheadquarter->take_the_other=1;
            }
            else
                printf("%03d:10 red dragon %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            location=pcity[place];
            
        }
        else
        {
            place--;
            if(place==0)
            {
                printf("%03d:10 blue dragon %d reached red headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                printf("%03d:10 red headquarter was taken\n",time);
                pheadquarter->take_the_other=1;
            }
            else
                printf("%03d:10 blue dragon %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            location=pcity[place];
            
        }
    }
}
void ninja::march(int time){
    if(gone==0)
    {
        int place=location->get_number();
        if(pheadquarter->getcolor())
        {
            place++;
            if(place==n+1)
            {
                printf("%03d:10 red ninja %d reached blue headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                printf("%03d:10 blue headquarter was taken\n",time);
                pheadquarter->take_the_other=1;
            }
            else
                printf("%03d:10 red ninja %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            location=pcity[place];
            
        }
        else
        {
            place--;
            if(place==0)
            {
                printf("%03d:10 blue ninja %d reached red headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                printf("%03d:10 red headquarter was taken\n",time);
                pheadquarter->take_the_other=1;
            }
            else
                printf("%03d:10 blue ninja %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            location=pcity[place];
            
        }
    }
    
}
void iceman::march(int time){
    if(gone==0)
    {
        int place=location->get_number();
        int reduce=element/10;
        element-=reduce;
        if(pheadquarter->getcolor())
        {
            place++;
            if(place==n+1)
            {
                printf("%03d:10 red iceman %d reached blue headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                printf("%03d:10 blue headquarter was taken\n",time);
                pheadquarter->take_the_other=1;
            }
            else
                printf("%03d:10 red iceman %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            location=pcity[place];
            
        }
        else
        {
            place--;
            if(place==0)
            {
                printf("%03d:10 blue iceman %d reached red headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                printf("%03d:10 red headquarter was taken\n",time);
                pheadquarter->take_the_other=1;
            }
            else
                printf("%03d:10 blue iceman %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            location=pcity[place];
            
        }
    }
    
}
void lion::march(int time){
    if(gone==0)
    {
        int place=location->get_number();
        if(pheadquarter->getcolor())
        {
            place++;
            if(place==n+1)
            {
                printf("%03d:10 red lion %d reached blue headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                printf("%03d:10 blue headquarter was taken\n",time);
                pheadquarter->take_the_other=1;
            }
            else
                printf("%03d:10 red lion %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            location=pcity[place];
            
        }
        else
        {
            place--;
            if(place==0)
            {
                printf("%03d:10 blue lion %d reached red headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                printf("%03d:10 red headquarter was taken\n",time);
                pheadquarter->take_the_other=1;
            }
            else
                printf("%03d:10 blue lion %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            location=pcity[place];
            
        }
        loyalty-=k;
    }
    
}
void wolf::march(int time){
    if(gone==0)
    {
        int place=location->get_number();
        if(pheadquarter->getcolor())
        {
            place++;
            if(place==n+1)
            {
                printf("%03d:10 red wolf %d reached blue headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                printf("%03d:10 blue headquarter was taken\n",time);
                pheadquarter->take_the_other=1;
            }
            else
                printf("%03d:10 red wolf %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            location=pcity[place];
            
        }
        else
        {
            place--;
            if(place==0)
            {
                printf("%03d:10 blue wolf %d reached red headquarter with %d elements and force %d\n",time,totalNo,element,ATK);
                printf("%03d:10 red headquarter was taken\n",time);
                pheadquarter->take_the_other=1;
            }
            else
                printf("%03d:10 blue wolf %d marched to city %d with %d elements and force %d\n",time,totalNo,place,element,ATK);
            location=pcity[place];
            
        }
    }
    
}
void dragon::attack(warrior * pattack,int x){
    int cnt=0;
    while(1)
    {
        if(wp[x]==NULL)
        {
            x=(x+1)%10;
            cnt++;
            if(cnt==10)
                return;
            continue;
        }
        if(wp[x]->type==0)
        {
            int minus=ATK/5;
            pattack->hurted(minus);
            return;
        }
        else if(wp[x]->type==1)
        {
            int minus1=ATK*2/5;
            int minus2=minus1/2;
            pattack->hurted(minus1);
            hurted(minus2);
            wp[x]=NULL;
            return;
        }
        else if(wp[x]->type==2)
        {
            int minus=ATK*3/10;
            pattack->hurted(minus);
            if(wp[x]->used)
                wp[x]=NULL;
            else
                wp[x]->used=1;
            return;
        }
        x=(x+1)%10;
        cnt++;
        if(cnt==10)
            return;
    }
}
void ninja::attack(warrior * pattack,int x){
    int cnt=0;
    while(1)
    {
        if(wp[x]==NULL)
        {
            x=(x+1)%10;
            cnt++;
            if(cnt==10)
                return;
            continue;
        }
        if(wp[x]->type==0)
        {
            int minus=ATK/5;
            pattack->hurted(minus);
            return;
        }
        else if(wp[x]->type==1)
        {
            int minus1=ATK*2/5;
            pattack->hurted(minus1);
            wp[x]=NULL;
            return;
        }
        else if(wp[x]->type==2)
        {
            int minus=ATK*3/10;
            pattack->hurted(minus);
            if(wp[x]->used)
                wp[x]=NULL;
            else
                wp[x]->used=1;
            return;
        }
        x=(x+1)%10;
        cnt++;
        if(cnt==10)
            return;
    }
}
void iceman::attack(warrior * pattack,int x){
    int cnt=0;
    while(1)
    {
        if(wp[x]==NULL)
        {
            x=(x+1)%10;
            cnt++;
            if(cnt==10)
                return;
            continue;
        }
        if(wp[x]->type==0)
        {
            int minus=ATK/5;
            pattack->hurted(minus);
            return;
        }
        else if(wp[x]->type==1)
        {
            int minus1=ATK*2/5;
            int minus2=minus1/2;
            pattack->hurted(minus1);
            hurted(minus2);
            wp[x]=NULL;
            return;
        }
        else if(wp[x]->type==2)
        {
            int minus=ATK*3/10;
            pattack->hurted(minus);
            if(wp[x]->used)
                wp[x]=NULL;
            else
                wp[x]->used=1;
            return;
        }
        x=(x+1)%10;
        cnt++;
        if(cnt==10)
            return;
    }
}
void lion::attack(warrior * pattack,int x){
    int cnt=0;
    while(1)
    {
        if(wp[x]==NULL)
        {
            x=(x+1)%10;
            cnt++;
            if(cnt==10)
                return;
            continue;
        }
        if(wp[x]->type==0)
        {
            int minus=ATK/5;
            pattack->hurted(minus);
            return;
            
        }
        else if(wp[x]->type==1)
        {
            int minus1=ATK*2/5;
            int minus2=minus1/2;
            pattack->hurted(minus1);
            hurted(minus2);
            wp[x]=NULL;
            return;
        }
        else if(wp[x]->type==2)
        {
            int minus=ATK*3/10;
            pattack->hurted(minus);
            if(wp[x]->used)
                wp[x]=NULL;
            else
                wp[x]->used=1;
            return;
        }
        x=(x+1)%10;
        cnt++;
        if(cnt==10)
            return;
    }
}
void wolf::attack(warrior * pattack,int x){
    int cnt=0;
    while(1)
    {
        if(wp[x]==NULL)
        {
            x=(x+1)%10;
            cnt++;
            if(cnt==10)
                return;
            continue;
        }
        if(wp[x]->type==0)
        {
            int minus=ATK/5;
            pattack->hurted(minus);
            return;
        }
        else if(wp[x]->type==1)
        {
            int minus1=ATK*2/5;
            int minus2=minus1/2;
            pattack->hurted(minus1);
            hurted(minus2);
            wp[x]=NULL;
            return;
        }
        else if(wp[x]->type==2)
        {
            int minus=ATK*3/10;
            pattack->hurted(minus);
            if(wp[x]->used)
                wp[x]=NULL;
            else
                wp[x]->used=1;
            return;
        }
        x=(x+1)%10;
        cnt++;
        if(cnt==10)
            return;
    }
}
void sortp(warrior * sortpw){
    for(int i=0;i<10;i++){
        for(int j=i+1;j<10;j++){
            if(sortpw->wp[j]==NULL)
                continue;
            if(sortpw->wp[i]!=NULL&&sortpw->wp[i]->type>sortpw->wp[j]->type)
            {
                weapon * tmp=sortpw->wp[i];
                sortpw->wp[i]=sortpw->wp[j];
                sortpw->wp[j]=tmp;
            }
            if(sortpw->wp[i]==NULL||(sortpw->wp[i]->used>sortpw->wp[j]->used&&sortpw->wp[i]->type==sortpw->wp[j]->type))
            {
                weapon * tmp=sortpw->wp[i];
                sortpw->wp[i]=sortpw->wp[j];
                sortpw->wp[j]=tmp;
            }
        }
    }
}
void warrior::tp(warrior * tpw){
    sortp(tpw);
    int j=0;
    for(int i=0;i<10;i++)
    {
        if(wp[i]!=NULL)
            continue;
        wp[i]=tpw->wp[j];
        j++;
    }
}
void wolf::takeweapon(int time,warrior * takepw){
    sortp(takepw);
    if(takepw->wp[0]==NULL)
        return;
    int firsttype=takepw->wp[0]->type;
    countweapon();
    int cantake=weaponnum[0]+weaponnum[1]+weaponnum[2];
    if(cantake>=10)
        return;
    int i=0;
    int taken=0;
    while(cantake<10&&i<10&&takepw->wp[i]){
        if(takepw->wp[i]->type!=firsttype)
        {
            i++;
            continue;
        }
        wp[cantake]=takepw->wp[i];
        takepw->wp[i]=NULL;
        taken++;
        cantake++;
        i++;
    }
    if(pheadquarter->getcolor())
        printf("%03d:35 red wolf %d took %d %s from blue %s %d in city %d\n",time,totalNo,taken,weapon::weapon_name[firsttype],warrior::names[takepw->get_typeofw()],takepw->get_totalNo(),location->get_number());
    else
        printf("%03d:35 blue wolf %d took %d %s from red %s %d in city %d\n",time,totalNo,taken,weapon::weapon_name[firsttype],warrior::names[takepw->get_typeofw()],takepw->get_totalNo(),location->get_number());
}
void timeline::tookweapon(int time){
    for(int i=1;i<=n;i++){
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1]&&pcity[i]->pcityw[0]->get_typeofw()==4&&pcity[i]->pcityw[1]->get_typeofw()!=4)
        {
            wolf * tmp=(wolf *)pcity[i]->pcityw[0];
            tmp->takeweapon(time,pcity[i]->pcityw[1]);
        }
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1]&&pcity[i]->pcityw[1]->get_typeofw()==4&&pcity[i]->pcityw[0]->get_typeofw()!=4)
        {
            wolf * tmp=(wolf *)pcity[i]->pcityw[1];
            tmp->takeweapon(time,pcity[i]->pcityw[0]);
        }
    }
}
void timeline::timeproduce(int time,headquarter * pred,headquarter * pblue){
    pred->produce(time);
    pblue->produce(time);
}
void timeline::reportelements(int time,headquarter * preportred,headquarter * preportblue){
    int tmpred=preportred->get_total_value();
    int tmpblue=preportblue->get_total_value();
    printf("%03d:50 %d elements in red headquarter\n",time,tmpred);
    printf("%03d:50 %d elements in blue headquarter\n",time,tmpblue);
}
void timeline::reportweapon(int time){
    for(int i=0;i<=n+1;i++)
    {
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[0]->gone==0)
        {
            pcity[i]->pcityw[0]->countweapon();
            pcity[i]->pcityw[0]->print_weapon(time);
        }
        if(pcity[i]->pcityw[1]&&pcity[i]->pcityw[1]->gone==0)
        {
            pcity[i]->pcityw[1]->countweapon();
            pcity[i]->pcityw[1]->print_weapon(time);
        }
    }
}
void timeline::reportlion(int time){
    for(int i=0;i<=n+1;i++)
    {
        if(pcity[i]->pcityw[0]!=NULL&&pcity[i]->pcityw[0]->get_typeofw()==3&&pcity[i]->pcityw[0]->gone==0)
        {
            lion * tmp=(lion *)pcity[i]->pcityw[0];
            int seek=tmp->get_loyalty();
            if(seek<=0)
            {
                printf("%03d:05 red lion %d ran away\n",time,pcity[i]->pcityw[0]->get_totalNo());
                pcity[i]->pcityw[0]->gone=1;
                pcity[i]->pcityw[0]=NULL;
            }
        }
        if(pcity[i]->pcityw[1]!=NULL&&pcity[i]->pcityw[1]->get_typeofw()==3&&pcity[i]->pcityw[1]->gone==0)
        {
            lion * tmp=(lion *)pcity[i]->pcityw[1];
            int seek=tmp->get_loyalty();
            if(seek<=0)
            {
                printf("%03d:05 blue lion %d ran away\n",time,pcity[i]->pcityw[1]->get_totalNo());
                pcity[i]->pcityw[1]->gone=1;
                pcity[i]->pcityw[1]=NULL;
            }
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
            marchred->pw[i]->location->pcityw[0]=marchred->pw[i];
        if(marchblue->pw[i]&&marchblue->pw[i]->gone==0)
            marchblue->pw[i]->location->pcityw[1]=marchblue->pw[i];
        i++;
    }
    pcity[0]->pcityw[0]=NULL;
    pcity[n+1]->pcityw[1]=NULL;
    if(marchred->take_the_other||marchblue->take_the_other)
        endofgame=1;
}

void timeline::reportbattle(int time){
    for(int i=1;i<=n;i++){
        if(pcity[i]->pcityw[0]&&pcity[i]->pcityw[1]&&pcity[i]->pcityw[0]->gone==0&&pcity[i]->pcityw[1]->gone==0)
            pcity[i]->battle(time);
    }
}
void city::battle(int time){
    bool first;
    if(number%2)
        first=0;
    else
        first=1;
    sortp(pcityw[0]);
    sortp(pcityw[1]);
    int wpp[2]={0};
    while(1){
        int tmp0=pcityw[0]->get_element();
        int tmp1=pcityw[1]->get_element();
        pcityw[first]->attack(pcityw[!first],wpp[first]);
        if(pcityw[!first]->get_element()<=0&&pcityw[first]->get_element()>0)
        {
            pcityw[!first]->gone=1;
            pcityw[first]->tp(pcityw[!first]);
        }
        if(pcityw[!first]->get_element()<=0&&pcityw[first]->get_element()<=0)
        {
            pcityw[!first]->gone=1;
            pcityw[first]->gone=1;
        }
        if(pcityw[!first]->gone||pcityw[first]->gone)
            break;
        pcityw[!first]->attack(pcityw[first],wpp[!first]);
        if(pcityw[first]->get_element()<=0&&pcityw[!first]->get_element()>0)
        {
            pcityw[first]->gone=1;
            pcityw[!first]->tp(pcityw[first]);
        }
        if(pcityw[first]->get_element()<=0&&pcityw[!first]->get_element()<=0)
        {
            pcityw[first]->gone=1;
            pcityw[!first]->gone=1;
        }
        if(pcityw[first]->gone||pcityw[!first]->gone)
            break;
        int tmpcnt0=0;
        int tmpcnt1=0;
        for(int z=0;z<10;z++){
            if(pcityw[0]->wp[z]&&pcityw[0]->wp[z]->type!=0)
            tmpcnt0++;
            if(pcityw[1]->wp[z]&&pcityw[1]->wp[z]->type!=0)
            tmpcnt1++;
        }
        if(tmp0==pcityw[0]->get_element()&&tmp1==pcityw[1]->get_element()&&tmpcnt0==0&&tmpcnt1==0)
            break;
        wpp[0]=(wpp[0]+1)%10;
        wpp[1]=(wpp[1]+1)%10;
    }
    if(pcityw[0]->gone&&(pcityw[1]->gone==0))
    {
        printf("%03d:40 blue %s %d killed red %s %d in city %d remaining %d elements\n",time,warrior::names[pcityw[1]->get_typeofw()],pcityw[1]->get_totalNo(),warrior::names[pcityw[0]->get_typeofw()],pcityw[0]->get_totalNo(),number,pcityw[1]->get_element());
        if(pcityw[1]->get_typeofw()==0)
            printf("%03d:40 blue dragon %d yelled in city %d\n",time,pcityw[1]->get_totalNo(),number);
    }
    else if(pcityw[0]->gone==0&&pcityw[1]->gone)
    {
        printf("%03d:40 red %s %d killed blue %s %d in city %d remaining %d elements\n",time,warrior::names[pcityw[0]->get_typeofw()],pcityw[0]->get_totalNo(),warrior::names[pcityw[1]->get_typeofw()],pcityw[1]->get_totalNo(),number,pcityw[0]->get_element());
        if(pcityw[0]->get_typeofw()==0)
            printf("%03d:40 red dragon %d yelled in city %d\n",time,pcityw[0]->get_totalNo(),number);
    }
    else if(pcityw[0]->gone==0&&pcityw[1]->gone==0)
    {
        printf("%03d:40 both red %s %d and blue %s %d were alive in city %d\n",time,warrior::names[pcityw[0]->get_typeofw()],pcityw[0]->get_totalNo(),warrior::names[pcityw[1]->get_typeofw()],pcityw[1]->get_totalNo(),number);
        if(pcityw[0]->get_typeofw()==0)
            printf("%03d:40 red dragon %d yelled in city %d\n",time,pcityw[0]->get_totalNo(),number);
        if(pcityw[1]->get_typeofw()==0)
            printf("%03d:40 blue dragon %d yelled in city %d\n",time,pcityw[1]->get_totalNo(),number);
    }
    else
        printf("%03d:40 both red %s %d and blue %s %d died in city %d\n",time,warrior::names[pcityw[0]->get_typeofw()],pcityw[0]->get_totalNo(),warrior::names[pcityw[1]->get_typeofw()],pcityw[1]->get_totalNo(),number);
}

int main()
{
    int CaseNo;
    int t;
    cin>>t;
    for(int o=1;o<=t;o++)
    {
        endofgame=0;
        memset(pcity,0,sizeof(pcity));
        CaseNo=o;
        printf("Case %d:\n",CaseNo);
        cin>>m>>n>>k>>T;
        headquarter red(m,1);
        headquarter blue(m,0);
        headquarter * pred=&red;
        headquarter * pblue=&blue;
        for(int i=0;i<n+2;i++)
            pcity[i]=new city(i);
        red.changephcity(pcity[0]);
        blue.changephcity(pcity[n+1]);
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
                case 35:timeloop.tookweapon(time);break;
                case 40:timeloop.reportbattle(time);break;
                case 50:timeloop.reportelements(time,pred,pblue);break;
                case 55:timeloop.reportweapon(time);break;
            }
            
            if(60*time+timeline::echomoment[timeloop.cur]>=T)
                break;
            timeloop.cur++;
            if(timeloop.cur==7)
            {
                timeloop.cur=0;
                time++;
            }
            if(endofgame)
                break;
        }
    }
    return 0;
}