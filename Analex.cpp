#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <stdexcept>
#include <vector>

using namespace std;
// ---------------------------  -----------------------//

enum TokenType {
    INCONNU,
    tok_debug,
    tok_eof,
    tok_ident,
    tok_constante,
    tok_op,
    tok_plus,
    tok_minus,
    tok_multiply,
    tok_divide,
    tok_modulo,
    tok_equal,
    tok_not_equal,
    tok_less_than,
    tok_greater_than,
    tok_less_equal,
    tok_greater_equal,
    tok_logical_and,
    tok_logical_or,
    tok_logical_not,
    tok_bitwise_and,
    tok_bitwise_or,
    tok_assignment,
    tok_comma,
    tok_semicolon,
    tok_open_parenthesis,
    tok_close_parenthesis,
    tok_open_brace,
    tok_close_brace,
    tok_open_bracket,
    tok_close_bracket,
    tok_percent,
    tok_if,
    tok_else,
    tok_while,
    tok_for,
    tok_return,
    tok_int,
    tok_do,
    tok_recv,
    tok_break,
    tok_continue,
    tok_send
};

enum NodeType {
    nd_const,
    nd_ref,
    nd_decl,
    nd_debug,
    nd_bloc,
    nd_drop,
    nd_loop,
    nd_add,
    nd_sub,
    nd_mul,
    nd_div,
    nd_mod,
    nd_eq,
    nd_neq,
    nd_lt,
    nd_gt,
    nd_le,
    nd_ge,
    nd_and,
    nd_or,
    nd_not,
    nd_band,
    nd_bor,
    nd_assign,
    nd_comma,
    nd_semi,
    nd_open_parenthesis,
    nd_close_parenthesis,
    nd_open_brace,
    nd_close_brace,
    nd_open_bracket,
    nd_close_bracket,
    nd_percent,
    nd_if,
    nd_else,
    nd_while,
    nd_for,
    nd_return,
    nd_int,
    nd_do,
    nd_recv,
    nd_break,
    nd_continue,
    nd_send,
    nd_cond,   // Added nd_cond
    nd_vide,   // Added nd_vide
    nd_affect, // Added nd_affect
    nd_appel,  // Added nd_appel
    nd_NdMoinsUn,
    nd_fonc, // Added nd_fonc
    nd_eof,   // Added nd_eof
    nd_adr,   // Added nd_adr
    nd_ind,    // Added nd_ind
    nd_ancre,   // Added nd_ancre
    nd_indirect, // Added nd_indirect
    nd_seq,      // Added nd_seq
    nd_ret       // Added nd_ret
};

std::map<NodeType, std::string> Tables = {
    {nd_const, "nd_const"},
    {nd_ref, "nd_ref"},
    {nd_decl, "nd_decl"},
    {nd_debug, "nd_debug"},
    {nd_bloc, "nd_bloc"},
    {nd_drop, "nd_drop"},
    {nd_loop, "nd_loop"},
    {nd_add, "nd_add"},
    {nd_sub, "nd_sub"},
    {nd_mul, "nd_mul"},
    {nd_div, "nd_div"},
    {nd_mod, "nd_mod"},
    {nd_eq, "nd_eq"},
    {nd_neq, "nd_neq"},
    {nd_lt, "nd_lt"},
    {nd_gt, "nd_gt"},
    {nd_le, "nd_le"},
    {nd_ge, "nd_ge"},
    {nd_and, "nd_and"},
    {nd_or, "nd_or"},
    {nd_not, "nd_not"},
    {nd_band, "nd_band"},
    {nd_bor, "nd_bor"},
    {nd_assign, "nd_assign"},
    {nd_comma, "nd_comma"},
    {nd_semi, "nd_semi"},
    {nd_open_parenthesis, "nd_open_parenthesis"},
    {nd_close_parenthesis, "nd_close_parenthesis"},
    {nd_open_brace, "nd_open_brace"},
    {nd_close_brace, "nd_close_brace"},
    {nd_open_bracket, "nd_open_bracket"},
    {nd_close_bracket, "nd_close_bracket"},
    {nd_percent, "nd_percent"},
    {nd_if, "nd_if"},
    {nd_else, "nd_else"},
    {nd_while, "nd_while"},
    {nd_for, "nd_for"},
    {nd_return, "nd_return"},
    {nd_int, "nd_int"},
    {nd_do, "nd_do"},
    {nd_recv, "nd_recv"},
    {nd_break, "nd_break"},
    {nd_continue, "nd_continue"},
    {nd_fonc, "nd_fonc"}, // Added nd_fonc to the map,
}; 

