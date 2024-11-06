// Rayan Ahmed
// 23i-0018
// Assignment 03

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Implements the game tree structure
class Game
{
public:
    class Node
    {
    public:
        string gameId;
        string name;
        string developer;
        string publisher;
        float file_size_in_GB;
        int downloads;

        int height;
        Node *right;
        Node *left;

        Node()
        {
            gameId = "";
            name = "";
            developer = "";
            publisher = "";
            file_size_in_GB = 0.0;
            downloads = 0;
            height = 0;
            right = nullptr;
            left = nullptr;
        }

        Node(string _gameId, string _name, string _developer, string _publisher, float _file_size_in_GB, int _downloads)
        {
            gameId = _gameId;
            name = _name;
            developer = _developer;
            publisher = _publisher;
            file_size_in_GB = _file_size_in_GB;
            downloads = _downloads;
            height = 0;
            right = nullptr;
            left = nullptr;
        }
    };

private:
    Node *root;

    // Returns if the number stored in string form is greater than the other
    bool isGreater(string str1, string str2)
    {
        int len1 = 0;
        int len2 = 0;

        for (int i = 0; str1[i] != '\0'; i++)
            len1++;
        for (int i = 0; str2[i] != '\0'; i++)
            len2++;

        if (len1 > len2)
            return true;
        else if (len1 < len2)
            return false;

        for (int i = 0; i < len1; i++)
            if (str1[i] > str2[i])
                return true;
            else if (str1[i] < str2[i])
                return false;

        return false;
    }

    // Returns the height of the node
    int height(Node *node)
    {
        return (node ? node->height : -1);
    }

    // Applies a right rotation to the node and returns the new root node of the subtree
    Node *rotateRight(Node *node)
    {
        Node *leftChild = node->left;
        Node *rightChild = leftChild->right;

        leftChild->right = node;
        node->left = rightChild;

        node->height = max(height(node->left), height(node->right)) + 1;
        leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;

        return leftChild;
    }

    // Applies a left rotation to the node and returns the new root node of the subtree
    Node *rotateLeft(Node *node)
    {
        Node *rightChild = node->right;
        Node *leftChild = rightChild->left;

        rightChild->left = node;
        node->right = leftChild;

        node->height = max(height(node->left), height(node->right)) + 1;
        rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;

        return rightChild;
    }

    // Applies a right-left rotation to the node and returns the new root node of the subtree
    Node *rotateRightLeft(Node *node)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Applies a left-right rotation to the node and returns the new root node of the subtree
    Node *rotateLeftRight(Node *node)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Inserts a node into the tree and returns the new root node of the subtree
    Node *insert(Node *node, string _gameId, string _name, string _developer, string _publisher, float _file_size_in_GB, int _downloads)
    {
        if (node == nullptr)
        {
            node = new Node;
            node->gameId = _gameId;
            node->name = _name;
            node->developer = _developer;
            node->publisher = _publisher;
            node->file_size_in_GB = _file_size_in_GB;
            node->downloads = _downloads;

            node->height = 0;
            return node;
        }

        if (isGreater(node->gameId, _gameId))
            node->left = insert(node->left, _gameId, _name, _developer, _publisher, _file_size_in_GB, _downloads);
        else if (isGreater(_gameId, node->gameId))
            node->right = insert(node->right, _gameId, _name, _developer, _publisher, _file_size_in_GB, _downloads);

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = height(node->left) - height(node->right);

        // Balance the tree if it becomes unbalanced
        if (balance > 1)
        {
            // Left Left Case
            if (height(node->left->left) - height(node->left->right) >= 0)
                return rotateRight(node);

            // Left Right Case
            else
                return rotateLeftRight(node);
        }
        if (balance < -1)
        {
            // Right Right Case
            if (height(node->right->right) - height(node->right->left) >= 0)
                return rotateLeft(node);

            // Right Left Case
            else
                return rotateRightLeft(node);
        }

        return node;
    }

