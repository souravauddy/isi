#include "../day6/common.h"

#define LATEX_HEADER "\\documentclass[a4,landscape]{article}\n"         \
    "\\usepackage[margin=5mm]{geometry}\n"                               \
    "\\usepackage{graphicx}\n"

#define PSTREE_HEADER "\\usepackage{pstricks,pst-node,pst-text,pst-3d}\n" \
    "\\usepackage{pst-tree}\n"                                            \
    "\\psset{treesep=1cm,treefit=loose}\n"                                \
    "\n\n\\begin{document}\n\\resizebox{\\textwidth}{!}{\n"

#define TIKZ_HEADER "\\usepackage{tikz}\n"                              \
    "\\usetikzlibrary{arrows.meta}\n"                                   \
    "\\usetikzlibrary{calc}\n"                                          \
    "\\usetikzlibrary{decorations.text}\n"                              \
    "\\usetikzlibrary{positioning}\n"                                   \
    "\\usetikzlibrary{shapes, shapes.callouts}\n"                       \
    "\\usetikzlibrary{trees}\n"                                         \
    "\\tikzset{\n"                                                      \
    "  >={Stealth},\n"                                                  \
    "  invisible/.style={opacity=0},\n"                                 \
    "  visible on/.style={alt=#1{}{invisible}},\n"                      \
    "  alt/.code args={<#1>#2#3}{\n"                                    \
    "    \\alt<#1>{\\pgfkeysalso{#2}}{\\pgfkeysalso{#3}}\n "            \
    "  },\n"                                                            \
    "}\n\n\\begin{document}\n"                                          \
    "\\begin{tikzpicture}[overlay,remember picture,\n"                  \
    "  every node/.style={draw,circle,minimum size=7mm},\n"             \
    "  level distance=1.5cm,\n"                                         \
    "  level 1/.style={sibling distance=3cm},\n"                        \
    "  level 2/.style={sibling distance=1cm},\n"                        \
    "  edge from parent/.style={draw,-latex}\n"                         \
    "  ]\n"                                                             \
    "  \\node "

#define PSTREE_FOOTER "}\n"

#define TIKZ_FOOTER ";\n\\end{tikzpicture}\n\\end{document}\n"

#define LATEX_FOOTER ";\n\\end{document}\n"

typedef int DATA;
typedef struct tnode {
    DATA data;
    int left, right;
    int parent; //optional
} TNODE;

typedef struct {
    uint capacity, num_nodes;
    // num_nodes is optional
    int root, free;
    TNODE *nodelist;
} TREE;

int read_tree(TREE *t) {
    int i;
    TNODE *node;

    scanf("%u", &t->num_nodes);
    t->capacity = t->num_nodes;
    t->free = -1;
    t->root = 0;
    if (NULL == (t->nodelist = (TNODE *) malloc(t->num_nodes * sizeof(TNODE)))) {
        fprintf(stderr, "Out of memory\n");
        return -1;
    }
    for (node = t->nodelist, i = 0; i < t->num_nodes; node++, i++)
        scanf("%d %d %d", &(node->data), &(node->left), &(node->right));
    
    return 0;
}

void print_subtree_latex(TREE *tree, int root) {
    int i;
    if (root != -1) {
        fprintf(stderr, "{%d}\n", tree->nodelist[root].data);

        i = tree->nodelist[root].left;
        if (i == -1) // no left child
            fprintf(stderr, "child[missing]\n");
        else {
            fprintf(stderr, "child {node ");
            print_subtree_latex(tree, i);
            fprintf(stderr, "}\n");
        }
        
        i = tree->nodelist[root].right;
        if (i == -1) // no right child
            fprintf(stderr, "child[missing]\n");
        else {
            fprintf(stderr, "child {node ");
            print_subtree_latex(tree, i);
            fprintf(stderr, "}\n");
        }

        return;
    }
}

void print_pstree(TREE *tree, int root) {
    if (root != -1) {
        fprintf(stderr, "\\pstree{\\TCircle[radius=0.5]{%d}}{\n", tree->nodelist[root].data);
        print_pstree(tree, tree->nodelist[root].left);
        print_pstree(tree, tree->nodelist[root].right);
        fprintf(stderr, "}\n");
    }
    else
        fprintf(stderr, "\\pstree{\\Tn}{} \\pstree{\\Tn}{}");

    return;
}


#if 1
int main(int ac, char *av[])
{
    TREE t;

    if (0 != read_tree(&t))
        return 1;
    fprintf(stderr, LATEX_HEADER);
    fprintf(stderr, PSTREE_HEADER);
    print_pstree(&t, t.root);
    fprintf(stderr, PSTREE_FOOTER);
    fprintf(stderr, LATEX_FOOTER);
    return 0;
}
#endif
