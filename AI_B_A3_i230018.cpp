#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Implements the game tree structure
class Game
{
private:
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
    };
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

    // Prints the tree in order
    void print()
    {
        print(root);
    }
};

// Implements the game played tree structure
class Game_Played
{
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
    };
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

    // Prints the tree in order
    void print()
    {
        print(root);
    }
};

// Implements the player tree structure
class Player
{
private:
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
    };
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

    int getHeight()
    {
        return height(root);
    }

    // Inserts a node into the tree
    void insert(string playerId, string name, string phnNo, string email, string password)
    {
        root = insert(root, playerId, name, phnNo, email, password);
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

    ifstream file("Players.txt");

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
                player.insertGame(player.getRoot(), playerData[0], game_data[0], toFloat(game_data[1]), toInt(game_data[2]));
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
        // cout << ".";
    }
}

int main()
{
    Player player;
    Game game;

    load_player(player);
    load_games(game);
    // player.print();
    // game.print();


    return 0;
}