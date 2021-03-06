#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <climits>
#include <limits>

class TreeNode
{
public:
    int key;

    char color;

    TreeNode *left, *right,*parent;
};

TreeNode * deletion(int var);
void leftRotate(TreeNode *x);
void rightRotate(TreeNode *y);
void color_insert(TreeNode *z);
void insert(int val);
void inorderTree( TreeNode* root);

int flag = 0;

TreeNode* root = NULL;
std::ifstream input("input.txt");
std:: ofstream out("output.txt");

void leftRotate(TreeNode *x)

{
    TreeNode *y;

    y = x->right;
    x->right = y->left;

    if( y->left != NULL)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if( x->parent == NULL)
    {
        root = y;
    }

    else if((x->parent->left != NULL) && (x->key == x->parent->left->key))
    {
        x->parent->left = y;
    }

    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
    return;
}

void rightRotate(TreeNode *y)
{
    TreeNode *x;

    x = y->left;
    y->left = x->right;

    if(x->right != NULL)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if(y->parent == NULL)
    {
        root = x;
    }

    else if((y->parent->left != NULL) && (y->key == y->parent->left->key))
    {
        y->parent->left = x;
    }
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;

    return;

}

void color_insert(TreeNode *z)
{
    TreeNode *y=NULL;

    while ((z->parent != NULL) && (z->parent->color == 'r'))
    {

        if ((z->parent->parent->left != NULL) && (z->parent->key == z->parent->parent->left->key))
        {
            if(z->parent->parent->right!=NULL)
                y = z->parent->parent->right;

            if ((y!=NULL) && (y->color == 'r'))
            {
                z->parent->color = 'b';

                y->color = 'b';

                z->parent->parent->color = 'r';

                if(z->parent->parent!=NULL)

                z = z->parent->parent;

            }

            else
            {

                if ((z->parent->right != NULL) && (z->key == z->parent->right->key))

                {
                    z = z->parent;

                    leftRotate(z);

                }

                z->parent->color = 'b';

                z->parent->parent->color = 'r';

                rightRotate(z->parent->parent);

            }

        }

        else
        {

            if(z->parent->parent->left!=NULL)
                y = z->parent->parent->left;

            if ((y!=NULL) && (y->color == 'r'))
            {
                z->parent->color = 'b';

                y->color = 'b';

                z->parent->parent->color = 'r';

                if(z->parent->parent!=NULL)

                z = z->parent->parent;
            }

            else
            {

                if ((z->parent->left != NULL) && (z->key == z->parent->left->key))
                {
                    z = z->parent;

                    rightRotate(z);
                }

                z->parent->color = 'b';

                z->parent->parent->color = 'r';

                leftRotate(z->parent->parent);

            }

        }

    }
    root->color = 'b';

}

void insert(int val)
{
    TreeNode *x, *y;

    TreeNode *z = (TreeNode*)malloc(sizeof(TreeNode));

    z->key = val;

    z->left = NULL;

    z->right = NULL;

    z->color = 'r';

    x=root;


    if ( root == NULL )
    {
        root = z;

        root->color = 'b';

        return;
    }

    while ( x != NULL)
    {
        y = x;

        if(z->key < x->key)
        {
            x = x->left;
        }
        else
            x = x->right;

    }

    z->parent = y;

    if( y == NULL)
    {
        root = z;
    }

    else if( z->key < y->key )
    {
        y->left = z;
    }

    else
        y->right = z;

    color_insert(z);

    return;

}

void inorderTree( TreeNode* root)
{
    TreeNode* temp = root;

    if (temp != NULL)
    {
        inorderTree(temp->left);
        if(temp->parent != NULL)
        {
            if(temp->color == 'r')
                out << "key: " << temp->key << " parent: " << temp->parent->key << " color: red" << "\n";
            else
                out << "key: " << temp->key << " parent: " << temp->parent->key << " color: black" << "\n";
        }
        else
        {
            if(temp->color == 'r')
                out << "key: " << temp->key << " parent: " <<  " color: red" << "\n";
            else
                out << "key: " << temp->key << " parent: " << " color: black" << "\n";
        }
        inorderTree(temp->right);

    }
    return;

}
TreeNode* min(struct TreeNode *x)
{
    while (x->left)
    {
        x = x->left;
    }
    return x;

}
TreeNode* successor( TreeNode *x)
{
     TreeNode *y;

    if (x->right)
    {
        return min(x->right);

    }
    y = x->parent;
    while (y && x == y->right)
    {
        x = y;

        y = y->parent;
    }
    return y;

}

