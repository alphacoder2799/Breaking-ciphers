#include<bits/stdc++.h>
#include<fstream>
using namespace std;

void cae_enc()
{
	cout<<"Please enter the string you wish to encrypt: ";
	string s;
	fflush(stdin);
	getline(cin,s);
	for(int i=0;i<s.length();i++)
	{
		if(isalpha(s[i]))
		{
			s[i]=toupper(s[i]);
			if(s[i]<=87)
			s[i]+=3;
			else
			s[i]-=23;
		}
	}
	cout<<"The encrypted message is: "<<s<<endl;
	cout<<"You have full safety cover now!"<<endl;
}

void cae_dec()
{
	cout<<"Please enter the string you wish to decrypt: ";
	string s;
	fflush(stdin);	
	getline(cin,s);
	for(int i=0;i<s.length();i++)
	{
		if(isalpha(s[i]))
		{
			s[i] = toupper(s[i]);
			if(s[i]<=67)
			s[i]+=23;
			else
			s[i]-=3;
		}
		
	}
	cout<<"The decrypted message is: "<<s<<endl;
	cout<<"Cracked it captain!"<<endl;
}

void caesar()
{
	cout<<"---------Caesar Cipher---------"<<endl;
	cout<<"Select 1 for encryption"<<endl;
	cout<<"Select 2 for decryption"<<endl;
	int ch;
	cin>>ch;
	if(ch==1)
	cae_enc();
	else if(ch==2)
	cae_dec();
	else
	cout<<"Not a valid option";
}

void shi_enc()
{
	cout<<"Please enter the string you wish to encrypt: ";
	string s;
	fflush(stdin);
	getline(cin, s);
	cout<<endl<<"Please enter a shift value: ";
	int shifter;
	cin>>shifter;
	for(int i=0;i<s.length();i++)
	{
		if(isalpha(s[i]))
		{
			s[i]=toupper(s[i]);
			s[i]-=65;
			s[i]=(s[i]+shifter)%26;
			s[i]+=65;
		}
	}
	cout<<"The encrypted message is: "<<s<<endl;
	cout<<"You have full safety cover now!"<<endl;
}

void shi_dec()
{
	cout<<"Please enter the string you wish to decrypt: ";
	string s;
	fflush(stdin);
	getline(cin,s);
	string temp = s;
	cout<<endl<<"Here is the list of your possible decryptions: "<<endl;
	for(int i=1;i<=26;i++)
	{
		temp=s;
		for(int j=0;j<temp.length();j++)
		{
			if(isalpha(temp[j]))
			{
				temp[j]=toupper(temp[j]);
				temp[j]-=65;
				temp[j]=(temp[j]+i)%26;
				temp[j]+=65;
			}
		}
		cout<<temp<<" "<<26-i<<endl;
	}
}

void shift()
{
	cout<<"---------Shift Cipher---------"<<endl;
	cout<<"Select 1 for encryption"<<endl;
	cout<<"Select 2 for decryption"<<endl;
	int ch;
	cin>>ch;
	if(ch==1)
	shi_enc();
	else if(ch==2)
	shi_dec();
	else
	cout<<"Not a valid option";
}

void vig_enc()
{
	cout<<"Please enter the string you wish to encrypt: ";
	string s;
	fflush(stdin);
	getline(cin, s);
	//Fetching a random key from the key file
	ifstream input_file;
	input_file.open("keys.txt");
	vector<string> keys;
	string str;
	while (getline(input_file, str))
	{
		if(str.size() > 0)
			keys.push_back(str);
	}
	input_file.close();
	
	srand((unsigned) time(0));
	int randomNumber;
	randomNumber = (rand() % 968);
	string mykey = keys[randomNumber];
	string temp = mykey;
	cout<<"THE SECRET KEY IS: "<<mykey<<endl;
	for(int i=0,j=0;i<s.length();i++,j++)
	{
		mykey=temp;
		if(j>=mykey.length())
		{
			j=0;
		}
		
		if(isalpha(s[i]))
		{
			s[i]=toupper(s[i]);
			s[i]-=65;
			mykey[j]-=65;
			s[i]=s[i]+mykey[j];
			if(s[i]>25)
			s[i]=s[i]%26;
			s[i]+=65;
		}
		else
		{
			j--;
		}
		//spaces and other chars are ignored and key is utilised fully
	}
	cout<<"The encrypted message is: "<<s<<endl;
	cout<<"You have full safety cover now!"<<endl;
}

