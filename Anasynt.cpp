#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>

using namespace std;

struct Node{
    int type;
    int valeur;
    int Nenfants;
    Node *enfants[];
};



Node *A(){
    if (check(tok_constante)){
        A = CreerNode(Nd_const,L.valeur);
        return A;
    }
    else if (check(tok_open_parenthesis)){
        A=E();
        accept(tok_close_parenthesis);
        return A;
    }
    else if (check(tok_ident){
        return CreerNode(nd_ref, L.valeur);
    })
    erreur();
}

Node *I(){
    if(check(tok_debug)){
        Node *R = E();
        accept(tok_semicolon);
        return CreerNode(nd_debug,R);
    }
    else if (check(tok_open_bracket)){
        Node *R = CreerNode (nd_bloc);
        while(!check(tok_close_bracket)){
            AjouteEnfant(R,I());
        }
        return R;
    }
    else if (check(tok_int)) {
        accept(tok_ident);
        Node *R = creerNode(nd_decl, L.valeur);
        accept(tok_comma);
        return R;
}
    else if (check(tok_if)){
        accept(tok_pronom);
        Node *E= E();
        accept(tok_closeparenthese);
        Node *I1 = I();
        if (check(tok_else)){
            Node *I2 = I();
            .....
        }
    }
    else{
        Node *R=E();
        accept(tok_comma);
        return CreerNode(nd_drop, R);
    }
}

Node *P(){
    if (check(tok_plus)){
        A=P(); return A;
    }
    else if (check(tok_moins)){
        A = P();
        return CreerNode(NdMoinsUn,A);
    }
    else {
        A = S(); return A;
    }
}

Node E (int pmin){
    Node A1 = P();
    while (T.type != tok_eof){
        op = Table[T.type];
        if (op==NULL||op.prio <pmin){
            return A1;
            }
        next();
        Node A2= E(op.prio+op.assoc);
        A1 = CreerNode(op.type,A1,A2)
    }
}


void gencode(Node *N){
    if (Table[N.type]){
        for (int i = 0; i < N->Nenfants,i++){
            gencode(N.enfants[i]);
        }
        print(Table[N.type].code);
        return;
    }
    switch (N->type)
    {
    case Nd_const:
        print("push", N->valeur);
        break;
    
    case Nd_Not:
        gencode(N.enfants[0]);
        print("not");
        break;

    case NdMoinsUn:
        print("push 0");
        gencode(N.enfants[0]);
        print("sub");
        break;
    
    default:
        break;
    }
}

void AnaSem(Node *N) {
switch(N.type) {
default:
for(int i = 0; i < N.nbenfants; i++) {
AnaSem(N.enfants[i]);
}
return;
case nd_affect:
if(N.enfants[0].type != nd_ref) {
erreurfatale("...");
}
for(int i = 0; i < N.nbenfants; i++) {
AnaSem(N.enfants[i]);
}
return;
case nd_decl:
Symb *S = declare(N.valeur);
S.type = type_int;
S.position = nvar; nvar++;
return;
case nd_ref:
Symb *S = find(N.valeur);
if(S.type != type_int) {
erreurfatale("...");
}
N.position = S.position;
return;
case nd_bloc:
begin();
for(int i = 0; i < N.nbenfants; i++) {
AnaSem(N.enfants[i]);
}
end();
return;
}
}
voi