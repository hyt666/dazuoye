//
// Created by 涛涛的水 on 2019/12/11.
//

#ifndef PYTHON_INTERPRETER_BIGINTAGER_H
#define PYTHON_INTERPRETER_BIGINTAGER_H

#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstring>
using std::cout;

class BigInteger {
private:
    char *p;
    int flag;
public:
    friend BigInteger operator+(const BigInteger &front, const BigInteger &last);
    friend BigInteger operator-(const BigInteger &front, const BigInteger &last);
    friend BigInteger operator*(const BigInteger &front, const BigInteger &last);
    friend BigInteger operator/(const BigInteger &front, const BigInteger &last);
    friend BigInteger operator%(const BigInteger &front, const BigInteger &last);
    friend bool operator>(const BigInteger  &front, const BigInteger &last);
    friend bool operator==(const BigInteger  &front, const BigInteger &last);
    friend bool operator<(const BigInteger  &front, const BigInteger &last);
    friend bool operator<=(const BigInteger  &front, const BigInteger &last);
    friend bool operator>=(const BigInteger  &front, const BigInteger &last);
    friend bool operator!=(const BigInteger  &front, const BigInteger &last);
    BigInteger &operator=(const BigInteger &right)
    {
        //std::cout<<"hit"<<std::endl;
        if(this==&right) return *this;
        delete [] p;
        p =new char[strlen(right.p)+1];
        for(int i =0;i<strlen(right.p);++i)
        {
            p[i] = right.p[i];
        }
        p[strlen(right.p)]='\0';
        flag=right.flag;
        //std::cout<<"end"<<'\n';
        return *this;
    }
    friend std::ostream &operator<<(std::ostream & os,const BigInteger &obj);
    //类型转换
    operator float ()const
    {
        int state=1;
        double ans=0;
        for(int i=0;i<strlen(p);i++)
        {
            ans+=(p[strlen(p)-i-1]-'0')*state;
            state*=10;
            //cout<<ans<<" "<<state<<std::endl;
        }
        return ans;
    }
    operator bool ()const
    {
        if(p[0]=='0')return false;
        else return true;
    }
    operator std::string ()const
    {
        std::string s;
        s = p;
        return s;
    }
    BigInteger(const char*input,int flag1)
    {
        flag=flag1;
        p=new char[strlen(input)+1];
        int i;
        for(i=0;i<strlen(input);++i)
        {
            p[i]=input[i];
        }
        p[strlen(input)]='\0';
    }
    BigInteger(const char*input)
    {
        if(input[0]!='-')
        {
            flag=1;
            p =new char[strlen(input)+2];
            for(int i=0;i<strlen(input)+1;++i)  p[i]=input[i];
            p[strlen(input)+1]='\0';
        }
        else
        {
            flag=-1;
            p =new char[strlen(input)+1];
            for(int i=0;i<strlen(input);++i)    p[i]=input[i+1];
            p[strlen(input)]='\0';
        }
    }
    BigInteger(const BigInteger &tmp)
    {
        p = new char [strlen(tmp.p)+1];
        flag=tmp.flag;
        for(int i =0;i<strlen(tmp.p);i++)
        {
            p[i]=tmp.p[i];
        }
        p[strlen(tmp.p)]='\0';
    }
    ~BigInteger()
    {
        if(p)delete[]p;
    }
};
bool operator==(const BigInteger  &front, const BigInteger &last)
{
    if(front.flag!=last.flag)return false;
    if(strlen(front.p)!=strlen(last.p))return false;
    int ans=1;
    for(int i=0;i<strlen(front.p);i++)
    {
        if(front.p[i]!=last.p[i]){ans=0;break;}
    }
    if(ans==1)return true;
    else return false;
}
bool operator>(const BigInteger  &front, const BigInteger &last)
{
    if(strlen(front.p)>strlen(last.p))return true;
    if(strlen(front.p)<strlen(last.p))return false;
    for(int i=0;i<strlen(front.p);i++)
    {
        if(front.p[i]>last.p[i])return true;
        if(front.p[i]<last.p[i])return false;
    }
    return false;
}
bool operator<(const BigInteger  &front, const BigInteger &last)
{
    return (! operator>(front ,last))&&(!operator==(front,last));
}
bool operator<=(const BigInteger  &front, const BigInteger &last)
{
    return operator==(front,last)||operator<(front,last);
}
bool operator>=(const BigInteger  &front, const BigInteger &last)
{
    //cout<<"hit>="<<'\n';
    return operator==(front,last)||operator>(front,last);
}
bool operator!=(const BigInteger  &front, const BigInteger &last)
{
    return !operator==(front,last);
}
std::ostream &operator<<(std::ostream & os,const BigInteger &obj)
{
    //BigInteger tmp = obj;
    //std::cout<<"["<<strlen(obj.p)<<"]";
    //obj.p[strlen(obj.p)+1]='\0';
    //cout<<"end"<<std::endl;
    //cout<<"x"<<std::endl;
    if(obj.flag==-1)os<<"-";
    for(int i = 0; i<strlen(obj.p);++i)
        if(obj.p[i]>='0'&&obj.p[i]<='9')os<<obj.p[i];

    //os<<obj.p;
    return  os;
}
BigInteger operator+(const BigInteger &front, const BigInteger &last)
{
    //char *p1,*p2,*p0;
    //p1 = new char[strlen(front.p)+10]();
    //p2 = new char[strlen(last.p)+10]();
    //p0 = new char[strlen()];
    //std::cout<<"hit+"<<'\n';
    if(front.flag==-1&&last.flag==-1)
    {
        BigInteger tmp(front.p,1),change1(front.p,1),change2(last.p,1);
        tmp=operator+(change1,change2);
        tmp.flag=-1;
        return tmp;
    }
    if(front.flag==1&&last.flag==-1)
    {
        BigInteger tmp(front.p,1),change1(front.p,1),change2(last.p,1);
        //cout<<last.p<<std::endl;
        //cout<<change1.p<<" "<<change2<<std::endl;
        tmp=operator-(change1,change2);
        return tmp;
    }
    if(front.flag==-1&&last.flag==1)
    {
        BigInteger tmp(front.p,1),change1(front.p,1),change2(last.p,1);
        tmp=operator-(change2,change1);
        return tmp;
    }
    if(front.flag==1&&last.flag==1)
    {
        const int maxlength = std::max(strlen(front.p), strlen(last.p));

        char result[maxlength + 5];
        for (int i = 0; i < maxlength + 5; ++i) {
            result[i] = '0';
        }
        int intresult[maxlength + 2];
        //找到最大值，初始化答案数组
        for (int i = 0; i < maxlength + 2; i++) {
            intresult[i] = 0;
        }
        int intfront[maxlength], intlast[maxlength];
        for (int i = 0; i < maxlength; i++) {
            intfront[i] = 0;
        }
        for (int i = 0; i < maxlength; i++) {
            intlast[i] = 0;
        }
        for (int i = 0; i < strlen(front.p); ++i) {
            intfront[i] = front.p[strlen(front.p) - 1 - i] - '0';
            //cout<<intfront[i]<<" ";
        }
        for (int i = 0; i < strlen(last.p); ++i) {
            intlast[i] = last.p[strlen(last.p) - 1 - i] - '0';
            //cout<<intlast[i]<<" ";
        }
        //倒序存在int数组里面
        //cout<<std::endl;

        int i;

        for (i = 0; i < maxlength; ++i) {
            intresult[i] += intfront[i] + intlast[i];
            //cout<<intresult[i]<<std::endl;
            if (intresult[i] > 9) {
                intresult[i + 1] += intresult[i] / 10;
                intresult[i] = intresult[i] % 10;
            }
        }
        //for(int i=0;i<maxlength+1;i++)
        // {
        //  cout<<intresult[i]<<" ";
        // }
        //cout<<std::endl;
        while (intresult[i] == 0) {
            --i;
        }
        int i0 = i;
        //cout<<i0<<std::endl;
        for (; i >= 0; --i) {
            result[i0 - i] = intresult[i] + '0';
            //cout<<result[i0-i]<<" ";
        }
        result[i0 + 1] = '\0';
        for(int j=0;j<i0+1;j++)
        {
            if(result[j]>'9'||result[j]<'0'){result[j]='\0';break;}
        }
        //cout<<result<<"x"<<std::endl;
        BigInteger tmp(result, 1);
        //cout<<tmp.p<<std::endl;
        //cout<<tmp.p<<std::endl;
        //cout<<tmp;
        //std::cout<<"end+"<<'\n';
        return tmp;
    }
}
BigInteger operator-(const BigInteger &front, const BigInteger &last)
{

    //cout<<"x"<<std::endl;
    if (front.flag == 1 && last.flag == -1) {
        BigInteger tmp(front.p, 1), change1(front.p, 1), change2(last.p, 1);
        tmp = operator+(change1, change2);
        tmp.flag = 1;
        return tmp;
    }
    if (front.flag == -1 && last.flag == 1) {
        BigInteger tmp(front.p, 1), change1(front.p, 1), change2(last.p, 1);
        tmp = operator+(change1, change2);
        tmp.flag = -1;
        return tmp;
    }
    if (front.flag == -1 && last.flag == -1) {
        BigInteger tmp(front.p, 1), change1(front.p, 1), change2(last.p, 1);
        tmp = operator-(change1, change2);
        tmp.flag = -1;
        return tmp;
    }
    if (front.flag == 1 && last.flag == 1) {
        if(front>=last) {

            char result[strlen(front.p) ];
            //cout<<front.p<<" "<<last.p<<std::endl;
            for (int i = 0; i < strlen(front.p) ; ++i) {
                result[i] = '0';
            }
            int intresult[strlen(front.p) + 2];
            //找到最大值，初始化答案数组
            for (int i = 0; i < strlen(front.p) + 2; i++) {
                intresult[i] = 0;
            }
            int intfront[strlen(front.p)], intlast[strlen(last.p)];
            for (int i = 0; i < strlen(front.p); i++) {
                intfront[i] = 0;
            }
            for (int i = 0; i < strlen(front.p); i++) {
                intlast[i] = 0;
            }
            for (int i = 0; i < strlen(front.p); ++i) {
                intfront[i] = front.p[strlen(front.p) - 1 - i] - '0';
                //cout<<intfront[i]<<" ";
            }
            for (int i = 0; i < strlen(last.p); ++i) {
                intlast[i] = last.p[strlen(last.p) - 1 - i] - '0';
                //cout<<intlast[i]<<" ";
            }
            //倒序存在int数组里面
            int i;
            for (i = 0; i < strlen(front.p); ++i) {
                intresult[i] += intfront[i] - intlast[i];
                if (intresult[i] < 0) {
                    intresult[i + 1]--;
                    intresult[i] += 10;
                }
            }
            while (intresult[i] == 0 && i > 0) {
                --i;
            }
            int i0 = i;
            //cout<<i0<<std::endl;
            for (; i >= 0; --i) {
                result[i0 - i] = intresult[i] + '0';
            }
            result[i0 + 1] = '\0';
            for(int j=0;j<=i0+1;j++)
            {
                if(result[j]>'9'||result[j]<'0'){result[j]='\0';break;}
            }
            BigInteger tmp(result, 1);
            //cout<<tmp.p<<std::endl;
            tmp.p[strlen(result)]='\0';
            //cout<<strlen(result);
            //cout<<tmp<<std::endl;
            return tmp;
        }
        else
        {

            BigInteger tmp(front.p, 1), change1(front.p, front.flag), change2(last.p, last.flag);
            tmp = operator-(change2, change1);
            tmp.flag *= -1;
            return tmp;
        }
    }


}
BigInteger operator*(const BigInteger &front, const BigInteger &last)
{
    const int maxlength=strlen(front.p)+strlen(last.p);
    char result[maxlength+5];
    for(int i =0;i<maxlength+5;++i)
    {
        result[i]='0';
    }
    int intresult[maxlength+5];
    //找到最大值，初始化答案数组
    for(int i = 0;i<maxlength+5;i++)
    {
        intresult[i]=0;
    }
    int intfront[strlen(front.p)],intlast[strlen(last.p)];
    for(int i = 0;i<strlen(front.p);i++)
    {
        intfront[i]=0;
    }
    for(int i = 0;i<strlen(front.p);i++)
    {
        intlast[i]=0;
    }
    for(int i = 0;i < strlen(front.p);++i)
    {
        intfront[i] = front.p[strlen(front.p)-1-i]-'0';
        //cout<<intfront[i]<<" ";
    }
    for(int i = 0;i<strlen(last.p);++i)
    {
        intlast[i] = last.p[strlen(last.p)-1-i]-'0';
        //cout<<intlast[i]<<" ";
    }
    //倒序存在int数组里面
    for(int i=0;i<strlen(front.p);i++)
    {
        for(int j = 0;j<strlen(last.p);j++)
        {
            intresult[i+j]+=intfront[i]*intlast[j];
        }
    }

    int i;
    for(i=0;i<maxlength+3;i++)
    {
        intresult[i+1]+=intresult[i]/10;
        intresult[i]=intresult[i]%10;
    }
    while(intresult[i]==0&&i>0)
    {
        --i;
    }
    // for(int m=0;m<=i;++m)
    // {
    //   cout<<intresult[m]<<std::endl;
    //}
    int i0=i;
    //cout<<i0<<std::endl;
    for(;i>=0;--i)
    {
        result[i0-i]=intresult[i]+'0';
    }
    //cout<<"x";
    result[i0+1]='\0';
    for(int j=0;j<=i0+1;j++)
    {
        if(result[j]>'9'||result[j]<'0'){result[j]='\0';break;}
    }
    //cout<<result<<std::endl;
    BigInteger tmp(result,1);
    tmp.flag=front.flag*last.flag;
    if(tmp.p[0]=='0')tmp.flag=1;
    return tmp;
}
BigInteger operator/(const BigInteger &front, const BigInteger &last)
{
    if(front.p[0]=='0')
    {
        BigInteger tmp(front.p, 1);
        return tmp;
    }
    if(front.flag==-1&&last.flag==1)
    {
        BigInteger tmp(front.p, 1), change1(front.p, 1), change2(last.p, 1);
        tmp = operator/(change1, change2);
        tmp.flag = -1;//去0
        char c[] = "1";
        BigInteger D(c), E(c);
        D = (tmp * E);
        tmp = D;//快速去0
        D =(tmp-E);
        tmp =D;
        return tmp;
    }
    if(front.flag==-1&&last.flag==-1)
    {
        BigInteger tmp(front.p, 1), change1(front.p, 1), change2(last.p, 1);
        tmp = operator/(change1, change2);
        return tmp;
    }
    if(front.flag==1&&last.flag==-1)
    {
        BigInteger tmp(front.p, 1), change1(front.p, 1), change2(last.p, 1);
        tmp = operator/(change1, change2);
        tmp.flag = -1;//去0
        char c[] = "1";
        BigInteger D(c), E(c);
        D = (tmp * E);
        tmp = D;//快速去0
        D =(tmp-E);
        tmp =D;
        return tmp;
    }
    if(front.flag==1&&last.flag==1)
    {
        //cout<<"in"<<'\n';
        int maxlength = strlen(front.p) - strlen(last.p) + 1;
        char result[maxlength];
        for (int i = 0; i < maxlength; i++) {
            result[i] = '0';
        }
        //cout<<"in1"<<'\n';

        /*if(0)
        {
            int intfront[strlen(front.p)], intlast[strlen(front.p)];
            for (int i = 0; i < strlen(front.p); i++) {
                intfront[i] = 0;
            }
            for (int i = 0; i < strlen(front.p); i++) {
                intlast[i] = 0;
            }
            for (int i = 0; i < strlen(front.p); ++i) {
                intfront[i] = front.p[i] - '0';
                //cout<<intfront[i]<<" ";
            }
            for (int i = 0; i < strlen(last.p); ++i) {
                intlast[i] = last.p[i] - '0';
                //cout<<intlast[i]<<" ";
            }
        }*/
        char chfront[strlen(front.p)], chlast[strlen(front.p)];
        for (int i = 0; i < strlen(front.p); i++) {
            chfront[i] = '0';
        }
        chfront[strlen(front.p)] = '\0';
        for (int i = 0; i < strlen(front.p); i++) {
            chlast[i] = '0';
        }
        chlast[strlen(front.p)] = '\0';
        for (int i = 0; i < strlen(front.p); i++) {
            chfront[i] = front.p[i];
        }
        for (int i = 0; i < strlen(last.p); i++) {
            chlast[i] = last.p[i];
        }
        int i = 0;
        BigInteger A(chfront), B(chlast);
        while (i < maxlength) {

            //cout << "A" << A << std::endl;
            //cout << "B" << B << std::endl;
            while (A >= B) {
                if (A < B)break;
                //cout << "hit1" << '\n';
                BigInteger C = A - B;
                result[i] += 1;
                A = C;
                //cout << A << " b:" << B << " c:" << C << std::endl;
                //cout << i << "result:" << result[i] << std::endl;

            }
            i++;
            char c[] = "10";
            BigInteger D(A.p), E(c);
            D = (A * E);
            A = D;
            //cout<<strlen(B.p)<<std::endl;
            //B.p[strlen(B.p)-1]='\0';
            //cout<<strlen(B.p)<<std::endl;
            //cout<<i<<std::endl;
            //cout<<result[i]<<std::endl;
            //cout<<"x"<<std::endl;
            /*for(int j=0;j<strlen(B.p)-2;++j)
            {
                B.p[strlen(B.p)-1-i]=B.p[strlen(B.p)-2-i];
            }
            B.p[0]='0';


            int kk;
            for(kk=0;kk<strlen(B.p);kk++)
            {
                if(B.p[kk]!='0')break;
            }
            for(int j=kk;j<strlen(B.p);j++)
            {
                B.p[j-kk]=B.p[j];
            }*/
        }
        //cout<<i<<std::endl;
        result[i] = '\0';
        BigInteger tmp(result);
        char c[] = "1";
        BigInteger D(c), E(c);
        D = (tmp * E);
        tmp = D;
        D =(tmp-E);
        //cout << i << " " << strlen(result) << std::endl;
        return tmp;
    }
}
BigInteger operator%(const BigInteger &front, const BigInteger &last)
{
    return front-(front/last)*last;
}

#endif //PYTHON_INTERPRETER_BIGINTAGER_H
