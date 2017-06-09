#include<bits/stdc++.h>
#include<string.h>
#include<string>
#ifndef DAG_INCLUDED
#define DAG_INCLUDED

using namespace std;

class DAG_Node{
	string label;
	int lChild;
	int rChild;
public:
    DAG_Node(){
		lChild=0;
		rChild=0;
	}
	DAG_Node(string label, int l, int r){
		//write code here
		this->label=label;
		lChild=l;
		rChild=r;
	}
	~DAG_Node(){
		//Write Code Here
	}
};

int currIndex=1; // Current entry in dag_array will be at currIndex
DAG_Node dag_array[1000]; // Start from index 1

map<string,int> variable;

bool isVar(char x){
    if((x>='a' && x<='z') || (x>='A' && x<='Z') ||
           (x>='0' && x<='9') || x=='_' ){
        return true;
    }
    return false;
}

int constructNode(string label, int l, int r){
	// Write code to implement value number method
	// You can Declare additional global variables and functions
	// You have to do hashing instead of searching linearly in the dag_array
	// STL can be used
    string var;

    if(isVar(label[l])){

        for(l;l<=r;l++){
            if(isVar(label[l])){
            var+=label[l];
            }
            else break;
        }

        if(!variable[var]){
            //set position in DAG array
            DAG_Node newDAG((string)var,0,0);
            dag_array[currIndex]=newDAG;
            variable[var]=currIndex;
        }
        int leftPos=variable[var];
        if(l>r)return currIndex;
        else if(label[l]=='+' || label[l]=='-'){
            currIndex++;
            int rightPos=constructNode(label,l+1,r);
            DAG_Node newDAG((string)label[l],leftPos,rightPos);
            dag_array[currIndex]=newDAG;
            return currIndex;
        }
        else if(label[l]=='/' || label[l]=='*'){
            int rightPos;
            while(label[l]=='/' || label[l]=='*'){
                currIndex++;
                char op=label[l++];
                string var2;
                if(isVar(label[l])){
                    for(l;l<=r;l++){
                        if(isVar(label[l])){
                            var2+=label[l];
                        }
                        else break;
                    }

                    if(!variable[var2]){
                        //set position in DAG array
                        DAG_Node newDAG((string)var2,0,0);
                        dag_array[currIndex]=newDAG;
                        variable[var2]=currIndex++;
                    }
                    rightPos=variable[var2];
                    DAG_Node newDAG((string)op,leftPos,rightPos);
                    leftPos=currIndex;
                    dag_array[currIndex]=newDAG;
                    if(l>r)return currIndex;
                }
                else {
                    int tpos=l+1,cnt=1;
                    for(;cnt>0;tpos++){
                        if(label[tpos]=='(')cnt++;
                        if(label[tpos]==')')cnt--;
                    }
                    rightPos=constructNode(label,l+1,tpos-1);
                    l=tpos;
                    DAG_Node newDAG((string)op,leftPos,rightPos);
                    leftPos=currIndex;
                    dag_array[currIndex]=newDAG;
                    if(l>r)return currIndex;
                }

            }
            if(label[l]=='+' || label[l]=='-'){
                currIndex++;
                int rightPos=constructNode(label,l+1,r);
                DAG_Node newDAG((string)label[l],leftPos,rightPos);
                dag_array[currIndex]=newDAG;
                return currIndex;
            }
            return currIndex;
        }

    }
    else {
            int tpos=l+1,cnt=1;
            for(;cnt>0;tpos++){
                if(label[tpos]=='(')cnt++;
                if(label[tpos]==')')cnt--;
            }
            int leftPos=constructNode(label,l+1,tpos-1);
            l=tpos;
            if(l>r)return currIndex;
            if(label[l]=='+' || label[l]=='-'){
                currIndex++;
                int rightPos=constructNode(label,l+1,r);
                DAG_Node newDAG((string)label[l],leftPos,rightPos);
                dag_array[currIndex]=newDAG;
                return currIndex;
            }
            else if(label[l]=='/' || label[l]=='*'){
                int rightPos;
                while(label[l]=='/' || label[l]=='*'){
                    currIndex++;
                    char op=label[l++];
                    string var2;
                    if(isVar(label[l])){
                        for(l;l<=r;l++){
                            if(isVar(label[l])){
                                var2+=label[l];
                            }
                            else break;
                        }

                        if(!variable[var2]){
                            //set position in DAG array
                            DAG_Node newDAG((string)var2,0,0);
                            dag_array[currIndex]=newDAG;
                            variable[var2]=currIndex++;
                        }
                        rightPos=variable[var2];
                        DAG_Node newDAG((string)op,leftPos,rightPos);
                        leftPos=currIndex;
                        dag_array[currIndex]=newDAG;
                        if(l>r)return currIndex;
                    }
                    else {
                        int tpos=l+1,cnt=1;
                        for(;cnt>0;tpos++){
                            if(label[tpos]=='(')cnt++;
                            if(label[tpos]==')')cnt--;
                        }
                        rightPos=constructNode(label,l+1,tpos-1);
                        l=tpos;
                        DAG_Node newDAG((string)op,leftPos,rightPos);
                        leftPos=currIndex;
                        dag_array[currIndex]=newDAG;
                        if(l>r)return currIndex;
                    }

                }
                if(label[l]=='+' || label[l]=='-'){
                    currIndex++;
                    int rightPos=constructNode(label,l+1,r);
                    DAG_Node newDAG((string)label[l],leftPos,rightPos);
                    dag_array[currIndex]=newDAG;
                    return currIndex;
                }
                return currIndex;
            }

    }
    return currIndex;

}

void print_dag_array(){
	// write code for printing a all entries of dag_array
	// you should print exactly in the way shown in sample output
}

void construct_tac(){
	// write code to construct and print three address code generated from dag
	// you should print exactly in the way shown in sample output

}

#endif
