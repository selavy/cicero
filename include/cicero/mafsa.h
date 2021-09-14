#ifndef CICERO_MAFSA__H_
#define CICERO_MAFSA__H_

#include <cicero/cicero.h>

#ifdef __cplusplus
extern "C" {
#endif

// TODO: add allocate / deallocate API for custom allocators

struct mafsa_node_ { int children[26]; };
typedef struct mafsa_node_ mafsa_node_;

struct mafsa
{
    mafsa_node_  *nodes;
    unsigned int *terms;
    int           size;
};
typedef struct mafsa mafsa;

struct mafsa_edges
{
    int  terminal;
    char edges[27]; // [A-Z], null-terminated
};
typedef struct mafsa_edges mafsa_edges;

cicero_api int  mafsa_isword(const mafsa *m, const char *const word);
cicero_api int  mafsa_isterm(const mafsa *m, int s);
cicero_api void mafsa_free(mafsa *m);
cicero_api mafsa_edges mafsa_prefix_edges(const mafsa *m, const char *const word);


struct mafsa_builder
{
    mafsa_node_ *nodes;
    int         *terms;
    int          size;
    int          capacity;
};
typedef struct mafsa_builder mafsa_builder;

cicero_api int mafsa_builder_start (mafsa_builder *m);
cicero_api int mafsa_builder_insert(mafsa_builder *m, const char *const word);
cicero_api int mafsa_builder_finish(mafsa_builder *m, mafsa *out);

#ifdef __cplusplus
}
#endif

#endif // CICERO_MAFSA__H_
