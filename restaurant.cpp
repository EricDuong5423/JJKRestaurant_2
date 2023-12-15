#include "main.h"

int MAX_SIZE = 0;

class JJK_restaurant;
class GOJO_restaurant;
class Sukuna_restaurant;

class GOJO_restaurant {
    class BST_Tree;
private:
    vector<BST_Tree>GOJO_sector;
public:
    GOJO_restaurant() :GOJO_sector(MAX_SIZE + 1) {};
    void LAPSE_invite(int result) {
        int ID = result % MAX_SIZE + 1;
        GOJO_sector[ID].INSERT(result);
    }
    void KOKUSEN_kick() {
        for (int i = 1; i < MAX_SIZE + 1; i++) GOJO_sector[i].DELETE();
    }
    void LIMITLESS_print(int NUM) {
        if (NUM <= 0 || NUM > MAX_SIZE)return;
        GOJO_sector[NUM].print();
    }
private:
    class BST_Tree {
    private:
        class Node;
    private:
        Node* root;
        queue<int>Time_Line;
    public:
        BST_Tree() :root(nullptr) {};
        ~BST_Tree() {
            while (!Time_Line.empty())
            {
                int temp = Time_Line.front();
                Time_Line.pop();
                root = Recursive_DELETE(root, temp);
            }
        }
        int size() { return Time_Line.size(); }
        //-------------------------------Những hàm thêm------------------------------
        Node* Recursive_INSERT(Node* Root, int result) {
            if (!Root)return new Node(result);
            if (result < Root->result)Root->left = Recursive_INSERT(Root->left, result);
            else Root->right = Recursive_INSERT(Root->right, result);
            return Root;
        }
        void INSERT(int result) {
            this->root = Recursive_INSERT(root, result);
            Time_Line.push(result);
        }
        //-------------------------------Những hàm xóa------------------------------
        int Count_Node(Node* Root) {
            return (Root == nullptr ? 0 : 1 + Count_Node(Root->left) + Count_Node(Root->right));
        }
        unsigned long long PascalPermutate(int k, int n) {
            if (n == 0 || k == n)return 1;
            vector<vector<int>>C(n + 1, vector<int>(k + 1, 0));
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j <= min(i, k); j++) {
                    if (j == 0 || j == i) {
                        C[i][j] = 1;
                    }
                    else {
                        C[i][j] = C[i - 1][j - 1] % MAX_SIZE + C[i - 1][j] % MAX_SIZE;
                    }
                }
            }
            return C[n][k];
        }
        unsigned long long FindDiffTree(Node* Root) {
            if (!Root)return 1;
            int N = Count_Node(Root->left) + Count_Node(Root->right);
            int K = Count_Node(Root->left);
            return (PascalPermutate(K, N) * FindDiffTree(Root->left) * FindDiffTree(Root->right)) % MAX_SIZE;
        }
        Node* Recursive_DELETE(Node* Root, int result) {
            if (!Root)return Root;
            if (result < Root->result) {
                Root->left = Recursive_DELETE(Root->left, result);
                return Root;
            }
            else if (result > Root->result) {
                Root->right = Recursive_DELETE(Root->right, result);
                return Root;
            }
            if (!Root->left && !Root->right) {
                delete Root;
                return nullptr;
            }
            else if (!Root->left) {
                Node* temp = Root->right;
                delete Root;
                return temp;
            }
            else if (!Root->right) {
                Node* temp = Root->left;
                delete Root;
                return temp;
            }
            else {
                Node* succParent = Root;
                Node* succ = Root->right;
                while (succ->left) {
                    succParent = succ;
                    succ = succ->left;
                }
                if (succParent == Root) {
                    succParent->right = succ->right;
                }
                else {
                    succParent->left = succ->right;
                }
                Root->result = succ->result;
                delete succ;
                return Root;
            }
        }
        void DELETE() {
            if (this->size() < 1)return;
            unsigned long long number = FindDiffTree(root);
            while (number != 0 && !Time_Line.empty()) {
                int top = Time_Line.front();
                Time_Line.pop();
                root = Recursive_DELETE(root, top);
                number--;
            }
        }
        //-------------------------------Những hàm in ra------------------------------
        void print_recursive(Node* node)
        {
            if (node != NULL) {
                print_recursive(node->left);
                cout << node->result << "\n";
                print_recursive(node->right);
            }
        }
        void print()
        {
            print_recursive(root);
        }
        //^ ----------------------------------------------------------------------------------------------------------
    private:
        class Node {
        private:
            int result;
            Node* left;
            Node* right;
            friend class BST_Tree;
        public:
            Node(int result) :result(result), left(nullptr), right(nullptr) {};
        };
    };
};

