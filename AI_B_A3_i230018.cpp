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

    int Height(Node *node)
    {
        return (node ? node->height : -1);
    }

    Node *rotateRight(Node *node)
    {
        Node *leftChild = node->left;
        Node *rightChild = leftChild->right;

        leftChild->right = node;
        node->left = rightChild;

        node->height = max(Height(node->left), Height(node->right)) + 1;
        leftChild->height = max(Height(leftChild->left), Height(leftChild->right)) + 1;

        return leftChild;
    }

    Node *rotateLeft(Node *node)
    {
        Node *rightChild = node->right;
        Node *leftChild = rightChild->left;

        rightChild->left = node;
        node->right = leftChild;

        node->height = max(Height(node->left), Height(node->right)) + 1;
        rightChild->height = max(Height(rightChild->left), Height(rightChild->right)) + 1;

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

        node->height = 1 + max(Height(node->left), Height(node->right));

        int balance = Height(node->left) - Height(node->right);

        // Balance the tree if it becomes unbalanced
        if (balance > 1)
        {
            // Left Left Case
            if (Height(node->left->left) - Height(node->left->right) >= 0)
                return rotateRight(node);

            // Left Right Case
            else
                return rotateLeftRight(node);
        }
        if (balance < -1)
        {
            // Right Right Case
            if (Height(node->right->right) - Height(node->right->left) >= 0)
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
        cout << endl;
        cout << "Game ID: " << node->game.gameId << endl
             << "Game Name: " << node->game.name << endl
             << "Game Develepor: " << node->game.developer << endl
             << "Game Publisher: " << node->game.publisher << endl
             << "Game Size: " << node->game.file_size_in_GB << " GB" << endl
             << "Downloads: " << node->game.downloads << endl
             << "Hours Played: " << node->hours_played << endl
             << "Achievements Earned: " << node->achievements_unlocked << endl
             << "Height: " << node->height << endl;
        print(node->right);
    }
};

int main()
{
    Game_Played game;

    game.insert(Game("1", "a", "a", "a", 1, 1), 1, 1);
    game.insert(Game("2", "b", "b", "b", 2, 2), 2, 2);
    game.insert(Game("3", "c", "c", "c", 3, 3), 3, 3);
    game.insert(Game("10", "d", "d", "d", 4, 4), 4, 4);
    game.insert(Game("5", "e", "e", "e", 5, 5), 5, 5);

    game.print(game.getRoot());

    return 0;
}