std::string lireFichier(const std::string& cheminFichier) {
    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier." << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << fichier.rdbuf();  

    return buffer.str(); 
}
struct Token {
    TokenType type;
    int ligne;
    std::string valeur;
};

map <string, TokenType > keywords = {
    {"if", TokenType::tok_if},
    {"else", TokenType::tok_else},
    {"while", TokenType::tok_while},
    {"return", TokenType::tok_return},
    {"int", TokenType::tok_int},
    {"do", TokenType::tok_do},
    {"debug", TokenType::tok_debug},
    {"for", TokenType::tok_for},
    {"do", TokenType::tok_do},
    {"break", TokenType::tok_break},
    {"continue", TokenType::tok_continue},
    {"recv", TokenType::tok_recv},
    {"send", TokenType::tok_send},
};

Token T, L;
string code = "";
size_t ligne = 1 , position = 0;

void next(){

    if(T.type != TokenType::tok_eof && T.type != TokenType::INCONNU){
        L = T;
        position ++;
    }

    char temp = code[position];
        string s;
        while(isspace(temp)){
            position++;
            temp = code[position];
        }

        if ( temp == '+'){
            T.type =TokenType::tok_plus;
            s = string(1, temp);
        }else if (temp == '-'){
            T.type = TokenType::tok_minus;
            s = string(1, temp);
        }else if (temp == '*'){
            T.type = TokenType::tok_multiply;
            s = string(1, temp);
        }else if (temp == '/'){
            T.type = TokenType::tok_divide;
            s = string(1, temp);
        }else if (temp == '%'){
            T.type = TokenType::tok_modulo;
            s = string(1, temp);
        }else if (temp == '='){
            if (code[position+1] == '='){
                T.type = TokenType::tok_equal;
                s = temp + "=";
                position = position + 1;
            }else{
                T.type = TokenType::tok_assignment;
                s = string(1, temp);
            }
        }else if (temp == '!'){
            if (code[position+1] == '=')
            {
                T.type = TokenType :: tok_not_equal;
                s = temp + "=";
            }else{
                T.type = TokenType::tok_logical_not;
                s = string(1, temp);
            }
        }else if (temp == '<'){
            if (code[position+1] == '=')
            {
                T.type = TokenType :: tok_less_equal;
                s = temp + "=";
            }else{
                T.type = TokenType::tok_less_than;
                s = string(1, temp);
            }
        }else if (temp == '>'){
            if(code[position+1] == '='){
                T.type = TokenType :: tok_greater_equal;
                s = temp + "=";
            }else{
                T.type = TokenType::tok_greater_than;
                s = string(1, temp);
            }
        }else if (temp == '&'){
            if (code[position+1] == '&'){
                T.type = TokenType :: tok_logical_and;
                s = temp + "&";
            }else{
                T.type = TokenType::tok_bitwise_and;
                s = string(1, temp);
            }
        }else if (temp == '|'){
            if (code[position+1] == '|'){
                T.type = TokenType :: tok_logical_or;
                s = temp + "|";
            }else{
                T.type = TokenType::tok_bitwise_or;
                s = string(1, temp);
            }
        }else if (temp == ','){
            T.type = TokenType::tok_comma;
            s = string(1, temp);
        }else if (temp == ';'){
            T.type = TokenType::tok_semicolon;
            s = string(1, temp);
        }else if (temp == '('){
            T.type =TokenType::tok_open_parenthesis;
            s = string(1, temp);
        }else if (temp == ')'){
            T.type =TokenType::tok_close_parenthesis;
            s = string(1, temp);
        }else if (temp == '{'){
            T.type = TokenType::tok_open_brace;
            s = string(1, temp);
        }else if (temp == '}'){
            T.type = TokenType::tok_close_brace;
            s = string(1, temp);
        }else if (temp == '['){
            T.type = TokenType::tok_open_bracket;
            s = string(1, temp);
        }else if (temp == ']'){
            T.type = TokenType::tok_close_bracket;
            s = string(1, temp);
        }
        else if (isdigit(temp)){
            while(position < code.length() && isdigit(code[position])){
                s = s + code[position];
                position++;
            }

            T.type = TokenType::tok_constante;
        }else if(temp == '\0'){
            T.type = TokenType::tok_eof;
            s = "\0";
        }else {
            string text;
            while ((position < code.length()) && isalnum(code[position]))
            {
                text += code[position];
                position ++;
            }
            s = text;

            if(isalnum(code[position]) == false){
                position --;
            }

            /*Verification si c'est un mot clés connu*/
            bool patch = false;
            for (const auto& entry : keywords) {
                if(text == entry.first){
                    T.type = entry.second;
                    patch = true;
                }
            }
            
            /*Cest un identifiant*/
            if(patch == false ){
                T.type = TokenType::tok_ident;
            }  
        }
        T.valeur = s;
}

