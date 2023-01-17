#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;


// --------- Two DFAs ---------------------------------
//Reusable letters
string consonants = "bghkmnpr";
string consonantsOther = "djwyz";
string vowels = "aeiouIE";

/*
Description: This function will determine if the character is in the string we pass as a parameter.
Parameters: 
character - is the character we are checking for in the str.
str - This is either the consonant, consonantOther, or vowels string that is searched through to find the character if its there.
Locals: NONE
Return: True if found, false if not found.
*/
bool checkCharInChars(char character, string str) {
  //looping through chars in character groups
  for(int i = 0; i<str.length();i++){
    //if the char passed in is in the character group, return true
    if(str[i] == character){
      return true;
    }
  }
  //otherwise return false
  return false;
}

// WORD DFA 
// Regular Expression: (vowel | vowel n | consonant vowel| consonant vowel n | consonant-pair vowel | consonant-pair vowel n)^+

/* 
Q0 = 1       	qsa = 5
Qy = 2       	qt = 6
Qc = 3		q1q0 = 7
Qs = 4		q0qy = 8
*/


/*
Description: This functions takes in a string s and determines if it qualifies as a valid word
Parameters: 
s - the string we are trying to validate
Locals:
state - the current state of the DFA
charpos - the pointer to the current char of the string s
Return: true is tue string is a word, false otherwise
*/
bool word (string s)
{
  //state is initally 1, charpos initially 0
  int state = 1;
  int charpos = 0;

  while (s[charpos] != '\0') 
    {
      //state 1 || Q0
      if (state == 1 && s[charpos] == 'c'){
        state = 3;//Qc    
      }
      else if (state == 1 && s[charpos] == 't'){
        state = 6;//Qt
      }
      else if(state == 1 && s[charpos] == 's')
      {
        state = 4;//Qs
      }
      else if (state == 1 && checkCharInChars(s[charpos], vowels))      
      {
        state = 7;//Q1Q0 
      }
      else if (state == 1 && checkCharInChars(s[charpos], consonantsOther))      {
        state = 5;//Qsa
      }
      else if (state == 1 && checkCharInChars(s[charpos], consonants)){
        state = 2;//Q
      }


      //state 2 || Qy  
      else if (state == 2 && s[charpos] == 'y'){ 
        state = 5;//Qsa
        
      }
      else if (state == 2 && checkCharInChars(s[charpos], vowels)){
        state = 7;//Q1Q0
        
      }


      //state 3 || Qc  
      else if (state == 3 && s[charpos] == 'h'){
        state = 5;//Qsa
         
      }

      //state 4 || Qs
      else if (state == 4 && s[charpos] == 'h'){
        state = 5;//Qsa
        
      }
      else if (state == 4 && checkCharInChars(s[charpos], vowels)){
        state = 7;//Q1Q0
      }

        
      else if (state == 5 && checkCharInChars(s[charpos],vowels)){
        state = 7;//Q1Q0
      }


      else if(state == 6 && checkCharInChars(s[charpos], vowels)){
        state = 7;//Q1Q0
      }
      else if(state == 6 && s[charpos] == 's'){
        state = 5;//Qsa
      }

        
      else if(state == 7 && s[charpos] == 'n'){
        state = 8;//Q0Qy
      }
      else if(state == 7 && checkCharInChars(s[charpos], vowels)){
        state = 7;//Q0Q1
      }
      else if(state ==7 && s[charpos] == 's'){
        state = 4;//Qs
      }
      else if(state == 7 && s[charpos] == 'c'){
        state = 3;//Qc
      }
      else if(state == 7 && s[charpos] == 't'){
        state = 6;//Qt
      }
      else if(state == 7 && checkCharInChars(s[charpos], consonants)){
        state = 2;//Qy
      }
      else if(state == 7 && checkCharInChars(s[charpos], consonantsOther)){
        state = 5;//Qsa
      }

      //state 8 || Q0Qy
      else if (state == 8 && checkCharInChars(s[charpos],consonants))
      {
        state = 2;//Qy
      }
      else if (state == 8 &&checkCharInChars(s[charpos],consonantsOther))
      {
        state = 5;//Qsa
      }
      else if (state == 8 && checkCharInChars(s[charpos],vowels))
      {
        state = 7;//Q1Q0
      }
      else if (state == 8 && s[charpos] == 's')
      {
        state = 4;//Qs
      }
      else if (state == 8 && s[charpos] == 't')
      {
        state = 6;//Qt
      }
      else if (state == 8 && s[charpos] == 'c')
      {
        state = 3;//Qsa
      }
      else
      {
	    return(false);
      }
      charpos++;
    }//end of while

  
  if (state == 1 || state == 7 || state == 8) return(true);  // end in a final state
   else return(false);
}


/* 
PERIOD DFA 

Regular Expression: .

Description: This is simple function that determines if the character in the first position of the string is a period.
Parameters: 
s - The string we are checking to see if a period is present in the first position.
Locals: NONE
Return: True if a period is found, false otherwise.
*/
bool period (string s) {  // complete this
  //if first char of string is a period, return true
  if(s[0] == '.'){
    return true;
  }
  //otherwise return false
  else return
    (false);
}

