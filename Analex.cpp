#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>

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

enum TokenType {
    INCONNU,
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
    char temp = NULL;
  // Lire le fichier et attribuer le code dans la variable code -------------
    while (temp != '\0')
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
        else if (isdigit(temp)){
            while(position < code.size() && isdigit(code[position])){
                position++;
            }
            T.type  = TokenType::tok_constante;
        }else {
            string text;
            while (position < code.size() && isspace(code[position]) == false )
            {
                text += temp;
                position ++;
            }

            bool patch = false;
            for (const auto& entry : keywords) {
                if(text == entry.first){
                    T.type = entry.second;
                    patch = true;
                }
            }
             
            if(patch == false ){
                T.type = TokenType::tok_ident;
            }
        }

    }
    
}

void accept(int type){
    if(T.type != type){
        std::cout<<"Erreur fatale"<<std::endl;
    }
    next();
}



std::string lireFichier(const std::string& cheminFichier) {
    std::ifstream fichier(cheminFichier);  // Ouvrir le fichier en lecture
    if (!fichier.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier." << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << fichier.rdbuf();  // Lire le contenu du fichier dans le stringstream

    return buffer.str();  // Retourner le contenu sous forme de string
}


int main() {
    lireFichier("nom_du_fichier.txt");
    return 0;
}



struct Node{
    int type;
    int valeur;
    int Nenfants;
    Node *enfants[];
};