    // Returns the minimum value in a tree
    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node *deleteNode(Node *node, string gameId, Node *updatedNode = nullptr)
    {
        if (node == nullptr)
            return node;

        if (isGreater(node->gameId, gameId))
            node->left = deleteNode(node->left, gameId, updatedNode);
        else if (isGreater(gameId, node->gameId))
            node->right = deleteNode(node->right, gameId, updatedNode);
        else
        {
            if (updatedNode != nullptr)
            {
                // Instead of deleting, directly update the node's data
                node->gameId = updatedNode->gameId != "" ? updatedNode->gameId : node->gameId;
                node->name = updatedNode->name != "" ? updatedNode->name : node->name;
                node->developer = updatedNode->developer != "" ? updatedNode->developer : node->developer;
                node->publisher = updatedNode->publisher != "" ? updatedNode->publisher : node->publisher;
                node->file_size_in_GB = updatedNode->file_size_in_GB != -1.0f ? updatedNode->file_size_in_GB : node->file_size_in_GB;
                node->downloads = updatedNode->downloads != -1 ? updatedNode->downloads : node->downloads;
                return node;
            }

            // If we're not updating, perform the actual deletion process
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                node = nullptr;
                return node;
            }
            else if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            Node *temp = minValueNode(node->right);
            node->gameId = temp->gameId;
            node->name = temp->name;
            node->developer = temp->developer;
            node->publisher = temp->publisher;
            node->file_size_in_GB = temp->file_size_in_GB;
            node->downloads = temp->downloads;
            node->right = deleteNode(node->right, temp->gameId);
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = height(node->left) - height(node->right);

        // Balance the tree if it becomes unbalanced
        if (balance > 1)
        {
            if (height(node->left->left) - height(node->left->right) >= 0)
                return rotateRight(node);
            else
                return rotateLeftRight(node);
        }
        if (balance < -1)
        {
            if (height(node->right->right) - height(node->right->left) >= 0)
                return rotateLeft(node);
            else
                return rotateRightLeft(node);
        }

        return node;
    }

    // Prints the tree in order
    void print(Node *node)
    {
        if (node == NULL)
            return;
        print(node->left);
        cout << "Game ID: " << node->gameId << endl
             << "Game Name: " << node->name << endl
             << "Game Develepor: " << node->developer << endl
             << "Game Publisher: " << node->publisher << endl
             << "Game File Size: " << node->file_size_in_GB << " GB" << endl
             << "Downloads: " << node->downloads << endl
             << endl;
        cout << endl;
        print(node->right);
    }

public:
    Game()
    {
        root = NULL;
    }

    // Returns the root node of the tree
    Node *getRoot()
    {
        return root;
    }

    // Inserts a node into the tree
    void insert(string gameId, string name, string developer, string publisher, float file_size_in_GB, int downloads)
    {
        root = insert(root, gameId, name, developer, publisher, file_size_in_GB, downloads);
    }

    // Delete a player from the tree
    void deleteNode(string gameId)
    {
        root = deleteNode(root, gameId);
    }

    // Update the information of the game
    void updateGame(string _gameId, Node *updatedNode)
    {
        if (_gameId != updatedNode->gameId)
        {
            Node *game = get_game(_gameId);
            if (game == nullptr)
                throw out_of_range("Invalid Game Id!");

            updatedNode->name = updatedNode->name == "" ? game->name : updatedNode->name;
            updatedNode->developer = updatedNode->developer == "" ? game->developer : updatedNode->developer;
            updatedNode->publisher = updatedNode->publisher == "" ? game->publisher : updatedNode->publisher;
            updatedNode->file_size_in_GB = updatedNode->file_size_in_GB == -1.0f ? game->file_size_in_GB : updatedNode->file_size_in_GB;
            updatedNode->downloads = updatedNode->downloads == -1 ? game->downloads : updatedNode->downloads;

            root = deleteNode(root, _gameId);
            root = insert(root, updatedNode->gameId, updatedNode->name, updatedNode->developer, updatedNode->publisher, updatedNode->file_size_in_GB, updatedNode->downloads);
        }
        else
            root = deleteNode(root, _gameId, updatedNode);
    }