class Sukuna_restaurant {
    class Node;
private:
    vector<Node*>Sukuna_sector;
    list<Node*>Least_Recent_Used;
private:
    int Index(Node* node) {
        if (Least_Recent_Used.front() == node)return 0;
        if (Least_Recent_Used.back() == node)return Least_Recent_Used.size() - 1;

        list<Node*>::iterator it;
        int index = 0;
        for (it = Least_Recent_Used.begin(); it != Least_Recent_Used.end(); it++) {
            if (*it == node)return index;
            index++;
        }
        return index;
    }
    int Parent(int i) { return (i - 1) / 2; }
    int Left(int i) { return i * 2 + 1; }
    int Right(int i) { return i * 2 + 2; }
    void reHeapUp(int index) {
        if (index > 0) {
            if (Sukuna_sector[Parent(index)]->head.size() > Sukuna_sector[index]->head.size()) {
                swap(Sukuna_sector[index], Sukuna_sector[Parent(index)]);
                reHeapUp(Parent(index));
            }
        }
    }
    void reHeapDown(int index) {
        int left = Left(index);
        int right = Right(index);

        int smallest = index;
        int size = Sukuna_sector.size();
        if (left < size) {
            if (right < size &&
                (Sukuna_sector[right]->size() < Sukuna_sector[left]->size() ||
                 (Sukuna_sector[right]->size() == Sukuna_sector[left]->size() && Index(Sukuna_sector[right]) > Index(Sukuna_sector[left])))) {
                smallest = right;
            }
            else {
                smallest = left;
            }
        }

        if (Sukuna_sector[smallest]->size() < Sukuna_sector[index]->size() ||
            (Sukuna_sector[smallest]->size() == Sukuna_sector[index]->size() && Index(Sukuna_sector[smallest]) > Index(Sukuna_sector[index]))) {
            swap(Sukuna_sector[smallest], Sukuna_sector[index]);
            reHeapDown(smallest);
        }
    }
    void moveTop(Node* targetNode) {
        Least_Recent_Used.remove(targetNode);
        Least_Recent_Used.push_front(targetNode);
    }
    void removeNode(Node* targetNode) {
        Least_Recent_Used.remove(targetNode);
    }
public:
    Sukuna_restaurant() {};
    ~Sukuna_restaurant() {
        int size = Sukuna_sector.size();
        for (int i = 0; i < size; i++)delete Sukuna_sector[i];
    }
    void LAPSE_invite(int Result) {
        int ID = Result % MAX_SIZE + 1;
        int index = 0;
        int size = Sukuna_sector.size();
        while (index < size) {
            if (Sukuna_sector[index]->ID == ID) {
                break;
            }
            index++;
        }
        if (index == size) {
            Sukuna_sector.push_back(new Node(ID));
            index = Sukuna_sector.size() - 1;
            Sukuna_sector[index]->insert(Result);
            Least_Recent_Used.push_front(Sukuna_sector[index]);
            reHeapUp(index);
        }
        else {
            Sukuna_sector[index]->insert(Result);
            moveTop(Sukuna_sector[index]);
            reHeapDown(index);
        }
    }
    void KEITEIKEN_kick(int NUM) {
        if (Sukuna_sector.empty()) return;
        vector<Node* > areaTableNew(Sukuna_sector.begin(), Sukuna_sector.end());
        queue<Node* > listDelete;
        int size = Sukuna_sector.size();
        for (int i = 0; i < min(NUM,size); i++)
        {
            Node* nodeDelete = Sukuna_sector[0];
            swap(Sukuna_sector[0], Sukuna_sector[Sukuna_sector.size() - 1]);
            Sukuna_sector.pop_back();
            if (!Sukuna_sector.empty()) {
                reHeapDown(0);
            }
            listDelete.push(nodeDelete);
        }
        Sukuna_sector = areaTableNew;
        while (!listDelete.empty()) {
            Node* nodeDelete = listDelete.front();
            listDelete.pop();

            nodeDelete->remove(NUM);
            int index = 0;
            while (Sukuna_sector[index] != nodeDelete) index++;
            if (nodeDelete->size() == 0)
            {
                swap(Sukuna_sector[index], Sukuna_sector[Sukuna_sector.size() - 1]);
                this->removeNode(Sukuna_sector[Sukuna_sector.size() - 1]);
                delete Sukuna_sector[Sukuna_sector.size() - 1];
                Sukuna_sector.pop_back();
            }
            if (!Sukuna_sector.empty()) {
                reHeapDown(0);
            }
        }
    }
    void print_pre_order(int index, int number)
    {
        int size = Sukuna_sector.size();
        if (index >= size) return;

        this->Sukuna_sector[index]->print(number);
        print_pre_order(index * 2 + 1, number);
        print_pre_order(index * 2 + 2, number);
    }
    void CLEAVE_print(int NUM) {
        if (NUM <= 0) return;
        print_pre_order(0, NUM);
    }
private:
    class Node {
    private:
        int ID;
        list<int>head;
        friend class Sukuna_restaurant;
    public:
        Node(int ID) :ID(ID) {};
        ~Node() {};
        int size()const { return head.size(); }
        void insert(int Result) {
            head.push_front(Result);
        }
        void remove(int NUM) {
            while (NUM != 0 && !head.empty())
            {
                cout << head.back() << "-" << ID << "\n";
                head.pop_back();
                NUM--;
            }
        }
        void print(int number)
        {
            for (list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
            {
                cout << ID << "-" << *it << "\n";
            }
        }
    };
};

class HuffTree_AVL {
private:
    class Node;
private:
    Node* root = nullptr;
public:
    ~HuffTree_AVL() { clear(root); }
    void clear(Node* node) {
        if (node)
        {
            clear(node->left);
            clear(node->right);
            delete node;
            node = nullptr;
        }
    }
    static bool check(pair<char, int>a, pair<char, int>b) {
        if (a.second == b.second) {
            if (isupper(a.first) && islower(b.first)) {
                return true;
            }
            else if (islower(a.first) && isupper(b.first)) {
                return false;
            }
            return a.first > b.first;
        }
        else return a.second > b.second;
    }
    vector<pair<char, int>> string_Processing(string& name) {
        int name_size = name.size();
        map<char, int> freq_map;
        for (int i = 0; i < name_size; i++) {
            freq_map[name[i]] += 1;
        }
        vector<pair<char, int>>result(freq_map.begin(), freq_map.end());
        if (result.size() < 3)return {};
        for (int i = 0; i < name_size; i++) {
            if (isupper(name[i]))
                name[i] = (name[i] + freq_map[name[i]] - 65) % 26 + 65;
            else
                name[i] = (name[i] + freq_map[name[i]] - 97) % 26 + 97;
        }
        int result_size = result.size();
        for (int i = 0; i < result_size; i++) {
            if (isupper(result[i].first)) {
                result[i].first = (result[i].first + result[i].second - 65) % 26 + 65;
            }
            else {
                result[i].first = (result[i].first + result[i].second - 97) % 26 + 97;
            }
        }
        freq_map.clear();
        for (int i = 0; i < result_size; i++) {
            freq_map[result[i].first] += result[i].second;
        }
        result.clear();
        result = vector<pair<char, int>>(freq_map.begin(), freq_map.end());
        sort(result.begin(), result.end(), check);
        return result;
    }
    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + max(height(node->left), height(node->right));
    }
    Node* rotateLeft(Node* subroot)
    {
        Node* rightSucc = subroot->right;
        Node* leftRightSucc = rightSucc->left;

        subroot->right = leftRightSucc;
        rightSucc->left = subroot;

        return rightSucc;
    };
    Node* rotateRight(Node* subroot)
    {
        Node* leftSucc = subroot->left;
        Node* rightLeftSucc = leftSucc->right;

        subroot->left = rightLeftSucc;
        leftSucc->right = subroot;

        return leftSucc;
    };
    int getBalance(Node* subroot) {
        if (!subroot) return 0;
        return height(subroot->left) - height(subroot->right);
    }
    Node* balanceNode(Node* root, int& count)
    {
        if (count >= 3 || !root)return root;
        int balance_root = getBalance(root),
                balance_left = getBalance(root->left),
                balance_right = getBalance(root->right);
        if (root->left && balance_root > 1 && balance_left >= 0) {
            count++;
            return rotateRight(root);
        }
        if (root->left && balance_root > 1 && balance_left < 0) {
            root->left = rotateLeft(root->left);
            count++;
            return rotateRight(root);
        }
        if (root->right && balance_root < -1 && balance_right <= 0) {
            count++;
            return rotateLeft(root);
        }
        if (root->right && balance_root < -1 && balance_right > 0) {
            root->right = rotateRight(root->right);
            count++;
            return rotateLeft(root);
        }
        return root;
    }
    Node* balanceTree(Node* node, int& count)
    {
        if (count == 1 || !node)return node;
        node = balanceNode(node, count);
        node->left = balanceTree(node->left, count);
        node->right = balanceTree(node->right, count);
        return node;
    }
    Node* buildHuff(vector<pair<char, int>> freq)
    {
        vector<Node*> build;
        int freq_size = freq.size();
        for (int i = 0; i < freq_size; i++) {
            Node* newNode = new Node(freq[i].second, freq[i].first);
            build.push_back(newNode);
        }
        while (build.size() > 1)
        {
            int count = 0;
            Node* LWN = build.back();
            build.pop_back();
            Node* ndLWN = build.back();
            build.pop_back();
            Node* newNode = new Node(LWN->weight + ndLWN->weight, '\0', LWN, ndLWN);
            newNode = balanceTree(newNode, count);
            count = 0;
            newNode = balanceTree(newNode, count);
            count = 0;
            newNode = balanceTree(newNode, count);
            int size = build.size();
            int index = -1;
            for (int i = 0; i < size; i++) {
                if (newNode->weight >= build[i]->weight) {
                    build.insert(build.begin() + i, newNode);
                    index = i;
                    break;
                }
            }
            if (index == -1) build.push_back(newNode);
        }
        return build[0];
    }
    void encodingHuffman_rec(vector<string>& encoding, Node* node, string s = "")
    {
        if (node->left)encodingHuffman_rec(encoding, node->left, s + "0");
        if (node->right)encodingHuffman_rec(encoding, node->right, s + "1");
        if (node->isChar())encoding[node->c] = s;
    }
    int encodingHuffman(Node* root, string nameCaesar)
    {
        if (root->left == nullptr && root->right == nullptr) return 0;
        vector<string> encoding(256, "");
        encodingHuffman_rec(encoding, root);
        string newString = "";
        int nameCeasar_size = nameCaesar.size();
        for (int i = 0; i < nameCeasar_size; i++)newString += encoding[nameCaesar[i]];
        reverse(newString.begin(), newString.end());
        int size = newString.size();
        newString = newString.substr(0, min(size, 10));
        int result = stoi(newString, 0, 2);
        return result;
    }
    int encode(string name) {
        vector<pair<char, int>> freq = this->string_Processing(name);
        if (freq.size() == 0)return -1;
        clear(root);
        root = this->buildHuff(freq);
        int result = this->encodingHuffman(root, name);
        if (root->left == nullptr && root->right == nullptr) return 0;
        return result;
    }
    void print_recursive(Node* node) {
        if (node == nullptr) return;
        print_recursive(node->left);
        if (node->c == '\0') cout << node->weight << "\n";
        else cout << node->c << "\n";
        print_recursive(node->right);
    }
    void print()
    {
        print_recursive(root);
    }

private:
    class Node {
    public:
        int weight;
        char c;
        Node* left;
        Node* right;
        friend class HuffTree_AVL;
    public:
        Node(int weight, char c = '\0', Node* left = nullptr, Node* right = nullptr) : weight(weight), c(c), left(left), right(right) {}
        bool isChar() const { return c != '\0'; }
    };
};

