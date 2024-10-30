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

    Node *insert(Node *node, Game game, float hours_played, int achievements_unlocked)
    {
        if (node == NULL)
        {
            Node *newNode = new Node;
            newNode->game = game;
            newNode->hours_played = hours_played;
            newNode->achievements_unlocked = achievements_unlocked;
            newNode->height = 1;
            return newNode;
        }
        if (isGreater(node->game.gameId, game.gameId))
            node->left = insert(node->left, game, hours_played, achievements_unlocked);
        else if (isGreater(game.gameId, node->game.gameId))
            node->right = insert(node->right, game, hours_played, achievements_unlocked);

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
        cout << node->game.gameId << " " << node->game.name << " " << node->game.developer << " " << node->game.publisher << " " << node->game.file_size_in_GB << " " << node->game.downloads << " " << node->hours_played << " " << node->achievements_unlocked << endl;
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