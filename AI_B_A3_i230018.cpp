#include <iostream>

using namespace std;

class Game
{
public:
    string gameId;
    string name;
    string developer;
    string publisher;
    float file_size_in_GB;
    int downloads;

    Game() {}

    Game(string _gameId, string _name, string _developer, string _publisher, float _file_size_in_GB, int _downloads)
    {
        gameId = _gameId;
        name = _name;
        developer = _developer;
        publisher = _publisher;
        file_size_in_GB = _file_size_in_GB;
        downloads = _downloads;
    }
};

class Game_Played
{
    class Node
    {
    public:
        Game game;
        float hours_played;
        int achievements_unlocked;

        int height;
        Node *right;
        Node *left;

        Node()
        {
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

    int height(Node *node)
    {
        return (node ? node->height : -1);
    }

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

    Node *rotateRightLeft(Node *node)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    Node *rotateLeftRight(Node *node)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    Node *insert(Node *node, Game game, float hours_played, int achievements_unlocked)
    {
        if (node == nullptr)
        {
            node = new Node;
            node->game = game;
            node->hours_played = hours_played;
            node->achievements_unlocked = achievements_unlocked;
            node->height = 0;
            return node;
        }

        if (isGreater(node->game.gameId, game.gameId))
            node->left = insert(node->left, game, hours_played, achievements_unlocked);
        else if (isGreater(game.gameId, node->game.gameId))
            node->right = insert(node->right, game, hours_played, achievements_unlocked);

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

public:
    Game_Played()
    {
        root = NULL;
    }

    Node *getRoot()
    {
        return root;
    }

    void insert(Game game, float hours_played, int achievements_unlocked)
    {
        root = insert(root, game, hours_played, achievements_unlocked);
    }

    void print(Node *node)
    {
        if (node == NULL)
            return;
        print(node->left);
        cout << "Game ID: " << node->game.gameId << endl
             << "Game Name: " << node->game.name << endl
             << "Game Develepor: " << node->game.developer << endl
             << "Game Publisher: " << node->game.publisher << endl
             << "Game Size: " << node->game.file_size_in_GB << " GB" << endl
             << "Downloads: " << node->game.downloads << endl
             << "Hours Played: " << node->hours_played << endl
             << "Achievements Earned: " << node->achievements_unlocked << endl
             << "Height: " << node->height << endl;
        cout << endl;
        print(node->right);
    }
};

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

    int height(Node *node)
    {
        return (node ? node->height : -1);
    }

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

    Node *rotateRightLeft(Node *node)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    Node *rotateLeftRight(Node *node)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

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
            node->right = insert(node->left, _playerId, _name, _phnNo, _email, _password);

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

public:
    Player()
    {
        root = NULL;
    }

    Node *getRoot()
    {
        return root;
    }

    void insert(string playerId, string name, string phnNo, string email, string password)
    {
        root = insert(root, playerId, name, phnNo, email, password);
    }

    Node *insertGame(Node *node, string playerId, Game game, float hours_played, int achievements_unlocked)
    {
        if (node == nullptr)
            return nullptr;

        if (node->playerId == playerId)
            node->games.insert(game, hours_played, achievements_unlocked);

        if (isGreater(node->playerId, playerId))
            node->left = insertGame(node->left, playerId, game, hours_played, achievements_unlocked);
        else if (isGreater(playerId, node->playerId))
            node->right = insertGame(node->right, playerId, game, hours_played, achievements_unlocked);

        return node;
    }

    void print(Node *node)
    {
        if (node == nullptr)
            return;

        print(node->left);
        cout << node->playerId << " - " << node->name << endl;
        node->games.print(node->games.getRoot());
        print(node->right);
    }
};

int main()
{
    Player player;

    player.insert("P12345", "Player 1", "1234567890", "player1@email.com", "password1");
    player.insertGame(player.getRoot(), "P12345", Game("1", "a", "a", "a", 1, 1), 2.5, 50);
    player.insertGame(player.getRoot(), "P12345", Game("2", "b", "b", "b", 1, 1), 3.0, 60);
    player.insertGame(player.getRoot(), "P12345", Game("3", "c", "c", "c", 1, 1), 1.5, 40);

    player.insert("P12346", "Player 2", "1234567890", "player2@email.com", "password2");
    player.insertGame(player.getRoot(), "P12346", Game("4", "d", "d", "d", 1, 1), 4.0, 70);
    player.insertGame(player.getRoot(), "P12346", Game("5", "e", "e", "e", 1, 1), 2.0, 55);
    player.insertGame(player.getRoot(), "P12346", Game("6", "f", "f", "f", 1, 1), 3.5, 65);

    player.print(player.getRoot());

    return 0;
}