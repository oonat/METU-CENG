#include "the9.h"

// do not add extra libraries here

/*

We would like to search a given pattern P on a given text T with the following features:

- Only capital letters are used in the alphabet. The alphabet is going to be given to you as 2 letters, the first and the last letter that will be used.

- The lengths of the pattern and the text is limited as follows: |P|<20 and |T|<2000.

- Wild character is available that can match with any character. The wild character can occur only in the pattern and it is represented by "?".

- There can be at most one wild character in the pattern.

Your task is to construct the FSA  transition table for the given problem instance and determine the starting indexes of each occurrence of the pattern in the text (the starting index of the text is 1).

Since FSA construction is the prepossessing phase of the whole search problem, your FSA construction implementation does not have to be the most efficient one. However, the search operation should still be in linear time.


Input

L_1 L_k --- first and the last letter of the alphabet to be used in the text and the pattern

XX..XX --- the pattern with m characters (may include at most 1 wild character '?')

YY..YY  --- the text with n characters

Output

- If there is a wildcard in the pattern:

I_1 I_2 ...I_t --- starting indexes for the occurrences of the pattern P on the text T(must be sorted).

-Else
Q_1 Q_2 ... Q_k --- transitions to states from 0:  to Q_1 for the character L_1 as the input, ..., to Q_k for the input L_k
...                     --- m lines for all transitions (states are integers separated by a blank,note that there will be m+1 lines regarding FSA with the above one)
I_1 I_2 ...I_t --- starting indexes for the occurrences of the pattern P on the text T(must be sorted).

*/


#define DEBUG 
#define DEBUG_STDERR(x) do { std::cerr << (x) << endl; } while(0)
#define DEBUG_ARRAY(a, n) do { for (int i = 0; i < n; i++) std::cerr << a[i] << " "; std::cerr << endl; } while(0)

// for example usage of DEBUG macros check test.cpp

#define min(x,y) (x < y ? x : y)

vector<vector<int>> create_fsm(string pattern, vector<char> sigma){

    int pattern_len = pattern.length();
    int sigma_size = sigma.size();

    vector<vector<int>> table(pattern_len + 1, vector<int>(sigma_size));

    for(int q = 0; q <= pattern_len; q++){
        for(int j = 0; j < sigma.size(); j++){

            char ch = sigma[j];
            string tmp = pattern.substr(0, q);
            tmp.push_back(ch);
    
            for(int k = 0; k <= min(q + 1, pattern_len); k++){
                string str1 = tmp.substr(k);
                string str2 = pattern.substr(0, q-k+1);
          
                if(str1.compare(str2) == 0){
                    table[q][j] = q-k+1;
                    break;
                }
            }

        }
    }
    
    return table;
}


char * search_helper (char txt[], char pat[], char alphabet[], bool wild, int posw){
    vector<vector<int>> table;
    vector<int> indexes;
    vector<char> sigma;
    char* ret;

    // generate sigma
    for(int i = alphabet[0]; i <= alphabet[1]; i++){
      sigma.push_back((char) i);
    }

    string pattern (pat);


    if(wild){
    
    vector<vector<vector<int>>> table_list;
    vector<int> state_array = vector<int> (sigma.size(), 0);

    for(int j = 0; j < sigma.size(); j++){
      pattern[posw] = sigma[j];
      table = create_fsm(pattern, sigma);
      table_list.push_back(table);
    }

    for(int i = 0; txt[i] != 0; i++){
        int position = txt[i] - alphabet[0];
        for(int j = 0; j < sigma.size(); j++){
          state_array[j] = table_list[j][state_array[j]][position];
        }
        for(int j = 0; j < sigma.size(); j++){
        if(state_array[j] == pattern.length()){
            indexes.push_back(i - pattern.length() + 2);
            break;
          }
        }
    }

    string tmp = "";
    for(int i = 0; i < indexes.size(); i++)
      tmp += to_string(indexes[i]) + " ";


    ret = new char[tmp.length() + 1];
    for(int i = 0; i < tmp.length(); i++)
      ret[i] = tmp[i];

    ret[tmp.length()] = 0;
    

    }else{

    int q = 0;
    
    table = create_fsm(pattern, sigma);

    for(int i = 0; txt[i] != 0; i++){
        int position = txt[i] - alphabet[0];
        q = table[q][position];

        if(q == pattern.length()){
            indexes.push_back(i - pattern.length() + 2);
        }
    }

    
    string tmp = "";
    for(int i = 0; i < table.size(); i++){
      for(int j = 0; j < sigma.size(); j++){
        tmp += to_string(table[i][j]) + " ";
      }
      tmp += "\n";
    }

    for(int i = 0; i < indexes.size(); i++)
      tmp += to_string(indexes[i]) + " ";


    ret = new char[tmp.length() + 1];
    for(int i = 0; i < tmp.length(); i++)
      ret[i] = tmp[i];

    ret[tmp.length()] = 0;

    }


    return ret;
  
}


char * search (char txt[], char pat[], char alphabet[]){
  bool wild = false;
  int posw = -1;

  for(int i = 0; pat[i] != 0; i++)
    if(pat[i] == '?'){
      posw = i;
      wild = true;
      break;
    }
  
  return search_helper(txt, pat, alphabet, wild, posw);
}


