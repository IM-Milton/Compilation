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
    tok_send,
    tok_main
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
    nd_main,
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
    nd_indirect // Added nd_indirect
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
    {nd_main, "nd_main"},
    {nd_fonc, "nd_fonc"}, // Added nd_fonc to the map,
    {nd_main, "nd_main"}
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

Node *E(){
    return E(0);
}

Node *A(){
    if (check(TokenType :: tok_constante)){
        Node *A = creerNode(NodeType :: nd_const, L.valeur);
        return A;
    }
    else if (check(TokenType :: tok_open_parenthesis)){
        Node *A = E(0);
        accept(TokenType :: tok_close_parenthesis);
        return A;
    }
    else if (check( TokenType :: tok_ident)){
        return creerNode(nd_ref, L.valeur);
    }
    else if(check(tok_eof)){
        return creerNode(nd_eof);
    }
    else if(T.type == tok_semicolon){
        return creerNode(nd_vide);
    }
    else{    
        throw std::runtime_error("Erreur : trouvé " + L.valeur);
    } 
}


Node *I(){
    if(check(tok_debug)){
        Node *R = E();
        accept(tok_semicolon);
        return creerNode(nd_debug,R);
    }
    else if (check(tok_open_bracket)){
        Node *R = creerNode (nd_bloc);
        while(!check(tok_close_bracket)){
            ajouterEnfant(R,I());
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
        accept(tok_open_parenthesis);
        Node *expr= E();
        accept(tok_close_parenthesis);
        Node *I1 = I();
        Node *R = creerNode(nd_cond, expr, I1);

        if (check(tok_else)){
            Node *I2 = I();
            ajouterEnfant(R, I2);
        }
        return R;

    }else if(check(tok_while)){
        accept(tok_open_parenthesis);
        Node *expr = E();
        accept(tok_close_parenthesis);
        Node *I1 = I();
        Node *brek = creerNode(nd_break);
        Node *R = creerNode(nd_cond, expr, I1, brek);
        Node *ancre = creerNode(nd_ancre);
        Node *loop = creerNode(nd_loop, ancre, R);

        return loop;
    }else if(check(tok_for)){
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
    }else if(check(tok_do)){
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
    else if(check(tok_return)){
        Node *R = E();
        accept(tok_semicolon);
        return creerNode(nd_return, R);
    }
    else if(check(tok_break)){
        accept(tok_semicolon);
        return creerNode(nd_break);
    }
    else if(check(tok_continue)){
        accept(tok_semicolon);
        return creerNode(nd_continue);
    }
    else if(check(tok_send)){
        Node *R = E();
        accept(tok_semicolon);
        return creerNode(nd_send, R);
    }
    else if(check(tok_recv)){
        Node *R = E();
        accept(tok_semicolon);
        return creerNode(nd_recv, R);

    }
    else{
        Node *R=E();
        accept(tok_comma);
        return creerNode(nd_drop, R);
    }
}

Node *P(){
    Node *A;
    /*A revoir apres ajout des nouveaux champs*/
    if (check(tok_plus)){
        A = P(); return A;
    }
    else if (check(tok_minus)){
        A = P();
        return creerNode(nd_NdMoinsUn,A);
    }else if(check(tok_logical_not)){
        A = P();
        return creerNode(nd_not,A);
    }else if(check(tok_bitwise_and)){
        A = P();
        return creerNode(nd_band,A);//A revoir
    }else if(check(tok_multiply)){
        A = P();
        return creerNode(nd_mul,A);}
    else {
        A = S(); return A;
    }
}

Node *F(){
    accept(tok_int);
    accept(tok_ident);
    Node *R = creerNode(nd_fonc, L.valeur);
    accept(tok_open_parenthesis);
    while(check(tok_int)){
        accept(tok_ident);
        ajouterEnfant(R,creerNode(nd_decl, L.valeur));
        if(check(tok_comma)){
            continue;
        }
        else{
            break;
        }
    }
    accept(tok_close_parenthesis);
    Node* i = I();
    ajouterEnfant(R,i);
    return R;
}

void erreurfatale(const std::string& message) {
    throw std::runtime_error(message);
}

Node* analyseursynthax(){
    return F();
}

void AnaSem(Node *N) {
    switch(N->type) {
        default:
            for(int i = 0; i < N->nEnfants; i++) {
                AnaSem(N->enfants[i]);
                throw std::runtime_error("Semantic error: invalid reference type.");
            return;
        case nd_affect:
            if(N->enfants[0]->type != nd_ref && N -> enfants[0] -> type != nd_ind) {
                erreurfatale("...");
            }
            for(int i = 0; i < N->nEnfants; i++) {
                AnaSem(N->enfants[i]);
            }
            return;
        case nd_decl:
            Symbol *S = declare(N->valeur);
            S->type_ = "type_int";
            S->position = nbVar; 
            nbVar++;
            return;
        case nd_ref:
            Symbol *S = chercher(N->valeur);
            if(S->type_ != "type_int") {
                erreurfatale("...");
            }
            N->position = S->position;
            return;
        case nd_bloc:
            begin();
            for(int i = 0; i < N->nEnfants; i++) {
                AnaSem(N->enfants[i]);
            }
            end();
            return;
        case nd_appel:
            if (N->enfants[0]-> type != nd_ref) {
                erreurfatale(" ");
            }
            Symbol *S = chercher(N->enfants[0]->valeur);
            if (S->type_ != "type_fonc") {
                erreurfatale("");
            }
            for(int i = 1; i < N->nEnfants; i++) {
                AnaSem(N->enfants[i]);
            }
            return;
        case nd_fonc:
            Symbol *S = declare(N->valeur);
            S->type_ = "type_fonc";
            begin();
            nbVar = 0;
            for (int i = 0; i < N->nEnfants; i++) {
                AnaSem(N->enfants[i]);
            }
            end();
            N->nbVar = nbVar - (N->nEnfants - 1);
            return;
        case nd_adr:
            if(N -> enfants[0]->type != nd_ref)
		        erreurfatale(" ");
	        else {
		        return AnaSem(N-> enfants[0]);
	        }
    }
}
}
struct Operateur {
    TokenType TokenType; 
    int prio;             
    int assoc;             
    NodeType NodeType;   
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



Node *E (int pmin){
    Node *A1 = P();
    while (T.type != tok_eof){
        const Operateur *op = nullptr;
        for(const auto& op_ : operateurs){
            if (op_.TokenType == T.type){
                op = &op_;
                break;
            }
        }
        if (op == nullptr || op->prio < pmin){
            return A1;
        }
        next();
        Node *A2= E(op->prio + op->assoc);
        A1 = creerNode(op->NodeType, A1, A2);
    }
    return A1;
}

Node *S(){
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
        Node *e = E(0);
        accept(tok_close_bracket);
        Node *I = creerNode(nd_indirect, e);
        return I;
    }
    return N;        
  }

Token T, L;
string code = "";
size_t ligne = 1 , position = 0;

class Symbol {
public:
    std::string nom;
    std::string type_;
    int position;
    int nbVar;

    Symbol(const std::string& nom) : nom(nom), type_(""), position(0), nbVar(0) {}
};

std::vector<Symbol> Vars;
int nbVar = 0;

Symbol* declare(const std::string& nom) {
    for (int i = Vars.size() - 1; i >= 0; --i) {
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
    for (int i = Vars.size() - 1; i >= 0; --i) {
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

map <string, TokenType > keywords = {
    {"if", TokenType::tok_if},
    {"else", TokenType::tok_else},
    {"while", TokenType::tok_while},
    {"return", TokenType::tok_return},
    {"int", TokenType::tok_int},
    {"main", TokenType::tok_main},
    {"for", TokenType::tok_for},
    {"do", TokenType::tok_do},
    {"break", TokenType::tok_break},
    {"continue", TokenType::tok_continue},
    {"recv", TokenType::tok_recv},
    {"send", TokenType::tok_send},
};

void next(){
    for (size_t i = position; i < code.length(); i++){
        if( isspace(code[i])){
            continue;
        }
        L = T;
        position ++;
        break;
    }
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

void analex( string fname){
    char temp = ' ';
  // Lire le fichier et attribuer le code dans la variable code -------------
    code = lireFichier(fname);

    while (temp != '\0')
    {
        temp = code[position];
        string s;
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
            s = string(1, temp);
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
            while (position < code.length() && isalnum(code[position]))
            {
                text += code[position];
                position ++;
            }
            s = text;

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
        std :: cout << " le type : " << T.type << ", Valeur : " << T.valeur << ", Ligne : " << T.ligne << std::endl;
        next();
    }
    
}



int nblabel = 0;
int lbl_continue = 0;
int lbl_break = 0;
int iflabel = 0;

void gencode(Node *N){

    if(Tables.find(N->type) != Tables.end()){
        for (int i = 0; i < N->nEnfants; i++){
            gencode(N->enfants[i]);
        }
        std :: cout << Tables[N->type] << std::endl;
        return ;
    }

    switch (N->type)
    {
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
    case nd_loop:
        /* code */
        int lbl_debut = nblabel++;
        int save_lbl_continue = nblabel++;
        lbl_continue = save_lbl_continue;
        int save_lbl_break = nblabel++;
        lbl_break = save_lbl_break;

        std::cout << ".l" << lbl_debut << std::endl;
        for (Node* E : N->enfants) {
            gencode(E);
        }
        lbl_continue = save_lbl_continue;
        lbl_break = save_lbl_break;
        std::cout << "jump .l" << lbl_debut << std::endl;
        std::cout << ".l" << lbl_break << std::endl;
        break;
    case nd_if:
        iflabel ++;
        gencode(N->enfants[0]);
        std :: cout << "jmpl l1_" << iflabel << std::endl;
        gencode(N->enfants[1]);
        if (N -> nEnfants > 2){
            std :: cout << "jump l2_" << std::endl;
            std :: cout << ".l1_" << iflabel << std::endl;
            gencode(N->enfants[2]);
            std :: cout << ".l2_" << iflabel << std::endl;
        }
        break;
    case nd_fonc:
        std::cout << '.' << N->valeur << std::endl;
        std::cout << "resn " << N->nbVar << std::endl;
        gencode(N->enfants[N->nEnfants - 1]);
        std::cout << "push 0" << std::endl;
        std::cout << "ret" << std::endl;
        break;
    case nd_appel:
        if (N->enfants[0]->type != nd_ref) {
                throw std::runtime_error("Undefined function: " + N->valeur);
            } else if (chercher(N->enfants[0]->valeur)->type_ != "type_fonc") {
                throw std::runtime_error("Not a function: " + N->valeur);
            }
            std::cout << "prep " << N->valeur << std::endl;
            for (size_t i = 1; i < N->enfants.size(); ++i) {
                gencode(N->enfants[i]);
            }
            std::cout << "call " << (N->enfants.size() - 1) << std::endl;
            break;
	case nd_ref : 
		std :: cout << " get" << N -> position << std::endl;
		return ;
	case nd_affect :
		gencode(N -> enfants[1]);
		std :: cout << "dup" << std :: endl;
		std ::cout << "set" << N -> enfants[0] -> position << std :: endl;
		return ;
    case nd_ind: 
        gencode(N->enfants[0]);
        std :: cout << "read" << std::endl;
    default:
        break;
    }

}

void accept(TokenType type){
    if(check(type) == false){
        throw std::runtime_error("Error Fatal : trouve "+ T.valeur);
    }
}

int main(int argc, char *argv[]) {
    
    std :: cout << ".start" << std::endl;
    for (int i = 1; i < argc; i++){
        analex(argv[i]);
        while (T.type != tok_eof)
        {
            
        }
        
    }
    analex(argv[1]);
    return 0;
}

