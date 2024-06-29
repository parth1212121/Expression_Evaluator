/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */

#include "eppcompiler.h"

//Write your code below this line
//Write your code below this line


vector<string> generate(vector<string>&commands,ExprTreeNode* root,SymbolTable* S,MinHeap &least_mem_loc){


if(root==NULL){
    return commands;
}

else if(root->left==NULL){

            if(root->type=="VAL"){                
                commands.push_back("PUSH " + to_string(root->num));    
                return commands;
            }
            else if(root->type=="VAR"){               
                commands.push_back("PUSH mem[" + to_string(S->search(root->id)) + "]");  
                return commands;                  
            }

}

else{
    
    generate(commands,root->right,S,least_mem_loc);
    generate(commands,root->left,S,least_mem_loc);

    if(root->type=="ADD"){
        commands.push_back("ADD");
    }
    else if(root->type=="SUB"){
        commands.push_back("SUB");
    }
    else if(root->type=="MUL"){
        commands.push_back("MUL");
    }
    else if(root->type=="DIV"){
        commands.push_back("DIV");
    }

    return commands;
}

}

vector<string> generate2(vector<string>&commands,ExprTreeNode* root,SymbolTable* S,MinHeap &least_mem_loc){
    
    if(root==NULL){
        return commands;
    }    

    else{
    if(root->left->type=="DEL"){
        commands.push_back("DEL = mem[" + to_string(S->search(root->right->id))+ "]");
        return commands;
    }
    else if(root->left->type=="RET"){

  
        generate(commands,root->right,S,least_mem_loc);
        commands.push_back("RET = POP");
        return commands;        
    }

    else{
       
        generate(commands,root->right,S,least_mem_loc);

        if(S->search(root->left->id)==-1 || S->search(root->left->id)==-2){
        commands.push_back("mem["+to_string(least_mem_loc.get_min())+"] = POP");
        }
        else{
            commands.push_back("mem["+to_string(S->search(root->left->id))+"] = POP");
        }
        return commands;   
    }

}}


EPPCompiler::EPPCompiler(){

    memory_size=10;
    output_file="";
    for(int i=0;i<memory_size;i++){
        least_mem_loc.push_heap(i);
    }

}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){

    memory_size=mem_limit;
    output_file=out_file;
    for(int i=0;i<memory_size;i++){
    least_mem_loc.push_heap(i);
    }
    

}

void EPPCompiler::compile(vector<vector<string>> code){


        for(int i=0;i<code.size();i++){

            vector<string>expression=code[i];

            if(expression[0]=="ret"){

                targ.parse(expression);                                             // Parsing...
                vector<string>compiled_line;                                        // Compilation...
                compiled_line=generate_targ_commands();
                write_to_file(compiled_line);

                break;                        // Execution of the program stop.. Semantics will ensure this....

            }


            if(expression[0]=="del"){  


                least_mem_loc.push_heap(targ.symtable->search(expression[2]));  // Memory changes
              
                int prior_address=targ.symtable->search(expression[2]);

                targ.parse(expression);                                   // Parsing

              
                vector<string>compiled_line;                              // Compilation...                
                compiled_line.push_back("DEL = mem["+ to_string(prior_address)+ "]");
                write_to_file(compiled_line);               


            }

            

            else{                                               // VARIABLE ASSIGNMENT

                    targ.parse(expression);                                      // Parsing


                    vector<string>compiled_line;                                 // Compilation...
                    compiled_line=generate_targ_commands();
                    write_to_file(compiled_line);

                    if(targ.symtable->search(expression[0])==-1 || targ.symtable->search(expression[0])==-2){              // Memory changes

                    targ.symtable->assign_address(expression[0],least_mem_loc.get_min());            
                    least_mem_loc.pop();
                    
                    }
                  

            }
        }

}

vector<string> EPPCompiler::generate_targ_commands(){

        ExprTreeNode* root= targ.expr_trees.back();
        vector<string>commands;
        vector<string>ans;
        ans=generate2(commands,targ.expr_trees.back(),targ.symtable,least_mem_loc);
        return ans;

}

void EPPCompiler:: write_to_file(vector<string> commands){

    ofstream file(output_file,std::ios::app);                  
    if(file.is_open()){
          for(int i=0;i<commands.size();i++){
            file<<commands[i]<<endl;
        }
    }
    file.close();
}


EPPCompiler::~EPPCompiler(){
    
    delete &least_mem_loc;                       //            ------>        // Confirm once !!!!!!!!!!!        <--------
    delete &targ;
    
}