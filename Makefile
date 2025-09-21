AS = nasm
CC = gcc
LD = ld
CFLAGS = -ffreestanding -m32 -nostdlib -Iheaders
LDFLAGS = -m elf_i386 -T linker.ld
ASMFLAGS = -f elf32
KERNEL_C = kernel.c
KERNEL_ASM = kernel.asm
PIC_ASM = pic.asm
KERNEL_OBJ_C = kernel_c.o
KERNEL_OBJ_ASM = kernel_asm.o
PIC_OBJ_ASM = pic.o
KERNEL_BIN = kernel.bin
ISO_DIR = iso
ISO_BOOT = $(ISO_DIR)/boot
ISO_BIN = venetux.iso

GREEN = \033[32m
RESET = \033[0m
YELLOW = \033[33m

all: iso

$(KERNEL_OBJ_C): $(KERNEL_C)
	@echo "$(YELLOW)Compilando $(KERNEL_C)...$(RESET)"
	$(CC) $(CFLAGS) -c $(KERNEL_C) -o $(KERNEL_OBJ_C)
	@if [ $$? -eq 0 ]; then echo "$(GREEN)Compilazione $(KERNEL_C) riuscita.$(RESET)"; fi
	
$(KERNEL_OBJ_ASM): $(KERNEL_ASM)
	@echo "$(YELLOW)Compilando $(KERNEL_ASM)...$(RESET)"
	$(AS) $(ASMFLAGS) $(KERNEL_ASM) -o $(KERNEL_OBJ_ASM)
	@if [ $$? -eq 0 ]; then echo "$(GREEN)Compilazione $(KERNEL_ASM) riuscita.$(RESET)"; fi
$(KERNEL_BIN): $(KERNEL_OBJ_ASM) $(KERNEL_OBJ_C)
	@echo "$(YELLOW)Linkando $(KERNEL_OBJ_ASM) e $(KERNEL_OBJ_C) per creare $(KERNEL_BIN)...$(RESET)"
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(KERNEL_OBJ_ASM) $(KERNEL_OBJ_C)
	@if [ $$? -eq 0 ]; then echo "$(GREEN)Creazione del kernel $(KERNEL_BIN) riuscita.$(RESET)"; fi

iso: $(KERNEL_BIN)
	@echo "$(YELLOW)Creando l'ISO...$(RESET)"
	mkdir -p $(ISO_BOOT)/grub
	cp $(KERNEL_BIN) $(ISO_BOOT)/
	echo 'set timeout=0' > $(ISO_BOOT)/grub/grub.cfg
	echo 'set default=0' >> $(ISO_BOOT)/grub/grub.cfg
	echo 'menuentry "Ok" {' >> $(ISO_BOOT)/grub/grub.cfg
	echo '  multiboot /boot/$(KERNEL_BIN)' >> $(ISO_BOOT)/grub/grub.cfg
	echo '  boot' >> $(ISO_BOOT)/grub/grub.cfg
	echo '}' >> $(ISO_BOOT)/grub/grub.cfg
	grub-mkrescue -o $(ISO_BIN) $(ISO_DIR) --compress=xz
	@if [ $$? -eq 0 ]; then echo "$(GREEN)Creazione ISO $(ISO_BIN) riuscita.$(RESET)"; fi

all: $(KERNEL_BIN)
	@echo "$(YELLOW)Avviando la iso su QEMU...$(RESET)"
	clear
	qemu-img create -f raw disk.raw 256M
	qemu-system-i386 -cdrom $(ISO_BIN) -hda disk.raw -audiodev pa,id=speaker -machine pcspk-audiodev=speaker -net nic,model=rtl8139 -net user -m 512

.PHONY: clean

clean:
	@echo "Pulizia dei file generati..."
	rm -f $(KERNEL_OBJ_ASM) $(KERNEL_OBJ_C) $(KERNEL_BIN) disk.raw $(ISO_BIN)
	rm -rf $(ISO_DIR)
	@echo "Pulizia completata."