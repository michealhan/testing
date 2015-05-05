#include<iostream>
#include<fstream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include<windows.h>
using namespace std;
double item[1000],person[50],test,test2,zj[1000];

double gaussrand()
{
    static double V1, V2, S;
    static int phase = 0;
    double X;
    V1=0.0;
    V2=0.0;
    S=0.0;
    X=0.0;
    phase = 0;
    //srand(time(0));
    if ( phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;

            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);

        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);

    phase = 1 - phase;

    return X;
}

int Initialize()
{
    ifstream in("test_item_person.txt");
    //ofstream out("question_full_data_E_TEST.txt");
    char buffer[256];
    double data_true,data_false,pun;
    pun=0.05;
    int temp,a,b,c;
    temp=0;
    data_false=0;
    data_true=0;
    while(!in.eof())
    {
        in.getline(buffer,20);
        sscanf(buffer,"%d %d %d",&a,&b,&c);
        if (temp!=a)
        {
            double judge_item_true;
            judge_item_true=exp(data_true)/(exp(data_false)+exp(data_true));
            zj[temp]=judge_item_true;
            temp=a;
            data_false=0;
            data_true=0;
        }
        if (temp==a)
        {
            if (c==1)
            {
                data_true-=log(1+exp(-item[a]*person[b]));
                data_false+=log(1-1/(1+exp(-item[a]*person[b])));
            }
            else
            {
                data_false-=log(1+exp(-item[a]*person[b]));
                data_true+=log(1-1/(1+exp(-item[a]*person[b])));
            }
        }
        if (a==999)
        {
            zj[a]=exp(data_true)/(exp(data_false)+exp(data_true));
        }

    }
    /*for (int l=1;l<42625;l++)
    {
        out<<l<<" "<<zj[l]<<endl;
    }
    in.close();*/
    //out.close();
}

int Max()
{
    //========================================================================================================item
    double learning_rate,sum,t;
    learning_rate=0.005;
    sum=0;
    ifstream in("test_item_person.txt");
    //ofstream out("question_full_data_E_TEST.txt");
    char buffer[256];
    int temp,a,b,c;
    temp=0;
    while(!in.eof())
    {
        in.getline(buffer,20);
        sscanf(buffer,"%d %d %d",&a,&b,&c);
        if (temp!=a)
        {
            t = item[temp]-1;
            item[temp]+=((sum-pun*t)*learning_rate)/4;
            if (item[temp]<0)
                item[temp]=0;
            temp=a;
            sum=0;
        }
        if (temp==a)
        {
            if (c==1)
                sum+=((person[b]*exp(-person[b]*item[a]))*(2*zj[a]-1))/(1+exp(-person[b]*item[a]));
            if (c==0)
                sum+=((person[b]*exp(-person[b]*item[a]))*(1-2*zj[a]))/(1+exp(-person[b]*item[a]));
        }
        if (a==999)
        {
            t = item[999]-1;
            item[a]+=(sum*learning_rate)/4;
            if (item[a]<0)
                item[a]=0;
            sum=0;
        }

    }
    in.close();

    //============================================================================================================person
    ifstream in2("test_person_item.txt");
    temp=0;
    sum=0;
    while(!in2.eof())
    {
        in2.getline(buffer,20);
        sscanf(buffer,"%d %d %d",&a,&b,&c);
        if (temp!=b)
        {
            double avoidp=person[temp];
            person[temp]+=((sum)*learning_rate)/5;
            temp=b;
            sum=0;
        }
        if (temp==b)
        {
            if (c==1)
                sum+=((item[a]*exp(-person[b]*item[a]))*(2*zj[a]-1))/(1+exp(-person[b]*item[a]));
            if (c==0)
                sum+=((item[a]*exp(-person[b]*item[a]))*(1-2*zj[a]))/(1+exp(-person[b]*item[a]));
        }
        if (b==49)
        {
            double avoidp=person[b];
            person[b]+=((sum)*learning_rate)/5;
            sum=0;
        }

    }
    in2.close();
}

int main()
{
    srand((unsigned)time(0));

    //====================================================================================================initial
    for (int i=0;i<50;i++)
    {
        double testb;
        testb=gaussrand()*0.01+1;
        person[i]=testb;
    }
    ofstream out5("test_person_initial====.txt");
    for (int han2=0;han2<50;han2++)
    {
        out5<<han2<<" "<<person[han2]<<endl;
    }
    out5.close();
    for (int j=0;j<1000;j++)
    {
        double testc;
        testc=gaussrand()*0.01+1;
        item[j]=testc;
    }
    ofstream out4("test_item_initial====.txt");
    for (int han2=0;han2<1000;han2++)
    {
        out4<<han2<<" "<<item[han2]<<endl;
    }
    out4.close();
    for (int k=0;k<1000;k++)
    {
        zj[k]=-1;
    }
    for (int han=0;han<40;han++)
    {
        cout<<han<<endl;
        //======================================================================================================E
        Initialize();
        //======================================================================================================M
        Max();
    }
    ofstream out("test_result===============.txt");
    for (int han2=0;han2<1000;han2++)
    {
        out<<han2<<" "<<zj[han2]<<endl;
    }
    out.close();
    ofstream out2("test_person_result==============.txt");
    for (int han2=0;han2<50;han2++)
    {
        out2<<han2<<" "<<person[han2]<<endl;
    }
    out2.close();
    ofstream out3("test_item_result===============.txt");
    for (int han2=0;han2<1000;han2++)
    {
        out3<<han2<<" "<<item[han2]<<endl;
    }
    out3.close();
    return 0;
}
