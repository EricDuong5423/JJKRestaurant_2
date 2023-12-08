#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include<vector>
#include<map>
#include<stack>
#include<queue>
#include<list>
#include <utility> 
#include <algorithm>

using namespace std;

class Node{
public:
    int weight;
    char c;
    int height;
    Node* left;
    Node* right;
    friend class HuffTree_AVL;
public:
    Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr ): height(1), weight(weight), c(c), left(left), right(right) {}
    bool isChar() const { return c != '\0'; }
};
void encodingHuffman_rec(vector<string>& encoding, Node* node, string s = "")
{
    //TODO
    if(!node)return;
    if(node->isChar())encoding[node->c] = s;
    if(node->left)encodingHuffman_rec(encoding,node->left,s+'0');
    if(node->right)encodingHuffman_rec(encoding,node->right,s+'1');
}
int encodingHuffman(Node * root,string nameCaesar)
{
    if(root->left == nullptr && root->right == nullptr) return 0;
    vector<string> encoding(256, "");
    encodingHuffman_rec(encoding, root);
    string newString = "";
    for(int i = 0; i < nameCaesar.size(); i++)newString += encoding[nameCaesar[i]];
    reverse(newString.begin(),newString.end());
    newString = newString.substr(0,10);
    int result = stoi(newString,0,2);
    return result;
}


int main()
{
    //* test 1
    {
        Node* root = new Node(4, '\0', 
                                    new Node(1, 'a'),
                                    new Node(1, 'b'));
        string nameCaesar = "baa";
      
        int result = 1;
        int output_you = encodingHuffman(root, nameCaesar);
        if(result != output_you)
        {
            cout << "fail test 1 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 1 \n";
    }    

    //* test 2
    {
        Node* root = new Node(4, '\0', 
                                    new Node(1, 'a'),
                                    new Node(1, 'b'));
        string nameCaesar = "baa";reverse(nameCaesar.begin(), nameCaesar.end());
        int result = 4;
        int output_you = encodingHuffman(root, nameCaesar);
        if(result != output_you)
        {
            cout << "fail test 2 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 2 \n";
    }    


    //* test 3
    {
        Node* root = new Node(4, '\0', 
                                    new Node(1, 'a'),
                                    new Node(1, 'b'));
        string nameCaesar = "baaaaaaaaba";
        reverse(nameCaesar.begin(), nameCaesar.end());
        int result = pow(2,9) + 1;
        int output_you = encodingHuffman(root, nameCaesar);
        if(result != output_you)
        {
            cout << "fail test 3 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 3 \n";
    }    




    //* test 4
    {
        Node* root = new Node(4, '\0', 
                                    new Node(1, 'a'),
                                    new Node(1, 'b'));
        string nameCaesar = "aaaaaaaaaab";reverse(nameCaesar.begin(), nameCaesar.end());
        int result = 0;
        int output_you = encodingHuffman(root, nameCaesar);
        if(result != output_you)
        {
            cout << "fail test 4 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 4 \n";
    } 

    //* test 5
    {
        //! 4(7('d','c'), 14(2('a','b'), 'e'))
        //! 'd':00 'c':01 'a':100 'b':101 'e'11
        Node* root = new Node(4, '\0',
                                new Node(7, '\0',
                                    new Node(3, 'd'),
                                    new Node(2, 'c')),
                                new Node(14, '\0',
                                    new Node(2, '\0',
                                        new Node(1, 'a'),
                                        new Node(1, 'b')),
                                    new Node(10, 'e')));
        string nameCaesar = "e";reverse(nameCaesar.begin(), nameCaesar.end());
        int result = 3;
        int output_you = encodingHuffman(root, nameCaesar);
        if(result != output_you)
        {
            cout << "fail test 5 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 5 \n";
    }     

    //* test 6
    {
        //! 4(7('d','c'), 14(2('a','b'), 'e'))
        //! 'd':00 'c':01 'a':100 'b':101 'e'11
        Node* root = new Node(4, '\0',
                                new Node(7, '\0',
                                    new Node(3, 'd'),
                                    new Node(2, 'c')),
                                new Node(14, '\0',
                                    new Node(2, '\0',
                                        new Node(1, 'a'),
                                        new Node(1, 'b')),
                                    new Node(10, 'e')));
        string nameCaesar = "dddda";reverse(nameCaesar.begin(), nameCaesar.end());
        int result = 0;
        int output_you = encodingHuffman(root, nameCaesar);
        if(result != output_you)
        {
            cout << "fail test 6 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 6 \n";
    }     


    //* test 7
    {
        //! 4(7('d','c'), 14(2('a','b'), 'e'))
        //! 'd':00 'c':01 'a':100 'b':101 'e'11
        Node* root = new Node(4, '\0',
                                new Node(7, '\0',
                                    new Node(3, 'd'),
                                    new Node(2, 'c')),
                                new Node(14, '\0',
                                    new Node(2, '\0',
                                        new Node(1, 'a'),
                                        new Node(1, 'b')),
                                    new Node(10, 'e')));
        string nameCaesar = "eeeea";reverse(nameCaesar.begin(), nameCaesar.end());
        int result = 1020;
        int output_you = encodingHuffman(root, nameCaesar);
        if(result != output_you)
        {
            cout << "fail test 7 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 7 \n";
    }     

    //* test 8
    {
        //! 4(7('d','c'), 14(2('a','b'), 'e'))
        //! 'd':00 'c':01 'a':100 'b':101 'e'11
        Node* root = new Node(4, '\0',
                                new Node(7, '\0',
                                    new Node(3, 'd'),
                                    new Node(2, 'c')),
                                new Node(14, '\0',
                                    new Node(2, '\0',
                                        new Node(1, 'a'),
                                        new Node(1, 'b')),
                                    new Node(10, 'e')));
        string nameCaesar = "eeeeec";reverse(nameCaesar.begin(), nameCaesar.end());
        int result = 1023;
        int output_you = encodingHuffman(root, nameCaesar);
        if(result != output_you)
        {
            cout << "fail test 8 \n";
            cout << "nameCaesar = " << nameCaesar << endl;
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 8 \n";
    }     
}