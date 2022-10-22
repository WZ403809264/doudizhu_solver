#include<bits/stdc++.h>
using namespace std;
int number(char a)
{
	if(a=='3') return 1;
	if(a=='4') return 2;
	if(a=='5') return 3;
	if(a=='6') return 4;
	if(a=='7') return 5;
	if(a=='8') return 6;
	if(a=='9') return 7;
	if(a=='0') return 8;
	if(a=='J') return 9;
	if(a=='Q') return 10;
	if(a=='K') return 11;
	if(a=='A') return 12;
	if(a=='2') return 14;
	if(a=='Y') return 15;
	if(a=='Z') return 16;
	return 0;
}
char List[18]=" 34567890JQKA 2YZ";
char chr(int a)
{
	return List[a];
}
bool in(string a,string b)
{
	if(a[0]=='\0') return 1;
	int i;
	for(i=0;b[i]!='\0'&&number(b[i])<number(a[0]);i++);
	if(b[i]=='\0'||number(b[i])>number(a[0])) return 0;
	a.erase(0,1);
	b.erase(i,1);
	return in(a,b);
}
string del(string card,string d)
{
	if(d[0]=='\0') return card;
	int i;
	for(i=0;card[i]!='\0'&&number(card[i])<number(d[0]);i++);
	d.erase(0,1);
	card.erase(i,1);
	return del(card,d);
}
int same(string card)
{
	int i;
	int num[17];
	int max=0,max2=0;
	memset(num,0,sizeof(num));
	for(i=0;card[i]!='\0';i++)
	{
		num[number(card[i])]++;
		if(num[number(card[i])]>max)
		{
			max=num[number(card[i])];
			max2=number(card[i]);
		}
	}
	return max2*10+max;
}
int paixing(string card)
{
	int len=card.length();
	if(len==0) return -1;
	int Same=same(card);
	switch(Same%10)
	{
		case 1:{
			if(len==1) return 1;
			if(len==2&&number(card[0])==15&&number(card[1])==16) return 21;
			if(len>=5)
			{
				for(int i=0;i<len-1;i++)
				{
					if(number(card[i+1])-number(card[i])!=1) return 0;
				}
				return 10+len-4;
			}
			return 0;
		}
		case 2:{
			if(len==2) return 2;
			if(len&1==0&&len>=6)
			{
				for(int i=0;i<len-2;i+=2)
				{
					if(number(card[i+2])-number(card[i])!=1) return 0;
					else if(number(card[i])!=number(card[i+1])) return 0;
				}
				if(number(card[len-1])!=number(card[len-2])) return 0;
				return 21+len/2-2;
			}
			return 0;
		}
		case 3:{
			if(len==3) return 3;
			if(len==4) return 31;
			if(len==5)
			{
				if(number(card[0])==number(card[1])&&number(card[len-2])==number(card[len-1])) return 32;
				return 0;
			}
			if(number(card[len-1])==16&&number(card[len-2])==15) return 0;
			int three=0,two=0,one=0,i,card2[17];
			int threeappear=0;
			memset(card2,0,sizeof(card2));
			for(i=0;i<len;i++)
			{
				card2[number(card[i])]++;
			}
			for(i=1;i<=16;i++)
			{
				if(i==13) continue;
				if(card2[i]==1) one++;
				else if(card2[i]==2) two++;
				else if(card2[i]==3) three++;
				if(card2[i]==3&&threeappear==0) threeappear=1;
				if(card2[i]!=3&&threeappear==1) threeappear=2;
				if(card2[i]==3&&threeappear==2) return 0;
			}
			if(one==three&&two==0) return 301+three*10;
			if(two==three&&one==0&&number(card[len-1])!=16&&number(card[len-2])!=15) return 302+three*10;
			if(two==0&&one==0) return 300+three*10;
			return 0;
		}
		case 4:{
			if(len==4) return 4;
			if(len==6)
			{
				string dele;
				dele.assign(4,chr(Same/10));
				string newcard=del(card,dele);
				if(number(newcard[0])==number(newcard[1])||(number(newcard[0])==15&&number(newcard[1])==16)) return 0;
				return 421;
			}
			if(len==8)
			{
				string dele;
				dele.assign(4,chr(Same/10));
				string newcard=del(card,dele);
				int Sa=same(newcard);
				if(Sa%10==3||Sa%10==1) return 0;
				if(number(newcard[0])!=number(newcard[1])) return 0;
				if(number(newcard[2])!=number(newcard[3])) return 0; 
				return 422;
			}
			return 0;
		}
	}
}
int banmove[10],banmoves;
bool canplay(string next_hand,string last_hand)
{
	int px=paixing(next_hand);
	if(px==0) return 0;
	for(int i=0;i<banmoves;i++)
	{
		if(banmove[i]==px) return 0;
	}
	int next_len=next_hand.length();
	int last_len=last_hand.length();
	if(next_len==0)
	{
		if(last_len==0) return 0;
		return 1;
	}
	if(last_len==0) return 1;
	int last_px=paixing(last_hand);
	if(last_px==21) return 0;
	if(last_px==4)
	{
		if(px!=21&&px!=4) return 0;
		if(px==4&&(number(next_hand[0])<=number(last_hand[0]))) return 0;
		return 1;
	}
	if(px!=last_px&&px!=4&&px!=21) return 0;
	int s=same(next_hand),s_last=same(last_hand);
	if(s/10<=s_last/10&&px!=4&&px!=21) return 0;
	return 1;
}
int generatemoves(string my_cards,string last_hand,string*next_hand)
{
	int nextlen=0;
	int my_len=my_cards.length(); 
	for(int i=(1<<my_len)-1;i>=0;i--)
	{
		string create="";
		int digit=i,s=0;
		for(s=0;s<my_len;s++)
		{
			if(digit&1)
			{
				create+=my_cards[s];
			}
			digit>>=1;
		}
		if(!canplay(create,last_hand)) continue;
		bool repeat=0;
		for(int j=0;j<nextlen;j++)
		{
			if(next_hand[j]==create)
			{
				repeat=1;
				break;
			}
		}
		if(repeat) continue;
		next_hand[nextlen++]=create;
	}
	return nextlen;
}
string searchresult;
long long node=0;
clock_t start,end;
int search(string my_cards,string enemy_cards,string last_hand,int depth)
{
	if(enemy_cards.length()==0)
	{
		return -1;
	}
	string mvs[100];
	int moves=generatemoves(my_cards,last_hand,mvs);
	for(int i=0;i<moves;i++)
	{
		end=clock();
		node++;
		
		if(depth<=3)
		{
			if(node==1) printf("%d %d/%d node %lld\n",depth,i+1,moves,node);
			else
			{
				double t=0.001*(end-start);
				if(t>0) printf("%d %d/%d nodes %lld time %.2lfs speed %.0lf\n",depth,i+1,moves,node,t,1.0*node/t);
				else printf("%d %d/%d nodes %lld\n",depth,i+1,moves,node);
			}
		}
		if(search(enemy_cards,del(my_cards,mvs[i]),mvs[i],depth+1)==-1)
		{
			if(depth==0) searchresult=mvs[i];
			return 1;
		}
	}
	if(depth==0) searchresult=mvs[0];
	return -1;
}
string output[17]={"不出","3","4","5","6","7","8","9","10","J","Q","K","A","不出","2","小王","大王"};
void print(int result)
{
	printf("第一步：");
	if(searchresult[0]=='\0') cout<<output[0];
	else
	{
		for(int i=0;searchresult[i]!='\0';i++)
		{
			cout<<output[number(searchresult[i])]<<" ";
		}
	}
	if(result==1) printf("  P1赢\n");
	else if(result==-1) printf("  P2赢\n");
}
int main()
{
	string p1,p2,last="";
	system("title 斗地主残局解题器");
	printf("斗地主残局解题器\n");
	printf("输入P1牌：");
	cin>>p1;
	printf("输入P2牌：");
	cin>>p2;
	int i,j;
	for(j=0,i=p1.length()-1;j<i;i--,j++)
	{
		char temp=p1[i];
		p1[i]=p1[j];
		p1[j]=temp;
	}
	for(j=0,i=p2.length()-1;j<i;i--,j++)
	{
		char temp=p2[i];
		p2[i]=p2[j];
		p2[j]=temp;
	}
	printf("输入禁手数量：");
	cin>>banmoves;
	if(banmoves)
	{
		printf("输入禁手：");
		for(int i=0;i<banmoves;i++)
		{
			cin>>banmove[i];
		}
	}
	start=end=clock();
	printf("正在计算……\n");
	int result=search(p1,p2,last,0);
	print(result);
	printf("计算完毕，用时%.3lf秒，变化数%lld\n",0.001*(end-start),node);
	while(1)
	{
		p1=del(p1,searchresult);
		if(p1.length()==0) break;
		last=searchresult;
		swap(p1,p2);
		printf("P1牌：");
		for(i=p2.length()-1;i>=0;i--)
		{
			cout<<output[number(p2[i])]<<" ";
		}
		printf("\n");
		if(last[0]=='\0')
		{
			cout<<output[0]<<endl;
		}
		else
		{
			for(i=last.length()-1;i>=0;i--)
			{
				cout<<output[number(last[i])]<<" ";
			}
			printf("\n");
		}
		printf("P2牌：");
		for(i=p1.length()-1;i>=0;i--)
		{
			cout<<output[number(p1[i])]<<" ";
		}
		printf("\n");
		printf("请输入P2出牌（不出请输入P）：");
		string input;
		cin>>input;
		if(input=="P") input="\0";
		for(j=0,i=input.length()-1;j<i;i--,j++)
		{
			char temp=input[i];
			input[i]=input[j];
			input[j]=temp;
		}
		while(!canplay(input,last)||!in(input,p1))
		{
			printf("出牌不合规，请重新输入P2出牌（不出请输入P）：");
			cin>>input;
			if(input=="P") input="\0";
			for(j=0,i=input.length()-1;j<i;i--,j++)
			{
				char temp=input[i];
				input[i]=input[j];
				input[j]=temp;
			}
		}
		p1=del(p1,input);
		if(p1.length()==0) break;
		last=input;
		swap(p1,p2);
		node=0;
		start=end=clock();
		printf("正在计算……\n");
		int result=search(p1,p2,last,0);
		print(result);
		printf("计算完毕，用时%.3lf秒，变化数%lld\n",0.001*(end-start),node);
	}
	system("pause>nul");
	return 0;
}