bool check (TokenType type){
    if(T.type != type){
        return false;
    }
    else{
        next();
        return true;
    }

}

void reinitialiser() {
    position = 0;
    next(); // Initialise le premier token à T
}

void accept(TokenType type){
    if(check(type) == false){
        throw std::runtime_error("Error Fatal : trouve "+ T.valeur);
    }
}

struct Node {
    NodeType type;          
    string valeur;        
    int nEnfants;
    int position;
    int nbVar;
    std::vector<Node*> enfants; // Vecteur dynamique pour les enfants du noeud
};

// Fonction pour créer un Node avec seulement le type
Node* creerNode(NodeType type) {
    Node* nouveauNode = new Node;
    nouveauNode->type = type;
    nouveauNode->valeur = "";
    nouveauNode->nEnfants = 0;
    return nouveauNode;
}

// Function to create a Node with four child nodes
Node* creerNode(NodeType type, Node* enfant1, Node* enfant2, Node* enfant3) {
    Node* nouveauNode = new Node;
    nouveauNode->type = type;
    nouveauNode->valeur = "";
    nouveauNode->nEnfants = 3;
    nouveauNode->enfants.push_back(enfant1);
    nouveauNode->enfants.push_back(enfant2);
    nouveauNode->enfants.push_back(enfant3);
    return nouveauNode;
}

// Fonction pour créer un Node avec type et valeur
Node* creerNode(NodeType type, string valeur) {
    Node* nouveauNode = new Node;
    nouveauNode->type = type;
    nouveauNode->valeur = valeur;
    nouveauNode->nEnfants = 0;
    return nouveauNode;
}

//fonction pour créer un Node avec un Node enfant
Node* creerNode(NodeType type, Node* enfant) {
    Node* nouveauNode = new Node;
    nouveauNode->type = type;
    nouveauNode->valeur = "";
    nouveauNode->nEnfants = 1;
    nouveauNode->enfants.push_back(enfant);
    return nouveauNode;
}

Node* creerNode(NodeType type, Node* enfant1, Node* enfant2) {
    Node* nouveauNode = new Node;
    nouveauNode->type = type;
    nouveauNode->valeur = "";
    nouveauNode->nEnfants = 2;
    nouveauNode->enfants.push_back(enfant1);
    nouveauNode->enfants.push_back(enfant2);
    return nouveauNode;
}


// Fonction pour ajouter un enfant à un Node
void ajouterEnfant(Node* parent, Node* enfant) {
    parent->enfants.push_back(enfant);
    parent->nEnfants = parent->enfants.size();
}

// Fonction pour afficher les informations d'un noeud et de ses enfants
void afficherNode(const Node* node, int niveau = 0) {
    std::string indent(niveau * 2, ' ');  // Indentation pour affichage
    std::cout << indent << "Node type: " << node->type << ", valeur: " << node->valeur << ", nombre d'enfants: " << node->nEnfants << std::endl;

    // Afficher les enfants
    for (const Node* enfant : node->enfants) {
        afficherNode(enfant, niveau + 1);
    }
}

struct Operateur {
    TokenType type_; 
    int prio;             
    int assoc;             
    NodeType type_N;   
};

