/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
//Write your code below this 





SymNode* find(SymNode* root,string k){

          SymNode* tmp=root;
            while((tmp!=NULL) && (k!=tmp->key)){
                if(k<tmp->key){
                    tmp=tmp->left;
                }
                else{
                    tmp=tmp->right;
                }
            }
            return tmp;

}

int height2(SymNode* n){
    
    if(n==NULL){
        return -1;
    }
 
    return (max(height2(n->left),height2(n->right))+1);
    

}

bool is_balanced2(SymNode* n){
    if(n==NULL){
        return true;
    }
    else{
        if(abs(height2(n->left)-height2(n->right))<=1){
            return true;
        }
        return false;
    }
}

void insert_raw(SymNode* &root,SymNode* &v){                   
                                                  // Worst Case -->O(n).
                                                  // Average case--> O(log n)
    // Inserts node v into the BST.
    //Assumes that v->left and v->right are null
    // Assumes that v->key is not present in TREE.
    if(root==NULL){
        
        root=v;
        return ;
    }
    if(v->key<root->key){
        // Insert on the left side of the root.
        if(root->left==0){
            // We have found the right place to insert.
            root->left=v;
            v->par=root;
        }
        else{
            insert_raw(root->left,v);
        }
  }
  else{
     // Insert on the right side of the root.
        if(root->right==0){
            // We have found the right place to insert.
            root->right=v;
            v->par=root;
        }
        else{
            insert_raw(root->right,v);
        }
  }
}

void balance(SymNode* &root, SymNode* &n){

    SymNode* tmp=n;
    if(tmp==root){
        return;
    }
    
    while(is_balanced2(tmp->par)){
        tmp=tmp->par;
        if(tmp==root){
            return;
        }
    }
     
    // Case_1
   
     if((tmp->par->left==tmp) && (n->key<tmp->key)){       
      root=tmp->LeftLeftRotation();
    }

    // Case_2

    else if(tmp->par->right==tmp && (n->key)>(tmp->key)){         
      root=tmp->RightRightRotation();
    }

    // Case_3

    else if(tmp->par->left==tmp && n->key>tmp->key){            
      root=tmp->LeftRightRotation();    
    }

    // Case_4

    else if(tmp->par->right==tmp && n->key<tmp->key){          
      root=tmp->RightLeftRotation();
    }
}


SymNode* find_min(SymNode* root){
    if(root==NULL){
        return NULL;
    }
    while(root->left!=NULL){
        root=root->left;
    }
    return root;
}

SymNode* find_max(SymNode* root){
    if(root==NULL){
        return NULL;
    }
    while(root->right!=NULL){
        root=root->right;
    }
    return root;
}

SymNode* Successor(SymNode* u){                                                 // O(h) ... 
    if(u->right!=NULL){
        return find_min(u->right);
    }
    else{
        while((u->par!=NULL && (u==u->par->right))){
            u=u->par;
        }
        return u->par;
    }
}

void Remove_leaf(SymNode* &root,SymNode* &n){
    if(n==root){
    n=NULL;
    return;
    }

    else{
        if(n->par->left==n){          
            n->par->left=NULL;
        }
        else if(n->par->right==n){
            n->par->right=NULL;                    
        }
    }
}

