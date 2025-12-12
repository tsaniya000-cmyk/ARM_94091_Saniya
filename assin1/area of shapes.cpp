 #include<iostream>
 using namespace std;
 int main()
 { 
 int n;
 enum shape
 {circle=1,triangle=2,rectangle=3
 };
 cout<<"1.circle\n 2.triangle\n 3.rectangle";
 cin>>n;
 int r,h,b,l;
 float a;
 switch(n)
 {case 1:
 cout<<"enter radius";
 cin>>r;
 a=3.14*r*r;
 cout<<"area of circle= ";
 break;
 case 2:
 cout<<"enter height and base";
 cin>>h>>b;
 a=0.5*h*b;
 cout<<"area of triangle= "<<a;
 break;
 case 3:
 cout<<"enter length and breadth= ";
 cin>>l>>b;
 a=l*b;
 cout<<"area of rectangle= "<<a;
 break;
 }
 return 0;
 }