std::vector<Operateur> operateurs = {
    {tok_assignment, 1, 1, nd_assign},
     {tok_logical_or, 2, 0, nd_or},
     {tok_logical_and, 3, 0, nd_and},
     {tok_equal, 4, 0, nd_eq},
     {tok_not_equal, 4, 0, nd_neq},
    {tok_less_than, 5, 0, nd_lt},
    {tok_greater_than, 5, 0, nd_gt},
     {tok_less_equal, 5, 0, nd_le},
     {tok_greater_equal, 5, 0, nd_ge},
    {tok_plus, 6, 0, nd_add},
    {tok_minus, 6, 0, nd_sub},
    {tok_multiply, 7, 0, nd_mul},
    {tok_divide, 7, 0, nd_div},
    {tok_modulo, 7, 0, nd_mod},
    {tok_logical_not, 8, 1, nd_not},
};

// Forward declarations to ensure each function is known before use.
Node* A();
Node* S();
Node* P();
Node* E(int pmin);
Node* E();
Node* I();
Node* F();

Node *E(int pmin) {
    std::cout << "E(" << pmin << ")" << std::endl;
    std::cout << "T.type : " << T.type << ", T.valeur : " << T.valeur << std::endl;
    Node *A1 = P();
    while (T.type != tok_eof) {
        const Operateur *op = nullptr;
        for (const auto& op_ : operateurs) {
            if (op_.type_ == T.type) {
                op = &op_;
                break;
            }
        }
        if (op == nullptr || op->prio < pmin) {
            return A1;
        }
        next();
        Node *A2 = E(op->prio + op->assoc);
        A1 = creerNode(op->type_N, A1, A2);
    }
    std::cout << "T.type : " << T.type << ", T.valeur : " << T.valeur << std::endl;
    return A1;
}

Node *E() {
    return E(0);
}

Node *A() {
    std::cout << "A()" << std::endl;   
    if (check(TokenType::tok_constante)) {
        Node *A = creerNode(NodeType::nd_const, L.valeur);
        return A;
    }
    else if (check(TokenType::tok_open_parenthesis)) {
        Node *A = E(0);
        accept(TokenType::tok_close_parenthesis);
        return A;
    }
    else if (check(TokenType::tok_ident)) {
        return creerNode(nd_ref, L.valeur);
    }
    else if (check(tok_eof)) {
        return creerNode(nd_eof);
    }
    else if (T.type == tok_semicolon) {
        return creerNode(nd_vide);
    }
    else {
        throw std::runtime_error("Erreur : trouvé " + T.valeur);
    }
}

Node *S() {
    std::cout << "S()" << std::endl;
    Node *N = A();
    if (check(tok_open_parenthesis)) {
        N = creerNode(nd_appel, N);
        while (!check(tok_close_parenthesis)) {
            ajouterEnfant(N, E(0));
            if (check(tok_close_parenthesis)) {
                break;
            } else {
                accept(tok_comma);
            }
        }
        return N;
    } else if (check(tok_open_bracket)) {
        std::cout << "T.type : " << T.type << ", T.valeur : " << T.valeur << std::endl;
        Node *e = E(0);
        accept(tok_close_bracket);
        Node *I = creerNode(nd_indirect, e);
        return I;
    }
    return N;
}

Node *P() {
    std::cout << "P()" << std::endl;
    Node *A;
    std::cout << "T.type : " << T.type << ", T.valeur : " << T.valeur << std::endl;
    if (check(tok_plus)) {
        A = P(); 
        return A;
    }
    else if (check(tok_minus)) {
        A = P();
        return creerNode(nd_NdMoinsUn, A);
    } else if (check(tok_logical_not)) {
        A = P();
        return creerNode(nd_not, A);
    } else if (check(tok_bitwise_and)) {
        A = P();
        return creerNode(nd_band, A);
    } else if (check(tok_multiply)) {
        A = P();
        return creerNode(nd_mul, A);
    } else {
        A = S();
        return A;
    }
}

