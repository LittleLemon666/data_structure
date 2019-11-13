#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
//If the tree doesn't have parents, it is an empty tree.
//If parents of the tree have neither the right child nor the left child, the tree is only a root.
//The test cases have some space trap such as "1 2 3" instead of "1 2 3".
struct Node
{	
	long long data;
	struct Node *left, *right, *parents;
};
typedef struct Node node;
node *root=(node*)malloc(sizeof(node));
int have_print;
void ins(node *tree, long long x)
{
	node *head = tree;
	if(!(head->parents)) //initializing tree is very important. 
	{
		head->data=x;
		head->left=NULL;
		head->right=NULL;
		head->parents=root;
		return;
	}
	while(1)
	{
		if(x <= head->data)
		{
			if(head->left)
			{
				head=head->left;
			}
			else
			{
				head->left = (node*)malloc(sizeof(node));
				head->left->data=x;
				head->left->left=NULL;
				head->left->right=NULL;
				head->left->parents=head;
				return; 
			}
		}
		else if(x > head->data)
		{
			if(head->right)
			{
				head=head->right;
			}
			else
			{
				head->right = (node*)malloc(sizeof(node));
				head->right->data=x;
				head->right->left=NULL;
				head->right->right=NULL;
				head->right->parents=head;
				return; 
			}
		}
	}
}

void del(node *tree, long long x)
{
	node *head = tree;
	if(!(head->parents)) return; //tree is empty
	while(head->data!=x)
	{
		if(x > head->data)
		{
			head=head->right;
			if(!head) return; //not found
		}
		else
		{
			head=head->left;
			if(!head) return; //not found
		}
	}
	if(head->parents->left==NULL&&head->parents->right==NULL) //root
	{
		if(head->left&&head->right)
		{
			node* head_del=head->left;
			while(head_del->right)
			{
				head_del=head_del->right;
			}
			if(head_del==head->left)
			{
				head->left=head_del->left;
				if(head_del->left)
				{
					head_del->left->parents=head;
				}
			}
			else
			{
				head_del->parents->right=head_del->left;
				if(head_del->left)
				{
					head_del->left->parents=head_del->parents;
				}
			}
			head->data=head_del->data;
		}
		else if(head->left) //the root only has a left child
		{
			head->data=head->left->data;
			int ll_is_null=0;
			if(head->left->left)
			{
				if(head->left->right)
				{
					head->right=head->left->right;
					head->right->parents=head;
				}
			}
			else
			{
				ll_is_null=1;
				head->right=head->left->right;
				if(head->right)
					head->right->parents=head;
			}
			if(!ll_is_null)
			{
				head->left=head->left->left;
				head->left->parents=head;
			}
			else
			{
				head->left=NULL;
			}
		}
		else if(head->right) //the root only has a right child
		{
			head->data=head->right->data;
			int rr_is_null=0;
			if(head->right->right)
			{
				if(head->right->left)
				{
					head->left=head->right->left;
					head->left->parents=head;
				}
			}
			else
			{
				rr_is_null=1;
				head->left=head->right->left;
				if(head->left)
					head->left->parents=head;
			}
			if(!rr_is_null)
			{
				head->right=head->right->right;
				head->right->parents=head;
			}
			else
			{
				head->right=NULL;
			}
		}
		else //root is a leaf
		{
			head->parents=NULL;
		}
	}
	else
	{
		if(head->left&&head->right) //head is not a root
		{
			node* head_del=head->left;
			while(head_del->right)
			{
				head_del=head_del->right;
			}
			head->data=head_del->data;
			if(head_del==head->left)
			{
				head->left=head_del->left;
				if(head_del->left)
				{
					head_del->left->parents=head;
				}
			}
			else
			{
				head_del->parents->right=head_del->left;
				if(head_del->left)
				{
					head_del->left->parents=head_del->parents;
				}
			}
		}
		else if(head->left)
		{
			head->left->parents=head->parents;
			if(head->parents->left==head)
			{
				head->parents->left=head->left;
			}
			else
			{
				head->parents->right=head->left;
			}
		}
		else if(head->right)
		{
			head->right->parents=head->parents;
			if(head->parents->left==head)
			{
				head->parents->left=head->right;
			}
			else
			{
				head->parents->right=head->right;
			}
		}
		else
		{
			if(head->parents->left==head)
			{
				head->parents->left=NULL;
			}
			else
			{
				head->parents->right=NULL;
			}
		}
	}
}

void preorder(node *tree)
{
	if(!tree||!(tree->parents)) return;
	node *head=tree;
	if(have_print)
		printf(" %lld",head->data);
	else
	{
		printf("%lld",head->data);
		have_print=1;
	}
	preorder(head->left);
	preorder(head->right);
}

