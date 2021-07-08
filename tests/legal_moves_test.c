#include <cgreen/cgreen.h>
#include <cicero/cicero.h>
#include <string.h>
#include <assert.h>


struct legal_move
{
    char tiles[CICERO_VERT + 1];
    int  sq;
    int  dir;
};
typedef struct legal_move legal_move;

void legal_move_make(legal_move *m, const char *word, int sq, int dir)
{
    memset(m, 0, sizeof(*m));
    strncpy(m->tiles, word, sizeof(m->tiles) - 1);
    m->tiles[sizeof(m->tiles) - 1] = '\0';
    m->sq = sq;
    m->dir = dir;
}

struct legal_moves
{
    legal_move *b;
    size_t      size;
    size_t      capacity;
};
typedef struct legal_moves legal_moves;

int legal_moves_make(legal_moves *m)
{
    m->capacity = 8;
    m->b = calloc(m->capacity, sizeof(*m->b));
    if (!m->b) {
        return -1;
    }
    m->size = 0;
    return 0;
}

void legal_moves_destroy(legal_moves *m)
{
    free(m->b);
    m->capacity = 0;
    m->size = 0;
}

int legal_moves_push(legal_moves *m, const legal_move *move)
{
    assert(m->size <= m->capacity);
    if (m->size == m->capacity) {
        size_t newcap = (size_t)((double)m->capacity * 1.5);
        legal_move *n = realloc(m->b, newcap * sizeof(*m->b));
        if (!n) {
            return -1;
        }
        m->b = n;
        m->capacity = newcap;
    }
    assert(m->size < m->capacity);
    memcpy(&m->b[m->size++], move, sizeof(*move));
    return 0;
}

Describe(LegalMoves);
BeforeEach(LegalMoves) {}
AfterEach(LegalMoves) {}

Ensure(LegalMoves, legal_moves_starts_empty)
{
    legal_moves moves;
    int rc = legal_moves_make(&moves);
    assert_that(rc, is_equal_to(0));
    assert_that(moves.size, is_equal_to(0));
    legal_moves_destroy(&moves);
}


Ensure(LegalMoves, add_legal_moves)
{
    int rc;
    legal_moves moves;
    legal_move move;

    rc = legal_moves_make(&moves);
    assert_that(rc, is_equal_to(0));

    legal_move_make(&move, "HELLO", 42, CICERO_HORZ);
    rc = legal_moves_push(&moves, &move);
    assert_that(rc, is_equal_to(0));
    assert_that(moves.size, is_equal_to(1));

    legal_move_make(&move, "WORLD", 7, CICERO_VERT);
    rc = legal_moves_push(&moves, &move);
    assert_that(rc, is_equal_to(0));
    assert_that(moves.size, is_equal_to(2));

    legal_move_make(&move, "GEeZe", 9, CICERO_HORZ);
    rc = legal_moves_push(&moves, &move);
    assert_that(rc, is_equal_to(0));
    assert_that(moves.size, is_equal_to(3));

    assert_that(moves.b[0].tiles, is_equal_to_string("HELLO"));
    assert_that(moves.b[1].tiles, is_equal_to_string("WORLD"));
    assert_that(moves.b[2].tiles, is_equal_to_string("GEeZe"));

    legal_moves_destroy(&moves);
}

#if 0
Describe(GenerateMovesFromFirstPosition);
BeforeEach(GenerateMovesFromFirstPosition) {}
AfterEach(GenerateMovesFromFirstPosition) {}

Ensure(GenerateMovesFromFirstPosition, UNRYFIA_rack_from_starting_position)
{
    cicero engine;
    cicero_savepos sp;
    cicero_callbacks cb;
    // typedef void (*on_legal_move)(void *data, const char *word, int sq, int dir);
    // typedef cicero_edges (*prefix_edges)(void *data, const char *prefix);
    // on_legal_move onlegal;
    // const void   *onlegaldata;
    // prefix_edges  getedges;
    // const void   *getedgesdata;
    cicero_init(&engine, cb);
}
#endif


TestSuite *our_tests() {
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, LegalMoves, legal_moves_starts_empty);
    return suite;
}

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;
    return run_test_suite(our_tests(), create_text_reporter());
}
