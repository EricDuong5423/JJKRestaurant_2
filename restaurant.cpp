#include "main.h"

int MAX_SIZE = 0;

class JJK_restaurant;
class GOJO_restaurant;
class Sukuna_restaurant;

class GOJO_restaurant{
        class BST_Tree;
    private:
        vector<BST_Tree>GOJO_sector;
    public:
        GOJO_restaurant():GOJO_sector(MAX_SIZE+1){};
        void LAPSE_invite(int result){
            int ID = result%MAX_SIZE + 1;
            GOJO_sector[ID].INSERT(result);
        }
        void KOKUSEN_kick(){
            for(int i = 1; i < MAX_SIZE+1; i++)GOJO_sector[i].DELETE();
        }
        void LIMITLESS_print(int NUM){
            if(NUM <= 0 || NUM > MAX_SIZE)return;
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
                    if(n == 0 || k == n)return 1;
                    vector<vector<int>>C(n+1,vector<int>(k+1,0));
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
                    return C[n][k];
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
                    if(!Root->left && !Root->right){
                        delete Root;
                        return nullptr;
                    }
                    else if(!Root->left){
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

class Sukuna_restaurant{
    class Node;
    private:
        vector<Node*>Sukuna_sector;
        list<Node*>Least_Recent_Used;
    private:
        int Index(Node*node){
            if(Least_Recent_Used.front() == node)return 0;
            if(Least_Recent_Used.back() == node)return Least_Recent_Used.size() - 1;

            list<Node*>::iterator it;
            int index = 0;
            for(it = Least_Recent_Used.begin(); it != Least_Recent_Used.end(); it++){
                if(*it == node)return index;
                index++;
            }
            return index;
        }
        int Parent(int i){return (i - 1)/2;}
        int Left(int i){return i*2 + 1;}
        int Right(int i){return i*2 + 2;}
        void reHeapUp(int index){
            if(index > 0){
                if(Sukuna_sector[Parent(index)]->head.size() > Sukuna_sector[index]->head.size()){
                    swap(Sukuna_sector[index],Sukuna_sector[Parent(index)]);
                    reHeapUp(Parent(index));
                }
            }
        }
        void reHeapDown(int index){
            int left = Left(index);
            int right = Right(index);

            int smallest = index;

            if(left < Sukuna_sector.size()){
                if(right < Sukuna_sector.size() &&
                (Sukuna_sector[right]->size() < Sukuna_sector[left]->size() ||
                (Sukuna_sector[right]->size() == Sukuna_sector[left]->size() && Index(Sukuna_sector[right]) > Index(Sukuna_sector[left])))){
                    smallest = right;
                }
                else{
                    smallest = left;
                }
            }

            if(Sukuna_sector[smallest]->size() < Sukuna_sector[index]->size() ||
            (Sukuna_sector[smallest]->size() == Sukuna_sector[index]->size() && Index(Sukuna_sector[smallest]) > Index(Sukuna_sector[index]))){
                swap(Sukuna_sector[smallest], Sukuna_sector[index]);
                reHeapDown(smallest);
            }
        }
        void moveTop(Node*targetNode){
            Least_Recent_Used.remove(targetNode);
            Least_Recent_Used.push_front(targetNode);
        }
        void removeNode(Node*targetNode){
            Least_Recent_Used.remove(targetNode);
        }
    public:
        Sukuna_restaurant(){};
        void LAPSE_invite(int Result){
            int ID = Result%MAX_SIZE+1;
            int index = 0;
            while(index < Sukuna_sector.size()){
                if(Sukuna_sector[index]->ID == ID){
                    break;
                }
                index++;
            }
            if(index == Sukuna_sector.size()){
                Sukuna_sector.push_back(new Node(ID));
                index = Sukuna_sector.size() - 1;
                Sukuna_sector[index]->insert(Result);
                Least_Recent_Used.push_front(Sukuna_sector[index]);
                reHeapUp(index);
            }
            else{
                Sukuna_sector[index]->insert(Result);
                moveTop(Sukuna_sector[index]);
                reHeapDown(index);
            }
        }
        void KEITEIKEN_kick(int NUM){
            if(Sukuna_sector.empty())return;

            int kicknumber = NUM;
            while(!Sukuna_sector.empty() && kicknumber != 0){
                solution << "remove customers in the area ID = " << Sukuna_sector[0]->ID << ": ";
                Sukuna_sector[0]->remove(NUM);
                solution << "\n";

                if(Sukuna_sector[0]->size() == 0){
                    swap(Sukuna_sector[0], Sukuna_sector[Sukuna_sector.size() - 1]);
                    removeNode(Sukuna_sector[Sukuna_sector.size()-1]);
                    delete Sukuna_sector[Sukuna_sector.size() - 1];
                    Sukuna_sector.pop_back();
                    reHeapDown(0);
                }
                else{
                    reHeapDown(0);
                }
                kicknumber--;
            }
        }
        void print_pre_order(int index, int number)
        {
            if(index >= this->Sukuna_sector.size()) return;

            this->Sukuna_sector[index]->print(number);
            print_pre_order(index * 2 + 1, number);
            print_pre_order(index * 2 + 2, number);
        }
        void CLEAVE_print(int NUM){
            if(NUM <= 0)return;
            solution << "Heap : ";
            vector<Node*>::iterator it = Sukuna_sector.begin();
            for(; it != Sukuna_sector.end(); it++){
                int order = 0;
                list<Node*>::iterator ix = Least_Recent_Used.begin();
                for(;ix != Least_Recent_Used.end(); ix++){
                    if(*ix == *it)break;
                    order++;
                }
                solution << it.operator*()->ID << "(len=" << it.operator*()->size() << ",index=" << order << ")" << " ";
            }
            solution << "\n";

            solution << "Heap : ";
            for(it = Sukuna_sector.begin(); it != Sukuna_sector.end(); it++){
                solution << it.operator*()->ID << " ";
            }
            solution << "\n";
            solution << "list LRU : ";
            list<Node*>::iterator ix;
            for(ix = Least_Recent_Used.begin(); ix != Least_Recent_Used.end(); ix++){
                solution << ix.operator*()->ID << " ";
            }
            solution << "\n";

            print_pre_order(0, NUM);
        }
    private:
        class Node{
        private:
            int ID;
            list<int>head;
            friend class Sukuna_restaurant;
        public:
            Node(int ID):ID(ID){};
            ~Node(){};
            int size()const{return head.size();}
            void insert(int Result){
                head.push_front(Result);
            }
            void remove(int NUM){
                int timekick = NUM;
                while(!head.empty() && timekick != 0){
                    solution << head.back() << " ";
                    head.pop_back();
                    timekick--;
                }
            }
            void print(int NUM){
                solution << "customers in the area ID = " << ID << ": ";
                for(list<int>::iterator it = head.begin(); NUM > 0 && it != head.end(); ++it, --NUM)
                {
                    solution << *it << " ";
                }
                solution << "\n";
            }
        };
};

class HuffTree_AVL{
    private:
        class Node;
    private:
        Node*root = nullptr;
    public:
    static bool check(pair<char,int>a, pair<char,int>b){
        if(a.second == b.second){
            if(isupper(a.first) && islower(b.first)){
                return true;
            }
            else if (islower(a.first) && isupper(b.first)){
                return false;
            }
            return a.first > b.first;
        }
        else return a.second > b.second;
    }
    vector<pair<char, int>> string_Processing(string& name){
        int name_size = name.size();
        map<char,int> freq_map;
        for(int i = 0; i < name_size; i++){
            freq_map[name[i]] += 1;
        }
        vector<pair<char,int>>result(freq_map.begin(),freq_map.end());
        for (int i = 0; i < name_size; i++){
            if (isupper(name[i]))
                name[i] = (name[i] + freq_map[name[i]] - 65) % 26 + 65;
            else
                name[i] = (name[i] + freq_map[name[i]] - 97) % 26 + 97;
        }
        int result_size = result.size();
        for(int i = 0; i < result_size; i++){
            if(isupper(result[i].first)){
                result[i].first = (result[i].first + result[i].second - 65) % 26 + 65;
            }
            else{
                result[i].first = (result[i].first + result[i].second - 97) % 26 + 97;
            }
        }
        freq_map.clear();
        for(int i = 0; i < result_size; i++){
            freq_map[result[i].first] += result[i].second;
        }
        result.clear();
        result = vector<pair<char,int>>(freq_map.begin(),freq_map.end());
        sort(result.begin(),result.end(), check);
        return result;
    }
    int height(Node* node){
        if (node == nullptr) {
            return 0;
        }
        return 1 + max(height(node->left), height(node->right));
    }
    Node* rotateLeft(Node* subroot)
    {
        //TODO: Rotate and return new root after rotate
        Node*rightSucc = subroot->right;
        Node*leftRightSucc = rightSucc->left;

        subroot->right = leftRightSucc;
        rightSucc->left = subroot;

        return rightSucc;
    };
    Node* rotateRight(Node* subroot)
    {
        Node*leftSucc = subroot->left;
        Node*rightLeftSucc = leftSucc->right;

        subroot->left = rightLeftSucc;
        leftSucc->right = subroot;

        return leftSucc;
    };
    int getBalance(Node*subroot){
        if(!subroot) return 0;
        return height(subroot->left)- height(subroot->right);
    }
    Node* balanceNode(Node* root, int& count)
    {
        //TODO
        if(count >= 3 || !root)return root;
        int balance_root = getBalance(root),
                balance_left = getBalance(root->left),
                balance_right = getBalance(root->right);
        if(root->left && balance_root > 1 && balance_left >= 0){
            count++;
            return rotateRight(root);
        }
        if(root->left && balance_root > 1 && balance_left < 0){
            root->left = rotateLeft(root->left);
            count+=2;
            if(count >= 4)return root;
            return rotateRight(root);
        }
        if(root->right && balance_root < -1 && balance_right <= 0){
            count++;
            return rotateLeft(root);
        }
        if (root->right && balance_root < -1 && balance_right > 0){
            root->right = rotateRight(root->right);
            count+=2;
            if(count >= 4)return root;
            return rotateLeft(root);
        }
        return root;
    }
    Node* balanceTree(Node* node, int& count)
    {
        //TODO
        if(count >= 3 || !node)return node;
        node = balanceNode(node,count);
        node->left = balanceTree(node->left, count);
        node->right = balanceTree(node->right,count);
        return node;
    }
    Node* buildHuff(vector<pair<char, int>> freq)
    {
        vector<Node*> build;
        for(int i = 0; i < freq.size(); i++){
            Node* newNode = new Node(freq[i].second,freq[i].first);
            build.push_back(newNode);
        }

        while(build.size() > 1)
        {
            int count = 0;
            Node* LWN = build.back();
            build.pop_back();
            Node* ndLWN = build.back();
            build.pop_back();
            Node*newNode = new Node(LWN->weight + ndLWN->weight,'\0',LWN,ndLWN);
            newNode = balanceTree(newNode,count);
            vector<Node*>::iterator it;
            if(build.empty())build.push_back(newNode);
            else{
                for(it = build.begin(); it != build.end(); it++){
                    if(newNode->weight >= it.operator*()->weight){
                        build.insert(it,newNode);
                        break;
                    }
                }
                if(it == build.end())build.push_back(newNode);
            }
        }
        return build[0];
    }
    void encodingHuffman_rec(vector<string>& encoding, Node* node, string s = "")
    {
        //TODO
        if(node->left)encodingHuffman_rec(encoding,node->left,s+"0");
        if(node->right)encodingHuffman_rec(encoding,node->right,s+"1");
        if(node->isChar())encoding[node->c] = s;
    }
    int encodingHuffman(Node * root,string nameCaesar)
    {
        if(root->left == nullptr && root->right == nullptr) return 0;
        vector<string> encoding(256, "");
        encodingHuffman_rec(encoding, root);
        string newString = "";
        for(int i = 0; i < nameCaesar.size(); i++)newString += encoding[nameCaesar[i]];
        reverse(newString.begin(),newString.end());
        int size = newString.size();
        newString = newString.substr(0,min(size,10));
        int result = stoi(newString,0,2);
        return result;
    }
    int encode(string name){
        if(name.length() < 3) return -1;
        vector<pair<char, int>> freq = this->string_Processing(name);
        solution << "freq     : {";
        for (int i = 0; i <freq.size();i++){
            if(i == freq.size() - 1)  solution << "{" <<"'"<< freq[i].first <<"'" << "," << freq[i].second << "}";
            else  solution << "{" <<"'"<< freq[i].first <<"'" << "," << freq[i].second << "},";
        }
        solution << "}"<<endl;
        root = this->buildHuff(freq);

        if(root->left == nullptr && root->right == nullptr) return 0;
        this->print();
        solution << "name   = " << name << endl;
        int result = this->encodingHuffman(root ,name);
        solution << "result = " << result << endl;
        return -1;
        }
    void rec_print(const Node* tree) {
        if (tree == nullptr) {
            return;
        }
        if(tree->c) solution << "[" << tree->weight << "," << tree->c << "]";
        else solution << "[" << tree->weight << "]";

        if (tree->left != nullptr || tree->right != nullptr) {
            solution << "(";
            rec_print(tree->left);
            solution << ",";
            rec_print(tree->right);
            solution << ")";
        }
    }
    void print()
    {
        solution << "root : ";
        rec_print(root);
        solution << '\n';
    }

    private:
        class Node{
        public:
            int weight;
            char c;
            Node* left;
            Node* right;
            friend class HuffTree_AVL;
        public:
            Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr ): weight(weight), c(c), left(left), right(right) {}
            bool isChar() const { return c != '\0'; }
        };
};

class JJK_restaurant{
    private:
        GOJO_restaurant BST;
        Sukuna_restaurant Heap;
        HuffTree_AVL new_arrive_guest;
    public:
        JJK_restaurant() {

        }
//-------------------------------Dành cho cả 2 nhà hàng-------------------------------
        void LAPSE(string NAME){
            int result = new_arrive_guest.encode(NAME);
            return;
        }
        void HAND(){

        }
//-------------------------------Dành cho nhà hàng GOJO-------------------------------
        void KOKUSEN(){
            BST.KOKUSEN_kick();
        }
        void LIMITLESS(int NUM){
            BST.LIMITLESS_print(NUM);
        }
//-------------------------------Dành cho nhà hàng SUKUNA------------------------------
        void KEITEIKEN(int NUM){
            Heap.KEITEIKEN_kick(NUM);
        }
        void CLEAVE(int NUM){
            Heap.CLEAVE_print(NUM);
        }
};