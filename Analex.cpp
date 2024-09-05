#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <stdexcept>
#include <vector>

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
    TokenType type;
    int ligne;
    std::string valeur;
};

class S {
public:
    std::string nom;
    std::string type_;
    int position;
    int nbVar;

    // Constructeur
    S(const std::string& nom) : nom(nom), type_(""), position(0), nbVar(0) {}
};

/* il reste à implementer la ligne*/
Token T, L;
string code = "";
size_t ligne = 1 , position = 0;

// Déclaration de la liste Vars et la variable globale nbVar
std::vector<S> Vars;
int nbVar = 0;

// Fonction pour déclarer une variable
S& declare(const std::string& nom) {
    // Parcourt la liste des variables en sens inverse
    for (int i = Vars.size() - 1; i >= 0; --i) {
        if (Vars[i].nom == nom) {
            throw std::runtime_error("Declaration dupliquee de la variable : " + nom);
        } else if (Vars[i].nom == "---") {
            break;
        }
    }

    // Création d'une nouvelle instance de S et ajout à la liste Vars
    Vars.push_back(S(nom));
    return Vars.back();  // Retourne une référence à la dernière variable ajoutée
}


S& chercher(const std::string& nom) {
    // Parcourt la liste des variables en sens inverse
    for (int i = Vars.size() - 1; i >= 0; --i) {
        if (Vars[i].nom == nom) {
            return Vars[i];  // Retourne une référence à la variable trouvée
        }
    }
    throw std::runtime_error("Variable non trouvée : " + nom);
}

// Fonction pour commencer un nouveau scope
void begin() {
    Vars.push_back(S("---"));  // Ajoute un marqueur de scope dans la liste Vars
}

// Fonction pour terminer le scope courant
void end() {
    while (!Vars.empty() && Vars.back().nom != "---") {
        Vars.pop_back();  // Supprime les variables jusqu'au marqueur de scope
    }
    if (!Vars.empty()) {
        Vars.pop_back();  // Supprime le marqueur de scope
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

void accept(TokenType type){
    if(check(type) == false){
        throw std::runtime_error("Error Fatal : trouve "+ T.valeur);
    }
}

int main(int argc, char *argv[]) {
    
    analex(argv[1]);
    return 0;
}

