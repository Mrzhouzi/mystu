#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <stdlib.h>//随机数
#include <conio.h>
#include <vector>
#include <iterator>
#include <numeric>//提供计算和的函数
#include <time.h>
#include <algorithm>//算法头文件
#include <sstream>//将数字转换成字符串
#define CL "CLS"
using namespace std;

//创建一个学生类

class Student
{
public:
    int stnuber;//学号
    string name;//名字
    map<string,float> stum;//各科成绩
    float average;//平均分
public:
    Student(int stnuber,string name)//有参构造
    {
        this->stnuber=stnuber;
        this->name=name;
        this->average=0;
    }
    Student()
    {
        //无参构造
    }
 bool operator<(Student &ob)//重载 小于号
 {
     return this->average<ob.average;
 }
};
void clean(void);//清空输入缓存
void stu_insert(map<int,Student> &m);//放置学生信息
void test(void);//主启动函数
int get_menu(void);//菜单函数
void stu_rand(map<int,Student> &m,int sum,vector<string> &v,int s);//随机存取函数
void stu_revise(map<int,Student> &m);//通过查找学号修改学生信息
void printfStudent(map<int,Student> &m);//查看所有学生成绩
void printfcourse(map<int,Student> &m);//各科最高分 最小值，平均分
int main()
{
   //需要一个菜单进入函数
 test();
    return 0;
}


int get_menu(void)
{
system(CL);//清空屏幕
 int ch;
  printf(" **************************欢迎来到学生成绩管理系统***********************************\n");
  printf("                              * 1.录入学生成绩信息\n");
  printf("                              * 2.通过学号修改学生信息\n");
  printf("                              * 3.查看所有学生成绩\n");
  printf("                              * 4.各科成绩预览\n");
//  printf("                              * 5.显示选手排名次序\n");
  printf("                              * 5.退出系统\n");
  printf("***********************************************************************************\n");
cin>>ch;
getchar();
  while(1)
  {
      if(ch>=1 &&ch<=5)
      {
          return ch;
      }
      else
      {
          printf("                     请输入1-5位数字\n");
          getchar();
          ch=get_menu();
          system(CL);
          return ch;

      }
  }
}

void test(void)
{
   int ch;
   map<int,Student> m;//创建map 容器放置学生信息
   while((ch=get_menu())!=5)
   {
         switch(ch)
    {
         case 1://录入学生信息
             stu_insert(m);
           break;
         case 2:
             stu_revise(m);//修改学生数据
             break;
         case 3:
             printfStudent(m);//查看所有学生成绩
             break;
         case 4:
             printfcourse(m);//查看课程最高最低分
             break;
         default:
             break;

        }

    }
   cout<<"拜拜\n";
   getchar();
}
void stu_insert(map<int,Student> &m)//放置学生信息
{
    system(CL);
    int sum,subject,i;
    vector<string> v;//创建一个数组放置科目；
    string s;
    cout<<"请输入需要输入的学生个数:"<<endl;
    cin>>sum;
    cout<<"请输入科目个数\n";
    cin>>subject;
    for(i=1;i<=subject;i++)//将要存放的科目放进去
    {
        cout<<"请输入第"<<i<<"个科目为:"<<endl;
        cin>>s;
        v.push_back(s);//尾插
    }
    i=0;
    cout<<"如需随机填充数据请 按1，否则按任意数字输入学生名称以及各科成绩";
    cin>>i;
    if(i==1)//随机存储数据
    {
        stu_rand(m,sum,v,subject);//随机放置各科成绩
    }
    else
    {
        int stu=0;//存放学生编号
        float score=0.0;//存放成绩
        string stu_name;
        float grade=0.0;

       for(i=0;i<sum;i++)
       {   cout<<"请输入学号:"<<endl;
           cin>>stu;
           cout<<"请输入学号:"<<stu<<"的名字"<<endl;
           cin>>stu_name;
           m.insert(make_pair(stu,Student(stu,stu_name)));//存放编号和名字
           cout<<"请输入 学号:"<<stu<<"\t 姓名:"<<stu_name<<"各科成绩"<<endl;
           grade=0.0;//将总成绩置零
          for(auto it=v.begin();it!=v.end();it++)//迭代器循环//使用auto 代替 vector<string>::iterator
          {
              cout<<(*it)<<"成绩为:\n";
              cin>>score;
              (m[stu].stum).insert(make_pair((*it),score));//将成绩存放到学生的map 容器中
              grade+=score;
              score=0;
          }
            m[stu].average=grade/subject;//将平均分放入学生的数据中
            cout<<"学号:"<<stu<<endl;
            cout<<"姓名:"<<m[stu].name<<endl;
            map<string,float>::iterator itm=m[stu].stum.begin();//遍历刚才输入的数据防止出错
            for(;itm!=m[stu].stum.end();itm++)
            {
                cout<<(*itm).first<<" 成绩为: "<<(*itm).second<<endl;
            }
           cout<<"按回车继续\n";
            clean();
           getchar();
           system(CL);
       }

    }

}
//模拟随机数据
void stu_rand(map<int,Student> &m,int sum,vector<string> &v,int s)
{
  srand(time(nullptr));
  int i;

  int stu=0;//学生编号
  float f=0.0,sf=0.0;
  for(i=0;i<sum;i++)//学生数量循环
  {
      string stu_name="学生:";
      string str;//学生编号字符串
      stu=i+1000;
      str=to_string(stu);//to_string 和sprint 功能一样将数字转换成字符串 也可以自己写这个代码 比较麻烦
      stu_name=stu_name+str;//字符串相加
      m.insert(make_pair(stu,Student(stu,stu_name)));//将数据放入map 容器
       for(vector<string>::iterator it=v.begin();it!=v.end();it++)//将学生的课程遍历
       {
           f=rand()%100+rand()%10*0.1;//返回小数点问题
           m[stu].stum.insert(make_pair((*it),f));
           sf+=f;//保存总数
       }


       m[stu].average=sf/s;//将平均分放入数据
       //cout<<m[stu].average<<endl;
       //getchar();
       sf=0.0;//总数置零
  }
  cout<<"虚拟学生成绩已放置完毕"<<endl;
  clean();
  getchar();
}

