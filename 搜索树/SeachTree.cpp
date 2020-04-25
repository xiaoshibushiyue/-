#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DESC_SIZE 256
#define KEY_SIZE 256
#define BUFSIZE 512
#define FILENAME "log.txt"
//搜索树---空间换时间
struct node_st
{
    /* data */
    struct node_st* ch[26];
    char desc[DESC_SIZE];
};
//从文本中获取关键字和描述语句例如donkey: a person,并将其赋值给key和desc
int get_word(FILE* fp, char* key, char* desc) {
    char buf[BUFSIZE] = { '\0' };
    char* retp;

    retp = fgets(buf, BUFSIZE, fp);
    if (retp == NULL)
    {
        return -1;
    }
    int i;


    for (i = 0; i < KEY_SIZE - 1 && buf[i] != ':'; i++)
    {
        key[i] = buf[i];
    }
    key[i] = '\0';
    i++;
    int j;
    for (j = 0; j < DESC_SIZE - 1 && buf[i] != '\0'; j++, i++)
    {
        desc[j] = buf[i];
    }
    desc[j] = '\0';
    return 0;
}
//创建新的节点，并返回新节点的节点地址
struct node_st* newnode() {
    struct node_st* node;
    node = (struct node_st*)calloc(sizeof(*node), 1);
    if (node == NULL)
    {
        return NULL;
    }
    strcpy(node->desc, "\0");
    for (int i = 0; i < 26; i++)
    {
        node->ch[i] = NULL;
    }
    return node;
}
//插入节点，root为树的根，根据key中的字符，开辟新的节点，直到找到合适的节点，将desc赋值
int insert(struct node_st** root, const char* key, char* desc) {
    if (*root == NULL)
    {
        *root = newnode();
        if (*root == NULL)
        {
            return -1;
        }
    }
    if (*key == '\0')
    {
        strcpy((*root)->desc, desc);
        return 0;
    }

    return insert((*root)->ch + *key - 'a', key + 1, desc);

}
//查找函数 根据key中的字符,一级一级往下找.
char* find(struct node_st* root, const char* key) {
    if (root == NULL)
    {
        return NULL;
    }
    if (*key == '\0')
    {
        return root->desc;
    }
    return find(root->ch[*key - 'a'], key + 1);
}
int main()
{
    struct node_st* tree = NULL;
    FILE* fp;
    char desc[DESC_SIZE] = { '\0' };
    char key[KEY_SIZE] = { '\0' };
    fp = fopen(FILENAME, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "fopen() error!\n");
        exit(1);
    }
    while (1)
    {

        int ret = get_word(fp, key, desc);
        if (ret == -1)
        {
            break;
        }
        insert(&tree, key, desc);
    }
    char* datap = find(tree, "son");
    if (datap == NULL)
    {
        printf("no data!\n");
    }
    else {
        puts(datap);
    }
    fclose(fp);
    free(tree);
    exit(0);
}
