#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define CL "CLS"//清理屏幕函数 Windeo CLS linux 用clear
#define ST "选手:"
//打分 系统

//设置选手
typedef struct stu
{
    char name[81];//名字
    int numb;//编号
    int score[10];//分数这里存放的是分数
   // int average[10];//场次平均分
    float accumulate;//平均分
}Stu;
int dell=0;//定义全局变量用来判断步骤
Stu *pair_stu(int n);//返回一个学生数组
int get_menu(void);//菜单函数
void Play_game(Stu *p,int num,int *del);//输入分数
void clean(void);//清空输入函数
void Position(Stu *p,int num,int *del);//打印函数
void Play_average(Stu *p,int num,int *del);//计算平均分
void PrintStu(Stu *p,int num,int *del);//显示选手的最后得分
void Delete_if(Stu *p,int *num,int *dell);//这里num 使用指针 因为要修改其数据 并且dell 如果需要查看数据将对数据dell重新赋值
void delete_numb(Stu *p,int *num,int *dell);//按照编号删除成绩
void swap(Stu *p1,Stu *p2);//交换函数
void delete_acc(Stu *p,char *num,char *dell);//删除平均分数低于6.0的所有人
void sort(Stu *p,int num);//成绩排序
void delete_zero(Stu *p,int *num,int *dell);//有0分成绩的选手
void Prsition(Stu *p,int num);//成绩排名函数
int main()
{
 int num=0,m;//比赛人数
 int ch;
 //int *p=NULL;//存放晋级名单不考虑晋级情况
 printf("欢迎使用评分系统！\n");
 printf("请输入需要比赛的人数\n");
 scanf("%d",&num);
 m=num;//保存最初人数用以打印成绩
 Stu *stu=pair_stu(num);//返回数组并且初始化
 getchar();//主要用于交互
 printf("您已确定人数 共 %d 个人参加比赛,按回车开始比赛\n",num);
 getchar();
 system(CL);//清屏幕函数

 //进入菜单 get_menu 函数是菜单函数 返回int 类型的值
 while((ch=get_menu())!=6)
 {
 switch(ch)
 {
 case 1:
     Play_game(stu,num,&dell);//存放分数
     break;
 case 2:
     Play_average(stu,num,&dell);//计算平均分
     break;
 case 3:
     PrintStu(stu,num,&dell);//显示选手最后得分
     break;
 case 4:
    Delete_if(stu,&num,&dell);//删除指定选手需要修改选手个数
     break;
 case 5:
     Prsition(stu,num);
     break;
 default:
     break;
 }

 }
 puts("再见吧！");

 //释放内存
 //free(p);
 free(pair_stu);
    return 0;
}
//选手初始化函数
Stu *pair_stu(int n){

    int i=0;
    char tame[10];//存放编号字符
    Stu *s=(Stu *)malloc(n*sizeof(struct stu));
    //对数据初始化
    for(;i<n;i++)
    {
        int tem=1000+i;
        strcpy((s+i)->name,ST);//将选手拷贝进name
        sprintf(tame,"%d",tem);//将字符转换成字符串
        strcat((s+i)->name,tame);//将名字字符串拼接成字符串
      //  printf("%s\n",(s+i)->name);检测 名称代码

        (s+i)->numb=tem;//编号放入
        memset((s+i)->score,0,sizeof((s+i)->score));//对成绩数组归零操作
        (s+i)->accumulate=0;//总分置零
    }
    return s;

};
//菜单函数

int get_menu(void)
{
system(CL);//清空屏幕
 int ch;
  printf(" *********************************请选择操作代码***********************************\n");
  printf("                              * 1.输入分数\n");
  printf("                              * 2.计算平均分\n");
  printf("                              * 3.显示选手最后得分\n");
  printf("                              * 4.删除无效选手成绩\n");
  printf("                              * 5.显示选手排名次序\n");
  printf("                              * 6.退出系统\n");
  printf("***********************************************************************************\n");
scanf("%d",&ch);
 clean();//输入后结束后面所有的输入 包括回车
  while(1)
  {
      if(ch>=1 &&ch<=6)
      {
          return ch;
      }
      else
      {
          printf("                     请输入1-6位数字\n");
          ch=get_menu();
          system(CL);
          return ch;

      }
  }
}
//存放分数

