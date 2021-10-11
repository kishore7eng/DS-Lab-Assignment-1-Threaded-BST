

#include <iostream>

using namespace std;
//creating a class node to store elements of type tree
class node
{
    public:
    node*left;
    int data;
    node*right;
    bool lthread;
    bool rthread;
    int rcount;
};
//creating node of type list to store data in linked list
class lnode
{
public:
    int data;
    lnode*next;
};
class BST
{
public:
    //createnode function creates new node and returns the address of created node
     node*createnode(int data)
     {
        node *n =new node;
        n->data=data;
        n->left=NULL;
        n->right=NULL;
        n->lthread=true;
        n->rthread=true;
        n->rcount=0;
        return n;

     }
     //insernode fun ction inserts elements if not present in BST else throws an exception
    node* insertnode(node*root,int data)
    {
        node*ptr=root;
        node*parent=NULL;
        int x=-1;
          try
          {
          if(searchkey(ptr,data)==true)//searchkey function returns true if element already present in BST
            throw x;
          }
          catch(int x)
          {
            cout<<"Expception caught :Element already present\n"<<endl;
            return NULL;
          }
        while(ptr!=NULL)
        {

           parent=ptr;
           if(data<ptr->data)
           {
              if(ptr->lthread==false)
                {
                  ptr=ptr->left;

                }
              else break;
            }
           else if (data>ptr->data)
            {
                if (ptr->rthread==false)
                 {
                     ptr->rcount++;
                     ptr=ptr->right;

                 }
                else
                {
                        ptr->rcount++;
                        break;
                }
          }
        }
        node*n=createnode(data);
        if(parent==NULL)
            root=n;
        else if (data<parent->data)
        {
            n->left=parent->left;
            n->right=parent;
            parent->lthread=false;
            parent->left=n;

        }
        else
        {
           n -> left = parent;
           n -> right = parent -> right;
           parent -> rthread = false;
           parent -> right = n;
        }
        cout<<"success"<<endl;



    return root;
}
    bool searchkey(node*root,int key)
    {
        if(root==NULL)
            return false;
        while(1)
        {
            if(key<root->data)
            {
                if(root->lthread==true)
                    return false;
                root=root->left;
            }
            else if(key>root->data)
            {
                if (root->rthread==true)
                    return false;
                root=root->right;
            }
            else
                return true;
        }
    }
    node* searchfun(node*root,int key)
    {
        if(root==NULL)
            return NULL;
        while(1)
        {
            if(key<root->data)
            {
                if(root->lthread==true)
                    return NULL;
                root=root->left;
            }
            else if(key>root->data)
            {
                if (root->rthread==true)
                    return NULL;
                root=root->right;
            }
            else
                return root;
        }
    }
    //deletenode function deletes element in BST
    node* deletenode(node* root,int key)
    {
        int x=-1;
        try{
          if(!searchkey(root,key))
            throw x;
        }
        catch(int x)
        {
            cout<<"Expception caught: Element not present"<<endl;
            return NULL;
        }
        node*parent=NULL;
        node*ptr=root;
        //deleting an element has three cases
        if(ptr->lthread==false && ptr->rthread==false)//if both lthread and rthread are false then the node to be deleted has two children
                root=twochildnode(root,parent,ptr);
        else if(ptr->rthread==false )//if  rthread is false then the node to be deleted has only right children
            root=onechildnode(root,parent,ptr);
        else if( ptr->lthread==false)//if both lthread is false then the node to be deleted has only left children
            root=onechildnode(root,parent,ptr);
        else//if none are false then the node to be deleted is a leaf
            root=leafnode(root,parent,ptr);
        return root;
    }
    //deleting a leaf node
        node *leafnode(node*root,node*parent,node*ptr)
        {
            if(parent==NULL)
                root=NULL;
            else if(ptr==parent->left)
            {
                parent->lthread=true;
                parent->left=ptr->left;
            }
            else if(ptr==parent->right)
            {
                parent->rthread=true;
                parent->left=ptr->right;
            }
            free(ptr);
            return root;
        }
        //deleting node having one children
        node*onechildnode(node*root,node*parent,node*ptr)
        {
            node *child;
            if (ptr->lthread==false)
                child=ptr->left;
            else
              child=ptr->right;
            if(parent==NULL)
                root=child;
            else if(ptr==parent->left)
                parent->left=child;
            else
                parent->right=child;
            node*succ=inS(ptr);
            node*pred=inP(ptr);
            if(ptr->rthread==true)
                pred->right=succ;
            if(ptr->lthread==true)
                succ->left=pred;
            free(ptr);
            return root;

        }
        //deleting node having two children
        node*twochildnode(node*root,node*parent,node*ptr)
        {
            node*succ=ptr->right;
            node*psucc=ptr;
            while (succ->lthread==false)
            {
                 psucc = succ;
                 succ = succ->left;
            }

            ptr->data=succ->data;
            if (succ->lthread == true && succ->rthread == true)
                root = leafnode(root, psucc, succ);
            else
                root = onechildnode(root, psucc, succ);

            return root;

        }
        //finding inorder successcor
        node*inS(node*ptr)
        {
            if (ptr->rthread==true)
            {
                return ptr->right;
            }
            else
            {
                ptr=ptr->right;
                while(ptr->lthread==false)
                    ptr=ptr->left;
                return ptr;
            }

        }
        //finding inorder predecessor
        node*inP(node*ptr)
        {
            if(ptr->lthread==true)
                return ptr->left;
            else
            {
                ptr=ptr->left;
                while(ptr->rthread==false)
                    ptr=ptr->right;
            }
            return ptr;
        }

