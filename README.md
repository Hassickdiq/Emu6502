# EMU6502 - 6502 & Özel Mimari Sanal Makinesi (VM) Dokümantasyonu

## Genel Bakış
**EMU650216**, standart MOS Technology 6502 komut seti mimarisini (ISA) tam olarak replike eden ve bunun üzerine özel 16-bit/20-bit mimari eklentileri sunan kapsamlı bir Sanal Makine (VM) emülatör projesidir. Sistem; bellek yönetimi, CPU komut döngüleri, Kesme (Interrupt) yönetimi ve BCD (Binary Coded Decimal) destekli Aritmetik Mantık Birimi'ni (ALU) modüler bir C++ altyapısıyla birleştirir. `raylib` kütüphanesi entegrasyonu sayesinde grafiksel donanım çıktısı alınmasına olanak tanır.

## Sistem Mimarisi

### Yazmaçlar (Registers)
Standart 6502'nin 8-bitlik yazmaç yapısı, özel mimari için genişletilmiştir:
- **16-bit Yazmaçlar (RegSet0):** `AX`, `BX`, `CX`, `DX`, `XX`, `YY`
  - Özel `LOW`, `HIGH`, `FULL` parametreleri ile bu yazmaçların alt ve üst 8-bitlik kısımlarına veya tamamına erişim sağlanır (Örn: `AX`'in alt 8 biti `A` registerı gibi davranır).
- **20-bit Yazmaçlar (RegSet1):** `BP` (Base Pointer), `SP` (Stack Pointer), `PC` (Program Counter)
  - Program sayacı ve yığın işaretçisi 20-bit adresleme alanı ile daha geniş bellek yönetimini destekler.

### Durum Bayrakları (Flags)
İşlemci durumunu kontrol eden 8 adet bayrak bulunur:
- **C (CF):** Carry (Elde)
- **Z (ZF):** Zero (Sıfır)
- **I (IF):** Interrupt Disable (Kesme Engelleme)
- **D (DF):** Decimal Mode (BCD formatında matematik işlemleri için)
- **B (BF):** Break (Yazılımsal kesme)
- **S (SF):** Stack
- **V (VF):** Overflow (Taşma)
- **N (NF):** Negative (Negatif)

## Modül Detayları

### 1. Bellek Yönetimi (`memory.hpp` & `memory.cpp`)
- **Boyut:** Varsayılan bellek boyutu `65536` byte (64 KB) olarak ayarlanmıştır (`MEMORY_SIZE`), ancak 20-bitlik adres yolu potansiyeliyle genişletilebilir.
- **Yığın (Stack) Operasyonları:** 
  - `Push8Stack` / `Pull8Stack`: 8-bit veri itme/çekme.
  - `Push16Stack` / `Pull16Stack`: 16-bit (word) veri itme/çekme işlemleri.
- **Adresleme Fonksiyonları:** Bellek üzerinden 8-bit (`ReadByte`/`WriteByte`), 16-bit (`ReadWord`/`WriteWord`) ve genişletilmiş 20-bit (`Read20bit`) bellek okuma desteklenir. Endianness (Byte sıralaması) LSB-first mantığıyla çalışır.

### 2. Aritmetik ve Mantık Birimi (`alu.hpp`)
Tüm matematiksel ve mantıksal işlemler ALU sınıfı içerisinde izole edilmiştir.
- **Desteklenen Operasyonlar:** `Add` (ADC), `Sub` (SBC), `And`, `Or`, `Xor`, `Asl`, `Lsr`, `Rol`, `Ror`, `Cmp`, `Bit`, `Inc`, `Dec`.
- **Decimal Mod (BCD) Desteği:** `DF` (Decimal Flag) aktif edildiğinde `Add` ve `Sub` fonksiyonları standart ikilik (binary) işlemler yerine 10'luk taban düzeltmeleri uygular. Taşıma (Carry) ve yarı elde mantığı donanıma birebir sadık kalınarak hesaplanır.

### 3. İşlemci Çekirdeği (`cpu.hpp` & `cpu.cpp`)
6502 opcode'larının (komutlarının) çözümlendiği ve çalıştırıldığı ana döngü modülüdür.
- **Komut Döngüsü:** `Run()` fonksiyonu üzerinden PC (Program Counter) 1 byte ilerletilerek opcode alınır ve `ExecuteOpcode` fonksiyonunda işlenir.
- **Adresleme Modları (Addressing Modes):**
  - *Immediate, ZeroPage, ZeroPage,X, ZeroPage,Y, Absolute, Absolute,X, Absolute,Y, Indirect, Indirect,X, Indirect,Y, Relative* gibi standart 6502 modlarının hepsi gerçeklenmiştir.
- **Dallanma (Branching):** Bayrak durumlarına dayalı göreceli atlamalar (`BCC`, `BCS`, `BEQ`, `BMI`, `BNE`, `BPL`, vb.).
- **Donanım Kesmeleri (IRQs) ve Yazılım Kesmeleri:** `IrqExec` tetiklendiğinde veya `BRK` komutu okunduğunda sistem PC ve Flag durumunu güvenli şekilde Stack'e (yığına) atarak Kesme Yönlendirme (Interrupt Vector) adresine sıçrar (`0xFFFE`). 

### 4. VM Parametreleri (`vmp.hpp`)
Sistemin genel konfigürasyonunu tutan kısımdır.
- `VM_DEBUG`: Makinenin konsol üzerinden anlık PC, Opcode ve yazmaç dökümü yapmasını (debugger modunu) açıp kapatır.
- `<raylib.h>` dahil edilmiştir, bu sayede sistem ileride VRAM bellek bölgesini doğrudan grafik ekrana yansıtacak şekilde genişletilebilir.
