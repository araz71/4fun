#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

class HNode;
void huffman_build(vector<HNode *> &tree);
class HNode
{
  public:
	int type;
	int cnt;
	char ch;
	HNode *left;
	HNode *right;
	HNode()
	{
		left = 0;
		ch = 0;
		cnt = 0;
		right = 0;
		type = 0;
	}
};
bool cmp_node(HNode *a, HNode *b)
{
	if (a->cnt < b->cnt)
	{
		return true;
	}
	return false;
}

void msort(vector<HNode *> &t)
{
	HNode *m, *x, h1, h2;
	for (int j = 0; j < t.size(); j++)
	{
		m = t.at(j);
		for (int i = j; i < t.size(); i++)
		{
			x = t.at(i);
			if (m->cnt > x->cnt)
			{
				m = x;
			}
		}
		h1 = *t.at(j);
		h2 = *m;

		*t.at(j) = h2;
		*m = h1;
	}
}

void print_tree(HNode *t)
{
	if (t == 0)
		return;
	cout << "\tvalue : " << t->cnt << " ch: " << t->ch << "\r\n";
	cout << "left : \r\n";
	print_tree(t->left);
	cout << "right : \r\n";
	print_tree(t->right);
}

stack<int>fs;
int find(HNode *p, char _c){
	if(p==NULL){
		return 0;
	}
	
	if(p->ch==_c){
		return 1;
	}
	if(find(p->right, _c)){
		fs.push(1);
		return 1;
	}
	if(find(p->left, _c)){
		fs.push(0);
		return 1;
	}
	return 0;
}
int main()
{
	vector<HNode *> htree;
	vector<HNode *>::iterator p;
	HNode *temp;
	int f = 0;
	char str[] = "huffman codding program!";
	cout << "started...\r\n";
	for (int i = 0; i < strlen(str); i++)
	{
		f = 0;
		p = htree.begin();
		while (p != htree.end())
		{
			temp = *p;
			if (temp->ch == str[i])
			{
				temp->cnt++;
				f = 1;
				break;
			}
			p++;
		}
		if (!f)
		{
			HNode *t = new HNode;
			t->ch = str[i];
			t->cnt = 1;
			htree.push_back(t);
		//	cout << "character " << str[i] << " inserted\r\n";
		}
	}

	huffman_build(htree);
	print_tree(htree.at(0));
	cout << "tokandi\r\n";
	queue<int>res;
	for(int i=0; i<strlen(str); i++){
		if(find(htree.at(0), str[i])){
			while(!fs.empty()){
				cout<<(int)(fs.top());
				res.push(fs.top());
				fs.pop();
			}
		}
	}
	
	uint8_t res_bin[res.size()];
	memset(res_bin, 0, res.size());
	int l=0;
	int c=0;
	while(!res.empty()){
		if(res.front()){
			res_bin[c] |=1;
		}
		
		res.pop();
		l++;
		if(l>=8){
			l=0;
			c++;
		}else{
			res_bin[c]=res_bin[c]<<1;
		}
	}
	printf("\r\n");
	for(int i=0; i<c; i++){
		printf("%02x ", res_bin[i]);
	}
	
	return 10;
}

void huffman_build(vector<HNode *> &tree)
{
	vector<HNode *> htree;
	HNode *a, *b, *temp;
	if (tree.size() <= 1)
		return;

	//cout << "size : " << tree.size() << "\r\n";

	msort(tree);
	//cout << "sorted\r\n";
	for (int i = 0; i < tree.size(); i++)
	{
		a = tree.at(i);
		//cout << "char " << a->ch << " size: " << a->cnt << "\r\n";
	}
	for (int i = 0; i < tree.size() - 1; i += 2)
	{
		temp = new HNode;
		a = tree.at(i);
		temp->right = a;
		b = tree.at(i + 1);
		temp->left = b;
		temp->cnt = a->cnt + b->cnt;
		htree.push_back(temp);
		//cout << "sum : " << temp->cnt << "\r\n";
	}
	if ((tree.size() % 2) == 0)
	{
	}
	else
	{
		a = tree.at(tree.size() - 1);
		htree.push_back(a);
	}

	tree = htree;
	huffman_build(tree);
}