    //finding Kth largest element in BST
    int Kthlargest(node*root,int k)
    {
        if(root==NULL)
            return -1;
        node*temp=root;
        while(temp)
        {
            if(temp->rcount+1==k)
                return temp->data;
            else if(temp->rcount+1<k)
            {
                k=k-(temp->rcount+1);
                temp=temp->left;
            }
            else
                temp=temp->right;
        }
        return -1;
    }
    //writing dot code in file to print the BST
    void printBST(FILE*fp,node*root)
    {

        node*ptr=root;
        if(ptr->lthread==false)
        {

            fprintf(fp,"  %d -> %d;\n",ptr->data,ptr->left->data);
            printBST(fp,ptr->left);
        }
       else{
            if(ptr->left!=NULL){
                fprintf(fp,"  %d -> %d [color=\"#ff0000\"];\n",ptr->data,ptr->left->data);

               }
        }

         if(ptr->rthread==false)
        {
            fprintf(fp,"  %d-> %d;\n",ptr->data,ptr->right->data);
            printBST(fp,ptr->right);
        }
        else
        {
            if(ptr->right!=NULL)
            {
               fprintf(fp,"  %d -> %d[color=\"#0000ff\"];\n",ptr->data,ptr->right->data);
               return;
            }

        }
        return;
    }

};


class LIST:public BST
{
    public:
    int flag=1;
    lnode*head=NULL;
    lnode*p=NULL;
    //createlnode function creates new node of type linked list and returns its address

