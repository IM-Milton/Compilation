// --- Test 1 : Opérations unitaires (négations, pré- et post-incréments) ---

// Test 1.1 : Négations simples
int main() {
    int a = 5;
    int b = -a; // Devrait donner -5
    return b;
}

// Test 1.2 : Pré-incrémentation et post-incrémentation
int main() {
    int a = 5;
    int b = ++a; // b = 6, a = 6
    int c = a++; // c = 6, a = 7
    return a + b + c; // Devrait donner 19
}

// Test 1.3 : Pré-décrémentation et post-décrémentation
int main() {
    int a = 5;
    int b = --a; // b = 4, a = 4
    int c = a--; // c = 4, a = 3
    return a + b + c; // Devrait donner 11
}

// Test 1.4 : Négation logique
int main() {
    bool flag = true;
    bool result = !flag; // Devrait donner false
    return result;
}

// --- Test 2 : Opérations binaires de base ---

// Test 2.1 : Addition et soustraction
int main() {
    int a = 10 + 5;
    int b = 10 - 5;
    return a + b; // Devrait donner 20
}

// Test 2.2 : Multiplication et division
int main() {
    int a = 10 * 5;
    int b = 10 / 5;
    return a + b; // Devrait donner 52
}

// Test 2.3 : Modulo
int main() {
    int a = 10 % 3; // Devrait donner 1
    return a;
}

// Test 2.4 : Opérations logiques (ET, OU)
int main() {
    bool result = (5 > 3) && (3 < 10); // Devrait donner true
    bool result2 = (5 == 5) || (10 != 10); // Devrait donner true
    return result && result2; // Devrait donner true (1)
}

// Test 2.5 : Opérations bit à bit
int main() {
    int a = 5 & 3;  // Devrait donner 1 (0101 & 0011 = 0001)
    int b = 5 | 3;  // Devrait donner 7 (0101 | 0011 = 0111)
    int c = 5 ^ 3;  // Devrait donner 6 (0101 ^ 0011 = 0110)
    return a + b + c; // Devrait donner 14
}

// Test 2.6 : Décalages bit à bit
int main() {
    int a = 4 << 1;  // Devrait donner 8 (0100 << 1 = 1000)
    int b = 4 >> 1;  // Devrait donner 2 (0100 >> 1 = 0010)
    return a + b; // Devrait donner 10
}

// --- Test 3 : Précédence des opérateurs et utilisation des parenthèses ---

// Test 3.1 : Précédence sans parenthèses
int main() {
    int result = 5 + 3 * 2; // Devrait donner 11 (3*2 = 6, puis 5+6)
    return result;
}

// Test 3.2 : Utilisation de parenthèses pour changer la précédence
int main() {
    int result = (5 + 3) * 2; // Devrait donner 16 (5+3 = 8, puis 8*2)
    return result;
}

// Test 3.3 : Opérations imbriquées avec parenthèses
int main() {
    int result = ((2 + 3) * (5 - 2)) + (4 / 2); // Devrait donner 17
    return result;
}

// Test 3.4 : Parenthèses dans des opérations logiques
int main() {
    bool result = (5 > 3) && ((3 < 10) || (2 > 5)); // Devrait donner true (1)
    return result;
}

// --- Test 4 : Cas spéciaux ---

// Test 4.1 : Division par zéro (si le compilateur le gère)
int main() {
    int a = 5;
    int b = 0;
    int c = a / b; // Devrait soulever une erreur ou exception
    return c;
}

// Test 4.2 : Overflow d'entier
int main() {
    int maxInt = 2147483647; // Valeur maximale pour un int
    int overflow = maxInt + 1; // Devrait overflow si non géré
    return overflow;
}

// Test 4.3 : Underflow d'entier
int main() {
    int minInt = -2147483648; // Valeur minimale pour un int
    int underflow = minInt - 1; // Devrait underflow si non géré
    return underflow;
}

// Test 4.4 : Opérateurs unaires combinés avec des expressions binaires
int main() {
    int a = 5;
    int b = 3;
    int result = -a + (b * -2); // Devrait donner -11
    return result;
}

// Test 4.5 : Utilisation combinée de tous les opérateurs
int main() {
    int a = 5, b = 3, c = 4;
    int result = (a + b) * c - (b << 1) + (c >> 1) & (~a | b); 
    return result; // Devrait donner un résultat complexe
}

// Test 4.6 : Opérations imbriquées avec mélange d'opérations binaires et unaires
int main() {
    int a = 5;
    int b = -((a + 3) * (a - 2)) + (a++); // Calcul complexe avec unaires et binaires
    return b;
}


// --- Test 1 : Constantes et constantes de type littéral ---

// Test 1.1 : Constantes entières
int main() {
    const int a = 5;
    const int b = 10;
    int c = a + b; // Devrait donner 15
    return c;
}

