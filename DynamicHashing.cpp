#include <bits/stdc++.h>
using namespace std;


int MOD; //MOD value for hash function
int bucket_max_size; //maximum bucket size possible 

//key Type to work with
struct Key_Type{
	int id; //integer is key type here
};

//Bucket / bin
struct Bucket{
	int local_bit; //local bit 
	vector<Key_Type>key;//value to save
};

//global address 
struct Address_Space{
	int global_bit; //global bit
	vector<Bucket*>bucket_address; //bucket address space
};
Address_Space *address_space; //basic address space

//hash function
int hash_function(Key_Type object){
	int remainder = object.id%MOD;
	return remainder;
}
//input function to take input of mod value
void basic_input(){
	printf("Please give mod value ");
	cin>>MOD;
	printf("Please give input bucket size: ");
	cin>>bucket_max_size;
}

//initialization of function 
void init(){
	//variable start 
	address_space = new Address_Space();
	address_space->global_bit=1;
	Bucket *bucket = new Bucket();
	bucket->local_bit=1;
	address_space->bucket_address.push_back(bucket);
	Bucket *bucket2 = new Bucket();
	bucket2->local_bit=1;
	address_space->bucket_address.push_back(bucket2);
}

//function is to calculate bit wise value from LSB 
int finding_bit_wise_value(int value,int bit){
	int cal = (1<<bit)-1;
	return (value & cal); //returns LSB depended on bit size
}

//void insert into hash table 
bool insertion(Key_Type object){
	int hash_value = hash_function(object); 
	int cal = finding_bit_wise_value(hash_value,address_space->global_bit);
	if((int)address_space->bucket_address[cal]->key.size()<bucket_max_size) {
		address_space->bucket_address[cal]->key.push_back(object);
		return true;
	}
	else{
		//space not empty need to do many things
		//space increase
		int current_size = address_space->bucket_address.size();
		address_space->global_bit++;
		for(int i=0;i<current_size;i++){
			address_space->bucket_address.push_back(address_space->bucket_address[i]);
		}
		//find the indexes where memory collide
		Bucket *target=address_space->bucket_address[cal];
		vector<int>index_pos; //indexes where memory collide
		for(int i=0;i<(int)address_space->bucket_address.size();i++){
			if(address_space->bucket_address[i] == target){
				index_pos.push_back(i);
				address_space->bucket_address[i]=NULL;
			}
		}
		//create two new memory
		Bucket *one = new Bucket();
		Bucket *two = new Bucket();
		one->local_bit=target->local_bit+1;
		two->local_bit=target->local_bit+1;
		for(int i=0;i<(int)target->key.size();i++){
			int value = hash_function(target->key[i]); //hash value
			int bit_value = finding_bit_wise_value(value,one->local_bit);
			if(i==0) {
				one->key.push_back(target->key[i]);
			}
			else{
				int bit_value_one = finding_bit_wise_value(hash_function(one->key[0]),one->local_bit);
				if(bit_value == bit_value_one) {
					one->key.push_back(target->key[i]);
				}
				else{
					two->key.push_back(target->key[i]);
				}
			}
		}
		//linking new memory to main address space
		int temp = finding_bit_wise_value(hash_function(one->key[0]),one->local_bit);
		for(int i=0;i<(int)index_pos.size();i++){
			int v=finding_bit_wise_value(index_pos[i],one->local_bit);
			if(temp == v) {
				address_space->bucket_address[index_pos[i]]=one;
			}
			else{
				address_space->bucket_address[index_pos[i]]=two;
			}
		}
		free(target); 
		return insertion(object);
	}
}

void print_function(){
	printf("Status\n");
	printf("Global bit %d\n",address_space->global_bit);
	Bucket *target=NULL;
	for(int i=0;i<(int)address_space->bucket_address.size();i++){
		cout<<i<<"  = " << endl;
		target = address_space->bucket_address[i];
		cout<<" local bit = " << target->local_bit<<endl;
		for(int j=0;j<(int)target->key.size();j++){
			cout<<target->key[j].id<<" ";
		}
		cout<<endl;
	}
	cout<<"Status print done "<<endl;
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
			bool ok = insertion(object);
			if(ok==true) {
				printf("Inserted\n");
			}
			else{
				int value=0;
				assert(value != 1);
			}
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