void color_deletion( TreeNode *x)
{
    while (x != root && x->color == 'b')
    {
         TreeNode *w = NULL;

        if ((x->parent->left!=NULL) && (x == x->parent->left))
        {
            w = x->parent->right;

            if ((w!=NULL) && (w->color == 'r'))
            {
                w->color = 'b';

                x->parent->color = 'r';

                leftRotate(x->parent);

                w = x->parent->right;
            }

            if ((w!=NULL) && (w->right!=NULL) && (w->left!=NULL) && (w->left->color == 'b') && (w->right->color == 'b'))
            {

                w->color = 'r';

                x = x->parent;

            }

            else if((w!=NULL) && (w->right->color == 'b'))
            {
                w->left->color = 'b';

                w->color = 'r';

                rightRotate(w);

                w = x->parent->right;
            }

            if(w!=NULL)
            {
                w->color = x->parent->color;

                x->parent->color = 'b';

                w->right->color = 'b';

                leftRotate(x->parent);

                x = root;
            }

      }

      else if(x->parent!=NULL)
      {
          w = x->parent->left;

          if ((w!=NULL) && (w->color == 'r'))
          {

              w->color = 'b';

              x->parent->color = 'r';

              leftRotate(x->parent);

              if(x->parent!=NULL)

              w = x->parent->left;

          }

          if ((w!=NULL) && (w->right!=NULL) && (w->left!=NULL) && (w->right->color == 'b') && (w->left->color == 'b'))
          {
              x = x->parent;
          }

          else if((w!=NULL) && (w->right!=NULL) && (w->left!=NULL) && (w->left->color == 'b'))
          {
              w->right->color = 'b';

              w->color = 'r';

              rightRotate(w);

              w = x->parent->left;
          }

          if(x->parent!=NULL)
          {
              w->color = x->parent->color;

              x->parent->color = 'b';
          }

          if(w->left!=NULL)
              w->left->color = 'b';

          if(x->parent !=NULL)
              leftRotate(x->parent);

          x = root;

       }

    }
    x->color = 'b';
}

TreeNode* deletion(int var)
{
    TreeNode *x = NULL, *y = NULL, *z;

    z=root;

    if((z->left ==NULL ) &&(z->right==NULL) && (z->key==var))
    {
        root=NULL;
        std::cout << "empty tree!";
        out << "empty tree!";
    }

    while(z->key !=var && z!=NULL)
    {
        if(var<z->key)

        z=z->left;

        else
            z=z->right;

        if(z== NULL)
        {

        }
    }

    if((z->left==NULL)||(z->right==NULL))
    {
        y = z;
    }
    else
    {
        y = successor(z);
    }
    if (y->left!=NULL)
    {
        x = y->left;
    }
    else
    {
        if(y->right !=NULL)
            x = y->right;
    }

    if((x!=NULL) && (y->parent !=NULL))
        x->parent = y->parent;

    if ((y !=NULL) && (x!=NULL) && (y->parent==NULL))
    {
        root=x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    if (y != z)
    {
        z->key = y->key;
    }

    if ((y!=NULL) && (x!=NULL) && (y->color == 'b'))
    {
        color_deletion(x);
    }
    return y;

}

int getline_num(std::ifstream &f)
{
    std::string line;
    std::getline(f, line);
    return std::stoi(line);
}

void parse(std::ifstream &f)
{
    int num;
    std::vector<int> value;

    int table_num = getline_num(f);

    while (table_num--)
    {
        // which type {insert = 1, extract = 2} to perform
        int type = getline_num(f);

        if (type == 1 /* insert */)
        {
            std::string whole_line;
            std::getline(f, whole_line);
            std::stringstream ss(whole_line);

            // get insert number
            std::vector<int> insert_list;
            int n = 0;
            for (int num = 0; ss >> num;)
            {
                insert_list.push_back(num);
                n++;
            }
            int *number;
            number = new int[n];
            for(int i = 0; i < insert_list.size(); i++)
            {
                number[i] = insert_list[i];
            }
            for(int i = 0; i < n; i++)
            {
                insert(number[i]);
            }

            out << "Insert:" ;
            for(int i = 0; i < insert_list.size() - 1; i++)
            {
                out << insert_list[i] << ",";
            }
            out << insert_list.back();
            out << "\n";
            inorderTree(root);
            delete [] number;

        }
        else if (type == 2)
        {
            std::string whole_line;
            std::getline(f, whole_line);
            std::stringstream ss(whole_line);

            // get insert number
            std::vector<int> delete_list;
            int n = 0;
            for (int num = 0; ss >> num;)
            {
                delete_list.push_back(num);
                n++;
            }
            int *number;
            number = new int[n];
            for(int i = 0; i < delete_list.size(); i++)
            {
                number[i] = delete_list[i];
            }
            for(int i = 0; i < n; i++)
            {
                deletion(number[i]);
            }

            out << "Delete:" ;
            for(int i = 0; i < delete_list.size() - 1; i++)
            {
                out << delete_list[i] << ",";
            }
            out << delete_list.back();
            out << "\n";
            inorderTree(root);
            delete [] number;
        }
    }
}
int main(int argc, char* argv[])
{
    parse(input);
    return 0;
}
