#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;
map<string,list<int>> followers;
class Graph{
public:
    unordered_map<int,list<int>> adj;
    void insert(int u,int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void print(map<int,string> &mp)
    {
        for(auto it:adj)
        {
            cout<<mp[it.first]<<"->";
            for(auto jt:it.second)
            {
                cout<<mp[jt]<<",";
            }
            cout<<endl;
        }

    }
     vector<pair<int,int>> shortTestPath(int src,int n)
    {
            vector<int> dist(n,1000);
            queue<pair<int,int>> q;
            dist[src]=0;
            q.push({src,0});
            while(!q.empty())
            {
                auto it=q.front();
                q.pop();
                int node=it.first;
                int d=it.second;
                for(auto i:adj[node])
                {
                    if(d+1 < dist[i])
                    {
                        dist[i]=d+1;
                        q.push({i,dist[i]});
                    }
                }
            }
            vector<pair<int,int>> new_dist;
            for(int i=0;i<dist.size();i++)
            {
                new_dist.push_back({dist[i],i});
            }
            return new_dist;
    }
};
bool comparePairs(const pair<int, int> &a, const pair<int, int> &b) {
    return a.first > b.first; // Compare based on the first element in decreasing order
}
bool searchItemInMapList(const std::unordered_map<int, std::list<int>>& adj, int index, int searchItem) {
    auto it = adj.find(index); // Find the list associated with the given index

    if (it != adj.end()) {
        const list<int>& myList = it->second;

        // Search for the item in the list
        for (int value : myList) {
            if (value == searchItem) {
                // Item found in the list; return true
                return true;
            }
        }
    }
    // Index not found or item not found in the list; return false
    return false;
}
bool checkCorrectEmail(string email)
    {
        int len=email.length();
        bool flag1=false;
        bool flag2=false;
        for (int i=0;i<len;i++)
        {
            if(email[i]=='@' || flag1){
                flag1=true;
                cout<<"flag 1 true"<<endl;
                    if(email[i]=='.'){
                        flag2=true;
                        cout<<"flag2 true"<<endl;
                        break;
                    }
            }
        }
        if(!flag1 || !flag2)
            cout<<"Incorrect Email Address"<<endl;
        return flag1 && flag2;
    }
    bool searchFollowers(string parent,int child)
    {
        for(auto it:followers[parent])
        {
            if(it == child)
                return true;
        }
        return false;
    }
class User{
public:
    string user_id;
    string password;
    int index;
    string email;
    string status;
    int following;
    void addUser(vector<User> &lis)
    {
            ofstream fout("allUserDetails",ios::app);
            fflush(stdin);
            User newUser;
              while (true) {
            cout << "Enter the User Id: ";
            getline(cin, newUser.user_id);
            bool isUnique = true;
        for (const User& existingUser : lis) {
            if (existingUser.user_id == newUser.user_id) {
                cout << "User Id already exists. Please enter a unique User Id." << endl;
                isUnique = false;
                break;
            }
        }
        if(isUnique) break;
    }
            user_id=newUser.user_id;
            ofstream new_fout(user_id);
            fflush(stdin);
            fout<<user_id<<";";
            new_fout<<user_id<<";";
            cout<<"Enter the Password:";
            getline(cin,password);
            fout<<password<<";";
            do{
            cout<<"Enter the Email Address:";
            getline(cin,email);
            fflush(stdin);
            }while(!checkCorrectEmail(email));
            fout<<email<<";";
            new_fout<<email<<";";
            cout<<"Enter into Your Bio:";
            getline(cin,status);
            fflush(stdin);
            fout<<status<<";";
            new_fout<<status<<"|"<<endl;
            fout.close();
            lis.push_back(*this);
    }
    void print()
    {
        cout<<endl;
        cout<<"UserId:"<<this->user_id<<endl;
        cout<<"Email:"<<this->email<<endl;
        cout<<"Bio:"<<this->status<<endl;
        cout<<"Num of People Following:"<<this->following<<endl;
    }
    bool checkFriend(int parent,int check,Graph g)
    {
        for(auto it:g.adj[parent])
        {
            if(it==check)
                return true;
        }
        return false;
    }
    void addFriend(map<string,int> &mp,Graph &g,map<int,string> &mp2)
    {
        bool found=false;
        do{
        cout<<"Suggestions on Making Friends"<<endl;
        vector<pair<int,int>> rcmnd=g.shortTestPath(mp[this->user_id],mp.size());
        sort(rcmnd.begin(),rcmnd.end(),comparePairs);
        for(auto it:rcmnd)
        {
            //cout<<mp2[it.second]<<" "<<it.first<<endl;
            if( it.first!=0 && ((searchItemInMapList(g.adj, mp[this->user_id], it.second) && !searchFollowers(this->user_id,it.second) || it.first>1))){
                cout<<mp2[it.second]<<" ";
            }
        }
        string id;
        cout<<"Enter the User_Id:";
        fflush(stdin);
        getline(cin,id);
        fflush(stdin);
            if(mp.find(id)==mp.end())
            {
                found=false;
            }
            else if(mp.find(id)!=mp.end() && !checkFriend(mp[this->user_id],mp[id],g))
            {
                followers[this->user_id].push_back(mp[id]);
                ofstream fout(this->user_id,ios::app);
                fout<<id<<'|';
                fout.close();
                //g.adj[mp[this->user_id]].push_back(mp[id]);
                g.insert(mp[this->user_id],mp[id]);
                found=true;
                cout<<id<<" is added to your Follow List"<<endl;
                return;
            }
            /*else if(checkFriend(mp[this->user_id],mp[id],g))
            {
                cout<<"User Already Exists in the List"<<endl;
                found=true;
            }*/
        if(!found)
            cout<<endl<<"User Not Found Please ";
    }while(!found);
    }

};

class admin{
    public:
    string adid;
    string pass;
};
    int checkadmin(vector<admin> adm)
    {
        cout<<"Log In Page"<<endl;
        cout<<"Admin ID:";
        string z;
        fflush(stdin);
        getline(cin,z);
        fflush(stdin);
        cout<<"Password:";
        string x;
        fflush(stdin);
        getline(cin,x);
        fflush(stdin);
        int flag=0;
        for(auto it:adm)
        {
            if(it.adid==z && it.pass==x){
                flag=1;
                break;
            }
        }
        return flag;
    }


