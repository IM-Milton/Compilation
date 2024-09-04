#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>

using namespace std;
// --------------------------- -----------------------//


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

struct Token {
    TokenType type;
    int ligne;
    std::string valeur;
};

Token T, L;
string code;
int ligne = 1 , position = 0; 
bool fin = false;

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
/*
int check (string type){
    if(T.type != type){
        return false;
    }
    else{
        next();
        return true;
    }

}*/


void analex( string fname){
    char temp = ' ';
  // Lire le fichier et attribuer le code dans la variable code -------------
    code = lireFichier(fname);
    std :: cout << code << endl;
    
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
        std :: cout << T.type << endl;
        std :: cout << " ICI" << endl;
        next();
    }

}

/*
void accept(int type){
    if(T.type != type){
        std::cout<<"Erreur fatale"<<std::endl;
    }
    next();
}*/


int main(int argc, char *argv[]) {
    analex(argv[1]);
    return 0;
}



struct Node{
    int type;
    int valeur;
    int Nenfants;
    Node *enfants[];
};

/*
Node *A(){
    if (check(tok_constante)){
    A = CreerNode(,L.valeur)
    }
    else if (check(tok_open_parenthesis)){
        A=E(); 
        accept(tok_close_parenthesis);
        return A

    }
}*/