class JJK_restaurant {
private:
    GOJO_restaurant BST;
    Sukuna_restaurant Heap;
    HuffTree_AVL new_arrive_guest;
public:
    //-------------------------------Dành cho cả 2 nhà hàng-------------------------------
    void LAPSE(string name)
    {
        int result = new_arrive_guest.encode(name);
        if (result == -1) return;

        if (result % 2 == 1) BST.LAPSE_invite(result);
        else Heap.LAPSE_invite(result);
    }
    void HAND() { new_arrive_guest.print(); }
    //-------------------------------Dành cho nhà hàng GOJO-------------------------------
    void KOKUSEN() {
        BST.KOKUSEN_kick();
    }
    void LIMITLESS(int NUM) {
        BST.LIMITLESS_print(NUM);
    }
    //-------------------------------Dành cho nhà hàng SUKUNA------------------------------
    void KEITEIKEN(int NUM) {
        Heap.KEITEIKEN_kick(NUM);
    }
    void CLEAVE(int NUM) {
        Heap.CLEAVE_print(NUM);
    }
};

void simulate(string filename)
{
    ifstream ss(filename);
    string str, name;
    int num;

    ss >> str; ss >> MAX_SIZE;

    JJK_restaurant* restaurant = new JJK_restaurant();
    while (ss >> str)
    {
        if (str == "LAPSE")
        {
            ss >> name;
            restaurant->LAPSE(name);
        }
        else if (str == "KOKUSEN")
        {
            restaurant->KOKUSEN();
        }
        else if (str == "KEITEIKEN")
        {
            ss >> num;
            restaurant->KEITEIKEN(num);
        }
        else if (str == "HAND")
        {
            restaurant->HAND();
        }
        else if (str == "LIMITLESS")
        {
            ss >> num;
            restaurant->LIMITLESS(num);
        }
        else if (str == "CLEAVE")
        {
            ss >> num;
            restaurant->CLEAVE(num);
        }
    }
    delete restaurant;
}