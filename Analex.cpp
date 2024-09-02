#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>

using namespace std;
// --------------------------- -----------------------//

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
struct Token {
private:
    TokenType type;     
    std::string valeur; 
    int ligne;          

public:
    // Constructeur par défaut
    Token() : type(TokenType::INCONNU), valeur(""), ligne(0) {}

    // Constructeur pour initialiser un token avec des valeurs spécifiques
    Token(TokenType t, const std::string& v, int l) : type(t), valeur(v), ligne(l) {}

    // Getter pour le type du token
    TokenType getType() const {
        return type;
    }

    // Setter pour le type du token
    void setType(TokenType t) {
        type = t;
    }

    // Getter pour la valeur du token
    std::string getValeur() const {
        return valeur;
    }

    // Setter pour la valeur du token
    void setValeur(const std::string& v) {
        valeur = v;
    }

    // Getter pour le numéro de ligne
    int getLigne() const {
        return ligne;
    }

    // Setter pour le numéro de ligne
    void setLigne(int l) {
        ligne = l;
    }
};

/* il reste à implementer la ligne*/
Token T, L;
string code = "";
size_t ligne = 1 , position = 0;



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
        position = i;
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
    char temp;
  // Lire le fichier et attribuer le code dans la variable code -------------
    code = lireFichier(fname);

    while (temp != '\0')
    {
        temp = code[position];
        string s;
        if ( temp == '+'){
            T.setType(TokenType::tok_plus);
            s = string(1, temp);
        }else if (temp == '-'){
            T.setType(TokenType::tok_minus);
            s = string(1, temp);
        }else if (temp == '*'){
            T.setType(TokenType::tok_multiply);
            s = string(1, temp);
        }else if (temp == '/'){
            T.setLigne(TokenType::tok_divide);
            s = string(1, temp);
        }else if (temp == '%'){
            T.setType(TokenType::tok_modulo);
            s = string(1, temp);
        }else if (temp == '='){
            if (code[position+1] == '='){
                T.setType(TokenType::tok_equal);
                s = temp + "=";
                position = position + 1;
            }else{
                T.setType(TokenType::tok_assignment);
                s = string(1, temp);
            }
        }else if (temp == '!'){
            if (code[position+1] == '=')
            {
                T.setType(TokenType :: tok_not_equal);
                s = temp + "=";
            }else{
                T.setType(TokenType::tok_logical_not);
                s = string(1, temp);
            }
        }else if (temp == '<'){
            if (code[position+1] == '=')
            {
                T.setType(TokenType :: tok_less_equal);
                s = temp + "=";
            }else{
                T.setType(TokenType::tok_less_than);
                s = string(1, temp);
            }
        }else if (temp == '>'){
            if(code[position+1] == '='){
                T.setType(TokenType :: tok_greater_equal);
                s = temp + "=";
            }else{
                T.setType(TokenType::tok_greater_than);
                s = string(1, temp);
            }
        }else if (temp == '&'){
            if (code[position+1] == '&'){
                T.setType(TokenType :: tok_logical_and);
                s = temp + "&";
            }else{
                T.setType(TokenType::tok_bitwise_and);
                s = string(1, temp);
            }
        }else if (temp == '|'){
            if (code[position+1] == '|'){
                T.setType(TokenType :: tok_logical_or);
                s = temp + "|";
            }else{
                T.setType(TokenType::tok_bitwise_or);
                s = string(1, temp);
            }
        }else if (temp == ','){
            T.setType(TokenType::tok_comma);
            s = string(1, temp);
        }else if (temp == ';'){
            T.setType(TokenType::tok_semicolon);
            s = string(1, temp);
        }else if (temp == '('){
            T.setType(TokenType::tok_open_parenthesis);
            s = string(1, temp);
        }else if (temp == ')'){
            T.setType(TokenType::tok_close_parenthesis);
            s = string(1, temp);
        }else if (temp == '{'){
            T.setType(TokenType::tok_open_brace);
            s = string(1, temp);
        }else if (temp == '}'){
            T.setType(TokenType::tok_close_brace);
            s = string(1, temp);
        }else if (temp == '['){
            T.setType(TokenType::tok_open_bracket);
            s = string(1, temp);
        }else if (temp == ']'){
            T.setType(TokenType::tok_close_bracket);
            s = string(1, temp);
        }
        else if (isdigit(temp)){
            s = string(1, temp);
            while(position < code.length() && isdigit(code[position])){
                s = s + code[position];
                position++;
            }
            T.setType(TokenType::tok_constante);
        }else if(temp == '\0'){
            T.setType(TokenType::tok_eof);
            s = "\0";
        }else {
            string text;
            while (position < code.length() && isspace(code[position]) == false )
            {
                text += code[position];
                position ++;
            }
            s = text;

            /*Verification si c'est un mot clés connu*/
            bool patch = false;
            for (const auto& entry : keywords) {
                if(text == entry.first){
                    T.setType(entry.second);
                    patch = true;
                }
            }
            
            /*Cest un identifiant*/
            if(patch == false ){
                T.setType(TokenType::tok_ident);
            }
        }
        T.setValeur(s);
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
    
    code = lireFichier(argv[0]);
    return 0;
}


/*
struct Node{
    int type;
    int valeur;
    int Nenfants;
    Node *enfants[];
};*/