    Node *get_game(string _gameId)
    {
        Node *node = root;

        while (node != NULL)
        {
            if (node->gameId == _gameId)
                return node;
            else if (isGreater(node->gameId, _gameId))
                node = node->left;
            else
                node = node->right;
        }

        throw out_of_range("Invalid Game Id!");
    }

    // Prints the tree in order
    void print()
    {
        print(root);
    }
};

// Implements the game played tree structure
class Game_Played
{
public:
    class Node
    {
    public:
        string gameId;
        float hours_played;
        int achievements_unlocked;

        int height;
        Node *right;
        Node *left;

        Node()
        {
            gameId = "";
            hours_played = 0.0;
            achievements_unlocked = 0;
            right = NULL;
            left = NULL;
            height = 0;
        }

        Node(string _gameId, float _hours_played, int _achievements_unlocked)
        {
            gameId = _gameId;
            hours_played = _hours_played;
            achievements_unlocked = _achievements_unlocked;
            right = NULL;
            left = NULL;
            height = 0;
        }
    };

private:
    Node *root;

    // Returns if the number stored in string form is greater than the other
    bool isGreater(string str1, string str2)
    {
        int len1 = 0;
        int len2 = 0;

        for (int i = 0; str1[i] != '\0'; i++)
            len1++;
        for (int i = 0; str2[i] != '\0'; i++)
            len2++;

        if (len1 > len2)
            return true;
        else if (len1 < len2)
            return false;

        for (int i = 0; i < len1; i++)
            if (str1[i] > str2[i])
                return true;
            else if (str1[i] < str2[i])
                return false;

        return false;
    }

    // Returns the height of the node
    int height(Node *node)
    {
        return (node ? node->height : -1);
    }

    // Applies a right rotation to the node and returns the new root node of the subtree
    Node *rotateRight(Node *node)
    {
        Node *leftChild = node->left;
        Node *rightChild = leftChild->right;

        leftChild->right = node;
        node->left = rightChild;

        node->height = max(height(node->left), height(node->right)) + 1;
        leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;

        return leftChild;
    }

    // Applies a left rotation to the node and returns the new root node of the subtree
    Node *rotateLeft(Node *node)
    {
        Node *rightChild = node->right;
        Node *leftChild = rightChild->left;

        rightChild->left = node;
        node->right = leftChild;

        node->height = max(height(node->left), height(node->right)) + 1;
        rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;

        return rightChild;
    }

    // Applies a right-left rotation to the node and returns the new root node of the subtree
    Node *rotateRightLeft(Node *node)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Applies a left-right rotation to the node and returns the new root node of the subtree
    Node *rotateLeftRight(Node *node)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Inserts a node into the tree and returns the new root node of the subtree
    Node *insert(Node *node, string _gameId, float hours_played, int achievements_unlocked)
    {
        if (node == nullptr)
        {
            node = new Node;
            node->gameId = _gameId;
            node->hours_played = hours_played;
            node->achievements_unlocked = achievements_unlocked;
            node->height = 0;
            return node;
        }

        if (isGreater(node->gameId, _gameId))
            node->left = insert(node->left, _gameId, hours_played, achievements_unlocked);
        else if (isGreater(_gameId, node->gameId))
            node->right = insert(node->right, _gameId, hours_played, achievements_unlocked);
        else
            throw invalid_argument("Cannot insert duplicate game"); // Throw exception when trying to insert duplicate player

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = height(node->left) - height(node->right);

        // Balance the tree if it becomes unbalanced
        if (balance > 1)
        {
            // Left Left Case
            if (height(node->left->left) - height(node->left->right) >= 0)
                return rotateRight(node);

            // Left Right Case
            else
                return rotateLeftRight(node);
        }
        if (balance < -1)
        {
            // Right Right Case
            if (height(node->right->right) - height(node->right->left) >= 0)
                return rotateLeft(node);

            // Right Left Case
            else
                return rotateRightLeft(node);
        }

        return node;
    }

