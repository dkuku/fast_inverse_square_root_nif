#ifdef __GNUC__
#define UNUSED(x) UNUSED_##x __attribute__((__unused__))
#else
#define UNUSED(x) UNUSED_##x
#endif

#include "erl_nif.h"
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

static ERL_NIF_TERM _fisr(ErlNifEnv *env, int UNUSED(arc),
                          const ERL_NIF_TERM(argv[])) {
  double number_double;
  enif_get_double(env, argv[0], &number_double);

  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  float number = (float)number_double;

  x2 = number * 0.5F;
  y = number;
  i = *(long *)&y;           // evil floating point bit level hacking
  i = 0x5f3759df - (i >> 1); // what the fuck?
  y = *(float *)&i;

  return enif_make_double(env, y);
}

static ERL_NIF_TERM _fisr1(ErlNifEnv *env, int UNUSED(arc),
                           const ERL_NIF_TERM(argv[])) {
  double number_double;
  enif_get_double(env, argv[0], &number_double);

  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  float number = (float)number_double;

  x2 = number * 0.5F;
  y = number;
  i = *(long *)&y;           // evil floating point bit level hacking
  i = 0x5f3759df - (i >> 1); // what the fuck?
  y = *(float *)&i;
  y = y * (threehalfs - (x2 * y * y)); // 1st iteration

  return enif_make_double(env, y);
}

// float fisr2( float number )
static ERL_NIF_TERM _fisr2(ErlNifEnv *env, int UNUSED(arc),
                           const ERL_NIF_TERM(argv[])) {
  double number_double;
  enif_get_double(env, argv[0], &number_double);

  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  float number = (float)number_double;

  x2 = number * 0.5F;
  y = number;
  i = *(long *)&y;           // evil floating point bit level hacking
  i = 0x5f3759df - (i >> 1); // what the fuck?
  y = *(float *)&i;
  y = y * (threehalfs - (x2 * y * y)); // 1st iteration
  y = y * (threehalfs - (x2 * y * y)); // 2nd iteration, this can be removed

  return enif_make_double(env, y);
}

static ErlNifFunc nif_funcs[] = {
    {"_fisr", 1, _fisr, 1}, {"_fisr1", 1, _fisr1, 1}, {"_fisr2", 1, _fisr2, 1}};

/* Change Elixir.NIF to the name you use in the project */
ERL_NIF_INIT(Elixir.FISR.Nif, nif_funcs, NULL, NULL, NULL, NULL)
