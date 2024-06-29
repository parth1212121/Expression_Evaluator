/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

MinHeap::MinHeap(){

    size=0;
    root=NULL;
}

void swap(int &a,int &b){
    int tmp=a;
    a=b;
    b=tmp;
}


int pow_2(int y){
    int ans=1;
    while(y--){
        ans=ans*2;
    }
    return ans;
}

int max_pow_2(int n){

    if(n==0){
    return 0;
        }
    int cnt=0;
    while(n!=1){

        cnt++;
        n=n/2;

    }
    return cnt;
}

int reach_last_node(HeapNode* &tmp,int size){

    int x=size;
    int y=pow_2(max_pow_2(x));
    x=x%(y);

    while(y!=2){
        y=y/2;
        if(x/y==0){
            tmp=tmp->left;
        }
        else{
            tmp=tmp->right;
        }
         x=x%y;
    }
    return x;
}

void raw_push(HeapNode* &n,HeapNode* &root,int size){

    if(root==NULL){
    
        root=n;
        return;
    }
    else{
            HeapNode* tmp=root;
            if(reach_last_node(tmp,size+1)==0){
                    tmp->left=n;
                    n->par=tmp;
            }
            else{
                    tmp->right=n;
                    n->par=tmp;                
            }
            return;
    }
}

// void heapifyUp(int index,vector<int>& heap){             //O(logn)

//     if(index==0){
//         return;   
//     }
//     else{
//         int parent_index=Parent(index);
//         if(heap[parent_index]>heap[index]){
//             swap(heap[parent_index],heap[index]);
//             heapifyUp(parent_index,heap);
//         }
//         return;
//     }
// }

void HeapifyUp(HeapNode* &n,HeapNode* &root){

    if(n==root){
        return;
    }
    else{
        HeapNode* tmp=n;
        while(tmp!=root && tmp->val<tmp->par->val){
            int x=tmp->par->val;
            tmp->par->val=tmp->val;
            tmp->val=x;

            tmp=tmp->par;

            if(tmp==root){
                break;
            }
        }
        return;
    }

}

void MinHeap::push_heap(int num){

    HeapNode* n=new HeapNode(num);
    //cout<<"HI"<<endl;
    raw_push(n,root,size);
    HeapifyUp(n,root);
    size++;
    return ;

}

int MinHeap::get_min(){
    return root->val;
}

// void HeapifyDown_2(int index,vector<int>& heap,int i){          //O(logn)

//     int left=leftchild(index);
//     int right=rightchild(index);
//     int minindex=index;
//     if(left>=i){
//         return;
//     }    
//     if(left<i && heap[left]<heap[minindex]){
//         minindex=left;
//     }
//     if(right<i && heap[right]<heap[minindex]) {
//         minindex=right;
//     }
//     if(index!=minindex){
//         swap(heap[minindex],heap[index]);
//         HeapifyDown_2(minindex,heap,i);
//     }

// }

void HeapifyDown(HeapNode* &n,HeapNode* &root){

    HeapNode* mini=n;
    if(n->left==NULL){
        return;
    }
    else if(n->left && n->left->val<mini->val){
        mini=n->left;
    }
     if(n->right!=NULL){
     if(n->right && n->right->val<mini->val){
        mini=n->right;
    }}

    if(mini!=n){
        swap(n->val,mini->val);
        HeapifyDown(mini,root);
    }
}


void MinHeap::pop(){

    HeapNode* tmp=root;
    if(reach_last_node(tmp,size)==1){
        
        root->val=tmp->right->val;
        tmp->right=NULL;
        //delete tmp;                                     // Once confirm!!!!!!!!

        HeapifyDown(root,root);
    }
    else{
        root->val=tmp->left->val;
        tmp->left=NULL;
        //delete tmp;                                     // Once confirm!!!!!!!!

        HeapifyDown(root,root);
    }
    size--;
    return;

}

MinHeap::~MinHeap(){
    
    delete root;

}