    // Returns the minimum value in a tree
    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node *deleteNode(Node *node, string gameId, Node *updatedNode = nullptr)
    {
        if (node == nullptr)
            return node;

        if (isGreater(node->gameId, gameId))
            node->left = deleteNode(node->left, gameId, updatedNode);
        else if (isGreater(gameId, node->gameId))
            node->right = deleteNode(node->right, gameId, updatedNode);
        else
        {
            if (updatedNode != nullptr)
            {
                // Instead of deleting, directly update the node's data
                node->gameId = updatedNode->gameId != "" ? updatedNode->gameId : node->gameId;
                node->hours_played = updatedNode->hours_played != -1.0f ? updatedNode->hours_played : node->hours_played;
                node->achievements_unlocked = updatedNode->achievements_unlocked != -1 ? updatedNode->achievements_unlocked : node->achievements_unlocked;
                return node;
            }

            // If we're not updating, perform the actual deletion process
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                node = nullptr;
                return node;
            }
            else if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            Node *temp = minValueNode(node->right);
            node->gameId = temp->gameId;
            node->hours_played = updatedNode->hours_played;
            node->achievements_unlocked = updatedNode->achievements_unlocked;
            node->right = deleteNode(node->right, temp->gameId);
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = height(node->left) - height(node->right);

        // Balance the tree if it becomes unbalanced
        if (balance > 1)
        {
            if (height(node->left->left) - height(node->left->right) >= 0)
                return rotateRight(node);
            else
                return rotateLeftRight(node);
        }
        if (balance < -1)
        {
            if (height(node->right->right) - height(node->right->left) >= 0)
                return rotateLeft(node);
            else
                return rotateRightLeft(node);
        }

        return node;
    }

    // Prints the tree in order
    void print(Node *node)
    {
        if (node == NULL)
            return;
        print(node->left);
        cout << "Game ID: " << node->gameId << endl
             << "Hours Played: " << node->hours_played << endl
             << "Achievements Earned: " << node->achievements_unlocked << endl
             << "Height: " << node->height << endl;
        cout << endl;
        print(node->right);
    }

public:
    Game_Played()
    {
        root = NULL;
    }

    // Returns the root node of the tree
    Node *getRoot()
    {
        return root;
    }

    // Inserts a node into the tree
    void insert(string gameId, float hours_played, int achievements_unlocked)
    {
        root = insert(root, gameId, hours_played, achievements_unlocked);
    }

    // Delete a game from the tree
    void deleteGame(string gameId)
    {
        root = deleteNode(root, gameId);
    }

    // Update the information of the game
    void updateGame(string _gameId, Node *updatedNode)
    {
        if (_gameId != updatedNode->gameId)
        {
            Node *game = get_game(_gameId);
            updatedNode->hours_played = updatedNode->hours_played == -1.0f ? game->hours_played : updatedNode->hours_played;
            updatedNode->achievements_unlocked = updatedNode->achievements_unlocked == -1 ? game->achievements_unlocked : updatedNode->achievements_unlocked;

            root = deleteNode(root, _gameId);
            root = insert(root, updatedNode->gameId, updatedNode->hours_played, updatedNode->achievements_unlocked);
        }
        else
            root = deleteNode(root, _gameId, updatedNode);
    }

    // Returns the game with the given game id
    Node *get_game(string gameId)
    {
        Node *node = root;

        while (node != nullptr)
        {
            if (isGreater(node->gameId, gameId))
                node = node->left;
            else if (isGreater(gameId, node->gameId))
                node = node->right;
            else
                return node;
        }

        throw out_of_range("Invalid Game Id!");
    }

    // Prints the tree in order
    void print()
    {
        print(root);
    }
};