void Remove_leaf_balance(SymNode* &root,SymNode* n){

    if(n==NULL){
        n=NULL;
        return;
    }
    SymNode* tmp=n;

    while(is_balanced2(tmp->par)){

        if(tmp==root){
           
            return;
        }
    
        tmp=tmp->par;
        if(tmp==root){
            
            return;
        }
    }           // tmp->par will be unbalnced....

    // Case_T1


    if(tmp->par->key>tmp->key){   // leaf removed from the left sub_tree..

        SymNode* u=tmp->par;
        SymNode* v=tmp->par->right;
        SymNode* w=tmp->par->right->left;
        SymNode* t1=tmp->par->left;
        SymNode* t4=tmp->par->right->right;

        // Case_1 [h(w)=h(T4)=(h-2)]

        if(height2(w)==height2(t4)){
                              
                v->par=u->par;
                if(u!=root){
                if(u->par->left==u){
                    u->par->left=v;
                }
                else if(u->par->right==u){
                    u->par->right=v;
                }}
                if(u==root){
                root=v;
                }
                u->par=v;
                u->right=w;

                if(w!=NULL){
                w->par=u;}

                v->left=u;                                          // How do I free the allocated memory....

                delete tmp;
                // The entire tree is balanced now....
        }

        // Case_2 : [h(w)=h-3 && h(t4)=h-2]

        if(height2(w)<height2(t4)){
               
            v->par=u->par;
            if(u!=root){
            if(u->par->left==u){
                u->par->left=v;
            }
            else if(u->par->right==u){
                u->par->right=v;
            }}

             if(u==root){
                root=v;
            }
            u->par=v;
            u->right=w;

            if(w!=NULL){
            w->par=u;}

            v->left=u;
            delete tmp;

            Remove_leaf_balance(root,v);    // Further par checking.....
       }
        
       // Case_3 : [h(w)=h-2 && h(t4)=h-3]

       if(height2(w)>height2(t4)){
       
        w->par=u->par;
        if(u!=root){
        if(u->par->left==u){
            
            w->par->left=w;
        }

        else if(u->par->right==u){
            w->par->right=w;
        }}

        if(u==root){
            root=w;
        }

        SymNode* t2=w->left;
        SymNode* t3=w->right;
      
        w->left=u;
        w->right=v;

        u->par=w;
        v->par=w;
    
        if(t2!=NULL){
        t2->par=u;}

        if(t3!=NULL){
        t3->par=v;}

        u->right=t2;
        v->left=t3;

        delete tmp;

        Remove_leaf_balance(root,w);        // check for the pars.....

       }

    }
    
    // Case_T2:

    if(tmp->par->key<n->key){   // leaf removed from the right sub_tree..
   
        SymNode* u=tmp->par;
        SymNode* v=tmp->par->left;
        SymNode* w=tmp->par->left->right;
        SymNode* t1=tmp->par->right;
        SymNode* t4=tmp->par->left->left;

        // Case_1 [h(w)=h(T4)=(h-2)]

        if(height2(w)==height2(t4)){
                
              
                v->par=u->par;
                if(u!=root){
                if(u->par->left==u){
                    u->par->left=v;
                }
                else if(u->par->right==u){
                    u->par->right=v;
                }}
                if(u==root){
                    root=v;
                }
                u->par=v;
                u->left=w;

                if(w!=NULL){
                w->par=u;}

                v->right=u;

                delete tmp;
                // The entire tree is balanced now....
        }

        // Case_2 : [h(w)=h-3 && h(t4)=h-2]

        if(height2(w)<height2(t4)){
              
            v->par=u->par;
            if(u!=root){
            if(u->par->left==u){
                u->par->left=v;
            }
            else if(u->par->right==u){
                u->par->right=v;
            }}
            if(u==root){
                    root=v;
            }
            u->par=v;
            u->left=w;

            if(w!=NULL){
            w->par=u;}

            v->right=u;

            Remove_leaf_balance(root,v);    // Further par checking.....

       }
        
       // Case_3 : [h(w)=h-2 && h(t4)=h-3]

       if(height2(w)>height2(t4)){
       
        w->par=u->par;
        if(u!=root){
        if(u->par->left==u){
            
            w->par->left=w;
        }

        else if(u->par->right==u){
            w->par->right=w;
        }}
        if(u==root){
            root=w;
        }

        SymNode* t2=w->right;
        SymNode* t3=w->left;
      
        w->right=u;
        w->left=v;

        u->par=w;
        v->par=w;
    
        if(t2!=NULL){
        t2->par=u;}

        if(t3!=NULL){
        t3->par=v;}

        u->left=t2;
        v->right=t3;

        delete tmp;

        Remove_leaf_balance(root,w);        // check for the pars.....

       }
    }

}

void Remove_it(SymNode* &root,SymNode* &n){

   
    if(n->left==NULL && n->right==NULL){     // No child.
        Remove_leaf(root,n);
        Remove_leaf_balance(root,n);
    }

    else if(n->left==NULL){                 // Single child.

        n->key=n->right->key;
        n->address=n->right->address;
        Remove_it(root,n->right);      //  ------> CHECK THESE.......... <-----

    }

    else if(n->right==NULL){                 // Single child.

        n->key=n->left->key;
        n->address=n->left->address;
        Remove_it(root,n->left);

    }

    else{                                    // Dual child.

    SymNode* copy= Successor(n);
    n->key=copy->key;
    n->address=copy->address;
    Remove_it(root,copy);

    }

}

SymbolTable::SymbolTable(){

    size=0;
    root=NULL;

}

void SymbolTable::insert(string k){
    
    SymNode* n=new SymNode(k);           // Dynamically alloted memory should be freed when done with it...
    insert_raw(root,n);
    balance(root,n);
    size++;
    return;

}

void SymbolTable::remove(string k){

    SymNode* to_remove=find(root,k);
    if(to_remove==NULL){
        return;
    }
    Remove_it(root,to_remove);
    size--;
    //delete to_remove;
    
}

int SymbolTable::search(string k){

    if(find(root,k)==NULL){
        return -2;
    }

    return find(root,k)->address;
}

void SymbolTable::assign_address(string k,int idx){

    find(root,k)->address=idx;
    return;
}

int SymbolTable::get_size(){

    return size;
}

SymNode* SymbolTable::get_root(){

        return root;
}

SymbolTable::~SymbolTable(){

    delete root;                                            // Once confirm!!!!
}


