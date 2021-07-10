#include <cgreen/cgreen.h>
#include <cicero/cicero.h>
#include <string.h>
#include <assert.h>

struct move
{
    char    tiles[CICERO_MAX_WORD_LEN + 1]; // 16 B
    uint8_t len : 4; // [0, 16)  --> 4      // 0.5 B
    uint8_t dir : 4; // [0, 16)  --> 4      // 0.5 B
    uint8_t sq;      // [0, 225) --> 8      // 1B
};
typedef struct move move_t;
_Static_assert(sizeof(move_t) == 18, "!");

int move_is_valid(const move_t *const move)
{
    const int len = move->len;
    const int dir = move->dir;
    const int sq = move->sq;
    if (len < CICERO_MIN_WORD_LEN) {
        return CICERO_WORD_TOO_SHORT;
    }
    if (len > CICERO_MAX_WORD_LEN) {
        return CICERO_TOO_MANY_TILES;
    }
    if (dir != CICERO_HORZ && dir != CICERO_VERT) {
        return CICERO_DIRECTION_INVALID;
    }
    if (!(0 <= sq && sq < CICERO_NSQS)) {
        return CICERO_SQUARE_INVALID;
    }
    return CICERO_OK;
}

void move_init(move_t *m)
{
    memset(m->tiles, '\0', sizeof(m->tiles));
    m->len = 0;
    m->dir = 0;
    m->sq = CICERO_INVALID_SQUARE;
}

move_t move_make(const char *word, int sq, int dir)
{
    move_t move;
    move_init(&move);
    if (!(0 <= sq && sq < CICERO_NSQS)) {
        return move;
    }
    if (dir != CICERO_HORZ && dir != CICERO_VERT) {
        return move;
    }
    strncpy(move.tiles, word, sizeof(move.tiles) - 1);
    assert(move.tiles[sizeof(move.tiles) - 1] == '\0');
    move.len = strlen(move.tiles);
    move.sq = sq;
    move.dir = dir;
    return move;
}

int move_append_tile(move_t *m, char tile)
{
    if (m->len > CICERO_MAX_WORD_LEN) {
        return CICERO_TOO_MANY_TILES;
    }
    m->tiles[m->len++] = tile;
    return CICERO_OK;
}

struct legal_moves
{
    move_t *b;
    size_t  size;
    size_t  capacity;
};
typedef struct legal_moves legal_moves_t;

legal_moves_t legal_moves_make()
{
    legal_moves_t m;
    m.b = NULL;
    m.size = 0;
    m.capacity = 0;
    return m;
}

void legal_moves_destroy(legal_moves_t *m)
{
    free(m->b);
    m->capacity = 0;
    m->size = 0;
}

size_t zumax(size_t a, size_t b) { return a > b ? a : b; }

int legal_moves_push(legal_moves_t *m, const move_t *move)
{
    assert(m->size <= m->capacity);
    if (m->size == m->capacity) {
        const size_t newcap = zumax(m->capacity * 1.5, 8);
        move_t *n = realloc(m->b, newcap * sizeof(*m->b));
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
    legal_moves_t moves = legal_moves_make();
    assert_that(moves.size, is_equal_to(0));
    legal_moves_destroy(&moves);
}

Ensure(LegalMoves, add_legal_moves)
{
    int rc;
    legal_moves_t moves = legal_moves_make();
    move_t move;

    move = move_make("HELLO", 42, CICERO_HORZ);
    assert_that(move_is_valid(&move), is_equal_to(CICERO_OK));
    rc = legal_moves_push(&moves, &move);
    assert_that(rc, is_equal_to(0));
    assert_that(moves.size, is_equal_to(1));

    move = move_make("WORLD", 7, CICERO_VERT);
    assert_that(move_is_valid(&move), is_equal_to(CICERO_OK));
    rc = legal_moves_push(&moves, &move);
    assert_that(rc, is_equal_to(0));
    assert_that(moves.size, is_equal_to(2));

    move = move_make("GEeZe", 9, CICERO_HORZ);
    assert_that(move_is_valid(&move), is_equal_to(CICERO_OK));
    rc = legal_moves_push(&moves, &move);
    assert_that(rc, is_equal_to(0));
    assert_that(moves.size, is_equal_to(3));

    assert_that(moves.b[0].tiles, is_equal_to_string("HELLO"));
    assert_that(moves.b[1].tiles, is_equal_to_string("WORLD"));
    assert_that(moves.b[2].tiles, is_equal_to_string("GEeZe"));

    const int start_size = 3;
    char buf[] = "PIZZA_";
    size_t pos = strlen(buf) - 1;
    for (int i = 0; i < 26; ++i) {
        buf[pos] = 'A' + i;
        move = move_make(&buf[0], i, CICERO_VERT);
        assert_that(move_is_valid(&move), is_equal_to(CICERO_OK));
        rc = legal_moves_push(&moves, &move);
        assert_that(rc, is_equal_to(0));
        assert_that(moves.size, is_equal_to(start_size + i + 1));
    }

    assert_that(moves.b[0].tiles, is_equal_to_string("HELLO"));
    assert_that(moves.b[1].tiles, is_equal_to_string("WORLD"));
    assert_that(moves.b[2].tiles, is_equal_to_string("GEeZe"));
    for (int i = 0; i < 26; ++i) {
        buf[pos] = 'A' + i;
        assert_that(moves.b[i+start_size].tiles, is_equal_to_string(buf));
    }

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


#if 0
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
#endif