Node *I() {
    std::cout << "I()" << std::endl;
    if (check(tok_debug)) {
        Node *R = E();
        accept(tok_semicolon);
        return creerNode(nd_debug, R);
    }
    else if (check(tok_open_brace)) {
        Node *R = creerNode(nd_bloc);
        while (!check(tok_close_brace)) {
            ajouterEnfant(R, I());
        }
        return R;
    }
    else if (check(tok_int)) {
        accept(tok_ident);
        Node *R = creerNode(nd_decl, L.valeur);
        accept(tok_semicolon);
        return R;
    }
    else if (check(tok_if)) {
        accept(tok_open_parenthesis);
        Node *expr = E();
        accept(tok_close_parenthesis);
        Node *I1 = I();
        Node *R = creerNode(nd_cond, expr, I1);

        if (check(tok_else)) {
            Node *I2 = I();
            ajouterEnfant(R, I2);
        }
        return R;
    } else if (check(tok_while)) {
        accept(tok_open_parenthesis);
        Node *expr = E();
        accept(tok_close_parenthesis);
        Node *I1 = I();
        Node *brek = creerNode(nd_break);
        Node *R = creerNode(nd_cond, expr, I1, brek);
        Node *ancre = creerNode(nd_ancre);
        Node *loop = creerNode(nd_loop, ancre, R);

        return loop;
    } else if (check(tok_for)) {
        accept(tok_open_parenthesis);
        Node *A1 = E();
        accept(tok_semicolon);
        Node *A2 = E();
        accept(tok_semicolon);
        Node *A3 = E();
        accept(tok_close_parenthesis);
        Node *I1 = I();
        Node *brek = creerNode(nd_break);
        Node *R = creerNode(nd_cond, A2, I1, brek);
        Node *ancre = creerNode(nd_ancre);
        Node *loop = creerNode(nd_loop, ancre, R, A3);
        return creerNode(nd_bloc, A1, loop);
    } else if (check(tok_do)) {
        Node *I1 = I();
        accept(tok_while);
        accept(tok_open_parenthesis);
        Node *expr = E();
        accept(tok_close_parenthesis);
        accept(tok_semicolon);
        Node *notexpr = creerNode(nd_not, expr);
        Node *brek = creerNode(nd_break);
        Node *R = creerNode(nd_cond, notexpr, I1, brek);
        Node *ancre = creerNode(nd_ancre);
        Node *loop = creerNode(nd_loop, ancre, R);
        return loop;
    }
    else if (check(tok_return)) {
        Node *R = E();
        accept(tok_semicolon);
        return creerNode(nd_return, R);
    }
    else if (check(tok_break)) {
        accept(tok_semicolon);
        return creerNode(nd_break);
    }
    else if (check(tok_continue)) {
        accept(tok_semicolon);
        return creerNode(nd_continue);
    }
    else if (check(tok_send)) {
        Node *R = E();
        accept(tok_semicolon);
        return creerNode(nd_send, R);
    }
    else if (check(tok_recv)) {
        Node *R = E();
        accept(tok_semicolon);
        return creerNode(nd_recv, R);
    }
    else {
        Node *R = E();
        accept(tok_semicolon);
        return creerNode(nd_drop, R);
    }
}

Node *F() {
    std::cout << "F()" << std::endl;
    accept(tok_int);
    accept(tok_ident);
    Node *R = creerNode(nd_fonc, L.valeur);
    accept(tok_open_parenthesis);
    while (check(tok_int)) {
        accept(tok_ident);
        ajouterEnfant(R, creerNode(nd_decl, L.valeur));
        if (check(tok_comma)) {
            continue;
        } else {
            break;
        }
    }
    accept(tok_close_parenthesis);
    Node* i = I();
    ajouterEnfant(R, i);
    return R;
}

void erreurfatale(const std::string& message) {
    throw std::runtime_error(message);
}

Node* analyseursynthax(){
    return F();
}


struct Symbol {
    std::string nom;
    std::string type_;
    int position;
    int nbVar;

    // Constructeur
    Symbol(const std::string& nom) : nom(nom), type_(""), position(0), nbVar(0) {}
};

std::vector<Symbol> Vars;
int nbVar = 0;

Symbol* declare(const std::string& nom) {
    for (size_t i = Vars.size() - 1; i >= 0; --i) {
        if (Vars[i].nom == nom) {
            throw std::runtime_error("Declaration dupliquee de la variable : " + nom);
        } else if (Vars[i].nom == "---") {
            break;
        }
    }

    Vars.push_back(Symbol(nom));
    return &Vars.back();  
}


