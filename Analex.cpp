#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;
// --------------------------- -----------------------//
struct Token {
    TokenType type;
    int ligne;
    std::string valeur;
};


Token T, L;
string code;
int ligne = 1 , position = 0; 
bool fin = false;

enum TokenType {
    INCONNU,
    tok_eof,
    tok_id,
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
    tok_main
};

std::string tokenOperators[] = {
    "+",
    "-",
    "*",
    "/",
    "%",
    "==",
    "!=",
    "<",
    ">",
    "<=",
    ">=",
    "&&",
    "||",
    "!",
    "&",
    "|",
    "=",
    ",",
    ";",
    "(",
    ")",
    "{",
    "}",
    "[",
    "]",
    "%",
    "if",
    "else",
    "while",
    "for",
    "return",
    "int",
    "main"
};

void next(){
    for (int i = position; i < code.size(); i++){
        if( isspace(code[i])){
            continue;
        }
        L = T;
        position = i;
        break;
    }
}

int check (string type){
    if(T.type != type){
        return false;
    }
    else{
        next();
        return true;
    }

}


void analex( string fname){
    char temp;
  // Lire le fichier et attribuer le code dans la variable code -------------
    while (T.type != "tok_eof")
    {
        temp = code[position];

        if ( temp == '+'){
            T.type = TokenType::tok_plus;
        }else if (temp == '-'){
            T.type = TokenType::tok_minus;
        }else if (temp == '*'){
            T.type = TokenType::tok_multiply;
        }else if (temp == '/'){
            T.type = TokenType::tok_divide;
        }else if (temp == '%'){
            T.type = TokenType::tok_modulo;
        }else if (temp == '='){
            if (code[position+1] == '='){
                T.type = TokenType::tok_equal;
                position = position + 1;
            }else{
                T.type = TokenType::tok_assignment;
            }
        }else if (temp == '!'){
            if (code[position+1] == '=')
            {
                T.type = TokenType :: tok_not_equal;
            }else{
                T.type = TokenType::tok_logical_not;
            }
        }else if (temp == '<'){
            if (code[position+1] == '=')
            {
                T.type = TokenType :: tok_less_equal;
            }else{
                T.type = TokenType::tok_less_than;
            }
        }else if (temp == '>'){
            if(code[position+1] == '='){
                T.type = TokenType :: tok_greater_equal;
            }else{
                T.type = TokenType::tok_greater_than;
            }
        }else if (temp == '&'){
            if (code[position+1] == '&'){
                T.type = TokenType :: tok_logical_and;
            }else{
                T.type = TokenType::tok_bitwise_and;
            }
        }else if (temp == '|'){
            if (code[position+1] == '|'){
                T.type = TokenType :: tok_logical_or;
            }else{
                T.type = TokenType::tok_bitwise_or;
            }
        }else if (temp == ','){
            T.type = TokenType::tok_comma;
        }else if (temp == ';'){
            T.type = TokenType::tok_semicolon;
        }else if (temp == '('){
            T.type = TokenType::tok_open_parenthesis;
        }else if (temp == ')'){
            T.type = TokenType::tok_close_parenthesis;
        }else if (temp == '{'){
            T.type = TokenType::tok_open_brace;
        }else if (temp == '}'){
            T.type = TokenType::tok_close_brace;
        }else if (temp == '['){
            T.type = TokenType::tok_open_bracket;
        }else if (temp == ']'){
            T.type = TokenType::tok_close_bracket;
        }
        else if (

        ){

        }

    }
    
}

void accept(int type){
    if(T.type != type){
        std::cout<<"Erreur fatale"<<std::endl;
    }
    next();
}



void lireFichier(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier); // Ouvre le fichier en lecture
    if (!fichier.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return;
    }

    std::string ligne;
    while (std::getline(fichier, ligne)) {
        std::cout << ligne << std::endl; // Affiche chaque ligne du fichier
    }

    fichier.close(); // Ferme le fichier
}


int main() {
    lireFichier("nom_du_fichier.txt");
    return 0;S
}



struct Node{
    int type;
    int valeur;
    int Nenfants;
    Node *enfants[];
}


Node *A(){
    if (check(tok_constante)){
    A = CreerNode(,L.valeur)
    }
    else if (check(tok_open_parenthesis)){
        A=E(); 
        accept(tok_close_parenthesis);
        return A

    }
}

Node *CreerNode(int type); 