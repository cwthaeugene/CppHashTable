/*HASH TABLE
*Code by luka guraspashvili.
*This program takes users name of choice,hashes it with a bad hash function,
*and saves it to a chain of linked lists depending on the hash function's return value.
*This table allows you to search faster for a name than an array,and linked lists make a great use for low memory usage. 
*may 4th 2022. thank you!
*/


#include <iostream>
using namespace std;


//this is our linked list node class
class node
{
	public:
	string value;
	node * next;
};


//we get user input
void get_user_input(string * name)
{
	cout<<"enter a name and press enter or type (done) and hit enter:";
	cin>>*name;
}



//this is a stupid hash function,only works with lower case characters.
void to_ascii(string a,int * tmp)
{
	*tmp=int(a[0]-97);
}


//we print lists
void print_list(node * tmp[])
{
	for(int i=0;i<26;i++)
	{
		cout<<i<<"---"<<endl;
		if(tmp[i]!=NULL)
		{
			for(node * n=tmp[i];n!=NULL;n=n->next)
			{
				cout<<"   | "<<endl;
				cout<<"  "<<n->value<<endl;
			}
		}
	}

}

//set all head pointers to null to be sure we wont have garbage values
void to_null(node * tmp[])
{
	for(int i = 0;i<26;i++)
	{
		tmp[i]=NULL;
	}
}

//we delete the list with recursion
void delete_list(node * tmp)
{
	if(tmp==NULL)
	{
		return;
	}
	delete_list(tmp->next);
	delete tmp;
}



//we delete the row of the table
void delete_table(node * tmp[])
{
	for(int i=0;i<26;i++)
	{
		delete_list(tmp[i]);
	}
}




bool valid_name(int tmp)
{
	if(tmp>=0 && tmp<=25)
	{
		return true;
	}
	else 
	{
		return false;
	}
}


int main()
{
	node * head[26];//heads of our linked lists.
	to_null(head);
	string * name = new string;//to store names temporarily
	int * hash = new int;//to store the hash temporarily
	while(*name!="done")
	{
		to_ascii(*name,hash);
		bool validity=valid_name(*hash);
		if(*name!="done" && validity)
		{
			if(head[*hash]==NULL)
			{
				head[*hash]= new node;
				head[*hash]->value=*name;
				head[*hash]->next=NULL;
			}
			else if(head[*hash]!=NULL)
			{
				node * tmp=new node;
				tmp->value=*name;
				tmp->next=head[*hash];
				head[*hash]=tmp;
			}
			
		}
		else
		{
			cout<<"invalid name! use only the lower case charcter in the beginning of the name!"<<endl;
		}
		
	}
	print_list(head);
	//we free memory
	delete_table(head);
	delete hash;
	delete name;
}