#ifdef __GNUC__
#define UNUSED(x) UNUSED_##x __attribute__((__unused__))
#else
#define UNUSED(x) UNUSED_##x
#endif

#include "erl_nif.h"

static ERL_NIF_TERM _fisr(ErlNifEnv *env, int UNUSED(arc),
                           const ERL_NIF_TERM(argv[])) {
  double number;

  enif_get_double(env, argv[0], &number);
  double y = number;
  double x2 = y * 0.5;
  int64_t i = *(int64_t *)&y;
  i = 0x5fe6eb50c7b537a9 - (i >> 1);
  y = *(double *)&i;
  y = y * (1.5 - (x2 * y * y)); // 1st iteration

  return enif_make_double(env, y);
}

static ErlNifFunc nif_funcs[] = {
    {"_fisr", 1, _fisr, 1}
};

ERL_NIF_INIT(Elixir.FISR.Nif, nif_funcs, NULL, NULL, NULL, NULL)