void Play_game(Stu *p,int num,int *del)//这里P是结构体数组指针， num 是参赛人数
{
    srand(time(NULL));//时间种子用以随机数
    system(CL);//清空菜单
    int i=0,j,sum=0;
    char ch;
    (*del)=1;//赋值为1
    printf("如需要自动 打分请按 '1' 按其他键进入 自动输入\n ");
    ch=getch();
    if(ch=='1')
    {
        for(i=0;i<num;i++)
        {
            for(j=0;j<10;j++)
            {
                (p+i)->score[j]=rand()%10;//0-10
            }
        }
       for(i=0;i<num;i++)
       {
            printf(" %s 的分数为\n",(p+i)->name);

           for(j=0;j<10;j++)
           {
               printf("%d  ",(p+i)->score[j]);
           }
           puts("\n");
       }
       printf("按任意键开始下一步\n");
         clean();
        system(CL);
    }
    else {

    for(i=0;i<num;i++)
    {
        printf("请给 %s 打分\n",(p+i)->name);//打印选手名称
        for(j=0;j<10;j++)//共10次打分
        {

              scanf("%d",&sum);
              printf("进入循环");
              if(sum>=0 && sum<=10)
                {
                   (p+i)->score[j]=sum;
                }
                else
                {
                    printf("请输入 0-10的分值 本次分值作废请重新输入 %s 的分值\n",(p+i)->name);
                     j=0;//将循环条件置零 重新循环一次
                  clean();//键盘清空
                }
            }
            clean();

    }

}
}

void clean(void)
{
    char ch;
    while((ch=getchar())!='\n') //舍弃后面所有输入
        continue;
}

//计算平均分
void Play_average(Stu *p,int num,int *del)
{
    system(CL);
    if(*del==0)
    {
        printf("请先增加成绩在求平均分\n");
        getchar();
        return;
    }
    (*del)=2;//赋值为2 表示第二步
    int i=0,j,k,sum=0,temp;
    int b[10];

    //这里使用选择排序去掉最高分和最低分
    for(k=0;k<num;k++)//进入结构体循环
    {
        memset(b,0,sizeof(b));//将内存初始化
        for(i=0;i<10;i++)
        {
            b[i]=(p+k)->score[i];//将数据拷贝给数组b
        }

        for(i=0;i<10;i++)
        {
           temp=i;//指向一个结构体的分数数组的0的位置下标 p+i是指针
            for(j=temp;j<10;j++)
            {
                temp=b[j]<b[temp]? j:temp;//三木运算比较最大的值

            }
           if(temp!=i)//也就是现在temp=j
           {
               int tm;
               tm=b[i];
               b[i]=b[temp];
               b[temp]=tm;
           }

        }

        sum=0;
        for(i=1;i<9;i++)//计算平均分 从下标1开始到 8结束去掉最高分和最低分
        {
            sum+=b[i];//计算总值
        }
        (p+k)->accumulate=(float)sum/8.0;//((sizeof((p+k)->score))/sizeof(int)-2) 直接除8 省事

    }

    for(i=0;i<num;i++)
    {
         printf(" %s 的平均分数为:\t",(p+i)->name);

            printf("%.2f",(p+i)->accumulate);
        puts("\n");
    }
    getchar();
}
//显示选手的最后评分 名字 编号 评分
void PrintStu(Stu *p,int num,int *del)

{
    int i,k;
    if(*del!=2)//如果没有进行第二步则返回
    {
        printf("请先打分，获取平均分后再进行操作，按任意键返回上级\n");
        getchar();//等待信号
        return;
    }
    *del=3;//赋值为3 表示第三部
    for(i=0;i<num;i++)
    {
        printf("编号: %d\t",(p+i)->numb);
        printf("%s\t",(p+i)->name);
        printf("最后得分为:%d \n",(p+i)->score[9]);
    }
printf("按任意键继续.....\n");
getchar();
}
//条件删除
void  Delete_if(Stu *p,int *num,int *dell)