// Implements the player tree structure
class Player
{
public:
    class Node
    {
    public:
        string name;
        string playerId;
        string phnNo;
        string email;
        string password;
        Game_Played games;

        Node *left;
        Node *right;
        int height;

        Node()
        {
            name = "";
            playerId = "";
            phnNo = "";
            email = "";
            password = "";
            left = NULL;
            right = NULL;
            height = 0;
        }

        Node(string _name, string _playerId, string _phnNo, string _email, string _password)
        {
            name = _name;
            playerId = _playerId;
            phnNo = _phnNo;
            email = _email;
            password = _password;
            left = NULL;
            right = NULL;
            height = 0;
        }
    };

private:
    Node *root;

    // Returns if the number stored in string form is greater than the other
    bool isGreater(string str1, string str2)
    {
        int len1 = 0;
        int len2 = 0;

        for (int i = 0; str1[i] != '\0'; i++)
            len1++;
        for (int i = 0; str2[i] != '\0'; i++)
            len2++;

        if (len1 > len2)
            return true;
        else if (len1 < len2)
            return false;

        for (int i = 0; i < len1; i++)
            if (str1[i] > str2[i])
                return true;
            else if (str1[i] < str2[i])
                return false;

        return false;
    }

    // Returns the height of the node
    int height(Node *node)
    {
        return (node ? node->height : -1);
    }

    // Applies a right rotation to the node and returns the new root node of the subtree
    Node *rotateRight(Node *node)
    {
        Node *leftChild = node->left;
        Node *rightChild = leftChild->right;

        leftChild->right = node;
        node->left = rightChild;

        node->height = max(height(node->left), height(node->right)) + 1;
        leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;

        return leftChild;
    }

    // Applies a left rotation to the node and returns the new root node of the subtree
    Node *rotateLeft(Node *node)
    {
        Node *rightChild = node->right;
        Node *leftChild = rightChild->left;

        rightChild->left = node;
        node->right = leftChild;

        node->height = max(height(node->left), height(node->right)) + 1;
        rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;

        return rightChild;
    }

    // Applies a right-left rotation to the node and returns the new root node of the subtree
    Node *rotateRightLeft(Node *node)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Applies a left-right rotation to the node and returns the new root node of the subtree
    Node *rotateLeftRight(Node *node)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Inserts a node into the tree and returns the new root node of the subtree
    Node *insert(Node *node, string _playerId, string _name, string _phnNo, string _email, string _password)
    {
        if (node == nullptr)
        {
            node = new Node;
            node->playerId = _playerId;
            node->name = _name;
            node->phnNo = _phnNo;
            node->email = _email;
            node->password = _password;
            node->height = 0;
            return node;
        }

        if (isGreater(node->playerId, _playerId))
            node->left = insert(node->left, _playerId, _name, _phnNo, _email, _password);
        else if (isGreater(_playerId, node->playerId))
            node->right = insert(node->right, _playerId, _name, _phnNo, _email, _password);
        else
            throw invalid_argument("Cannot insert duplicate player"); // Throw exception when trying to insert duplicate player

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = height(node->left) - height(node->right);

        // Balance the tree if it becomes unbalanced
        if (balance > 1)
        {
            // Left Left Case
            if (height(node->left->left) - height(node->left->right) >= 0)
                return rotateRight(node);

            // Left Right Case
            else
                return rotateLeftRight(node);
        }
        if (balance < -1)
        {
            // Right Right Case
            if (height(node->right->right) - height(node->right->left) >= 0)
                return rotateLeft(node);

            // Right Left Case
            else
                return rotateRightLeft(node);
        }

        return node;
    }

    // Inserts a game in a player's games list
    Node *insertGame(Node *node, string playerId, string gameId, float hours_played, int achievements_unlocked)
    {
        if (node == nullptr)
            return nullptr;

        if (node->playerId == playerId)
            node->games.insert(gameId, hours_played, achievements_unlocked);

        if (isGreater(node->playerId, playerId))
            node->left = insertGame(node->left, playerId, gameId, hours_played, achievements_unlocked);
        else if (isGreater(playerId, node->playerId))
            node->right = insertGame(node->right, playerId, gameId, hours_played, achievements_unlocked);

        return node;
    }