void inorder(node *tree)
{
	if(!tree||!(tree->parents)) return;
	node *head=tree;
	inorder(head->left);
	if(have_print)
		printf(" %lld",head->data);
	else
	{
		printf("%lld",head->data);
		have_print=1;
	}
	inorder(head->right);
}

void postorder(node *tree)
{
	if(!tree||!(tree->parents)) return;
	node *head=tree;
	postorder(head->left);
	postorder(head->right);
	if(have_print)
		printf(" %lld",head->data);
	else
	{
		printf("%lld",head->data);
		have_print=1;
	}
}

int level(node *tree, int p)
{
	if(!tree||!(tree->parents)) return p-1;
	node *head=tree;
	int x = level(head->left,p+1);
	int y = level(head->right,p+1);
	return x>y?x:y;
}

int node_num(node *tree)
{
	if(!tree||!(tree->parents)) return 0;
	node *head=tree;
	int x = node_num(head->left);
	int y = node_num(head->right);
	return x+y+1;
}

int internalnode(node *tree)
{
	if(!tree||!(tree->parents)) return 0;
	node *head=tree;
	if(!head->left&&!head->right) return 0;
	int x = internalnode(head->left);
	int y = internalnode(head->right);
	return x+y+1;
}

long long min(node *tree)
{
	if(!(tree->parents)) return 0;
	node *head=tree;
	while(head->left)
	{
		head=head->left;
	}
	return head->data;
}

long long max(node *tree)
{
	if(!(tree->parents)) return 0;
	node *head=tree;
	while(head->right)
	{
		head=head->right;
	}
	return head->data;
}

int main()
{
	node *tree=(node*)malloc(sizeof(node));
	tree->parents=NULL;
	root->left=NULL; //uninitialized is rather undefine than NULL
	root->right=NULL;	
	string s_in;
	int i,len,sign,have_value;
	long long t;
	while(getline(cin,s_in))
	{
		len=s_in.length();
		if(len>=3&&s_in[0]=='i'&&s_in[1]=='n'&&s_in[2]=='s')
		{
			t=0;
			sign=1;
			have_value=0;
			for(i=4;i<len;i++)
			{
				if(s_in[i]=='-')
				{
					sign = -1;
				}
				else if(s_in[i]!=' ')
				{
					t=t*10+sign*(s_in[i]-'0');
					have_value=1;
					if(i==len-1)
					{
						ins(tree,t);
					}
				}
				else if(have_value)
				{
					ins(tree,t);
					t=0;
					sign=1;
					have_value=0;
				}
			}
		}
		else if(len>=3&&s_in[0]=='d')
		{
			t=0;
			sign=1;
			have_value=0;
			for(i=4;i<len;i++)
			{
				if(s_in[i]=='-')
				{
					sign=-1;
				}
				else if(s_in[i]!=' ')
				{
					t=t*10+sign*(s_in[i]-'0');
					have_value=1;
					if(i==len-1)
					{
						del(tree,t);
					}
				}
				else if(have_value)
				{
					del(tree,t);
					t=0;
					sign=1;
					have_value=0;
				}
			}
		}
		else if(len>=9&&s_in[0]=='p'&&s_in[1]=='o')
		{
			have_print=0;
			postorder(tree);
			if(have_print)
				printf("\n");
		}
		else if(len>=8&&s_in[0]=='p'&&s_in[1]=='r')
		{
			have_print=0;
			preorder(tree);
			if(have_print)
				printf("\n");
		}
		else if(len>=7&&s_in[0]=='i'&&s_in[1]=='n'&&s_in[2]=='o')
		{
			have_print=0;
			inorder(tree);
			if(have_print)
				printf("\n");
		}
		else if(len>=5&&s_in[0]=='l')
		{
			printf("%d\n",level(tree,1));
		}
		else if(len>=4&&s_in[0]=='n')
		{
			printf("%d\n",node_num(tree));
		}
		else if(len>=12&&s_in[0]=='i'&&s_in[1]=='n'&&s_in[2]=='t')
		{
			printf("%d\n",internalnode(tree));
		}
		else if(len>=3&&s_in[0]=='m'&&s_in[1]=='i')
		{
			if(tree->parents!=NULL)
				printf("%lld\n",min(tree));
		}
		else if(len>=3&&s_in[0]=='m'&&s_in[1]=='a')
		{
			if(tree->parents!=NULL)
				printf("%lld\n",max(tree));
		}
	}
	return 0;
}
