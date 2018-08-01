#include <iostream>
#include<vector>
#include <fstream>

#define max 100000

using namespace std;
vector < vector <int> > canh;// luu canh cua do thi

vector < vector <int> > a;  // danh sach ke

int DinhBacMin(int n,int m,vector < vector<int> > a,vector <int> bac,int khoa[]){// tim dinh co bac nho nhat trong do thi va tra ve vi tri cua dinh do
    int dinh=n;
    int vitri;
    for(int i=0;i<n;i++){
        if(dinh>bac[i]&&khoa[i]== 0){
            dinh=bac[i];
            vitri=i;
        }
    }
    return vitri;
}

void Tomaudothi(int n,int m, vector < vector<int> > a){
    vector <int> Bac=vector <int> (n); // luu bac cua cua cac dinh
    for(int i=0;i<n;i++){
        Bac[i]=a[i].size();
    }

    int sapxep[n]={0};
    int khoa[n]={0};
    int kichco = 0;// so phan tu trong mang sapxep[]
    int vitri=0;
    // dua ra mang sap xep cho thuat toan tham lam
    while(kichco<n){
        vitri= DinhBacMin(n,m,a,Bac,khoa);
        sapxep[kichco]=vitri+1;
        khoa[vitri]=1;
        int dem=kichco;
        kichco++;

        while(1){// liet ke hang xom ho hang cua dinh vua cho vao mang sapxep
                if(dem==kichco) break;
                for(int i=0;i<a[sapxep[dem]-1].size();i++){
                    if(khoa[a[sapxep[dem]-1][i]-1]==0){
                        sapxep[kichco]=a[sapxep[dem]-1][i];
                        khoa[sapxep[kichco]-1]=1;
                        kichco++;
                    }
                }
                dem++;
        }
    }
    int sapxepthamlam[n]={0};
    for(int i=0;i<n;i++){
        sapxepthamlam[i]=sapxep[n-i-1];
    }

    int mangmau[10]={0};// 10 mau tu 0->9 de to mau

    int Tomau[n]={0}; //luu lai mau da to ; gia tri bang 0: dinh chua duoc to mau

    for(int i=0;i<n;i++){

        //kiem tra mau nhung dinh ke voi no to mau gi

        for(int j=0;j<a[sapxepthamlam[i]-1].size();j++){
            if(Tomau[a[sapxepthamlam[i]-1][j]-1]!=0){
                mangmau[Tomau[a[sapxepthamlam[i]-1][j]-1]-1]=1; // danh dau mau da dung de to dinh ke cua dinh dang xet
            }
            }

        for(int j=0;j<10;j++){
            if(mangmau[j]==0){
                Tomau[sapxepthamlam[i]-1]=j+1;
                break;
            }
        }


        for(int j=0;j<10;j++){
            mangmau[j]=0;
        }

    }
    freopen("dothitomau.dot","w+",stdout);
    // in ra man hinh theo cau truc de
    cout <<"graph dothi"<<endl<<endl;
    cout <<"{"<<endl<<endl;

    for(int i=0;i<n;i++){
        cout<< "     "<<sapxep[i]<<" [fillcolor=";
        if(Tomau[sapxep[i]-1]==1) cout<<"red";
        if(Tomau[sapxep[i]-1]==2) cout<<"green";
        if(Tomau[sapxep[i]-1]==3) cout<<"blue";
        if(Tomau[sapxep[i]-1]==4) cout<<"yellow";
        if(Tomau[sapxep[i]-1]==5) cout<<"white";
        if(Tomau[sapxep[i]-1]==6) cout<<"brown";
        if(Tomau[sapxep[i]-1]==7) cout<<"grey";
        if(Tomau[sapxep[i]-1]==8) cout<<"orange";
        if(Tomau[sapxep[i]-1]==9) cout<<"pink";
        if(Tomau[sapxep[i]-1]==10) cout<<"black";
        cout<< ", style=filled];"<<endl<<endl;
    }

    for(int i=0;i<m;i++){
        cout <<"     ";
        cout <<canh[i][0];
        cout <<" -- ";
        cout <<canh[i][1];
        cout <<";"<<endl;

    }
    cout<<endl<<"}";


}



int main()
{   int data;
    int n;
    int m;
    int u,v;

    ifstream infile;
    infile.open("dothi.txt");

    infile >> n;     //Nhap vao so dinh
    infile >> m;     //Nhap vao so canh

    a = vector< vector<int> > (n);
    canh = vector< vector<int> > (m);
    for(int i=0;i<m;i++){
        infile>>u;
        infile>>v;
        a[u-1].push_back(v);// Danh sach canh ke cua u
        a[v-1].push_back(u);// danh sach canh ke cua v
        // luu canh cua do thi (Chi de in ra thoi)
        canh[i].push_back(u);
        canh[i].push_back(v);
    }

   Tomaudothi(n,m,a);
    return 0;
}