    // Returns the minimum value in a tree
    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Delete a node from the tree
    Node *deleteNode(Node *node, string playerId, Node *updatedNode = nullptr)
    {
        if (node == nullptr)
            return node;

        if (isGreater(node->playerId, playerId))
            node->left = deleteNode(node->left, playerId, updatedNode);
        else if (isGreater(playerId, node->playerId))
            node->right = deleteNode(node->right, playerId, updatedNode);
        else
        {
            if (updatedNode != nullptr)
            {
                // Instead of deleting, directly update the node's data
                node->playerId = updatedNode->playerId != "" ? updatedNode->playerId : node->playerId;
                node->name = updatedNode->name != "" ? updatedNode->name : node->name;
                node->phnNo = updatedNode->phnNo != "" ? updatedNode->phnNo : node->phnNo;
                node->email = updatedNode->email != "" ? updatedNode->email : node->email;
                node->password = updatedNode->password != "" ? updatedNode->password : node->password;
                return node;
            }

            // If we're not updating, perform the actual deletion process
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                node = nullptr;
                return node;
            }
            else if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            Node *temp = minValueNode(node->right);
            node->playerId = temp->playerId;
            node->name = temp->name;
            node->phnNo = temp->phnNo;
            node->email = temp->email;
            node->password = temp->password;
            node->right = deleteNode(node->right, temp->playerId);
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = height(node->left) - height(node->right);

        // Balance the tree if it becomes unbalanced
        if (balance > 1)
        {
            if (height(node->left->left) - height(node->left->right) >= 0)
                return rotateRight(node);
            else
                return rotateLeftRight(node);
        }
        if (balance < -1)
        {
            if (height(node->right->right) - height(node->right->left) >= 0)
                return rotateLeft(node);
            else
                return rotateRightLeft(node);
        }

        return node;
    }

    // Prints the tree in order
    void print(Node *node)
    {
        if (node == nullptr)
            return;

        print(node->left);
        cout << node->playerId << " - " << node->name << endl;
        // node->games.print();
        print(node->right);
    }

public:
    Player()
    {
        root = NULL;
    }

    // Returns the root node of the tree
    Node *getRoot()
    {
        return root;
    }

    // Returns the height of the tree
    int getHeight()
    {
        return height(root);
    }

    // Inserts a node into the tree
    void insert(string playerId, string name, string phnNo, string email, string password)
    {
        root = insert(root, playerId, name, phnNo, email, password);
    }

    // Insert a new game in player's game list
    void insertGame(string playerId, string gameId, float hours_played, int achievements_unlocked)
    {
        root = insertGame(root, playerId, gameId, hours_played, achievements_unlocked);
    }

    // Delete a player from the tree
    void deletePlayer(string playerId)
    {
        root = deleteNode(root, playerId);
    }

    // Update the information of the player
    void updatePlayer(string _playerId, Node *updatedNode)
    {
        if (_playerId != updatedNode->playerId && updatedNode->playerId != "")
        {
            Node *player = get_player(_playerId);
            updatedNode->name = updatedNode->name == "" ? player->name : updatedNode->name;
            updatedNode->phnNo = updatedNode->phnNo == "" ? player->phnNo : updatedNode->phnNo;
            updatedNode->email = updatedNode->email == "" ? player->email : updatedNode->email;
            updatedNode->password = updatedNode->password == "" ? player->password : updatedNode->password;

            root = deleteNode(root, _playerId);
            root = insert(root, updatedNode->playerId, updatedNode->name, updatedNode->phnNo, updatedNode->email, updatedNode->password);
        }
        else
            root = deleteNode(root, _playerId, updatedNode);
    }

