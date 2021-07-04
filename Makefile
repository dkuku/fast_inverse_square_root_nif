ERLANG_PATH = $(shell erl -eval 'io:format("~s", [lists:concat([code:root_dir(), "/erts-", erlang:system_info(version), "/include"])])' -s init stop -noshell)
CFLAGS = -g -O3 -pedantic -Wall -Wextra -I$(ERLANG_PATH)

ifneq ($(OS),Windows_NT)
	CFLAGS += -fPIC

	ifeq ($(shell uname),Darwin)
		LDFLAGS += -dynamiclib -undefined dynamic_lookup
	endif
endif

priv/lib_fast_inverse_square_root.so: clean
	@$(CC) $(CFLAGS) -shared $(LDFLAGS) -o $@ c_src/fast_inverse_square_root_nif.c

clean:
	@$(RM) -r priv/*