// ------ Three  Tables -------------------------------------

//Tokentypes
enum tokentype {ERROR,VERB,VERBNEG,VERBPAST,VERBPASTNEG,IS,WAS,OBJECT,SUBJECT,DESTINATION,PRONOUN,CONNECTOR, WORD1, WORD2, PERIOD, EOFM};

// Token Strings - must be in the same order as the tokentypes.
string tokenName[30] = {"ERROR", "VERB", "VERBNEG","VERBPAST","VERBPASTNEG","IS","WAS","OBJECT","SUBJECT","DESTINATION","PRONOUN","CONNECTOR","WORD1","WORD2","PERIOD","EOFM"}; 

vector<vector<string>> reservedWords = {{"masu"}, {"masen"}, {"mashita"}, {"masendeshita"}, {"desu"}, {"deshita"}, {"o"}, {"wa"}, {"ni"}, {"watashi", "anata", "kare", "kanojo", "sore"}, {"mata", "soshite", "shikashi", "dakara"}};


/*
Description: Checks the reserved words list to see if the word passed in is valid.
Parameters:
word - string that is being checked.
Locals:
i - counter for the appropriate array within the reserved words list.
j - counter for within the array being chosen.
Return: if word is found, return the index + 1 so the type can be found in enum 
list.
if not found return -1 indicating the word was not in the list.
*/
int checkReserved(string& word){
  //looping through columns and rows of table
  for(int i = 0;i < reservedWords.size(); i++){
    for(int j = 0;j < reservedWords[i].size(); j++){
      //if cell is equal to passed in word, return the index of the row + 1 to get corresponding enum value
      if(reservedWords[i][j] == word){
        return i+1;
      }
    }
  }
  //return -1 if not found
  return -1;
}

// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

/* 
Scanner processes only one word each time it is called
Gives back the token type and the word itself
Done by: Ian M, Kyle H, Dylan K

Description: This function grabs the next token from the file and determines the the token type.
Parameters:
tt - Is the variable that gets assigned a token type based off the token read in from the file.
w - Is the string variable that gets assigned the token read in from the file.
Locals: NONE
Return: An interger indicated success or failure. 0 is successs. -1 is failure.
*/
int scanner(tokentype& tt, string& w)
{

  fin >> w;
  
  if (w == "eofm") {
    tt = EOFM;
    return 0;
  }
 
  else if (word(w)) {
    //if word is reserved
    if(checkReserved(w) != -1){
      //set tt to return from checkReserved(w)
      tt = (tokentype) checkReserved(w);
    }
    //if word ends in I or E, tt is WORD2
    else if(w[w.size()-1] == 'I'|| w[w.size()-1] == 'E'){
      tt = WORD2;
    }
    //otherwise tt is WORD1
    else {
      tt = WORD1;
    }
    return 0;
  }
  //if w is period, tt is PERIOD
  else if(period(w)) {
    tt = PERIOD;
    return 0;
  }
  else {  
    tt = ERROR;//lexical error
    return -1;
  }
   

}


// ----- Four Utility Functions and Globals -----------------------------------
tokentype  saved_token;
string  saved_lexeme;
bool token_available = false;  

// Type of error: Match fails
void syntaxerror1(string lexeme, tokentype token){    
  cout << "SYNTAX ERROR1: expected " << tokenName[token] << " but found " << lexeme << endl;
  exit(1);
}
// Type of error: Switch Default
void syntaxerror2(string lexeme, tokentype token){
  cout << "SYNTAX ERROR2: unexpected " << lexeme << " found in " << tokenName[token] << endl;
  exit(1);
}

// next_token(void)
//    HOW: checks first to see if the token_available flag is false.
//                If so, saved_token gets scanner() result.
//                and the flag is set true.
//    A token is grabbed but is not eaten up.
//    Returns the saved_token
//   
// Purpose:  Looks ahead to see what token comes next from the scanner.
tokentype next_token(){
  string word;
   if (!token_available)   // if there is no saved token yet
   { 
       scanner(saved_token, word);    // call scanner to grab a new token
       saved_lexeme = word;
	   // saved_token is the token type and 
       // saved_lexeme is the word that is read in
       token_available = true;// mark that fact that you have saved it

       if (saved_token == ERROR)
       { 
            syntaxerror1(saved_lexeme, saved_token);
       }
   }
   
   return saved_token;// return the saved token

}


//match(expected)
//  Checks and eats up the expected token.
//  HOW: checks to see if expected is different from next_token()
//              and if so, generates a syntax error and handles the error
//              else token_available becomes false (eat up) and returns true.

// Purpose: checks to see if expected is different from next_token()
bool match(tokentype expected) {  
      if (next_token() != expected)// mismatch has occurred with the next token+
   {
        // calls a syntax error function here to generate a syntax error message here and do recovery
        syntaxerror2(saved_lexeme, expected);
   }
   else  // match has occurred
   {
        token_available = false;
        cout << "Matched " << tokenName[expected] << endl;// eat up the token
        return true;// say there was a match
   }
  
  return false;
}

