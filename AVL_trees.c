#include<stdio.h>
#include <stdlib.h>
#include <malloc.h>



struct btnode{
    int data;
    struct btnode *leftChild;
    struct btnode *rightChild;
    int height;
};
struct btnode*root=NULL;


int max(int i, int j){
    if(i > j){
        return i;
    }
    else if(j > i){
        return j;
    }
    else{
        return 0;
    }
}

int height(struct btnode*temp){
    if(temp == NULL){
        return 0;
    }
    return temp->height;
}

//Tree Balancing Operations
//Shift Left
struct btnode*rotateLeft(struct btnode*curr){
    struct btnode*temp = curr->rightChild;
    struct btnode*temp2 = temp->leftChild;

    temp->leftChild = curr;
    curr->rightChild = temp2;

    temp->height = 1 + max(height(temp->leftChild), height(temp->rightChild));
    curr->height = 1 + max(height(temp->leftChild), height(temp->rightChild));

    return temp;
}

//Shift Right
struct btnode*rotateRight(struct btnode*curr){
    struct btnode*temp = curr->leftChild;
    struct btnode*temp2 = temp->rightChild;

    temp->rightChild = curr;
    curr->leftChild = temp2;

    temp->height = 1 + max(height(temp->leftChild), height(temp->rightChild));
    curr->height = 1 + max(height(temp->leftChild), height(temp->rightChild));

    return temp;
}

//Double shift (Left then Right)
struct btnode*rotateLeftRight(struct btnode*curr){
    curr->leftChild = rotateLeft(curr->leftChild);
    return rotateRight(curr);
}

//Double shift (Right then Left)
struct btnode*rotateRightLeft(struct btnode*curr){
    curr->rightChild = rotateRight(curr->rightChild);
    return rotateLeft(curr);
}
//End of Balancing Operations



int getBalance(struct btnode*temp){
    if(temp == NULL){
        return 0;
    }
    else{
        return ((height(temp->leftChild)) - height(temp->rightChild));
    }
}

//Insert function
struct btnode*insertAVL(struct btnode*node, int n){
    if(node == NULL){
        struct btnode *temp;
        temp = (struct btnode*)malloc(sizeof(struct btnode));
        temp->data = n;
        temp->height = 0;
        temp->leftChild = NULL;
        temp->rightChild = NULL;
        return temp;
    }
    if(n < node->data){
        node->leftChild = insertAVL(node->leftChild, n);
    }
    else{
        node->rightChild = insertAVL(node->rightChild, n);
    }
    node->height = 1 + max(height(node->leftChild), height(node->rightChild));

    int balance = getBalance(node);

    if(balance > 1 && n < node->leftChild->data){
        node = rotateRight(node);
    }
    else if(balance > 1 && n > node->leftChild->data){
        node = rotateLeftRight(node);
    }
    else if(balance < -1 && n > node->rightChild->data){
        node = rotateLeft(node);
    }
    else if(balance < -1 && n < node->rightChild->data){
        node = rotateRightLeft(node);
    }

    return node;
}
//End of Insert Function



//Delete function
struct btnode*deleteAVL(struct btnode*node, int n){
    struct btnode*temp;
    if(node == NULL){
        printf("Value not found");
        return NULL;
    }
    if(n < node->data){
        node->leftChild = deleteAVL(node->leftChild, n);
    }
    else if(n > node->data){
        node->rightChild = deleteAVL(node->rightChild, n);
    }
    else{//If node has only one or no child.
        if(node->leftChild == NULL){
            temp = node->rightChild;
            free(node);
            printf("Deleted Successfully!!\n");
            return temp;
        }
        else if(node->rightChild == NULL){
            temp = node->leftChild;
            free(node);
            printf("Deleted Successfully!!\n");
            return temp;
        }
        else{//If node has two children then go to left
             //and search for max value.
            temp = node->leftChild;
            while(temp->rightChild != NULL){
                temp = temp->rightChild;
            }
            node->data = temp->data;
            node->leftChild = deleteAVL(node->leftChild, temp->data);
        }

    }
    return node;
};
//End of delete function



//Search Function
struct btnode*searchAVL(struct btnode*node, int n){
    struct btnode*temp;
    if(node == NULL){
        printf("Value not found!!\n");
        return NULL;
    }
    if(n == node->data){
        printf("Value Found!!\n");
        return node;
    }
    else if(n < node->data){
        node->leftChild = searchAVL(node->leftChild, n);
    }
    else if(n > node->data){
        node->rightChild = searchAVL(node->rightChild, n);
    }
};
//End of Search Function


//Traversing Functions
void preOrder(struct btnode*rootNode){
    if(rootNode == NULL){
        return;
    }
    printf("%d\n", rootNode->data);
    preOrder(rootNode->leftChild);
    preOrder(rootNode->rightChild);
}

void inOrder(struct btnode*rootNode){
    if(rootNode == NULL){
        return;
    }
    inOrder(rootNode->leftChild);
    printf("%d\n", rootNode->data);
    inOrder(rootNode->rightChild);
}

void postOrder(struct btnode*rootNode){
    if(rootNode == NULL){
        return;
    }
    postOrder(rootNode->leftChild);
    postOrder(rootNode->rightChild);
    printf("%d\n", rootNode->data);
}
//End of traversing function.



int main(){
    int n=1;
    printf("Select an option:\n");
    while(n != 0){
    	printf("\nEnter 1 to Insert\nEnter 2 to Delete\nEnter 3 to Traverse\nEnter 4 to Search\nEnter 0 to exit\n");
    	scanf("\n%d", &n);
    	if(n == 1){
    		int toInsert;
    		printf("Enter a value to insert:\n");
    		scanf("\n%d", &toInsert);
    		root = insertAVL(root, toInsert);
		}
		else if(n == 2){
			int toDelete;
			printf("Enter a value to delete:\n");
    		scanf("\n%d", &toDelete);
    		deleteAVL(root,toDelete);
		}
		else if(n == 3){
			printf("In which way do you want to traverse?\n");
			printf("\nEnter 1 for Inorder\nEnter 2 to Preorder\nEnter 3 to Postorder\n");
			int a;
			scanf("%d", &a);
			if(a == 1){
                printf("Traversing in InOrder....\n");
                inOrder(root);
			}
			else if(a == 2){
			    printf("Traversing in PreOrder....\n");
                preOrder(root);
			}
			else if(a == 3){
			    printf("Traversing in PostOrder....\n");
                postOrder(root);
			}
			else if(a < 1 || a > 3){
                printf("Wrong choice");
			}
		}
		else if(n == 4){
            int toSearch;
            printf("Enter a value to search:\n");
            scanf("%d", &toSearch);
            searchAVL(root, toSearch);
		}
		else if(n<0 || n>4){
            printf("Wrong Choice");
		}
	}
}