void vig_dec()
{
	fflush(stdin);
	string para;
	ifstream text_data;
	text_data.open("encrypted.txt");
	string str1;
	
	while (getline(text_data, str1))
	{
		if(str1.size() > 0)
			para+=str1+" ";
	}
	text_data.close();

	
	ifstream input_file;
	input_file.open("keys.txt");
	vector<string> keys;
	string str;
	while (getline(input_file, str))
	{
		if(str.size() > 0)
			keys.push_back(str);
	}
	input_file.close();

	ifstream expectedfreq;
	expectedfreq.open("expectedFreq.txt");
	map<char, float> expected;
	string trial;
	while (getline(expectedfreq, trial))
	{
		string subtry = "";
		for(int i=3;i<=trial.size();i++)
		subtry+=trial[i];
		
		float val = stof(subtry);
		if(trial.size() > 0)
		{
			expected[trial[0]]= val;
		}
	}
	
	expectedfreq.close();

	
	
	vector<string> possibilities;
	vector<float> mismatch;
	for(int k=0;k<keys.size();k++)
	{
		string mykey = keys[k];
		string temp = mykey;
		
		string s = para;
		
		int totalcount = 0;
		
		map<char, float> alphabet_frequencies;  

		for(int i=0,j=0;i<s.length();i++,j++)
		{	
			mykey=temp;
			
			if(j>=mykey.length())
			{
				j=0;
			}
			
			if(isalpha(s[i]))
			{
				s[i]=toupper(s[i]);
				s[i]-=65;
				mykey[j]-=65;
				s[i]=s[i]-mykey[j];
				if(s[i]<0)
				s[i]+=26;
				s[i]+=65;
				char a = s[i];
				alphabet_frequencies[a]+=1;
				totalcount++; 
			}
			else
			{
				j--;
			}
		}
		
		possibilities.push_back(s);
		
	    for (auto it = alphabet_frequencies.begin(); it != alphabet_frequencies.end(); it++) 
		{
	        it->second = ((it->second)/(float)totalcount)*100;
	    }

		float cal = 0;
		for(char i = 65;i<=90;i++)
		{
			float sum = fabs(expected[i]-alphabet_frequencies[i]);
			cal+=sum;
		}
		
		mismatch.push_back(cal);
	}
	
	float min_ele = *min_element(mismatch.begin(), mismatch.end());
	int ind;
	for(int i=0;i<mismatch.size();i++)
	{
		if(mismatch[i]==min_ele)
		{
			ind = i;
			break;
		}
	}
	cout<<"***************************************************************************************************"<<endl;
	cout<<"The key is "<<keys[ind]<<endl;
	cout<<"THE MESSAGE HAS BEEN DECODED: "<<endl;
	cout<<possibilities[ind];
	
}

void vigenere()
{
	cout<<"---------Vignere Cipher---------"<<endl;
	cout<<"Select 1 for encryption"<<endl;
	cout<<"Select 2 for decryption"<<endl;
	int ch;
	cin>>ch;
	if(ch==1)
	vig_enc();
	else if(ch==2)
	vig_dec();
	else
	cout<<"Not a valid option";
}


int main()
{
    cout<<"Welcome to secret labs."<<endl;
    cout<<"Select one option from below:"<<endl;
    cout<<"Press 1 for Caesar cipher"<<endl;
    cout<<"Press 2 for Shift cipher"<<endl;
    cout<<"Press 3 for Vigenere cipher"<<endl;
    
    int option;
    cin>>option;
    if(option==1)
    caesar();
    else if(option==2)
    shift();
    else if(option==3)
    vigenere();
    else
    cout<<"Not a valid option!"<<endl;
    return 0;
}