void clean(void)
{
    char ch;
    while((ch=getchar())!='\n') continue;
}

void stu_revise(map<int,Student> &m)//通过学号修改学生信息
{
    int sum;
    string name;
    cout<<"请输入需要修改的学生的学号\n";
    cin>>sum;
    if(m.find(sum)==m.end())
    {
        cout<<"未找到该学生学号，请返回重试"<<endl;
        return;//返回上级
    }
    cout<<"请对学生"<<m[sum].name<<" 的数据进行修改"<<endl;
    cout<<"请输入学生姓名\n";
    cin>>name;
    m[sum].name=name;
    for(map<string,float>::iterator itm=m[sum].stum.begin();itm!=m[sum].stum.end();itm++)
    {
        cout<<"请对 学生"<<m[sum].name<<"的"<<(*itm).first<<" 成绩重新录入"<<endl;
        cin>>(*itm).second;
    }
    map<string,float>::iterator it=m[sum].stum.begin();//遍历刚才输入的数据防止出错
    for(;it!=m[sum].stum.end();it++)
    {
        cout<<(*it).first<<" 成绩为: "<<(*it).second<<endl;
    }
    clean();//清空输入数据
    getchar();
}

void printfStudent(map<int,Student> &m)
{
    //这里需要排序所以使用vector
    system(CL);//清空屏幕
    for(map<int,Student>::iterator it=m.begin();it!=m.end();it++)
    {
        cout<<"学号:"<<(*it).first<<endl;
        cout<<"姓名:"<<(*it).second.name<<endl;
        vector<float> v;//用于存放成绩
        for(auto item=(*it).second.stum.begin();item!=(*it).second.stum.end();item++)
            //这里atuo 代表map<string,float>::iterator
        {
           cout<<(*item).first<<" 成绩为: ";
           printf("%.1f\n",(*item).second);//cout打印浮点型可能有问题直接使用printf了
           v.push_back((*item).second);//存放数据
        }
        sort(v.begin(),v.end());//排序
        cout<<"最高成绩为: ";
        printf("%.1f\n",(float)v.back());//返回最后一个数据
        cout<<"最低成绩为: ";
        printf("%.1f\n",(float)v.front());//返回第一个数据
        cout<<"平均成绩为:";
        printf("%.1f\n",((*it).second).average);
        //cout<<(*it).second.average;//因平均数第一次用的数据类型是int 类型二次修改为float
        v.resize(0);//将容器中数据清空但容器不会释放内存
        cout<<endl;

    }
    clean();
    getchar();
}
void printfcourse(map<int,Student> &m)//打印各科的数据
{
   int i;
    vector<string> v;//存放课程


    map<int,Student>::iterator itm=m.begin();//获取m的迭代器
    for(map<string,float>::iterator it=((*itm).second.stum).begin();it!=((*itm).second.stum).end();it++)//获取课程
    {

      v.push_back((*it).first);//课程放入数据

    }

   for(vector<string>::iterator itv=v.begin();itv!=v.end();itv++)
       //遍历课程因为不知道课程的数量所以需要将全部课程挨个加一遍
   {
        vector<float> f;
       //cout<<"循环之前"<<endl;
      for(auto itm=m.begin();itm!=m.end();itm++)//遍历学生
       {
           i++;//统计学生数量
           f.push_back((*itm).second.stum[*itv]);
          // cout<<(*itm).second.stum[*itv];
           //这里(*itm).second.stum[*itv]是代表map容器中的第二个元素中Student对象的stum成员
           //该成员也是map容器，而其键值是string的课程类型 而迭代器 itv也是课程 所以直接通过键值的课程直接将对应的分数放入
       }
         sort(f.begin(),f.end());//排序
         cout<<"课程: "<<(*itv)<<endl;
         cout<<"最高分为:"<<f.back()<<endl;
         cout<<"最低分为:";
         printf("%.1f\n",(float)f.front());
         cout<<"平均分为：";
         cout<<(float)accumulate(f.begin(),f.end(),0)/i<<endl;
            i=0;//学生置零
            f.clear();//容器置零
            cout<<endl;

   }
   clean();
   getchar();

}