// Test 1.2 : Constantes flottantes
int main() {
    const float pi = 3.14159f;
    const float radius = 2.0f;
    float area = pi * radius * radius; // Devrait donner ~12.56636
    return (int)area; // Retourne la partie entière
}

// Test 1.3 : Constantes de caractère
int main() {
    const char letter = 'A';
    return letter; // Devrait donner le code ASCII de 'A', soit 65
}

// Test 1.4 : Constantes de chaîne de caractères
#include <string>
int main() {
    const std::string greeting = "Hello";
    return greeting.length(); // Devrait donner 5
}

// Test 1.5 : Constantes booléennes
int main() {
    const bool isTrue = true;
    const bool isFalse = false;
    return isTrue && !isFalse; // Devrait donner true (1)
}

// --- Test 2 : Constexpr et expressions constantes ---

// Test 2.1 : Constexpr avec des expressions constantes
constexpr int square(int x) { return x * x; }
int main() {
    int result = square(5); // Devrait donner 25
    return result;
}

// Test 2.2 : Constexpr avec des expressions imbriquées
constexpr int complexExpr(int a, int b) { return (a + b) * (a - b); }
int main() {
    int result = complexExpr(10, 3); // Devrait donner 91
    return result;
}

// Test 2.3 : Utilisation de constexpr dans les conditions
constexpr bool isEven(int x) { return x % 2 == 0; }
int main() {
    return isEven(4); // Devrait donner true (1)
}

// --- Test 3 : Structures de contrôle avec des accolades ---

// Test 3.1 : If avec accolades
int main() {
    int a = 10;
    if (a > 5) {
        a = 20;
    }
    return a; // Devrait donner 20
}

// Test 3.2 : If-Else avec accolades
int main() {
    int a = 3;
    if (a > 5) {
        a = 20;
    } else {
        a = 30;
    }
    return a; // Devrait donner 30
}

// Test 3.3 : Boucles For avec blocs d'accolades
int main() {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += i;
    }
    return sum; // Devrait donner 10
}

// Test 3.4 : Boucles While avec blocs d'accolades
int main() {
    int count = 0;
    int i = 0;
    while (i < 5) {
        count += i;
        i++;
    }
    return count; // Devrait donner 10
}

// Test 3.5 : Boucles imbriquées avec des accolades
int main() {
    int product = 1;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 2; j++) {
            product *= i + j; // Produit cumulatif de i+j
        }
    }
    return product; // Devrait donner 720
}

// --- Test 4 : Blocs d'accolades imbriqués et portée des variables ---

// Test 4.1 : Portée locale avec des blocs d'accolades
int main() {
    int a = 10;
    {
        int a = 5;  // Cette variable masque la précédente
        a += 10;    // a = 15 dans ce bloc
    }
    return a; // Devrait retourner 10 (variable en dehors du bloc)
}

// Test 4.2 : Variables déclarées dans des blocs imbriqués
int main() {
    int a = 0;
    {
        int b = 5;
        {
            int c = 10;
            a = b + c; // a = 15
        }
    }
    return a; // Devrait donner 15
}

// Test 4.3 : Variables constantes dans des blocs imbriqués
int main() {
    const int x = 10;
    {
        const int y = 20;
        {
            const int z = 30;
            return x + y + z; // Devrait donner 60
        }
    }
}

// --- Test 5 : Cas spéciaux avec des constantes et des accolades ---

// Test 5.1 : Initialisation constante complexe
const int baseValue = 100;
constexpr int computeValue(int x) { return baseValue + x * x; }
int main() {
    int result = computeValue(5); // Devrait donner 125
    return result;
}

// Test 5.2 : Utilisation de const dans les fonctions
int add(const int a, const int b) {
    return a + b;
}

int main() {
    int result = add(5, 10); // Devrait donner 15
    return result;
}

// Test 5.3 : Opérations arithmétiques et logiques avec des constantes
int main() {
    const int a = 3, b = 4, c = 5;
    int result = (a + b) * c; // Devrait donner 35
    return result;
}

// Test 5.4 : Constantes et variables statiques dans des blocs
int main() {
    static const int base = 10;
    int result = 0;
    {
        static const int multiplier = 5;
        result = base * multiplier; // Devrait donner 50
    }
    return result;
}

// Test 5.5 : Constante avec une expression conditionnelle
int main() {
    const int x = 10;
    const int y = (x > 5) ? 20 : 30; // Devrait donner 20
    return y;
}

// Test 5.6 : Utilisation de constexpr avec des expressions conditionnelles
constexpr int max(int a, int b) { return (a > b) ? a : b; }
int main() {
    int result = max(10, 20); // Devrait donner 20
    return result;
}
