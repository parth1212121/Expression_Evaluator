/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
#include<iostream>
using namespace std;

//Write your code below this line


int height(SymNode* n){
    
    if(n==NULL){
        return -1;
    }
 
    return (max(height(n->left),height(n->right))+1);
    

}

bool is_balanced(SymNode* n){
    if(n==NULL){
        return true;
    }
    else{
        if(abs(height(n->left)-height(n->right))<=1){
            return true;
        }
        return false;
    }
}



SymNode::SymNode(){

    key="";
    height=0;
    address=-1;
    par=NULL;
    left=NULL;
    right=NULL;


}

SymNode::SymNode(string k){


    key=k;
    height=0;
    address=-1;
    par=NULL;
    left=NULL;
    right=NULL;


}

SymNode* SymNode::LeftLeftRotation(){


        SymNode* tmp=this;
        
        SymNode* a=tmp;
        SymNode* b=tmp->par;
                                              // All connections.....

        a->par=a->par->par;
        if((b->par!=NULL)){
        if(b->par->left==b){
        b->par->left=a;}
        else if(b->par->right==b){
            b->par->right=a;
        }
        }
       
        
        SymNode* t2=a->right;

        a->right=b;        
        b->par=a;
       
        
        b->left=t2; 
   
        if(!(t2==NULL)){                         // Important!!!!
        t2->par=b;}

         if(b->par==NULL){                         // Special case......
            b=a;
        }

        SymNode* move_up=a;
        while(move_up->par!=NULL){
            move_up=move_up->par;
        }

        return move_up;                     // Returning the new root......

}

SymNode* SymNode::RightRightRotation(){


            SymNode* tmp=this;

            SymNode* a=tmp;
            SymNode* b=tmp->par;

            a->par=a->par->par;
            if(b->par!=NULL){
            if(b->par->left==b){
            b->par->left=a;}
            else if(b->par->right==b){
                b->par->right=a;
            }
            }

         
            SymNode* t1=a->left;

            a->left=b;
            b->par=a;

            b->right=t1;
            if(t1!=NULL){
                t1->par=b;
            }

            if(b->par==NULL){
                b=a;
            }


            SymNode* move_up=a;
            while(move_up->par!=NULL){
                move_up=move_up->par;
            }

            return move_up;                     // Returning the new root......

}

SymNode* SymNode::LeftRightRotation(){

            SymNode* tmp=this;

            SymNode* a=tmp;
            SymNode* b= tmp->par;
            SymNode* d=tmp->right;
       

            d->par=b->par;
            
            if(b->par!=NULL){
            if(b->par->left==b){
                d->par->left=d;
            }
            else if(b->par->right==b){
                d->par->right=d;
            }}
           

            a->par=d;

            SymNode* t2a=d->left;
            SymNode* t2b=d->right;

            d->left=a;

            a->right=t2a;

            if(t2a!=NULL){
            t2a->par=a;}
            
            b->par=d;
            d->right=b;
            b->left=t2b;

            if(t2b!=NULL){
            t2b->par=b;}

            if(b->par==NULL){
                b=d;
            }


            SymNode* move_up=a;
            while(move_up->par!=NULL){
                move_up=move_up->par;
            }

            return move_up;                     // Returning the new root......
}

SymNode* SymNode::RightLeftRotation(){


            SymNode* tmp=this;

            SymNode* a=tmp;
            SymNode* b= tmp->par;
            SymNode* d=tmp->left;
       
            d->par=b->par;
            if(b->par!=NULL){
            if(b->par->left==b){
                d->par->left=d;
            }
            else if(b->par->right==b){

                d->par->right=d;
            }}


            a->par=d;

            SymNode* t2a=d->left;
            SymNode* t2b=d->right;

            d->left=b;

            b->right=t2a;

            if(t2a!=NULL){
            t2a->par=b;}
            
            b->par=d;
            d->right=a;
            a->left=t2b;

            if(t2b!=NULL){
            t2b->par=a;}  

            if(b->par==NULL){
                b=d;
            }  

            SymNode* move_up=a;
            while(move_up->par!=NULL){
                move_up=move_up->par;
            }

            return move_up;                     // Returning the new root......

}

SymNode::~SymNode(){

    delete par;                                                                         // Once confirm!!!
    delete left;
    delete right;

}