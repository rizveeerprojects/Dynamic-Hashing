#include <bits/stdc++.h>
using namespace std;


int MOD; //MOD value for hash function
int bucket_max_size; //maximum bucket size possible 
int number_of_bit;//number of bit to compare

//key Type to work with
struct Key_Type{
	int id; //integer is key type here
};

//Bucket / bin
struct Bucket{
	int local_bit; //local bit 
	vector<Key_Type>key;//value to save
};


int global_bit; //global bit to express how many bits are needed to represent main table
vector<Bucket*>bucket_address_table; 
deque<deque<int>>corresponding_bit_address;


//input function to take input of mod value
void basic_input(){
	printf("Please give max number of bit to represent address ");
	cin>>number_of_bit;
	MOD = 1<<number_of_bit;
	printf("Please give input bucket size: ");
	cin>>bucket_max_size;
}

//hash function
int hash_function(Key_Type object){
	int remainder = object.id%MOD;
	return remainder;
}

void init(){
	//variable start 
	global_bit=1;
	//memory allocate
	bucket_address_table.push_back(new Bucket());
	bucket_address_table.push_back(new Bucket());
	//complete for bucket 0
	bucket_address_table[0]->local_bit=1;
	//complete for bucket 1
	bucket_address_table[1]->local_bit=1;
	//address making completeness
	deque<int>temp;
	temp.push_back(0);
	corresponding_bit_address.push_back(temp);
	temp[0]=1;
	corresponding_bit_address.push_back(temp);
	return;
}

int find_row_number(int remainder){
	int value=0;
	
	return value;	
}

void insertion(Key_Type object){
	int rem = hash_function(object);
	int row = rem>>(number_of_bit-global_bit);
	struct Bucket *target = bucket_address_table[row];
	if((int)target->key.size()<bucket_max_size) {
		target->key.push_back(object);
		return;
	}
	else{
		
		//if multiple address is taking the same place first split that
		vector<int>same_place;
		for(int i=0;i<(int)bucket_address_table.size();i++){
			if(bucket_address_table[i] == target){
				same_place.push_back(i);
			}
		}
		if(same_place.size() > 1) {
			//just local space elaborate
			Bucket *one = new Bucket();
			one->local_bit=target->local_bit+1;
			Bucket *two = new Bucket();
			two->local_bit=target->local_bit+1;
			for(int i=0;i<(int)target->key.size();i++){
				if(i==0){
					one->key.push_back(target->key[0]);
				}
				else{
					rem = hash_function(target->key[i]);
					int choice = rem>>(number_of_bit-one->local_bit);
					if(choice == (hash_function(one->key[0])>>(number_of_bit-one->local_bit))){
					one->key.push_back(target->key[i]);
				}
				else{
					two->key.push_back(target->key[i]);
				}
			}
		  }
		  int base = hash_function(one->key[0])>>(number_of_bit-one->local_bit);
			for(int i=0;i<(int)same_place.size();i++){
				int v=same_place[i];
				if((v>>(global_bit-one->local_bit)) == base){
					bucket_address_table[v]=one;
				}
				else{
					bucket_address_table[v]=two;
				}
			}
			insertion(object);
		}
		else{
			//need to elaborate
			vector<Bucket*>new_list;
			global_bit++;
			for(int i=0;i<(int)bucket_address_table.size()*2;i++){
				int idx = (i>>1);
				new_list.push_back(bucket_address_table[idx]);
			}
			bucket_address_table = new_list;
			vector<int>change_row;
			for(int i=0;i<(int)bucket_address_table.size();i++){
				if(bucket_address_table[i] == target){
					change_row.push_back(i);
					bucket_address_table[i]= NULL;
				}
			}
			Bucket *one = new Bucket();
			one->local_bit=target->local_bit+1;
			Bucket *two = new Bucket();
			two->local_bit=target->local_bit+1;
			//division
			for(int i=0;i<(int)target->key.size();i++){
				if(i==0){
					one->key.push_back(target->key[0]);
				}
				else{
					rem = hash_function(target->key[i]);
					int choice = rem>>(number_of_bit-one->local_bit);
					if(choice == (hash_function(one->key[0])>>(number_of_bit-one->local_bit))){
					one->key.push_back(target->key[i]);
				}
				else{
					two->key.push_back(target->key[i]);
				}
			}
		  }
			int base = hash_function(one->key[0])>>(number_of_bit-one->local_bit);
			for(int i=0;i<(int)change_row.size();i++){
				int v=change_row[i];
				if((v>>(global_bit-one->local_bit)) == base){
					bucket_address_table[v]=one;
				}
				else{
					bucket_address_table[v]=two;
				}
			}
			insertion(object);
		}
	}
	return;
}

map<struct Bucket*,int>M;

void print_function(){
	M.clear();
	for(int i=0;i<(int)bucket_address_table.size();i++){
		cout<<"address = "<< i<<" : ";
		if(M[bucket_address_table[i]] == 0) {
			M[bucket_address_table[i]]=1;
			cout<<"hash prefix = ( "<<bucket_address_table[i]->local_bit<<" ) value = ( ";
			for(int j=0;j<(int)bucket_address_table[i]->key.size();j++){
				cout<<bucket_address_table[i]->key[j].id<<" ";
			} 
			cout<<" ) " << endl;
		}
		else{
			cout<<"--------"<<endl;
		}
	}
	M.clear();
	return;
}

//menu function
void menu(){
	Key_Type object;
	while(1){
		cout<<"Press 1 to input number"<<endl;
		cout<<"Press 2 to print dynamic hasing table "<<endl;
		cout<<"Press 3 to exit code"<<endl;
		int choice;
		scanf("%d",&choice);
		if(choice == 1) {
			cout<<"Give input number " << endl;
			int number;
			cin>>number;
			object.id=number;
			insertion(object);
		}
		else if(choice == 2) {
			print_function();
		}
		else if(choice == 3) {
			break;
		}
	}
}

int main(void){
	//function to take input of mod value 
	basic_input();
	//initialize
	init(); 
	//input 
	menu();
	return 0;
}
