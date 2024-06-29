/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your expression below this line

SymNode* find2(SymNode* root,string k){

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

bool isval(string s){
    bool ans=true;
    for(int i=0;i<s.size();i++){
        if(!(s[i]>='0' && s[i]<='9')){
            ans=false;
            break;
        }
    }
return ans;
}


Parser::Parser(){

 symtable=new SymbolTable();

}

// Should parse the expression and 
// push the root to the exp_trees
// Also make necessary changes to the symtable

void Parser::parse(vector<string> expression){
    

    ExprTreeNode* root=new ExprTreeNode();
    ExprTreeNode* curr=root;
    vector<ExprTreeNode*>parents;
   
    expression.push_back(")");                                   // Completing the parenthesis......
    expression.insert(expression.begin(),"(");

    for(int i=0;i<expression.size();i++){ 

        if(expression[i]=="("){

            ExprTreeNode* left_child =new ExprTreeNode();
            curr->left=left_child;
            parents.push_back(curr);
            curr=curr->left;

        }

        else if(expression[i]=="+" || expression[i]=="-" || expression[i]=="/" || expression[i]=="*" || expression[i]==":="){
        // “ADD,” “SUB,” “MUL,” “DIV,” “VAL,” or “VAR”  
     
            if(expression[i]=="+"){
                curr->type="ADD";
            }
            if(expression[i]=="-"){
                curr->type="SUB";
            }
            if(expression[i]=="*"){
                curr->type="MUL";
            }
            if(expression[i]=="/"){
                curr->type="DIV";
            }


            if(expression[i]==":="){             // Garbage
                curr->type="UP";
            }

            ExprTreeNode* right_child =new ExprTreeNode();
            curr->right=right_child;
            parents.push_back(curr);
            curr=curr->right;
        }

        else if(expression[i]==")"){

            curr=parents[parents.size()-1];
            parents.pop_back();

        }

        else{

            if(expression[i]=="del"){
               
                curr->type="DEL";
                curr->num=0;                    // Garbage
                curr->id="del";                    // Garbage                
            }
            else if (expression[i]=="ret"){
                curr->type="RET";
                curr->num=0;                    // Garbage
                curr->id="ret";                    // Garbage                
            }
            else if(isval(expression[i])){
                curr->type="VAL";
                curr->id="";                            // garbage value...
                curr->num=stoi(expression[i]);
            }   
            else{
                curr->type="VAR";             
                curr->id=expression[i];
                curr->num=0;                            // garbage value...
            }

            curr=parents[parents.size()-1];
            parents.pop_back();
        }
    }

    expr_trees.push_back(root);

   // cout<<"NO"<<endl;

        //  Parse tree built...............
        // Changes in Symtable......

        ExprTreeNode* root_curr=expr_trees.back(); 
              
        if(root_curr->left->type=="DEL"){                          // DELETE
            symtable->remove(root_curr->right->id);
        }
        
        if(root_curr->left->type=="VAR"){                           /// Variable asignment
            if(find2(symtable->get_root(),root_curr->left->id)==NULL){   
                    symtable->insert(root_curr->left->id);                // If variable ia already present in the symtable then don't do anything...                   
            }
        }
}

Parser::~Parser(){
    delete symtable;
    expr_trees.clear(); 
}