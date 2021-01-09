//
//  main.cpp
//  cppconsole
//
//  Created by Yuxin Sun on 3/15/20.
//  Copyright © 2020 Yuxin Sun. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;
using std::vector;

void TestUnorderMap();

void Test_Unordered_set();

void test_vector_morden_cpp();

void Test_share_ptr();

void test_constrexpr();

void test_deque();

void test_stack();

void Test_move_forward();

void Test_value_categories();

void Test_fold_expression();

void Test_type_deduce();

void test_basic();

void test_async();

void test_function_able();

void Test_priority_queue();

void TestUnorderMap();

void Test_map();



class RemoveSubfolders {

public:

    vector<string> doit_dfs(vector<string>& folder) {
        size_t found;
        
        sort(folder.begin(), folder.end());
        
        string main_folder=folder[0];

        vector<string> answer;
        answer.reserve(folder.size());
        answer.push_back(main_folder);
        main_folder=main_folder+"/";       //  /a/b/c vs /a/b/ca, folder ends with '/'
        //cout<<"DEBUG main_folder: "<<main_folder<<endl;
        
        for(auto it=folder.begin()+1; it!=folder.end(); it++){
            //cout<<" *it: "<<*it<<" main_folder: "<<main_folder<<endl;
            string sub_folder=(string) (*it);
            /* check if main_folder is substring of current string */
            found=sub_folder.find(main_folder);
           // cout<<" founs is:"<<found;
            if(found == string::npos){ //uniq, another main folder found
                main_folder=*it;
                answer.push_back(main_folder);
                main_folder=main_folder+"/";
            }
        }

        return answer;
    }

    struct Trie {
        unordered_map<string, Trie*> _children;
        bool _done;
    };

public:
    vector<string> removeSubfolders(vector<string>&& folder) {
        Trie *_root = new Trie();

        std::function<void(string)> insert = [&](const string& target) {

            Trie *node = _root;
            int i = 1;
            string child;

            while (i < target.size()+1) {

                if (i == target.size() || target[i] == '/') {
                    
                    if (node->_children.find(child) == node->_children.end()) {
                        node->_children[child] = new Trie();
                    }
                    node = node->_children[child];
                    child = "";
                    if (node->_done) return;
                } else {
                    child += target[i];
                }
                i++;
            }
            node->_done = true;
        };

        vector<string> ans;
        std::function<void(Trie*, string)> find = [&](Trie* p, string path){
            
            if (p->_done) {
                ans.push_back(path);
                return;
            }

            for (auto c: p->_children) {
                find(c.second, path + '/' + c.first);
            }
        };

        for (auto w: folder)
            insert(w);

        find(_root, "");

        return ans;
    }
};

int main(int argc, const char * argv[]) {

    std::cout << "Hello, World!\n";
    
    RemoveSubfolders().removeSubfolders(vector<string>{"/a","/a/b","/c/d","/c/d/e","/c/f"});
    
    
    // Test_map();
    
    // TestUnorderMap();
    
    // Test_priority_queue();
    
    // test_function_able();
    
    // test_basic();
    
    // Test_type_deduce();
    
    // Test_fold_expression();
    
    // Test_value_categories();
    
    // Test_move_forward();

    // TestUnorderMap();

    // Test_Unordered_set();

    // test_vector_morden_cpp();

    // Test_share_ptr();
    
    // test_constrexpr();
    
    // test_deque();
    
    // test_stack();
    
    // test_async();

    return 1;
}

