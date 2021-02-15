#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <string>

using namespace std;

const char*hostname="127.0.0.1";
const char*username="root";
const char*password="";
const char*database="todo";
unsigned int port =3306;
const char* unixsocket=NULL;
unsigned long clinentflag=0;
string usernamedb, emailbd, passdb;
MYSQL_ROW row;
MYSQL_RES*res;
MYSQL*connectdatabase(){
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, hostname, username, password, database, port, unixsocket, clinentflag);
    if(conn){
      // cout << "Connected"<< endl;
        return conn;
    }else{
        cout << "Connection Error" << endl;
         return conn;
    }
}
//login site
string login(MYSQL* conn){
    cout<<"LOGIN:\n";
    int count=0;
    while(count==0){
        cout<< "Enter username: "<<endl;
        cin>>usernamedb;
        cout<< "Enter password: "<<endl;
        cin>>passdb;

        int qstate=mysql_query(conn,"SELECT * FROM users");
        if(!qstate){
            res=mysql_store_result(conn);
             while(row=mysql_fetch_row(res)){
                    //pass[1] username[2]
                    if(row[1]==passdb && row[2]==usernamedb){
                       // count=1;
                        cout<<"Logined\n";
                        return usernamedb;
                    }
             }
             if(count==0){
                cout<<"Wrong username or pass..\n Please try again...\n";
             }
        }
    }
}
createNewAccount(MYSQL* conn){
    cout<<"Create new account\n";
    int qstate=0;
    stringstream ss;
    //user input create new account
    int exist=0;
    //check if the exist user
    do {
        cout<< "Enter username  :"<<endl;
        cin>>usernamedb;
        if(conn){
            int check=mysql_query(conn,"SELECT `username` FROM `users`");
            //exist=1;
            exist=0;
            if(!check){
                res=mysql_store_result(conn);
                int count =mysql_num_fields(res);
                while(row=mysql_fetch_row(res)){
                    for(int i=0;i<count;i++){
                        if(usernamedb==row[i]){
                           exist-=1;
                           //cout<<exit;
                        }
                    }
                }
                if(exist<0){
                   cout<<"This user already exist. Please Input new one...\n";
                }
            }
            }else{

            cout<<"Failed to load";
            }
    }while(exist<0);

    cout<< "Enter email:"<<endl;
    cin>>emailbd;
    cout<< "Enter password:"<<endl;
    cin>>passdb;
    ss<<"INSERT INTO users (username, email, password) VALUES('"+usernamedb+"', '"+emailbd+"', '"+passdb+"')";
    string query= ss.str();
    const char* q= query.c_str();
    qstate=mysql_query(conn,q);
    if(qstate==0){
        cout<<"record inserted..";
        //login(conn);
        //either login or return username
    }else{
    cout<<"failed to insert..";
    }

}

int main()
{
    MYSQL*conn =connectdatabase();
    cout<<"Wellcome to todo list: \n member login click 1.\n New user click 0.\n  ";
    int number;
    cin>>number;
    if(number==1){
       string user= login(conn);
       //either can use id or username from the input
        cout<<"return user: "<<user;
        //cout<<usernamedb;

    }else{
        createNewAccount(conn);
    }
    return 0;
}




