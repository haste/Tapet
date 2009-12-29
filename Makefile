include config.mk

all: opt tapet

opt:
	@echo build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

tapet: ${OBJNAME}
	@echo CC -o $@
	@${CC} -o $@ ${OBJNAME} ${LDFLAGS}