// ----- RDP functions - one per non-term -------------------
void story();
void sentence();
void after_subject();
void after_noun();
void after_object();
void noun();
void verb();
void be();
void tense();

string filename;


// Grammar: <story> ::= <s> {<s>}
void story(){
  bool done = false;
  cout << "Processing <story>" << endl;
  
  sentence();
  while(!done){
    switch(next_token()){
      case tokentype::CONNECTOR:
        sentence();
        break;
      case tokentype::WORD1:
        sentence();
        break;
      case tokentype::PRONOUN:
        sentence();
        break;
      case tokentype::EOFM:
        cout << "Successfully parsed <story>" << endl;
        done = true;
        break;
      default:
        syntaxerror2(saved_lexeme,saved_token);
    }
    
  }
}

 
// Grammar: <s> ::= [CONNECTOR]<noun>SUBJECT <after subject>
void sentence(){
  cout<<"Processing <sentence>"<<endl;
  if (next_token() == tokentype::CONNECTOR){
    match(tokentype::CONNECTOR);
  }
  noun();
  match(tokentype::SUBJECT);
  after_subject();
}


// Grammar: <after subject> :: = <verb> <tense> PERIOD | <noun> <after noun>
void after_subject(){
  cout<<"Processing <after subject>"<<endl;
  switch(next_token()){
    case tokentype::WORD2:
      verb();
      tense();
      match(tokentype::PERIOD);
      break;
    case tokentype::WORD1:
      noun();
      after_noun();
      break;
    case tokentype::PRONOUN:
      noun();
      after_noun();
      break;
    default:
      syntaxerror2(saved_lexeme, saved_token);
  }
}


// Grammar: <after noun> ::= <be> PERIOD | DESTINATION  <verb> <tense> PERIOD | OBJECT <after object>
void after_noun(){
  cout<<"Processing <after noun>"<<endl;
  switch(next_token()){
    case tokentype::IS:
      be();
      match(tokentype::PERIOD);
      break;
    case tokentype::WAS:
      be();
      match(tokentype::PERIOD);
      break;
    case tokentype::DESTINATION:
      match(tokentype::DESTINATION);
      verb();
      tense();
      match(tokentype::PERIOD);
      break;
    case tokentype::OBJECT:
      match(tokentype::OBJECT);
      after_object();
      break;
    default:
      syntaxerror2(saved_lexeme, saved_token);
  }
}


// Grammar: <after object> ::= <verb> <tense> PERIOD |<noun> DESTINATION  <verb> <tense> PERIOD
void after_object(){
  cout<<"Processing <after_object>"<<endl;
  switch(next_token()){
    case tokentype::WORD2:
      verb();
      tense();
      match(tokentype::PERIOD);
      break;
    case tokentype::WORD1:
      noun();
      match(tokentype::DESTINATION);
      verb();
      tense();
      match(tokentype::PERIOD);
      break;
    case tokentype::PRONOUN:
      noun();
      match(tokentype::DESTINATION);
      verb();
      tense();
      match(tokentype::PERIOD);
      break;
    default:
      syntaxerror2(saved_lexeme, saved_token);
  }
}


// Grammar: <noun> ::= WORD1 | PRONOUN
void noun(){
  cout<<"Processing <noun>"<<endl;
  switch(next_token()){
    case tokentype::WORD1:
      match(tokentype::WORD1);
      break;
    case tokentype::PRONOUN:
      match(tokentype::PRONOUN);
      break;
    default:
      syntaxerror2(saved_lexeme, saved_token);
  }
}

// Grammar: <verb> ::= WORD2
void verb(){
  cout<<"Processing <verb>"<<endl;
  match(tokentype::WORD2);
  
}

// Grammar: <be> ::= IS | WAS
void be(){
  cout<<"Processing <be>"<<endl;
  switch(next_token()){
    case tokentype::IS:
      match(tokentype::IS);
      break;
    case tokentype::WAS:
      match(tokentype::WAS);
      break;
    default:
      syntaxerror2(saved_lexeme, saved_token);
  }
}

// Grammar: <tense> := VERB_PAST  | VERB_PASTNEG | VERB | VERB_NEG
void tense(){
  cout<<"Processing <tense>"<<endl;
  switch(next_token()){
    case tokentype::VERBPAST:
      match(tokentype::VERBPAST);
      break;
    case tokentype::VERBPASTNEG:
      match(tokentype::VERBPASTNEG);
      break;
    case tokentype::VERB:
      match(tokentype::VERB);
      break;
    case tokentype::VERBNEG:
      match(tokentype::VERBNEG);
      break;
    default:
      syntaxerror2(saved_lexeme, saved_token);
  }
}
//----------- Driver ---------------------------
// The new test driver to start the parser
int main()
{
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());
  story();
  fin.close();
  //** calls the <story> to start parsing
  //** closes the input file 

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions


