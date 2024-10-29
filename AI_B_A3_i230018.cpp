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

    Game(string gameId, string name, string developer, string publisher, float file_size_in_GB, int downloads)
    {
        this->gameId = gameId;
        this->name = name;
        this->developer = developer;
        this->publisher = publisher;
        this->file_size_in_GB = file_size_in_GB;
        this->downloads = downloads;
    }
};

class Game_Played
{
private:
    struct Node
    {
        Game game;
        float hours_played;
        int achievements_unlocked;

        int height;
        Node *right;
        Node *left;
    };
    Node *root;

    /**
     * @brief Performs a right rotation on a node in the binary search tree.
     * This function is used to balance the tree after an insertion or deletion operation.
     * @param node The node to perform the rotation on.
     * @return The new root node after the rotation.
     */
    Node *rightRotate(Node *node)
    {
        Node *new_root = node->left;
        node->left = new_root->right;
        new_root->right = node;
    }

    /**
     * @brief Performs a left rotation on a node in the binary search tree.
     * This function is used to balance the tree after an insertion or deletion operation.
     * @param node The node to perform the rotation on.
     * @return The new root node after the rotation.
     */
    Node *leftRotate(Node *node)
    {
        Node *new_root = node->right;
        node->right = new_root->left;
        new_root->left = node;
    }

    /**
     * @brief Performs a left-right rotation on a node in the binary search tree.
     * This function is used to balance the tree after an insertion or deletion operation.
     * @param node The node to perform the rotation on.
     * @return The new root node after the rotation.
     */
    Node *leftRightRotate(Node *node)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    /**
     * @brief Performs a right-left rotation on a node in the binary search tree.
     * This function is used to balance the tree after an insertion or deletion operation.
     * @param node The node to perform the rotation on.
     * @return The new root node after the rotation.
     */
    Node *rightLeftRotate(Node *node)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

public:
    Game_Played()
    {
        root = NULL;
    }

    /**
     * @brief Returns the height of a node in the binary search tree.
     *
     * This function returns the height of a given node in the binary search tree.
     * If the node is NULL, it returns -1.
     *
     * @param node The node for which the height is to be calculated.
     *
     * @return The height of the node.
     */
    int Height(Node *node)
    {
        if (node == NULL)
            return -1;
        else
            return node->height;
    }

    /**
     * @brief Returns the root node of the binary search tree.
     *
     * This function returns the root node of the binary search tree.
     * @return The root node of the binary search tree.
     */
    Node *getRoot()
    {
        return root;
    }

    /**
     * @brief Returns the balance factor of a node in the binary search tree.
     *
     * This function returns the balance factor of a given node in the binary search tree.
     *
     * @param node The node for which the balance factor is to be calculated.
     * @return The balance factor of the node.
     */
    int BalanceFactor(Node *node)
    {
        return Height(node->left) - Height(node->right);
    }

    /**
     * @brief Inserts a new game into the binary search tree.
     *
     * This function creates a new node with the given game information and inserts
     * it into the binary search tree based on the game's ID.
     *
     * @param R The root node of the binary search tree.
     * @param game The Game object to be inserted.
     * @param hours_played The number of hours played for this game.
     * @param achievements_unlocked The number of achievements unlocked for this game.
     *
     * @return void
     */
    Node *insert(Node *R, Game game, float hours_played, int achievements_unlocked)
    {
        if (R == NULL)
        {
            R = new Node;
            cout << "Helo" << endl;
            R->game = game;
            R->hours_played = hours_played;
            R->achievements_unlocked = achievements_unlocked;
            R->right = NULL;
            R->left = NULL;
            R->height = 0;
        }
        else if (game.gameId < R->game.gameId)
        {
            R->left = insert(R->left, game, hours_played, achievements_unlocked);
            // if (BalanceFactor(R) == 2)
            // {
            //     if (BalanceFactor(R->left) > 0)
            //         R = rightRotate(R);
            //     else
            //         R = leftRightRotate(R);
            // }
        }
        else if (game.gameId > R->game.gameId)
        {
            R->right = insert(R->right, game, hours_played, achievements_unlocked);
            // if (BalanceFactor(R) == -2)
            // {
            //     if (BalanceFactor(R->right) < 0)
            //         R = leftRotate(R);
            //     else
            //         R = rightLeftRotate(R);
            // }
        }

        // R->height = 1 + max(Height(R->left), Height(R->right));
        return R;
    }

    void print(Node *R)
    {
        if (R == NULL)
            return;
        print(R->left);
        cout << "Game ID: " << R->game.gameId << endl;
        cout << "Name: " << R->game.name << endl;
        cout << "Developer: " << R->game.developer << endl;
        cout << "Publisher: " << R->game.publisher << endl;
        cout << "File Size: " << R->game.file_size_in_GB << " GB" << endl;
        cout << "Downloads: " << R->game.downloads << endl;
        cout << "Hours Played: " << R->hours_played << endl;
        cout << "Achievements Unlocked: " << R->achievements_unlocked << endl;
        cout << endl;
        print(R->right);
    }
};

class Player
{
    struct Node
    {
        string playerId;
        string name;
        string phoneNo;
        string email;
        string password;
        Game_Played games_played;

        Node *right;
        Node *left;
    };
    Node *root;

public:
    Player()
    {
        root = NULL;
    }

    /**
     * @brief Returns the root node of the binary search tree.
     *
     * This function returns the root node of the binary search tree.
     * @return The root node of the binary search tree.
     */
    Node *getRoot()
    {
        return root;
    }

    // Insert a game in a player's list of games played
    Node *insert_game(Game game, float hours_played, int achievements_unlocked, string playerId, Node *R)
    {
        if (R == NULL)
        {
            R = new Node;
            R->playerId = playerId;
            R->games_played.insert(R->games_played.getRoot(), game, hours_played, achievements_unlocked);
        }
    }

    void print()
    {
        Node *temp = root;
        while (temp != NULL)
        {
            cout << temp->playerId << endl;
            temp = temp->right;
        }
    }
};

int main()
{
    Game_Played game;

    game.insert(game.getRoot(), Game("1", "Game1", "Developer1", "Publisher1", 1.5, 1000), 10.5, 5);
    game.insert(game.getRoot(), Game("2", "Game2", "Developer2", "Publisher2", 2.0, 2000), 20.0, 10);
    game.insert(game.getRoot(), Game("3", "Game3", "Developer3", "Publisher3", 1.0, 1500), 15.0, 7);
    game.insert(game.getRoot(), Game("4", "Game4", "Developer4", "Publisher4", 1.5, 1200), 12.0, 4);

    game.print(game.getRoot());

    return 0;
}