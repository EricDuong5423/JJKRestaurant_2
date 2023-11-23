#include "main.h"

int MAX_SIZE = 0;

class JJK_restaurant;
class AVL_HuffTree;
class GOJO_restaurant;
class Sukuna_restaurant;

class JJK_restaurant{
    GOJO_restaurant *Hash_Restaurant;
    Sukuna_restaurant*Heap_Restaurant;
    public:
    JJK_restaurant() {
        Heap_Restaurant = nullptr;
        Hash_Restaurant = nullptr;
    }
//-------------------------------Dành cho cả 2 nhà hàng-------------------------------
    void LAPSE(string NAME){

    }
    void HAND(){

    }
//-------------------------------Dành cho nhà hàng GOJO-------------------------------
    void KOKUSEN(){

    }
    void LIMITLESS(int NUM){

    }
//-------------------------------Dành cho nhà hàng SUKUNA------------------------------
    void KEITEIKEN(int NUM){

    }
    void CLEAVE(int NUM){

    }
};

class GOJO_restaurant{
        class BST_Tree;
    private:
        vector<BST_Tree>GOJO_sector;
    public:
        GOJO_restaurant():GOJO_sector(MAX_SIZE+1){};
        void INVITE_Sector(int result){
            int ID = result%MAX_SIZE + 1;
            GOJO_sector[ID].INSERT(result);
        }
        void KOKUSEN_kick(){
            for(int i = 1; i < MAX_SIZE+1; i++)GOJO_sector[i].DELETE();
        }
        void LIMITLESS_print(int NUM){
            if(NUM <= 0 || NUM > MAX_SIZE + 1)return;
            GOJO_sector[NUM].PRINT_Inorder();
        }
    private:
        class BST_Tree{
            private:
                class Node;
            private:
                Node *root;
                queue<int>Time_Line;
            public:
                BST_Tree():root(nullptr){};
                int size(){return Time_Line.size();}
//-------------------------------Những hàm thêm------------------------------
                Node*Recursive_INSERT(Node*Root, int result){
                    if(!Root)return new Node(result);
                    if(result < Root->result)Root->left = Recursive_INSERT(Root->left,result);
                    else Root->right = Recursive_INSERT(Root->right,result);
                    return Root;
                }
                void INSERT(int result){
                    this->root = Recursive_INSERT(root,result);
                    Time_Line.push(result);
                }
//-------------------------------Những hàm xóa------------------------------
                int Count_Node(Node*Root){
                    return (Root == nullptr ? 0:1 + Count_Node(Root->left) + Count_Node(Root->right));
                }
                unsigned long long PascalPermutate(int k, int n){
                    //Tạo một mảng có chiều dọc là n + 1 với chiều ngang là k + 1
                    int C[n+1][k+1];
                    //Không xài đệ quy vì quá lâu với số như là 15!
                    for(int i = 0; i <= n; i++){
                        for(int j = 0; j <= min(i,k); j++){
                            //TH C(n,1) và C(n,n) thì bằng 1
                            if(j == 0 || j == i){
                                C[i][j] = 1;
                            }
                            //TH bình thường thì áp dụng công thức của tam giác pascal C(n,k) = C(n-1,k-1) + C(n-1,k)
                            else{
                                C[i][j] = C[i-1][j-1] + C[i-1][j];
                            }
                        }
                    }
                }
                unsigned long long FindDiffTree(Node*Root){
                    if(!Root)return 1;
                    int N = Count_Node(Root->left) + Count_Node(Root->right);
                    int K = Count_Node(Root->left);
                    unsigned long long nCk = PascalPermutate(K,N);
                    return nCk * FindDiffTree(Root->left) * FindDiffTree(Root->right);
                }
                Node*Recursive_DELETE(Node*Root, int result){
                    //TH Cơ bản
                    if(!Root)return Root;
                    //Đi tìm Node cần xóa
                    if(result < Root->result){
                        Root->left = Recursive_DELETE(Root->left, result);
                        return Root;
                    }
                    else if(result > Root->result){
                        Root->right = Recursive_DELETE(Root->right,result);
                        return Root;
                    }
                    //Sau khi tìm xong
                    //TODO:Nếu như nhánh cây chỉ có 1 con
                    if(!Root->left){
                        //Nhánh cây chỉ có con bên phải
                        //TODO:Lấy nhánh phải làm tổ tiên luôn
                        Node*temp = Root->right;
                        delete Root;
                        return temp;
                    }
                    else if (!Root->right){
                        //Nhánh cây chỉ có con bên trái
                        //TODO:Lấy nhánh trái làm tổ tiên luôn
                        Node*temp = Root->left;
                        delete Root;
                        return temp;
                    }
                    else{
                        //Nhánh cây có cả 2 con
                        //TODO:Đi tìm con cháu có giá trị nhỏ nhất của nhánh bên phải gốc
                        Node*succParent = Root;
                        Node*succ = Root->right;
                        while(succ->left){
                            succParent = succ;
                            succ = succ->left;
                        }
                        //Nếu như con cháu có giá trị nhỏ nhất là gốc bên phải của gốc đang xét
                        if(succParent == Root){
                            //TODO: Thì cho cái nhánh phải của gốc lấy phần nhánh phải của con cháu
                            succParent->right = succ->right;
                        }
                        //Nếu không phải
                        else{
                            //TODO: Thì cái nhánh trái của gốc lấy phần nhánh phải của con cháu
                            succParent->left = succ->right;
                        }
                        //TODO:Sau đó copy data của con cháu nhỏ nhất bên phải vào Root
                        Root->result = succ->result;
                        //TODO:Xóa con node con cháu đi và trả về gốc.
                        delete succ;
                        return Root;
                    }
                }
                void DELETE(){
                    if(this->size() == 0)return;
                    if(this->size() == 1)return;
                    unsigned long long number = FindDiffTree(root);
                    while(number != 0 && !Time_Line.empty()){
                        int top = Time_Line.front();
                        Time_Line.pop();
                        root = Recursive_DELETE(root,top);
                        number--;
                    }
                }
//-------------------------------Những hàm in ra------------------------------
                string Recursive_PRINT(Node*Root){
                    if(!Root)return "NULL";
                    string LeftResult = Recursive_PRINT(Root->left);
                    solution << Root->result << " ";
                    string RightResult = Recursive_PRINT(Root->right);

                    if(!Root->left && !Root->right)return to_string(Root->result);
                    return to_string(Root->result) + "(" + LeftResult + "," + RightResult + ")";
                }
                void PRINT_Inorder(){
                    if(this->size() == 0){
                        solution << "EMPTY" ;
                        return;
                    }
                    solution << "inoder: ";
                    string s = Recursive_PRINT(this->root);
                    solution << "\nTree: " << s;
                    queue<int> tempQueue = Time_Line;
                    solution << "\nQueue: ";
                    while (!tempQueue.empty()) {
                        solution << tempQueue.front() << " ";
                        tempQueue.pop();
                    }
                }
            private:
                class Node{
                    private:
                        int result;
                        Node*left;
                        Node*right;
                        friend class BST_Tree;
                    public:
                        Node(int result):result(result),left(nullptr),right(nullptr){};
                };
        };
};