Symbol* chercher(const std::string& nom) {
    for (size_t i = Vars.size() - 1; i >= 0; --i) {
        if (Vars[i].nom == nom) {
            return &Vars[i];
        }
    }
    throw std::runtime_error("Variable non trouvée : " + nom);
}

void begin() {
    Vars.push_back(Symbol("---"));  
}

void end() {
    while (!Vars.empty() && Vars.back().nom != "---") {
        Vars.pop_back();  
    }
    if (!Vars.empty()) {
        Vars.pop_back();  
    }
}


Node* Optim( Node* A) {
	for(int i = 0; i < A -> nEnfants; i++) {
		A -> enfants[i] = Optim(A-> enfants[i]);
	}
	switch (A -> type){
		case nd_add:
			if (A -> enfants[0]->type == nd_const && A-> enfants[1]->type == nd_const){
				return creerNode(nd_const, A -> enfants[0]->valeur + A -> enfants[1]->valeur);
			}
			return A;
            break;
        default:
        return A;
            break;
	}
}

void analex( string fname){
  // Lire le fichier et attribuer le code dans la variable code -------------
    code = lireFichier(fname);


    while (T.type != TokenType::tok_eof)
    {
        next();
        cout << " le type : " << T.type << ", Valeur : " << T.valeur << ", Ligne : " << T.ligne << std::endl;
    }
    
}

int nblabel = 0;
int label_boucle = 0;

void gencode(Node *N){

    if(Tables.find(N->type) != Tables.end()){
        for (auto i = 0; i < N->nEnfants; i++){
            gencode(N->enfants[i]);
        }
        std :: cout << Tables[N->type] << std::endl;
        return ;
    }

    switch (N->type){
    default:
        cerr << "Erreur : Nœud de type inconnu (" << N->type << ")" << endl;
        exit(1);
        break;
    case nd_const:
        /* code */
        std :: cout << "push " << N -> valeur << std::endl;
        break;
    case nd_add:
        /* code */
        std :: cout << "add" << std::endl;
        break;
    case nd_not:
        /* code */
        gencode(N->enfants[0]);
        std :: cout << "not" << std::endl;
        break;
    case nd_NdMoinsUn:
        std :: cout << "push 0" << std::endl;
        gencode(N->enfants[0]);
        std :: cout << "sub" << std::endl;
        break;
    case nd_decl :
            return;
    case nd_affect :
            if (N->enfants[0]->type == nd_ref){
            gencode(N->enfants[1]);
            cout << "dup"<<endl;
            cout << "set "<<N->enfants[0]->position<<endl;
            }
            else if (N->enfants[0]->type == nd_ind){
                gencode (N->enfants[1]);
                gencode (N->enfants[0]->enfants[0]);
                cout<<"write"<<endl;
            }
            return ;
    case nd_bloc :
            for (auto i = 0; i<N->nEnfants; i++){
                gencode(N->enfants[i]);
            }
            return ;
    case nd_drop:
            gencode(N->enfants[0]);
            cout<< "drop 1"<<endl;
            return;
    case nd_ancre:
            cout<<".l3_"<<label_boucle<<endl;
            return;
    case nd_continue:
            cout<<"jump l3_"<<label_boucle<<endl;

    case nd_break:
            cout<<"jump l2_"<<label_boucle<<endl;
            return;

    case nd_loop : {
            int l = nblabel++;
            int tmp = label_boucle;
            label_boucle = l;
            cout<<".loop_l1_"<<l<<endl;
            for ( Node* E : N->enfants){
                gencode(E);
            }
            cout<<"jump loop_l1_"<<l<<endl;
            cout<<".l2_"<<l<<endl;
            label_boucle = tmp;
            break; }

    case nd_cond :{
            int temp_if = nblabel;
            nblabel++;
            gencode(N->enfants[0]);
            cout<<"jumpf if_l1_"<<temp_if<<endl;
            gencode(N->enfants[1]);
            cout<<"jump if_l2_"<<temp_if<<endl;
            if (N->enfants.size()>2){
                cout<<".if_l1_"<<temp_if<<endl;
                gencode(N->enfants[2]);
                cout<<".if_l2_"<<temp_if<<endl;
            }
            else {
                cout<<".if_l1_"<<temp_if<<endl;
                cout<<".if_l2_"<<temp_if<<endl;

            }
            break;}
    case nd_seq:
            for (int i = 0; i<N->nEnfants; i++){
                gencode(N->enfants[i]);
            }
            break;
    case nd_ret :
            gencode(N->enfants[0]);
            cout<<"ret"<<endl;
            break;
    case nd_debug:
            gencode(N->enfants[0]);
            cout<<"dbg"<<endl;
            break;
    case nd_appel:  
            cout<<"prep "<<N->enfants[0]->valeur<<endl;
            for(int i = 1; i<N->nEnfants;i++){
                gencode(N->enfants[i]);
            }
            cout<<"call "<<N->enfants.size()-1<<endl;
            return;
    case nd_fonc:
            cout<<"."<<N->valeur<<endl;
            cout<<"resn "<< N->nbVar<<endl;
            gencode(N->enfants[N->nEnfants-1]);
            cout<<"push 0"<<endl;
            cout<<"ret"<<endl;

            return;
    case nd_adr : 
            cout<< "prep start"<<endl;
            cout<< "swap"<<endl;
            cout<< "drop 1"<<endl;
            cout<<"push "<<N->enfants[0]->position + 1<<endl;
            cout<<"sub"<<endl;
            
            return;
	case nd_ref : 
		std :: cout << " get" << N -> position << std::endl;
		break;
    case nd_ind: 
        gencode(N->enfants[0]);
        std :: cout << "read" << std::endl;
        break;
    }

}