    // Returns the player with the given player id
    Node *get_player(string _playerId)
    {
        Node *node = root;

        while (node)
        {
            if (node->playerId == _playerId)
                return node;
            else if (isGreater(node->playerId, _playerId))
                node = node->left;
            else
                node = node->right;
        }

        throw out_of_range("Invalid Player Id!");
    }

    // Prints the tree in order
    void print()
    {
        print(root);
    }
};

// Returns the length of the string
int len(string str)
{
    int len = 0;
    for (int i = 0; str[i] != '\0'; i++)
        len++;
    return len;
}

// Converts the string to float
float toFloat(string str)
{
    float result = 0.0f;
    float decimalPlace = 1.0f;
    bool hasDecimal = false;

    for (int i = 0; i < len(str); i++)
    {
        if (str[i] == '.')
        {
            hasDecimal = true;
            continue;
        }
        if (hasDecimal)
        {
            decimalPlace *= 0.1f;
            result += (str[i] - '0') * decimalPlace;
        }
        else
            result = result * 10.0f + (str[i] - '0');
    }
    return result;
}

// Converts the string to integer
int toInt(string str)
{
    int result = 0;
    for (int i = 0; i < len(str); i++)
        result = result * 10 + (str[i] - '0');
    return result;
}

// Loads the data from the Players.txt file into the tree
void load_player(Player &player)
{
    int BATCH = 230018;
    srand(BATCH);

    int THRESHOLD = (BATCH % 100) * 10 + 100;

    ifstream file("hello.txt");

    // Read each line from the file
    string line = "";
    while (getline(file, line))
    {
        string playerData[5];
        int i = 0;
        int j = 0;

        int randomNumber = rand() % 1000;
        if (randomNumber < THRESHOLD)
            continue;

        // Read and store information of player
        for (j = 0; i < 5; j++)
        {
            if (line[j] == ',')
            {
                i++;
                continue;
            }
            playerData[i] += line[j];
        }

        // Insert a new player
        player.insert(playerData[0], playerData[1], playerData[2], playerData[3], playerData[4]);

        string game_data[3];
        i = 0;

        // Read and store information of games
        while (j < len(line))
        {
            if (line[j] == ',')
            {
                i++;
                j++;
                continue;
            }
            if (i == 3)
            {
                // Insert a new game into the player's games list
                player.insertGame(playerData[0], game_data[0], toFloat(game_data[1]), toInt(game_data[2]));
                i = 0;
                game_data[0] = "";
                game_data[1] = "";
                game_data[2] = "";
            }
            game_data[i] += line[j];
            j++;
        }
    }
}

// Loads the data from the Games.txt to the game tree
void load_games(Game &game)
{
    int BATCH = 230018;
    srand(BATCH);

    int THRESHOLD = (BATCH % 100) * 10 + 100;

    ifstream file("Games.txt");

    // Read each line from the file
    string line = "";
    while (getline(file, line))
    {
        string gameData[6];
        int i = 0;
        int j = 0;

        int randomNumber = rand() % 1000;
        if (randomNumber < THRESHOLD)
            continue;

        // Read and store information of games
        while (j < len(line))
        {
            if (line[j] == ',')
            {
                i++;
                j++;
                continue;
            }
            gameData[i] += line[j];
            j++;
        }

        // // Insert a new game
        game.insert(gameData[0], gameData[1], gameData[2], gameData[3], toFloat(gameData[4]), toInt(gameData[5]));
    }
}

int main()
{
    Player player;
    Game game;

    load_player(player);
    // load_games(game);

    player.print();
    // game.print();
    cout << endl;
    
    Player::Node *updatedNode = new Player::Node("Yango", "9675812504", "0323", "ra33286", "ra990");
    player.updatePlayer("4973616414", updatedNode);
    player.print();
    
    // Game::Node *updatedNode = new Game::Node("2301982", "Tango", "Yellow", "Green", 15.678, 120);
    // game.updateGame("9410009774", updatedNode);
    // game.print();

    return 0;
}