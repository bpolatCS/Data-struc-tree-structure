#include "avlHeader.h"

using namespace std;

/**
    * Construct the tree.
    */
template <class Comparable>
BinarySearchTree<Comparable>:: BinarySearchTree(const Comparable & notFound ) :
	ITEM_NOT_FOUND(notFound), root( NULL)
{
}

/**
    * Destructor for the tree.
    */
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( )
{
    makeEmpty( );
}

/**
    * Copy constructor.
    */
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) :
        root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{ 
    *this = rhs;
}

/**
    * Internal method to get element field in node t.
    * Return the element field or ITEM_NOT_FOUND if t is NULL.
    */
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::elementAt( BinaryNode<Comparable> *t ) const
{
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}

/**
    * Find item x in the tree.
    * Return the matching item or ITEM_NOT_FOUND if not found.
    */
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::find( const Comparable & x ) const
{
        return elementAt(find(x, root));
}


/**
    * Internal method to find an item in a subtree.
    * x is item to search for.
    * t is the node that roots the tree.
    * Return node containing the matched item.
    */
template <class Comparable> //PRIVATE FIND
BinaryNode<Comparable> *BinarySearchTree<Comparable>::find( const Comparable & x, BinaryNode<Comparable> * t ) const
{
        if ( t == NULL )
            return NULL;
        else if( x < t->element )
            return find( x, t->left );
        else if( t->element < x )
            return find( x, t->right );
        else
            return t;    // Match
}


/**
    * Find the smallest item in the tree.
    * Return smallest item or ITEM_NOT_FOUND if empty.
    */
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin( ) const
{
    return elementAt(findMin(root));
}

/**
    * Internal method to find the smallest item in a subtree t.
    * Return node containing the smallest item.
    */
template <class Comparable> //PRIVATE FINDMIN
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t ) const
{
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin(t->left);
}



/**
    * Find the smallest item in the tree.
    * Return smallest item or ITEM_NOT_FOUND if empty.
    */
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax( ) const
{
    return elementAt( findMax( root ) );
}

/**
    * Internal method to find the largest item in a subtree t.
    * Return node containing the largest item.
    */
template <class Comparable> //PRIVATE FINDMAX
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t )const
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}

/**
    * Insert x into the tree; duplicates are ignored.
    */
template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x ) //D�Z INSERT
{
    insert(x,root );
}

/**
    * Internal method to insert into a subtree.
    * x is the item to insert.
    * t is the node that roots the tree.
    * Set the new root.
    */
template <class Comparable>
 void AvlTree<Comparable>::insert( const Comparable & x, AvlNode<Comparable> * & t ) const
 {
    if ( t == NULL )
        t = new AvlNode<Comparable>( x, NULL, NULL );

    else if ( x < t->element )// X should be inserted to the left tree!
	{
        insert( x, t->left );  // Check if the left tree is out of balance (left subtree grew in height!)        							
        if ( height( t->left ) - height( t->right ) == 2 )
		{
            if ( x < t->left->element )  // X was inserted to the left-left subtree!
				rotateWithLeftChild( t );
            else			     // X was inserted to the left-right subtree!
				doubleWithLeftChild( t );    
		}
	}
	else if( t->element < x )
	{    // Otherwise X is inserted to the right subtree
		insert( x, t->right );
		if ( height( t->right ) - height( t->left ) == 2 )// height of the right subtree increased
		{			
			if ( t->right->element < x )// X was inserted to right-right subtree							
				rotateWithRightChild( t );
			else // X was inserted to right-left subtree
				doubleWithRightChild( t );
		}
	}
	else
    ;  // Duplicate; do nothing
            
		// update the height the node
	t->height = max( height( t->left ), height( t->right ) ) + 1;
}

            


/**
    * Remove x from the tree. Nothing is done if x is not found.
    */
template <class Comparable> //D�Z REMOVE
void BinarySearchTree<Comparable>::remove( const Comparable & x )
{
	remove( x, root );
}

/**
    * Internal method to remove from a subtree.
    * x is the item to remove.
    * t is the node that roots the tree.
    * Set the new root.
    */
template <class Comparable> //PRIVATE REMOVE
void BinarySearchTree<Comparable>::remove( const Comparable & x, BinaryNode<Comparable> * & t ) const
{
    if( t == NULL )
        return;   // Item not found; do nothing
    if( x < t->element )
        remove( x, t->left );

    else if( t->element < x )
        remove( x, t->right );

    else if( t->left != NULL && t->right != NULL ) // Two children
    {
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    }
    else // one or no children
    {
        BinaryNode<Comparable> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
}  

/**
    * Make the tree logically empty.
    */
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( )
{
	 makeEmpty(root);
}

/**
    * Internal method to make subtree empty.
    */
template <class Comparable> void BinarySearchTree<Comparable>::makeEmpty( BinaryNode<Comparable> * & t ) const
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}

/**
    * Print the tree contents in sorted order.
    */
template <class Comparable> //D�Z 
void BinarySearchTree<Comparable>::printTree( ) const
{
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    else
        printTree( root );
}


/**
* Internal method to print a subtree rooted at t in sorted order.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::printTree( BinaryNode<Comparable> * t ) const
{
    if ( t != NULL )
    {
        printTree( t->left );
        cout << t->element << endl;
        printTree( t->right );
    }
}

/**
		* Return the height of node t, or -1, if NULL.
*/
template <class Comparable>
int AvlTree<Comparable>::height( AvlNode<Comparable> *t ) const
{
	if (t == NULL)
		return -1;
	
	return t->height;
}

 /**
         * Return maximum of lhs and rhs.
 */
template <class Comparable>
int AvlTree<Comparable>::max( int lhs, int rhs ) const
{
      if (lhs > rhs)
	      return lhs;

      return rhs;            
}

/**
    * Rotate binary tree node with left child.
    * For AVL trees, this is a single rotation for case 1.
    * Update heights, then set new root.
    */
template <class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const
{
	AvlNode<Comparable> *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
	k1->height = max( height( k1->left ), k2->height ) + 1;
	k2 = k1;
}

/**
* Rotate binary tree node with right child.
* For AVL trees, this is a single rotation for case 4.
* Update heights, then set new root.
*/
template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild( AvlNode<Comparable> * & k1 ) const
{
    AvlNode<Comparable> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
}


/**
    * Double rotate binary tree node: first left child.
    * with its right child; then node k3 with new left child.
    * For AVL trees, this is a double rotation for case 2.
    * Update heights, then set new root.
    */
template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const
{
	rotateWithRightChild( k3->left );
	rotateWithLeftChild( k3 );
}

/**
    * Double rotate binary tree node: first right child.
    * with its left child; then node k1 with new right child.
    * For AVL trees, this is a double rotation for case 3.
    * Update heights, then set new root.
    */
template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild( AvlNode<Comparable> * & k1 ) const
{
	rotateWithLeftChild( k1->right );
	rotateWithRightChild( k1 );
}

