#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstring>
#include <iostream>
#include <set>

using std::cout;
using namespace std;



class  Checker{
private:
    set <char> allowed_symbols;
    set<char> non_break_symbols;
    set<string> submited_words;
    const int MAX_WORD_SIZE;

    string convert_to_str(char* a, int size)
    {
        int i;
        string s = "";
        for (i = 0; i < size; i++) {
            s = s + a[i];
        }
        return s;
    }
public:
    Checker( char* allowed, char* non_breaks,int max_word_size): MAX_WORD_SIZE(max_word_size){
        char* pAllowed;
        for (pAllowed = allowed; *pAllowed != '\0'; pAllowed++) {
            allowed_symbols.insert(*pAllowed );
        }
        char* pnon_break;
        for (pnon_break = non_breaks; *pnon_break != '\0'; pnon_break++) {
            non_break_symbols.insert(*pnon_break );
        }

        //відняти allowed_sybols від non_break_symbols

    }
    void print_allowed_symbols(){
        cout << "allowed symbols are: " ;

        for(auto i: allowed_symbols)
            cout << i;
        cout << endl;
    }
    void get_uniq_allowed_words(string to_check){
        char stack[MAX_WORD_SIZE];
        int head = 0;

        for (char i: to_check){
            /*here 3 cases: allowed, break, else
            allowed - add letter to stack
            not allowed - clean stack, move next
             break -submit word, set clean stack, move next
             */

            bool is_word_allowed=true;
            if(is_word_allowed and allowed_symbols.contains(i)){
                stack[head] = i;
                head++;
            }
            else if(non_break_symbols.contains(i)){
                is_word_allowed = false;
                head = 0;
            }
            else{
                if (is_word_allowed and head > 0){
                    submited_words.insert(convert_to_str(stack, head));
                }
                head= 0;

            }
        }
    }

    void print_submited_words(){
        cout << "sybmited words are: " ;

        for(auto i: submited_words)
            cout << i << " ";
        cout << endl;
    }


};




/*
 * program workflow:
     take input txt
     create vector strings
     do: save head as 0 symbol; is_head = true
     while(true):
        if break symbol:
            tail = break symbol
            word = tail - head
            mein_controller(word)
        else:
            reader.next_word()

     funcs:
        add to sorted string
        search in string binary
        mein_controller()
        is_vowel()
        is_break_symbol()

    const arrays:
        symbols_chars
        vowel_chars*/
int main () {
    system("chcp 65001");
    SetConsoleOutputCP(CP_UTF8);

    string allowed = "youaserhgft";//"аяіїеєуюАЯЇІЕЄУЮqeuioüaöäyQEUIOÜAÖÄY";
    string non_break = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"; //йцукенгшщзхъфывапролджэячсмитьбюЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮЮїєґіІҐЄЇ";

    Checker my_checker( const_cast<char *>(allowed.c_str()), const_cast<char *>(non_break.c_str()), 10);
    my_checker.print_allowed_symbols();
    char16_t a;
    string line;

    ifstream myfile ("C:/Users/teraf/Desktop/texttotest.txt");
    if (myfile.is_open())
    {
        string input;

        while(getline(myfile, line)) {
            my_checker.get_uniq_allowed_words(line);
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    my_checker.print_submited_words();
    return 0;
}
