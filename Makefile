ifeq ($(OS),Windows_NT)
mkdir = mkdir $(subst /,\,$(1)) > nul 2>&1 || (exit 0)
rmrf = rmdir $(subst /,\,$(1)) /s /q > nul 2>&1 || (exit 0)
ext = .exe
else
mkdir = mkdir -p $(1)
rmrf = rm -rf $(1) > /dev/null 2>&1 || true
ext =
endif

default: bin/nnucat$(ext)

bin:
	$(call mkdir,bin)

bin/nnucat$(ext): bin
	$(CC) $(CFLAGS) -o bin/nnucat$(ext) main.c

clean:
	$(call rmrf,bin)
