DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

# Get the project-relative output directory.
# We do this before changing the CWD.
PROJECT_INTERMEDIATE_DIR:=$(INTERMEDIATE_DIR)/kernel

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=$(SYSROOT_DIR)
PREFIX?=/usr
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(patsubst %.o,$(PROJECT_INTERMEDIATE_DIR)/%.o,$(KERNEL_ARCH_OBJS)) \
$(PROJECT_INTERMEDIATE_DIR)/kernel/kernel.o \
$(patsubst interrupts/exceptions/%.c,$(PROJECT_INTERMEDIATE_DIR)/interrupts/exceptions/%.o,$(wildcard interrupts/exceptions/*.c)) \
$(patsubst interrupts/irqs/%.c,$(PROJECT_INTERMEDIATE_DIR)/interrupts/irqs/%.o,$(wildcard interrupts/irqs/*.c)) \
$(patsubst drivers/%.c,$(PROJECT_INTERMEDIATE_DIR)/drivers/%.o,$(wildcard drivers/*.c)) \

OBJS=\
$(PROJECT_INTERMEDIATE_DIR)/$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(PROJECT_INTERMEDIATE_DIR)/$(ARCHDIR)/crtend.o \


LINK_LIST=\
$(LDFLAGS) \
$(PROJECT_INTERMEDIATE_DIR)/$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(PROJECT_INTERMEDIATE_DIR)/$(ARCHDIR)/crtend.o \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S

all: $(PROJECT_INTERMEDIATE_DIR)/phoibos.kernel install

$(PROJECT_INTERMEDIATE_DIR)/$(ARCHDIR)/asm/%.o: $(ARCHDIR)/asm/%.S
	mkdir -p $(@D)
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

$(PROJECT_INTERMEDIATE_DIR)/interrupts/exceptions/%.o: interrupts/exceptions/%.c
	mkdir -p $(@D)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

$(PROJECT_INTERMEDIATE_DIR)/interrupts/irqs/%.o: interrupts/irqs/%.c
	mkdir -p $(@D)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

$(PROJECT_INTERMEDIATE_DIR)/drivers/%.o: drivers/%.c
	mkdir -p $(@D)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

$(PROJECT_INTERMEDIATE_DIR)/phoibos.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	mkdir -p $(@D)
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	i686-elf-grub-file --is-x86-multiboot $(PROJECT_INTERMEDIATE_DIR)/phoibos.kernel

$(PROJECT_INTERMEDIATE_DIR)/$(ARCHDIR)/crtbegin.o $(PROJECT_INTERMEDIATE_DIR)/$(ARCHDIR)/crtend.o:
	mkdir -p $(@D)
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

$(PROJECT_INTERMEDIATE_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

$(PROJECT_INTERMEDIATE_DIR)/%.o: %.S
	mkdir -p $(@D)
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -rf $(PROJECT_INTERMEDIATE_DIR)

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R -p include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: $(PROJECT_INTERMEDIATE_DIR)/phoibos.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp $(PROJECT_INTERMEDIATE_DIR)/phoibos.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