    User checkUser(vector<User> arr)
    {
        do{
        cout<<"Log In Page"<<endl;
        cout<<"Username:";
        string u;
        fflush(stdin);
        getline(cin,u);
        fflush(stdin);
        cout<<"Password:";
        string p;
        fflush(stdin);
        getline(cin,p);
        fflush(stdin);
        int flag=0;
        for(auto it:arr)
        {
            if(it.user_id==u && it.password==p)
                flag=1;
        }
        if(!flag)
        {
            cout<<"Wrong Credentials Try Again"<<endl;
        }
        else
        {
            for(auto it:arr)
            {
                if(it.user_id==u)
                    return it;
            }
        }
    }while(1);
}

string getName(string str)
    {
        string name;
        int len=str.length();
        for(int i=0;i<len;i++)
        {
            if(str[i]!=';')
                name.push_back(str[i]);
            else
                break;
        }
        return name;
    }
    string getPassword(string str)
    {
        int len=str.length();
        int cnt=0;
        string pass;
        for(int i=0;i<len;i++)
        {
            if(str[i]==';'){
                cnt++;
                continue;
            }
            if(cnt==1)
                pass.push_back(str[i]);
            if(cnt==2)
                break;
        }
        return pass;
    }
    string getEmail(string str)
    {
        string email;
        int cnt=0;
        int len=str.length();
        for(int i=0;i<len;i++)
        {
            if(str[i]==';'){
                cnt++;
                continue;
            }
            if(cnt==2)
                email.push_back(str[i]);
            if(cnt==3)
                break;
        }
        return email;
    }
    string getStatus(string str)
    {
        string status;
        int len=str.length();
        int cnt=0;
        int k=0;
        for(int i=0;i<len;i++)
        {
            if(str[i]==';'){
                cnt++;
                continue;
            }
            if(cnt==3)
                status.push_back(str[i]);
            if(cnt==4)
                break;
        }
        return status;
    }
     void printFollowers(string name,map<int,string> &mp2)
    {
        cout<<"Friend List:"<<endl;
        for(auto it:followers[name])
        {
            cout<<mp2[it]<<endl;
        }
    }
        void getFollowers(string parent,map<string,int> &mp1)
    {
        string str;
        ifstream fin(parent);
        while(getline(fin,str)){
        int len=str.length();
        string name;
        bool check=false;
        for(int i=0;i<len;i++)
        {
            if(str[i]=='|'){
                if(name!=""){
                    followers[parent].push_back(mp1[name]);
                    name="";
                }
                check=true;
                continue;
            }
            if(check && str[i]!='|')
            {
                name.push_back(str[i]);
            }
        }
        }
}
    int getFollow(string str)
    {
        string num;
        int len=str.length();
        int k=0;
        int cnt=0;
        for(int i=0;i<len;i++){
            if(str[i]==';'){
                cnt++;
                continue;
            }
            if(str[i]=='.')
                break;
            if(cnt==4)
                num.push_back(str[i]);
        }
        int result=stoi(num);
        return result;
    }
    vector<admin> readadmin()
        {
            vector<admin> lis;
            string l;
            ifstream fin("admindetails");
            while(getline(fin,l))
            {
                admin a;
                a.adid=getName(l);
                a.pass=getPassword(l);
                lis.push_back(a);
            }
            fin.close();
            return lis;
        }

