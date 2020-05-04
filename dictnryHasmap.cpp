#include<iostream>
#include<vector>
#include<string>
#include<bits/stdc++.h>
using namespace std;

//Implementing a dictionary by using my own built hasmap

class Node
{
private:
        string key;
        string value;
        Node* next;

public:
        Node(string key, string value)
        {
          this->key=key;
          this->value=value;
        }
friend class ourmap;

};

class ourmap
{       
        Node** arr;
        int numBuckets;
        int count;

        int getHashIndex(string key)
        {
            int hashCode=0;
            int p=1;
            for(int i=key.length()-1;i>=0;i--)
            {
              hashCode+=p;
              hashCode= hashCode%numBuckets;
              p=p*37;
              p=p%numBuckets;
            }
            return hashCode%numBuckets;
        }

        double getLoadFactor()
        {
          return 1.0*(count)/numBuckets;
        }

        void rehash()
        {
          Node** temp=arr;
          count=0;
          int oldnumBuckets=numBuckets;
          numBuckets*=2;
          arr= new Node*[numBuckets];
          for(int i=0;i<numBuckets;i++)
           arr[i]=NULL;
          for(int i=0;i<oldnumBuckets;i++)
          {
            Node*head=temp[i];
            while(head!=NULL)
            {
              insertWord(head->key,head->value);
            }
            head=head->next;
          }

          for(int i=0;i<oldnumBuckets;i++)
           delete []temp[i];
          delete []temp;
        }

public:
        ourmap()
        {
          numBuckets=20;
          arr=new Node*[numBuckets];
          count=0;
        } 

        void insertWord(string key, string value)
        {
          int index=getHashIndex(key);
          Node* head= arr[index];
          while(head!=NULL)
          {
            if(head->key==key)
            {
              cout<<"Oops such a word already exits in your dictionary"<<endl;
              cout<<"Do you want to change the meaning of the word ?: Press y for yes and n for no";
              char ans;
              if(ans=='y')
              {
                head->value=value;
              }
              cout<<"Value changed!!"<<endl;
              return;
            }
            head=head->next;
          }

          head=arr[index];
          Node* newNode= new Node(key,value);
          newNode->next=head;
          arr[index]=newNode;
          cout<<"The word has been inserted in your dictionary: "<<endl;
          count++;

          double LF= getLoadFactor();
          if(LF>0.7)
           rehash();
        }

        void searchWord(string key)
        {
          int index=getHashIndex(key);
          Node* head=arr[index];
          while(head!=NULL)
          {
            if(head->key==key)
             {
               cout<<"The meaning of the word "<<key<<" is: "<<head->value<<endl;
               return;
             }
            head=head->next;
          }
          cout<<"Word not found in your dictionary";
        }


        void deleteWord(string key)
        {
          int index=getHashIndex(key);
          Node* head= arr[index];
          Node* prev=NULL;
          while(head!=NULL)
          {
            if(head->key==key)
            {
              if(prev==NULL)
              {
                arr[index]=head->next;
              }
              else
              {
                prev->next=head->next;
              }
              delete head;
              count--;
              cout<<"The word has been deleted from your dictionary"<<endl;
              return;
            }
            prev=head;
            head=head->next;
          }
          cout<<"No such word found in your dictionary: "<<endl;
        }



        void displayDictionary()
        {
          cout<<"Your dictionary looks like this: "<<endl;
          for(int i=0;i<numBuckets;i++)
          {
            Node* head=arr[i];
            while(head!=NULL)
            {
              cout<<head->key<<"-"<<head->value<<endl;
              head=head->next;
            }
          }
        }

};


int main()
{

  cout<<"YOUR OWN DICTIONARY ";
  ourmap m;
  int choice;
  string key;
  string value;
  do
  {
  cout<<"\nMENU:\n1.Insert your word and meaning\n2.Search your word in the dictionary\n3.Delete your word from the dictionary.\n4.Display your dictionary\n5.Exit";
  cout<<"\nEnter your choice: ";
  cin>>choice;
  switch(choice)
  {
    case 1:
          cout<<"Enter the word "<<endl;
          cin>>key;
          cout<<"Enter its meaning "<<endl;
          getline(cin, value); 
          m.insertWord(key, value);
    break;

    case 2:
          cout<<"Enter the word ";
          cin>>key;
          m.searchWord(key);
    break;

    case 3:
          cout<<"Enter the word ";
          cin>>key;
          m.deleteWord(key);
    break;

    case 4:
           m.displayDictionary();
    break;

    default: cout<<"Wrong choice entered.";
  }

  }while(choice!=5);
  return 0;
}