void AnaSem(Node *N) {

    std::cout << "Node type: " << N->type << ", valeur: " << N->valeur << ", nombre d'enfants: " << N->nEnfants << std::endl;
    if (N->type == nd_affect) {
        if (N->enfants[0]->type != nd_ref && N->enfants[0]->type != nd_ind) {
            erreurfatale("...");
        }
        for (auto i = 0; i < N->nEnfants; i++) {
            AnaSem(N->enfants[i]);
        }
    } else if (N->type == nd_decl) {
        Symbol* S = declare(N->valeur);
        S->type_ = "type_int";
        S->position = nbVar;
        nbVar++;
    } else if (N->type == nd_ref) {
        Symbol* S = chercher(N->valeur);
        if (S->type_ != "type_int") {
            erreurfatale("...");
        }
        N->position = S->position;
    } else if (N->type == nd_bloc) {
        begin();
        for (auto i = 0; i < N->nEnfants; i++) {
            AnaSem(N->enfants[i]);
        }
        end();
    } else if (N->type == nd_appel) {
        if (N->enfants[0]->type != nd_ref) {
            erreurfatale(" ");
        }
        Symbol* S = chercher(N->enfants[0]->valeur);
        if (S->type_ != "type_fonc") {
            erreurfatale(" ..... ");
        }
        for (auto i = 1; i < N->nEnfants; i++) {
            AnaSem(N->enfants[i]);
        }
    } else if (N->type == nd_fonc) {
        
        Symbol* S = declare(N->valeur);
        std::cout << "ici"<< std::endl;
        S->type_ = "type_fonc";
        begin();
        nbVar = 0;
        for (auto i = 0; i < N->nEnfants; i++) {
            AnaSem(N->enfants[i]);
        }
        end();
        N->nbVar = nbVar - (N->nEnfants - 1);
    } else if (N->type == nd_adr) {
        if (N->enfants[0]->type != nd_ref) {
            erreurfatale(" ");
        } else {
            AnaSem(N->enfants[0]);
        }
    } else {
        for (auto i = 0; i < N->nEnfants; i++) {
            AnaSem(N->enfants[i]);
        }
        throw std::runtime_error("Semantic error: invalid reference type.");
    }
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Erreur : veuillez spécifier le chemin du fichier source." << std::endl;
        return 1;
    }
    printf(". start\n");
    for (int i = 1; i < argc; i++) {
        analex(argv[i]);
        reinitialiser();
        while (T.type != tok_eof) {
            Node *N = analyseursynthax();
            std :: cout << "ici\n";
            AnaSem(N);
            N = Optim(N);
            gencode(N);
            next();
        }
    }
    printf("debug\nhalt\n");
    return 0;
}