    lnode*createlnode(int data)
     {
         lnode*n=new lnode;
         n->data=data;
         n->next=NULL;
         return n;
     }
     //inorder reversal in BST
     lnode*reverseinorder(node*root)
    {
        lnode*head=NULL;
        lnode*p=NULL;
        node*temp=root;
        node*ptr=NULL;
        while(temp->rthread==false){
            temp=temp->right;
            }
        lnode*n=createlnode(temp->data);
        head=n;
        p=n;
        while(inP(temp)!=NULL)
        {
            ptr=inP(temp);
            lnode *n1=createlnode(ptr->data);
            p->next=n1;
            p=p->next;
            temp=ptr;

        }
        return head;

    }
    //finding all elements between K1 and K2
    lnode*allElementsBetween(int k1,int k2,node*root)
    {
        node*temp=root;
        if(temp==NULL)
            return head;
        if(temp->data>k1 && temp->lthread==false)
        {
            allElementsBetween(k1,k2,temp->left);
        }
        if(temp->data>=k1 &&temp->data <=k2)
        {
            lnode *n=createlnode(temp->data);
            if(flag==1){
                head=n;
                p=n;
                flag=0;
                }
            else
            {
                p->next=n;
                p=p->next;
            }
        }
        if(temp->data<k2 &&temp->rthread==false )
        {
            allElementsBetween(k1,k2,temp->right);
        }

        return head;

    }
    lnode*ElementsBetween(int k1,int k2,node*root)
    {
        lnode*head=NULL;
        head=allElementsBetween(k1,k2,root);
        return head;
    }
    //printing elements of the list for better visualization
    void printlist(lnode*n)
    {
            while (n != NULL)
            {
              cout << n->data << " ";
              n = n->next;
            }
            cout<<endl;
    }
};
int main()
{
    BST obj;
    node*root=NULL;
    node*ptr=NULL;
    node*s=NULL;
    LIST obj1;
    lnode*head=NULL;
    FILE*fp;
    fopen_s(&fp,"C:\\Users\\rmkis\\new.txt","w+");
    fprintf(fp, "digraph BST {\n");
    fprintf(fp, "label=\"Left thread: RED , Right thread: BLUE\"\n");
    int a,x,k1,k2;
    root=obj.insertnode(root,6);
    root=obj.insertnode(root,3);
    root=obj.insertnode(root,8);
    root=obj.insertnode(root,1);
    root=obj.insertnode(root,5);
    root=obj.insertnode(root,7);
    root=obj.insertnode(root,11);
    root=obj.insertnode(root,9);
    root=obj.insertnode(root,13);
    while(1){
    cout<<" 1-Insert\n 2-Search\n 3-Delete\n 4-ReverseInorder\n 5-Successor\n 6-Split on K\n 7-All elements between k1 and k2\n 8-Kth Largest Element\n 9-Print Tree\n 10-Exit\n";
    cout<<"Enter Choice:";
    cin>>a;

    switch(a)
    {
        case 1:cout<<"Enter the element to be inserted: ";
               cin>>x;
               root=obj.insertnode(root,x);
               break;
        case 2:cout<<"Enter the element to be searched: ";
               cin>>x;
               s=obj.searchfun(root,x);
               cout<<"Element found at reference "<<s<<endl;
               break;
        case 3:cout<<"Enter the element to be deleted: ";
               cin>>x;
               obj.deletenode(root,x);
               break;
        case 4:cout<<"Inorder reversal\n";
               head=obj1.reverseinorder(root);
               cout<<"Printing the elements of the list\n";
               obj1.printlist(head);
               break;
        case 5:cout<<"Enter the element for which Inorder Successor to be found: ";
               cin>>x;
               ptr=obj.searchfun(root,x);
               ptr=obj.inS(ptr);
               cout<<"Inorder successor of "<<x<<" is: "<<ptr->data<<endl;
               break;
        case 6:cout<<"Enter the element on which the tree is to be splitted: ";
               cin>>x;
               cout<<"Sorry I haven't implemented this function";
               break;
        case 7:cout<<"Enter k1 and k2: ";
               cin>>k1;
               cin>>k2;
               head=obj1.ElementsBetween(k1,k2,root);
               cout<<"Printing the elements of the list\n";
               obj1.printlist(head);
               head=NULL;
               break;
        case 8: cout<<"Enter K to find Kth largest element: ";
               cin>>x;
               cout<<x<<"th latgest element is: "<<obj.Kthlargest(root,x)<<endl;
               break;
        case 9:cout<<"Printing tree using graphviz\n";
               obj.printBST(fp,root);
               fprintf(fp, "}\n");
               break;

        case 10:exit(1);
    }
    }
    delete(root);
    delete(head);
    delete(ptr);
    delete(s);
    fclose(fp);
    return 0;
}