       vector<User> readExistingUsers()
        {
            vector<User> lis;
            string line;
            ifstream fin("allUserDetails");
            while(getline(fin,line))
            {
                User u;
                u.user_id=getName(line);
                u.email=getEmail(line);
                u.status=getStatus(line);
                u.password=getPassword(line);
                //u.following=getFollow(line);
                lis.push_back(u);
            }
            fin.close();
            return lis;
        }
        void insertPeople(vector<User> &arr,map<string,int> &mp,Graph &g)
        {
            for(auto p:arr)
            {
                getFollowers(p.user_id,mp);
                int indexP=mp[p.user_id];
                for(auto f:followers[p.user_id])
                {
                    g.insert(indexP,f);
                }
            }
        }
int main()
{
    do{
    int q;
    cout<<"Enter your choice: 1 for Admin login && 2 for User login."<<endl;
    cin>>q;
    switch(q){
    case 1:{
    vector<admin> adm;
    adm=readadmin();
    if(checkadmin(adm)){
    cout<<"Success!"<<endl;
    vector<User>arr;
    arr=readExistingUsers();
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        User new_user;
        cout<<endl<<"Enter Details for the New user:"<<endl;
        new_user.addUser(arr);
    }
    cout<<endl<<"Information For All The Users Are:"<<endl;

    for(auto it:arr)
    {
        it.print();
        cout<<endl<<"-------------"<<endl;
    }
    }
    else{
        cout<<"Try Again Later"<<endl;
    }
    break;
}
    case 2:{
    vector<User> arr;
    arr=readExistingUsers();
    map<string,int> mp1;
    map<int,string> mp2;
    for(int i=0;i<arr.size();i++)
    {
        mp1.insert({arr[i].user_id,i});
        mp2.insert({i,arr[i].user_id});
    }
    Graph g;
    insertPeople(arr,mp1,g);
    cout<<"Welcome"<<endl;
    cout<<"PLease Enter Your Login Credentials"<<endl;
        User curr=checkUser(arr);
        bool flag_switch=false;
        cout<<"Hello "<<curr.user_id<<endl;
        do{
        cout<<"Enter 1 to View All The Current Jexts"<<endl;
        cout<<"Enter 2 to Enter a New Jext"<<endl;
        cout<<"Enter 3 to Get to Know about New People"<<endl;
        cout<<"Enter 4 to Display all People you Follow"<<endl;
        cout<<"Enter 5 to Log Out"<<endl;
        cout<<"Enter Your Choice:"<<endl;
        int op;
        cin>>op;
        switch(op)
        {
        case 1:{
            string chat;
        ifstream fin("allChats");
        while(getline(fin,chat))
        {
            cout<<chat<<endl;
        }
        fin.close();
        break;
        }
        case 2:{
            string jext;
            cout<<"Having Thoughts,Just Jext It:";
            fflush(stdin);
            do{
            getline(cin,jext);
            if(jext!="")
                break;
            fflush(stdin);
            }while(1);
            ofstream fout("allChats",ios::app);
            fout<<curr.user_id<<":"<<jext<<endl;
            fout.close();
            break;
        }
        case 3:
            {
                curr.addFriend(mp1,g,mp2);
                break;
            }
        case 4:
            {
                printFollowers(curr.user_id,mp2);
                break;
            }
        case 5:
            {
                flag_switch=true;
                g.print(mp2);
                break;
            }
    }
    }while(!flag_switch);
}
    cout<<"Press 1 to Restart The Program and 0 to exit:";
    int o;
    cin>>o;
    if(!o)
        return 0;
}
}while(1);
}
