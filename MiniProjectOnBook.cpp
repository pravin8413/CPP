#include<iostream>
#include<string.h>
#include<fstream>

using namespace std;

class Book
{
    int id;
    char name[20];
    float price;
public:
    Book()
    {
        id=0;
        strcpy(name,"No title");
        price=0.0;
    }
    void setdata();
    void showdata();
    void storedata();
    void viewalldata();
    void searchdata(char*);
    void deletedata(char*);

};

void Book::setdata()
{
    cout<<"Enter the Id, title and Price: "<<endl;
    cin>>id;
    cin.ignore();
    cin.getline(name,19);
    cin>>price;

}

void Book::showdata()
{

    cout<<"ID : "<<id<<endl<<"Title: "<<name<<endl<<"Price: "<<price<<endl;
}
void Book::storedata()
{
    if(id==0&&price==0)
    {
        cout<<"\nData not initialize ";
        return;
    }else
    {
        ofstream fout;
        fout.open("Book.txt",ios::app);
        fout.write((char*)this,sizeof(*this));
        fout.close();
    }

}

void Book::viewalldata()
{

    ifstream fin;
    fin.open("Book.txt",ios::in);
    if(!fin)
    {
        cout<<"\nfile not found";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            showdata();
            cout<<endl;
            fin.read((char*)this,sizeof(*this));

        }
        fin.close();
    }
}

void Book::searchdata(char *t)
{
    int count=0;
    ifstream fin;
    fin.open("Book.txt",ios::in);
    if(!fin)
    {
        cout<<"\nFile not found";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {

            if(!strcmp(t,name))
            {
                showdata();
                count++;
                break;
            }
            fin.read((char*)this,sizeof(*this));
        }
        if(count==0)
        {
            cout<<"Data not found";
        }
        fin.close();
    }

}

void Book::deletedata(char *t)
{
    ofstream fout;
    ifstream fin;
    fin.open("Book.txt",ios::in);
    if(!fin)
    {
        cout<<"\nFile not found";
    }
    else{
        fout.open("Temp.txt",ios::out);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(strcmp(name,t))
            {
                fout.write((char*)this,sizeof(*this));
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("Book.txt");
        rename("Temp.txt","Book.txt");
    }

}

int menu()
{
    //create a menu
    int choice;
    cout<<"\t\t-------------------------------";
    cout<<"\n\t\tBook Management System"<<endl;
    cout<<"\t\t-------------------------------"<<endl;
    cout<<"\n*********************************";
    cout<<"\n\n\t 1. Insert Data ";
    cout<<"\n\n\t 2. Viewalldata ";
    cout<<"\n\n\t 3. Search Data ";
    cout<<"\n\n\t 4. Delete Data ";
    cout<<"\n\n\t 5. Exit ";
    cout<<"\n\n\t Enter your choice : ";
    cout<<"\n\n*******************************\n";
    cin>>choice;
    return choice;
}

int main()
{
    Book b1;

    char namee[20];
    while(1)
    {
        system("cls");
        switch(menu())
        {
        case 1:
            b1.setdata();
            b1.storedata();
            cout<<"Store data successfully ..."<<endl;

            break;
        case 2:
            b1.viewalldata();

            break;
        case 3:
            cout<<"Enter the name of book to search : "<<endl;
            cin.ignore();
            cin.getline(namee,19);
            b1.searchdata(namee);

            break;

        case 4:
            cout<<"Enter name of book to delete : "<<endl;
            cin.ignore();
            cin.getline(namee,19);
            b1.deletedata(namee);
            break;
        case 5:
            cout<<"Thank you for using this application"<<endl;
            system("cls");
            exit(0);
            break;
        default:
            cout<<"Invalid Input "<<endl;


        }
        system("pause");
    }
    return 0;
}

