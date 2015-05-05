#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    ifstream in("test_item_person.txt");
    ofstream out("test_most_result.txt");
    char buffer[256];
    int a,b,d,c,temp,t,f;
    d=0;
    t=0;
    f=0;
    //while(!in.eof())
    out<<"ID "<<" ? "<<"t "<<" f"<<endl;
    while(!in.eof())
    {
        in.getline(buffer,20);
        sscanf(buffer,"%d %d %d",&a,&b,&c);
        if (d!=a)
        {
            //cout<<a<<endl;
            if (t>f)
              out<<d<<" "<<1<<" "<<t<<" "<<f<<endl;
            if (t<f)
              out<<d<<" "<<0<<" "<<t<<" "<<f<<endl;
            if (t==f)
              out<<d<<" "<<0.5<<" "<<t<<" "<<f<<endl;
            t=0;
            f=0;
            d=a;
        };

        if (c==1)
            t+=1;

        if(c==0)
            f+=1;

    }
    cout<<"1"<<endl;
    in.close();
    out.close();
    return 0;
}