{
    //先判断是否有已经有数据
    if(*dell<1 )
    {
        printf("请先进行打分\n");
        getchar();
        return;
    }
   int sum=0,i,j;
   printf("请选择操作\n");
   while(1)
   {
       system(CL);//屏幕清空
       printf("***********************************************************\n");
       printf("******************** 1、 按编号删除选手成绩  ******************\n");
       printf("*********************2、 平均分低于6分的选手成绩****************\n");
       printf("*********************3、 成绩中有0分的选手成绩******************\n");
       printf("*********************4、 ****返回菜单*************************\n");

       scanf("%d",&sum);
       clean();
       switch(sum)
       {
        case 1:
           delete_numb(p,num,dell);//这里的参数都是指针
           break;
       case 2:
           delete_acc(p,num,dell);//平均分低于6
           break;
       case 3:
          delete_zero(p,num,dell);//有0分成绩的选手
           break;
       case 4:
           return;
       default:printf("您输入有误，请重新输入\n");
                getchar();
          break;

       }
   }
}
//按照编号删除成绩
void delete_numb(Stu *p,int *num,int *dell)
{

    system(CL);//清空屏幕
    Stu s;//创建一个结构体临时存放数据
    int sum,i,j;
    printf("请输入您要删除的编号\n");
    for(i=0;i<*num;i++)
    {
        printf("%d \t",(p+i)->numb);
        if(i%5==0)
            puts("\n");//每隔5个就进行一次回车
    }
    scanf("%d",&sum);
    for(i=0;i<*num;i++)
    {
        if(sum==((p+i)->numb))//如果查到了这个数据 就将最后的数据和他替换
        {
           swap((p+i),(p+(*num-1)));//这里传入的是下标指针所以需要-1
            *num--;
           printf("删除成功\n");
            clean();//清空输入流
            *dell=1;//将步骤放到1的位置
           return;
        }

    }
    printf("未找到数据 或输入有误 请重新输入\n");
    getchar();

}
void swap(Stu *p1,Stu *p2)//交换函数
{
    Stu s;
    int j;
    strcpy(s.name,p1->name);//最后一个数据的名字
    s.numb=p1->numb;//编号赋值
    for(j=0;j<10;j++)
    {
       s.score[j]=p1->score[j];//分数赋值
    }
    s.accumulate=p1->accumulate;//平均分赋值
    /***************************************/
    strcpy(p1->name,p2->name);//最后一个数据的名字
    p1->numb=p2->numb;//编号赋值
    for(j=0;j<10;j++)
    {
        p1->score[j]=p2->score[j];//分数赋值
    }
    p1->accumulate=p2->accumulate;//平均分赋值
    /****************************************/
    strcpy(p2->name,s.name);//最后一个数据的名字
    p2->numb=s.numb;//编号赋值
    for(j=0;j<10;j++)
    {
        p2->score[j]=s.score[j];//分数赋值
    }
    p2->accumulate=s.accumulate;//平均分赋值
}
//删除平均分低于6.0的所有人
void delete_acc(Stu *p,char *num,char *dell)
{
    if(*dell<1)
    {
        clean();
        printf("未计算平均数，请先计算平均数在进行删除\n");
        getchar();
        return;
    }
    int i,m=*num,j=0;

    float f=6.0;
    sort(p,*num);//排序从大到小

    for(i=0;i<m;i++)
    {
        if((p+i)->accumulate<f)
            break;//如果小于了就不在读取了

    }
    clean();//清除键盘缓存 不然后面的数据看不到
    *num=i;
    printf("成功删除平均值小于6.0 的选手成绩\n");
   /* for(i=0;i<*num;i++)
    {
        printf("%s\t",(p+i)->name);
        printf("%f\n",(p+i)->accumulate);
    }*/
    getchar();
    }


//成绩排序
void sort(Stu *p,int num)
{   //选择

    int i=0,j,temp;
    for(i=0;i<num;i++)
    {
        temp=i;
        for(j=temp;j<num;j++)
        {
            temp=((p+j)->accumulate)>((p+temp)->accumulate) ?j:temp;
        }
        if(temp!=i)//如果改变了
        {
            swap((p+i),(p+temp));//交换函数
        }
    }
  /*  printf("交换函数\n");

    */ //测试代码
}

void delete_zero(Stu *p,int *num,int *dell)//有0分成绩的选手
{
    if(*dell<0)
    {
        printf("请先输入成绩在进行删除操作\n");
        getchar(); return;
    }
    char ch;
    printf("删除成绩有0分的选手会彻底修改选手命运，请慎重操作 按任意键继续\n");
    clean();//先清空键盘流
    printf("如果返回请按 1 按其他则执行删除操作\n");
    ch=getchar();
    if(ch=='1')
        return;
    int j,i,zero=0,m=*num,k=0;
    Stu *s=pair_stu(m);//创建了一个结构数组指针

    for(j=0;j<m;j++)
    {
        zero=0;
       for(i=0;i<10;i++)
       {
           if(((p+j)->score[i])==0)
           {
               zero=1;
               break;
           }
       }
       if(zero!=1)//如果zero 为0
       {
           swap((s+k),(p+j));
           k++;
       }
    }

    *num=k;//将选手数据进行修改
    for(i=0;i<k;i++)
    {
       swap((p+i),(s+i));//将没有0的数据拷贝过来
    }
    free(s);//释放内存
   printf("成绩为0的已删除完毕 按任意键继续\n");
   clean();

}

//打印排名
void Prsition(Stu *p,int num)
{
   int i;
   sort(p,num);
   for(i=0;i<num;i++)
   {
       printf("第%d名:\t",i+1);
       printf("%s\n",(p+i)->name);
       printf("编号:%d\t",(p+i)->numb);
       printf("总成绩为 :%.2f\n",(p+i)->accumulate);

   }
   clean();
}
