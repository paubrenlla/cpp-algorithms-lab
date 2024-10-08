#include <cassert>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

struct Libro
{
    int id;
    string titulo;
    bool habilitado;

    // Constructor
    Libro(int unId, string unTitulo) : id(unId), titulo(unTitulo), habilitado(true) {}
};

class BibliotecaAVL
{
private:
    struct AVLNode
    {
        Libro* libro;
        AVLNode *left;
        AVLNode *right;
        int height;
        AVLNode(Libro* unLibro) : libro(unLibro), left(NULL), right(NULL), height(1) {};
    };

    AVLNode *root; // root of the tree
    int cantLibros;
    int cantHabilitados;

    // A utility function to get the height of the tree.
    // In case of an empty tree, it returns 0.
    int height(AVLNode *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return node->height;
    }

    // A utility function to right
    // rotate subtree rooted with y
    AVLNode *rightRotate(AVLNode *y)
    {
        AVLNode *x = y->left;
        AVLNode *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = std::max(height(y->left),
                             height(y->right)) +
                    1;
        x->height = std::max(height(x->left),
                             height(x->right)) +
                    1;

        // Return new root
        return x;
    }

    // A utility function to left
    // rotate subtree rooted with x
    AVLNode *leftRotate(AVLNode *x)
    {
        AVLNode *y = x->right;
        AVLNode *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = std::max(height(x->left),
                             height(x->right)) +
                    1;
        y->height = std::max(height(y->left),
                             height(y->right)) +
                    1;

        // Return new root
        return y;
    }

    // Get Balance factor of node N
    int getBalance(AVLNode *node)
    {
        if (node == NULL)
            return 0;
        return height(node->right) - height(node->left);
    }

    // Recursive function to insert a element
    // in the subtree rooted with node and
    // returns the new root of the subtree.
    AVLNode *insert(AVLNode *node, int id, string titulo)
    {
        /* 1. Perform the normal BST insertion */
        if (node == NULL) {
            Libro* libroNuevo = new Libro(id, titulo);

            this->cantLibros++;
            this->cantHabilitados++;

            return new AVLNode(libroNuevo);
        }
        else if (id < node->libro->id){
            node->left = insert(node->left, id, titulo);
        }
        else if (id > node->libro->id){
            node->right = insert(node->right, id, titulo);
        }
        else
        { // Equal elements are not allowed in BST
            if (node->libro->habilitado == false)
            {
                node->libro->habilitado = true;
                cantHabilitados++;
            }
            node->libro->titulo = titulo;
            return node;
        }

        /* 2. Update height of this ancestor AVLnode */
        node->height = 1 + std::max(height(node->left),
                                    height(node->right));

        /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
        int balance = getBalance(node);

        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance < -1 && id < node->left->libro->id)
            return rightRotate(node);

        // Right Right Case
        if (balance > 1 && id > node->right->libro->id)
            return leftRotate(node);

        // Left Right Case
        if (balance < -1 && id > node->left->libro->id)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance > 1 && id < node->right->libro->id)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    string contains(AVLNode *node, int unId)
    {
        if (node == NULL)
        {
            return "libro_no_encontrado";
        }
        if (node->libro->id == unId)
        {
            return node->libro->titulo + " " + libroHabilitado(node->libro->habilitado);
        }
        if (node->libro->id > unId)
        {
            return contains(node->left, unId);
        }
        else
        {
            return contains(node->right, unId);
        }
    }

    string toggle(AVLNode *node, int unId)
    {
        if (node == NULL)
        {
            return "libro_no_encontrado";
        }
        if (node->libro->id == unId)
        {
            if (node->libro->habilitado == false)
            {
                node->libro->habilitado = true;
                this->cantHabilitados++;
            }
            else
            {
                node->libro->habilitado = false;
                this->cantHabilitados--;
            }

            return "existe";
        }
        else if (node->libro->id > unId)
        {
            return toggle(node->left, unId);
        }
        else
        {
            return toggle(node->right, unId);
        }
    }

    string libroHabilitado(bool hab)
    {
        if (hab)
        {
            return "H";
        }
        else
        {
            return "D";
        }
    }

public:
    BibliotecaAVL() : root(NULL), cantLibros(0), cantHabilitados(0) {}

    void add(int unId, string unNombre)
    {
        root = insert(root, unId, unNombre);
    }

    string find(int unId)
    {
        return this->contains(root, unId);
    }

    string toggle(int unId)
    {
        return this->toggle(root, unId);
    }

    string count()
    {
        int totalDesHab = this->cantLibros - this->cantHabilitados;
        return to_string(this->cantLibros) + " " + to_string(this->cantHabilitados) + " " + to_string(totalDesHab);
    }
};

int main()
{
    int n;
    cin >> n;
    string command;
    int id;
    string name;

    BibliotecaAVL *biblioteca = new BibliotecaAVL();

    for (int i = 0; i < n; ++i)
    {
        cin >> command;
        if (command == "ADD")
        {
            cin >> id >> ws;
            getline(cin, name);
            biblioteca->add(id, name);
        }
        else if (command == "FIND")
        {
            cin >> id;
            cout << biblioteca->find(id) << endl;
        }
        else if (command == "TOGGLE")
        {
            cin >> id;
            string resultado = biblioteca->toggle(id);
            if (resultado != "existe")
            {
                cout << resultado << endl;
            }
        }
        else if (command == "COUNT")
        {
            cout << biblioteca->count() << endl;
        }
    }

    return 0;
}